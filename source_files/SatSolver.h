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

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Cnf.h"

class SatSolver{
private:
    SatSolver();
public:
    /**
     * Calls the command picosat with the cnf as input
     *@param cnf
     */
    static void solve(Cnf cnf);
    /**
     * Calls the command picosat with the cnf as input and returns the result
     *@param cnf
     *@return string : result from picosat
     */
    static std::string solve2(Cnf cnf);
};

#endif // SATSOLVER_H
