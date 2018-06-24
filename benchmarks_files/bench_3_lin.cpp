#include <iostream>
#include <string>
#include <chrono>

#include "Solver.h"
#include "LinearSearchStrategy.h"
#include "BinarySearchStrategy.h"

//Adapted benchmark from minlplib2-pb-0.1.0/opb/sporttournament10.opb

int main() {

    std::vector< PBConstraint > constraints = {
        PBConstraint(PBFormula(
            {-1},
            {1}),
            0)
    };
    PBFormula costFunction(
        {2, -2, -4, 2, 2, -2, 2, -2, -2, 2, -4, 2, -2, 2, -4, -2, 2, -4, 2, -2, -4, 2, -2, 2, -2, 2, 2, -2, 2, 2, -4, 2, -2, 2, 2, -2, 2, -2, 2, 2, 2, -2, -2, 2, -2, 2, -2, 2, 2, -2, 2, -2, 2, -2, -2, -2, 2, 2, 2, 2, 2, -2, -2, 2, 2, 2, -2, -2, 2, -2, 2, -2, 2, -2, 2, 2, -2, -2, -2, -2, -2, 2, 2, 2, 2, 2, 2, -2, -2, 2, 2, -2, 2, 2, 2, -2, 2, -2, 2, -2, -2, 2, 2, 2, -2, -2, -2, 2, 2, -2, -2, -2},
        {1, 1, 14, 1, 1, 1, 2, 2, 3, 2, 31, 3, 4, 3, 8, 3, 4, 9, 5, 5, 7, 5, 11, 6, 6, 6, 7, 13, 7, 8, 19, 8, 28, 8, 9, 10, 9, 18, 9, 10, 11, 11, 12, 12, 12, 12, 12, 13, 13, 25, 14, 16, 14, 15, 15, 17, 15, 15, 15, 16, 16, 26, 16, 17, 17, 18, 30, 18, 19, 20, 19, 29, 20, 21, 21, 22, 21, 23, 22, 24, 22, 22, 23, 23, 23, 24, 24, 25, 27, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 32, 30, 31, 31, 33, 33, 34, 36, 37, 37, 39, 41, 43}
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
