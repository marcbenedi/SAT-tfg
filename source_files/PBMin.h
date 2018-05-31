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
    /**
     *Constructs a pseudo-boolean minimization problem with
     *@param p_constraints
     *@param p_costFunction
     */
    PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction);

    std::vector<PBConstraint> getConstraints() const;

    PBFormula getCostFunction() const;

    /**
     *@return the biggest literal+1
     */
    int32_t getFirstFreshVariable() const;

    /**
     *@return the maximum possible value of the cost function
     */
    int64_t getCostFunctionMax() const;

    /**
     *@return the minimum possible value of the cost function
     */
    int64_t getCostFunctionMin() const;
};

#endif // PBMIN_H
