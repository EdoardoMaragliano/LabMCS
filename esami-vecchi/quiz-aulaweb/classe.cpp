#include "classe.h"

using namespace std;


double Derivative2::Der(double x,double h){
	return (this->Eval(x+h)+this->Eval(x-h)-2*this->Eval(x))/(h*h);
	//cout << "Der restituisce " << (this->Eval(x+h)+this->Eval(x-h)-2*this->Eval(x))/(h*h)<<endl;

}
double Derivative2::Compute(double x,double p){
	cout << endl << "calcolo derivata seconda in x=" << x << endl;
	cout << "precisione="<<p<<endl;
	double der=Derivative2::Der(x,m_h);
	double epsilon=abs(Derivative2::Der(x,m_h)-Derivative2::Der(x,m_h-0.001*m_h));
	//cout << "eps " << epsilon << endl;
	while(epsilon>p){
		m_h=m_h-0.001*m_h;
		der=Derivative2::Der(x,m_h);
		epsilon=abs(Derivative2::Der(x,m_h)-Derivative2::Der(x,m_h-0.001*m_h));
		
	}
	return der;
}