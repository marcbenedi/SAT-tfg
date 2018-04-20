#include "gtest/gtest.h"

#include "Solver.h"
#include "LinearSearchStrategy.h"

namespace {

    TEST(Solve,problem1){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1},{1}),1)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = true;
        int64_t e_min = 0;
        std::vector< int32_t > e_model = {-1};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,problem2){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBFormula costFunction({-1,-3,7,-5},{1,-1,2,-2});
        bool e_sat = true;
        int64_t e_min = -8;
        std::vector< int32_t > e_model = {-1,-2,-3};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,problem3){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({2,2},{1,-1}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBFormula costFunction({-1,-3,7,-5},{1,-1,2,-2});
        bool e_sat = false;
        int64_t e_min = -8;
        std::vector< int32_t > e_model = {-1};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        EXPECT_EQ(sat, e_sat);
    }

    TEST(Solve,problem4){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({4},{1}),3)
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});
        bool e_sat = true;
        int64_t e_min = -3;
        std::vector< int32_t > e_model =  {-1,-2};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,problem5){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3)
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});
        bool e_sat = true;
        int64_t e_min = 7;
        std::vector< int32_t > e_model =  {-1,2};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,problem6){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({4},{-1}),3),
            PBConstraint(PBFormula({4},{-2}),3)
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});
        bool e_sat = true;
        int64_t e_min = 3;
        std::vector< int32_t > e_model =  {1,2};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,knapsackProblem){
        //problem definition
        //http://www.mafy.lut.fi/study/DiscreteOpt/DYNKNAP.pdf
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1,5,3,4},{1,2,3,4}),8)
        };
        PBFormula costFunction({-15,-10,-9,-5},{1,2,3,4});
        bool e_sat = true;
        int64_t e_min = -29;
        std::vector< int32_t > e_model =  {1,-2,3,4};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,minimumIsTheFirstK){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1},{-1}),0)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = true;
        int64_t e_min = 1;
        std::vector< int32_t > e_model =  {1};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,minimumIsTheLastK){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1},{1}),0)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = true;
        int64_t e_min = 0;
        std::vector< int32_t > e_model =  {-1};

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(Solve,unsat){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({2},{1}),1),
            PBConstraint(PBFormula({2},{-1}),1)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = false;
        int64_t e_min;
        std::vector< int32_t > e_model;

        LinearSearchStrategy bs;
        PBMin m = PBMin(constraints, costFunction);
        Solver s(&bs,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);

        EXPECT_EQ(sat, e_sat);
    }

}
