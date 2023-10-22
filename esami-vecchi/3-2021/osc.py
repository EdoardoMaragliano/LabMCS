'''si vuole risolvere l'equazione dell'oscillatore armonico relativistico

md^2x/dt^2=-kx(1-v^2/c^2)^(3/2)	

con un opportuno sistema, c=1, m=1, k=100 con un metodo per la soluzione
delle equazioni differenziali a piacere di grado superiore al primo. Si disegni l'andamento di x in funzione 
di t per t in [0,10] sapendo che a t=0 x0=0 e 0<=v0<c.
Si sovrapponga x(t) per v0=0.5c, v0=0.8c, v0=0.99c.
'''

from ROOT import *
import numpy as np
import matplotlib.pyplot as plt
import math 


m=1.0
c=1.0
k=100.0
tmax=10.0
n=10000
t=np.linspace(0.,tmax,n)
dt=t[1]-t[0]


def acc(x,v):
	return (1/m)*(-k*x*(1-v**2/c**2)**(1.5))


def Rk2(x,v):				##prende due array np
	for i in range (0,n-1):
		k1=dt*v[i]
		w1=dt*acc(x[i],v[i])
		k2=dt*(v[i]+w1/2)
		w2=dt*acc(x[i]+k1/2,v[i]+w1/2)
		x[i+1]=x[i]+k2
		v[i+1]=v[i]+w2
			

##main

plt.title("Oscillatore relativistico")
plt.xlabel("t [s]")
plt.ylabel("x [m]")


x1=np.zeros(n)		##creo array valori x
v1=np.zeros(n)		##creo array valori v
v1[0]=0.5 			##imposto il dato iniziale

Rk2(x1,v1)
plt.plot(t,x1)


x2=np.zeros(n)		##creo array valori x
v2=np.zeros(n)		##creo array valori v

v2[0]=0.8 			##imposto il dato iniziale, h=100m
Rk2(x2,v2)
plt.plot(t,x2)

x3=np.zeros(n)		##creo array valori x
v3=np.zeros(n)		##creo array valori v

v3[0]=0.99 			##imposto il dato iniziale, h=100m
Rk2(x3,v3)
plt.plot(t,x3)
plt.legend(["v0=0.5c", "v0=0.8c", "v0=0.99c"])
#plt.legend([ "v0=0.5c", "v0=0.8c"])

plt.show()





