
//nel .h

#ifndef _MYTF1
#define _MYTF1

#include "TF1.h"
class myTF1 : public TF1{
    public:
    using TF1::TF1;
    double Integrale (double a, double b, int n);
    double Integrale (double a, double b, double eps);
};

#endif

//nel .cpp
#include "myTF1.h"
double myTF1::Integrale (double a, double b, int n){
    double w=(b-a)/n;
    double integ=w*Eval(a)/2+w*Eval(b)/2; //eval metodo di TF1
    for(int i=1;i<=n-1;i++)
        integ+=w*Eval(a+i*w);
    return integ;
}
double myTF1::Integrale (double a, double b, double eps){
    int n=2;
    double integ=-;
    double integ_old=-999;
    do {
        integ_old=integ;
        integ=Integrale(a,b,n);
        n*=2;
    } while (abs(integ_old-integ)>eps);
    return integ;
}
//nel main
#include "myTF1.h"
#include <iostream>

using namespace std;

int main(){
    myTF1 f("f","x^2",0,10);
    cout << f.Integrale(0,1) << endl;
    return 0;
}

/*
 Affrontate, a scelta, uno dei seguenti problemi
 
 Create un classe di numeri complessi derivandola da TVector2 (classe di ROOT per vettori 2D). La classe deve avere almeno un metodo Print() (o la ridefinizione di <<) che stampi opportunamente il numero complesso, un metodo per il complesso coniugato, gli operatori +,-,* (per alcuni di questi, ma non per tutti, vanno bene quelli default derivati da TVector2). Create un breve programma di test
 Create una classe FIFO (first in first out) derivandola da vector<double>. Il costruttore dovrà fissare la lunghezza e il metodo che aggiunge un valore dovrà fare in modo che quando l'array è pieno, all'aggiunta di un nuovo elemento, venga eliminato il valore più vecchio (aiuto: per accede a vector dentro la classe derivata usate this)
 Partendo dall'esempio visto in classe creare una classe poligono (con metodo area astratto), si implementi il metodo generale perimetro e si derivi la classe triangolo (implementando il metodo area). Si usi TVector2 per descrivere i vertici del poligono.
*/
