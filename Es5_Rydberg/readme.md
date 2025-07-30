# MC Simulation: Fit of the Rydberg Constant

## 🧠 Theoretical Background: The Rydberg Constant

The **Rydberg constant** `R_H` is a fundamental physical constant that describes the wavelengths of spectral lines in hydrogen and hydrogen-like atoms. It appears in the **Rydberg formula**, which gives the inverse of the wavelength `λ` of emitted or absorbed light as an electron transitions between energy levels:

```
1/λ = R_H * (1/n₁² - 1/n₂²)
```

where:
- `λ` is the wavelength of the spectral line,
- `n₁` and `n₂` are the principal quantum numbers of the energy levels involved (`n₂ > n₁`),
- `R_H` is the Rydberg constant for hydrogen.

### Value and Importance

The currently accepted CODATA value is:

```
R_H ≈ 1.0967757 × 10⁷ m⁻¹
```

This constant is central to atomic physics and quantum mechanics, as it encapsulates the binding energy structure of hydrogen.

In this notebook, we estimate `R_H` by inverting the Rydberg formula using measured wavelengths for the Balmer series (H-alpha and H-beta), and the parameters `A` and `B` previously obtained from diffraction measurements.

---

## 📘 Part 1: Monte Carlo Estimation of A and B

This notebook computes the parameters **A** and **B** from measured diffraction angles of the H-alpha and H-beta lines. It uses Monte Carlo sampling to simulate measurement uncertainties on the angles and propagate them into the estimation of A and B.

### Aims

Measure the parameters A and B modeling the dependence of the refraction index on the wavelength, according to the Cauchy relation:

```
n(λ) = A + B / λ² + O(1 / λ³)
```

For a given material, measuring the refraction index at two different wavelengths allows one to compute A and B using:

```
A = n₂ - λ₁² * (n₁ - n₂) / (λ₂² - λ₁²)

B = (n₁ - n₂) * λ₁² * λ₂² / (λ₂² - λ₁²)
```

The refraction indices are obtained by measuring the deviation angles for each wavelength:

```
n(θᵢ) = sin[(θᵢ - θ₀ + α) / 2] / sin(α / 2)
```

for measured angles `θ₁ ≡ θ(λ₁)` and `θ₂ ≡ θ(λ₂)`, and prism angle `α`.

We also aim to propagate the uncertainties on the measured angles to the derived A and B values.

### Inputs

- Known wavelengths:
  - `λₐ = 656.3 nm` (Hα)
  - `λ_b = 486.1 nm` (Hβ)
- Angular measurements: `θ₁`, `θ₂`, and their uncertainties
- Prism angle: `α`

### Outputs

- Distributions of A and B from the Monte Carlo simulation
- Mean values and standard deviations
- Plots and ROOT file for further analysis

---

## 📗 Part 2: Measure Wavelengths Using Calibrated A and B

For different wavelengths, we invert the Rydberg formula:

```
1/λ = R_H * (1/n₁² - 1/n₂²)
```

Using known `n₁` and `n₂` (e.g. for Balmer series, `n₁ = 2`), and the calibrated refraction law `n(λ)` from Part 1,
