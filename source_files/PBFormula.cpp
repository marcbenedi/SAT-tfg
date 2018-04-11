#include "PBFormula.h"

PBFormula::PBFormula(const std::vector< int64_t > & p_weights, const std::vector< int32_t > & p_literals){

    if (p_literals.size() != p_weights.size())
    {
      std::cerr << "c [PB++] error: size of weights differ from size of literals, can not encode constraint" << std::endl;
      exit(1);
    }

    if (p_literals.size() == 0) {
        std::cerr << "c [PB++] error: size of (weights OR literals) can not be zero" << std::endl;
        exit(1);
    }

    weights = p_weights;
    literals = p_literals;
}

std::vector< int64_t > PBFormula::getWeights(){
    return weights;
}
std::vector< int32_t > PBFormula::getLiterals(){
    return literals;
}

void PBFormula::addPair(int64_t weight, int32_t literal){
    weights.push_back(weight);
    literals.push_back(literal);
}
