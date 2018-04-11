#include "PBMin.h"

PBMin::PBMin(std::vector<PBConstraint> p_constraints, PBFormula p_costFunction):constraints(p_constraints),costFunction(p_costFunction)
{

}

std::vector<PBConstraint> PBMin::getConstraints(){
    return constraints;
}

PBFormula PBMin::getCostFunction(){
    return costFunction;
}
