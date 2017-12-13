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
    print("printing bdd cnf");
    Cnf bdd = CnfConverter::convertToCnf(result,mgr);
    bdd.printPicosatFormat();
    print("printing tseytin cnf");
    Cnf tseytin = CnfConverter::tseitin(f);
    tseytin.print();

    Cnf unsat;
    unsat.addCnf(bdd);
    unsat.addCnf(tseytin);

    Clause abf = Clause(3,-2,3,6);
    Clause cdf = Clause(3,-4,5,6);

    Cnf rootBdd;
    rootBdd.addClause(abf);
    rootBdd.addClause(cdf);
    //rootBdd.add(rootf);

    Clause rootf = Clause(1,6);
    Clause roott = Clause();
    Cnf roots;


}
