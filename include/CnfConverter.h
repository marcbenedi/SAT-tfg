#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"
#include "VarsManager.h"
#include <map>

class CnfConverter{
private:
    CnfConverter();

    static int getNodeVar(Formula const & boolFunc, std::map<Formula,int> & auxToNode);
//////////////////////////////TSEITIN///////////////////////////////////////////
    static void tseitinNOT(Formula const & boolFunc,
        std::map<Formula,int> & auxToNode, Formula const & child1);

    static Cnf tseitinChilds(Formula const & child1,
        Formula const & child2,
        std::map<Formula,int> & auxToNode);

    static Cnf tseitinRec(Formula const & boolFunc, std::map<Formula,int> & auxToNode);
public:

    static Cnf tseitin(Formula const & boolFunc);

    static Cnf convertToCnf(const BDD & f);
};

#endif // CNFCONVERTER_H
