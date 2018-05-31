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

    /**
     * Initializes the class with n literals
     * @param n
     * @param ... an array of literals
     */
    Clause(int n, ...);

    void addVar(int v);
    void print() const;
    /**
     * Represents the Clause in picosat format
     */
    std::string picosat() const;
    
    void clear();
    int getNumVars() const;
    int getVar(int i) const;
};
#endif // CLAUSE_H
