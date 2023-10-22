//
//  Complesso.cpp
//  
//
//  Created by Edoardo Maragliano on 13/10/20.
//

#include "Complesso.h"
Complesso::Complesso(TVector2 v){
    fX=v.X();
    fY=v.Y();
}
double Complesso::Re() const{
    return fX;
}
double Complesso::Im() const{
    return fY;
}

void Complesso::Re(double a){
    fX=a;
}
void Complesso::Im(double b){
    fY=b;
}

Complesso Complesso::Conj(){
    Complesso w(fX,-fY);
    return w;
}

std::ostream& operator<<(std::ostream &stream, Complesso z){
    if(z.Im()>0)
    stream <<  z.Re() << "+" << z.Im() << "j" ;
    else if(z.Im()<0)
    stream <<  z.Re() << z.Im() << "j" ;
    else 
        stream << z.Re();
    return stream;
}

Complesso Complesso::operator*(const Complesso& z) const{
    Complesso appo(fX*z.Re()-fY*z.Im(),fX*z.Im()+fY*z.Re());
    return appo;
}

