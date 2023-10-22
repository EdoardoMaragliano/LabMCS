/*(Esame 21/01/19) Sono state effettuate n misure x1 , ..., xn di una grandezza X distribuita secondo (file DatiGamma.dat) la distribuzione:
f(x,θ) = x^2exp(−x/θ)/2θ^3
• Si determini la miglior stima del parametro theta e il suo errore.
• Si sovrapponga la distribuzione (con il parametro determinato al punto precedente) ai dati.
*/


{
TApplication app("app",0,NULL);
double appo;
vector <double> data;
TCanvas c("Plot","Plot",500,500);

ifstream filein;
filein.open("DatiGamma.dat");
while(filein>>appo){
	data.push_back(appo);
}

double max=data[0];
double min=data[0];

//cerco max e min
for (int i=0;i<data.size();i++){
	if(data[i]>max)
		max=data[i];

	if(data[i]<min)
		min=data[i];
}
cout << "max=" << max << "\t min=" <<  min << endl;

double NBins=100;
TH1D h("h","Plot",NBins,min-1,max+1);

for (int i=0;i<data.size();i++)
	h.Fill(data[i]);

TF1 f("f","[0]*x**2*exp(-x/[1])/(2*[1]**3)");
f.FixParameter(0,h.GetBinWidth(1)*h.GetEntries());
f.SetParameter(1,5);
h.Fit("f","L");
h.Draw();
cout <<"stima parametro = "<< f.GetParameter(1)<< " +/- "<< f.GetParError(1) << endl;
app.Run(true);

}