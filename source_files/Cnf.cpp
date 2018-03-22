#include "Cnf.h"

Clause Cnf::getClause(int i) const{
    return cnf[i];
}

int Cnf::getClauseNumber() const {return cnf.size();}

int Cnf::getNumVars() const {
    std::set<int> myset;

    for (int i = 0; i < getClauseNumber(); ++i ) {
        Clause c = cnf[i];
        for (int j = 0; j < c.getNumVars(); ++j) {
            int var = c.getVar(j);
            if(var < 0) var = -var;
            myset.insert(var);
        }
    }

    return myset.size();
}

void Cnf::addClause(Clause const & clause){
    cnf.push_back(clause);
}
void Cnf::addCnf(Cnf const & param){
    for (int i = 0; i < param.getClauseNumber(); ++i ) {
        addClause(param.getClause(i));
    }
}

void Cnf::addUnsat(){
    //Afegim empty clause
    Clause c;
    c.clear();
    cnf.push_back(c);
}
void Cnf::print() const{
    for(uint i = 0; i < cnf.size(); ++i){
        cnf[i].print();
    }
}

std::string Cnf::picosat() const{
    std::string returnValue = "";
    int num_vars= getNumVars(), num_clauses = getClauseNumber();
    returnValue +="p cnf "+std::to_string(num_vars)+" "+std::to_string(num_clauses);
    for(uint i = 0; i < cnf.size(); ++i){
        returnValue+=cnf[i].picosat();
    }
    return returnValue;
}

void Cnf::clear(){
    cnf.clear();
}
