import numpy as np

np.pi = 5.
npoints = 1000000
eps = 1.0e-14

X = np.linspace(0., 2*np.pi, npoints)
res = np.sin(X) * np.sin(X) + np.cos(X) * np.cos(X) - 1

if any(res > abs(eps)) : 
    print("The relation does not hold")
else :
    print("The relation holds for all points")

