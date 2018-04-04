#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"
#include "BDDConverter.h"
#include "SatSolver.h"
#include "MixCNFConverter.h"

int main() {

    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");

    Formula f = a;
    Formula f2 = (a+b);
    Formula f3 = (a*b);
    Formula f4 = (a+b) * (c+d);
    Formula f5 = a*b*c;
    Formula f6 = a+b+c;
    Formula f7 = (a*b) + (c*d);
    Formula f8 = !f7;
    Formula f9 = ((!a)*b*(!c)*d) + (a*c);
    Formula f10 = !a*!b*d + a*b;
    Formula f11 = b*d + !b*!d;

    BDD bdd = BDDConverter::convertFormula(f8);

    BDD aa = VarsManager::getInstance()->bddVar();
    BDD bb = VarsManager::getInstance()->bddVar();
    BDD cc = VarsManager::getInstance()->bddVar();
    BDD dd = VarsManager::getInstance()->bddVar();

    BDD bdd2 = ((~aa)*bb*(~cc)*dd) + (aa*cc);

    MixCNFConverter mixCNFConverter;
    mixCNFConverter.worthToConvert(bdd);

}
