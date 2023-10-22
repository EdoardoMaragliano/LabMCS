{
	TRandom3 rnd;
	rnd.SetSeed(12345678);
	double R=1;
	int	ntot=100000;
	double nacc=0.0;

	for(int i=1;i<ntot;i++){
		double x=rnd.Rndm()*2-1; //x tra -1 e 1
		double y=rnd.Rndm()*2-1;
		double z=rnd.Rndm()*2-1;
		double r=sqrt(x*x+y*y+z*z);
		double rho=sqrt(x*x+y*y);
		if(r<R && rho>R/2)
			nacc++;
	}
	cout << (4/3.)*TMath::Pi()*pow(R,3) << endl;	//volume ideale
	cout << (nacc/ntot)*pow(2*R,3) << endl;	//volume numerico
}