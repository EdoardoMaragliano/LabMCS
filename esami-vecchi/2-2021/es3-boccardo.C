void es3(){
  TApplication app("app",NULL,NULL);
  TCanvas c1;
  ifstream ifile("expo_lowstat.dat");
  double x;
  TH1D *h = new TH1D ("h", "lowstat",15,0,10);
  while(ifile>>x){
    h->Fill(x);
    }


  TF1 *f = new TF1("f", "[0]*0.5*exp(-x/2.)",0,10);
  f->SetParameter(0, h->Integral(0,10));
  h->Fit("f");

  double pvalue = f->GetProb();
  cout << "pvalue = " << pvalue << endl;
    
TCanvas c2;
  ifstream file ("expo_highstat.dat");
  double y;

  TH1D *h1 = new TH1D ("h1", "highstat",90,0,10);
  while(file>>y){
    h1->Fill(y);
    
  }
  h1->Draw();
  TF1 *f1 = new TF1("f1", "[0]*([3]/[1]*exp(-x/[1])+((1-[3])/[2])*exp(-x/[2]))",0,40);
  f1->FixParameter(0,1);
  f1->SetParameter(1,2);
  f1->SetParameter(2,400);
  f1->SetParameter(3,0.2);
  
  
  h1->Fit("f1","0MULTI");
  
  
 
  f1->SetParameter(0,h1->GetEntries()*h1->GetBinWidth(1));
  f1->Draw("SAME");

  double tau1 = f1->GetParameter(1);
  double etau1 = f1->GetParError(1);
  double etau2 = f1->GetParError(2);
  double tau2 = f1->GetParameter(2);
  double k = 100*(f1->GetParameter(3));
  double t = 100-k;
  cout << "tau1 = " << tau1 << " +/- " << etau1 << " con percentuale " << k << " %" << endl << "tau2 = " << tau2 << " +/- " << etau2 << " con percentuale " << t << " %" << endl;

  app.Run(true);



}
