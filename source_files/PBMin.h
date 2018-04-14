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


enum SEARCH_TYPE {
    BINARY_SEARCH,
    LINEAR_SEARCH
};

class PBMin{
private:
    std::vector<PBConstraint> constraints;
    PBFormula costFunction;
    SEARCH_TYPE searchType;
    bool minisat(std::vector< int32_t > & model, const std::vector< std::vector< int32_t > > & cnf);
    bool binarySearch(std::vector< int32_t > & model, int64_t & min);
    bool linearSearch(std::vector< int32_t > & model, int64_t & min);
public:
    PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction, SEARCH_TYPE search = BINARY_SEARCH);
    std::vector<PBConstraint> getConstraints();
    PBFormula getCostFunction();
    SEARCH_TYPE getSearchType();
    int32_t getFirstFreshVariable();
    bool solve(std::vector< int32_t > & model, int64_t & min);
    int64_t getCostFunctionMax();
    int64_t getCostFunctionMin();
};

#endif // PBMIN_H
