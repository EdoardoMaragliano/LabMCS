# MC simulation: fit of the Rydberg constant

## 🧠 Theoretical Background: The Rydberg Constant

The **Rydberg constant** $R_H$ is a fundamental physical constant that describes the wavelengths of spectral lines in hydrogen and hydrogen-like atoms. It appears in the **Rydberg formula**, which gives the inverse of the wavelength $\lambda$ of emitted or absorbed light as an electron transitions between energy levels:

$
\frac{1}{\lambda} = R_H \left( \frac{1}{n_1^2} - \frac{1}{n_2^2} \right)
$

where:
- $ \lambda $ is the wavelength of the spectral line,
- $ n_1 $ and $ n_2 $ are the principal quantum numbers of the energy levels involved ($ n_2 > n_1 $),
- $ R_H $ is the Rydberg constant for hydrogen.

### Value and Importance
The currently accepted CODATA value is:

$
R_H \approx 1.0967757 \times 10^7 \, \text{m}^{-1}
$

This constant is central to atomic physics and quantum mechanics, as it encapsulates the binding energy structure of hydrogen.

In this notebook, we estimate $ R_H $ by inverting the Rydberg formula using measured wavelengths for the Balmer series (H-alpha and H-beta) and the parameters A and B previously obtained from diffraction measurements.


## 📘 Part 1: Monte Carlo Estimation of A and B

This notebook computes the parameters **A** and **B** from measured diffraction angles of the H-alpha and H-beta lines. It uses Monte Carlo sampling to simulate measurement uncertainties on the angles and propagate them into the estimation of A and B.

- **Aims**
  - Measure the A and B parameters modeling the dependence of the refraction index on the wavelength, according to Cauchy relation
  $n(\lambda) = A + \frac{B}{\lambda^2} + O(\frac{1}{\lambda^3})$.

  For a given material, measuring the refraction index at two different wavelengths one can obtain the A and B coefficients.
  
  $A = n_2 - \lambda_1^2 \frac{n_1 - n_2}{\lambda_2^2 - \lambda_1^2}$

  $B = \frac{(n_1 - n_2) \lambda_1^2 \lambda_2^2}{\lambda_2^2 - \lambda_1^2}$

  The refracion index are obtained measuring the refraction angles at different wavelengths, as follows
  
  $n_i = n(\theta_i) = \frac{\sin\left(\frac{\theta_i - \theta_0 + \alpha}{2}\right)}{\sin\left(\frac{\alpha}{2}\right)}$

  for measured angles $\theta_1\equiv\theta(\lambda_1), \theta_2\equiv\theta(\lambda_2)$ and the prism angle $\alpha$.

  We also aim to propagate the uncertainties on the measured angles to these A and B parameters.

- **Inputs**:
  - Known wavelengths: $\lambda_a$ (656.3 nm, H $\alpha$), $\lambda_b$ (486.1 nm, H $\beta$)
  - Angular measurements: $\theta_1$, $\theta_2$, and their uncertainty

  - Grating spacing: d
  - Prism angle: $\alpha$

- **Outputs**:
  - Distributions of A and B from the Monte Carlo simulation
  - Mean values and standard deviations
  - Plots and ROOT file for further analysis

### Part 2: measure wavelengths using the calibrated A and B

For different wavelengths, fit the formula

$\frac{1}{\lambda} = R_H \left( \frac{1}{n_{1}^{2}} - \frac{1}{n_{2}^{2}} \right)$

to obtain $R_H$.