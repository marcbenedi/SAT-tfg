#include <iostream>
#include <string>
#include "cudd.h"
#include "cuddObj.hh"

int main(){
    Cudd mgr(0,0);
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD f = x * y;
    BDD g = y + !x;
    std::cout << "f is" << (f <= g ? "" : " not") << " less than or equal to g\n";
}
