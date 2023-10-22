from ROOT import *
from math import *
import numpy as np
from scipy import stats	#per test kolmogorov

B=0.1
V=1E03
q=1.6E-19
cl=0.99 ##cioe' significativita' 0.05
data=np.array([])

h=TH1D("Spettrometro","Spettrometro",100,0.55,0.6)
file =open("Dati_Spettrometro.dat","r")
for line in file:
	h.Fill(double(line))
	data=np.append(data,double(line))

'''MyFit=stats.norm.fit(data)								##NO! LA CARDINALE DICE CHE KOLMOGOROV NON SI PUO'
t,p=stats.kstest(data,stats.norm(MyFit[0],MyFit[1]).cdf)	##USARE SE USO I DATI PER STIMARE I PARAMETRI
print "prob k-test", p'''
h.Fit

h.GetXaxis().SetTitle("diametro")
h.GetYaxis().SetTitle("occorrenze")

f=TF1("f","[2]*TMath::Gaus(x,[0],[1],1)",0.55,0.6)
f.SetParameter(0,0.5)
f.SetParameter(1,0.005)
f.SetParameter(2,h.Integral("width"))
h.Fit("f","LR")												##fit con L per test di ipotesi

print "prob Likelihood=", f.GetProb(), "\n"

if(f.GetProb()<1-cl):
	print "ipotesi singola gaussiana rigettata"
else:
	print "ipotesi singola gaussiana accettata con CL", cl


g=TF1("g","[0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,[4],[5],1)",0.5,0.6)
g.SetParameter(0,0.3)
g.SetParameter(1,0.6)
g.SetParameter(2,0.05)
g.SetParameter(3,0.6)
g.SetParameter(4,4)
g.SetParameter(5,0.03)

#g.SetParameter(0,h.Integral("width"))
#h.Fit("g","LR")
h.Draw()
gApplication.Run(True)	
