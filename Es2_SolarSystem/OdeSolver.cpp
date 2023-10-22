#include "Vettore.h"
#include "OdeSolver.h"

void OdeSolver::Punto(unsigned int i,PuntoMateriale tmp){ //setta m_p[i]
  m_p[i] = tmp;
}

vector<PuntoMateriale> OdeSolver::Punti(){  //restituisce m_p
  return m_p;
}

PuntoMateriale OdeSolver::Punto(unsigned int i){ //restituisce m_p[i]
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::Passo(double h){
  m_h = h;
}

double OdeSolver::Passo(){
  return   m_h;
}


Vettore OdeSolver::m_eqDiff(unsigned int i, double t, vector<PuntoMateriale> p){
  //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
    //m*a=F_{int}+F_{ext}
    Vettore f;//f_tot su i
    for(unsigned int j=0; j<p.size();j++){
        if (i!=j)
            f=f+fInterna(i,j,t,p);
    }
  return 1/p[i].Massa()*(f+fEsterna(i,t,p));
}

//Da implementare a cura dello studente
void OdeSolver::Cinematica(){

  if (m_method=="Eulero"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }

  } else if (m_method=="Rk2"){
    // STEP 5 implementare Runge Kutta al secondo ordine
      vector<Vettore> k1(m_p.size());
      vector<Vettore> w1(m_p.size());
      vector<Vettore> k2(m_p.size());
      vector<Vettore> w2(m_p.size());
      for(unsigned int i=0;i<m_p.size();i++){
          k1[i] = m_h*m_p[i].V();
          w1[i] = m_h*m_eqDiff(i,m_t,m_p);
      }
      auto appo(m_p);
      for(unsigned int i=0;i<m_p.size();i++){
          appo[i].R(m_p[i].R()+0.5*k1[i]);
          appo[i].V(m_p[i].V()+0.5*w1[i]);
      }
      
      for(unsigned int i=0;i<m_p.size();i++){
          k2[i]=m_h*appo[i].V();
          w2[i]=m_h*m_eqDiff(i,m_t+0.5*m_h,appo);
      }
      for(unsigned int i=0;i<m_p.size();i++){
          m_p[i].R(m_p[i].R()+k2[i]);
          m_p[i].V(m_p[i].V()+w2[i]);
      }
      
  }
  m_t += m_h;

}

