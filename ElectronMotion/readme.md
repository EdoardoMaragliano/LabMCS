# Charged Particle Simulation in Electric and Magnetic Fields with ROOT

This project simulates the motion of charged particles (e.g. electrons) under uniform electric and magnetic fields using a 4th-order Runge-Kutta solver and ROOT for visualization.

---

## Code Explanation

- The simulation models point particles (`PuntoMateriale`), here specifically an electron (`Elettrone`), moving in an external electromagnetic field.
- The electric field is defined as a uniform field in the x-direction via function `fE()` returning a constant vector.
- The magnetic field is currently a uniform, weak field in the z-direction, defined inside `fEsterna()` as a constant vector `B`.
- The external force `fEsterna` calculates the Lorentz force on each particle:  
  \[
  \mathbf{F} = q \left( \mathbf{E} + \mathbf{v} \times \mathbf{B} \right)
  \]
- Internal forces (`fInterna`) are set to zero since we simulate a single charged particle here.
- The initial condition creates one electron at the origin with an initial velocity `(1e6, 0, 1e3)`.
- The numerical solver used is Runge-Kutta 4th order (`"Rk4"`), with a very small timestep (`5 \times 10^{-6}`) to resolve fast particle dynamics.
- ROOT's `TGraph` objects plot the XY trajectory of the particle.
- The main simulation loop advances the state and updates the plot every 10 steps, with `gSystem->ProcessEvents()` to refresh the display during the loop.
- The canvas frame size is set to ±5000 units to encompass the particle trajectory.

---

## Important Points

- Time integration stops when the simulation time `T()` exceeds 0.1 units.
- The timestep must be carefully chosen to balance accuracy and performance due to the high velocities and fields.
- The Lorentz force calculation uses vector cross product (`^`) between velocity and magnetic field vectors.
- The visualization shows the trajectory projected onto the XY plane.

---

## Compilation

Compilation is handled via the included `Makefile`. Simply run:

```bash
make