#include "SatSolver.h"

int64_t SatSolver::calculateModelCost()
{
    cost = 0;
    for (auto& wlit: sum) {
        int32_t signed_lit = wlit.lit;
        int64_t val = model[abs(signed_lit)] ? 1 : 0;
        if (signed_lit < 0) val = 1 - val;  // Negate the literal
        cost +=  wlit.weight * val;
    }
    return cost;
}

int64_t SatSolver::tightModel()
{

    if (maximize and cost == upper_bound) return 0;
    if (not maximize and cost == lower_bound) return 0;

    int64_t ini_cost = cost;
    for (auto& wlit: sum) {
        int32_t signed_lit = wlit.lit;
        int32_t lit = abs(signed_lit);
        // Let us calculate the potential increment by flipping the literal
        int64_t inc = wlit.weight * (signed_lit > 0 ? 1 : -1);
        if (model[lit]) inc = -inc;
        // See if we get some imporvement
        if (maximize) {
            if (inc <= 0 or cost + inc > upper_bound) continue;

        } else {
            if (inc >= 0 or cost + inc < lower_bound) continue;
        }
        // Try to flip the literal
        if (tryFlipLiteral(lit)) {
            cost += inc;
            model[lit] = not model[lit];
        }
    }

    cout << "Tightening cost: " << ini_cost << " -> " << cost << '.' << endl;
    return cost - ini_cost;
}

bool SatSolver::tryFlipLiteral(int32_t literal)
{
    // For all clauses, check that this is not the only literal
    // that satisfies the clause
    const vector<vector<int32_t>>& CL = clauses.getClauses();

    for (const auto& c: CL) {
        // See how many literals are asserted
        int nlit = 0;
        int32_t which;
        for (auto signed_lit: c) {
            if ((signed_lit > 0 and model[signed_lit]) or
                (signed_lit < 0 and not model[-signed_lit])) {
                ++nlit;
                if (nlit > 1) continue;
                which = abs(signed_lit);
            }
        }
        // Check if it is the only literal asserted in the clause
        if (which == literal) return false;
    }

    return true;
}

bool SatSolver::solve()
{
    // Add all clauses to the solver
    for (auto& c : clauses.getClauses()) solver.addClause(c);

    IncPBConstraint costFunction;

    bool bounds_defined = false;

    // Encode the cost function
    if (hasCostFunction() > 0) {

        int64_t maxsum = 0;
        int64_t minsum = 0;
        for (auto& wl: sum) {
            if (wl.weight > 0) maxsum += wl.weight;
            else minsum += wl.weight;
        }

        //cout << "minsum: " << minsum << "  maxsum: " << maxsum << endl;

        if (not has_lowerbound) lower_bound = minsum;
        else lower_bound = max(lower_bound, minsum);

        if (not has_upperbound) upper_bound = maxsum;
        else upper_bound = min(upper_bound, maxsum);

        bounds_defined = true;
        if (has_lowerbound and has_upperbound) {
            costFunction = IncPBConstraint(sum, BOTH, upper_bound, lower_bound);
        } else if (has_lowerbound) {
            costFunction = IncPBConstraint(sum, GEQ, lower_bound);
        } else if (has_upperbound) {
            costFunction = IncPBConstraint(sum, LEQ, upper_bound);
        } else {
            bounds_defined = false;
        }

        if (bounds_defined) {
            costClauses.clearDatabase();
            pb2cnf.encodeIncInital(costFunction, costClauses, auxVars);
            for (auto& clause : costClauses.getClauses()) solver.addClause(clause);
        }

    }


    satisfiable = false;

    // Iterate shrinking the bounds until unsatisfiable
    while (true) {
        cout << "Finding SAT model in [" << lower_bound << ',' << upper_bound << "]. ";


        // Print stats
        cout << "Vars: " << solver.nVars()
             << ", Original clauses: " << solver.nClauses()
             << ", Learned: " << solver.nLearnts() << ". " << flush;

        if (not solver.solve()) {
            cout << "(UNSAT)" << endl;
            break;
        }

        satisfiable = true;

        // Get the model
        solver.getModel(model);

        // If no cost function, we are done
        if (not hasCostFunction()) {
            cout << "(SAT)" << endl;
            break;
        }

        calculateModelCost();

        // Try to improve the cost function
        tightModel();
        //cout << "[SAT (cost: " << getCost() << ")]" << endl;

        // Now get tighter bounds depending on maximization or minimization
        int64_t current_cost = getCost();
        if (maximize) {
            if (current_cost == upper_bound) {
                cout << endl;
                break;
            }
            lower_bound = current_cost + 1;
            has_lowerbound = true;
            if (not bounds_defined) {
                costFunction = IncPBConstraint(sum, GEQ, lower_bound);
            } else {
                costFunction.encodeNewGeq(lower_bound, costClauses, auxVars);
            }

        } else {
            if (current_cost == lower_bound) {
                cout << endl;
                break;
            }
            upper_bound = current_cost - 1;
            has_upperbound = true;
            if (not bounds_defined) {
                costFunction = IncPBConstraint(sum, LEQ, upper_bound);
            } else {
                costFunction.encodeNewLeq(upper_bound, costClauses, auxVars);
            }
        }

        if (not bounds_defined) {
            costClauses.clearDatabase();
            pb2cnf.encodeIncInital(costFunction, costClauses, auxVars);
            bounds_defined = true;
        }

        // Add the new clauses
        for (auto& clause : costClauses.getClauses()) solver.addClause(clause);
    }

    return satisfiable;
}

void SatSolver::addFormula(const BDD& f, bool verbose)
{
    if (verbose) cout << "  Adding formula" << endl;

    // Trivial cases
    if (f.IsOne()) return; // Nothing to do
    if (f.IsZero()) return clauses.addUnsat();

    // Normal case: extract prime by prime

    BDD g = !f;
    BDD remainder = g;

    vecLiterals clause;

    while (not remainder.IsZero()) {
        BDD prime = remainder.LargestCube();
        prime = prime.MakePrime(g);
        remainder *= !prime;

        clause.clear();
        // Store the cube as a clause
        while (not prime.IsOne()) {

            int idx = prime.NodeReadIndex();
            BDD v = mgr.bddVar(idx);
            BDD cof = prime.Cofactor(v);
            if (not cof.IsZero()) {
                // Positive literal (negative in the CNF)
                clause.push_back(-idx);
                prime = cof;
            } else {
                clause.push_back(idx);
                prime = prime.Cofactor(!v);
            }
        }

        clauses.addClause(clause);
        if (verbose) {
            cout << "  Adding clause";
            for_each(clause.begin(), clause.end(), [](int i)->void {std::cout << ' ' << i;});
            cout << endl;
        }
    }
}
