import numpy as np
import matplotlib.pyplot as plt
from numba import njit, prange

# === Simulation Parameters ===
N = 1000
R = 0.75
M = 2.0
mass = M / N
dim = 3
gamma = 2.0
K = 1e-1
nu = 1e-1
lambda_ = 2.01203286081606
h = 0.2
dt = 1e-2
t_end = 20.0
steps = int(t_end / dt)

# === Cubic Spline Kernel & Derivative ===
@njit
def kernel(r, h):
    q = r / h
    sigma = 1 / (np.pi * h**3)
    if q < 0.5:
        return sigma * (6 * (q**3 - q**2) + 1)
    elif q < 1.0:
        return sigma * (2 * (1 - q)**3)
    return 0.0

@njit
def grad_kernel(rij, r, h):
    q = r / h
    sigma = 1 / (np.pi * h**3)
    if q == 0 or r == 0:
        return np.zeros(3)
    if q < 0.5:
        grad = sigma * (18 * q**2 - 12 * q) / h
    elif q < 1.0:
        grad = -6 * sigma * (1 - q)**2 / h
    else:
        grad = 0.0
    return grad * rij / r

# === SPH Core Functions ===
@njit(parallel=True)
def compute_density(pos):
    rho = np.zeros(N)
    for i in prange(N):
        for j in range(N):
            r = np.linalg.norm(pos[i] - pos[j])
            rho[i] += mass * kernel(r, h)
    return rho

@njit(parallel=True)
def compute_pressure(rho):
    return K * rho**gamma

@njit(parallel=True)
def compute_acceleration(pos, vel, rho, pressure):
    acc = np.zeros((N, 3))
    for i in prange(N):
        for j in range(N):
            if i == j:
                continue
            rij = pos[i] - pos[j]
            r = np.linalg.norm(rij)
            if r > h:
                continue
            p_term = (pressure[i]/rho[i]**2 + pressure[j]/rho[j]**2)
            acc[i] += -mass * p_term * grad_kernel(rij, r, h)
        acc[i] += -lambda_ * pos[i] - nu * vel[i]
    return acc

# === Time Integration ===
@njit
def euler_step(pos, vel, acc):
    return pos + dt * vel, vel + dt * acc

# === Initial Conditions ===
def generate_initial_positions():
    data = np.loadtxt("random_distribution.dat")
    pos = data[:, 0:3]  # x, y, z
    return pos

# === Main Simulation ===
def run_simulation():
    pos = generate_initial_positions()
    vel = np.zeros((N, 3))

    for step in range(steps):
        rho = compute_density(pos)
        pressure = compute_pressure(rho)
        acc = compute_acceleration(pos, vel, rho, pressure)
        pos, vel = euler_step(pos, vel, acc)

        if step % 100 == 0:
            print(f"Step {step}/{steps}")

    return pos, rho

# === Plotting ===
def plot_radial_density(pos, rho):
    r = np.linalg.norm(pos, axis=1)
    bins = np.linspace(0, 2 * R, 50)
    hist, edges = np.histogram(r, bins=bins, weights=rho)
    count, _ = np.histogram(r, bins=bins)
    radial_rho = hist / (count + 1e-5)
    centers = 0.5 * (edges[1:] + edges[:-1])

    # Analytical
    n = 1
    analytical = (lambda_ / (2 * K * (1 + n)) * (R**2 - centers**2))
    analytical = np.clip(analytical, 0, None) ** n

    plt.plot(centers, radial_rho, label="Simulated")
    plt.plot(centers, analytical, label="Analytic", linestyle="--")
    plt.xlabel("Radius r")
    plt.ylabel("Density ρ")
    plt.title("Radial Density Profile")
    plt.legend()
    plt.grid()
    plt.tight_layout()
    plt.savefig("radial_density.png", dpi=300)
    plt.show()

# === Entry Point ===
if __name__ == "__main__":
    pos, rho = run_simulation()
    plot_radial_density(pos, rho)
