#include "Solver.h"

Solver::Solver(SearchStrategy *p_searchStrategy, const PBMin & p_pbmin):searchStrategy(p_searchStrategy),pbmin(p_pbmin){}

bool Solver::run(std::vector< int32_t > & model, int64_t & min){
    bool sat = false;
    searchStrategy->init(pbmin);
    searchStrategy->loop(&Solver::solver, model, min, sat, this, pbmin);
    searchStrategy->end();
    return sat;
}

void Solver::solver(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf, bool & sat){
    model.clear();

    std::string input = "p cnf "+ std::to_string(pbmin.getFirstFreshVariable()) + " " + std::to_string(cnf.size()) + " ";
    for (size_t i = 0; i < cnf.size(); i++) {
        for (size_t j = 0; j < cnf[i].size(); j++) {
            input += std::to_string(cnf[i][j]) + " ";
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
            sat = true;
        }else if (content == "UNSAT") {
            sat = false;
        }
    }
    if (sat) {
        int number;
        while (infile >> number) {
            model.push_back(number);
        }
    }

}

bool Solver::hasTimeoutOccurred(){
    return timeoutOccurred;
}
