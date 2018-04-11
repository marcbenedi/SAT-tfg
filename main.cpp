#include <iostream>
#include <string>
#include <vector>
#include "pb2cnf.h"

using namespace std;

int main() {

    PB2CNF pb2cnf;

    vector< int64_t > weights = {3,2};
    vector< int32_t > literals = {-1,2};
    vector< vector< int32_t > > formula;
    int32_t firstFreshVariable = 3;
    firstFreshVariable = pb2cnf.encodeLeq(weights, literals, 1, formula, firstFreshVariable) + 1;

    weights = {2};
    literals = {2};
    firstFreshVariable = pb2cnf.encodeGeq(weights, literals, 2, formula, firstFreshVariable) + 1;

    weights = {3};
    literals = {1};
    firstFreshVariable = pb2cnf.encodeGeq(weights, literals, 3  , formula, firstFreshVariable) + 1;


    for (size_t i = 0; i < formula.size(); i++) {
        std::vector< int32_t > *clause = &formula[i];
        for (size_t j = 0; j < clause->size(); j++) {
            std::cout << (*clause)[j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "pene" << '\n';
}
