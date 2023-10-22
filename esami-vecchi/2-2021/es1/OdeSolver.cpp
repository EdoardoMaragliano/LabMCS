//classe ode solver
//edoardo maragliano
//last update 31 gen 2021


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
          k1[i] = m_h*m_p[i].V();		//h*V(t_n)
          w1[i] = m_h*m_eqDiff(i,m_t,m_p);	//h*a(t_n)
      }
      auto appo(m_p);				//punto intermedio
      for(unsigned int i=0;i<m_p.size();i++){
          appo[i].R(m_p[i].R()+0.5*k1[i]);     //x(t_n+h/2)=x(t_n)+0.5*k1
          appo[i].V(m_p[i].V()+0.5*w1[i]);     //v(t_n+h/2)=v(t_n)+0.5*w1
      }
      
      for(unsigned int i=0;i<m_p.size();i++){ 
          k2[i]=m_h*appo[i].V();			//h*v(t_n+h/2)
          w2[i]=m_h*m_eqDiff(i,m_t+0.5*m_h,appo);	//h*a(t_n+h/2)
      }
      for(unsigned int i=0;i<m_p.size();i++){
          m_p[i].R(m_p[i].R()+k2[i]);		//x(t_n+h)=x(t_n)+h*v(t_n+h/2)
          m_p[i].V(m_p[i].V()+w2[i]);		//v(t_n+h)=v(t_n)+h*a(t_n+h/2)
      }
      
  } else if (m_method=="Rk4"){
      //implementare Runge Kutta al quarto ordine
      vector<Vettore> k1(m_p.size());
      vector<Vettore> w1(m_p.size());
      vector<Vettore> k2(m_p.size());
      vector<Vettore> w2(m_p.size());
      vector<Vettore> k3(m_p.size());
      vector<Vettore> w3(m_p.size());
      vector<Vettore> k4(m_p.size());
      vector<Vettore> w4(m_p.size());
      for(unsigned int i=0;i<m_p.size();i++){
          k1[i] = m_h*m_p[i].V();		//h*f(t,x)
          w1[i] = m_h*m_eqDiff(i,m_t,m_p);
      }
      auto appo(m_p);		//devo crearlo per passarlo ad eqDiff e calcolare v in t+h/2,x+0.5k1
      for(unsigned int i=0;i<m_p.size();i++){
          appo[i].R(m_p[i].R()+0.5*k1[i]);	
          appo[i].V(m_p[i].V()+0.5*w1[i]);
      }
      
      for(unsigned int i=0;i<m_p.size();i++){
          k2[i]=m_h*appo[i].V();		//h*f(t+0.5h,x+0.5k1)
          w2[i]=m_h*m_eqDiff(i,m_t+0.5*m_h,appo);
      }
      
      auto appo2(m_p);		//devo crearlo per passarlo ad eqDiff e calcolare v in t+h/2,x+0.5k2
      for(unsigned int i=0;i<m_p.size();i++){
          appo2[i].R(m_p[i].R()+0.5*k2[i]);
          appo2[i].V(m_p[i].V()+0.5*w2[i]);
      }
      
      for(unsigned int i=0;i<m_p.size();i++){
          k3[i]=m_h*appo2[i].V();
          w3[i]=m_h*m_eqDiff(i,m_t+0.5*m_h,appo2);
      }
      
      auto appo3(m_p);		//devo crearlo per passarlo ad eqDiff e calcolare v in t+h,x+k3
      for(unsigned int i=0;i<m_p.size();i++){
          appo3[i].R(m_p[i].R()+k3[i]);
          appo3[i].V(m_p[i].V()+w3[i]);
      }
      
      for(unsigned int i=0;i<m_p.size();i++){
          k4[i]=m_h*appo3[i].V();
          w4[i]=m_h*m_eqDiff(i,m_t+m_h,appo3);
      }
      
      for(unsigned int i=0;i<m_p.size();i++){
          m_p[i].R(m_p[i].R()+1/6.*k1[i]+1/3.*k2[i]+1/3.*k3[i]+1/6.*k4[i]);
          m_p[i].V(m_p[i].V()+1/6.*w1[i]+1/3.*w2[i]+1/3.*w3[i]+1/6.*w4[i]);
      }
      
  }
  m_t += m_h;

}

