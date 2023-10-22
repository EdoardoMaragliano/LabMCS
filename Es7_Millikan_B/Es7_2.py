'''Si vuole stabilire se tra gli eventi registrati in un esperimento ci sia evidenza di qualche "nuovo" 
processo (segnale) rispetto ai processi noti (fondo)

Si assuma che, in qualche variabile:

il fondo abbia distribuzione esponenziale
il segnale (se presente) si accumuli intorno a 15 (unità arbitrarie) secondo una distribuzione gaussiana
l'intervallo di dati "interessante" (individuato a priori da considerazioni sperimentali e/o da motivazioni teoriche) è [14,16] (di nuovo in unità arbitrarie)
un esperimento abbia raccolto, in sequenza, una campione di dati a bassa statistica (dati_lowstat.dat) e uno ad alta statistica (dati_highstat.dat)

Utilizzando il file a bassa statistica (dati_lowstat.dat):
-si calcoli la probabilità che il fondo aspettato ( Nb = 22.35) possa fluttuare fino a raggiungere 
un valore maggiore o uguale rispetto al numero totale di eventi osservato Nobs nell'intervallo [14,16]  
(P(N≥Nobs|Nb), dove P è la probabilità poissiana)). Si usi la function TMath::PoissonI
-Si dica se l'ipotesi che, nell'intervallo dato, i dati siano descritti dalle sole combinazioni 
casuali possa essere rigettata o meno. Si assuma come livello di significanza del test 0.01.'''

from ROOT import *
import numpy as np
import math as m
from scipy import stats

##main
acc=0.01
conta=0

data=np.array([])
histo= TH1D("Segnale-fondo-lowstat","Segnale-fondo-lowstat",100,0,50)


file = open ("dati_lowstat.dat","r")
for line in file:
	if(float(line)<16):
		if(float(line)>14):
			conta=conta+1
	histo.Fill(float(line))

print ("numero dati tra 14 e 16=",conta)
sum=0
atteso=22.35
for i in range(0,conta+1):
	sum+=TMath.PoissonI(i,atteso)		#integro Poisson da 0 a Nobs

p=1-sum									#p(N>Nobs)
print("prob=",p)

if(p<acc):
	print "rigetto l'ipotesi nulla"

	

histo.Draw()

gPad.Modified()			
gPad.Update()


##gApplication.Run(True)





