#ifndef PBFORMULA_H
#define PBFORMULA_H
#include <vector>
#include <stdint.h>
#include<iostream>

class PBFormula{
private:
    std::vector< int64_t > weights;
    std::vector< int32_t > literals;
public:
    PBFormula(const std::vector< int64_t > & weights, const std::vector< int32_t > & literals);
    std::vector< int64_t > getWeights();
    std::vector< int32_t > getLiterals();
    void addPair(int64_t weight, int32_t literal);

};

#endif // PBFORMULA_H
