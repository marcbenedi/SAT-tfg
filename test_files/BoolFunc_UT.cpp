#include "gtest/gtest.h"
#include "BoolFunc.h"

namespace {

    TEST(Constructors,node_id){
        BoolFunc f = BoolFunc("a");
        ASSERT_EQ(f.getType(),NOD_ID);
        ASSERT_EQ(f.getValue(),1);
    }

    TEST(Constructors,node_not){
        BoolFunc f = BoolFunc(NOD_NOT,NULL);
        ASSERT_EQ(f.getType(),NOD_NOT);
        ASSERT_EQ(f.getValue(),UNDEF);
    }

    // TEST(Constructors,node_not_invalid){
    //     ASSERT_ANY_THROW(BoolFunc f = BoolFunc(NOD_ID,NULL));
    // }

    // TEST(Constructors,node_binary_op_invalid){
    //     ASSERT_ANY_THROW(BoolFunc f = BoolFunc(NOD_ID,NULL,NULL));
    // }

    TEST(Constructors,node_or){
        BoolFunc f = BoolFunc(NOD_OR,NULL,NULL);
        ASSERT_EQ(f.getType(),NOD_OR);
        ASSERT_EQ(f.getValue(),UNDEF);
    }

    TEST(Constructors,node_and){
        BoolFunc f = BoolFunc(NOD_AND,NULL,NULL);
        ASSERT_EQ(f.getType(),NOD_AND);
        ASSERT_EQ(f.getValue(),UNDEF);
    }

    TEST(Constructors,node_xor){
        BoolFunc f = BoolFunc(NOD_XOR,NULL,NULL);
        ASSERT_EQ(f.getType(),NOD_XOR);
        ASSERT_EQ(f.getValue(),UNDEF);
    }

    TEST(Constructors,copy_node){
        //TODO: To implement
    }

    TEST(FormulaConstructors,newNot){
        Formula a = BoolFunc::newLit("a");
        Formula n = BoolFunc::newNot(a);
        ASSERT_EQ(n->getType(),NOD_NOT);
        ASSERT_EQ(n->getChild1(), a);
    }

    TEST(FormulaConstructors,newAnd){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = BoolFunc::newAnd(a,b);
        ASSERT_EQ(f->getType(),NOD_AND);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaConstructors,newOr){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = BoolFunc::newOr(a,b);
        ASSERT_EQ(f->getType(),NOD_OR);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaConstructors,newXor){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = BoolFunc::newXor(a,b);
        ASSERT_EQ(f->getType(),NOD_XOR);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);

    }

    TEST(FormulaConstructors,newLit){
        Formula a = BoolFunc::newLit("a");
        ASSERT_EQ(a->getType(),NOD_ID);
    }

    TEST(FormulaOperator,equals){
        //TODO: To implement
    }

    TEST(FormulaOperator,not1){
        Formula a = BoolFunc::newLit("a");
        Formula f = !a;
        ASSERT_EQ(f->getType(),NOD_NOT);
        ASSERT_EQ(f->getChild1(), a);
    }

    TEST(FormulaOperator,not2){
        Formula a = BoolFunc::newLit("a");
        Formula f = ~a;
        ASSERT_EQ(f->getType(),NOD_NOT);
        ASSERT_EQ(f->getChild1(), a);
    }

    TEST(FormulaOperator,and1){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a*b;
        ASSERT_EQ(f->getType(),NOD_AND);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaOperator,and2){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a&b;
        ASSERT_EQ(f->getType(),NOD_AND);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaOperator,or1){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a+b;
        ASSERT_EQ(f->getType(),NOD_OR);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaOperator,or2){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a|b;
        ASSERT_EQ(f->getType(),NOD_OR);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaOperator,xor1){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        Formula f = a^b;
        ASSERT_EQ(f->getType(),NOD_XOR);
        ASSERT_EQ(f->getChild1(), a);
        ASSERT_EQ(f->getChild2(), b);
    }

    TEST(FormulaOperator,orequals){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        a += b;
        ASSERT_EQ(a->getType(),NOD_OR);
        // ASSERT_EQ(a->getChild1(), a);
        ASSERT_EQ(a->getChild2(), b);
    }

    TEST(FormulaOperator,andequals){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        a *= b;
        ASSERT_EQ(a->getType(),NOD_AND);
        // ASSERT_EQ(a->getChild1(), a);
        ASSERT_EQ(a->getChild2(), b);
    }

    TEST(FormulaOperator,xorequals){
        Formula a = BoolFunc::newLit("a");
        Formula b = BoolFunc::newLit("b");
        a ^= b;
        ASSERT_EQ(a->getType(),NOD_XOR);
        // ASSERT_EQ(a->getChild1(), a);
        ASSERT_EQ(a->getChild2(), b);
    }

}
