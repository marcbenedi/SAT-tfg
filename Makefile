FLAGS = -std=c++0x -o
DEBUG = -g
EXE_NAME = main
FOLDER = ./marc/
MY_HEADERS = BoolFunc.h VarsManager.h Clause.h Cnf.h CnfConverter.h
MY_HEADERS_IN_FOLDER = $(foreach MY_HEADERS,$(MY_HEADERS),$(FOLDER)$(MY_HEADERS))
LIBRARY = -I ./cudd/cplusplus -I ./cudd/cudd -L ./cudd/cudd/.libs/ -l cudd

make: main.cpp $(MY_HEADERS_IN_FOLDER)
	g++ $(DEBUG) $(FLAGS) $(EXE_NAME) main.cpp
	make clean

cudd: cudd_test.cpp
	g++ $(FLAGS) cudd_test cudd_test.cpp $(LIBRARY)
	make clean

clean:
	rm -f *.o *.gch

ultraclean:
	rm -f *.o *.gch main

valgrind:
	 valgrind --leak-check=yes ./$(EXE_NAME)
