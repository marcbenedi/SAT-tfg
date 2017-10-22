#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>
#include <assert.h>

class Clause{
private:
    std::vector<int> lits;

public:
    void addVar(int v){
        lits.push_back(v);
    }

};

#endif // CLAUSE_H
