#ifndef CNF_H
#define CNF_H

#include <vector>
#include "Clause.h"
#include "VarsManager.h"

class Cnf{
private:
    std::vector<Clause> cnf;
public:
    Clause getClause(int i) const;
    int getClauseNumber() const;
    int getNumVars() const;
    void addClause(Clause const & clause);
    void addCnf(Cnf const & param);
    //NOTE: Assegurar-se de que funciona bé
    void addUnsat();
    void print() const;
    //BUG: Les variables han d'anar entre 1 i num_vars.
    //Sinó el picosat no funciona.
    std::string picosat() const;
    void clear();
};

#endif // CNF_H
