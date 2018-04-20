#ifndef BINARY_SEARCH_STRATEGY_H
#define BINARY_SEARCH_STRATEGY_H

#include <vector>
#include <stdint.h>
#include "SearchStrategy.h"

class BinarySearchStrategy: public SearchStrategy {
private:
    std::vector< std::vector< int32_t > > cnf_constraints;
    int32_t firstFreshVariable;
    int64_t left;
    int64_t right;
public:
    BinarySearchStrategy();
    void init(const PBMin & p) override;
    void loop(void (Solver::*solver)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *s, const PBMin & pm)override;
    void end() override;
};

#endif // BINARY_SEARCH_STRATEGY_H
