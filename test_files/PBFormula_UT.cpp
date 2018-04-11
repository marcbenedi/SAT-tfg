#include "gtest/gtest.h"
#include "PBFormula.h"

namespace {

    TEST(Constructors, empty){
        ASSERT_DEATH( {PBFormula a = PBFormula({},{});},"");
    }

    TEST(Constructors, differentSize){
        ASSERT_DEATH( {PBFormula a = PBFormula({3},{});},"");
    }

    TEST(Constructors, valid){
        std::vector<int64_t> i_weights = {3,2};
        std::vector<int32_t> i_literals = {1,2};
        PBFormula a = PBFormula(i_weights, i_literals);
        std::vector<int64_t> weights = a.getWeights();
        std::vector<int32_t> literals = a.getLiterals();
        for (size_t i = 0; i < weights.size(); i++) {
            EXPECT_EQ(i_weights[i], weights[i]);
            EXPECT_EQ(i_literals[i], literals[i]);
        }
    }

    TEST(Constructors, valid2){
        std::vector<int64_t> i_weights = {-3,2};
        std::vector<int32_t> i_literals = {1,-2};
        PBFormula a = PBFormula(i_weights, i_literals);
        std::vector<int64_t> weights = a.getWeights();
        std::vector<int32_t> literals = a.getLiterals();
        for (size_t i = 0; i < weights.size(); i++) {
            EXPECT_EQ(i_weights[i], weights[i]);
            EXPECT_EQ(i_literals[i], literals[i]);
        }
    }

    TEST(addPair,addPair){
        std::vector<int64_t> i_weights = {-3,2,4};
        std::vector<int32_t> i_literals = {1,-2,3};
        PBFormula a = PBFormula({-3,2}, {1,-2});

        a.addPair(4,3);
        std::vector<int64_t> weights = a.getWeights();
        std::vector<int32_t> literals = a.getLiterals();
        for (size_t i = 0; i < weights.size(); i++) {
            EXPECT_EQ(i_weights[i], weights[i]);
            EXPECT_EQ(i_literals[i], literals[i]);
        }
    }



}
