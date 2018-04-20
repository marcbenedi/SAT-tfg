#ifndef SOLVER_H
#define SOLVER_H

#include "SearchStrategy.h"
#include "PBMin.h"

class Solver {
protected:
    //Pointer to use inheritance
    SearchStrategy *searchStrategy;
    PBMin pbmin;
public:
    Solver(SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);

    virtual bool run(std::vector< int32_t > & model, int64_t & min);

    virtual void solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat);
};

#endif // SOLVER_H
