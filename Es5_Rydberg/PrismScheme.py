

from   ROOT import *
from   math import *
import numpy as np
import time 

#Parametri e misure
lambda1 = 579.1
lambda2 = 404.7
alpha   = pi/3
th0     = 1.5701
th1     = 2.6958
th2     = 2.7904
eth     = 0.0005
sigmath = eth/sqrt(3)



nsteps=20000 #numero iterazioni nel monte carlo

#Funzioni 
def GetAB(th0,th1,th2):

	delta1=th1-th0
	delta2=th2-th0

	n1=sin((delta1+alpha)/2)/sin(alpha/2)
	n2=sin((delta2+alpha)/2)/sin(alpha/2)

	A=n2-lambda1**2*(n1-n2)/(lambda2**2-lambda1**2)
	B=(n1-n2)*lambda1**2*lambda2**2/(lambda2**2-lambda1**2)
	v=np.array([A,B])
	return v

def getLambda(theta,th0,A,B):
	n=sin((theta-th0+alpha)/2)/sin(alpha/2)		##refraction indexes
	l=sqrt(B/(n-A))
	return l	

#Main
[A,B]=GetAB(th0,th1,th2)


##calcolo errori con variazione delle variabili indipendenti
e1 = GetAB(th0+sigmath,th1,th2)-GetAB(th0,th1,th2)
e2 = GetAB(th0,th1+sigmath,th2)-GetAB(th0,th1,th2)
e3 = GetAB(th0,th1,th2+sigmath)-GetAB(th0,th1,th2)
eA = sqrt(e1[0]**2+e2[0]**2+e3[0]**2)
eB = sqrt(e1[1]**2+e2[1]**2+e3[1]**2)
'''
print ("variazione a +sigma")
print "A= ",A,"+/-",eA
print "B= ",B, "+/-",eB
print ("e%A= ", eA/A)
print ("e%B= ", eB/B)
'''

##controllo l'effettiva linearita della funzione
e1 = GetAB(th0-sigmath,th1,th2)-GetAB(th0,th1,th2)
e2 = GetAB(th0,th1-sigmath,th2)-GetAB(th0,th1,th2)
e3 = GetAB(th0,th1,th2-sigmath)-GetAB(th0,th1,th2)
eA = sqrt(e1[0]**2+e2[0]**2+e3[0]**2)
eB = sqrt(e1[1]**2+e2[1]**2+e3[1]**2)
'''
print "\n variazion a -sigma"
print "A= ",A,"+/-",eA
print "B= ",B, "+/-",eB
print "e%A= ", eA/A
print "e%B= ", eB/B
'''

##genero dati 
rnd=TRandom3()
rnd.SetSeed(157346789)

distr='gaus'
print ("MonteCarlo basato su variabili gaussiane. Per modificare, riga 77 ")


##creo grafici
hA		= TH1D("A "+distr,"",100,A-4*eA,A+4*eA)
hB		= TH1D("B "+distr,"",100,B-4*eB,B+4*eB)
hCorr	= TH2D("A vs B "+distr,"",100,A-4*eA,A+4*eA,100,B-4*eB,B+4*eB)
hDelta  = TH2D("#delta_1 vs #delta_2 "+distr,"",100,0,5,100,0,5)
hN		= TH2D("n_1 vs n_2 "+distr,"",100,0,5,100,0,5)

for i in range(0,nsteps):

	if distr=="gaus":
		t0=rnd.Gaus(th0,sigmath)		##creo variabili gaussiane
		t1=rnd.Gaus(th1,sigmath)
		t2=rnd.Gaus(th2,sigmath)
	elif distr=="unif":					##creo variabili uniformi
		t0=(2*eth*rnd.Rndm()-eth)+th0
		t1=(2*eth*rnd.Rndm()-eth)+th1
		t2=(2*eth*rnd.Rndm()-eth)+th2

	delta1=t1-t0
	delta2=t2-t0

	n1=sin((delta1+alpha)/2)/sin(alpha/2)
	n2=sin((delta2+alpha)/2)/sin(alpha/2)


	[A,B]=GetAB(t0,t1,t2)
	hA.Fill(A)
	hB.Fill(B)
	hCorr.Fill(A,B)
	hDelta.Fill(delta1,delta2)
	hN.Fill(n1,n2)

'''
##disegno i grafici
c1=TCanvas()
c1.Divide(1,2)
c1.cd(1)
hA.Draw()
c1.cd(2)
hB.Draw()

c2=TCanvas()
hCorr.Draw()
c3=TCanvas()
hDelta.Draw()
c4=TCanvas()
hN.Draw()
'''

##ottengo valori dai grafici
meanA=hA.GetMean()
sigmaA=hA.GetRMS()
meanB=hB.GetMean()
sigmaB=hB.GetRMS()
corrAB=hCorr.GetCorrelationFactor()

