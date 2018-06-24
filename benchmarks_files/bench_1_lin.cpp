#include <iostream>
#include <string>
#include <chrono>

#include "Solver.h"
#include "LinearSearchStrategy.h"
#include "BinarySearchStrategy.h"

//Adapted benchmark from minlplib2-pb-0.1.0/opb/autocorr_bern20-03.opb

int main() {

    std::vector< PBConstraint > constraints = {
        PBConstraint(PBFormula({-1},{1}),0)
    };
    PBFormula costFunction({8, -4, -8, 8, -4, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -8, 8, -4, 8, -4},{1, 1, 3, 2, 2, 4, 3, 5, 4, 6, 5, 7, 6, 8, 7, 9, 8, 10, 9, 11, 10, 12, 11, 13, 12, 14, 13, 15, 14, 16, 15, 17, 16, 18, 17, 19, 18, 20});

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
