#include <iostream>
#include <string>
#include <chrono>

#include "Solver.h"
#include "LinearSearchStrategy.h"
#include "BinarySearchStrategy.h"

//Adapted benchmark from minlplib2-pb-0.1.0/opb/hmittelman.opb

int main() {

    std::vector< PBConstraint > constraints = {
        PBConstraint(PBFormula(
            {3, -12, -8, 1, -7, 2},
            {5, 1, 3, 3, 1, 13}),
            -2),
        PBConstraint(PBFormula(
            {1, -10, -5, 1, 7, 1},
            {1, 3, 6, 6, 9, 5}),
            -1),
        PBConstraint(PBFormula(
            {5, -3, -1, -2, 1},
            {5, 1, 3, 5, 13}),
            -1),
        PBConstraint(PBFormula(
            {3, -5, 1, 2, -1},
            {1, 5, 3, 5, 13}),
            1),
        PBConstraint(PBFormula(
            {-4, -2, -5, 1, -9, -2},
            {3, 3, 6, 9, 5, 1}),
            -3),
        PBConstraint(PBFormula(
            {9, -12, -7, 6, 2, -15, 3},
            {1, 3, 6, 6, 5, 1, 13}),
            -7),
        PBConstraint(PBFormula(
            {5, -8, 2, -7, -1, -5, -10},
            {1, 5, 3, 3, 6, 9, 1}),
            -1)
    };
    PBFormula costFunction(
        {10, 7, 1, 12, 8, 3, 1, 5, 3},
        {5, 1, 3, 3, 6, 6, 9, 5, 1}
    );

    LinearSearchStrategy bs;
    PBMin m = PBMin(constraints, costFunction);
    Solver s(&bs,m);

    std::vector< int32_t > model;
    int64_t min;
    auto start = std::chrono::high_resolution_clock::now();
    bool sat = s.run(model,min);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "time: "<<elapsed.count()<< "\n";
    std::cout << "sat: " << sat << "\n";
    for(int i = 0; i < model.size(); ++i){
        //std::cout << model[i] << " ";
    }
    std::cout << "" << "min: " << min << "\n\n";

}
