#include "OdeSolver.h"
#include "PuntoMateriale.h"
#include "Vettore.h"
#include <cmath>
#include <iostream>
#include <functional>

#include <TStyle.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraph.h>

using namespace std;

double rho=1; //kg/m3
double rho0=2; //kg/m3
double mu=0.001; //Pa s
double r=0.5; //m
double h=100;
double Vol=4/3*TMath::Pi()*pow(r,3);
double m=rho0*Vol;

double Re=2*rho*r/mu;
double g=9.81;

double Cd( double v){
	return 24/Re*v+4/Re*pow(v,1.5)+0.4*pow(v,2);
}

Vettore fInterna(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p){

  return Vettore(0,0,0);
}

Vettore fEsterna(unsigned int i, double t, vector<PuntoMateriale> p){
	Vettore peso=Vettore(0,0,-g*m);
		Vettore visc=-0.5*Cd(p[i].V().Mod())*rho*TMath::Pi()*pow(r,2)*(p[i].V().Vers());
	cout << visc << endl;
	Vettore archimede=Vettore(0,0,rho*g*Vol);
	cout << archimede << endl;
  return peso+visc+archimede;
}

int main(){ 
    
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  PuntoMateriale biglia(m,0,Vettore(0.0,0.0,h),Vettore(0.0,0.0,0.0));
  vector <PuntoMateriale> p;
  p.push_back(biglia);
  OdeSolver ode("Rk2",p);

  ode.fInterna = fInterna;
  ode.fEsterna = fEsterna;
  ode.Passo(0.1);

  TGraph gr;
  gr.SetTitle("Velocita");
 // gr->GetXaxis()->SetTitle("t [s]");
 // gr->GetYaxis()->SetTitle("v [m/s]");
  TCanvas c("c","",10,10,500,500);

  gr.SetMarkerStyle(8);
  gr.SetPoint(gr.GetN(),ode.T(),ode.Punto(0).V().Z());


  while (ode.Punto(0).R().Z()>0){
  	ode.Cinematica();
  	//if(ode.Punto(0).R().Z()>0)
  		gr.SetPoint(gr.GetN(),ode.T(),ode.Punto(0).V().Z());
  

  }

  gr.Draw("AP");
  app.Run(true);


	return 0;
}
