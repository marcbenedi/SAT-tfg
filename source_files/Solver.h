#ifndef SOLVER_H
#define SOLVER_H

#include "SearchStrategy.h"
#include "PBMin.h"

class Solver {
protected:
    //Pointer to use inheritance
    SearchStrategy *searchStrategy;
    PBMin pbmin;
    bool timeoutOccurred = false;
public:
    Solver(SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);

    virtual bool run(std::vector< int32_t > & model, int64_t & min);

    virtual void solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat);

    virtual bool hasTimeoutOccurred();
};

#endif // SOLVER_H
