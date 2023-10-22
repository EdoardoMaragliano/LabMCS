from ROOT import *
import math 
import numpy as np
import matplotlib.pyplot as plt

'''moto di una biglia di acciaio in caduta libera in acqua che parte da ferma da 100 m di altezza
la forza di attrito viscoso e' Fd=-0.5*Cd(v)\rho*pi*r^2 \vers(v) con Cd(v)=24v/Re+4v^(3/2)+0.4v^2
Re=2\rho*r/mu
Si considerino la forza peso e la spinta di Archimede e si calcoli il moto con un metodo del 2 ordine
Si grafichi l v in funzione di t con e senza il contributo della spinta di Archimede'''

h=100
g=9.81
dt=0.01
rho=1		##densita fluido
rho0=2		##densita oggetto
mu=0.001
r=0.5
V=(4/3)*math.pi*(r)**3
m=V*rho0
Re=2*rho0*(r/mu)

tmax=4*(2*g*h)**(1/2)
n=int(tmax/dt)

def Cd(v):
	return (24*v/Re+4*(v)**(3/2)/Re+0.4*(v)**2)

##accelerazione con archimede
def acc(x,v):
	return (1/m)*(-m*g+rho*V*g+0.5*Cd(v)*rho*math.pi*r**2)

def acc2(x,v):
	return (1/m)*(-m*g+0.5*Cd(v)*rho*math.pi*r**2)	

def Rk2(x,v):				##prende due array np
	for i in range (0,n-1):
		if x[i]>0:
			k1=dt*v[i]
			w1=dt*acc(x[i],v[i])
			k2=dt*(v[i]+w1/2)
			w2=dt*acc(x[i]+k1/2,v[i]+w1/2)
			x[i+1]=x[i]+k2
			v[i+1]=v[i]+w2

def Rk2b(x,v):				##prende due array np
	for i in range (0,n-1):
		if x[i]>0:
			k1=dt*v[i]
			w1=dt*acc2(x[i],v[i])
			k2=dt*(v[i]+w1/2)
			w2=dt*acc2(x[i]+k1/2,v[i]+w1/2)
			x[i+1]=x[i]+k2
			v[i+1]=v[i]+w2			


x1=np.zeros(n)		##creo array valori x
v1=np.zeros(n)		##creo array valori v
x1[0]=h 			##imposto il dato iniziale, h=100m

Rk2(x1,v1)
t=np.linspace(0,tmax,n)
plt.plot(t,v1)
plt.title("Con Archimede")
plt.xlabel("t [s]")
plt.ylabel("v [m/s]")
plt.show()

x2=np.zeros(n)		##creo array valori x
v2=np.zeros(n)		##creo array valori v
x2[0]=h 			##imposto il dato iniziale, h=100m
Rk2b(x2,v2)	

plt.plot(t,v2)
plt.title("Senza Archimede")
plt.xlabel("t [s]")
plt.ylabel("v [m/s]")
plt.show()


