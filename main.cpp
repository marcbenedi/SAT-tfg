#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"
#include "BDDConverter.h"
#include "SatSolver.h"
#include "MixCNFConverter.h"

void print(std::string s){
        std::cout << s << std::endl;
}

void tseitinVSbdd(){
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    Formula rt = BoolFunc::newLit("rt");
    Formula rc = BoolFunc::newLit("rc");
    Formula f = a*!b+c*!d;
    //Formula f = a+b*!c+d*a*b;

    Formula f2 = !rt*!f + rt*f;
    Formula f3 = !rc*!f + rc*f;
    Formula f4 = !rc*rt + rc*!rt;

    BDD f3_bdd = BDDConverter::convertFormula(f3);

    Cnf f2_cnf = CnfConverter::tseitin(f2);
    Cnf f3_cnf = CnfConverter::convertToCnf(f3_bdd);
    Cnf f4_cnf = CnfConverter::tseitin(f4);

    Cnf cnf;
    cnf.addCnf(f2_cnf);
    cnf.addCnf(f3_cnf);
    cnf.addCnf(f4_cnf);
    std::cout << SatSolver::solve2(cnf) << std::endl;
}

void mixMethod(){
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");

    Formula f = a + b * c * d * (!a);
    MixCNFConverter m = MixCNFConverter();
    m.convert(f);
    Cnf result = m.getResult();
    result.print();
}

void cnfBDD(){
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    Formula f = a*!b+c*!d+a+b+c+!d;
    BDD f3_bdd = BDDConverter::convertFormula(f);
    Cnf f3_cnf = CnfConverter::convertToCnf(f3_bdd);
    f3_cnf.print();
}

int main() {

    //tseitinVSbdd();
    mixMethod();
    //cnfBDD();

}
