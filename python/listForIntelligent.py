#!/bin/python

h = [1,2,3,4,5,3,6,7,8,3,9,0]
print(h)
for i,v in enumerate(h):
    if v == 3:
        h.pop(i)

print(h)
