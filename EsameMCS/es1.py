from ROOT import *
import math

rnd=TRandom3()
rnd.SetSeed(123456678)

N=100000
h=TH1D("histo","histo",200,0,10)

for i in range(0,N):
	t=(-math.log(1-rnd.Rndm()))**(2.0/3)
	h.Fill(t)

f=TF1("f","[2]*([0]/([1]**[0])*x**([0]-1)*exp(-(x/[1])**[0]))",0,10)
f.SetParameter(0,1.5)
f.SetParameter(1,1)
f.SetParameter(2,h.Integral("width"))
h.Fit("f","LR")
h.Draw()
print "k=", f.GetParameter(0)
print "lambda=",f.GetParameter(1)
gApplication.Run(True)