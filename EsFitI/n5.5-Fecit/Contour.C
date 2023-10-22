#include <TMinuit.h>
void Contour(){
  TGraphErrors *gr = new TGraphErrors("pendolo.dat");
  TF1 *f = new TF1("f","[0]*x+[1]",0,10);
  f->SetParameter(0,4);
  f->SetParameter(1,0);
  TCanvas *c = new TCanvas;
  c->Divide(2,1);
  c->cd(1); gr->Draw("AP"); gr->Fit("f");
  c->cd(2);
  gMinuit->SetErrorDef(1); //Setto delta chi quadro 1
  TGraph *grc = (TGraph*)gMinuit->Contour(100,1,0);//la parte prima serve perche' root e' strano //(n punti, par 1, par2)
  grc->Draw("AC"); //disegno
  //osservo quali sono le coppie di parametri che hanno delta chi quadro 1
}
