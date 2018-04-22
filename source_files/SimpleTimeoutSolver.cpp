#include "SimpleTimeoutSolver.h"

SimpleTimeoutSolver::SimpleTimeoutSolver(int p_seconds, SearchStrategy *p_searchStrategy, const PBMin & p_pbmin):seconds(p_seconds),Solver(p_searchStrategy,p_pbmin){
    if (seconds <= 0) {
        //NOTE: At least one second or the thread will not have enough time to register signal
        seconds = 1;
    }
}

void SimpleTimeoutSolver::solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat){
    pthread_t thread;
    thread_data td;
    td.model = model;
    td.cnf = cnf;
    td.sat = sat;
    td.pbm = &pbmin;
    int c = pthread_create(&thread, NULL, SimpleTimeoutSolver::minisat, &td);
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

}

void *SimpleTimeoutSolver::minisat(void *p){
    signal(SIGTERM,timeout);

    thread_data *d;
    d = (thread_data *) p;

    // sleep(5);
    d->model.clear();


    std::string input = "p cnf "+ std::to_string(d->pbm->getFirstFreshVariable()) + " " + std::to_string(d->cnf.size()) + " ";
    for (size_t i = 0; i < d->cnf.size(); i++) {
        for (size_t j = 0; j < d->cnf[i].size(); j++) {
            input += std::to_string(d->cnf[i][j]) + " ";
        }
        input += "0 ";
    }
    std::system(("echo " + input + " > input.txt").c_str());
    std::string command = "minisat > /dev/null 2>&1 input.txt output.txt";
    std::system(command.c_str());

    std::string content;
    std::ifstream infile;
    infile.open("output.txt");

    if (!infile.eof()) {
        getline(infile,content);
        if (content == "SAT") {
            d->sat = true;
        }else if (content == "UNSAT") {
            d->sat = false;
        }
    }
    if (d->sat) {
        int number;
        while (infile >> number) {
            d->model.push_back(number);
        }
    }
    d->finished = true;
    pthread_exit(NULL);
}

void SimpleTimeoutSolver::timeout(int signum)
{
    pthread_exit(NULL);
}
