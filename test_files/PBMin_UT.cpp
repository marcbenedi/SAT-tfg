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

    TEST(SolveBinary,solve){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-1,-3,7,-5},{1,-1,2,-2}));

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,-2,-3,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, -8);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveBinary,solve2){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({2,2},{1,-1}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-1,-3,7,-5},{1,-1,2,-2}));

        int64_t min;
        std::vector< int32_t > model;
        bool sat = m.solve(model, min);
        bool expected_sat = false;
        EXPECT_EQ(expected_sat, sat);
        EXPECT_EQ(model.size(), 0);
    }

    TEST(SolveBinary,solve3){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}));

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,-2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, -3);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveBinary,solve4){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}));

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, 7);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveBinary,solve5){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{-1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}));

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {1,2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, 3);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveBinary,knapsackProblem){
        //problem definition
        //http://www.mafy.lut.fi/study/DiscreteOpt/DYNKNAP.pdf
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1,5,3,4},{1,2,3,4}),8)
        };
        PBFormula costFunction = PBFormula({-15,-10,-9,-5},{1,2,3,4});
        PBMin m = PBMin(constraints, costFunction);
        bool e_sat = true;
        int64_t e_min = -29;
        std::vector< int32_t > expected_model = {1,-2,3,4};
        //execution and check
        int64_t min;
        std::vector< int32_t > model;
        bool sat = m.solve(model, min);
        EXPECT_EQ(e_sat, sat);
        EXPECT_EQ(min, e_min);
        for (size_t i = 0; i < expected_model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveLinear,solve){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-1,-3,7,-5},{1,-1,2,-2}),LINEAR_SEARCH);

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,-2,-3,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, -8);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveLinear,solve2){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({2,2},{1,-1}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-1,-3,7,-5},{1,-1,2,-2}),LINEAR_SEARCH);

        int64_t min;
        std::vector< int32_t > model;
        bool sat = m.solve(model, min);
        bool expected_sat = false;
        EXPECT_EQ(expected_sat, sat);
        EXPECT_EQ(model.size(), 0);
    }

    TEST(SolveLinear,solve3){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3)
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}),LINEAR_SEARCH);

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,-2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, -3);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveLinear,solve4){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}),LINEAR_SEARCH);

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {-1,2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, 7);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveLinear,solve5){
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{-1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBMin m = PBMin(e_constraints, PBFormula({-7,-3,10},{1,-1,2}),LINEAR_SEARCH);

        int64_t min;
        std::vector< int32_t > model;
        std::vector< int32_t > expected_model = {1,2,0};
        bool sat = m.solve(model, min);
        EXPECT_EQ(true, sat);
        EXPECT_EQ(min, 3);
        for (size_t i = 0; i < model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

    TEST(SolveLinear,knapsackProblem){
        //problem definition
        //http://www.mafy.lut.fi/study/DiscreteOpt/DYNKNAP.pdf
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1,5,3,4},{1,2,3,4}),8)
        };
        PBFormula costFunction = PBFormula({-15,-10,-9,-5},{1,2,3,4});
        PBMin m = PBMin(constraints, costFunction,LINEAR_SEARCH);
        bool e_sat = true;
        int64_t e_min = -29;
        std::vector< int32_t > expected_model = {1,-2,3,4};
        //execution and check
        int64_t min;
        std::vector< int32_t > model;

        bool sat = m.solve(model, min);
        EXPECT_EQ(e_sat, sat);
        EXPECT_EQ(min, e_min);
        for (size_t i = 0; i < expected_model.size(); i++) {
            EXPECT_EQ(model[i],expected_model[i]);
        }
    }

}
