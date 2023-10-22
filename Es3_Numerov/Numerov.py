'''
 Numerov method
'''
import matplotlib.pyplot as plt
import numpy as np
import math as m


def V(xi):

    return xi**2                   ##oscillatore armonico
    #return xi**2+gamma*xi**4        ##oscillatore anarmonico
    

def b(eps,xi):
##   calcolo di b a partire a E (eps), x e h (globale)    
    return (h**2)/12*(2*eps-V(xi))

def numerov(n1,n2,eps):
## riempe i valori di psi(xi) da i=n1 a i=n2 (compresi entrambi)
##sia in avanti che all'indietro
    psi = np.array(xi)  ## copio xi in psi
    j=np.sign(n2-n1)   ##1 se n2>n1, -1 altrimenti

##S1/S2  fornisco i primi due valori di psi
    psi[n1]=0
    psi[n1+j]=1e-06
##S1/S2  implemento Numerov
    for i in range(n1+2*j,n2+j,j):
        psi[i]=(2*psi[i-j]*(1-5*b(eps,xi[i-j]))-psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i])) 
    return psi

def evalDerivative(eps):
##S3 per energia eps fornita crea sequenza left e right
    global psir, psil                   ##le dichiaro global affinche siano disponibili fuori
    psil = numerov(0,nmatch+1,eps)      ##soluzione da sinistra , nmatch sta nel main = 10000
    psir = numerov(n-1,nmatch-1,eps)    ##soluzione da destra
##   le normalizza a nmatch
    alpha=psil[nmatch]/psir[nmatch]    ##incollaggio con continuita' 
    psir=alpha*psir                    

##   calcola la differenza (diff) tra le derivate centrate (left e right) in match
    dpsil=(psil[nmatch+1]-psil[nmatch-1])/(2*h)     ##sia psil sia psir sono indicizzate da sinistra
    dpsir=(psir[nmatch+1]-psil[nmatch-1])/(2*h)     
    diff = dpsir-dpsil
    return diff

def findE(emin,emax,tol):               ##cerca l'energia nell'intervallo (emin,emax)
##  implementazione di bisezione gia' fornita
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;




 
## Main code
n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]
gamma   = 0.075


##ricerca degli stati fisici in un dato intervallo
print "ricerco stati fisici"
nsteps=100
grid = np.linspace(0.2,2.7, nsteps) ##creo partizione dell'intervallo
e=np.array([])
j=0
i=0

for j in range(0,nsteps-1):
    if evalDerivative(grid[j])*evalDerivative(grid[j+1])<0:
        e = np.append(e,findE(grid[j],grid[j+1],0.0001))
        print  'energy', e[i]
        i=i+1

print "ricerca stati fisici terminata"


##scelto uno stato, costruisce la funzione d'onda
print "costruisco funzione d'onda "
e1=input('inserire emin: ')
e2=input('inserire emax: ')
e = findE(e1,e2,0.0001)
print "Energy ", e


##S4
##copiare psir nella parte 'vuota' di psil di modo che psil rappresenti tutta psi(x)

#for i in range (nmatch,n):     ##e' equivalente all'assegnazione vettoriale della riga sotto
 #   psil[i]=psir[i]

psil[nmatch:n]=psir[nmatch:n]


##calcolo dell'integrale di psi con metodo dei trapezi
w=14./n
S=0
for i in range(1,n-1):
    S+=(psil[i])**2

I=w/2*((psil[0])**2+(psil[n-1])**2)+w*S
print "integrale ", I

psi=psil/m.sqrt(I)

##controllo che la normalizzazione sia corretta
S=0
for i in range(1,n-1):
    S+=(psi[i])**2

I=w/2*((psi[0])**2+(psi[n-1])**2)+w*S
print "integrale normalizzato", I

plt.plot(xi,psi)
plt.show()
plt.plot(xi,psi**2)
plt.show()





