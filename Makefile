VERSION =
FLAGS = -std=c++0x -o
DEBUG = -g
EXE_NAME = main

make: main.cpp BoolFunc$(VERSION).h
	g++ $(DEBUG) $(FLAGS) $(EXE_NAME) main.cpp

clean:
	rm -f *.o *.gch main

valgrind:
	 valgrind --leak-check=yes ./$(EXE_NAME)
