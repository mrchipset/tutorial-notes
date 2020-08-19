def overrelaxation(no_intervals, precision, charge_density, relax_param):
    import numpy as np
    
    solution = np.zeros((no_intervals, no_intervals), float)
    mult_constant = np.pi*(1./no_intervals**2)
        
    charge = mult_constant*charge_density
    current_precision = 1.0
    iteration=1
    
    while current_precision>precision:
        old = solution
        solution = np.zeros((no_intervals, no_intervals), float)        
        for i in range(1, no_intervals-1):
            for j in range(1, no_intervals-1):
                solution[i, j] = old[i, j] +relax_param*(0.25*(old[i+1, j]+solution[i-1, j]+old[i, j+1]+solution[i, j-1])+charge[i, j]-old[i, j])                                        
        current_precision = abs(np.max(old-solution))
        iteration+=1
    return solution

def gauss_seidel(no_intervals, precision, charge_density):
    import numpy as np
    
    solution = np.zeros((no_intervals, no_intervals), float)
    mult_constant = np.pi*(1./no_intervals**2)
        
    charge = mult_constant*charge_density
    current_precision = 1.0
    iteration = 1
    
    while current_precision>precision:
        old = solution
        solution = np.zeros((no_intervals, no_intervals), float)
        for i in range(1, no_intervals-1):
            for j in range(1, no_intervals-1):
                solution[i, j] = 0.25*(old[i+1, j]+solution[i-1, j]+old[i, j+1]+solution[i, j-1])+charge[i, j]                        
        
        current_precision = np.max(old-solution)
        iteration+=1
    return solution

def simple(no_intervals, precision, charge_density):
    import numpy as np
    from scipy.ndimage import convolve 
    weights = np.array([[0, 0.25, 0], [0.25, 0, 0.25], [0, 0.25, 0]])
    charge = np.pi*(1./no_intervals**2)*charge_density    
    solution = np.zeros((no_intervals, no_intervals), float)     
    
    current_precision = 1
    iteration = 1    
    
    while current_precision>precision:
        old = solution        
        solution = convolve(solution, weights, mode='constant')+charge
        solution[0, :]=0
        solution[no_intervals-1, :] =0
        solution[:, 0] = 0
        solution[:, no_intervals-1]=0                
        current_precision = np.max(old-solution)
        iteration+=1
    return solution
    
