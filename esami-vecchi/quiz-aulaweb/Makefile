CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`


classe.o: classe.cpp
	$(CC) $(CFLAGS) -c classe.cpp      $(CFLAGSROOT)
Main.x: Es1.cpp classe.o 
	$(CC) $(CFLAGS) -o Es1.x Es1.cpp classe.o $(CFLAGSROOT) $(LIBSROOT)
 

clean:
	rm *.o 