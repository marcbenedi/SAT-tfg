#include "BDDConverter.h"

BDDConverter::BDDConverter(){};


BDD BDDConverter::convertFormulaRec(Formula const & boolFunc){
    BDD result;
    NodeType type = boolFunc->getType();

    //Base case
    if(type == NOD_ID) {

        BDD aux;

        int my_idx = boolFunc->getValue();
        int cudd_idx = VarsManager::getInstance()->getCuddFromId(my_idx);
        if (cudd_idx != -1) {
            // previously created
            aux = VarsManager::getInstance()->bddVar(cudd_idx);
        }
        else {
            //create variable
            aux = VarsManager::getInstance()->bddVar();
            int idx = aux.NodeReadIndex();
            VarsManager::getInstance()->storeCuddWithId(idx,my_idx);
        }
        return aux;
    }

    //Recursive case
    Formula child1 = boolFunc->getChild1();
    Formula child2 = boolFunc->getChild2();

    BDD bdd1, bdd2;

    if(child1 != NULL){
        bdd1 = convertFormulaRec(child1);
    }
    if(child2 != NULL){
        bdd2 = convertFormulaRec(child2);
    }

    if(type == NOD_NOT){
        result = ~bdd1;
    }
    else if(type == NOD_AND){
        result = bdd1 * bdd2;
    }
    else if(type == NOD_OR){
        result = bdd1 + bdd2;
    }
    //TODO: implementar aquests casos
    else if (type == NOD_XOR){
        assert(false && "still not implemented");
    }
    else{assert(false);}
    return result;

}

BDD BDDConverter::convertFormula(Formula const & boolFunc){
    BDD result = convertFormulaRec(boolFunc);
    return result;
}
