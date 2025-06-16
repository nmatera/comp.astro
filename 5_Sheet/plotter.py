import numpy as np
import matplotlib.pyplot as plt

# Load data from file
data = np.loadtxt('output.dat', comments='#')  # Skip header line(s) starting with #

xi = data[:, 0]  # First column
w = data[:, 1]   # Second column
z = data[:, 2]   # Third column

# Plot w vs xi
plt.figure(figsize=(8, 6))
plt.plot(xi, w, label=r'$w(\xi)$', color='blue')
plt.xlabel(r'$\xi$')
plt.ylabel(r'$w$')
plt.title('Lane-Emden Solution')
plt.grid(True)
plt.legend()
plt.savefig("plot.jpg")
