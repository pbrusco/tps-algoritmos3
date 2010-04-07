CC=g++
GCCFLAGS= -g -o
.PHONY=clean all

all: ej1.out ej3.out

%.out: %.cpp
	$(CC) $(GCCFLAGS) $@ $<

clean:
	rm -f ./outputs/* 
	rm *.out
	



