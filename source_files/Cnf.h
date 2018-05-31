#ifndef CNF_H
#define CNF_H

#include <vector>
#include <set>
#include "Clause.h"

class Cnf{
private:
    std::vector<Clause> cnf;
public:
    Clause getClause(int i) const;
    int getClauseNumber() const;
    int getNumVars() const;
    void addClause(Clause const & clause);
    void addCnf(Cnf const & param);

    /**
     * Adds the empty clause (unsat)
     */
    void addUnsat();
    void print() const;
    
    //BUG: Les variables han d'anar entre 1 i num_vars.
    //Sinó el picosat no funciona.

    /**
     * String representing the cnf in picosat format
     */
    std::string picosat() const;
    void clear();
};

#endif // CNF_H
