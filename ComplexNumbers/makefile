ROOT_CFLAGS  = `root-config --cflags`
ROOT_LIBFLAGS = `root-config --libs`
CVERS = --std=c++11

compila: main.x 

esegui: main.x
	./main.x

main.x: main.cpp Complesso.o
	g++ $(CVERS) main.cpp Complesso.o -o main.x $(ROOT_CFLAGS) $(ROOT_LIBFLAGS)

Complesso.o: Complesso.cpp Complesso.h
	g++ $(CVERS) -c Complesso.cpp $(ROOT_CFLAGS) $(ROOT_LIBFLAGS)

clean:
	rm *.o
	
delete:
	rm *.o *.x
