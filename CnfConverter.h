#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"
#include "VarsManager.h"
#include <map>

class CnfConverter{
private:
    CnfConverter();
    static Cnf tseitinRec(BoolFunc const & boolFunc, std::map<const BoolFunc*,int> & auxToNode){

        Cnf result;

        const NodeType type = boolFunc.getType();
        if(type == NOD_CONST || type == NOD_ID) return result; //In this case empty

        const BoolFunc* child1 = boolFunc.getChild1(); // modifiable pointer  const value
        const BoolFunc* child2 = boolFunc.getChild2();
        const BoolFunc* child3 = boolFunc.getChild3();

        if(child1 != NULL) tseitinRec(*child1, auxToNode);
        if(child2 != NULL) tseitinRec(*child2, auxToNode);
        if(child3 != NULL) tseitinRec(*child3, auxToNode);

        if(type == NOD_NOT){

        }
        else if (type == NOD_AND){
            //Get the aux vars of the childs
            //MARC: S'ha de mirar que els childs no siguin CONST or ID perquè no estaran en el map
            //MARC: Si un child és false ja sabem que no es complirà
            int varC1 = auxToNode[child1];
            int varC2 = auxToNode[child2];

            int me = VarsManager::newId();
            //Insert ourself into the map
            auxToNode[&boolFunc] = me;

            Clause c1 = Clause(2,-me,varC1); //c1.addVar(-me);c1.addVar(varC1);
            Clause c2 = Clause(2,-me,varC2); //c2.addVar(-me);c2.addVar(varC2);
            Clause c3 = Clause(3,-varC1,-varC2,me); //c3.addVar(-varC1);c3.addVar(-varC2);c3.addVar(me);

            result.addClause(c1);
            result.addClause(c2);
            result.addClause(c3);

        }
        else if (type == NOD_OR){
            //Si un dels childs es true ja sabem que es complirà
            int varC1 = auxToNode[child1];
            int varC2 = auxToNode[child2];

            int me = VarsManager::newId();
            //Insert ourself into the map
            auxToNode[&boolFunc] = me;

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
    static Cnf silly(BoolFunc const & boolFunc){
        /**
         * 1 - Apply De Morgan
         * 2 - Apply distributive
         * The size of boolFunc grows!!
         **/
        Cnf cnf;
        return cnf;
    }

    static Cnf tseitin(BoolFunc const & boolFunc){
        /**
         * x = a ^ b
         * x -> a = !x v a
         * x -> b = !x v b
         * a ^ b -> x = !a v !b v x
         *
         * x = a v b
         * a -> x = x v !a
         * b -> x = x v !b
         * x -> a v b = a v b v !x
         **/
        //This map saves for each aux var what node it references
        std::map<const BoolFunc*, int> auxToNode;
        //MARC: Recordar afegir que l'arrel sigui true a la cnf
        return tseitinRec(boolFunc,auxToNode);

    }
};

#endif // CNFCONVERTER_H
