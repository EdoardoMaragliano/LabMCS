/*si implementi una classe derivata di TH1D in grado di riempire un istogramma a partire da un file di 
dati con un metodo specifico(ad esempio ReadFile(const char*). Il metodo deve anche occuparsi di salvare
le informazioni necessarie per calcolare media e varianza "unbinned"; queste quantità dovranno essere
poi ritornate dai metodi double GetUnbinnedMean() e double GetUnbinnedRMS().
Costruire anche un programma principale che testi il funzionamento della classe*/

#include "classe.h"
#include <TH1D.h>
#include <iostream>
#include <TApplication.h>

using namespace std;

int main(){
TApplication app(0,0,NULL);
Istogramma h;
h.ReadFile("expo_highstat.dat");
cout<< "mean="<< h.GetUnbinnedRMS() << "\t RMS=" << h.GetUnbinnedRMS() << endl;
h.Draw();
app.Run(true);


	return 0;
}