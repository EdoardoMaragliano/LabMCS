#include "Vettore.h"
#include <iostream>
#include <vector>

using namespace std;


int main(){
  Vettore a(3,1,1);
  Vettore b(2,2,2);

  Vettore r1  = a+b;
  Vettore r2  = a-b;

  cout << "Somma " << r1 << endl;
  cout << "Diff  " << r2 << endl;

    double modulo;
    modulo=a.getModulus();
    cout << "|a|= " << modulo << endl;
    double d;
    d=a*b;
    cout <<"a*b=" << d << endl;
    d=dot(a,b);
    cout <<"a*b=" << d << endl;
    Vettore c;
    c=cross(a,b);
    cout << "il prodotto vettore tra a e b é: " << c << endl;
    Vettore p;
    p=a^b;
    cout << "il prodotto vettore tra a e b é: " << p << endl;
    
   // vector <Vettore> v;
    

  return 0;
}
