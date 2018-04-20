#include "SimpleTimeoutSolver.h"

SimpleTimeoutSolver::SimpleTimeoutSolver(SearchStrategy *p_searchStrategy, const PBMin & p_pbmin):Solver(p_searchStrategy,p_pbmin){}

void SimpleTimeoutSolver::solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat){
    pthread_t thread;
    thread_data td;
    td.model = model;
    td.cnf = cnf;
    td.sat = sat;
    td.pbm = &pbmin;
    int c = pthread_create(&thread, NULL, SimpleTimeoutSolver::minisat, &td);
    time_t seconds;
    seconds = time (NULL);
    int timeout = 20+seconds;
    while (!td.finished) {
        // std::cout << "soc el pare i estic esperant" << '\n';
        seconds = time (NULL);
        if(timeout == seconds ){
            int k = pthread_kill(thread, SIGTERM);
            std::cout << "k " << k << '\n';
            td.finished = true;
        }
        // sleep(1);
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
