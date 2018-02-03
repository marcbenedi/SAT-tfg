#ifndef MIXCNFCONVERTER_H
#define MIXCNFCONVERTER_H

#include "BDDConverter.h"
#include "CnfConverter.h"
#include "VarsManager.h"
#include "BoolFunc.h"

#include <map>
#include <assert.h>

class MixCNFConverter{
private:
    static const int minValueCover = 0;
    std::map<Formula,Cnf> nodeToCnf;
    std::map<Formula,BDD> nodeToBDD;
    std::map<Formula,int> nodeToVar;
    Cnf result;

    void baseCase(Formula const & f){
        BDD bdd = BDDConverter::convertFormula(f);
        nodeToBDD[f] = bdd;
        nodeToCnf[f] = Cnf();
        nodeToVar[f] = f->getValue();
    }

    void hardBDD(Formula const & f){
        int var = nodeToVar[f];
        Formula old_c = f->getChild1(); //TODO: get biggest child
        int aux = VarsManager::newId("");
        Formula new_c = BoolFunc::newLit("");
        //f->childX = new_c;
        
    }

    void recursiveCase(Formula const & f){
        Formula child1 = f->getChild1();
        Formula child2 = f->getChild2();
        if (child1!=NULL) convertRec(child1);
        if (child2!=NULL) convertRec(child2);

        int var = VarsManager::newId("");
        nodeToVar[f] = var;

        BDD temp;

        NodeType type = f->getType();
        switch (type) {
            case NOD_ID:
                assert(false);
                break;
            case NOD_CONST:
                assert(false);
                break;
            case NOD_NOT:
                temp = ~nodeToBDD[child1];
                break;
            case NOD_AND:
                temp = nodeToBDD[child1] * nodeToBDD[child2];
                break;
            case NOD_OR:
                temp = nodeToBDD[child1] + nodeToBDD[child2];
                break;
            case NOD_XOR:
                assert(false);
                break;
            case NOD_COND:
                assert(false);
                break;
        }

        BDD largestCube = temp.LargestCube();
        BDD prime = largestCube.MakePrime(temp);

        //TODO: find condition
        if (true)
            hardBDD(f);
        else
            nodeToBDD[f] = temp;
    }

    void convertRec(Formula const & f){
        if (f->getType() == NOD_ID)
            baseCase(f);
        else
            recursiveCase(f);
    }

public:

    Cnf getResult(){
        return result;
    }

    void clear(){
        nodeToCnf.clear();
        nodeToBDD.clear();
        nodeToVar.clear();
        result.clear();
    }

    void convert(Formula const & f){
        clear();
        convertRec(f);
    }

};

#endif // MIXCNFCONVERTER_H
