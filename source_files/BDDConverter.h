#ifndef BDDCONVERTER_H
#define BDDCONVERTER_H

#include "BoolFunc.h"
#include "VarsManager.h"

class BDDConverter{
private:
    BDDConverter();
    static BDD convertFormulaRec(Formula const & boolFunc);

public:
    /**
     * Converts the given formula to a BDD
     * @param boolean formula to be converted
     * @return the boolean formula converted to a BDD
     */
    static BDD convertFormula(Formula const & boolFunc);
};

#endif // BDDCONVERTER_H
