#!/bin/python

import numpy as np
import scipy as sp
import scipy.spatial

points = np.array([[1.,0.,1.], [1.,1.,0], [0.2,0.8,0.2], [0.,1.,1.], [0.4,0.8,0.9], [1.5,0.5,0.5], [0.,0.,0.], [1.,1.,1.], [0.6,0.1,0.7], [2.,0.5,0.5], [0.,1.,0.], [0.2,0.5,0.3], [0.,0.,1.], [1.,0.,0.]])

print('Conv hull ---------------------------------------')
chull = sp.spatial.ConvexHull(points)
for simplex in chull.simplices:
	print('({}, {}, {})'.format(chull.points[simplex[0]], chull.points[simplex[1]], chull.points[simplex[2]]))

print('Delaunay ----------------------------------------')
dela = sp.spatial.Delaunay(points)
for simplex in dela.simplices:
	print('({}, {}, {})'.format(dela.points[simplex[0]], dela.points[simplex[1]], dela.points[simplex[2]]))

