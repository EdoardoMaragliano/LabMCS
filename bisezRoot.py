import matplotlib.pyplot as plt 
import numpy as np
from ROOT import *

def fun(x):
	return x**2-1

def zeri(f,a,b,eps=1e-3):
	xmed=(a+b)/2
	while abs(b-a)>eps:
		fmed=f.Eval(xmed)
		fmin=f.Eval(a)
		if fmed*fmin<=0:
			b=xmed
		else:
			a=xmed	
		xmed=(a+b)/2
	return xmed

f= TF1("f","x^2-1",0,2)
x=zeri(f,0.,2.)
print(x)
f.Draw()
gApplication.Run(True)
