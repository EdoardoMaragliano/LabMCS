{
  TGraphErrors *gr = new TGraphErrors("pendolo.dat");
  TF1 *f = new TF1("f","[0]*x+[1]",0,10);
  f->SetParameter(0,4);
  f->SetParameter(1,0);
  TCanvas *c = new TCanvas;
  c->Divide(2,1);
  c->cd(1); gr->Draw("AP"); gr->Fit("f");
  c->cd(2);
  gMinuit->SetErrorDef(1);
  TGraph *grC = (TGraph*)gMinuit->Contour(100,0,1);
  grC->Draw("AC");
}
