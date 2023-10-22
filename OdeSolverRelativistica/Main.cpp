#include <cmath>
#include <fstream>
#include <vector>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>


#include "OdeSolver.h"
#include "Vettore.h"
#include "PuntoMateriale.h"
#include "Elettrone.h"
#include "fB.h"
using namespace std;

//STEP 2 definizione forza interna: nulla nel caso del singolo elettrone
Vettore fInterna(unsigned int i,unsigned int j, double t, vector<PuntoMateriale> p){
  Vettore nullo (0,0,0);
  return nullo;
}


//STEP 2 definizione forza esterna: utilizzo di un campo magnetico perpendicolare alla velocità della carica e dipendente dalla sua posizione, e di un campo elettrico che può eventualemnte essere definito  per dipendere anch'esso dalla posizione. Il campo elettrico accelera la carica, la cui velocità non uniforme all'ingresso nel campo magnetico genera un moto a spirale semplice se E è costante. In questo caso, è stato scelto un campo dipendente linearmente dalla posizione dell'elettrone.

Vettore fEsterna(unsigned int i, double t, vector<PuntoMateriale> p){
  Vettore B = 0.01*fB(p[i].R());
  double q = p[i].Carica();
  Vettore E = 4*(p[i].R());
  Vettore F = q*(E+(p[i].V()^B));
  return F;
}

int main(){ 
  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

// STEP 1 creazione dell'oggetto della classe OdeSolver
  //   - creazione oggetto OdeSolver vuoto, assegnazione con il metodo Punto
  //   - creazione di vector<PuntoMateriale> e poi creazione di OdelSover: in questo caso specifico il vector<PuntoMateriale> avrà una sola entrata (c'è un solo elettrone)

  vector <PuntoMateriale> e;
  
  Elettrone a;
  PuntoMateriale elettrone(a, Vettore(1,0,0), Vettore(0,0,0));
  Vettore vel(5E6,0,0);
  elettrone.V(vel);
  e.push_back(elettrone);
  OdeSolver ode("Rk2", e);




  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)

  ode.fInterna = fInterna;
  ode.fEsterna = fEsterna;
  ode.Passo(9E-7);
  cout << fEsterna (0,0,e)<<endl;
  //Creazione del grafico (uno per ogni elemento del vector)

  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dell'elettrone in moto nel campo

  gPad->DrawFrame(-2000,-2000,2000,2000);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.Punto(i).R().X(),ode.Punto(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("PC");
  }
  gPad->Modified(); gPad->Update();
  app.Run(true);
  
  //Run del metodo numerico + grafico in tempo reale delle coordinate

  while (ode.T()<90E-5){
    
    ode.Cinematica();
  
   
    //STEP 4 riempimento delle grafico gr[0] con le coordinate aggiornate

    for (unsigned int i=0;i<ode.N();i++){
      gr[i].SetPoint(gr[i].GetN(),ode.Punto(i).R().X(),ode.Punto(i).R().Y());
      } 
    gPad->Modified(); gPad->Update();
    }

  app.Run(true);
  return 0;
  
  
}
