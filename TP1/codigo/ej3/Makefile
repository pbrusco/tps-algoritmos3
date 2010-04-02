CPPCOMPILER = g++
CPPFLAGS = -c -g
OBJS = Hora.o ej3.o

.PHONY = clean all

all: clean main


%.o : %.cpp
	$(CPPCOMPILER) $(CPPFLAGS) -o $@ $<
	

main: main.cpp $(OBJS)
	$(CPPCOMPILER) -g -o $@ $^
	
clean:
	rm -f *.o
	rm -f main
