#include "gtest/gtest.h"
#include "PBMin.h"
#include <vector>

namespace {

    TEST(Constructors, constructor){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };

        PBMin m = PBMin(e_constraints, PBFormula({3,-5},{-1,2}));
        std::vector< PBConstraint > constraints = m.getConstraints();
        PBFormula costFunction = m.getCostFunction();

        for (size_t i = 0; i < e_constraints.size(); i++) {
            EXPECT_EQ(constraints[i].getK(),e_constraints[i].getK());
            for (size_t k = 0; k < constraints[i].getPBFormula().getWeights().size(); k++) {
                EXPECT_EQ(e_constraints[i].getPBFormula().getWeights()[k], constraints[i].getPBFormula().getWeights()[k]);
                EXPECT_EQ(e_constraints[i].getPBFormula().getLiterals()[k], constraints[i].getPBFormula().getLiterals()[k]);
            }

        }

        EXPECT_EQ(BINARY_SEARCH, m.getSearchType());
    }

    TEST(Constructors,binarySearch){
        PBMin m = PBMin({}, PBFormula({3,-5},{-1,2}), BINARY_SEARCH);
        EXPECT_EQ(m.getSearchType(), BINARY_SEARCH);
    }

    TEST(Constructors,linearSearch){
        PBMin m = PBMin({}, PBFormula({3,-5},{-1,2}), LINEAR_SEARCH);
        EXPECT_EQ(m.getSearchType(), LINEAR_SEARCH);
    }

    TEST(GetFirstFreshVariable,getFirstFreshVariable){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };

        PBMin m = PBMin(e_constraints, PBFormula({3,-5},{-1,2}));
        EXPECT_EQ(m.getFirstFreshVariable(), 4);
    }

    TEST(GetFirstFreshVariable,getFirstFreshVariable2){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{-1,-2}),1),
            PBConstraint(PBFormula({3,4},{2,-3}),1),
            PBConstraint(PBFormula({3,7},{1,-3}),1)
        };

        PBMin m = PBMin(e_constraints, PBFormula({3,-5},{-1,2}));
        EXPECT_EQ(m.getFirstFreshVariable(), 4);
    }

    TEST(GetFirstFreshVariable,getFirstFreshVariable3){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{-1,-2}),1),
            PBConstraint(PBFormula({3,4},{2,-3}),1),
            PBConstraint(PBFormula({3,7},{1,-3}),1)
        };

        PBMin m = PBMin(e_constraints, PBFormula({3,-5},{4,5}));
        EXPECT_EQ(m.getFirstFreshVariable(), 6);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax){
        PBMin m = PBMin({}, PBFormula({1,1},{1,2}));
        EXPECT_EQ(m.getCostFunctionMax(), 2);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax2){
        PBMin m = PBMin({}, PBFormula({1,1},{1,-1}));
        EXPECT_EQ(m.getCostFunctionMax(), 1);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax3){
        PBMin m = PBMin({}, PBFormula({1,2,3},{1,2,3}));
        EXPECT_EQ(m.getCostFunctionMax(), 6);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax4){
        PBMin m = PBMin({}, PBFormula({-1,-2,3},{1,2,3}));
        EXPECT_EQ(m.getCostFunctionMax(), 3);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax5){
        PBMin m = PBMin({}, PBFormula({-1,-3},{1,-1}));
        EXPECT_EQ(m.getCostFunctionMax(), -1);
    }

    TEST(GetCostFunctionMax,getCostFunctionMax6){
        PBMin m = PBMin({}, PBFormula({-1,-3,7,-5},{1,-1,2,-2}));
        EXPECT_EQ(m.getCostFunctionMax(), 6);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin){
        PBMin m = PBMin({}, PBFormula({1,1},{1,2}));
        EXPECT_EQ(m.getCostFunctionMin(), 0);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin2){
        PBMin m = PBMin({}, PBFormula({1,1},{1,-1}));
        EXPECT_EQ(m.getCostFunctionMin(), 1);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin3){
        PBMin m = PBMin({}, PBFormula({-1,-2,-3},{1,2,3}));
        EXPECT_EQ(m.getCostFunctionMin(), -6);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin4){
        PBMin m = PBMin({}, PBFormula({-1,-2,3},{1,2,3}));
        EXPECT_EQ(m.getCostFunctionMin(), -3);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin5){
        PBMin m = PBMin({}, PBFormula({-1,-3},{1,-1}));
        EXPECT_EQ(m.getCostFunctionMin(), -3);
    }

    TEST(GetCostFunctionMin,getCostFunctionMin6){
        PBMin m = PBMin({}, PBFormula({-1,-3,7,-5},{1,-1,2,-2}));
        EXPECT_EQ(m.getCostFunctionMin(), -8);
    }



}
