
#include "PuntoMateriale.h"


    
//Costruttori
/*
PuntoMateriale::PuntoMateriale(Particella p, Vettore R, Vettore V){
    this->Massa(p.Massa());
    this->Carica(p.Carica());
    m_R=R;
    m_V=V;
}*/
/*
PuntoMateriale::PuntoMateriale(double m, double q, Vettore R, Vettore V){
    this->Massa(m);
    this->Carica(q);
    m_R=R;
    m_V=V;
}*/
//getters
Vettore PuntoMateriale::R() const{
    return m_R;
}
Vettore PuntoMateriale::V() const{
    return m_V;
}
//setters    

void PuntoMateriale::R(double x,double y,double z){
    m_R.X(x);
    m_R.Y(y);
    m_R.Z(z);
}
void PuntoMateriale::R(Vettore R){
    m_R=R;
}
void PuntoMateriale::V(double vx,double vy,double vz){
    m_V.X(vx);
    m_V.Y(vy);
    m_V.Z(vz);
}
void PuntoMateriale::V(Vettore V){
    m_V=V;
};
//metodi

Vettore PuntoMateriale::CampoGravitazionale(Vettore R){
    double G=1;
    Vettore campo;
  //  Vettore d=R-this->R();
    Vettore d=R-m_R;
    
    campo=-G*Massa()/pow(d.Mod(),2)*d.Vers();
    return campo;
}
