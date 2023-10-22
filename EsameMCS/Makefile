CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`


poly.o: poly.cpp poly.h
	$(CC) $(CFLAGS) -c poly.cpp      $(CFLAGSROOT)
main.x: main.cpp poly.o 
	$(CC) $(CFLAGS) -o main.x main.cpp poly.o $(CFLAGSROOT) $(LIBSROOT)
 

clean:
	rm *.o 