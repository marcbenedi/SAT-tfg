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
    Cnf getResult();
    void clear();
    void convert(Formula const & f);
    void setValueCover(int i);
    bool worthToConvert(BDD const & f);
};

#endif // MIXCNFCONVERTER_H
