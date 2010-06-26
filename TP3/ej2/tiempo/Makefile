CC=g++
CFLAGS= -g -w -o
OBJ = grafo.cpp
.PHONY: all clean

all: clean ej2

ej2: main.cpp $(OBJ)
	$(CC) $(CFLAGS) $@ $^
	
clean:
	rm -f ej2
