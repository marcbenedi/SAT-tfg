#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

#include <vector>
#include <stdint.h>
#include "PBMin.h"

class Solver;//Solve cyclic dependencies

class SearchStrategy {
private:

public:
    /**
     *This function should be the first one called
     *@param problem : The problem to be solved
     */
    virtual void init(const PBMin & problem) = 0;

    /**
     *This function should be called after init()
     *@param solve : Function from the Solver class which solves a cnf
     *@param model : Place where the model will be stored
     *@param min : Place where the minimum value for the cost function will be stored
     *@param sat : Boolean where the satisfiability of the problem will be stored
     *@param solver 
     *@param problem
     */
    virtual void loop(void (Solver::*solve)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *solver, const PBMin &problem) = 0;

    /**
     * This function should be called after loop()
     */
    virtual void end() = 0;
};

#endif // SEARCH_STRATEGY_H
