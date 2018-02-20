#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"
#include "BDDConverter.h"
#include "SatSolver.h"
#include "MixCNFConverter.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

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

Formula a = BoolFunc::newLit("a");
Formula b = BoolFunc::newLit("b");
Formula c = BoolFunc::newLit("c");
Formula d = BoolFunc::newLit("d");
Formula e = BoolFunc::newLit("e");
Formula f = BoolFunc::newLit("f");
Formula g = BoolFunc::newLit("g");
Formula h = BoolFunc::newLit("h");
Formula i = BoolFunc::newLit("i");
Formula j = BoolFunc::newLit("j");
Formula k = BoolFunc::newLit("k");
Formula l = BoolFunc::newLit("l");
Formula m = BoolFunc::newLit("m");
Formula n = BoolFunc::newLit("n");
Formula o = BoolFunc::newLit("o");
Formula p = BoolFunc::newLit("p");
Formula q = BoolFunc::newLit("q");
Formula r = BoolFunc::newLit("r");
Formula s = BoolFunc::newLit("s");
Formula t = BoolFunc::newLit("t");
Formula u = BoolFunc::newLit("u");
Formula v = BoolFunc::newLit("v");
Formula w = BoolFunc::newLit("w");
Formula x = BoolFunc::newLit("x");
Formula y = BoolFunc::newLit("y");
Formula z = BoolFunc::newLit("z");

Formula vars[26] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

Formula generateRandom (int & level){

    //std::this_thread::sleep_for (std::chrono::seconds(2));
    int op = rand() % 5;

    Formula result;

    if(op == 0){//AND
        int level1, level2;
        Formula a = generateRandom(level1);
        Formula b = generateRandom(level2);
        result = a * b;
        level = level1 > level2? (level1+1) : (level2+1);
    }else if (op == 1) {//OR
        int level1, level2;
        Formula a = generateRandom(level1);
        Formula b = generateRandom(level2);
        result = a * b;
        level = level1 > level2? (level1+1) : (level2+1);
    }else if (op == 2) {//NOT
        Formula child = generateRandom(level);
        result = !child;
        level += 1;
    }else {//VAR
        int var = rand()%26;
        result = vars[var];
        level = 1;
    }

    return result;

}

void mixMethod(){
    /* initialize random seed: */
      srand (time(NULL));

    int level = 0;
    Formula formula = generateRandom(level);

    MixCNFConverter m = MixCNFConverter();
    m.convert(formula);
    Cnf result = m.getResult();

    std::string  s_value = getenv ("D");
    double value = atof(s_value.c_str());
    std::cout << value/1000.0 << "," << result.getNumVars() << ","<<result.getClauseNumber() <<std::endl;
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