corrDelta=hDelta.GetCorrelationFactor()
corrN=hN.GetCorrelationFactor()
print ("\n")
print ("valori ricavati da MonteCarlo")
print ("A = ") , meanA, ("+/-"), sigmaA
print ("B = ") , meanB, ("+/-"), sigmaB
print ("coeff correlazione AB= "), corrAB
print ("\n")
print ("coeff correlazione su delta= "), corrDelta
print ("coeff correlazione su n= "), corrN

#############################################################################################
##COMPITO A CASA


print ("\n ---------------------------- \n")
print ("INIZIO COMPITO A CASA")

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
xaxis=np.array([])
for i in range(3,7):					
	xaxis=np.append(xaxis,1./(j**2)-1./(i**2))		##array con le coord x

can=TCanvas()
can.Divide(2,2)

##considero solo errori sugli angoli th_i
can.cd(1)
can.SetTitle("Costante di Rydberg")
gr	= TGraphErrors ()						
gr.SetTitle("errori sugli angoli")
gr.GetXaxis().SetTitle("#frac{1}{n^{2}} - #frac{1}{m^{2}}")
gr.GetYaxis().SetTitle("1/#lambda")

sigmaY=np.array([])						##array con gli errori su y
for i in range(0,4):
	sigmaY=np.append(sigmaY,1/getLambda(theta[i]+sigmath,th0,meanA,meanB)-1/l[i])

	gr.SetPoint(i,xaxis[i],1/l[i])
	gr.SetPointError(i,0,sigmaY[i])


gr.Draw("AP");	
f=TF1("f","[0]*x",0,1)
f.SetParName(0,"Rh")
gr.Fit("f")
Rh_angoli=f.GetParameter(0)
sigmaRh_angoli=f.GetParError(0)



##errori su A e B e th0

grA	= TGraphErrors ()	
grB = TGraphErrors ()	
grTh0 = TGraphErrors ()

for i in range(0,4):
	sigmaYA=1/getLambda(theta[i],th0,meanA+sigmaA,meanB)-1/l[i]
	sigmaYB=1/getLambda(theta[i],th0,meanA,meanB+sigmaB)-1/l[i]
	sigmaYth0=1/getLambda(theta[i],th0+sigmath,meanA,meanB)-1/l[i]

	grA.SetPoint(i,xaxis[i],1/getLambda(theta[i],th0,meanA+sigmaA,meanB))
	grA.SetPointError(i,0,sigmaYA)
	grB.SetPoint(i,xaxis[i],1/getLambda(theta[i],th0,meanA,meanB+sigmaB))
	grB.SetPointError(i,0,sigmaYB)
	grTh0.SetPoint(i,xaxis[i],1/getLambda(theta[i],th0+sigmath,meanA,meanB))
	grTh0.SetPointError(i,0,sigmaYth0)

can.cd(2)
grA.SetTitle("errori su A")
grA.GetXaxis().SetTitle("#frac{1}{n^{2}} - #frac{1}{m^{2}}")
grA.GetYaxis().SetTitle("1/#lambda")
grA.Draw("AP");
grA.Fit("f")
RhA=f.GetParameter(0);
sigmaRh_A=f.GetParError(0)

can.cd(3)
grB.SetTitle("errori su B")
grB.GetXaxis().SetTitle("#frac{1}{n^{2}} - #frac{1}{m^{2}}")
grB.GetYaxis().SetTitle("1/#lambda")
grB.Draw("AP");
grB.Fit("f")
RhB=f.GetParameter(0);
sigmaRh_B=f.GetParError(0)

can.cd(4)
grTh0.SetTitle("errori su #theta_{0}")
grTh0.GetXaxis().SetTitle("#frac{1}{n^{2}} - #frac{1}{m^{2}}")
grTh0.GetYaxis().SetTitle("1/#lambda")
grTh0.Draw("AP");
grTh0.Fit("f")
RhTh0=f.GetParameter(0);
sigmaRh_th0=f.GetParError(0)


sigmaRh_AB=sqrt((Rh_angoli-RhA)**2+(Rh_angoli-RhB)**2+2*corrAB*(Rh_angoli-RhA)*(Rh_angoli-RhB))
sigmaRh_Tot=sqrt(sigmaRh_angoli**2+sigmaRh_AB**2+(RhTh0-Rh_angoli)**2)

print ("\n")
print ("------------------------")
print ("\n")


print ("contributo da AB"), sigmaRh_AB
print ("contributo da th0"), abs(RhTh0-Rh_angoli)
print ("contributo da th_i"), sigmaRh_angoli


print ("Miglior stima per Costante di Rydberg: "), Rh_angoli,("+/-"),sigmaRh_Tot

gApplication.Run(True)

