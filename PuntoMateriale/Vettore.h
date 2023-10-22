

#ifndef _VETTORE
#define _VETTORE

#include <iostream>
#include <cmath>

class Vettore{
public:
    Vettore(double x=0,double y=0,double z=0); //implementato nel cpp
    double  X() const;
    void    X(double);
    double  Y() const;
    void    Y(double);
    double  Z() const;
    void    Z(double);
    Vettore operator-();                        // - unario
    Vettore operator-(const Vettore&) const;    // - binario
    Vettore operator+(const Vettore&) const;    // + binario     
    double  operator*(const Vettore&) const;    // prod. scalare 
    Vettore operator^(const Vettore&) const;    // prod. vettore 
    Vettore operator*(double) const;            // molt. per scalare
    double  Mod() const;                        // modulo  (da impl.)
    Vettore Vers() const;                       // versore (da impl.)
private:
    double m_v[3];
};

std::ostream& operator<<(std::ostream&, const Vettore & );
std::istream& operator>>(std::istream&, Vettore &);
Vettore operator*(double,const Vettore& );

#endif



