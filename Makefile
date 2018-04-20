DIR = .

MAIN = main

CC = g++

#TFG
TFG_FOLDER = $(DIR)/source_files/
TFG_BUILD = $(DIR)/source_build/
TFG_INCLUDE = -I$(TFG_FOLDER)
TFG_LIBS = -ltfg
#CUDD
CUDD = $(DIR)/cudd-3.0.0
CUDD_INCLUDE = -I$(CUDD)/cudd -I$(CUDD)/cplusplus -I$(CUDD)/util -I$(CUDD)
CUDD_LIBS_INCLUDE = -L$(CUDD)/cudd/.libs
#-L$(CUDD)/cplusplus/.libs  -L$(CUDD)/util -L$(CUDD)/mtr/.libs -L$(CUDD)/st/.libs
CUDD_LIBS = -lcudd
#-lobj -lutil -lmtr -lst #-lepd
#  TEST
GT_FOLDER = $(DIR)/googletest/googletest
GT_INCLUDE = -I$(GT_FOLDER)/include
GT_LIB_INCLUDE = -L$(GT_FOLDER)/make
GT_LIBS = -lgtest_main
#TESTING
TEST_FOLDER = $(DIR)/test_files/
TEST_BUILD = $(DIR)/test_build/
#PBLIB
PBLIB = $(DIR)/pblib
PBLIB_INCLUDE = -I$(PBLIB)/lib
PBLIB_LIBS_INCLUDE = -L$(PBLIB)/lib
PBLIB_LIBS = -lpblib

compile_main:
	$(CC) -c -std=c++0x -g -fpermissive   $(MAIN).cpp $(TFG_INCLUDE) $(CUDD_INCLUDE) $(PBLIB_INCLUDE)

link_main:
	$(CC) -o $(MAIN) $(MAIN).o -L$(TFG_BUILD) $(TFG_LIBS) $(CUDD_LIBS_INCLUDE) $(PBLIB_LIBS_INCLUDE)  -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -static $(CUDD_LIBS) $(PBLIB_LIBS)

main:
	make compile_main link_main
	./main

compile_tfg:
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)Clause.cpp -o $(TFG_BUILD)Clause.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)Cnf.cpp -o $(TFG_BUILD)Cnf.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)VarsManager.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)VarsManager.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)BoolFunc.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)BoolFunc.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)CnfConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)CnfConverter.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)BDDConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)BDDConverter.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)MixCNFConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)MixCNFConverter.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)SatSolver.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)SatSolver.o
    #
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)PBMin.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)PBMin.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)PBConstraint.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)PBConstraint.o
	# $(CC) -c -std=c++0x -g $(TFG_FOLDER)PBFormula.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)PBFormula.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)Solver.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)Solver.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)SearchStrategy.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)SearchStrategy.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)BinarySearchStrategy.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)BinarySearchStrategy.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)LinearSearchStrategy.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)LinearSearchStrategy.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)SimpleTimeoutSolver.cpp $(PBLIB_INCLUDE) -o $(TFG_BUILD)SimpleTimeoutSolver.o

lib_tfg:
	ar rcs $(TFG_BUILD)libtfg.a $(TFG_BUILD)*.o

tfg:
	make compile_tfg lib_tfg

clean:
	rm -f *.o *.gch $(MAIN)
	rm -f $(TFG_BUILD)*.gch $(TFG_BUILD)*.o $(TFG_BUILD)*.a
	rm -f $(TEST_BUILD)*.gch $(TEST_BUILD)*.o $(TEST_BUILD)*.a
	rm -f output.txt
	rm -f input.txt

