#include "Vettore.h"
#include <iostream>
#include <vector>

using namespace std;


int main(){
  Vettore a(3,1,1);
  Vettore b(2,2,2);

  Vettore r1  = a+b;
  Vettore r2  = a-b;

  cout << "Vettore a: " << a << endl;
  cout << "Vettore b: " << b << endl;

  cout << "Somma " << r1 << endl;
  cout << "Diff  " << r2 << endl;

    double modulo;
    modulo=a.getModulus();
    cout << "|a|= " << modulo << endl;
    double d;
    cout << "computing a*b" << endl;
    d=a*b;
    cout <<"a*b=" << d << endl;
    cout << "computing a*b with dot()" << endl;
    d=dot(a,b);
    cout <<"a*b=" << d << endl;
    Vettore c;
    cout << "computing a x b with cross()" << endl;
    c=cross(a,b);
    cout << "a x b is: " << c << endl;
    Vettore p;
    cout << "computing a x b with operator ^" << endl;
    p=a^b;
    cout << "il prodotto vettore tra a e b é: " << p << endl;
    
   // vector <Vettore> v;
    

  return 0;
}
