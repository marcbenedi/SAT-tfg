#ifndef BDDCONVERTER_H
#define BDDCONVERTER_H

#include "BoolFunc.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"

class BDDConverter{
private:
    BDDConverter();
    Cudd mgr;

    BDD convertFormulaRec(Formula const & boolFunc){
        BDD result;
        NodeType type = boolFunc->getType();

        //Base case
        //Todo: si es const returnar la funcio directament
        if(type == NOD_CONST || type == NOD_ID) return mgr.bddVar(); //In this case a new var

        //Recursive case
        Formula child1 = boolFunc->getChild1();
        Formula child2 = boolFunc->getChild2();
        Formula child3 = boolFunc->getChild3();

        BDD bdd1, bdd2, bdd3;

        if(child1 != NULL)bdd1 = convertFormulaRec(child1);
        if(child2 != NULL)bdd2 = convertFormulaRec(child2);
        if(child3 != NULL)bdd3 = convertFormulaRec(child3);

        if(type == NOD_NOT){
            result = ~bdd1;
        }
        else if(type == NOD_AND){
            result = bdd1 * bdd2;
        }
        else if(type == NOD_OR){
            result = bdd1 + bdd2;
        }
        else if (type == NOD_XOR){
            assert(false && "still not implemented");
        }
        else if (type == NOD_COND){
            assert(false && "still not implemented");
        }
        else{assert(false);}

        return result;

    }

public:
    BDDConverter(Cudd mgr):mgr(mgr){}

    BDD convertFormula(Formula const & boolFunc){
        BDD result = convertFormulaRec(boolFunc);
        return result;
    }
};

#endif // BDDCONVERTER_H
