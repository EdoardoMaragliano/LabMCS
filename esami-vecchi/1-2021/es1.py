'''In un processo sono attesi 3 eventi, calcolare il numero minimo N (intero) di eventi osservati
 che permettono di escludere al 95% CL l'ipotesi nulla.
In un altro processo si osservano 0 eventi, calcolare il limite superiore 
(decimale) di eventi attesi che fa rientrare il numero di osservazioni nel 95% di CL.'''

##suppongo che i dati siano distribuiti con Poisson di media 3
##qual e' Nmin tc la probabilita' di osservare Nmin eventi e' minore del 5 %?

from ROOT import *

atteso=3

cl=0.95
acc=1-cl
Nmin=0
p_value=1

##metodo 1(piu' astruso)
while p_value>acc:
	prob=0

	for i in range(0,Nmin+1):		##integro da 0 a n_min
		prob+=TMath.PoissonI(i,atteso)
	p_value=1-prob
	Nmin+=1

print "\n p-value=",p_value,"\t n min per escludere h0 con CL=95% :", Nmin	

##metodo 2(più semplice)
integral=0
i=0
while integral<0.95:
	integral+=TMath.PoissonI(i,atteso)
	i+=1
print "p-value=",1-integral,"\t n min per escludere h0 con CL=95% :", i	





##calcolo il limite superiore dell'intervallo di confidenza

atteso2=0.0			##poisson di media 0 fa sempre 0!
Nmax=0.0			##inizializzo il conteggio
pmax=0.0			##inizializzo l'integrale della pdf

'''for i in range (0,5):
	p2=TMath.PoissonI(i,0)
	print p2
'''
while(pmax<cl):										
	pmax+=TMath.PoissonI(Nmax,atteso2)				#INTEGRO DA 0 A NMAX INCLUSO
		
	Nmax+=0.01
	print "Nmax=", Nmax
	print "pmax=", pmax										#Incremento NMAX A DESTRA



