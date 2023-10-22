//metodo di Buffon per il calcolo di pigreco
//Edoardo Maragliano 2 feb 2021
{
	TRandom3 rnd;
	rnd.SetSeed(123456789);
	double d=10;
	double L=10;
	int N=100000000;
	int Nfav=0;
	for(int i=0;i<N;i++){
		double x=0.5*d*rnd.Rndm();
		double phi=TMath::Pi()*rnd.Rndm();
		if(x<L/2*TMath::Sin(phi)){
			Nfav++;
		}
	}	
	double stima=2*L/d*float(N)/Nfav;
	cout << stima << endl;

}