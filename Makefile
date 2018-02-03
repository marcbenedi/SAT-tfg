DIR = .

NAME = main
CFILES = $(NAME).cpp
OBJFILES = $(NAME).o

#MY headers
MY_FOLDER = $(DIR)/include/
MY_H = BoolFunc.h VarsManager.h Clause.h Cnf.h CnfConverter.h BDDConverter.h SatSolver.h MixCNFConverter.h
MY = $(foreach MY_H,$(MY_H),$(MY_FOLDER)$(MY_H))
MY_FLAGS = -I$(MY_FOLDER)
#CUDD
CUDD = $(DIR)/cudd-3.0.0
#HFILES2 = $(CUDD)/cudd/cudd.h
CUDD_FLAGS = -I$(CUDD)/cudd -I$(CUDD)/cplusplus -I$(CUDD)/util -I$(CUDD) -L$(CUDD)/cudd/.libs #-L$(CUDD)/cplusplus/.libs  -L$(CUDD)/util -L$(CUDD)/mtr/.libs -L$(CUDD)/st/.libs

LIBS = -lcudd #-lobj -lutil -lmtr -lst #-lepd

#SRCFILES = $(CFILES) $(MY) $(HFILES2)
CFLAGS = $(DEBUG) $(MY_FLAGS) $(CUDD_FLAGS)

DEBUG = -g
CC = g++

main: $(OBJFILES)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJFILES) -static $(LIBS)

main.o: $(CFILES) $(MY)
	$(CC) -c -std=c++0x $(CFLAGS) $(CFILES)

my: $(MY)
	$(CC) -c -std=c++0x $(CFLAGS) $(MY)

clean:
	rm -f $(OBJFILES)

ultraclean:
	rm -f *.o *.gch $(NAME)
	rm -f $(MY_FOLDER)*.gch $(MY_FOLDER)*.o

valgrind:
	 valgrind --leak-check=yes ./$(NAME)
