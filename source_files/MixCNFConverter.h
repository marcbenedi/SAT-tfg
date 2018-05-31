#ifndef MIXCNFCONVERTER_H
#define MIXCNFCONVERTER_H

#include "BDDConverter.h"
#include "CnfConverter.h"
#include "VarsManager.h"
#include "BoolFunc.h"

#include "util.h"
#include "cudd.h"
#include "cuddObj.hh"

#include <map>
#include <assert.h>

#include <stdlib.h>

//TODO: ALLIBREAMENT DE MEMORIA
class MixCNFConverter{
private:
    int minValueCover = 0;
    std::map<Formula,Cnf> nodeToCnf;
    std::map<Formula,BDD> nodeToBDD;
    Cnf result;
    void baseCase(Formula const & f);
    Formula getBiggestChild(Formula const & f);
    Formula getSmallestChild(Formula const & f);
    void replaceChild(Formula const & f, Formula const & old_c, Formula const & new_c);
    void hardBDD(Formula const & f);
    void recursiveCase(Formula const & f);
    void convertRec(Formula const & f);

public:
    /**
     * Must be called after convert()
     * @return cnf resulting from converting the given boolean formula
     */
    Cnf getResult();

    /**
     * Clears the class internally
     */
    void clear();

    /**
     * Converts the given boolean formula to a CNF which can be get with getResult().
     * The method applies different methods depending on the formula characteristics.
     *@param f : Formula to be converted
     */
    void convert(Formula const & f);

    /**
     * If the number of minterms of the function is LEQ than i/10000 the function will be converted using a different method
     *@param i: between 0 and 10000
     */
    void setValueCover(int i);

    /**
     * 
     *@param bdd
     *@return true if the bdd's primes cover enough 1's
     */
    bool worthToConvert(BDD const & bdd);
};

#endif // MIXCNFCONVERTER_H
