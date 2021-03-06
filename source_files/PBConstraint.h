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
    /**
     * Constructs a pseudo-boolean constraint of the type formula <= k
     *@param formula
     *@param k
     */
    PBConstraint(const PBFormula & formula, int64_t k);

    PBFormula getPBFormula() const;

    int64_t getK();
    /**
     * Encodes the PBConstraint to a cnf
     *@param cnf : where the encoding will be stored
     *@param firstFreshVariable : needed for PBLib, has to be greater than the last id used
     */
    void encode(std::vector< std::vector< int32_t > > & cnf, int32_t & firstFreshVariable);

    void setK(int64_t p_k);

};

#endif // PBCONTRAINT_h
