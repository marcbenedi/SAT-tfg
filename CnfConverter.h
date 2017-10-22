#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"

class CnfConverter{
private:
    CnfConverter();
public:
    static Cnf boolFuncToCnf(BoolFunc const & boolfunc){
        Cnf cnf;
        return cnf;
    }
};

#endif // CNFCONVERTER_H
