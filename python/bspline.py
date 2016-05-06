#!/usr/bin/python

from mpl_toolkits.mplot3d import  axes3d,Axes3D
import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import scipy.interpolate
import math

fig = plt.figure('Curve')
ax = fig.gca(projection='3d')

#degree = 3
degree = 4
#controlPolygon = np.array([[0.,0.,0.], [0.,6.,1.], [-1.,5.,2.], [-3.,8.,3.], [-1.,14.,4.],[2.,14.,5.],[4.,8.,6.], [2.,5.,7.], [1.,6.,8.], [1.,0.,9.]])
controlPolygon = np.array([[0.,0.,0.], [0.,6.,10.], [-1.,5.,2.], [-3.,8.,13.], [-1.,14.,4.],[2.,14.,15.],[4.,8.,6.], [2.,5.,17.], [1.,6.,8.], [1.,0.,19.]])


x = controlPolygon[:,0]
y = controlPolygon[:,1]
z = controlPolygon[:,2]

polLen = 0.
for i in range(1, len(controlPolygon)):
    polLen += sp.spatial.distance.euclidean(controlPolygon[i-1], controlPolygon[i])

l = len(x)
t = np.linspace(0,1,l-degree+1,endpoint=True)
t = np.append([0]*degree,t)
t = np.append(t,[1]*degree)

#[knots, coeff, degree]
tck = [t,[x,y,z], degree]

u=np.linspace(0,1,(max(polLen*100,100)),endpoint=True)
out = sp.interpolate.splev(u, tck)
outD1 = sp.interpolate.splev(u, tck, 1)
outD2 = sp.interpolate.splev(u, tck, 2)
outD3 = sp.interpolate.splev(u, tck, 3)

spline = np.stack(out).T
splineD1 = np.stack(outD1).T
splineD2 = np.stack(outD2).T
splineD3 = np.stack(outD3).T

curvL = []
torsL = []
for i in range(len(u)):
    d1Xd2 = np.cross(splineD1[i], splineD2[i])
    Nd1Xd2 = np.linalg.norm(d1Xd2)

    currCurv = Nd1Xd2 / math.pow(np.linalg.norm(splineD1[i]),3)
    currTors = np.dot(d1Xd2, splineD3[i]) / math.pow(Nd1Xd2, 2)
    #currTors = np.linalg.det(np.stack([splineD1[i], splineD2[i], splineD3[i]]).T) / math.pow(np.linalg.norm(np.cross(splineD1[i], splineD2[i])), 2)
            
    curvL.append(currCurv)
    torsL.append(currTors)

curv = np.array(curvL)
tors = np.array(torsL)

ax.plot(out[0], out[1], out[2], '-')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.figure('Curvature')
plt.plot(u, curv, '.')

plt.figure('Torsion')
plt.plot(u, tors, '.')

plt.show()
