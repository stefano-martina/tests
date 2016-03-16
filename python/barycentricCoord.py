#!/usr/bin/python

from mpl_toolkits.mplot3d import  axes3d,Axes3D
import numpy as np
import matplotlib.pyplot as plt

triang = np.array([[0.,0.,0.],[0.,0.6,1.],[1.,1.,0.]])
alpha = [0.3, 0.5, 0.2]
coll = alpha[0]*triang[0] + alpha[1]*triang[1] + alpha[2]*triang[2]

tests = np.array([
#    0.*triang[0] + alpha[1]*triang[1] + (1-alpha[1])*triang[2],
    (1-alpha[1])*triang[0] + alpha[1]*triang[1] + 0.*triang[2]])

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot(triang[:,0], triang[:,1], triang[:,2], 'o')
ax.plot([coll[0]], [coll[1]], [coll[2]], 'ro')
ax.plot(tests[:,0], tests[:,1], tests[:,2], 'go')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.show()
