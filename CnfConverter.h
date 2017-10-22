#ifndef CNFCONVERTER_H
#define CNFCONVERTER_H

#include "Cnf.h"
#include "BoolFunc.h"

class CnfConverter{
private:
    CnfConverter();
public:
    static Cnf silly(BoolFunc const & boolFunc){
        /**
         * 1 - Apply De Morgan
         * 2 - Apply distributive
         * The size of boolFunc grows!!
         **/
        Cnf cnf;
        return cnf;
    }

    //Other methods
    static Cnf tseitin(BoolFunc const & boolFunc){}
};

#endif // CNFCONVERTER_H
