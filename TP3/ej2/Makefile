CC=g++
CFLAGS= -g -w -o
OBJ = grafo.o
.PHONY: all clean

all: clean ej2

ej2: main.cpp $(OBJ)
	$(CC) $(CFLAGS) $@ $^
	rm -f *.o	
	
clean:
	rm -f ej2
