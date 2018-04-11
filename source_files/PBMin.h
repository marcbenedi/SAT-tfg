#ifndef PBMIN_H
#define PBMIN_H

#include "PBConstraint.h"
#include <set>
#include "pb2cnf.h"
#include <map>

enum SEARCH_TYPE {
    BINARY_SEARCH,
    LINEAR_SEARCH
};

class PBMin{
private:
    std::vector<PBConstraint> constraints;
    PBFormula costFunction;
    SEARCH_TYPE searchType;
public:
    PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction, SEARCH_TYPE search = BINARY_SEARCH);
    std::vector<PBConstraint> getConstraints();
    PBFormula getCostFunction();
    SEARCH_TYPE getSearchType();
    int32_t getFirstFreshVariable();
    void solve();
    int64_t getCostFunctionMax();
    int64_t getCostFunctionMin();
};

#endif // PBMIN_H
