#include <iostream>
#include <vector>
#include "poly.h"

double poly::eval(double x){
if(this->size()==1)
	return 0;
else if(this->size()==2)
	return this->at(0)+x*this->at(1);
else if(this->size()==3)
	return this->at(0)+x*this->at(1)+x*x*this->at(2);
else if(this->size()==4)
	return this->at(0)+x*this->at(1)+x*x*this->at(2)+x*x*x*this->at(3);

}

poly poly::operator+(const poly& b) const{ //somma

	double v[4];
	for(int i=0;i<4;i++)
		v[i]=0;

	if (this->size()<=b.size()){

		for(int i=0;i<this->size();i++)
			v[i]=this->at(i)+b.at(i);
		for(int j=this->size();j<b.size();j++)
			v[j]=v[j]+b.at(j);
	}

	else {
		for(int i=0;i<b.size();i++)
			v[i]=this->at(i)+b.at(i);
		for(int j=b.size();j<this->size();j++)
			v[j]=v[j]+this->at(j);

	}

	return poly(v[0],v[1],v[2],v[3]); 

}

/*poly poly::operator+(const poly& b) const{ //somma

	if(this->size()!=b.size()){
		cout << "gradi diversi, ritorno polinomio nullo" << endl;
		return poly(0);
	}
	else{
		
		double v[4];
		for(int i=0;i<4;i++)
			v[i]=0;

		for(int i=0;i<this->size();i++){
			v[i]=this->at(i)+b.at(i);
		}

		return poly(v[0],v[1],v[2],v[3]); 
	}
 	 
}*/