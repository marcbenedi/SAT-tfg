DIR = .

NAME = main
CFILES = $(NAME).cpp
OBJFILES = $(NAME).o

#BDD headers
BDD_FOLDER = $(DIR)/include/
BDD_H = BoolFunc.h VarsManager.h Clause.h Cnf.h CnfConverter.h
BDD = $(foreach BDD_H,$(BDD_H),$(BDD_FOLDER)$(BDD_H))
BDD_FLAGS = -I$(BDD_FOLDER)
#CUDD
CUDD = $(DIR)/cudd-3.0.0
#HFILES2 = $(CUDD)/cudd/cudd.h
CUDD_FLAGS = -I$(CUDD)/cudd -I$(CUDD)/cplusplus -I$(CUDD)/util -I$(CUDD) -L$(CUDD)/cudd/.libs #-L$(CUDD)/cplusplus/.libs  -L$(CUDD)/util -L$(CUDD)/mtr/.libs -L$(CUDD)/st/.libs

LIBS = -lcudd #-lobj -lutil -lmtr -lst #-lepd

#SRCFILES = $(CFILES) $(BDD) $(HFILES2)
CFLAGS = $(DEBUG) $(BDD_FLAGS) $(CUDD_FLAGS)

DEBUG = -g
CC = g++

main: $(OBJFILES)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJFILES) -static $(LIBS)

main.o: $(CFILES) $(BDD)
	$(CC) -c -std=c++0x $(CFLAGS) $(CFILES)

bdd: $(BDD)
	$(CC) -c -std=c++0x $(CFLAGS) $(BDD)

clean:
	rm -f $(OBJFILES)

ultraclean:
	rm -f *.o *.gch $(NAME)
	rm -f $(BDD_FOLDER)*.gch $(BDD_FOLDER)*.o

valgrind:
	 valgrind --leak-check=yes ./$(NAME)
