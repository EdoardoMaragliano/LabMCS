#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE

#include "Particella.h"
#include "Vettore.h"

namespace consts{
  const double c = 299792458;
  const double G = 1;
};

class PuntoMateriale: public Particella{
 public:
 PuntoMateriale(Particella p=Particella(), Vettore r=Vettore(), Vettore v=Vettore()):Particella(p),m_r(r),m_p(v){}
 PuntoMateriale(double massa, double carica, Vettore r, Vettore k):PuntoMateriale(Particella(massa,carica),r,k){}
  Vettore R();    
  double  Beta_p();
  double  Gamma_p();
  double  Beta_v();
  double  Gamma_v();
  Vettore V();
  Vettore P();
  void    R(Vettore);
  void    V(Vettore);
  void    P(Vettore);
  Vettore CampoGravitazionale(Vettore);
  
 private:
  Vettore m_r;
  Vettore m_p;		//per integratore relativistico
};

#endif
