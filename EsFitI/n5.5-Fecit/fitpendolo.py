from   ROOT    import *
from   iminuit import Minuit
from   numpy   import *
#funzione #CON ERRORE SULLA X: NON CONSCO X VERO E DIVENTA PARAMETRO
def f(x,a,b):
    return a*x+b
#chi quadro
def chi2(par):
    val = 0
    for i in range(0,len(x)):
	#val = val + ((y[i]-f(x[i],par[0],par[1]))/ey[i])**2
        val = val + ((y[i]-f(par[i+2],par[0],par[1]))/ey[i])**2 #anziche' xi metto i parametri x
	val = val + (x[i]-par[i+2]/ex[i])**2
    return val
#accesso ai dati
gr = TGraphErrors()
x  = array([]); y  = array([]); ex = array([]); ey = array([])
for line in open("pendolo.dat"):
    dt  = line.split() 
    if len(dt)!=4:
        continue
    x   = append(x,  float(dt[0])); y   = append(y,  float(dt[1]))
    ex  = append(ex, float(dt[2])); ey  = append(ey, float(dt[3]))
    gr.SetPoint(i,x[i],y[i])
    gr.SetPointError(i,ex[i],ey[i])
    i=i+1
#minimizzazione
par = ndarray(2+len(x)) #dal terzo in poi sono i parametri della x
par[0]=4 #i primi due parametri
par[1]=0
m = Minuit.from_array_func(chi2,par,error=0.01,errordef=1,print_level=2)
m.migrad()       # run minimiser
print(m.values)  # output parametri
print(m.errors)  # output errori

gr.Fit("pol1")
