#ifndef SIMPLE_TIMEOUT_SOLVER_H
#define SIMPLE_TIMEOUT_SOLVER_H

#include "SearchStrategy.h"
#include "PBMin.h"
#include "Solver.h"
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h> //sleep

class SimpleTimeoutSolver: public Solver {

private:
    static void *minisat(void * p);
    struct thread_data {
       std::vector< int32_t >  model;
       std::vector< std::vector< int32_t > >  cnf;
       bool sat;
       bool finished = false;
       PBMin *pbm;
    };
    static void timeout(int signum);
    int seconds;

public:
    /**
     * Constructs a Solver with a timeout for each call at the sat solver
     *@param seconds : timeout. The minimum value is 1
     *@param p_searchStrategy : the search strategy used for finding the minimum value for the cost function
     *@param p_pbmin : the pseudo-boolean minimization problem
     */
    SimpleTimeoutSolver(int seconds, SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);

    /**
     * Function called by the SearchStrategy to solve the cnf
     *@param model : where the model will be stored
     *@param cnf : the cnf of the problem
     *@param sat : where the satisfiability of the problem will be stored
     */
    virtual void solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat) override;
};

#endif // SIMPLE_TIMEOUT_SOLVER_H
