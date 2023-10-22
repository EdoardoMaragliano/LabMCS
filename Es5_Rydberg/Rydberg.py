

from   ROOT import *
from   math import *
import numpy as np
import time 

#Parametri e misure

meanA=1.7298
sigmaA=0.0003
meanB=13462
sigmaB=58
corrAB=-0.876
th0=1.5701

alpha   = pi/3

eth     = 0.0005
sigmath = eth/sqrt(3)

#Funzioni 

def getLambda(theta,th0,A,B):
	n=sin((theta-th0+alpha)/2)/sin(alpha/2)		##refraction indexes
	l=sqrt(B/(n-A))
	return l	

#Main

theta=np.array([2.6773,2.7324,2.7651,2.7846]) ##red green blue violet

#n=np.array([])
l=np.array([])


for i in range(0,4):
	#n=np.append(n,sin((theta[i]-th0+alpha)/2)/sin(alpha/2))		##refraction indexes					
	l=np.append(l,getLambda(theta[i],th0,meanA,meanB))					##wavelenghts

##print("refraction indexes \n"), n
print("wavelenghts \n"), l

##preparo creazione del grafico per il fit per R_H

j=2					##livello energetico 2 dell'idrogeno, lettera n gia occupata
xaxis=np.array([3,4,5,6])		##array con le coord x

can=TCanvas()
can.Divide(2,2)

##considero solo errori sugli angoli th_i
can.cd(1)
can.SetTitle("Costante di Rydberg")
gr	= TGraphErrors ()						
gr.SetTitle("errori sugli angoli #theta_{i}")
gr.GetXaxis().SetTitle("m")
gr.GetYaxis().SetTitle("#lambda")

sigmaY=np.array([])						##array con gli errori su y
for i in range(0,4):
	sigmaY=np.append(sigmaY,getLambda(theta[i]+sigmath,th0,meanA,meanB)-l[i])

	gr.SetPoint(i,xaxis[i],l[i])
	gr.SetPointError(i,0,sigmaY[i])


gr.Draw("AP");	
f=TF1("f","1/([1]*(1/[0]^2-1/x^2))",0,10)
f.SetParName(1,"Rh")
f.SetParName(0,"n")
f.FixParameter(0,2)
f.SetParameter(1,0.01)
gr.Fit("f")
Rh_angoli=f.GetParameter(1)
sigmaRh_angoli=f.GetParError(1)



##errori su A e B e th0

grA	= TGraphErrors ()	
grB = TGraphErrors ()	
grTh0 = TGraphErrors ()

for i in range(0,4):
	sigmaYA=getLambda(theta[i],th0,meanA+sigmaA,meanB)-l[i]
	sigmaYB=getLambda(theta[i],th0,meanA,meanB+sigmaB)-l[i]
	sigmaYth0=getLambda(theta[i],th0+sigmath,meanA,meanB)-l[i]

	grA.SetPoint(i,xaxis[i],getLambda(theta[i],th0,meanA+sigmaA,meanB))
	grA.SetPointError(i,0,sigmaYA)
	grB.SetPoint(i,xaxis[i],getLambda(theta[i],th0,meanA,meanB+sigmaB))
	grB.SetPointError(i,0,sigmaYB)
	grTh0.SetPoint(i,xaxis[i],getLambda(theta[i],th0+sigmath,meanA,meanB))
	grTh0.SetPointError(i,0,sigmaYth0)

can.cd(2)
grA.SetTitle("errori su A")
grA.GetXaxis().SetTitle("m")
grA.GetYaxis().SetTitle("#lambda")
grA.Draw("AP");
grA.Fit("f")
RhA=f.GetParameter(1);
sigmaRh_A=f.GetParError(1)

can.cd(3)
grB.SetTitle("errori su B")
grB.GetXaxis().SetTitle("m")
grB.GetYaxis().SetTitle("#lambda")
grB.Draw("AP");
grB.Fit("f")
RhB=f.GetParameter(1);
sigmaRh_B=f.GetParError(1)

can.cd(4)
grTh0.SetTitle("errori su #theta_{0}")
grTh0.GetXaxis().SetTitle("m")
grTh0.GetYaxis().SetTitle("#lambda")
grTh0.Draw("AP");
grTh0.Fit("f")
RhTh0=f.GetParameter(1);
sigmaRh_th0=f.GetParError(1)


sigmaRh_AB=sqrt((Rh_angoli-RhA)**2+(Rh_angoli-RhB)**2+2*corrAB*(RhA-Rh_angoli)*(RhB-Rh_angoli))
sigmaRh_Tot=sqrt(sigmaRh_angoli**2+sigmaRh_AB**2+(RhTh0-Rh_angoli)**2)

print ("\n")
print ("------------------------")
print ("\n")


print ("contributo da AB"), sigmaRh_AB
print ("contributo da th0"), abs(RhTh0-Rh_angoli)
print ("contributo da th_i"), sigmaRh_angoli


print ("Miglior stima per Costante di Rydberg: "), Rh_angoli,("+/-"),sigmaRh_Tot

gApplication.Run(True)

