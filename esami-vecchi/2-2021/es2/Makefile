CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`


classe.o: classe.cpp classe.h
	$(CC) $(CFLAGS) -c classe.cpp      $(CFLAGSROOT)
es2.x: es2.cpp classe.o 
	$(CC) $(CFLAGS) -o es2.x es2.cpp classe.o $(CFLAGSROOT) $(LIBSROOT)
 

clean:
	rm *.o 