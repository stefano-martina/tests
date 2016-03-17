#!/bin/python

def f1():
    return True,[1,2,3]

def f2():
    return False,[]

r1,v1 = f1()
print(r1)
print(v1)

r2,v2 = f2()
print(r2)
print(v2)

