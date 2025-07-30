# 📘 Estimating the Rydberg Constant via Monte Carlo Simulation

## 🧠 Theoretical Background: The Rydberg Constant

The **Rydberg constant** \( R_H \) is a fundamental physical constant that describes the wavelengths of spectral lines in hydrogen and hydrogen-like atoms. It appears in the **Rydberg formula**, which gives the inverse of the wavelength $$ \lambda $$ of emitted or absorbed light as an electron transitions between energy levels:

$$
\frac{1}{\lambda} = R_H \left( \frac{1}{n_1^2} - \frac{1}{n_2^2} \right)
$$

where:
- $$ \lambda $$ is the wavelength of the spectral line,
- $$ n_1 $$ and $$ n_2 $$ are the principal quantum numbers of the energy levels involved ($$ n_2 > n_1 $$),
- $$ R_H $$ is the Rydberg constant for hydrogen.

### Value and Importance
The currently accepted CODATA value is:

$$
R_H \approx 1.0967757 \times 10^7 \, \text{m}^{-1}
$$

This constant is central to atomic physics and quantum mechanics, as it encapsulates the binding energy structure of hydrogen. Precise determination of $$ R_H $$ allows experimental tests of quantum electrodynamics (QED), and contributes to defining other constants like the fine-structure constant $$ \alpha $$.

In this notebook, we estimate $$ R_H $$ by inverting the Rydberg formula using measured wavelengths for the Balmer series (H-alpha and H-beta) and the parameters A and B previously obtained from diffraction measurements.


## Overview

This project consists of two Python scripts using the **ROOT** framework to analyze optical measurements and estimate the **Rydberg constant** \( R_H \). The scripts simulate experimental uncertainties and propagate them through to the final result using **Monte Carlo techniques** and analytical methods.

### Structure

1. **Script 1** – Computes the parameters \( A \) and \( B \) from angular measurements and evaluates their uncertainties through Monte Carlo simulations.
2. **Script 2** – Uses the estimated values of \( A \) and \( B \) to compute the Rydberg constant \( R_H \), propagating errors from all relevant variables.

---

## ⚙️ Requirements

- Python with **PyROOT**
- `numpy`
- `math`
- `ROOT` installed (e.g., from the [CERN ROOT project](https://root.cern/))

---

## 🧪 Script 1 – Estimating A and B via Monte Carlo

### Purpose

This script computes the parameters \( A \) and \( B \) based on measured diffraction angles \( \theta_1 \) and \( \theta_2 \), assuming a known grating spacing \( d \) and known wavelengths of spectral lines. It also performs a Monte Carlo simulation to propagate the uncertainties of the measured angles.

### Inputs

- Measured angles \( \theta_1 \) and \( \theta_2 \), with uncertainty \( \sigma_\theta \)
- Grating spacing \( d \)
- Wavelengths \( \lambda_{\alpha} \) and \( \lambda_{\beta} \)

### Output

- Estimated values of \( A \) and \( B \)
- Corresponding uncertainties from the Monte Carlo sample
- Histogram of \( A \) and \( B \) values saved as `AB_distribution.root`
- Best estimates saved to `AB_values.txt`

---

## 🔬 Script 2 – Estimating the Rydberg Constant

### Purpose

This script uses the parameters \( A \) and \( B \) obtained in the first step to calculate the Rydberg constant \( R_H \), using the relation:

\[
R_H = \frac{1}{\lambda} \left( \frac{1}{n_1^2} - \frac{1}{n_2^2} \right)^{-1}
\]

It fits the measured wavelengths of spectral lines (H-alpha and H-beta) to the known quantum transitions, then computes \( R_H \) and propagates all relevant uncertainties analytically.

### Inputs

- Wavelengths \( \lambda_{\alpha} \), \( \lambda_{\beta} \)
- Quantum level indices \( (n_1, n_2) \)
- Values of \( A \), \( B \), and their uncertainties from `AB_values.txt`

### Output

- Estimated value of the Rydberg constant with uncertainty
- Summary printed to terminal
- Optionally, values can be stored for further analysis or plotting

---

## 📈 Notes

- The Monte Carlo in Script 1 assumes Gaussian uncertainties in angle measurements.
- The error propagation in Script 2 uses standard Gaussian error propagation formulas.
- All physics formulas and assumptions follow the standard treatment of diffraction and hydrogen spectral lines.

---

## 🧑‍🔬 Author

This code was developed as part of a lab exercise to understand the propagation of measurement errors and the extraction of fundamental constants from experimental data.

---
