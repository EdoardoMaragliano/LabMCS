CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags` 
LIBSROOT   = `root-config --glibs`

Millikan: Esame21-01-19.cpp 
	$(CC) $(CFLAGS) -o Esame.x Esame21-01-19.cpp $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o 