compile_tests:
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)Clause_UT.cpp -o $(TEST_BUILD)Clause_UT.o $(TFG_INCLUDE) $(GT_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)Cnf_UT.cpp -o $(TEST_BUILD)Cnf_UT.o $(TFG_INCLUDE) $(GT_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)VarsManager_UT.cpp -o $(TEST_BUILD)VarsManager_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)BoolFunc_UT.cpp -o $(TEST_BUILD)BoolFunc_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)CnfConverter_UT.cpp -o $(TEST_BUILD)CnfConverter_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)BDDConverter_UT.cpp -o $(TEST_BUILD)BDDConverter_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)MixCNFConverter_UT.cpp -o $(TEST_BUILD)MixCNFConverter_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)SatSolver_UT.cpp -o $(TEST_BUILD)SatSolver_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)
    #
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)PBFormula_UT.cpp -o $(TEST_BUILD)PBFormula_UT.o $(TFG_INCLUDE) $(GT_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)PBConstraint_UT.cpp -o $(TEST_BUILD)PBConstraint_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)PBMin_UT.cpp -o $(TEST_BUILD)PBMin_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)Solver_UT.cpp -o $(TEST_BUILD)Solver_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)SearchStrategy_Stub.cpp -o $(TEST_BUILD)SearchStrategy_Stub.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)BinarySearchStrategy_UT.cpp -o $(TEST_BUILD)BinarySearchStrategy_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)Solver_BinarySearchStrategy_INT.cpp -o $(TEST_BUILD)Solver_BinarySearchStrategy_INT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	# $(CC) -c -std=c++0x -g $(TEST_FOLDER)Solver_LinearSearchStrategy_INT.cpp -o $(TEST_BUILD)Solver_LinearSearchStrategy_INT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)
	$(CC) -c -std=c++0x -g $(TEST_FOLDER)SimpleTimeoutSolver_LinearSearchStrategy_INT.cpp -o $(TEST_BUILD)SimpleTimeoutSolver_LinearSearchStrategy_INT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(PBLIB_INCLUDE)

link_tests:
	# $(CC) -o $(TEST_BUILD)Clause_UT $(TEST_BUILD)Clause_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread
	# $(CC) -o $(TEST_BUILD)Cnf_UT $(TEST_BUILD)Cnf_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread
	# $(CC) -o $(TEST_BUILD)VarsManager_UT $(TEST_BUILD)VarsManager_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
	# $(CC) -o $(TEST_BUILD)BoolFunc_UT $(TEST_BUILD)BoolFunc_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
	# $(CC) -o $(TEST_BUILD)CnfConverter_UT $(TEST_BUILD)CnfConverter_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
	# $(CC) -o $(TEST_BUILD)BDDConverter_UT $(TEST_BUILD)BDDConverter_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
	# $(CC) -o $(TEST_BUILD)MixCNFConverter_UT $(TEST_BUILD)MixCNFConverter_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
	# $(CC) -o $(TEST_BUILD)SatSolver_UT $(TEST_BUILD)SatSolver_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a
    #
	# $(CC) -o $(TEST_BUILD)PBFormula_UT $(TEST_BUILD)PBFormula_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread
	# $(CC) -o $(TEST_BUILD)PBConstraint_UT $(TEST_BUILD)PBConstraint_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	# $(CC) -o $(TEST_BUILD)PBMin_UT $(TEST_BUILD)PBMin_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	# $(CC) -o $(TEST_BUILD)Solver_UT $(TEST_BUILD)Solver_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	# $(CC) -o $(TEST_BUILD)SearchStrategy_Stub $(TEST_BUILD)SearchStrategy_Stub.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread
	# $(CC) -o $(TEST_BUILD)BinarySearchStrategy_UT $(TEST_BUILD)BinarySearchStrategy_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	# $(CC) -o $(TEST_BUILD)Solver_BinarySearchStrategy_INT $(TEST_BUILD)Solver_BinarySearchStrategy_INT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	# $(CC) -o $(TEST_BUILD)Solver_LinearSearchStrategy_INT $(TEST_BUILD)Solver_LinearSearchStrategy_INT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)
	$(CC) -o $(TEST_BUILD)SimpleTimeoutSolver_LinearSearchStrategy_INT $(TEST_BUILD)SimpleTimeoutSolver_LinearSearchStrategy_INT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread $(PBLIB_LIBS_INCLUDE) $(PBLIB_LIBS)

tests:
	make compile_tests link_tests
	# ./test_build/Clause_UT
	# ./test_build/Cnf_UT
	# ./test_build/VarsManager_UT
	# ./test_build/BoolFunc_UT
	# ./test_build/CnfConverter_UT
	# ./test_build/BDDConverter_UT
	# ./test_build/MixCNFConverter_UT
	# ./test_build/SatSolver_UT
    #
	# ./test_build/PBFormula_UT
	# ./test_build/PBConstraint_UT
	# ./test_build/PBMin_UT
	# ./test_build/Solver_UT
	# ./test_build/BinarySearchStrategy_UT
	# ./test_build/Solver_BinarySearchStrategy_INT
	# ./test_build/Solver_LinearSearchStrategy_INT
	./test_build/SimpleTimeoutSolver_LinearSearchStrategy_INT
