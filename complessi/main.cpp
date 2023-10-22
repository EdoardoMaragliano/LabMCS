#include "Complesso.h"
#include <iostream>

using namespace std;
int main(){
    
    Complesso z(1,1);
    cout << z << endl;
    Complesso w=z.Conj();
    cout << w << endl;
    
    Complesso a(1,1);
    Complesso b(2,1);
    Complesso c=a-b; //controllo sottrazione
    cout << c << endl;
    Complesso d=a*b; //controllo prodotto
    cout << d << endl;
    cout << 2*d << endl;
    d.Re(5);
    d.Im(5);
    cout << d << endl;
    return 0;
}
