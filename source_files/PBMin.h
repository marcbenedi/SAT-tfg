#ifndef PBMIN_H
#define PBMIN_H

#include "PBConstraint.h"
#include <set>

class PBMin{
private:
    std::vector<PBConstraint> constraints;
    PBFormula costFunction;
public:
    PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction);
    std::vector<PBConstraint> getConstraints();
    PBFormula getCostFunction();
};

#endif // PBMIN_H
