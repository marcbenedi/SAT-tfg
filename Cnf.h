#ifndef CNF_H
#define CNF_H

#include <vector>
#include "Clause.h"

class Cnf{
private:
std::vector<Clause> cnf;

public:
    void addClause(Clause const & clause){
        cnf.push_back(clause);
    }
    void print(){
        for(uint i = 0; i < cnf.size(); ++i){
            cnf[i].print();
            std::cout<<std::endl;
        }
    }
};

#endif // CNF_H
