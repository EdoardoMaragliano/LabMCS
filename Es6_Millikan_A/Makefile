CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags` -lMinuit
LIBSROOT   = `root-config --glibs`

Millikan: Millikan.cpp 
	$(CC) $(CFLAGS) -o Millikan.x Millikan.cpp $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o Millikan MillikanPM
