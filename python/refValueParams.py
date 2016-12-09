import numpy as np

class Test:
    def setValue(self, param):
        self.att = param

    def changeValue(self):
        self.att[1] = 5

test1 = Test()
a = [1,2,3]
test1.setValue(a)
a[0] = 4
print(test1.att)

test1.changeValue()
print(a)


test2 = Test()
b = {0:'un', 1:'du', 2:'tre'}
test2.setValue(b)
b[3] = 'quat'
print(test2.att)

test2.changeValue()
print(b)

test3 = Test()
c = ([1,2,3], [4,5,6])
test3.setValue(c)
c[0][0] = 4
#c[1] = 0
print(test3.att)

