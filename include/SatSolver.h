#ifndef SATSOLVER_H
#define SATSOLVER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>

#include "Cnf.h"

class SatSolver{
private:
    SatSolver();
public:
    static void solve(Cnf cnf);
    static std::string solve2(Cnf cnf);
};

#endif // SATSOLVER_H
