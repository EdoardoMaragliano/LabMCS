# Orbital Simulation with ROOT

This project simulates the motion of multiple point masses (planets) under mutual gravitational forces using a numerical ODE solver (Runge-Kutta 2nd order) and ROOT for visualization.

---

## Code Overview

- The simulation reads initial conditions (mass, position, velocity) for each planet from a file named `fileInput`.
- Each planet is represented by an instance of the `PuntoMateriale` class, storing mass, position, and velocity as `Vettore` objects.
- The internal gravitational force on each planet is calculated by the function `fInterna`, which sums contributions from other planets.
- External forces are currently set to zero (`fEsterna`).
- The `OdeSolver` class (implemented elsewhere) manages the numerical integration of the equations of motion.
- The simulation uses a fixed timestep (`Passo(1)`) and integrates until the simulation time reaches 1000 units.
- ROOT's `TGraph` objects are used to plot the XY trajectory of each planet in real time.
- The main loop updates positions and appends points to each planet's graph every 10 steps, refreshing the canvas to show the evolving orbits.
- Colors and marker styles differentiate planets visually.

---

## Key functions

- `fInterna(i, j, t, p)`: Computes the gravitational force exerted by planet `j` on planet `i` at time `t`.
- `fEsterna(i, t, p)`: Placeholder for any external forces (currently returns zero).
- `main()`: 
  - Reads initial conditions,
  - Initializes the solver,
  - Creates ROOT graphs for visualization,
  - Runs the time integration loop with real-time updates.

---

## Notes

- The number of planets is determined by the number of lines in the input file `fileInput`.
- To change the number of planets or initial conditions, modify the input file accordingly.
- The graphical update loop uses `gSystem->ProcessEvents()` to allow ROOT to refresh the display while integrating.

---

## Compilation

Compilation is handled via the included `Makefile`. Simply run:

```bash
make