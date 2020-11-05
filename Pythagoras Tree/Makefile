CC = g++
CFLAGS = -O2 -c -g -Og -Wall -Werror -ansi -pedantic
OBJ = main.o pTree.o
DEPS = pTree.hpp
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = Tree

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
