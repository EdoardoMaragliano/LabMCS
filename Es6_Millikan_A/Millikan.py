import numpy as np
from ROOT import TCanvas, TGraph, TF1, TH1D, gApplication, kGreen, kRed, kBlue
from iminuit import Minuit

from math import *
from scipy import stats

def chi2(par):
    final =((par[1]/par[0] - he)/ehe)**2+((par[1]/par[2]-hk)/ehk)**2+((par[0]/par[2]-ek)/eek)**2+((par[0]-elec)/erre)**2

    return final


file1 = open("Millikan.dat")
h = TH1D("h","Millikan", 120,0,0)
data = np.array([])
for line in file1:
   val = line.split()
   h.Fill(float(val[0]))
   data=np.append(data,float(val[0]))
h.Draw()


f = TF1("f", "[4]*([0]*TMath::Gaus(x,[1],[2],1)+[3]*TMath::Gaus(x,2*[1],[2],1)+(1-[0]-[3])*TMath::Gaus(x,3*[1],[2],1))",0,6)

f.SetParameter(0,0.3)
f.SetParameter(1,1.5)
f.SetParameter(2,0.5)
f.SetParameter(3,0.3)
f.SetParameter(4,h.GetEntries()*h.GetBinWidth(1))


h.Fit("f","R")

elec = f.GetParameter(1)
erre =f.GetParError(1)

print("e = ", elec, "+/-", erre)

par = np.ndarray(3)
par[0] = 1.602
par[1] = 6.626
par[2] = 1.380


he = 5.68
ehe = 1.02

ek = 1.159
eek = 0.008

hk = 4.70962
ehk = 0.159533

m = Minuit.from_array_func(chi2, par, print_level = 1)
m.migrad()

print (" e = ", m.values[0], "+/-", m.errors[0], "E-19 C")
print ("h = ", m.values[1], "+/-", m.errors[1], "E-34 J*s")
print ("k = ", m.values[2], "+/-", m.errors[2], "E-23 J/K")

xminos1, yminos1, ctr1 = m.mncontour('x0','x1',sigma=1,numpoints=100)  #(e/h)
xminos2, yminos2, ctr2 = m.mncontour('x0','x2',sigma=1,numpoints=100) #(e/k)
xminos3, yminos3, ctr3 = m.mncontour('x1','x2',sigma=1,numpoints=100) #(h/k)

con1 = TGraph()
con2 = TGraph()
con3 = TGraph()
for i in range(0,len(ctr1)):
    con1.SetPoint(i+1,ctr1[i][0],ctr1[i][1])
for i in range(0,len(ctr2)):
    con2.SetPoint(i+1,ctr2[i][0],ctr2[i][1])
for i in range(0,len(ctr3)):
    con3.SetPoint(i+1,ctr3[i][0],ctr3[i][1])


con1.SetMarkerColor(kGreen)    
con2.SetMarkerColor(kRed)
con3.SetMarkerColor(kBlue)

con1.SetMarkerStyle(20)    
con2.SetMarkerStyle(20)
con3.SetMarkerStyle(20)

con1.SetPoint(0,par[0],par[1])
con2.SetPoint(0,par[0],par[2])
con3.SetPoint(0,par[1],par[2])





a = TCanvas()
con1.SetTitle("e/h")
con1.Draw("AP")
b = TCanvas()
con2.SetTitle("e/k")
con2.Draw("AP")
c = TCanvas()
con3.SetTitle("h/k")
con3.Draw("AP")

gApplication.Run(True)
