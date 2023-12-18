import numpy as np
import matplotlib.pyplot as plt
from matplotlib import font_manager

font_dirs = ['C:\Windows\Fonts']
font_files = font_manager.findSystemFonts(fontpaths=font_dirs)
 
for font_file in font_files:
    font_manager.fontManager.addfont(font_file)

plt.rcParams['font.family'] = 'Latin Modern Roman'
plt.rcParams['mathtext.fontset'] = 'custom'
plt.rcParams['mathtext.rm'] = 'Latin Modern Roman'
plt.rcParams['mathtext.it'] = 'Latin Modern Roman:italic'
plt.rcParams['mathtext.bf'] = 'Latin Modern Roman:bold'
plt.rcParams['font.size'] = '12'

# Load data from Adams-Bashforth method
data = np.genfromtxt('adams_bashforth_results.dat')
x = data[:, 0]
y_adams_bashforth = data[:, 1]

# Analytical solution
C = 1  # Constant of integration
y_analytical = -x - 1 + 2 * np.exp(x)

# Plot results
plt.plot(x, y_adams_bashforth, label='Adams-Bashforth Method', color='red', marker='s', fillstyle='none', markersize=10)
plt.plot(x, y_analytical, label='Analytical Solution', color='black', linestyle='-.')
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.title('Comparison of Adams-Bashforth Method and Analytical Solution')
plt.legend()
plt.grid(True)
plt.show()