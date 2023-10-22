ROOT_CFLAGS  = `root-config --cflags`
ROOT_LIBFLAGS = `root-config --libs`

compila: main.x 

esegui: main.x
	./main.x

main.x: main.o Vettore.o
	g++ -std=c++17 main.o Vettore.o -o main.x 

main.o: main.cpp
	g++ -std=c++17 -c main.cpp 
	
Vettore.o: Vettore.cpp Vettore.h
	g++ -std=c++17 -c Vettore.cpp 
	
clean:
	rm *.o
	
delete:
	rm *.o *.x
