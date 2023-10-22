'''In un esperimento, in una certa regione di interesse, si osservano 30 eventi (attesi 15).  
si puo rigettare l'ipotesi nulla al 5 % di significanza? qual e' l'intervallo al 95% CL
del numero di eventi in eccesso ?'''

from ROOT import*
import numpy as np
from math import*

n_att=15
n_obs=30

Prob=0
for i in range(0,n_obs):							##integra da 0 a n_obs
    Prob=Prob+TMath.PoissonI(i,n_att)
p_value=1-Prob 										##integrale da n_obs a +inf
print ("il p_value vale=",p_value)

if p_value>1 or p_value<0.05:
    print("ipotesi rigettata al 5% di significanza")	
else:
    print("ipotesi non rigettata al 5% di significanza")

"""Prob2=0
while p_value<0.5:
    for j in range(n_obs,,-1):
        Prob2=Prob2+TMath.PoissonI(j,nbkg)
        p_value=1-Prob2
"""
#Voglio trovare quanti eventi devo osservare per avere 95% CL

Prob1=0
j=0
while(Prob1<0.95):
    j=j+1
    Prob1=Prob1+TMath.PoissonI(j,n_att)

print ("numero dati per avere il 95% di Cl=", j)
