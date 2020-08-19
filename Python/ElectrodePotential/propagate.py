# -*- coding: utf-8 -*-
import math
import numpy as np
import matplotlib.pyplot as plt



#Constants
GNa = 120 #Maximal conductance(Na+) ms/cm2
Gk = 36 #Maximal condectance(K+) ms/cm2
Gleak = 0.3 #Maximal conductance(leak) ms/cm2
cm = 1 #Cell capacitance uF/cm2
delta = 0.01 #Axon condectivity ms2
ENa = 50 #Nernst potential (Na+) mV
Ek = -77 #Nernst potential (K+) mV
Eleak = -54.4 #Nernst potential (leak) mV



#Simulation Parameters
simulation_time = 25.0 #ms
domain_length = 4 #cm
dt = 0.001 #ms
dx = 0.1 #cm
x = np.arange(0,domain_length,dx)
time = np.arange(0,simulation_time,dt)



#Convenience variables 
a1 = delta*dt/(dx*dx*cm)  #V(i-1,t)
a2 = 1 - 2*delta*dt/(dx*dx*cm) #V(i,t)  
a3 = delta*dt/(dx*dx*cm) #V(i+1,t)

#Solution matrix
V = np.zeros((len(x),len(time)))
M = np.zeros((len(x),len(time)))
N = np.zeros((len(x),len(time)))
H = np.zeros((len(x),len(time)))
V_initial = -70  #mV

#Initial condition
#When t=0, V=-70mV M=N=H=0

V[:,0] = V_initial
M[:,0] = 0
N[:,0] = 0
H[:,0] = 0

#time loop
for n in range(0,len(time)-1):  
    #loop over space
    for i in range(1,len(x)-1): 
        if   n*dt <= 0.9 and n*dt >= 0.5 and i*dx <= 0.3:
            Istim = -25 #uA/cm2
        else:
            Istim = 0

        
        #Convenience variables 
        INa = GNa*math.pow(M[i,n],3)*H[i,n]*(V[i,n]-ENa)
        Ik = Gk*math.pow(N[i,n],4)*(V[i,n]-Ek)
        Ileak = Gleak*(V[i,n]-Eleak)
        Iion = INa + Ik + Ileak + Istim

        
        #FTCS
        V[i,n+1] = a1*V[i-1,n] + a2*V[i,n] + a3*V[i+1,n] - dt*Iion/cm
        #Gating variables:M
        aM = (40+V[i,n])/(1-math.exp(-0.1*(40+V[i,n])))
        bM = 0.108*math.exp(-V[i,n]/18)
        Minf = aM/(aM+bM)
        tM = 1/(aM+bM)
        M[i,n+1] = M[i,n] + dt*(Minf-M[i,n])/tM

        #Gating variables:H
        aH = 0.0027*math.exp(-V[i,n]/20)  
        bH = 1/(1+math.exp(-0.1*(35-V[i,n])))  
        Hinf = aH/(aH+bH)
        tH = 1/(aH+bH)
        H[i,n+1] = H[i,n] + dt*(Hinf-H[i,n])/tH
        #Gating variables:N
        aN = 0.01*(55+V[i,n])/(1-math.exp(-0.1*(55+V[i,n])))
        bN = 0.055*math.exp(-V[i,n]/80)
        Ninf = aN/(aN+bN)
        tN = 1/(aN+bN)
        N[i,n+1] = N[i,n] + dt*(Ninf-N[i,n])/tN
    #No flux boundary condition at both end    
    V[0,n+1] = V[1,n+1]    
    V[len(x)-1,n+1] = V[len(x)-2,n+1] 




#Conduction velocity
Max1 = np.argmax(V[0,:])
Max2 = np.argmax(V[len(x)-1,:])
print(domain_length/((Max2-Max1)*dt))



#Plot V versus time for the first and last node of the axon.
plt.figure(1)
plt.clf()
plt.plot(time,V[0,:],'r-',time,V[len(x)-1,:],'b-')
plt.show()

