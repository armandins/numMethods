import numpy as np
import matplotlib.pyplot as plt

# Load data from .dat files
data_2nd_order = np.loadtxt('runge_kutta_2nd_order.dat')
data_3rd_order = np.loadtxt('runge_kutta_3rd_order.dat')
data_4th_order = np.loadtxt('runge_kutta_4th_order.dat')

# Extract x and y values from the data
x_2nd_order, y_2nd_order = data_2nd_order[:, 0], data_2nd_order[:, 1]
x_3rd_order, y_3rd_order = data_3rd_order[:, 0], data_3rd_order[:, 1]
x_4th_order, y_4th_order = data_4th_order[:, 0], data_4th_order[:, 1]

# Plot the results with increased marker size
plt.figure(figsize=(10, 6))
plt.plot(x_2nd_order, y_2nd_order, label='Runge-Kutta 2nd Order', color='blue', marker='*', fillstyle='none', markersize=10)
plt.plot(x_3rd_order, y_3rd_order, label='Runge-Kutta 3rd Order', color='red', marker='s', fillstyle='none', markersize=10)
plt.plot(x_4th_order, y_4th_order, label='Runge-Kutta 4th Order', color='black', marker='x', fillstyle='none', markersize=10)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Comparison of Numerical Solutions with Different Orders')
plt.legend()
plt.grid(True)
plt.show()
