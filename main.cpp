#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"
#include "BDDConverter.h"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    Formula j =  BoolFunc::newLit("x");
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    // Formula i = (p*q) + !(!p*(q+!r));
    Formula f = a*!b+c*!d;
    f->print();

    Cudd mgr;

    BDDConverter converter = BDDConverter(mgr);
    BDD result = converter.convertFormula(f);
    //result.print(30);
    Cnf cnf = CnfConverter::convertToCnf(result,mgr);
    cnf.print();

}
