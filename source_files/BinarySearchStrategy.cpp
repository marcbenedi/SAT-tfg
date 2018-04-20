#include "BinarySearchStrategy.h"

BinarySearchStrategy::BinarySearchStrategy(){}

void BinarySearchStrategy::init(const PBMin & p){
    firstFreshVariable = p.getFirstFreshVariable();

    PB2CNF pb2cnf;

    //Encoding constraints
    for (size_t i = 0; i < p.getConstraints().size(); i++) {
        firstFreshVariable = pb2cnf.encodeLeq(p.getConstraints()[i].getPBFormula().getWeights(), p.getConstraints()[i].getPBFormula().getLiterals(), p.getConstraints()[i].getK(), cnf_constraints, firstFreshVariable) + 1;
    }

    left = p.getCostFunctionMin();
    right = p.getCostFunctionMax();
}

void BinarySearchStrategy::loop(void (Solver::*solver)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *s, const PBMin & pm){

    std::vector< int32_t > temp_model;
    PB2CNF pb2cnf;
    std::vector< std::vector< int32_t > > cnf;
    min = right + 1;
    bool end = false;

    while (not end) {
        if(left<=right){
            cnf.clear();
            cnf.insert(cnf.end(),cnf_constraints.begin(),cnf_constraints.end());

            int64_t k = (left+right)/2;

            if (left == right) {
                //no more values to try
                end = true;
            }

            firstFreshVariable = pb2cnf.encodeLeq(pm.getCostFunction().getWeights(), pm.getCostFunction().getLiterals(), k, cnf, firstFreshVariable) + 1;

            bool t_sat;
            (s->*solver)(temp_model, cnf,t_sat);

            if (t_sat) {
                min = k;
                right = k-1;
                model = temp_model;
            }
            else{
                if (min == k + 1) {
                    end = true;
                }
                left = k+1;
            }
        }
        else{
            end = true;
        }

    }

    if (model.size() != 0) {
        // std::cout << "SAT" << '\n';
        // std::cout << "min " << std::to_string(min) << '\n';
        // for (size_t i = 0; i < model.size(); i++) {
        //     std::cout << std::to_string(model[i]) << " ";
        // }
        // std::cout << '\n';
        sat = true;
    }
    else{
        // std::cout << "UNSAT" << '\n';
        sat = false;
    }




}

void BinarySearchStrategy::end(){

}
