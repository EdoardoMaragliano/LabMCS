#include "PuntoMateriale.h"
#include "Vettore.h"
#include <cmath>

Vettore PuntoMateriale::R(){
  return m_r;
}

Vettore PuntoMateriale::V(){
  return m_v;
}

double PuntoMateriale::Beta(){
  return V().Mod()*(1/consts::c);
}

double PuntoMateriale::Gamma(){
  return 1/sqrt(1-Beta()*Beta());
}

Vettore PuntoMateriale::P(){
  return Gamma()*Massa()*V();
}

void PuntoMateriale::R(Vettore r){
  m_r = r;
}

void PuntoMateriale::V(Vettore v){
  m_v = v;
}

Vettore PuntoMateriale::CampoGravitazionale(Vettore r){
  // F = -G m m_prova/(r-r0)^2 vers(r-r0)
  // a = F/m_prova = -G m /(r-r0)^2 vers(r-r0)


  Vettore r0   = m_r;
  Vettore dist = r-r0;

  Vettore val  = -consts::G*Massa()/pow(dist.Mod(),2)*dist.Vers();

  return val;
  
  
}
