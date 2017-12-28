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
//////////////////////////////CONSTRUCTORS//////////////////////////////////////
    Clause(){};

    //n is the number of elements in the list
    Clause(int n, ...){
        va_list vl;
        va_start(vl,n);
        for (int i=0;i<n;i++){
            lits.push_back(va_arg(vl,int));
        }
        va_end(vl);
    }
//////////////////////////////OTHER FUNCTIONS///////////////////////////////////
    void addVar(int v){
        lits.push_back(v);
    }

    void print() const{
        for(uint i = 0; i < lits.size(); ++i){
            std::cout << lits[i] << " ";
        }
        std::cout << std::endl;
    }

    std::string picosat() const {
        std::string returnValue = " ";
        for(uint i = 0; i < lits.size(); ++i){
            returnValue += std::to_string(lits[i]) + " ";
        }
        returnValue += '0';

        return returnValue;
    }

    void clear() {lits.clear();}
    int getNumVars() const{return lits.size();}
    int getVar(int i) const{return lits[i];}

};

#endif // CLAUSE_H
