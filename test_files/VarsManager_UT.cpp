#include "gtest/gtest.h"
#include "VarsManager.h"

namespace {

    TEST(GetInstance,getInstance){
        VarsManager* v = VarsManager::getInstance();
        ASSERT_EQ(0,v->getLastId());
    }

    TEST(NewId,newId){
        VarsManager* v = VarsManager::getInstance();
        v->newId("a");
        v->newId("b");
        v->newId("c");
        ASSERT_EQ(3,v->getNumIds());
        v->clearInstance();
    }

    TEST(NewId,diferentIds){
        VarsManager* v = VarsManager::getInstance();
        int a = v->newId("a");
        int b = v->newId("b");
        int c = v->newId("c");
        ASSERT_EQ(a,1);
        ASSERT_EQ(b,2);
        ASSERT_EQ(c,3);
        ASSERT_EQ(3,v->getNumIds());
        v->clearInstance();
    }

    TEST(NewId,emptyId){
        VarsManager* v = VarsManager::getInstance();
        v->newId("");
        v->newId("");
        v->newId("");
        ASSERT_EQ(3,v->getLastId());
        v->clearInstance();
    }

    //TODO: new ID quan n'hi ha per reciclar

    TEST(NewId,repeatedId){
        VarsManager* v = VarsManager::getInstance();
        int a1 = v->newId("a");
        int a2 = v->newId("a");
        ASSERT_EQ(a1,a2);
        ASSERT_EQ(1,v->getNumIds());
        v->clearInstance();
    }

    TEST(FreeId,freeExistingId){
        VarsManager* v = VarsManager::getInstance();
        int id = v->newId("a");
        v->newId("b");
        v->freeId(id);
        ASSERT_EQ(1,v->getNumIds());
        v->clearInstance();
    }

    TEST(FreeId,freeNoExistingId){
        VarsManager* v = VarsManager::getInstance();
        v->newId("a");
        v->newId("b");
        v->freeId(333);
        ASSERT_EQ(2,v->getNumIds());
        v->clearInstance();
    }

    TEST(StoreWithCuddId,storeCuddWithId){
        VarsManager* v = VarsManager::getInstance();
        v->storeCuddWithId(1,2);
        int id = v->getIdFromCudd(1);
        ASSERT_EQ(2,id);
        v->clearInstance();
    }

    TEST(GetIdFromCudd,getNoExistingIdFromCudd){
        VarsManager* v = VarsManager::getInstance();
        int id = v->getIdFromCudd(33);
        ASSERT_EQ(0,id);
        v->clearInstance();
    }

    TEST(BDDVar,bddVar){
        //TODO: To implement
    }

    TEST(GetCuddMgr,getCuddMgr){
        //TODO: To implement
    }

}
