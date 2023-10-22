'''integrale della sfera n dimensionale con metodo monte carlo'''

from ROOT import *
import math as m

rnd=TRandom2();

l=10					##semi-lato cubo n dim
r=l				##raggio crf n dim
dim=4			###Volume=alpha*r**dim
norm=(2*l)**dim/(r**dim)
N=5000000
fav=0.0
alpha=0.0
atteso=m.pi**(dim/2)/TMath.Gamma(dim/2+1)
delta=0.0
print "valore atteso per alpha", atteso

##TF1("f","TMath::Constant()",0,N)
gr=TGraph()
gr.SetTitle("grafico")
gr.GetXaxis().SetTitle("N")
gr.GetYaxis().SetTitle("alpha")

rnd.SetSeed(123456789)

for i in range(1,N):
	x=l-2*l*rnd.Rndm()			##le coordinate del punto devono appartenere allo spazio campionario 
	y=l-2*l*rnd.Rndm()					##il quadrato n dim [-l,l]
	z=l-2*l*rnd.Rndm()
	w=l-2*l*rnd.Rndm()
	d=x**2+y**2+z**2+w**2
	#print x,y,z,w

	if d<=r**2:
		fav=fav+1
		alpha=(fav/N)*norm
		delta=atteso-alpha
		if(i%1000000==0):
			print alpha
			gr.SetPoint(gr.GetN(),i,alpha)

print alpha

c=TCanvas()
gr.Draw("AP")
gApplication.Run(True)
		
		
