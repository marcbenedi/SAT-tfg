#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"
#include "VarsManager.h"
#include <map>

class CnfConverter{
private:
    CnfConverter();

    static int getNodeVar(Formula const & boolFunc, std::map<Formula,int> & auxToNode){
        return (boolFunc->getType() == NOD_ID || boolFunc->getType() == NOD_CONST)?
                    boolFunc->getValue():auxToNode[boolFunc];
    }
//////////////////////////////TSEITIN///////////////////////////////////////////
    static void tseitinNOT(Formula const & boolFunc,
        std::map<Formula,int> & auxToNode, Formula const & child1){

        NodeType typeChild = child1->getType();
        int varChild = getNodeVar(child1, auxToNode);

        if(typeChild == NOD_CONST){
            if (varChild == TRUE) {auxToNode[boolFunc] = FALSE;}
            else if (varChild == FALSE){auxToNode[boolFunc] = TRUE;}
            else{assert(false && "Unhandled value of NOD_CONST");}
        }
        else{auxToNode[boolFunc] = -varChild;}
    }

    static Cnf tseitinChilds(Formula const & child1,
        Formula const & child2,
        Formula const & child3,
        std::map<Formula,int> & auxToNode){

        Cnf result, cnf1, cnf2, cnf3;

        if(child1 != NULL) cnf1 = tseitinRec(child1, auxToNode);
        if(child2 != NULL) cnf2 =tseitinRec(child2, auxToNode);
        if(child3 != NULL) cnf3 =tseitinRec(child3, auxToNode);

        result.addCnf(cnf1);
        result.addCnf(cnf2);
        result.addCnf(cnf3);

        return result;
    }

    static Cnf tseitinRec(Formula const & boolFunc, std::map<Formula,int> & auxToNode){

        Cnf result;
        const NodeType type = boolFunc->getType();

        //Base case
        if(type == NOD_CONST || type == NOD_ID) return result; //In this case empty

        //Recursive case
        Formula child1 = boolFunc->getChild1();
        Formula child2 = boolFunc->getChild2();
        Formula child3 = boolFunc->getChild3();

        Cnf childs = tseitinChilds(child1, child2, child3, auxToNode);
        result.addCnf(childs);

        if(type == NOD_NOT)tseitinNOT(boolFunc,auxToNode,child1);

        else if(type == NOD_AND || type == NOD_OR){
            int varC1 = getNodeVar(child1, auxToNode);
            int varC2 = getNodeVar(child2, auxToNode);
            int me = VarsManager::newId("");
            //Insert ourself into the map
            auxToNode[boolFunc] = me;

            Clause c1,c2,c3;

            //IDEA: Depenent de quin operador és i de si hi ha algun fill true o false, ja podem saber si es complirà o no
            if (type == NOD_AND) {
                //Si un child és false ja sabem que no es complirà
                c1 = Clause(2,-me,varC1); //c1.addVar(-me);c1.addVar(varC1);
                c2 = Clause(2,-me,varC2); //c2.addVar(-me);c2.addVar(varC2);
                c3 = Clause(3,-varC1,-varC2,me); //c3.addVar(-varC1);c3.addVar(-varC2);c3.addVar(me);
            }
            else { //OR
                //Si un dels childs es true ja sabem que es complirà
                c1 = Clause(2,me,-varC1); //c1.addVar(me);c1.addVar(-varC1);
                c2 = Clause(2,me,-varC2); //c2.addVar(me);c2.addVar(-varC2);
                c3 = Clause(3,varC1,varC2,-me); //c3.addVar(varC1);c3.addVar(varC2);c3.addVar(-me);
            }

            result.addClause(c1);
            result.addClause(c2);
            result.addClause(c3);

        }
        //FIXME: Acabar d'implementar aquests casos
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

    static Cnf convertToCnf(const BDD & f){

        Cnf result;
        // Trivial cases
        if (f.IsOne()){
            if (f.IsZero()){result.addUnsat();}
            // Nothing to do
            return result;
        }

        // Normal case: extract prime by prime
        BDD g = !f;
        BDD remainder = g;

        Clause clause;

        while (not remainder.IsZero()) {
            BDD prime = remainder.LargestCube();
            prime = prime.MakePrime(g);
            remainder *= !prime;

            clause.clear();
            // Store the cube as a clause
            while (not prime.IsOne()) {

                int idx = prime.NodeReadIndex();
                int my_idx = VarsManager::getIdFromCudd(idx);
                BDD v = VarsManager::bddVar(idx);
                BDD cof = prime.Cofactor(v);
                if (not cof.IsZero()) {
                    // Positive literal (negative in the CNF)
                    clause.addVar(-my_idx);
                    prime = cof;
                } else {
                    clause.addVar(my_idx);
                    prime = prime.Cofactor(!v);
                }
            }
            result.addClause(clause);
        }
    }
};

#endif // CNFCONVERTER_H
