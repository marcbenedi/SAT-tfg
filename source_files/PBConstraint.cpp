#include "PBConstraint.h"

PBConstraint::PBConstraint(const PBFormula & p_formula, int64_t p_k):formula(p_formula), k(p_k)
{}

PBFormula PBConstraint::getPBFormula(){
    return formula;
}
int64_t PBConstraint::getK(){
    return k;
}

void PBConstraint::encode(std::vector< std::vector< int32_t > > & cnf, int32_t & firstFreshVariable){
    PB2CNF pb2cnf;

    firstFreshVariable = pb2cnf.encodeLeq(formula.getWeights(), formula.getLiterals(), k, cnf, firstFreshVariable) + 1;

}

void PBConstraint::setK(int64_t p_k){
    k = p_k;
}
