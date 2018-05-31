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
    /**
     * Constructs a pseudo-boolean formula of the type weights[0]literals[0] + ... + weights[n-1]literals[n-1]
     *@param weights
     *@param literals
     */
    PBFormula(const std::vector< int64_t > & weights, const std::vector< int32_t > & literals);

    std::vector< int64_t > getWeights() const;
    std::vector< int32_t > getLiterals() const;
    void addPair(int64_t weight, int32_t literal);

};

#endif // PBFORMULA_H
