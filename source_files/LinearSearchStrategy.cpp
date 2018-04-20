#include "LinearSearchStrategy.h"

LinearSearchStrategy::LinearSearchStrategy(){}

void LinearSearchStrategy::init(const PBMin & p){
    firstFreshVariable = p.getFirstFreshVariable();

    PB2CNF pb2cnf;

    //Encoding constraints
    for (size_t i = 0; i < p.getConstraints().size(); i++) {
        firstFreshVariable = pb2cnf.encodeLeq(p.getConstraints()[i].getPBFormula().getWeights(), p.getConstraints()[i].getPBFormula().getLiterals(), p.getConstraints()[i].getK(), cnf_constraints, firstFreshVariable) + 1;
    }
}

void LinearSearchStrategy::loop(void (Solver::*solver)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *s, const PBMin & pm){
    PB2CNF pb2cnf;
    std::vector< std::vector< int32_t > > cnf;
    std::vector< int32_t > temp_model;
    int64_t min_costFunc = pm.getCostFunctionMin();
    int64_t k = pm.getCostFunctionMax();
    min = pm.getCostFunctionMax()+1;

    //Convert costFunction to vector< WeightedLit>
    std::vector< PBLib::WeightedLit> w_costFunction;
    for (size_t i = 0; i < pm.getCostFunction().getWeights().size(); i++) {
        w_costFunction.push_back(PBLib::WeightedLit(pm.getCostFunction().getLiterals()[i],pm.getCostFunction().getWeights()[i]));
    }

    AuxVarManager auxVarManager(firstFreshVariable);
    PBConfig config = std::make_shared< PBConfigClass >();
    VectorClauseDatabase cdb(config, &cnf_constraints);

    IncPBConstraint inc_costFunction = IncPBConstraint(w_costFunction, PBLib::LEQ, k);
    pb2cnf.encodeIncInital(inc_costFunction, cdb, auxVarManager);

    bool end = false;
    while (!end) {
        if (k == min_costFunc) {
            end = true;
        }

        inc_costFunction.encodeNewLeq(k, cdb, auxVarManager);

        bool t_sat;
        (s->*solver)(temp_model, cdb.getClauses(),t_sat);

        if (t_sat) {
            model = temp_model;
            min = k;
            k--;
        }
        else{
            end = true;
        }
    }
    if (model.size() != 0) {
        sat = true;
    }
    else{
        sat = false;
    }

}

void LinearSearchStrategy::end(){

}
