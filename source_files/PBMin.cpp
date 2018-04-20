#include "PBMin.h"

PBMin::PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction):constraints(p_constraints),costFunction(p_costFunction)
{

}

std::vector<PBConstraint> PBMin::getConstraints() const{
    return constraints;
}

PBFormula PBMin::getCostFunction() const{
    return costFunction;
}

int32_t PBMin::getFirstFreshVariable() const{
    int32_t max = -1;
    for (size_t i = 0; i < constraints.size(); i++) {
        for (size_t k = 0; k < constraints[i].getPBFormula().getLiterals().size(); k++) {
            if (max < abs(constraints[i].getPBFormula().getLiterals()[k])) {
                max = abs(constraints[i].getPBFormula().getLiterals()[k]);
            }
        }
    }
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (max < abs(costFunction.getLiterals()[i])) {
            max = abs(costFunction.getLiterals()[i]);
        }
    }
    return max+1;
}

int64_t PBMin::getCostFunctionMax() const{
    std::map<int32_t,int64_t> positive;
    std::map<int32_t,int64_t> negative;
    std::set<int32_t> lits;
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (costFunction.getLiterals()[i] < 0) {
            negative[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        else{
            positive[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        lits.insert(abs(costFunction.getLiterals()[i]));
    }
    int64_t max = 0;

    for (std::set<int32_t>::iterator it = lits.begin(); it != lits.end(); it++) {
        int32_t lit = *it;
        max += positive[lit] > negative[lit] ? positive[lit] : negative[lit];
    }

    return max;
}
int64_t PBMin::getCostFunctionMin() const{
    std::map<int32_t,int64_t> positive;
    std::map<int32_t,int64_t> negative;
    std::set<int32_t> lits;
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (costFunction.getLiterals()[i] < 0) {
            negative[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        else{
            positive[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        lits.insert(abs(costFunction.getLiterals()[i]));
    }
    int64_t min = 0;

    for (std::set<int32_t>::iterator it = lits.begin(); it != lits.end(); it++) {
        int32_t lit = *it;
        min += positive[lit] < negative[lit] ? positive[lit] : negative[lit];
    }

    return min;
}
