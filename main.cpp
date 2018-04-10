#include <iostream>
#include <string>
#include "VarsManager.h"

void func1(){
    VarsManager* m = VarsManager::getInstance();
    m->newId("a");
}

void func2(){
    VarsManager *m = VarsManager::getInstance();
    m->newId("b");
    std::cout << m->getLastId() << '\n';
    m->clearInstance();
}

void func3(){
    VarsManager *m = VarsManager::getInstance();
    std::cout << m->getLastId() << '\n';
    m->newId("c");
}

void func4(){
    VarsManager *m = VarsManager::getInstance();
    m->newId("d");
    std::cout <<"ddsdsffd"<< m->getLastId() << '\n';
    m->clearInstance();
}


int main() {
    func1();
    func2();
    func3();
    func4();
}
