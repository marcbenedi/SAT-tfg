#include "MixCNFConverter.h"
void MixCNFConverter::baseCase(Formula const & f){
    BDD bdd = BDDConverter::convertFormula(f);
    //This is done by BDDConverter
    // int idx = bdd.NodeReadIndex();
    // VarsManager::storeCuddWithId(idx,f->getValue());

    //TODO: delete this code
    BDD largestCube = bdd.LargestCube();//maxim 1's restants
    BDD prime = largestCube.MakePrime(bdd);//extendre'l a altres 1's

    double d = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                prime.getNode(),
                0);
    //f->print();
    //std::cout << d << std::endl;

    nodeToBDD[f] = bdd;
    nodeToCnf[f] = CnfConverter::convertToCnf(bdd);
    //nodeToCnf[f] = Cnf();
}

Formula MixCNFConverter::getBiggestChild(Formula const & f){
    //TODO: implement
    return f->getChild1();
}

Formula MixCNFConverter::getSmallestChild(Formula const & f){
    //TODO: implement
    return f->getChild2();
}

void MixCNFConverter::replaceChild(Formula const & f, Formula const & old_c, Formula const & new_c){
    if (f->getChild1() == old_c)
        f->setChild1(new_c);
    else if (f->getChild2() == old_c)
        f->setChild2(new_c);
    else
        assert(false);
}

void MixCNFConverter::hardBDD(Formula const & f){
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

void MixCNFConverter::recursiveCase(Formula const & f){
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

    double d = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
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

void MixCNFConverter::convertRec(Formula const & f){
    if (f->getType() == NOD_ID)
        baseCase(f);
    else
        recursiveCase(f);
}



Cnf MixCNFConverter::getResult(){
    return result;
}

void MixCNFConverter::clear(){
    nodeToCnf.clear();
    nodeToBDD.clear();
    result.clear();
}

void MixCNFConverter::convert(Formula const & f){
    clear();
    convertRec(f);
    Cnf remaining = CnfConverter::convertToCnf(nodeToBDD[f]);
    result.addCnf(remaining);
}

void MixCNFConverter::setValueCover(int i){
    minValueCover = i;
}

//TODO: replace by value
const double X = 0.0;

bool MixCNFConverter::worthToConvert(const BDD & f){
    if(f.IsOne() || f.IsZero())
        return true;

    BDD remainder = f;

    double d2 = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                f.getNode(),
                0);
    std::cout << "Original\t" <<d2 << '\n';
    std::cout << '\n';

    while(not remainder.IsZero()){
        BDD cube = remainder.LargestCube();
        BDD prime = cube.MakePrime(f);
        BDD prime2 = cube.MakePrime(remainder);
        BDD remainderactual = remainder;
        BDD primeremainder = remainder*prime;

        remainder *= !prime;

        double d5 = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    remainderactual.getNode(),
                    0);
        std::cout << "Remainder Actual\t" <<d5 << '\n';

        double d4 = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    cube.getNode(),
                    0);
        std::cout << "Cube\t" <<d4 << '\n';

        double d3 = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    remainder.getNode(),
                    0);
        std::cout << "Remainder\t" <<d3 << '\n';

        double d = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    prime.getNode(),
                    0);
        std::cout << "Prime\t" << d << '\n';

        double d6 = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    prime2.getNode(),
                    0);
        std::cout << "Prime2\t" << d6 << '\n';

        double pr = Cudd_CountMinterm(VarsManager::getInstance()->getCuddMgr(),
                    primeremainder.getNode(),
                    0);
        std::cout << "PrimeRemainder\t" << pr << '\n';

        if (d < X)
            return false;

        std::cout << '\n';
    }

    return true;
}
