GXX = g++
GXXFLAGS = -g -w -o

.PHONY=clean all

generador: generador.cpp
	$(GXX) $(GXXFLAGS) $@ $<
	
gennerador: gennerador.cpp
	$(GXX) $(GXXFLAGS) $@ $<

all: cleanGenerador cleanGennerador generador gennerador

cleanGenerador:
	rm generador
	
cleanGennerador:
	rm gennerador

