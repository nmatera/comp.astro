import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("orbit.csv")

for body in ['M', 'H']:
    for method in ['fixed', 'newton']:
        subset = df[(df['body'] == body) & (df['method'] == method)]
        plt.scatter(subset['x'], subset['y'], label=f'{body}-{method}', s=5)
    plt.axis('equal')
    plt.legend()
    if body == 'M':
        plt.title(f"Orbit of Mercury")
        
    elif body == 'H':
        plt.title(f"Orbits of Halley's comet and Mercury")
    plt.xlabel("x [AU]")
    plt.ylabel("y [AU]")
    plt.grid(True)
    plt.savefig(f"plot{body}.jpg")

