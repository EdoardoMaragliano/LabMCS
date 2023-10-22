'''Partendo dal file con i dati dell'esperimento di Millikan.dat, e limitandosi alla regione di carica 
a cui e' sensibile l'esperimento (circa (0,5.5) in unità di 10-19)

    si calcoli, immaginando che i dati siano acquisiti in sequenza, dopo quanti dati si 
    può escludere al 99% di C.L. l'ipotesi nulla 
    che la distribuzione sia uniforme (si usi il test di Kolmogorov) ? 
    Suggerimento: impostare il test d'ipotesi per i primi n dati, quindi variare n.

    Si usi: kstest

    si esegua il fit binned (compito sesta esercitazione) e unbinned estraendo il valore 
    di carica dell'elettrone. Tavola riassuntiva dei metodi di ROOT per fit di likelhood

Binned 											 Unbinned
Likelihood 				 Fit + opzione MULTI  	 TTree + metodo UnbinnedFit 
Extended Likelihood   	 Fit + opzione L 	                         -


    Per poter eseguire allo stesso tempo fit extended e normali occorre scrivere la funzione 
    in modo che possa essere al tempo stesso una funzione o una pdf

         f(x) = γ( αG(x,q,σ) + βG(x,2q,σ) + (1-α-β)G(x,3q,σ) )

    (se γ=1 f(x) è una pdf, se γ=area_istogramma è una funzione con la stessa area dell'istogramma)'''



from ROOT import *
import numpy as np
import math as m
from scipy import stats

##main
cl=0.99

data=np.array([])
histo= TH1D("Millikan","Millikan",100,0,15)
f= TF1 ("f","[0]*([3]*TMath::Gaus(x,[1],[2],1)+[4]*TMath::Gaus(x,2*[1],[2],1)+(1-[3]-[4])*TMath::Gaus(x,3*[1],[2],1))",0,5.5)
f.SetParameter(0,3)
f.SetParameter(1,2)
f.SetParameter(2,0.4)
f.SetParameter(3,0.3)
f.SetParameter(4,0.4)
f.SetParName(1,"mu")
f.SetParName(2,"sigma")
f.SetParName(0,"global")
f.SetParName(3,"A1")
f.SetParName(4,"A2")



##c=TCanvas ("c","",10,10,500,500)

file = open ("Millikan.dat","r")
for line in file:
	data=np.append(data,float(line))
	histo.Fill(float(line))
	t,p=stats.kstest(data,'uniform',args=(0,5.5))
	if(len(data)>3):
		if(p<1-cl):
			print("numero dati", len(data))
	

histo.Draw()
histo.Fit("f","LR")		##L fa un fit di likelihood, altrimenti fa un chi2 che pero' va bene solo se in ogni bin
gPad.Modified()			##ho abbastanza dati da approssimare Poisson con Gauss
gPad.Update()

mu_bin=f.GetParameter(1)
sigma_bin=f.GetParameter(2)

tree=TTree()
tree.ReadFile("Millikan.dat","q")
f.FixParameter(0,1)			##questo fit e' unbinned quindi devo mettere a 1 il parametro di normalizzazione globale
tree.UnbinnedFit("f","q","q<5.5")

mu_unbin=f.GetParameter(1)
sigma_unbin=f.GetParameter(2)

gApplication.Run(True)





