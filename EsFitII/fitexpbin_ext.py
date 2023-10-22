from   ROOT    import *
from   iminuit import Minuit
import numpy   as     np
from   math    import *

def flogl(tau,norm):
    val = 0
    for i in range(1,h.GetNbinsX()+1):
        tmin = h.GetBinCenter(i)-h.GetBinWidth(1)/2
        tmax = h.GetBinCenter(i)+h.GetBinWidth(1)/2
        mu   = (exp(-tmin/tau)-exp(-tmax/tau))*norm
        val = val - (h.GetBinContent(i)*log(mu)-mu)
    return val

#Main
h  = TH1D("h","",20,0,10)
for line in open("exp.dat"):
    h.Fill(float(line))

m = Minuit(flogl,tau=2,norm=1000,errordef=0.5,print_level=2)
m.migrad()       # run minimiser

tau  = m.values[0]
norm = m.values[1]
print(tau,norm)
h.Draw("E")
hfit = TH1D(h)
for i in range(1,h.GetNbinsX()+1):
    tmin = h.GetBinCenter(i)-h.GetBinWidth(i)/2
    tmax = h.GetBinCenter(i)+h.GetBinWidth(i)/2
    p   = (exp(-tmin/tau)-exp(-tmax/tau))
    hfit.SetBinContent(i,p*norm)
hfit.Draw("SAME")
hfit.SetLineColor(2)

gApplication.Run(True)

