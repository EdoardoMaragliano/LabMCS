'''
  Ricerca di zeri
'''

import matplotlib.pyplot as plt
import numpy as np
from   ROOT import * 


def findZero(f1,emin,emax,tol):
    emed = (emin+emax)/2
    while (emax-emin>tol):
        fmed = f1.Eval(emed);
        fmin = f1.Eval(emin)
        if (fmin*fmed<=0):
            emax = emed
        else:
            emin = emed
        emed=(emin+emax)/2
    return emed


f = TF1("f","x^2-1",0,2,1)
print(findZero(f,0.,2.,0.001))
f.Draw()
gApplication.Run(True)

