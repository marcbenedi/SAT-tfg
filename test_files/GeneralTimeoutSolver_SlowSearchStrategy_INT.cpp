#include "gtest/gtest.h"

#include "GeneralTimeoutSolver.h"
#include "SlowSearchStrategy_Stub.cpp"

namespace {

    TEST(Solve,noTimeout){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1},{1}),1)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = true;
        int64_t e_min = 123;
        std::vector< int32_t > e_model = {1,2,3};

        SlowSearchStrategy_Stub bs;
        PBMin m = PBMin(constraints, costFunction);
        GeneralTimeoutSolver s(5,&bs,m);
        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(s.hasTimeoutOccurred(), false);
    }

    TEST(Solve,timeout){
        std::vector< PBConstraint > constraints = {
            PBConstraint(PBFormula({1},{1}),1)
        };
        PBFormula costFunction({1},{1});
        bool e_sat = false;

        SlowSearchStrategy_Stub bs;
        PBMin m = PBMin(constraints, costFunction);
        GeneralTimeoutSolver s(1,&bs,m);
        std::vector< int32_t > model;
        int64_t min;
        bool sat = s.run(model,min);
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(s.hasTimeoutOccurred(), true);
    }


}
