import numpy as np

v = np.array(['a','b','c','d','e','f','g'])
v1 = v[[1,2,3]]
v1[1] = 'x'
print(v)

v2 = v[3:6]
v2[1] = 'x'
print(v)

