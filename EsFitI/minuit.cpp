#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>


using namespace std;

namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

TF1 *f1;
TF1 *f2;

double fun1(const double *x1,const double *par){  //funzione che fitta la prima serie di dati
  f1->SetParameter(0,par[0]);                     //parametri 0 e 1 in comune!!
  f1->SetParameter(1,par[1]);
  f1->SetParameter(2,par[2]);
  f1->SetParameter(3,par[3]);
  return f1->Eval(*x1);
}

double fun2(const double *x2,const double *par){  //funzione che fitta la seconda serie di dati
  f2->SetParameter(0,par[0]);                     //parametri 0 e 1 in comune!!
  f2->SetParameter(1,par[1]);
  f2->SetParameter(2,par[4]);
  f2->SetParameter(3,par[5]);
  return f2->Eval(*x2);
}

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  for(int i=0;i<data::t1.size();i++)
    f+=pow((data::t1[i]-fun1(&data::x1[i],par))/data::et1[i],2);
  for(int i=0;i<data::t2.size();i++)
    f+=pow((data::t2[i]-fun2(&data::x2[i],par))/data::et2[i],2);
}  


int main(){

  TApplication app("app",0,NULL);

  ifstream fp1("perno1.dat");
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1;
  double tx2,tt2,tex2,tet2;


  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);				//carico i dati nel grafico 1
    gr1.SetPointError(gr1.GetN(),tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);				//carico i dati nel grafico 2
    gr2.SetPointError(gr2.GetN(),tex2,tet2);
  }
  

  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",20,50);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",20,50);
 
  // Minuit
  TMinuit minuit(6);
  //'root-config --cflags --glibs' -lMinuit

  minuit.SetFCN(chi2);
  minuit.DefineParameter(0,"x0",30,0.01,0.,0.);
  minuit.DefineParameter(1,"T0",4,0.01,0.,0.);
  minuit.DefineParameter(2,"a1",f1->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(3,"b1",f1->GetParameter(3),0.01,0.,0.);
  minuit.DefineParameter(4,"a2",f2->GetParameter(2),0.01,0.,0.);
  minuit.DefineParameter(5,"b2",f2->GetParameter(3),0.01,0.,0.);
  minuit.Command("MIGRAD");

  TCanvas c("Pendolo","Pendolo",600,500);
  gr1.SetMarkerStyle(7);
  gr2.SetMarkerStyle(7);
  gr1.SetMarkerColor(kBlue);
  gr2.SetMarkerColor(kRed);
  gr1.Draw("AP");
  gr2.Draw("P");
  f1->Draw("SAME");
  f1->SetLineColor(kBlue);
  f2->SetLineColor(kRed);
  f2->Draw("SAME");
  gPad->Modified(); gPad->Update();
   // Get result
  double t0,et0;
  minuit.GetParameter(1,t0,et0);
  cout << endl << "***********************************************************" << endl;
  cout << "Periodo di isocronia del pendolo di Kater: " << t0 << " +/- " << et0 << endl;


  app.Run(true);

  return 0;

}
