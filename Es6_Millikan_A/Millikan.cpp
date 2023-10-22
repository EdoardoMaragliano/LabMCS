#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TMinuit.h>

using namespace std;

namespace data{ //dati presi dal logbook, uno per ciascun rapporto
		
	double eq_millikan, q_millikan;
	double he=	5.7E-15;
	double ehe=	0.6E-15;
	double hk=	4.7256E-11;	
	double ehk=	2.55506E-12;
	double ke= 	11613;
	double eke= 50;
}


void fcn(int &npar, double *gin, double &f,double *par, int iflag){
	f=0;
	
	f+=pow((par[1]/par[0]-data::he)/data::ehe,2);
	f+=pow((par[1]/par[2]-data::hk)/data::ehk,2);
	f+=pow((par[0]/par[2]-data::ke)/data::eke,2);
	f=f+pow((par[0]-data::q_millikan)/data::eq_millikan,2);
}


int main(){

	double real_e=1.602E-19;
	double real_h=6.626E-34;
	double real_k=1.3806E-23;

	ifstream dataMillikan; 

	dataMillikan.open("Millikan.dat");
	
	
	double appo;

	TApplication app("app",0,NULL);
  	gStyle->SetOptStat(0);
	TCanvas c("c","Carica elettrone",10,10,500,500);
	TH1D histo("Millikan","Millikan",100,0,15);

	//cout << "inizio importazione Millikan" << endl;	//debug

	while(dataMillikan >> appo ){
		histo.Fill(appo);
	}
	//cout << "dati importati" << endl;					//debug
	dataMillikan.close();

	TF1 g("g","[0]*([3]*TMath::Gaus(x,[1],[2],1)+[4]*TMath::Gaus(x,2*[1],[2],1)+(1-[3]-[4])*TMath::Gaus(x,3*[1],[2],1))",0,5.5);
	
		g.SetParameter(0,4);
		g.SetParameter(1,2);
		g.SetParameter(2,0.4);
		g.SetParameter(3,0.3);
		g.SetParameter(4,0.4);
		g.SetParName(1,"mu");
		g.SetParName(2,"sigma");
		g.SetParName(0,"global");
		g.SetParName(3,"A1");
		g.SetParName(4,"A2");

	histo.Draw();
	histo.Fit("g","LR");
	gPad->Modified(); gPad->Update();


	data::q_millikan=g.GetParameter(1)*pow(10,-19);
	data::eq_millikan=g.GetParameter(2)*pow(10,-19);

	cout << "carica dell'elettrone= (" << data::q_millikan << " +/- " << data::eq_millikan << ") C" << endl;

	cout << "per proseguire file -> quit root"<<endl;
	app.Run(true);

	//fit simultaneo dei dati
	//importo i dati

	cout << "**********************************************" << endl;
	cout << "**********************************************" << endl<<endl;


	TMinuit *minuit=new TMinuit(3);
	minuit->SetFCN(fcn);
	minuit->DefineParameter(0,"e",1.6E-19,1E-21,0.,0.); 		//ho messo step \simeq 0.001*misura
	minuit->DefineParameter(1,"h",6.6E-34,1E-37,0.,0.);			//altrimenti venivano errori tipo
	minuit->DefineParameter(2,"k",1.3E-23,1E-26,0.,0.);			//matrice errori non def pos

	minuit->Command("MIGRAD");

	double e, sigmae, k, sigmak, h, sigmah;

	minuit->GetParameter(0,e,sigmae);
	minuit->GetParameter(1,h,sigmah);
	minuit->GetParameter(2,k,sigmak);

	cout << endl << "**********************************************" << endl <<endl;
	cout << "migliori stime per e,h,k: " << endl << endl;

	cout << "e= "<< e << " +/- " << sigmae << endl;
	cout << "h= "<< h << " +/- " << sigmah << endl;
	cout << "k= "<< k << " +/- " << sigmak << endl;
	
	cout << endl << "**********************************************" << endl <<endl;

//siamo entro 2\sigma dal valore vero per cui direi che ci siamo

	TCanvas *c1= new TCanvas("c1","contour",10,10,600,800);
	c1->Divide(2,2);
	c1->cd(1);
	TGraph *gr1= new TGraph;
	gMinuit->SetErrorDef(2.3);
	gr1=(TGraph*)minuit->Contour(70,0,1);		//devo fare il cast da TObject* a TGraph*
	gr1->SetTitle("h/e");
	gr1->SetMarkerStyle(5);
	gr1->GetXaxis()->SetTitle("e [C]");
	gr1->GetYaxis()->SetTitle("h [Js]");
	gr1->Draw("AC");

	TGraph *gr4=new TGraph;
	gr4->SetPoint(gr4->GetN(),real_e,real_h);
	gr4->SetMarkerColor(4);
	gr4->SetMarkerSize(1);
	gr4->SetMarkerStyle(8);
	gr4->Draw("P");

	c1->cd(2);
	TGraph *gr2= new TGraph;
	gMinuit->SetErrorDef(2.3);			//nota bene: DeltaChi2 = 1 da' 68% con 1 GDL, con 2 GDL devo mettere
	gr2=(TGraph*)minuit->Contour(70,2,0);	//DeltaChi2=2.3
	gr2->SetTitle("e/k");
	gr2->SetMarkerStyle(5);
	gr2->GetXaxis()->SetTitle("k [J/K]");
	gr2->GetYaxis()->SetTitle("e [C]");
	gr2->Draw("AC");

	TGraph *gr5=new TGraph;					//non so perche' ma non viene stampato
	gr5->SetPoint(gr5->GetN(),real_k,real_h);
	gr5->SetMarkerColor(4);
	gr5->SetMarkerSize(1);
	gr5->SetMarkerStyle(8);
	gr5->Draw("P");
	

	c1->cd(3);
	TGraph *gr3= new TGraph;
	gMinuit->SetErrorDef(2.3);
	gr3=(TGraph*)minuit->Contour(70,2,1);
	gr3->SetTitle("h/k");
	gr3->SetMarkerStyle(5);
	gr3->GetXaxis()->SetTitle("k [J/K]");
	gr3->GetYaxis()->SetTitle("h [Js]");
	gr3->Draw("AC");

	TGraph *gr6=new TGraph;						//non so perche' ma non viene stampato
	gr6->SetPoint(gr6->GetN(),real_k,real_e);
	gr6->SetMarkerColor(4);
	gr6->SetMarkerSize(1);
	gr6->SetMarkerStyle(8);
	gr6->Draw("P");
	
	
	gPad->Modified(); gPad->Update();

	app.Run(true);

	return 0;
}