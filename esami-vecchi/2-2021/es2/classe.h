/*si implementi una classe derivata di TH1D in grado di riempire un istogramma a partire da un file di 
dati con un metodo specifico(ad esempio ReadFile(const char*). Il metodo deve anche occuparsi di salvare
le informazioni necessarie per calcolare media e varianza "unbinned"; queste quantità dovranno essere
poi ritornate dai metodi double GetUnbinnedMean() e double GetUnbinnedRMS().
Costruire anche un programma principale che testi il funzionamento della classe*/

#ifndef _CLASSEESAME
#define _CLASSEESAME

#include <TH1D.h>

using namespace std;
#include <fstream>
#include <iostream>

class Istogramma: public TH1D {
public:
	using TH1D::TH1D;
	Istogramma():TH1D("histo","histo",200,0,50),m_mean(0),m_RMS(0){};
	void ReadFile(const char*);
	double GetUnbinnedMean();
	double GetUnbinnedRMS();

private:
	double m_mean;
	double m_RMS;
	//TH1D m_histo;


}
;







#endif