#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"
#include "VarsManager.h"
#include <map>

class CnfConverter{
private:
    CnfConverter();

    static Cnf tseitinRec(Formula const & boolFunc, std::map<Formula,int> & auxToNode){

        Cnf result;

        const NodeType type = boolFunc->getType();
        if(type == NOD_CONST || type == NOD_ID) return result; //In this case empty

        Formula child1 = boolFunc->getChild1(); // modifiable pointer  const value
        Formula child2 = boolFunc->getChild2();
        Formula child3 = boolFunc->getChild3();

        Cnf cnf1, cnf2, cnf3;

        if(child1 != NULL) cnf1 = tseitinRec(child1, auxToNode);
        if(child2 != NULL) cnf2 =tseitinRec(child2, auxToNode);
        if(child3 != NULL) cnf3 =tseitinRec(child3, auxToNode);

        result.addCnf(cnf1);
        result.addCnf(cnf2);
        result.addCnf(cnf3);

        if(type == NOD_NOT){
            NodeType typeChild = child1->getType();
            if(typeChild == NOD_CONST){
                if (child1->getValue() == TRUE) {

                }
                else if (child1->getValue() == FALSE){

                }
                else{
                    assert(false && "Unhandled value of NOD_CONST");
                }
            }
            else if (typeChild == NOD_ID){
                int varChild = child1->getValue();
                auxToNode[boolFunc] = -varChild;
            }
            else{
                int varChild = auxToNode[child1];
                auxToNode[boolFunc] = -varChild;
            }
        }
        else if (type == NOD_AND){
            //Get the aux vars of the childs
            //MARC: S'ha de mirar que els childs no siguin CONST or ID perquè no estaran en el map
            //MARC: Si un child és false ja sabem que no es complirà
            int varC1 = (child1->getType() == NOD_ID || child1->getType() == NOD_CONST)?
                        child1->getValue():auxToNode[child1];

            int varC2 = (child2->getType() == NOD_ID || child2->getType() == NOD_CONST)?
                        child2->getValue():auxToNode[child2];

            int me = VarsManager::newId();
            //Insert ourself into the map
            auxToNode[boolFunc] = me;

            Clause c1 = Clause(2,-me,varC1); //c1.addVar(-me);c1.addVar(varC1);
            Clause c2 = Clause(2,-me,varC2); //c2.addVar(-me);c2.addVar(varC2);
            Clause c3 = Clause(3,-varC1,-varC2,me); //c3.addVar(-varC1);c3.addVar(-varC2);c3.addVar(me);

            result.addClause(c1);
            result.addClause(c2);
            result.addClause(c3);

        }
        else if (type == NOD_OR){
            //Si un dels childs es true ja sabem que es complirà
            int varC1 = (child1->getType() == NOD_ID || child1->getType() == NOD_CONST)?
                        child1->getValue():auxToNode[child1];

            int varC2 = (child2->getType() == NOD_ID || child2->getType() == NOD_CONST)?
                        child2->getValue():auxToNode[child2];

            int me = VarsManager::newId();
            //Insert ourself into the map
            auxToNode[boolFunc] = me;

            Clause c1 = Clause(2,me,-varC1); //c1.addVar(me);c1.addVar(-varC1);
            Clause c2 = Clause(2,me,-varC2); //c2.addVar(me);c2.addVar(-varC2);
            Clause c3 = Clause(3,varC1,varC2,-me); //c3.addVar(varC1);c3.addVar(varC2);c3.addVar(-me);

            result.addClause(c1);
            result.addClause(c2);
            result.addClause(c3);
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

    static Cnf tseitin(Formula const & boolFunc){
        //This map saves for each aux var what node it references
        std::map<Formula, int> auxToNode;

        Cnf result = tseitinRec(boolFunc,auxToNode);
        //We add a new Clause which is the aux var of the root node
        //Root node must be satisfied
        int varRoot = auxToNode[boolFunc];
        Clause c = Clause(1, varRoot);
        result.addClause(c);
        return result;

    }
};

#endif // CNFCONVERTER_H
