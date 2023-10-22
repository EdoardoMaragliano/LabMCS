'''su un'area in cui sono state tracciate linee rette parallele a distanza d viene lanciato un ago 
sottile di lunghezza l<d. La probabilita' che l'ago intersechi una linea e' p(intersez)=2L/(pi*d)

Si simuli il lancio dell'ago sulla griglia di linee parallele e si ottenga una stima di pi con il suo 
errore. Si grafichi il valore di pi ottenuto in funzione del numero di lanci e si confronti con il valore
nominale'''

from ROOT import *
import math

rnd=TRandom2()
d=10.0
L=10.0
N=1000000

Nfav=0.0

for i in range(0,N):
	x=0.5*d*rnd.Rndm()
	phi=math.pi*rnd.Rndm()
	if x<L/2*math.sin(phi):
		Nfav+=1
stima=2*L/d*float(N)/Nfav
print stima

