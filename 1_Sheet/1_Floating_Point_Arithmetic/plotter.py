# creates log-log plot of errors
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("rel_err_float.csv")
data2 = pd.read_csv("rel_err_double.csv")

k_values = data['k']
relative_errors = data['relative_error']

# plot
plt.loglog(k_values, relative_errors, marker='o', linestyle='-', color='blue', label='Relative Error float')

k_values2 = data2['k']
relative_errors2 = data2['relative_error']

# plot
plt.loglog(k_values2, relative_errors2, marker='o', linestyle='-', color='red', label='Relative Error double')

# Labels and grid
plt.xlabel('k (number of terms)')
plt.ylabel('Relative Error')
plt.title('Relative Error vs k (log-log scale)')
plt.grid(True, which="both", ls="--", linewidth=0.5)
plt.legend()

# Show plot
plt.tight_layout()
plt.savefig("accuracy.jpg")