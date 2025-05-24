import numpy as np
import matplotlib.pyplot as plt
from datetime import date, timedelta

# Orbital parameters
earth = {
    'a': 1.000,      # AU
    'e': 0.0167,
    'phi0': np.radians(102.95),
    'lambda0': np.radians(100.46)
}

mars = {
    'a': 1.524,
    'e': 0.0934,
    'phi0': np.radians(336.04),
    'lambda0': np.radians(355.45)
}

# Kepler's third law (P in years, a in AU)
def orbital_period(a):
    return a ** 1.5

# Mean anomaly M(t)
def mean_anomaly(lambda0, phi0, t, P, M0):
    return 2 * np.pi * t / P + M0

# Solve Kepler’s equation: E - e*sin(E) = M
def solve_kepler(M, e, tol=1e-9, max_iter=100):
    E = M if e < 0.8 else np.pi  # good starting guess
    for _ in range(max_iter):
        delta = (E - e * np.sin(E) - M) / (1 - e * np.cos(E))
        E -= delta
        if abs(delta) < tol:
            break
    return E

# True anomaly f from eccentric anomaly E
def true_anomaly(E, e):
    return 2 * np.arctan2(np.sqrt(1 + e) * np.sin(E / 2),
                          np.sqrt(1 - e) * np.cos(E / 2))

# Distance from Sun
def radius(a, e, f):
    return a * (1 - e**2) / (1 + e * np.cos(f))

# Cartesian position
def position(a, e, E):
    f = true_anomaly(E, e)
    r = radius(a, e, f)
    x = r * np.cos(f)
    y = r * np.sin(f)
    return x, y

# Compute days between two dates
start_date = date(1985, 1, 1)
end_date = date(2025, 5, 21)
num_days = (end_date - start_date).days

# Periods in years
P_earth = orbital_period(earth['a'])
P_mars = orbital_period(mars['a'])

# M0 from problem statement
M0_earth = earth['lambda0'] - earth['phi0'] - 15 * 2 * np.pi / P_earth
M0_mars = mars['lambda0'] - mars['phi0'] - 15 * 2 * np.pi / P_mars

# Store distances and times
distances = []
dates = []

for day in range(num_days + 1):
    t = day / 365.25  # time in years from 1985-01-01

    # Mean anomalies
    M_earth = mean_anomaly(earth['lambda0'], earth['phi0'], t, P_earth, M0_earth)
    M_mars = mean_anomaly(mars['lambda0'], mars['phi0'], t, P_mars, M0_mars)

    # Eccentric anomalies
    E_earth = solve_kepler(M_earth, earth['e'])
    E_mars = solve_kepler(M_mars, mars['e'])

    # Positions
    x_earth, y_earth = position(earth['a'], earth['e'], E_earth)
    x_mars, y_mars = position(mars['a'], mars['e'], E_mars)

    # Distance
    distance = np.sqrt((x_earth - x_mars)**2 + (y_earth - y_mars)**2)
    distances.append(distance)
    dates.append(start_date + timedelta(days=day))

# Plot
plt.figure(figsize=(12, 6))
plt.plot(dates, distances, label='Earth-Mars Distance (AU)')
plt.xlabel('Date')
plt.ylabel('Distance (AU)')
plt.title('Earth–Mars Distance from 1985 to 2025')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("ex1iiplot.jpg")
