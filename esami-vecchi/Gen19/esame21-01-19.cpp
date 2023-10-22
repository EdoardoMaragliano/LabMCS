#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TRandom2.h>
#include <TF1.h>
#include <iostream>
#include <cmath>

using namespace std;

int main(){

TApplication app("app",0,NULL);

TRandom2 rnd;

double l = 1;					
double r=l	;			
int dim=4	;				
double norm=pow((2*l),dim)/pow(r,dim);
double N=1E09;
double fav=0.0;
double alpha=0.0;
double atteso=pow(TMath::Pi(),dim/2)/TMath::Gamma(dim/2+1);
double delta=0.0;
cout << "valore atteso per alpha " << atteso << endl << endl;
double x,y,z,w;
 
TGraph gr;
gr.SetTitle("grafico");
gr.GetXaxis()->SetTitle("N");
gr.GetYaxis()->SetTitle("alpha");

rnd.SetSeed(12345);

for(int i=1;i<N;i++){
	x=l-2*l*rnd.Rndm()	;		
	y=l-2*l*rnd.Rndm()	;				
	z=l-2*l*rnd.Rndm()	;
	w=l-2*l*rnd.Rndm()	;
	double d=x*x+y*y+z*z+w*w	;
	

	if (d<=r*r){
		fav=fav+1;
		alpha=(fav/N)*norm;
		delta=atteso-alpha;
		if(i%1000000==0){
			cout <<  alpha << endl;
			gr.SetPoint(gr.GetN(),i,alpha);
		}
	}
}

cout <<  alpha << endl;
cout << gr.GetN() << endl;
TCanvas *c1= new TCanvas("c1","Grafico",10,10,500,500);
c1->SetLogx();
gr.Draw("AP");
app.Run(true);

	return 0;
}

