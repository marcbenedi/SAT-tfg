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
    //print("mixMethod");
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    Formula e = BoolFunc::newLit("e");
    Formula ff = BoolFunc::newLit("f");
    Formula g = BoolFunc::newLit("g");
    Formula h = BoolFunc::newLit("h");
    Formula i = BoolFunc::newLit("i");
    Formula j = BoolFunc::newLit("j");
    Formula k = BoolFunc::newLit("k");
    Formula s1 = (a*b)+(c*d);
    Formula s2 = (e*ff)+(g*h);
    Formula s3 = !s1;
    Formula s4 = !s2;
    Formula f1 = (s1*s2)+(s3*s4);
    Formula f2 = (s2*s3)+(s4*s1);
    Formula f3 = (s3*s4)+(s1*s2);
    Formula f4 = (s4*s1)+(s2*s3);
    Formula f = (f1*f2)+(f3*f4);

    MixCNFConverter m = MixCNFConverter();
    m.convert(f);
    Cnf result = m.getResult();
    //result.print();
    //print("Numero vars cnf");
    std::string  s_value = getenv ("D");
    double value = atof(s_value.c_str());
    std::cout << value/10000.0 << "," << result.getNumVars() << ","<<result.getClauseNumber() <<std::endl;
    //print("Numero clauses cnf");
    //std::cout << result.getClauseNumber()<<std::endl;
}

void cnfBDD(){
    print("cnfBDD");
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    Formula f = a*!b+c*!d+a+b+c+!d;
    BDD f3_bdd = BDDConverter::convertFormula(f);
    Cnf f3_cnf = CnfConverter::convertToCnf(f3_bdd);
    f3_cnf.print();
}

void mixVSbdd(){
    Formula a = BoolFunc::newLit("a");
    Formula b = BoolFunc::newLit("b");
    Formula c = BoolFunc::newLit("c");
    Formula d = BoolFunc::newLit("d");
    Formula rbdd = BoolFunc::newLit("rbdd");
    Formula rmix = BoolFunc::newLit("rmix");
    Formula f = a*!b+c*!d;

    Formula f2 = !rbdd*!f + rbdd*f;
    //Formula f3 = !rmix*!bad + rmix*bad;
    Formula f3 = !rmix*!f + rmix*f;
    Formula f4 = !rmix*rbdd + rmix*!rbdd;//XOR

    BDD f2_bdd = BDDConverter::convertFormula(f2);
    Cnf f2_cnf = CnfConverter::convertToCnf(f2_bdd);

    MixCNFConverter m = MixCNFConverter();
    m.convert(f3);
    Cnf f3_cnf = m.getResult();

    Cnf f4_cnf = CnfConverter::tseitin(f4);

    Cnf cnf;
    cnf.addCnf(f2_cnf);
    cnf.addCnf(f3_cnf);
    cnf.addCnf(f4_cnf);
    cnf.print();

    std::cout << SatSolver::solve2(cnf) << std::endl;
}

int main() {

    //tseitinVSbdd();
    mixMethod();
    //cnfBDD();
    //mixVSbdd();



}
