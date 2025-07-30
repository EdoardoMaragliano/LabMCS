# EsFitII – Exponential Fit with ROOT

This folder contains scripts for fitting experimental data (e.g., exponential decay) using Python and ROOT.

## 📁 Key Files

- `fitexpbin.py`: performs exponential fit on binned data (Python)
- `fitexpbin_ROOT.py`: Python version using ROOT for fitting
- `fitexpbinext_ROOT.py`: extended version with data uncertainties
- `fitexp.C`, `fitexp_ROOT.C`: equivalent fit scripts written in C++ using ROOT
- `test.C`: test script for ROOT fitting
- `exp.dat`, `pendolo.dat`: experimental datasets

## 🎯 Goal

Compare implementations of exponential curve fitting using:
- Pure Python + SciPy
- Python with ROOT
- ROOT in C++
