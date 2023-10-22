{
  ifstream inputfile ("costanti-fond.dat");
  if (!inputfile){
    cout << "File non esistente o non accessibile" << endl;
    return 0;
  }
  
  TGraphErrors gr;
  int i=0;
  double x,y,ex,ey,nu, enu, sigmax;
  const double c=299792458;

  while (inputfile >> x >> ex >> y >> ey){
  	if(y>10E-11){
      sigmax=ex/sqrt(3);    //l'errore dato è massimo
    enu=c/(x*x)*sigmax;
    nu=c/x;                   // mi da lambda ma voglio nu
    gr.SetPoint(i,nu,y);
    gr.SetPointError(i,enu,ey);
    i++;
	}
  }

  TF1 r("r","[0]+[1]*x",0,8E14);
  r.SetParameter(0,2);
  r.SetParameter(1,2E-14);
   
  gr.Draw("AP");
  gr.GetXaxis()->SetTitle("Frequenza [Hz]");
  gr.GetYaxis()->SetTitle("Tensione [V]");
  gr.Fit("r");
  double vglobale=r.GetParameter(1);
  double eVglobale=r.GetParError(1);

  cout << "stima da fit globale " << vglobale << " +/- " << eVglobale << endl;


  double vblu=6.086E-15;
  double vverde=5.6763E-15;
  double varancione=5.564E-15;
  double vrosso=5.288E-15;
  double vref=5.635E-15;
  double evref=1.3E-18;

  double err=sqrt(pow(vref-vblu,2)+pow(vref-vverde,2)+pow(vref-varancione,2)+pow(vref-vrosso,2)+evref*evref);
  cout << "stima da lambda separate "<< vref << " +/- " << err << endl;

  cout << endl << endl;
  cout << "errore dovuto al rosso " << abs(vref-vrosso) << endl;
  cout << "errore dovuto all'arancione " << abs(vref-varancione) << endl;
  cout << "errore dovuto al verde " << abs(vref-vverde) << endl;
  cout << "errore dovuto al blu " << abs(vref-vblu) << endl;
} 
