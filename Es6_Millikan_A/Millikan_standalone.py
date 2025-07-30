
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit, minimize
from scipy.stats import norm

# === Lettura dati ===
with open("Millikan.dat", "r") as f:
    data = np.array([float(line.strip()) for line in f])

# === Fit con somma di 3 gaussiane su e, 2e, 3e ===
def triple_gaussian(x, A1, mu, sigma, A2, scale):
    # Coefficiente A1 per la prima gaussiana (e)
    # Coefficiente A2 per la seconda gaussiana (2e)
    # Coefficiente A3 per la terza gaussiana (3e)
    # A3 è calcolato come 1 - A1 - A2 per assicurare che la somma dei coefficienti sia 1
    A3 = 1 - A1 - A2
    return scale * (
        A1 * norm.pdf(x, mu, sigma) +
        A2 * norm.pdf(x, 2*mu, sigma) +
        A3 * norm.pdf(x, 3*mu, sigma)
    )

# Istogramma dei dati
counts, bins = np.histogram(data, bins=120, range=(0, max(data)))
x = (bins[:-1] + bins[1:]) / 2
y = counts
dy = np.sqrt(np.maximum(y, 1))

# Fit iniziale
A1_init = 0.1  # Coefficiente per la prima gaussiana (e)
mu_init = 1.5  # Media della prima gaussiana (e)
sigma_init = 0.5  # Deviazione standard delle gaussiane
A2_init = 0.3  # Coefficiente per la seconda gaussiana (2e)
scale_init = np.sum(y) * (bins[1] - bins[0])  # Scala per normalizzare l'area sotto la curva

# p0 contiene i parametri iniziali per il fit
p0 = [A1_init, mu_init, sigma_init, A2_init, scale_init]
#p0 = [0.3, 1.5, 0.5, 0.3, np.sum(y)*(bins[1]-bins[0])]

# Fit dei dati con curve_fit
popt, pcov = curve_fit(triple_gaussian, x, y, p0=p0, sigma=dy, absolute_sigma=True)
A1, mu, sigma, A2, scale = popt
mu_err = np.sqrt(np.diag(pcov))[1]

# plot del risultato del fit
plt.figure(figsize=(10, 6))
plt.errorbar(x, y, yerr=dy, fmt='.',alpha=0.5, label='Dati', color='grey', markersize=1)
plt.bar(x, y, width=bins[1]-bins[0], alpha=0.5, label='Istogramma', color='lightblue')
plt.plot(x, triple_gaussian(x, *popt), label='Fit', color='red')
plt.title('Fit dei dati di Millikan')
plt.legend()

# Parametri sperimentali
elec, erre = mu, mu_err
he, ehe = 5.68, 1.02
hk, ehk = 4.70962, 0.159533
ek, eek = 1.159, 0.008

# === Chi2 ===
def chi2(par):
    e, h, k = par
    return (
        ((h/e - he)/ehe)**2 +
        ((h/k - hk)/ehk)**2 +
        ((e/k - ek)/eek)**2 +
        ((e - elec)/erre)**2
    )

x0 = [1.602, 6.626, 1.380]
res = minimize(chi2, x0)
e_fit, h_fit, k_fit = res.x

print(f"e = {e_fit:.5f} ± {erre:.5f} × 10⁻¹⁹ C")
print(f"h = {h_fit:.5f} ± {h_fit*ehe/he:.5f} × 10⁻³⁴ J·s")
print(f"k = {k_fit:.5f} ± {k_fit*eek/ek:.5f} × 10⁻²³ J/K")

# === Contour plot ===
# --- Funzione per tracciare contorni chi²=chi²_min+1 ---

chi2_min = chi2(res.x)
params_min = res.x
names = ['e', 'h', 'k']

# Valori veri CODATA (in unità coerenti con il tuo fit)
true_values = np.array([1.602176634, 6.62607015, 1.380649])

def plot_contour(i, j, ax, levels=[chi2_min + 1]):
    grid_points = 100
    span_i = 0.2 * params_min[i]
    span_j = 0.2 * params_min[j]
    x = np.linspace(params_min[i] - span_i, params_min[i] + span_i, grid_points)
    y = np.linspace(params_min[j] - span_j, params_min[j] + span_j, grid_points)
    X, Y = np.meshgrid(x, y)
    
    Z = np.zeros_like(X)
    for m in range(grid_points):
        for n in range(grid_points):
            p = params_min.copy()
            p[i] = X[m, n]
            p[j] = Y[m, n]
            Z[m, n] = chi2(p)
    
    cs = ax.contour(X, Y, Z, levels=levels, colors='red')
    ax.plot(params_min[i], params_min[j], 'bo', label='Best fit')
    ax.plot(true_values[i], true_values[j], 'g*', markersize=12, label='Valore vero (CODATA)')
    ax.set_xlabel(names[i])
    ax.set_ylabel(names[j])
    ax.legend()
    ax.set_title(f'Contour: {names[i]} vs {names[j]}')


# --- Plot contorni ---
fig, axs = plt.subplots(1, 3, figsize=(15, 4))
plot_contour(0, 1, axs[0])  # e vs h
plot_contour(0, 2, axs[1])  # e vs k
plot_contour(1, 2, axs[2])  # h vs k
plt.tight_layout()
plt.show()
