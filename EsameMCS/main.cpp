#include <iostream>
#include <vector>
#include "poly.h"

int main(){

	poly pol(0);
	cout << pol.eval(4) << endl;
	poly pol1(1,2);
	cout << endl << "1+2x, x=2 \t" << pol1.eval(2) << endl;
	poly pol2(1,2,1);
	cout << endl << "1+2x+x^2, x=2 \t" << pol2.eval(2) << endl;
	poly pol3(5,2,2,1);
	cout << endl << "5+2x+2x^2+x^3, x=2 \t" << pol3.eval(2) << endl;
	poly pol4(3,4);

	poly sum=pol1+pol4;
	 cout << endl << " 4+6x, x=2 \t "<< sum.eval(2) << endl;
	poly sum2=pol1+pol2;
	cout << endl << "2+4x+x^2, x=2 \t " << sum2.eval(2) << endl;

	return 0;
}