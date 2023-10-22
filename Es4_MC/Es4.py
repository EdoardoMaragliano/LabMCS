'''    Simulare il processo di un decadimento di una sostanza radioattiva con tempi di decadimento τ1  e τ2 
la cui funzione di densita' di probabilita' a' data da 
f1/tau1 * exp(tau1) + 1/tau2 * (1-f1)*exp(tau2)
      
con τ1  = 0.1 s e τ1  = 1 s e f = 0.3 e rappresentate i tempi di decadimento in un istogramma. 

'''

from ROOT import *
import numpy as np 
import random
import math as m

##problema 1: decadimento. somma di pdf esponenziali

rnd = TRandom3()
rnd.SetSeed(12345678)
ntot = 1000
##parametri della pdf
f=0.3
tau1=0.1
tau2=1
tau=0.
tacc=0.1

h=TH1D("h","",100,0,3)
hm=TH1D("hm","",100,0,3)
for i in range(0,ntot):
	if rnd.Rndm()<f:
		tau=tau1
	else:
		tau=tau2
	t=-tau*m.log(1-rnd.Rndm())
	#t=rnd.Exp(tau) #usa il metodo predefinito di root

##la probabilita di essere rivelato al tempo t e' 0 per t=0 e tende a 1 per t>>1,
##secondo la legge 1-exp(-t/tacc)
	if rnd.Rndm()<(1-m.exp(-t/tacc)):
		hm.Fill(t)
	h.Fill(t)

h.Draw()
hm.Draw("SAME")
hm.SetLineColor(2)

gApplication.Run(True)


