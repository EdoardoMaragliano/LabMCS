'''Esame 04/02/19 
Si vuole risolvere l'equazione dell'oscillatore armonico forzato
m* d^2x/dt^2 + kx = A sin(omega*t)
(m = 1 kg,k = 0.25 N/m, A = 0.1 N, omega = 0.25 rad/s) usando Verlet-Velocity 
x(n+1) =x(n) +hv(n) + h**2/2 a(xn,tn)
v(n+1) = v(n) + h/2 (a(x_n+1, t_n+1) + a(x_n, t_n))
Si disegni l'andamento di x in funzione di t per t in [0, 100] sapendo che all'istante t = 0 
la posizione vale x = 1 m e il corpo e' in quiete.'''


import matplotlib.pyplot as plt
import math
import numpy as np

m=1.0
k=0.25
A=0.1
omega=0.25
x0=1.0
v0=0.0
N=5000
tmax=100.0
t= np.linspace(0.,tmax,N)
dt=t[1]-t[0]

def acc(x,t):
	return (1/m)*(-k*x+A*math.sin(omega*x))

def verlet(x,v,t):
	xNew=x+dt*v+0.5*dt**2*acc(x,t)
	vNew=v+0.5*dt*acc(xNew,t+dt)+acc(x,t)
	return xNew,vNew


##main

x=np.zeros(N)
v=np.zeros(N)
x[0]=x0
v[0]=v0

for i in range(1,N):
	x[i],v[i]=verlet(x[i-1],v[i-1],t[i-1])

plt.plot(t,x)
plt.xlabel("t [s]")
plt.ylabel("x [m]")	
plt.show()



