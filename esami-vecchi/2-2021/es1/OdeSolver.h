//classe ode solver
//edoardo maragliano
//last update 31 gen 2021


#ifndef _ODESOLVER
#define _ODESOLVER

#include <vector>
#include "Vettore.h"
#include "PuntoMateriale.h"
#include "functional"

using namespace std;

class OdeSolver{
 public:
 	//uso la costruzione per delega attraverso lista dei parametri da settare di default
  OdeSolver(string method="Rk2", vector<PuntoMateriale> p=vector<PuntoMateriale>(0)):m_method(method),m_p(p),m_t(0),m_h(0.1){}
    
  void                   Punto(unsigned int i,PuntoMateriale tmp);//set m_p[i]
  PuntoMateriale         Punto(unsigned int i); //restituisce m_p[i]
  vector<PuntoMateriale> Punti(); //restituisce m_p
  unsigned int   N();             //lunghezza di m_p
  void           T(double t0);    //set T
  double         T();             //get T
  void           Passo(double h); //set h
  double         Passo();         //get h
  void           Cinematica();    //aggiorna le coord
  std::function < Vettore(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p) > fInterna;	//template func
  std::function < Vettore(unsigned int i,double t, vector<PuntoMateriale> p) >        fEsterna;				//template func
 private:
  string   m_method;    		//metodo di approssimazione
  vector<PuntoMateriale> m_p;	//vettore di punti materiali
  double   m_t,m_h;         	//tempo e incremento
  Vettore  m_eqDiff(unsigned int i, double t, vector<PuntoMateriale>);

};


#endif
