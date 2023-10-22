'''Con il campione ad alta statistica:
-calcolare il limite superiore (al 95% C.L.) al numero di eventi di segnale osservati usando il numero 
di eventi totali nell'intervallo [14,16] e assumendo che il numero atteso di eventi di fondo 
combinatorio siano 44.7;
-eseguire un fit (binned e unbinned) dei dati assumendo come pdf la distribuzione somma di quella di
segnale e di quella di fondo (tutti i parametri sono liberi eccetto la larghezza della gaussiana). 

'''

from ROOT import *
import numpy as np
import math as m
from scipy import stats

##main
acc=0.05
conta=0

data=np.array([])
histo= TH1D("Segnale-fondo-highstat","Segnale-fondo-highstat",100,0,50)


file = open ("dati_highstat.dat","r")
for line in file:
	if(float(line)<16):
		if(float(line)>14):
			conta=conta+1
	histo.Fill(float(line))

print ("numero dati tra 14 e 16=",conta)
sum=0
atteso=44.7
for i in range(0,conta+1):
	sum+=TMath.PoissonI(i,atteso)		##PoissonI(x,mean)

p=1-sum
print("p=",p)

if(p<acc):
	print "rigetto l'ipotesi nulla \n "

#########

print "calcolo massimo valore di Nobs compatibile con Poisson di media Natteso \n "


Nmax=int(atteso)		##mi aspetto che Nmax sia maggiore di Natteso
p=1						##generico valore maggiore di acc

while(p>acc):
	sum=0	##inizializzo l'integrale della pdf

	for i in range(0,Nmax+1):			##integro da 0 a Nmax incluso in ogni ciclo while(cambiando l'estremo)
		sum+=TMath.PoissonI(i,atteso)	##p(n<Nmax)
	print "sum=", sum	
	p=1-sum								##p(n>Nmax), lo voglio <5%
	Nmax=Nmax+1	
	print "p= ", p 			##debug
	print "Nmax= ", Nmax		##debug


print "Nobs max=", Nmax

##verifica che quanto sopra sia corretto

print "\n eseguo verifica con Nmax=", Nmax
sum=0
for i in range(0,Nmax):
	sum+=TMath.PoissonI(i,atteso)

p=1-sum			#p=p(n>Nmax)
print("p=",p)

if(p<acc):
	print "rigetto l'ipotesi nulla"
else:
	print "non rigetto l'ipotesi nulla"
	

f= TF1 ("f", "[0]*([1]*TMath::Gaus(x,[2],[3],1)+(1-[1])*[4]*exp(-x*[4]))",0,50)
f.SetParameter(0,histo.Integral("width"))		##normalizzazione globale
f.SetParameter(1,0.8)							##peso gaussiana
f.SetParameter(2,15)		##media
f.FixParameter(3,0.5)		##RMS fissata come da consegna, ma a quale valore? Ho messo 0.5
f.SetParameter(4,2)			##in modo che in (14,16) ci sia +/- 2sigma, cioe' 95%

f.SetParName(2,"mu");
f.SetParName(3,"sigma");
f.SetParName(0,"global");
f.SetParName(1,"A1");
f.SetParName(4,"lambda");

histo.Draw()
histo.Fit("f","LR")				##fit binned

gPad.Modified()			
gPad.Update()

tree=TTree()
tree.ReadFile("dati_highstat.dat","q")
f.FixParameter(0,1)
f.FixParameter(3,0.5)
tree.UnbinnedFit("f","q")		##fit unbinned


gApplication.Run(True)





