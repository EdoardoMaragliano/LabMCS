# OdeSolverRelativistica – Relativistic Motion Simulation

This folder contains a C++ implementation for simulating the motion of charged particles under electromagnetic forces using relativistic ODE solvers.

## 📁 Components

- `Main.cpp`, `MainPM.cpp`: simulation entry points
- `OdeSolver.cpp/h`, `OdeSolverRel.cpp/h`: numerical solvers (classical and relativistic)
- `Vettore.cpp/h`, `PuntoMateriale.cpp/h`, `Particella.h`, `Elettrone.cpp/h`: class definitions for physical entities
- `fB.h`: external magnetic field configuration
- `Makefile`: compilation script

## 🎯 Goal

Numerically solve the relativistic equations of motion for particles in electromagnetic fields using a modular class-based approach.
