import finite_diff_solver
import numpy as np
import pylab as p
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import time

def set_charge_region(radius):
    #Create charged disc region    
    size_sides = 2*(radius)+1     
    charge_region = np.zeros((int(size_sides), int(size_sides)))    
    region_length = len(charge_region)
    middle_point = (region_length-1)//2        
    values = range(region_length)   
    for i in values :
        for j in values:
            if ((i-middle_point)**2+(j-middle_point)**2)**(1/2)<=radius:
                charge_region[i, j] = 1
    return charge_region
    
def set_total_density(num_vertices=500, radius=0.5, charge=5, distance=0.15):
    radius*=(num_vertices*0.5)
    radius=int(radius)
    #Creates the total charge distribution    
    density= np.zeros((num_vertices, num_vertices), float)
    plus_density= charge/(np.pi*radius**2)
    offset_from_center = distance/2*np.cos(np.deg2rad(45))
    plus_position = int((0.5-offset_from_center)*num_vertices)
    minus_position = int((0.5+offset_from_center)*num_vertices)
    charge_region = set_charge_region(radius)*plus_density    
    density[plus_position-radius:plus_position+(radius+1), plus_position-radius:plus_position+(radius+1)] = charge_region    
    density[minus_position-radius:minus_position+(radius+1), plus_position-radius:plus_position+(radius+1)] = -1*charge_region    
    density[minus_position-radius:minus_position+(radius+1), minus_position-radius:minus_position+(radius+1)] = 1*charge_region
    density[plus_position-radius:plus_position+(radius+1), minus_position-radius:minus_position+(radius+1)] = -1*charge_region

    return density
   
number_vertices = 150
density = set_total_density(number_vertices, 0.1, 5, distance=0.15)

#Set up the grid environment and make plot
axis = np.arange(0, 1., 1./number_vertices)

#Meshgrid returns a two element array, one containing the x array, the other y
X, Y = p.meshgrid(axis, axis)

precision_value = 1e-06
solution = finite_diff_solver.simple(number_vertices, precision_value, density)
    
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, solution, cmap = cm.bwr,linewidth=0, antialiased=True, rstride=1, cstride=1)    
ax.azim=-45
ax.set_zlabel('Potential')
ax.set_xlabel('$x$')
ax.set_ylabel('$y$')
plt.title('Solution of Poisson equation (prec=+'+str(precision_value)+')', y=1.08)
plt.show()
