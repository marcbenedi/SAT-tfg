#include "gtest/gtest.h"
#include "BoolFunc.h"

namespace {

    TEST(Constructors,node_id){
        BoolFunc f = BoolFunc("a");
        ASSERT_EQ(f.getType(),NOD_ID);
        ASSERT_EQ(f.getValue(),1);
    }

}
