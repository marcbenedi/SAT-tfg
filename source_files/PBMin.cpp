#include "PBMin.h"

PBMin::PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction, SEARCH_TYPE p_searchType):constraints(p_constraints),costFunction(p_costFunction),searchType(p_searchType)
{

}

std::vector<PBConstraint> PBMin::getConstraints(){
    return constraints;
}

PBFormula PBMin::getCostFunction(){
    return costFunction;
}

SEARCH_TYPE PBMin::getSearchType(){
    return searchType;
}

int32_t PBMin::getFirstFreshVariable(){
    int32_t max = -1;
    for (size_t i = 0; i < constraints.size(); i++) {
        for (size_t k = 0; k < constraints[i].getPBFormula().getLiterals().size(); k++) {
            if (max < abs(constraints[i].getPBFormula().getLiterals()[k])) {
                max = abs(constraints[i].getPBFormula().getLiterals()[k]);
            }
        }
    }
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (max < abs(costFunction.getLiterals()[i])) {
            max = abs(costFunction.getLiterals()[i]);
        }
    }
    return max+1;
}

int64_t PBMin::getCostFunctionMax(){
    std::map<int32_t,int64_t> positive;
    std::map<int32_t,int64_t> negative;
    std::set<int32_t> lits;
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (costFunction.getLiterals()[i] < 0) {
            negative[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        else{
            positive[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        lits.insert(abs(costFunction.getLiterals()[i]));
    }
    int64_t max = 0;

    for (std::set<int32_t>::iterator it = lits.begin(); it != lits.end(); it++) {
        int32_t lit = *it;
        max += positive[lit] > negative[lit] ? positive[lit] : negative[lit];
    }

    return max;
}
int64_t PBMin::getCostFunctionMin(){
    std::map<int32_t,int64_t> positive;
    std::map<int32_t,int64_t> negative;
    std::set<int32_t> lits;
    for (size_t i = 0; i < costFunction.getLiterals().size(); i++) {
        if (costFunction.getLiterals()[i] < 0) {
            negative[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        else{
            positive[abs(costFunction.getLiterals()[i])] += costFunction.getWeights()[i];
        }
        lits.insert(abs(costFunction.getLiterals()[i]));
    }
    int64_t min = 0;

    for (std::set<int32_t>::iterator it = lits.begin(); it != lits.end(); it++) {
        int32_t lit = *it;
        min += positive[lit] < negative[lit] ? positive[lit] : negative[lit];
    }

    return min;
}

bool PBMin::minisat(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf){

    model.clear();

    std::string input = "p cnf "+ std::to_string(getFirstFreshVariable()) + " " + std::to_string(cnf.size()) + " ";
    for (size_t i = 0; i < cnf.size(); i++) {
        for (size_t j = 0; j < cnf[i].size(); j++) {
            input += std::to_string(cnf[i][j]) + " ";
        }
        input += "0 ";
    }
    std::system(("echo " + input + " > input.txt").c_str());
    std::string command = "minisat > /dev/null 2>&1 input.txt output.txt";
    std::system(command.c_str());

    bool sat;
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


    return sat;
}

bool PBMin::solve(std::vector< int32_t > & model, int64_t & min){
    //TODO: falta fer depen searchtype
    int32_t firstFreshVariable = getFirstFreshVariable();
    std::vector< std::vector< int32_t > > cnf_constraints;

    PB2CNF pb2cnf;

    //Encoding constraints
    for (size_t i = 0; i < constraints.size(); i++) {
        firstFreshVariable = pb2cnf.encodeLeq(constraints[i].getPBFormula().getWeights(), constraints[i].getPBFormula().getLiterals(), constraints[i].getK(), cnf_constraints, firstFreshVariable) + 1;
    }

    std::vector< std::vector< int32_t > > cnf;
    int64_t left = getCostFunctionMin();
    int64_t right = getCostFunctionMax();
    min = right + 1;

    bool end = false;
    while (not end) {
        assert(left<=right);
        cnf.clear();
        cnf.insert(cnf.end(),cnf_constraints.begin(),cnf_constraints.end());

        int64_t k = (left+right)/2;
        // std::cout << k << '\n';

        if (left == right) {
            //no more values to try
            end = true;
        }

        firstFreshVariable = pb2cnf.encodeLeq(costFunction.getWeights(), costFunction.getLiterals(), k, cnf, firstFreshVariable) + 1;

        bool sat = minisat(model, cnf);

        if (sat) {
            min = k;
            right = k-1;
        }
        else{
            if (min == k + 1) {
                end = true;
            }
            left = k+1;
        }

    }

    if (model.size() != 0) {
        // std::cout << "SAT" << '\n';
        // std::cout << "min " << std::to_string(min) << '\n';
        // for (size_t i = 0; i < model.size(); i++) {
        //     std::cout << std::to_string(model[i]) << " ";
        // }
        // std::cout << '\n';
        return true;
    }
    else{
        // std::cout << "UNSAT" << '\n';
        return false;
    }

}
