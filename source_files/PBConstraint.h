#ifndef PBCONTRAINT_h
#define PBCONTRAINT_h

#include "PBFormula.h"
#include <string>
#include "pb2cnf.h"

class PBConstraint{
private:
    PBFormula formula;
    int64_t k;
public:
    PBConstraint(const PBFormula & formula, int64_t k);
    PBFormula getPBFormula();
    int64_t getK();
    void encode(std::vector< std::vector< int32_t > > & cnf, int32_t & firstFreshVariable);
    void setK(int64_t p_k);

};

#endif // PBCONTRAINT_h
