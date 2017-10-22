#ifndef SATSOLVER_H
#define	SATSOLVER_H

#include <cassert>
#include <vector>

#include "cuddObj.hh"

#include "VectorClauseDatabase.h"
#include "BasicSATSolver.h"
#include "PBConfig.h"
#include "pb2cnf.h"
#include "formula.h"

using namespace std;
using namespace PBLib;

typedef vector<Lit> vecLiterals;
typedef vector<WeightedLit> linearFunction;

/**
 * @class BoolFunc
 * @author Jordi Cortadella
 * @date 13/08/17
 * @file SatSolver.h
 * @brief Class to represent boolean functions either as BDDs (Cudd)
 * or formulae (using Pblib formula class).
 */
class BoolFunc
{
private:
    bool useBDD;
    BDD bdd;
    Formula form;
public:
    /**
     * @brief Default constructor
     */
    BoolFunc() : useBDD(true) {};

    /**
     * @brief Constructor with a BDD.
     * @param f The function represented as a BDD.
     */
    BoolFunc(const BDD& f) : useBDD(true), bdd(f) {};

    /**
     * @brief Constructor with a formula.
     * @param f The function represented as a formula.
     */
    BoolFunc(const Formula& f) : useBDD(false), form(f) {};

    /**
     * @brief Is it represented as a BDD?
     */
    inline bool isBDD() const {
        return useBDD;
    }

    /**
     * @brief Is it represented as a formula?
     */
    inline bool isFormula() const {
        return not useBDD;
    }

    /**
     * @brief Get the BDD.
     */
    const BDD& getBDD() const {
        assert(useBDD);
        return bdd;
    }

    /**
     * @brief Get the formula.
     */
    const Formula& getFormula() const {
        assert(not useBDD);
        return form;
    }

    // Boolean operations
    BoolFunc operator!() const {
        if (useBDD) return BoolFunc(~bdd);
        return BoolFunc(~form);
    }

    BoolFunc operator~() const {
        if (useBDD) return BoolFunc(~bdd);
        return BoolFunc(~form);
    }

    BoolFunc operator*(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) return BoolFunc(bdd * f.bdd);
        return AND(form, f.form);
    }

    BoolFunc operator*=(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) bdd *= f.bdd;
        else form = AND(form, f.form);
        return *this;
    }

    BoolFunc operator&(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) return BoolFunc(bdd * f.bdd);
        return AND(form, f.form);
    }

    BoolFunc operator&=(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) bdd *= f.bdd;
        else form = AND(form, f.form);
        return *this;
    }

    BoolFunc operator+(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) return BoolFunc(bdd + f.bdd);
        return OR(form, f.form);
    }

    BoolFunc operator+=(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) bdd += f.bdd;
        else form = OR(form, f.form);
        return *this;
    }

    BoolFunc operator|(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) return BoolFunc(bdd + f.bdd);
        return OR(form, f.form);
    }

    BoolFunc operator|=(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) bdd += f.bdd;
        else form = OR(form, f.form);
        return *this;
    }

    BoolFunc operator^(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) return BoolFunc(bdd ^ f.bdd);
        return XOR(form, f.form);
    }

    BoolFunc operator^=(const BoolFunc& f) {
        assert(useBDD == f.useBDD);
        if (useBDD) bdd ^= f.bdd;
        else form = XOR(form, f.form);
        return *this;
    }
};

/**
 * @class SatSolver
 * @author Jordi Cortadella
 * @date 31/07/17
 * @file SatSolver.h
 * @brief Class for a nice interface for a Sat Solver solving PB contraints.
 */
class SatSolver
{
public:
    SatSolver() : use_bdd(true), maximize(true),
        has_lowerbound(false), has_upperbound(false),
        lower_bound(0), upper_bound(0),
        auxVars(1),
        config(make_shared<PBConfigClass>()),
        clauses(config), costClauses(config) {}

    /**
     * @return A new fresh variable.
     */
    inline Lit getNewLiteral() {
        return auxVars.getVariable();
    }

    /**
     * @return The biggest returned var.
     */
    inline Lit lastVar() {
        return auxVars.getBiggestReturnedAuxVar();
    }

    /**
     * @brief Returns the BDD representing a literal (positive or negative)
     * @param lit The literal.
     * @return The BDD representing the literal.
     */
    inline BoolFunc getLiteral(Lit lit) {
        assert (lit != 0 and abs(lit) <= lastVar());
        if (use_bdd) {
            if (lit > 0) return BoolFunc(mgr.bddVar(lit));
            return BoolFunc(~mgr.bddVar(-lit));
        }
        return BoolFunc(LIT(lit));
    }

