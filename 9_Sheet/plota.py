import matplotlib.pyplot as plt
import numpy as np
import glob
import os

files = sorted(glob.glob("output/step_*.dat"))

for fname in files:
    data = np.loadtxt(fname)
    x = data[:, 0]
    rho = data[:, 1]
    plt.plot(x, rho)
    plt.xlabel('x')
    plt.ylabel('Density')
    plt.title(f"{fname}")
    plt.ylim(0.9, 1.4)
    plt.grid()
    plt.savefig(f"{fname.replace('.dat', '.png')}")
    plt.clf()


files = sorted(glob.glob("output/step_*.png"))

for i, fname in enumerate(files):
    new_name = f"output/frame_{i:04d}.png"
    os.rename(fname, new_name)

# to make video bash: ffmpeg -framerate 10 -i output/frame_%04d.png -pix_fmt yuv420p isothermal_evolution.mp4

