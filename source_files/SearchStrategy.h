#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

#include <vector>
#include <stdint.h>
#include "PBMin.h"

class Solver;//Solve cyclic dependencies

class SearchStrategy {
private:

public:
    virtual void init(const PBMin & p) = 0;
    virtual void loop(void (Solver::*solver)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *s, const PBMin &p) = 0;
    virtual void end() = 0;
};

#endif // SEARCH_STRATEGY_H
