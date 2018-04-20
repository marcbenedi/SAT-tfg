#ifndef SEARCH_STRATEGY_STUB
#define SEARCH_STRATEGY_STUB

#include "SearchStrategy.h"

class SearchStrategy_Stub : public SearchStrategy {
private:
public:
    void init(const PBMin & p) override{

    }
    void loop(void (Solver::*solver)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *s, const PBMin &p) override {
        model.clear();
        model.push_back(1);
        model.push_back(2);
        model.push_back(3);
        min = 123;
        sat = true;
    }
    void end() override {

    }
};

#endif // SEARCH_STRATEGY_STUB
