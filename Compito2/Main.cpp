#include <cmath>
#include <fstream>
#include <vector>
#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TSystem.h>

#include "OdeSolver.h"
#include "Vettore.h"
#include "PuntoMateriale.h"
#include "Elettrone.h"
#include "fB.h"             //magnetic bottle definition
#include <functional>


using namespace std;

Vettore fE(Vettore R){
  return Vettore(0.001,0,0); //uniform electric field in the x direction. Change at will.
}

Vettore fInterna(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p){
  return Vettore(0,0,0);
}

Vettore fEsterna(unsigned int i, double t, vector<PuntoMateriale> p){
  //STEP 2 definizione forza esterna
    Vettore E=fE(p[i].R());                   //electric field
    //Vettore B=0.001*fB(p[i].R());
    Vettore B(0,0,1E-09);                     //magnetic field

    Vettore FLorentz=p[i].Carica()*(E+(p[i].V()^B)); //F=q(E+v^B) Lorentz Force
    
  return FLorentz;
}

int main(){ 
    
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);
  vector <PuntoMateriale> p;
    
  PuntoMateriale temp(Elettrone(),Vettore(0,0,0),Vettore(1E06,0,1E03));   //create the electron
  p.push_back(temp);
   

  OdeSolver ode("Rk4",p);   //setting the ODE
    
  ode.fInterna = fInterna;  //assigning the template functions to the class
  ode.fEsterna = fEsterna;
  ode.Passo(5E-06);         //setting the increment in time per step (critical)

  
  //Graphs creation
  vector<TGraph> gr(p.size());
  //TGraph *gr=new TGraph[p.size()];

  TCanvas c("c","",10,10,500,500);
  
  //XY coordinates graph
  double size=5000;                             //graph size
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(i,ode.Punto(i).R().X(),ode.Punto(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(0.5);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();
  app.Run(true);

  //Run of the numerical method + real-time plot of the coordinates 
  int k=0;
  while (ode.T()<1E-1){
    ode.Cinematica();
     // if (k%10==0){
    if (k%10==0){         //filling the graph gr[i] with updated coordinates 
      for (unsigned int i=0;i<ode.N();i++){
        gr[i].SetPoint(gr[i].GetN(),ode.Punto(i).R().X(),ode.Punto(i).R().Y());
      }
      
      gPad->Modified(); gPad->Update();
      gSystem->ProcessEvents();
    }
    k++;
  }
  // k++;
  // }

  app.Run(true);

  return 0;
  
  
}
