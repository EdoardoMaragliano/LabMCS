#ifndef _DERIVATIVE2
#define _DERIVATIVE2

#include <TF1.h>
#include <cmath>
#include <iostream>


class Derivative2: public TF1{
	public:
		using TF1::TF1;
		Derivative2(TF1 f=TF1()): TF1(f),m_h(0.0001) {}
		

		double Compute(double,double);
	private:
		double Der(double,double);
		double m_h;

};

#endif