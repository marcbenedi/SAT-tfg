#include "gtest/gtest.h"
#include "VarsManager.h"

namespace {

    TEST(GetInstance,getInstance){
        VarsManager v = VarsManager::getInstance();
        ASSERT_EQ(0,v.getLastId());
    }

    TEST(NewId,newId){
        VarsManager v = VarsManager::getInstance();
        v.newId("a");
        v.newId("b");
        v.newId("c");
        ASSERT_EQ(3,v.getNumIds());
    }

    TEST(NewId,emptyId){
        VarsManager v = VarsManager::getInstance();
        v.newId("");
        v.newId("");
        v.newId("");
        ASSERT_EQ(3,v.getLastId());
    }

    TEST(NewId,repeatedId){
        VarsManager v = VarsManager::getInstance();
        int a1 = v.newId("a");
        int a2 = v.newId("a");
        ASSERT_EQ(a1,a2);
        ASSERT_EQ(1,v.getNumIds());
    }

    TEST(FreeId,freeExistingId){
        VarsManager v = VarsManager::getInstance();
        int id = v.newId("a");
        v.newId("b");
        v.freeId(id);
        ASSERT_EQ(1,v.getNumIds());
    }

    TEST(FreeId,freeNoExistingId){
        VarsManager v = VarsManager::getInstance();
        v.newId("a");
        v.newId("b");
        v.freeId(333);
        ASSERT_EQ(2,v.getNumIds());
    }

    TEST(StoreWithCuddId,storeCuddWithId){
        VarsManager v = VarsManager::getInstance();
        v.storeCuddWithId(1,2);
        int id = v.getIdFromCudd(1);
        ASSERT_EQ(2,id);

    }

    TEST(GetIdFromCudd,getNoExistingIdFromCudd){
        VarsManager v = VarsManager::getInstance();
        int id = v.getIdFromCudd(33);
        ASSERT_EQ(0,id);
    }

    TEST(BDDVar,bddVar){

    }

    TEST(GetCuddMgr,getCuddMgr){

    }

}
