#include "gtest/gtest.h"
#include "Cnf.h"

namespace {

    TEST(Constructors,defaultConstructor){
        Cnf c;
        ASSERT_EQ(0,c.getClauseNumber());
        ASSERT_EQ(0,c.getNumVars());
    }

    TEST(GetNumVars, emptyCnf){
        Cnf c;
        ASSERT_EQ(0,c.getNumVars());
    }

    TEST(AddClause, addEmptyClause){
        Cnf c;
        Clause clause;
        c.addClause(clause);
        ASSERT_EQ(1,c.getClauseNumber());
        c.addClause(clause);
        ASSERT_EQ(2,c.getClauseNumber());
        ASSERT_EQ(0,c.getNumVars());
    }

    TEST(AddClause, addClause){
        Cnf c;
        Clause clause = Clause(5,1,2,3,4,5);
        c.addClause(clause);
        ASSERT_EQ(1,c.getClauseNumber());
        ASSERT_EQ(5,c.getNumVars());
    }

    TEST(Clear, clearEmpty){
        Cnf c;
        c.clear();
        ASSERT_EQ(0,c.getClauseNumber());
        ASSERT_EQ(0,c.getNumVars());
    }

    TEST(Clear, clear){
        Cnf c;
        Clause clause = Clause(5,1,2,3,4,5);
        c.addClause(clause);
        c.clear();
        ASSERT_EQ(0,c.getClauseNumber());
        ASSERT_EQ(0,c.getNumVars());
    }

    TEST(Picosat, printPicosat){
        Cnf cnf; Clause c1,c2,c3;
        c1 = Clause(3,1,2,3);
        c2 = Clause(3,4,5,6);
        c3 = Clause(3,1,2,3);
        cnf.addClause(c1);
        cnf.addClause(c2);
        cnf.addClause(c3);
        std::string result = cnf.picosat();
        std::string expected = "p cnf 6 3 1 2 3 0 4 5 6 0 1 2 3 0";
        EXPECT_EQ(result,expected);
    }

    TEST(Picosat, addUnsat){
        Cnf cnf;
        cnf.addUnsat();
        std::string result = cnf.picosat();
        std::string expected = "p cnf 0 1 0";
        EXPECT_EQ(result,expected);
    }

}
