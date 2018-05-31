#ifndef SOLVER_H
#define SOLVER_H

#include "SearchStrategy.h"
#include "PBMin.h"

class Solver {
protected:
    //Pointer to use inheritance (work with child classes)
    SearchStrategy *searchStrategy;
    PBMin pbmin;
    bool timeoutOccurred = false;
public:
    /**
     * Constructs a Solver
     *@param p_searchStrategy : the search strategy used for finding the minimum value for the cost function
     *@param p_pbmin : the pseudo-boolean minimization problem
     */
    Solver(SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);

    /**
     * Function called by the user to start the problem solving
     *@param model : where the model will be stored
     *@param min : where the minimum value for the cost function will be stored
     *@return true if satisfiable, otherwise false
     */
    virtual bool run(std::vector< int32_t > & model, int64_t & min);

    /**
     *Function called by the SearchStrategy which calls a sat solver (minisat)
     *@param model : where the model will be stored
     *@param cnf : the cnf for the sat solver
     *@param sat : where the satisfiability of the cnf will be stored
     */
    virtual void solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat);

    /**
     * If the timeout has occurred, the solution may not be optimal.
     *@return true if the timeout has occurred, false otherwise. 
     */
    virtual bool hasTimeoutOccurred();
};

#endif // SOLVER_H