    /**
     * @return A new fresh variable.
     */
    inline BoolFunc getNewVar() {
        return getLiteral(getNewLiteral());
    }

    /**
     * @brief Gets a formula representing the constant zero or one.
     * @param v Value of the constant.
     * @return The formula representing the constant.
     */
    inline BoolFunc getConstant(bool v) {
        if (use_bdd) return BoolFunc(v ? mgr.bddOne() : mgr.bddZero());
        return BoolFunc(v ? _true_ : _false_);
    }

    /**
     * @brief Sets the solver to maximize the cost function.
     */
    inline void setMaximize () {
        maximize = true;
    }

    /**
     * @brief Sets the solver to minimize the cost function.
     */
    inline void setMinimize () {
        maximize = false;
    }

    /**
     * @brief Adds a unit clause to the database
     * @param lit The literal of the clause.
     */
    void addClause(Lit lit) {
        clauses.addClause(lit);
    }

    /**
     * @brief Adds a clause to the database.
     * @param c The clause to be added.
     */
    void addClause(const vecLiterals& c) {
        clauses.addClause(c);
    }

    /**
     * @brief Adds a formula to the database.
     * @param f The formula to be added.
     * @param verbose If asserted, some information is printed.
     */
    void addFormula(const BoolFunc& f, bool verbose = false) {
        if (f.isBDD()) return addFormula(f.getBDD(), verbose);
        clauses.addFormula(f.getFormula(), auxVars);
    }


    /**
     * @brief Adds a new term to the cost function.
     * @param weight Weight of the literal.
     * @param lit Literal.
     */
    void addCostTerm(int64_t weight, Lit lit) {
        sum.push_back( {lit, weight});
    }

    /**
     * @brief Defines the lower bound of the cost function
     * @param bound The lower bound.
     */
    inline void defineLowerBound(int64_t bound) {
        lower_bound = bound;
        has_lowerbound = true;
    }

    /**
     * @brief Defines the upper bound of the cost function
     * @param bound The upper bound.
     */
    inline void defineUpperBound(int64_t bound) {
        upper_bound = bound;
        has_upperbound = true;
    }

    /**
     * @return True if a cost funciton has been defined, and false otherwise.
     */
    inline bool hasCostFunction() const {
        return sum.size() > 0;
    }

    /**
     * @brief Solves the PB problem.
     * @return True if satisfiable, and false otherwise.
     */
    bool solve();

    /**
     * @brief Indicates whether the formula is satisfiable.
     * @return True if satisfiable, false if not satisfiable.
     */
    inline bool isSatisfiable() const {
        return satisfiable;
    }

    /**
     * @return The model obtained after the last call to the sat solver.
     */
    const vector<bool>& getModel() const {
        return model;
    }

    /**
     * @return The cost of the model after SAT.
     */
    inline int64_t getCost() const {
        return cost;
    }

private:
    bool use_bdd;                           // Indicates whether to use BDDs of Formula
    bool maximize;                          // True: maximize, False: minimize
    bool has_lowerbound;                    // Indicates whether a lower bound has been defined.
    bool has_upperbound;                    // Indicates whether an upper bound has been defined.
    int64_t lower_bound;                    // Lower bound for the cost function.
    int64_t upper_bound;                    // Upper bound for the cost function.
    Cudd mgr;                               // BDD manager
    AuxVarManager auxVars;                  // Manager of variables
    BasicSATSolver solver;                  // Sat solver (minisat)
    PBConfig config;                        // Configuration
    PB2CNF pb2cnf;                          // Encoder from PB constraints to CNF clauses
    VectorClauseDatabase clauses;           // Clauses modeling the constraints of the problem
    VectorClauseDatabase costClauses;       // Clauses modeling the cost function
    linearFunction sum;                     // Weighted sum of literals (to build de cost function)
    bool satisfiable;                       // Indicates whether the formula is satisfiable
    vector<bool> model;                     // Model obtained from the last call to the SAT solver
    int64_t cost;                           // Total cost of the model

    /**
     * @brief Calculates the cost of the model.
     * @return The cost of the model.
     */
    int64_t calculateModelCost();

    /**
     * @brief Find a tighter model after solving SAT.
     * @return Returns the incremental modification of the cost function.
     */
    int64_t tightModel();

    /**
     * @brief Tries to flip the literal in the model.
     * @param literal The literal to be flipped.
     * @return True if the literal can be flipped.
     */
    bool tryFlipLiteral(int32_t literal);

    /**
     * @brief Adds a new formula represented as a BDD.
     * @param f The formula to be added.
     * @param verbose If asserted, some information is printed.
     */
    void addFormula(const BDD& f, bool verbose);

};

#endif // SATSOLVER_H
