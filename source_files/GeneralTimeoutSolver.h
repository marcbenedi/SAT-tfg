#ifndef GENERAL_TIMEOUT_SOLVER_H
#define GENERAL_TIMEOUT_SOLVER_H

#include "SearchStrategy.h"
#include "PBMin.h"
#include "Solver.h"
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h> //sleep

class GeneralTimeoutSolver: public Solver {

private:
    static void *callLoop(void *p);
    int seconds;
    struct thread_data {
       std::vector< int32_t >  model;
       int64_t min;
       bool sat;
       bool finished = false;
       PBMin *pbm;
       SearchStrategy *strategy;
       Solver *me;
    };
    static void timeout(int signum);
public:
    GeneralTimeoutSolver(int seconds, SearchStrategy *p_searchStrategy, const PBMin & p_pbmin);
    virtual bool run(std::vector< int32_t > & model, int64_t & min) override;

};

#endif // GENERAL_TIMEOUT_SOLVER_H
