DIR = .

NAME = main
CFILES = $(NAME).cpp
OBJFILES = $(NAME).o

#My headers
HFILES1_FOLDER = $(DIR)/include/
#HFILES1_H = BoolFunc.h VarsManager.h Clause.h Cnf.h CnfConverter.h
#HFILES1 = $(foreach HFILES1_H,$(HFILES1_H),$(HFILES1_FOLDER)$(HFILES1_H))
MY_FLAGS = -I$(HFILES1_FOLDER)
#CUDD
CUDD = $(DIR)/cudd-3.0.0
#HFILES2 = $(CUDD)/cudd/cudd.h
CUDD_FLAGS = -I$(CUDD)/cudd -I$(CUDD)/cplusplus -I$(CUDD)/util -I$(CUDD) -L$(CUDD)/cplusplus/.libs -L$(CUDD)/cudd/.libs -L$(CUDD)/util -L$(CUDD)/mtr/.libs -L$(CUDD)/st/.libs

LIBS = -lcudd -lobj -lutil -lmtr -lst #-lepd

#SRCFILES = $(CFILES) $(HFILES1) $(HFILES2)
CFLAGS = $(DEBUG) $(MY_FLAGS) $(CUDD_FLAGS)

DEBUG = -g
CC = g++

mycudd: $(OBJFILES)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJFILES) $(LIBS)

main.o: $(CFILES)
	$(CC) -c -std=c++0x $(CFLAGS) $(CFILES)

clean:
	rm -f $(OBJFILES)

ultraclean:
	rm -f *.o *.gch $(NAME)

valgrind:
	 valgrind --leak-check=yes ./$(NAME)
