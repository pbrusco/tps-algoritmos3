GXX = g++
GXXFLAGS = -g -w -o

.PHONY=clean all

generador: generador.cpp
	$(GXX) $(GXXFLAGS) $@ $<

all: clean generador

clean:
	rm generador

