#include "gtest/gtest.h"

#include "Solver.h"
#include "SearchStrategy_Stub.cpp"

namespace {

    TEST(Constructors,definedConstructor){
        SearchStrategy_Stub stub;
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1,2},{1,2}),1)
        };
        PBMin m = PBMin(e_constraints, PBFormula({3,-5},{-1,2}));

        Solver solver(&stub,m);
    }

    TEST(Solver,solver1){
        SearchStrategy_Stub stub;
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({1},{1}),1)
        };
        PBFormula costFunction({1},{1});
        PBMin m = PBMin(e_constraints, costFunction);
        bool e_sat = true;
        std::vector< int32_t > e_model = {};

        int32_t firstFreshVariable = m.getFirstFreshVariable();
        std::vector< std::vector< int32_t > > cnf;

        PB2CNF pb2cnf;

        //Encoding constraints
        for (size_t i = 0; i < m.getConstraints().size(); i++) {
            firstFreshVariable = pb2cnf.encodeLeq(m.getConstraints()[i].getPBFormula().getWeights(), m.getConstraints()[i].getPBFormula().getLiterals(), m.getConstraints()[i].getK(), cnf, firstFreshVariable) + 1;
        }

        firstFreshVariable = pb2cnf.encodeLeq(m.getCostFunction().getWeights(), m.getCostFunction().getLiterals(), 1, cnf, firstFreshVariable) + 1;

        Solver solver(&stub,m);

        std::vector< int32_t > model;
        bool sat;
        solver.solver(model,cnf,sat);

        EXPECT_EQ(model.size(), 1);
        EXPECT_EQ(sat, e_sat);
    }

    TEST(Solver,solver2){
        SearchStrategy_Stub stub;
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({2,2},{1,-1}),1),
            PBConstraint(PBFormula({3,4},{2,3}),1),
            PBConstraint(PBFormula({3,7},{1,3}),1)
        };
        PBFormula costFunction({-1,-3,7,-5},{1,-1,2,-2});
        bool e_sat = false;
        std::vector< int32_t > e_model = {};

        PBMin m = PBMin(e_constraints, costFunction);
        int32_t firstFreshVariable = m.getFirstFreshVariable();
        std::vector< std::vector< int32_t > > cnf;

        //Encoding constraints
        PB2CNF pb2cnf;
        for (size_t i = 0; i < m.getConstraints().size(); i++) {
            firstFreshVariable = pb2cnf.encodeLeq(m.getConstraints()[i].getPBFormula().getWeights(), m.getConstraints()[i].getPBFormula().getLiterals(), m.getConstraints()[i].getK(), cnf, firstFreshVariable) + 1;
        }
        firstFreshVariable = pb2cnf.encodeLeq(m.getCostFunction().getWeights(), m.getCostFunction().getLiterals(), 1, cnf, firstFreshVariable) + 1;

        Solver solver(&stub,m);

        std::vector< int32_t > model;
        bool sat;
        solver.solver(model,cnf,sat);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
    }

    TEST(Solver,solver3){
        SearchStrategy_Stub stub;
        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});
        bool e_sat = true;
        std::vector< int32_t > e_model = {-1,2,0};

        PBMin m = PBMin(e_constraints, costFunction);
        int32_t firstFreshVariable = m.getFirstFreshVariable();
        std::vector< std::vector< int32_t > > cnf;

        //Encoding constraints
        PB2CNF pb2cnf;
        for (size_t i = 0; i < m.getConstraints().size(); i++) {
            firstFreshVariable = pb2cnf.encodeLeq(m.getConstraints()[i].getPBFormula().getWeights(), m.getConstraints()[i].getPBFormula().getLiterals(), m.getConstraints()[i].getK(), cnf, firstFreshVariable) + 1;
        }
        firstFreshVariable = pb2cnf.encodeLeq(m.getCostFunction().getWeights(), m.getCostFunction().getLiterals(), 7, cnf, firstFreshVariable) + 1;

        Solver solver(&stub,m);

        std::vector< int32_t > model;
        bool sat;
        solver.solver(model,cnf,sat);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
    }

    TEST(Run,run){

        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});
        bool e_sat = true;
        std::vector< int32_t > e_model = {1,2,3};
        int64_t e_min = 123;

        SearchStrategy_Stub stub;
        PBMin m = PBMin(e_constraints, costFunction);
        Solver solver(&stub,m);

        std::vector< int32_t > model;
        int64_t min;
        bool sat = solver.run(model,min);

        for (size_t i = 0; i < e_model.size(); i++) {
            EXPECT_EQ(model[i], e_model[i]);
        }
        EXPECT_EQ(sat, e_sat);
        EXPECT_EQ(min, e_min);
    }

    TEST(HasTimeoutOccurred,hasTimeoutOccurred){

        std::vector< PBConstraint > e_constraints = {
            PBConstraint(PBFormula({4},{1}),3),
            PBConstraint(PBFormula({4},{-2}),3),
        };
        PBFormula costFunction({-7,-3,10},{1,-1,2});

        SearchStrategy_Stub stub;
        PBMin m = PBMin(e_constraints, costFunction);
        Solver solver(&stub,m);

        std::vector< int32_t > model;
        int64_t min;
        EXPECT_EQ(solver.hasTimeoutOccurred(), false);
        bool sat = solver.run(model,min);
        EXPECT_EQ(solver.hasTimeoutOccurred(), false);
    }



}
