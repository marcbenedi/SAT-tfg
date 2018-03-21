#include "Clause.h"

Clause::Clause(){};
Clause::Clause(int n, ...){
    va_list vl;
    va_start(vl,n);
    for (int i=0;i<n;i++){
        lits.push_back(va_arg(vl,int));
    }
    va_end(vl);
}

void Clause::addVar(int v){
    lits.push_back(v);
}

void Clause::print() const{
    for(uint i = 0; i < lits.size(); ++i){
        std::cout << lits[i] << " ";
    }
    std::cout << std::endl;
}

std::string Clause::picosat() const {
    std::string returnValue = " ";
    for(uint i = 0; i < lits.size(); ++i){
        returnValue += std::to_string(lits[i]) + " ";
    }
    returnValue += '0';

    return returnValue;
}

void Clause::clear() {lits.clear();}
int Clause::getNumVars() const{return lits.size();}
int Clause::getVar(int i) const{return lits[i];}
