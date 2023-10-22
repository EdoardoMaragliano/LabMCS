#ifndef _VETTORE
#define _VETTORE

#include <ostream>
#include <istream>
#include <cmath>


// Classi
class Vettore{
public:
    Vettore(double x=0, double y=0, double z=0):m_v{x,y,z}{}
    //getters
    double X() const;
    double Y() const;
    double Z() const;
    //setters
    void X(double);
    void Y(double);
    void Z(double);
    //metodi vari
    double getModulus() const;          //modulo
    Vettore Vers() const;
    //operators
    Vettore operator-() const;
    Vettore operator+(const Vettore& b) const;
    Vettore operator-(const Vettore& b) const;
    Vettore operator*(double b) const;
    double operator*(const Vettore& b); //prod scalare
    Vettore operator^(const Vettore& b) const; //prod vettore
    
    
private:
    double m_v[3];
};

// Funzioni
Vettore operator*(double, const Vettore &); //prod per scalare
double dot(const Vettore&, const Vettore& );//prod scalare
Vettore cross(const Vettore&, const Vettore&);//prod vettore
//stream
std::ostream& operator<<(std::ostream &stream, Vettore v);
std::istream& operator>>(std::istream &stream, Vettore &v);

#endif
