import matplotlib.pyplot as plt 
import numpy as np

def fun(x):
	return x**2-1

def zeri(f,a,b,eps=1e-3):
	xmed=(a+b)/2
	while abs(b-a)>eps:
		fmed=fun(xmed)
		fmin=fun(a)
		if fmed*fmin<=0:
			b=xmed
		else:
			a=xmed	
		xmed=(a+b)/2
	return xmed

x=zeri(fun,0.,2.)
print(x)
xx=np.linspace(0,2,100)
yy=fun(xx)
plt.plot(xx,yy,"-r")
plt.show()
