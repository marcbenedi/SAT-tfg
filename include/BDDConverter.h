#ifndef BDDCONVERTER_H
#define BDDCONVERTER_H

#include "BoolFunc.h"
#include "VarsManager.h"

class BDDConverter{
private:
    BDDConverter();
    static BDD convertFormulaRec(Formula const & boolFunc);

public:
    static BDD convertFormula(Formula const & boolFunc);
};

#endif // BDDCONVERTER_H
