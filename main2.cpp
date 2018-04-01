#include <iostream>
#include <string>
#include "CnfConverter.h"
#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"
#include "BDDConverter.h"
#include "SatSolver.h"
#include "MixCNFConverter.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


void func(){
    Formula a = BoolFunc::newLit("a");
    VarsManager* m = VarsManager::getInstance();
    std::cout << m->getNumIds() << '\n';
}

int main() {

    func();
    VarsManager* m = VarsManager::getInstance();
    std::cout << m->getNumIds() << '\n';

}
