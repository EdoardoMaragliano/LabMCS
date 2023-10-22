from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau):
    val = 0
    for i in range(1,h.GetNbinsX()+1):
    	# h.GetBinLowEdge(i)
    	# h.GetBinLowEdge(i)+GetBinWidth(i)
        tmin = h.GetBinCenter(i)-h.GetBinWidth(1)/2
        tmax = h.GetBinCenter(i)+h.GetBinWidth(1)/2
        p   = (exp(-tmin/tau)-exp(-tmax/tau))
        val = val - h.GetBinContent(i)*log(p)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,error_tau=0.01,errordef=0.5,print_level=2)
m.migrad()       # run minimiser

tau = m.values[0]
print(tau)
h.Draw("E")
hfit = TH1D(h)
for i in range(1,h.GetNbinsX()+1):
    tmin = h.GetBinCenter(i)-h.GetBinWidth(i)/2
    tmax = h.GetBinCenter(i)+h.GetBinWidth(i)/2
    p   = (exp(-tmin/tau)-exp(-tmax/tau))
    hfit.SetBinContent(i,p*h.GetEntries())
hfit.Draw("SAME")
hfit.SetLineColor(2)

gApplication.Run(True)

