#ifndef MIXCNFCONVERTER_H
#define MIXCNFCONVERTER_H

#include "BDDConverter.h"
#include "CnfConverter.h"
#include "VarsManager.h"
#include "BoolFunc.h"

#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"

#include <map>
#include <assert.h>

#include <stdlib.h>

//TODO: ALLIBREAMENT DE MEMORIA
class MixCNFConverter{
private:
    int minValueCover = 0;
    std::map<Formula,Cnf> nodeToCnf;
    std::map<Formula,BDD> nodeToBDD;
    Cnf result;

    void baseCase(Formula const & f){
        BDD bdd = BDDConverter::convertFormula(f);
        //This is done by BDDConverter
        // int idx = bdd.NodeReadIndex();
        // VarsManager::storeCuddWithId(idx,f->getValue());

        //TODO: delete this code
        BDD largestCube = bdd.LargestCube();//maxim 1's restants
        BDD prime = largestCube.MakePrime(bdd);//extendre'l a altres 1's

        double d = Cudd_CountMinterm(VarsManager::getCuddMgr(),
                    prime.getNode(),
                    0);
        //f->print();
        //std::cout << d << std::endl;

        nodeToBDD[f] = bdd;
        nodeToCnf[f] = CnfConverter::convertToCnf(bdd);
        //nodeToCnf[f] = Cnf();
    }

    Formula getBiggestChild(Formula const & f){
        //TODO: implement
        return f->getChild1();
    }

    Formula getSmallestChild(Formula const & f){
        //TODO: implement
        return f->getChild2();
    }

    void replaceChild(Formula const & f, Formula const & old_c, Formula const & new_c){
        if (f->getChild1() == old_c)
            f->setChild1(new_c);
        else if (f->getChild2() == old_c)
            f->setChild2(new_c);
        else
            assert(false);
    }

    void hardBDD(Formula const & f){
        Formula old_c = getBiggestChild(f);
        Formula new_c = BoolFunc::newLit("");
        replaceChild(f, old_c, new_c);

        //Setup new_c
        BDD bdd_new_c = BDDConverter::convertFormula(new_c);
        nodeToBDD[new_c] = bdd_new_c;
        //nodeToCnf[new_c] = Cnf();
        nodeToCnf[new_c] = CnfConverter::convertToCnf(bdd_new_c);

        // OLD_C XNOR NEW_C
        BDD substitution = (nodeToBDD[old_c] * nodeToBDD[new_c]) + (!nodeToBDD[old_c] * !nodeToBDD[new_c]);
        // Store its cnf
        result.addCnf(CnfConverter::convertToCnf(substitution));

        // Do BDD of f with the new_c
        BDD temp;

        switch (f->getType()) {
            case NOD_NOT:
                temp = ~bdd_new_c;
                break;
            case NOD_AND:
                temp = bdd_new_c * nodeToBDD[getSmallestChild(f)];
                break;
            case NOD_OR:
                temp = bdd_new_c + nodeToBDD[getSmallestChild(f)];
                break;
            case NOD_XOR:
                //TODO: implement this case
                assert(false && "Still not implemented");
                break;
        }

        nodeToBDD[f] = temp;
        nodeToCnf[f] = CnfConverter::convertToCnf(temp);

    }

    void recursiveCase(Formula const & f){
        Formula child1 = f->getChild1();
        Formula child2 = f->getChild2();
        if (child1!=NULL) convertRec(child1);
        if (child2!=NULL) convertRec(child2);

        BDD temp;

        NodeType type = f->getType();
        switch (type) {
            case NOD_ID:
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
                //TODO: implement this case
                assert(false && "Still not implemented");
                break;
        }

        BDD largestCube = temp.LargestCube();//maxim 1's restants
        BDD prime = largestCube.MakePrime(temp);//extendre'l a altres 1's

        double d = Cudd_CountMinterm(VarsManager::getCuddMgr(),
                    prime.getNode(),
                    0);
        // std::string  s_value = getenv ("D");
        // double value = atof(s_value.c_str());
        // value /= 1000.0;

        if (d <= (minValueCover/1000.0))
            hardBDD(f);
        else{
            Cnf myCnf = CnfConverter::convertToCnf(temp);
            nodeToCnf[f] = myCnf;
            nodeToBDD[f] = temp;
        }
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
        result.clear();
    }

    void convert(Formula const & f){
        clear();
        convertRec(f);
        Cnf remaining = CnfConverter::convertToCnf(nodeToBDD[f]);
        result.addCnf(remaining);
    }

    void setValueCover(int i){
        minValueCover = i;
    }

};

#endif // MIXCNFCONVERTER_H
