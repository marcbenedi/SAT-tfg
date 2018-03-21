DIR = .

MAIN = main

CC = g++

#TFG
TFG_FOLDER = $(DIR)/include/
TFG_INCLUDE = -I$(TFG_FOLDER)
TFG_H = BoolFunc.o VarsManager.o Clause.o Cnf.o CnfConverter.o BDDConverter.o SatSolver.o MixCNFConverter.o
TFG_HS = $(foreach TFG_H,$(TFG_H),$(TFG_FOLDER)$(TFG_H))
#CUDD
CUDD = $(DIR)/cudd-3.0.0
CUDD_INCLUDE = -I$(CUDD)/cudd -I$(CUDD)/cplusplus -I$(CUDD)/util -I$(CUDD)
CUDD_LIBS_INCLUDE = -L$(CUDD)/cudd/.libs
#-L$(CUDD)/cplusplus/.libs  -L$(CUDD)/util -L$(CUDD)/mtr/.libs -L$(CUDD)/st/.libs
CUDD_LIBS = -lcudd
#-lobj -lutil -lmtr -lst #-lepd

compile_main:
	$(CC) -c -std=c++0x -g $(MAIN).cpp $(TFG_INCLUDE) $(CUDD_INCLUDE)

link_main:
	$(CC) -o $(MAIN) $(MAIN).o -L$(TFG_FOLDER) -ltfg $(CUDD_LIBS_INCLUDE) -static $(CUDD_LIBS)

compile_tfg:
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)Clause.cpp -o $(TFG_FOLDER)Clause.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)Cnf.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)Cnf.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)VarsManager.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)VarsManager.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)BoolFunc.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)BoolFunc.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)CnfConverter.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)CnfConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)BDDConverter.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)BDDConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)MixCNFConverter.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)MixCNFConverter.o
	$(CC) -c -std=c++0x -g $(TFG_FOLDER)SatSolver.cpp $(CUDD_INCLUDE) -o $(TFG_FOLDER)SatSolver.o

lib_tfg:
	ar rcs $(TFG_FOLDER)libtfg.a $(TFG_HS)

clean:
	rm -f *.o *.gch $(MAIN)
	rm -f $(TFG_FOLDER)*.gch $(TFG_FOLDER)*.o
