import matplotlib.pyplot as plt
import numpy as np

def load_data(file):
    data = np.loadtxt(file, delimiter=",")
    return data[:,0], data[:,1]

x, u_up = load_data("upwind.csv")
_, u_central = load_data("central.csv")
_, u_lax = load_data("laxwendroff.csv")
_, u_exact = load_data("analytical.csv")

plt.figure(1)
plt.plot(x, u_exact, label="Analytical", color="black", linewidth=2)
plt.plot(x, u_up, label="Upwind", linestyle="--")
plt.legend()
plt.title("Linear Advection t=4")
plt.xlabel("x")
plt.ylabel("u(x, t=4)")
plt.grid()
plt.savefig("Upwind.jpg")

# plt.plot(x, u_exact, label="Analytical", color="black", linewidth=2)
plt.plot(x, u_lax, label="Lax-Wendroff", linestyle="--")
#plt.legend()
#plt.title("Linear Advection t=4")
#plt.xlabel("x")
#plt.ylabel("u(x, t=4)")
#plt.grid()
plt.savefig("Lax-Wendroff.jpg")


plt.figure(2)
plt.plot(x, u_exact, label="Analytical", color="black", linewidth=2)
plt.plot(x, u_central, label="Centered", linestyle="--")
plt.legend()
plt.title("Linear Advection t=4")
plt.xlabel("x")
plt.ylabel("u(x, t=4)")
plt.grid()
plt.savefig("Centered.jpg")
