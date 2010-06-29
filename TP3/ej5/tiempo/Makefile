CC=g++
CFLAGS= -g -w -o
OBJ = ../grafo.cpp

.PHONY: all clean

all: clean tiempo

tiempo: tiempo.cpp $(OBJ)
	$(CC) $(CFLAGS) $@ $^
	
clean:
	rm -f tiempo
