#ifndef LINEAR_SEARCH_STRATEGY_H
#define LINEAR_SEARCH_STRATEGY_H

#include <vector>
#include <stdint.h>
#include "SearchStrategy.h"
#include "weightedlit.h"
#include "incpbconstraint.h"

class LinearSearchStrategy: public SearchStrategy {
private:
    std::vector< std::vector< int32_t > > cnf_constraints;
    int32_t firstFreshVariable;
public:
    LinearSearchStrategy();
    /**
     * Initializes the algorithm, must be called before loop and end
     * @param problem is a defined PBMin which defines the problem to be solved
     */
    void init(const PBMin & p) override;

    /**
     * This function executes the linear search algorithm.
     * Must be executed between init() and end()
     *
     * @param solve : function which takes 3 arguments (model, cnf, sat) and solves the given cnf storing the assignment in model and storing in sat its satisfiability
     * @param model : a structure where model will be stored
     * @param min : a int64_t where the minimum value for the cost function will be stored
     * @param sat : a boolean where the satisfiability of the problem will be stored
     * @param solver : the solver used to solve this problem
     * @param problem : the problem to be solved
     */
    void loop(void (Solver::*solve)(std::vector< int32_t > &, const std::vector< std::vector< int32_t > > &, bool &),std::vector< int32_t > & model, int64_t & min, bool &sat, Solver *solver, const PBMin & problem)override;

    /**
     * Finishes the execution of this class, in this implementation it does nothing
     * Must be called after loop()
     */
    void end() override;
};

#endif // LINEAR_SEARCH_STRATEGY_H
