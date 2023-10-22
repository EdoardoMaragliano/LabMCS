{
  ifstream inputfile ("arancione_IV.dat");
  if (!inputfile){
    cout << "File non esistente o non accessibile" << endl;
    return 0;
  }
  
  TGraphErrors gr;
  int i=0;
  double x,y,ex,ey,ly, ely;
  while (inputfile >> x >> y >> ex >> ey){
  	if(y>10E-7){
  	ly=log(y);
  	ely=ey/y;
    gr.SetPoint(i,x,ly);
    gr.SetPointError(i,ex,ely);
    i++;
	}
  }
  
  /*TF1 f("f","[0]*(exp([1]*(x/[2]))-1)",0.3,3);
  
  f.SetParameter(0,1e-11);
  f.SetParLimits(0,0,1e-3);
  f.SetParameter(1,1.16e4);
  f.FixParameter(2,273.15+24.8);*/

  TF1 r("r","[0]*(x-[1])",0,2.4);
  r.SetParameter(0,2);
  r.SetParameter(1,2);
   
  gr.Draw("AP");
  gr.GetXaxis()->SetTitle("Tensione [V]");
  gr.GetYaxis()->SetTitle("Corrente [A]");
  gr.Fit("r");
  //f.Draw();
}
