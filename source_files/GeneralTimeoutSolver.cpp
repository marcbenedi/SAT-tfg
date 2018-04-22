#include "GeneralTimeoutSolver.h"

GeneralTimeoutSolver::GeneralTimeoutSolver(int p_seconds, SearchStrategy *p_searchStrategy, const PBMin & p_pbmin):seconds(p_seconds),Solver(p_searchStrategy,p_pbmin){
    if (seconds <= 0) {
        //NOTE: At least one second or the thread will not have enough time to register signal
        seconds = 1;
    }
}

bool GeneralTimeoutSolver::run(std::vector< int32_t > & model, int64_t & min){
    bool sat = false;
    searchStrategy->init(pbmin);

    //search strategy loop called in another thread
    pthread_t thread;
    thread_data td;
    td.model = model;
    td.pbm = &pbmin;
    td.strategy = searchStrategy;
    td.me = this;
    int c = pthread_create(&thread, NULL, GeneralTimeoutSolver::callLoop, &td);

    time_t start;
    start = time (NULL);
    int timeout = start+seconds;
    while (!td.finished) {
        start = time (NULL);
        if(timeout <= start ){
            int k = pthread_kill(thread, SIGTERM);
            td.finished = true;
            td.sat = false; //if time is over then unsat
            timeoutOccurred = true;
        }
    }
    model = td.model;
    sat = td.sat;
    min = td.min;

    searchStrategy->end();
    return sat;
}

void *GeneralTimeoutSolver::callLoop(void *p){
    signal(SIGTERM,timeout);

    thread_data *d;
    d = (thread_data *) p;

    d->strategy->loop(&Solver::solver, d->model, d->min, d->sat, d->me, *(d->pbm));

    d->finished = true;
    pthread_exit(NULL);
}

void GeneralTimeoutSolver::timeout(int signum)
{
    pthread_exit(NULL);
}
