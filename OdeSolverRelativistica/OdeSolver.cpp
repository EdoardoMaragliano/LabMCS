//integratore relativistico

#include "Vettore.h"
#include "OdeSolver.h"

void OdeSolver::Punto(PuntoMateriale tmp){
  m_p.push_back(tmp);
}

vector<PuntoMateriale> OdeSolver::Punti(){
  return m_p;
}

PuntoMateriale OdeSolver::Punto(unsigned int i){
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

//STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
Vettore OdeSolver::m_eqDiff(unsigned int i, double t, vector<PuntoMateriale> p){
  Vettore sum(0,0,0);
  for (unsigned int j = 0; j < p.size(); j++)  {
   
    if (j != i){
      sum = sum + fInterna(i, j, t, p); }
      
  }
    Vettore ris = sum + fEsterna (i,t,p);
    return ris;
}

//Da implementare a cura dello studente
void OdeSolver::Cinematica(){

  if (m_method=="Eulero"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].P()*(1/(m_p[i].Massa()*m_p[i].Gamma_v()));
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].P(m_p[i].P() + w1[i]);
    }
 // STEP 5 implementare Runge Kutta al secondo ordine
  } else if (m_method=="Rk2"){

    vector<Vettore> k1(m_p.size());
    vector<Vettore> w1(m_p.size());
    vector<Vettore> k2(m_p.size());
    vector<Vettore> w2(m_p.size());
    auto pt(m_p);	//variabile di appoggio, temporanea

    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].P()*(1/(m_p[i].Massa()*m_p[i].Gamma_v()));
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }
    for (unsigned int i=0;i<m_p.size();i++){		//aggiorno la variabile di appoggio
      pt[i].R(pt[i].R() + 0.5*k1[i]);
      pt[i].P(pt[i].P() +0.5*w1[i]);
    }
    for (unsigned int i=0;i<m_p.size();i++){
      k2[i] = m_h*pt[i].P()*(1/(pt[i].Massa()*pt[i].Gamma_v()));
      w2[i] = m_h*m_eqDiff(i, m_t + m_h/2, pt);
    }
    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].P(m_p[i].P() + w2[i]);
    }


    
  }
  m_t += m_h;

}

