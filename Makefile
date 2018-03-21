DIR = .

MAIN = main

CC = g++

#TFG
TFG_FOLDER = $(DIR)/include/
TFG_INCLUDE = -I$(TFG_FOLDER)
TFG_H = BoolFunc.h VarsManager.h Clause.h Cnf.h CnfConverter.h BDDConverter.h SatSolver.h MixCNFConverter.h
TFG_SOURCES = $(foreach TFG_H,$(TFG_H),$(TFG_FOLDER)$(TFG_H))
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
	$(CC) -o $(MAIN) $(MAIN).o $(CUDD_LIBS_INCLUDE) -static $(CUDD_LIBS)

compile_tfg:
	$(CC) -c -std=c++0x -g $(TFG_SOURCES) $(CUDD_INCLUDE)

link_tfg:
	todo

clean:
	rm -f *.o *.gch $(MAIN)
	rm -f $(TFG_FOLDER)*.gch $(TFG_FOLDER)*.o
