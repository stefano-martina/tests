#!/bin/python

import numpy as np
import scipy as sp
import scipy.spatial

testInside = [0.2, 0.5, 0.7]
testOutside = [3., 3., 3.]
points = [[1.,0.,1.], [1.,1.,0], [0.2,0.8,0.2], [0.,1.,1.], [0.4,0.8,0.9], [1.5,0.5,0.5], [0.,0.,0.], [1.,1.,1.], [0.6,0.1,0.7], [2.,0.5,0.5], [0.,1.,0.], [0.2,0.5,0.3], [0.,0.,1.], [1.,0.,0.]]

print('Test inside -> ', end='')
allPoints = points.copy()
allPoints.append(testInside)
chull = sp.spatial.ConvexHull(np.array(allPoints))
outside = False
for simplex in chull.simplices:
        if (testInside == chull.points[simplex[0]]).all() or (testInside == chull.points[simplex[1]]).all() or (testInside == chull.points[simplex[2]]).all():
                outside = True
                break

if outside:
        print("Outside")
else:
        print("Inside")
        

print('Test outside -> ', end='')
allPoints = points.copy()
allPoints.append(testOutside)
chull = sp.spatial.ConvexHull(np.array(allPoints))
outside = False
for simplex in chull.simplices:
        if (testOutside == chull.points[simplex[0]]).all() or (testOutside == chull.points[simplex[1]]).all() or (testOutside == chull.points[simplex[2]]).all():
                outside = True
                break

if outside:
        print("Outside")
else:
        print("Inside")
        



