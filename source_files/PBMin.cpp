#include "PBMin.h"

PBMin::PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction, SEARCH_TYPE p_searchType):constraints(p_constraints),costFunction(p_costFunction),searchType(p_searchType)
{

}

std::vector<PBConstraint> PBMin::getConstraints(){
    return constraints;
}

PBFormula PBMin::getCostFunction(){
    return costFunction;
}

SEARCH_TYPE PBMin::getSearchType(){
    return searchType;
}

int32_t PBMin::getFirstFreshVariable(){
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

int64_t PBMin::getCostFunctionMax(){
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
int64_t PBMin::getCostFunctionMin(){
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

void PBMin::solve(){
    //depenen del tipus de cerca fer una cosa o una altra
    //estaria guay que no es fes lencoding sencer cada cop, nomes canviar lencoding de la cost function que es lunic que canvia. es podrien fer dos cnf i ajuntarles cada cop

    //first find firstFreshVariable
    int32_t firstFreshVariable = getFirstFreshVariable();
    std::vector< std::vector< int32_t > > cnf;

    //fer encoding de totes les constraints a la cnf
    PB2CNF pb2cnf;
    // firstFreshVariable = pb2cnf.encodeLeq(weights, literals, 1, cnf, firstFreshVariable) + 1;
    //fer encoding de la cost function amb el valor maxim
    //per fer aixo es necessari trobar el valor maxim i minim de la cost function possible
    //TODO: 

}
