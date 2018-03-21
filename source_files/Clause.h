#ifndef CLAUSE_H
#define CLAUSE_H

#include <vector>
#include <assert.h>
#include <cstdarg>
#include <iostream>

class Clause{
private:
    std::vector<int> lits;
public:
    Clause();
    //n is the number of elements in the list
    Clause(int n, ...);
    void addVar(int v);
    void print() const;
    std::string picosat() const;
    void clear();
    int getNumVars() const;
    int getVar(int i) const;
};
#endif // CLAUSE_H
