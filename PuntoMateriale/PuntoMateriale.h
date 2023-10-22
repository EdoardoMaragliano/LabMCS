

#ifndef PuntoMateriale_h
#define PuntoMateriale_h

#include "Vettore.h"
#include "Particella.h"


class PuntoMateriale : public Particella {
public:
   
    PuntoMateriale(Particella p=Particella(), Vettore R=Vettore(), Vettore V=Vettore()):Particella(p),m_R(R),m_V(V){}
    PuntoMateriale(double massa, double carica, Vettore R, Vettore V):PuntoMateriale(Particella(massa,carica),R,V){}
    
    
    //getters
    Vettore R() const;
    Vettore V() const;
    //setters
    void R(double,double,double);
    void R(Vettore);
    void V(double,double,double);
    void V(Vettore);
    //metodi
    Vettore CampoGravitazionale(Vettore);
private:
    Vettore m_R;
    Vettore m_V;
    
};

#endif 
