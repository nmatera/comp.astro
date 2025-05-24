import numpy as np
from scipy.constants import G
from scipy.optimize import root_scalar

# Constants
M = 5.974e24      # Mass of Earth in kg
m = 7.348e22      # Mass of Moon in kg
R = 3.844e8       # Distance between Earth and Moon in meters
omega = 2.662e-6  # Orbital frequency in s^-1

# Function for L1 equation
def lagrange_L1_equation(r):
    return  G * M / r**2 - G * m / (R - r)**2 - omega**2 * r

# Solve using root_scalar with a bracketing method
sol = root_scalar(lagrange_L1_equation, bracket=[1e7, R - 1e6], method='brentq')

if sol.converged:
    print(f"L1 is located at r = {sol.root:.2f} meters from Earth's center.")
else:
    print("Root-finding did not converge.")
