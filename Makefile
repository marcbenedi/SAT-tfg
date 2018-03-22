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

compile_main:
	$(CC) -c -std=c++0x -g $(MAIN).cpp $(TFG_INCLUDE) $(CUDD_INCLUDE)

link_main:
	$(CC) -o $(MAIN) $(MAIN).o -L$(TFG_BUILD) $(TFG_LIBS) $(CUDD_LIBS_INCLUDE) -static $(CUDD_LIBS)

main:
	make compile_main link_main

compile_tfg:
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)Clause.cpp -o $(TFG_BUILD)Clause.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)Cnf.cpp -o $(TFG_BUILD)Cnf.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)VarsManager.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)VarsManager.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)BoolFunc.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)BoolFunc.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)CnfConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)CnfConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)BDDConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)BDDConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)MixCNFConverter.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)MixCNFConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)SatSolver.cpp $(CUDD_INCLUDE) -o $(TFG_BUILD)SatSolver.o

lib_tfg:
	ar rcs $(TFG_BUILD)libtfg.a $(TFG_BUILD)*.o

tfg:
	make compile_tfg lib_tfg

clean:
	rm -f *.o *.gch $(MAIN)
	rm -f $(TFG_BUILD)*.gch $(TFG_BUILD)*.o $(TFG_BUILD)*.a
	rm -f $(TEST_BUILD)*.gch $(TEST_BUILD)*.o $(TEST_BUILD)*.a

compile_tests:
	$(CC) -c -std=c++0x -g $(TEST_FOLDER)Clause_UT.cpp -o $(TEST_BUILD)Clause_UT.o $(TFG_INCLUDE) $(GT_INCLUDE)
	$(CC) -c -std=c++0x -g $(TEST_FOLDER)Cnf_UT.cpp -o $(TEST_BUILD)Cnf_UT.o $(TFG_INCLUDE) $(GT_INCLUDE) $(CUDD_INCLUDE)

link_tests:
	$(CC) -o $(TEST_BUILD)Clause_UT $(TEST_BUILD)Clause_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread
	$(CC) -o $(TEST_BUILD)Cnf_UT $(TEST_BUILD)Cnf_UT.o -L$(TFG_BUILD) $(TFG_LIBS) $(GT_LIB_INCLUDE) $(GT_LIBS) -lpthread  $(CUDD)/cudd/.libs/libcudd.a

tests:
	make compile_tests link_tests
	./test_build/Clause_UT
	./test_build/Cnf_UT
