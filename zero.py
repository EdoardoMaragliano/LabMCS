'''
  Numerov method
'''

import matplotlib.pyplot as plt
import numpy as np
import math


def func(x):
    return x**2 - 1
    
def findZero(fun,emin,emax,tol):
    emed = (emin+emax)/2
    while (emax-emin>tol):
        fmed = fun(emed);
        fmin = fun(emin)
        if (fmin*fmed<=0):
            emax = emed
        else:
            emin = emed
        emed=(emin+emax)/2
    return emed;

print(findZero(func,0.,2.,0.01))

x = np.linspace(0,2,100)
y = func(x)
plt.plot(x,y)
plt.show()
