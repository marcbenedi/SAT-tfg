#include "gtest/gtest.h"
#include "CnfConverter.h"

namespace {

    TEST(Tseitin,var){
        Formula a = BoolFunc::newLit("a");
        Cnf cnf = CnfConverter::tseitin(a);
        ASSERT_EQ(cnf.picosat(), "p cnf 1 1 1 0");
        VarsManager::getInstance()->clearInstance();
    }

    TEST(Tseitin,Not){
        Formula a = BoolFunc::newLit("a");
        Formula f = !a;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 1 1 -1 0");
        VarsManager::getInstance()->clearInstance();
    }

    TEST(Tseitin,And){
        Formula a = BoolFunc::newLit("a");
        std::cout << "formula a " <<a->getValue() << '\n';
        Formula b = BoolFunc::newLit("b");
        std::cout << "formula b " <<b->getValue() << '\n';
        Formula f = a*b;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 3 4 -3 1 0 -3 2 0 -1 -2 3 0 3 0");
        VarsManager::getInstance()->clearInstance();
    }

    TEST(Tseitin,Or){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a+b;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 3 4 3 -1 -0 3 -2 0 1 2 -3 0 3 0");
        VarsManager::getInstance()->clearInstance();
    }


    //TODO: test this class

    TEST(convertToCnf,bdd1){

    }

}
