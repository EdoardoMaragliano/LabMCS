/*si implementi una classe derivata di TH1D in grado di riempire un istogramma a partire da un file di 
dati con un metodo specifico(ad esempio ReadFile(const char*). Il metodo deve anche occuparsi di salvare
le informazioni necessarie per calcolare media e varianza "unbinned"; queste quantità dovranno essere
poi ritornate dai metodi double GetUnbinnedMean() e double GetUnbinnedRMS().
Costruire anche un programma principale che testi il funzionamento della classe*/

#include "classe.h"
#include <fstream>
#include <iostream>

using namespace std;

void Istogramma::ReadFile(const char* nomefile){

double appo;
ifstream filein(nomefile);
vector <double> dati;
while(filein>>appo){
	dati.push_back(appo);
	this->Fill(appo);
}
double sum=0;
double sum2=0;
for(int i=0;i<dati.size();i++){
	sum+=dati[i];
	sum2+=dati[i]*dati[i];
}
cout << "data loaded="<<dati.size()<<endl;
m_mean=sum/dati.size();
m_RMS=sqrt(sum2/dati.size()-m_mean*m_mean);
}

double Istogramma::GetUnbinnedMean(){
	return m_mean;
}
double Istogramma::GetUnbinnedRMS(){
	return m_RMS;
}
