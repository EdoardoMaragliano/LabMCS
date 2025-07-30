#include "Complesso.h"
#include <iostream>

using namespace std;
int main(){
    
    Complesso z(1,1);
    cout << z << endl;
    Complesso w = z.Conj();
    cout << w << endl;
    
    Complesso a(1,1);
    Complesso b(2,1);
    cout << a << endl;
    cout << b << endl;
    cout << "computing a-b" << endl;
    Complesso c=a-b; //controllo sottrazione
    cout << c << endl;
    cout << "computing ab" << endl;
    Complesso d=a*b; //controllo prodotto
    cout << d << endl;
    d = 2*d; //controllo prodotto per scalare
    cout << "computing 2ab" << endl;
    cout << d << endl;
    cout << "Setting real part to 5" << endl;
    d.Re(5);
    cout << d << endl;
    cout << "Setting imaginary part to 5" << endl;
    d.Im(5);
    cout << d << endl;
    return 0;
}
