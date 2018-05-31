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

    /**
     * Generates a cnf equisatisfiable with the boolfunc using the tesitin transformation
     * @param boolFunc
     * @return cnf equisatisfiable with the boolFunc
     */
    static Cnf tseitin(Formula const & boolFunc);

    /**
     * Converts the BDD into a CNF
     * @param bdd 
     * @return cnf equisatisfiable with the boolFunc
     */
    static Cnf convertToCnf(const BDD & bdd);
};

#endif // CNFCONVERTER_H
