from   ROOT    import *
from   numpy   import *
from   ctypes  import *
def func(x,a,b):
    return a*x+b
def fcn(npar, gin, f, par,iflag):
    chi2 = 0.0
    for i in range(0,len(x)):
        chi2 += ((y[i]-func(x[i],par[0],par[1]))/ey[i])**2
    f.value = chi2
x  = array([]); y  = array([]); ex = array([]); ey = array([])
for line in open("pendolo.dat"):
    dt  = line.split()
    if len(dt)!=4:
        continue
    x   = append(x,  float(dt[0])); y   = append(y,  float(dt[1]))
    ex  = append(ex, float(dt[2])); ey  = append(ey, float(dt[3]))
minuit = TMinuit(2)
minuit.SetFCN(fcn);
minuit.DefineParameter(0,'par0',4,0.01,0.,0.)
minuit.DefineParameter(1,'par1',0,0.01,0.,0.)
minuit.Command("MIGRAD")
a  = c_double(0.0); b  = c_double(0.0)
ea = c_double(0.0); eb = c_double(0.0)
minuit.GetParameter(0,a,ea);
minuit.GetParameter(1,b,eb);
print("a = %f +- %f, b = %f +- %f"%(a.value,ea.value,b.value,eb.value))
