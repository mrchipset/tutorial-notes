
import numpy as np

import matplotlib.pyplot as plt

import numpy.linalg



if __name__ == '__main__':
    # Parameters
    max_iterations = 10000
    tolerance = 0.1
    # Define dimensions of simulation space
    h = 1
    x = np.arange(0, 122, h)
    y = np.arange(0, 102, h)
    # Allocate memory for storing potential function and electric field
    V = np.zeros((np.size(x), np.size(y)))
    Ex = np.zeros(V.shape)
    Ey = np.zeros(V.shape)
    # Apply voltage at electrodes
    V[61, 101] = -100
    V[0, 50] = 100
    V[121, 50] = 100
    V[60, 0] = -100
    # Calculate electric potential
    for iter in range(max_iterations):
        oldV = V.copy()
        for i in range(1, np.size(x) - 1):
            for j in range(1, np.size(y) - 1):
                # Traverse mesh and update
                V[i, j] = (V[i+1, j] + V[i-1, j] + V[i, j+1] + V[i, j-1]) / 4
        # Check if converged
        err = np.max(numpy.abs((V[1:x.size-2, 1:y.size-2] - oldV[1:x.size-2, 1:y.size-2])/V[1:x.size-2, 1:y.size-2]))
        print('Iteration:', iter, 'Error:', err)
        if err < tolerance:
            print('Solution converged')
            break
    # Calculate x-component of electric field
    for i in range(1, x.size-1):
        Ex[i, :] = -(V[i, :] - V[i+1, :])/(x[i] - x[i+1])
    # Calculate y-component of electric field
    for i in range(1, y.size-1):
        Ey[:, i] = -(V[:, i] - V[:, i+1]) / (y[i] - y[i+1])
    V = np.transpose(V)
    Ex = np.transpose(Ex)
    Ey = np.transpose(Ey)
    levels = np.arange(-100, 100, 20)
    cs = plt.contourf(x, y, V, levels, origin='upper')
    cs2 = plt.contour(cs, colors='k', linewidths=(1,), origin='upper')
    cbar = plt.colorbar(cs)
    cbar.add_lines(cs2)
    plt.streamplot(x, y, Ex, Ey, color='k')
    plt.savefig('potential_plot.png')
    plt.show()