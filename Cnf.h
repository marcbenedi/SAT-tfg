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
};

#endif // CNF_H
