'''il file di dati expo_lowstat.dat contiene una serie di misure di tempi di decadimento di una certa
sostanza radioattiva.
Si calcoli il p-value dell'ipotesi H0 per cui i dati sono descritti da un singolo esponenziale del tipo
1/tau * exp(-t/tau) con tau=2s
Avendo acquisito lo stesso processo per piu' tempo (expo_highstat.dat) si effettui un binned likelihood 
fit (non extended) alla distribuzine dei tempi con una funzione somma di due esponenziali, determinando
e stampando su schermo tau1 e tau2 e la frazione di eventi descritti da ciascun esponenziale'''



from ROOT import *
import numpy as np
import math as m
from scipy import stats

data=np.array([])
hlow=TH1D("lowstat","lowstat",20,0,4)
file=open("expo_lowstat.dat")
for line in file:
	data=np.append(data,double(line))		##kolmogorov vuole un array in input
	hlow.Fill(double(line))


t,p=stats.kstest(data,stats.expon(0,2).cdf)
print "p-value H0 lowstat=", p

##highstat
data2=np.array([])


c=TCanvas()



file2=open("expo_highstat.dat")
for line in file2:								##prima salvo i dati in un array
	data2=np.append(data2,double(line))
	#hhigh.Fill(double(line))
max=np.max(data2)								##trovo il massimo
print "ndati", len(data2)
print "max=",
hhigh=TH1D("highstat","highstat",200,0,max+2)	##creo l'istogramma con il range giusto
for i in range(0,len(data2)):
	hhigh.Fill(data2[i])
hhigh.Draw()

f=TF1("f", "[0]*([1]*(1/[2])*exp(-x/[2])+(1-[1])*(1/[3])*exp(-x/[3]))",0,40)
f.FixParameter(0,1)												##per fit non extended la norm=1
f.SetParameter(1,0.2)		##p1
f.SetParameter(2,2)			##tau1
f.SetParameter(3,400)		##tau2

f.SetParName(0,"norm")
f.SetParName(1,"p1")
f.SetParName(2,"#tau_1")
f.SetParName(3,"#tau_2")


hhigh.Fit("f","0MULTI")
f.SetParameter(0,hhigh.GetEntries()*hhigh.GetBinWidth(1))		##dopo, per graficare, normalizzo
print hhigh.GetEntries()*hhigh.GetBinWidth(1), "\t",hhigh.Integral("width")
f.Draw("SAME")
c.SetLogy()

print "tau1=", f.GetParameter(2), "+/-", f.GetParError(2)
print "frequenza tau1=", f.GetParameter(1)
print "tau2=", f.GetParameter(3), "+/-", f.GetParError(3)
print "frequenza tau2=", 1-f.GetParameter(1)
gApplication.Run(True)


