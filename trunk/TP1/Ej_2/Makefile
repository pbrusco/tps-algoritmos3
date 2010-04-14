CPPCOMPILER = g++
CPPFLAGS = -c -g -w
OBJS = Ronda.o Chica.o

.PHONY = clean all

all: clean main


%.o : %.cpp
	$(CPPCOMPILER) $(CPPFLAGS) -o $@ $<
	

main: main.cpp $(OBJS)
	$(CPPCOMPILER) -g -o $@ $^
	
clean:
	rm -f *.o
	rm -f main
