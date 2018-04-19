#ifndef PBMIN_H
#define PBMIN_H

#include "PBConstraint.h"
#include <set>
#include "pb2cnf.h"
#include <map>
#include <fstream>
#include "weightedlit.h"
#include "incpbconstraint.h"
#include <memory>

class PBMin{
private:
    std::vector<PBConstraint> constraints;
    PBFormula costFunction;
public:
    PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction);
    std::vector<PBConstraint> getConstraints();
    PBFormula getCostFunction();
    int32_t getFirstFreshVariable();
    int64_t getCostFunctionMax();
    int64_t getCostFunctionMin();
};

#endif // PBMIN_H
