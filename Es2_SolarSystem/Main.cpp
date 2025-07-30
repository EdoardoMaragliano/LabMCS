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

#include <functional>
#include "OdeSolver.h"
#include "Vettore.h"
#include "PuntoMateriale.h"

using namespace std;

Vettore fInterna(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p){
  //STEP 2 definizione forza interna
    Vettore campo=p[i].Massa()*p[j].CampoGravitazionale(p[i].R());
    //campo generato da p[j] nel punto p[i]*m_p[i]
    //forza sul punto i-esimo
  return campo;
}

Vettore fEsterna(unsigned int i, double t, vector<PuntoMateriale> p){
  //STEP 2 definizione forza esterna
  return Vettore(0,0,0);
}

int main(){ 
    
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);
  vector <PuntoMateriale> p;
    
  //Lettura dei dati dal file
  double mass;
  double x,y,z,vx,vy,vz;
  ifstream f("fileInput");
  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){

      PuntoMateriale temp(mass,0,Vettore(x,y,z),Vettore(vx,vy,vz));
      p.push_back(temp);
  }

  //create ODE

  OdeSolver ode("Rk2",p);
    
  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  // OdeSolver ode(p,"Eulero");
  ode.fInterna = fInterna;
  ode.fEsterna = fEsterna;
  ode.Passo(1);

  
  //Creazione dei grafici (uno per pianeta)
  vector<TGraph> gr(p.size());
  TCanvas c("c","",10,10,800,800);
  
  //Preparazione grafico delle coordinate dei pianeti
  double size=10; // 5 unita' astronomiche
  gPad->DrawFrame(-size,-size,size,size);

  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};

  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(i,ode.Punto(i).R().X(),ode.Punto(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();
  app.Run(true);

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  int k=0;
  while (ode.T()<5000){
    ode.Cinematica();
    if (k%10==0){
      for (unsigned int i=0;i<ode.N();i++){
        //STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
        gr[i].SetPoint(gr[i].GetN(),ode.Punto(i).R().X(),ode.Punto(i).R().Y());
      }

    gPad->Modified(); gPad->Update();
    gSystem->ProcessEvents();  // <---- questa linea!
    }
      k++;
  }

  app.Run(true);

  return 0;
  
  
}
