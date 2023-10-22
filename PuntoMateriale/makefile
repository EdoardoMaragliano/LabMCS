ROOT_CFLAGS  = `root-config --cflags`
ROOT_LIBFLAGS = `root-config --libs`
CVERSION = --std=c++11
compila: mainPM.x 

esegui: mainPM.x
	./mainPM.x

mainPM.x: mainPM.cpp Vettore.o Particella.o PuntoMateriale.o 
	g++ $(CVERSION) mainPM.cpp Vettore.o Particella.o PuntoMateriale.o -o mainPM.x 
	
Vettore.o: Vettore.cpp Vettore.h
	g++ $(CVERSION) -c Vettore.cpp 

Particella.o: Particella.cpp Particella.h   
	g++ $(CVERSION) -c Particella.cpp 

PuntoMateriale.o: PuntoMateriale.cpp PuntoMateriale.h 
	g++ $(CVERSION) -c PuntoMateriale.cpp 

cleanO:
	rm *.o
	
cleanAll:
	rm *.o *.x
