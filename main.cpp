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

    Formula p = BoolFunc::newLit("a");
    Formula q = BoolFunc::newLit("b");
    Formula r = BoolFunc::newLit("c");
    // Formula i = (p*q) + !(!p*(q+!r));
    Formula i = p*q+r;


    Cudd mgr;
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD f = x * y;
    BDD g = y + !f;
    std::cout << "f is" << (f <= g ? "" : " not")
    << " less than or equal to g\n";
    DdNode* node = g.getNode();
    int index = g.CountLeaves();
    std::cout << index << std::endl;
    std::cout << x.IsVar() << std::endl;

    BDDConverter converter = BDDConverter(mgr);
    BDD result = converter.convertFormula(i);
    result.print(30);

}
