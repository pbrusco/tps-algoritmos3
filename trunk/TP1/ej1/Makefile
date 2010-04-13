CC=g++
GCCFLAGS= -g -w -o
.PHONY=clean all

all: ejercicio_1 input_gen1

ejercicio_1: ./sources/ej1.cpp
	$(CC) $(GCCFLAGS) $@ $<

input_gen1: ./sources/input_gen1.cpp
	$(CC) $(GCCFLAGS) $@ $<

clean:
	rm ejercicio_1
	rm input_gen1	
	rm *.out



