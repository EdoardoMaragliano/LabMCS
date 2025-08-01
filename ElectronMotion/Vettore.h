#ifndef _VETTORE
#define _VETTORE

#include <iostream>
class Vettore{
 public:
  Vettore(double x=0,double y=0,double z=0):m_v{x,y,z}{}
  double  X() const;
  void    X(double);
  double  Y() const;
  void    Y(double);
  double  Z() const;
  void    Z(double);
  Vettore operator-();            // - unario
  Vettore operator-( Vettore);    // - binario
  Vettore operator+( Vettore);    // + binario     
  double  operator*( Vettore);    // prod. scalare 
  Vettore operator^( Vettore);    // prod. vettore 
  Vettore operator*(double);      // molt. per scalare
  double  Mod();                  // modulo  
  Vettore Vers();                 // versore 
    Vettore Pow(const Vettore, double); //potenza
 private:
  double m_v[3];
};

std::ostream& operator<<(std::ostream&,  Vettore );
std::istream& operator>>(std::istream&, Vettore &);
Vettore operator*(double,  Vettore );

#endif
