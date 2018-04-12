#include <iostream>
#include <string>
#include <vector>
#include "pb2cnf.h"

using namespace std;

int main() {

    PB2CNF pb2cnf;

    vector< vector< int32_t > > formula;
    int32_t firstFreshVariable = 4;

    vector< int64_t > weights = {1,2};
    vector< int32_t > literals = {1,2};

    vector< int64_t > weights2 = {3,4};
    vector< int32_t > literals2 = {2,3};

    vector< int64_t > weights3 = {3,7};
    vector< int32_t > literals3 = {1,3};

    firstFreshVariable = pb2cnf.encodeLeq(weights, literals, 1, formula, firstFreshVariable) + 1;
    firstFreshVariable = pb2cnf.encodeLeq(weights2, literals2, 1, formula, firstFreshVariable) + 1;
    firstFreshVariable = pb2cnf.encodeLeq(weights3, literals3, 1, formula, firstFreshVariable) + 1;

    for (size_t i = 0; i < formula.size(); i++) {
        std::vector< int32_t > *clause = &formula[i];
        for (size_t j = 0; j < clause->size(); j++) {
            std::cout << (*clause)[j] << " ";
        }
        std::cout << '\n';
    }
}
