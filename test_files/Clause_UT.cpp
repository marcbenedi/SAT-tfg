#include "gtest/gtest.h"
#include "Clause.h"

namespace {

    TEST(Constructors,defaultConstructor){
        Clause c = Clause();
        ASSERT_EQ(0,c.getNumVars());
    }
    TEST(Constructors,paramZero){
        Clause c = Clause(0);
        ASSERT_EQ(0,c.getNumVars());
    }
    TEST(Constructors,paramNoZero){
        Clause c = Clause(5,1,2,3,4,5);
        ASSERT_EQ(5,c.getNumVars());
        for (size_t i = 0; i < 5; i++) {
            ASSERT_EQ(i+1,c.getVar(i));
        }
    }
    TEST(AddVar,addOne){
        Clause c = Clause();
        c.addVar(-1);
        ASSERT_EQ(1,c.getNumVars());
        ASSERT_EQ(-1,c.getVar(0));
    }
    TEST(Clear,clear){
        Clause c = Clause();
        c.addVar(-1);
        c.clear();
        ASSERT_EQ(0,c.getNumVars());
    }

}
