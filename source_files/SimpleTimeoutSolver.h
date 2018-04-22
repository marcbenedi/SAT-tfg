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
    SimpleTimeoutSolver(int seconds, SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);

    virtual void solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat) override;
};

#endif // SIMPLE_TIMEOUT_SOLVER_H
