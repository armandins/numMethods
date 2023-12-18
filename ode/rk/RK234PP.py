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

data_2nd_order = np.loadtxt('runge_kutta_2nd_order.dat')
data_3rd_order = np.loadtxt('runge_kutta_3rd_order.dat')
data_4th_order = np.loadtxt('runge_kutta_4th_order.dat')

x_2nd_order, y_2nd_order = data_2nd_order[:, 0], data_2nd_order[:, 1]
x_3rd_order, y_3rd_order = data_3rd_order[:, 0], data_3rd_order[:, 1]
x_4th_order, y_4th_order = data_4th_order[:, 0], data_4th_order[:, 1]

# Analytical solution
x_analytical = np.linspace(0, 5, 100)
y_analytical = -x_analytical - 1 + 2 * np.exp(x_analytical)

plt.figure(figsize=(10, 6))
plt.plot(x_2nd_order, y_2nd_order, label='Runge-Kutta 2nd Order', color='blue', marker='*', fillstyle='none', markersize=10)
plt.plot(x_3rd_order, y_3rd_order, label='Runge-Kutta 3rd Order', color='red', marker='s', fillstyle='none', markersize=10)
plt.plot(x_4th_order, y_4th_order, label='Runge-Kutta 4th Order', color='black', marker='x', fillstyle='none', markersize=10)
plt.plot(x_analytical, y_analytical, label='Analytical Solution', color='green', linestyle='-.')
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.title('Runge-Kutta Comparison')
plt.legend()
plt.grid(True)
plt.show()