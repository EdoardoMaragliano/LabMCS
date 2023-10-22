{
	TRandom3 rnd;
	rnd.SetSeed(123456);

	int nacc=0.0;
	int nacc2=0.0;
	int ntot=10000000;
	
	L=0.2;
	d=0.2;

	for(int i=0;i<1000;i++){
		double phi = 2*TMath::Pi()*rnd.Rndm();
		double coseno = 2*rnd.Rndm()-1;
		double theta  = acos(coseno);

		if(theta<TMath::Pi()/2){
			TVector3 vers(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
			double alpha=d/cos(theta);
			TVector3 v= vers * alpha;

			if(abs(v.X())<L/2 & abs(v.Y())<L/2){
				nacc++;
			}
			if(v.X()<L && v.X()>0 && v.Y()<L && v.Y()>0){
				nacc2++;
			}
		}
	}

	double p=nacc/ntot;
	double ep=sqrt(p*(1-p)/ntot);
	double p2=nacc2/ntot;
	double ep2=sqrt(p2*(1-p2)/ntot);


	cout <<"p " << p << " +/- " << ep << endl;
	cout << L*L/(4*TMath::Pi()*d*d) << endl;
	cout <<"p2 " << p2 << " +/- " << ep2 << endl;


}