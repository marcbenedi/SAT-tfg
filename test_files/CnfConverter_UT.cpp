#include "gtest/gtest.h"
#include "CnfConverter.h"

namespace {

    TEST(Tseitin,var){
        VarsManager::getInstance()->clearInstance();
        Formula a = BoolFunc::newLit("a");
        Cnf cnf = CnfConverter::tseitin(a);
        ASSERT_EQ(cnf.picosat(), "p cnf 1 1 1 0");
    }

    TEST(Tseitin,Not){
        VarsManager::getInstance()->clearInstance();
        Formula a = BoolFunc::newLit("a");
        Formula f = !a;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 1 1 -1 0");
    }

    TEST(Tseitin,And){
        VarsManager::getInstance()->clearInstance();
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a*b;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 3 4 -3 1 0 -3 2 0 -1 -2 3 0 3 0");
    }

    TEST(Tseitin,Or){
        VarsManager::getInstance()->clearInstance();
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a+b;
        Cnf cnf = CnfConverter::tseitin(f);
        ASSERT_EQ(cnf.picosat(), "p cnf 3 4 3 -1 0 3 -2 0 1 2 -3 0 3 0");
    }


    //TODO: test this class

    TEST(convertToCnf,bdd1){

    }

}
