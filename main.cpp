#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"

void print(std::string s){
        std::cout << s << std::endl;
}

int main() {

    Formula p = BoolFunc::newLit("a");
    Formula q = BoolFunc::newLit("b");
    Formula r = BoolFunc::newLit("c");

    Formula i = (p*q) + !(!p*(q+!r));
    //i->print();
    Cnf result = CnfConverter::tseitin(i);
    result.printPicosatFormat();

    Cudd mgr(0,0);
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD f = x * y;
    BDD g = y + !x;
    std::cout << "f is" << (f <= g ? "" : " not")
    << " less than or equal to g\n";

}
