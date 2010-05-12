CC=g++
GCCFLAGS= -g -w -o
.PHONY=clean all

all: ejercicio_2

ejercicio_2: ./sources/ej2.cpp
	$(CC) $(GCCFLAGS) $@ $<


run:
	python ej2.py

clean:
	rm tests/*
	rm *-bis.out *_grafico.out ejercicio_2



