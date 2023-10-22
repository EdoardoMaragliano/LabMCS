#ifndef _POLY
#define _POLY

#include <vector>

using namespace std;

class poly: public vector<double>{

public:
	using vector::vector;
	poly(int n=0):vector<double>{0} {}						//pol nullo, size 1
  	poly(double p0, double p1):vector<double>{p0,p1}{}		//pol gr 1, size 2 
   	poly(double p0, double p1, double p2):vector<double>{p0,p1,p2}{}		//pol gr2
   	poly(double p0, double p1, double p2, double p3):vector<double>{p0,p1,p2,p3}{}		//pol gr3
   	poly operator+(const poly& b) const;

   	double eval(double);

private:
	//vector <double> m_v;
};



#endif