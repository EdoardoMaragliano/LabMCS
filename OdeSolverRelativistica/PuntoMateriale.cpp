//integratore relativistico

#include "PuntoMateriale.h"
#include "Vettore.h"
#include <cmath>

Vettore PuntoMateriale::R(){
  return m_r;
}


double PuntoMateriale::Beta_p(){
  return (1/consts::c)*sqrt((pow(m_p.Mod()*consts::c,2))/((pow(m_p.Mod(),2))+(pow(consts::c*Massa(),2))));
}

double PuntoMateriale::Gamma_p(){
  return 1/sqrt(1-Beta_p()*Beta_p());
}

double PuntoMateriale::Beta_v(){
  return V().Mod()*(1/consts::c);
}

double PuntoMateriale::Gamma_v(){
  return 1/sqrt(1-Beta_v()*Beta_v());
}


Vettore PuntoMateriale::V(){
 
  return (1/(Massa()*Gamma_p()))*m_p;
}

Vettore PuntoMateriale::P(){
  return m_p;
}
  

void PuntoMateriale::R(Vettore r){
m_r = r;
}

void PuntoMateriale::V(Vettore v){
m_p = Massa()*Gamma_v()*v;
  }
void PuntoMateriale::P(Vettore p){
m_p = p;
}

  
Vettore PuntoMateriale::CampoGravitazionale(Vettore r){
  // F = -G m m_prova/(r-r0)^2 vers(r-r0)
  // a = F/m_prova = -G m /(r-r0)^2 vers(r-r0)


  Vettore r0   = m_r;
  Vettore dist = r-r0;

  Vettore val  = -consts::G*Massa()/pow(dist.Mod(),2)*dist.Vers();

  return val;
  
  
}
