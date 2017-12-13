#ifndef CNF_H
#define CNF_H

#include <vector>
#include "Clause.h"
#include "VarsManager.h"

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
        }
    }
    Clause getClause(int i) const{
        return cnf[i];
    }
    int getClauseNumber() const {return cnf.size();}
    int getNumVars() const {
        int last_id = VarsManager::getLastId();
        std::vector<bool> counters = std::vector<bool>(last_id+1,false);
        //MARC: Trobar alguna forma de fer millor aquest mètode
        for (int i = 0; i < getClauseNumber(); ++i ) {
            Clause c = cnf[i];
            for (int j = 0; j < c.getNumVars(); ++j) {
                int var = c.getVar(j);
                if(var < 0) var = -var;
                counters[var]=true;
            }
        }

        int suma = 0;
        for (int i = 0; i < last_id+1; ++i ) {
            if(counters[i])suma += 1;
        }
        return suma;

    }

    void printPicosatFormat(){
        int num_vars= getNumVars(), num_clauses = getClauseNumber();
        std::cout << "p cnf "<<num_vars<< " " << num_clauses << std::endl;
        for(uint i = 0; i < cnf.size(); ++i){
            cnf[i].printPicosat();
        }
    }

    void addUnsat(){
        //Afegim empty clause
        Clause c;
        c.clear();
        cnf.push_back(c);
    }
};

#endif // CNF_H
