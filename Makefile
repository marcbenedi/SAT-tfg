FLAGS = -std=c++0x -o
DEBUG = -g
EXE_NAME = main
HEADERS = BoolFunc.h VarsManager.h Clause.h Cnf.h

make: main.cpp $(HEADERS)
	g++ $(DEBUG) $(FLAGS) $(EXE_NAME) main.cpp
	make clean

clean:
	rm -f *.o *.gch

ultraclean:
	rm -f *.o *.gch main

valgrind:
	 valgrind --leak-check=yes ./$(EXE_NAME)
