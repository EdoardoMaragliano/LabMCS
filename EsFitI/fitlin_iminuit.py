from   iminuit import Minuit
from   numpy   import *

def f(x,a,b):
    return a*x+b

def chi2(par):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],par[0],par[1]))/ey[i])**2
    return val

x  = array([]); y  = array([]); ex = array([]); ey = array([])
for line in open("pendolo.dat"):
    dt  = line.split() 
    if len(dt)!=4:
        continue
    x   = append(x,  float(dt[0])); y   = append(y,  float(dt[1]))
    ex  = append(ex, float(dt[2])); ey  = append(ey, float(dt[3]))

par = array([4.0,0.0])  ##array di parametri
lim = array([(0,10),(0,10)])
m = Minuit.from_array_func(chi2,par,limit=lim,print_level=2)
m.migrad()       # run minimiser
print(m.values)  # output parametri
print(m.errors)  # output errori

