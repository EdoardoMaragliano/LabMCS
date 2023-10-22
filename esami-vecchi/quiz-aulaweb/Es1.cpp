#include "classe.h"
#include <iostream>
#include <TApplication.h>

using namespace std;

int main(){
//"TMath::Gaus(x,[1],[2],0)
	TApplication App("app",0,NULL);
	TF1 f("f","TMath::Log(x)",0,10);
	Derivative2 der(f);
	
	/*der.SetParameter(1,1);
	der.SetParameter(2,1);
	der.SetParameter(3,1);*/
	der.Draw();
	double val=der.Compute(0.5,0.001);
	cout <<"2der "<< val<< endl;
	double d=f.Derivative2(0.5);
	cout << "der con root=" << d << endl;
	App.Run(true);

	return 0;
}