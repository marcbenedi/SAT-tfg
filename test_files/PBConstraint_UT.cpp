#include "gtest/gtest.h"
#include "PBConstraint.h"

namespace {

    TEST(Constructors, constructor){

        std::vector<int64_t> i_weights = {3,2};
        std::vector<int32_t> i_literals = {1,2};

        PBConstraint c = PBConstraint(PBFormula(i_weights,i_literals),1);
        PBFormula a = c.getPBFormula();
        int64_t k = c.getK();

        EXPECT_EQ(k,1);

        std::vector<int64_t> weights = a.getWeights();
        std::vector<int32_t> literals = a.getLiterals();
        for (size_t i = 0; i < weights.size(); i++) {
            EXPECT_EQ(i_weights[i], weights[i]);
            EXPECT_EQ(i_literals[i], literals[i]);
        }
    }

    TEST(Encode, encode){
        PBConstraint c = PBConstraint(PBFormula({3,2},{1,2}),1);
        std::vector< std::vector< int32_t > > cnf;
        int32_t firstFreshVariable = 3;
        c.encode(cnf, firstFreshVariable);
        std::string s = "";
        for (size_t i = 0; i < cnf.size(); i++) {
            std::vector< int32_t > *clause = &cnf[i];
            for (size_t j = 0; j < clause->size(); j++) {
                s += std::to_string((*clause)[j]) + " ";
            }
            s +="0 ";
        }
        std::string expected = "-2 0 -1 0 ";
        EXPECT_EQ(expected, s);
    }

}
