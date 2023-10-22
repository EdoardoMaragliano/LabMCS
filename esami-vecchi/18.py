'''Si estragga un campione di valori x che segua la distribuzione
f(x|θ) =|θx^(θ−1) 0<x<1
        | 0        x≤0
con θ= 3.  Dato il campione di eventi e assumendo θ incognito se ne determini il valore con il metodo di maximum likelihood unbinned.'''

from ROOT import *
import numpy as np
import math as m
from scipy import stats
import time 

rnd = TRandom3() 
rnd.SetSeed(int(time.time()))

data=np.array([]) ##vector dove metto i valori estratti dalla distribuzione

h=TH1D("h","istogramma",100,0,0)
a=TF1("a","3*x^2",0,1) ##funzione con theta noto

for i in range(0,1000):
    tmp=a.GetRandom() 
    data=np.append(data,tmp) ##riempo array
    h.Fill(tmp)
h.Draw()

with open("data.dat","w") as filehandle: ##metto gli elementi del mio array in un file .dat 
    for listitem in data:
        filehandle.write("%s\n" % listitem)

f=TF1("f","[0]*x^([0]-1)",0,1)

tree=TTree()
tree.ReadFile("data.dat","q")

f.SetParameter(0,3)
tree.UnbinnedFit("f","q")

print("theta=",f.GetParameter(0),"+/-",f.GetParError(0))

gPad.Modified()
gPad.Update()
gApplication.Run(True)
