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
    void addCnf(Cnf const & param){
        for (int i = 0; i < param.getClauseNumber(); ++i ) {
            addClause(param.getClause(i));
        }
    }
    void print(){
        for(uint i = 0; i < cnf.size(); ++i){
            cnf[i].print();
            std::cout<<std::endl;
        }
    }
    Clause getClause(int i) const{
        return cnf[i];
    }
    int getClauseNumber() const {return cnf.size();}
};

#endif // CNF_H
