from   iminuit import Minuit
from   numpy   import *

def f(x,a,b):
    return a*x+b
def chi2(a,b):
    val = 0
    for i in range(0,len(x)):
        val = val + ((y[i]-f(x[i],a,b))/ey[i])**2
    return val
x  = array([]); y  = array([]); ex = array([]); ey = array([])
for line in open("pendolo.dat"):
    dt  = line.split() 
    if len(dt)!=4:
        continue
    x   = append(x,  float(dt[0])); y   = append(y,  float(dt[1]))
    ex  = append(ex, float(dt[2])); ey  = append(ey, float(dt[3]))
m = Minuit(chi2,a=4,b=0,print_level=2) ##limit_a=(0,10)
m.migrad()       # run minimiser
print(m.values)  # output parametri
print(m.errors)  # output errori

