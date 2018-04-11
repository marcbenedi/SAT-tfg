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
    }

}
