CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags` -lMinuit
LIBSROOT   = `root-config --glibs`

compila: minuit.cpp 
	$(CC) $(CFLAGS) -o minuit.x minuit.cpp $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o 
