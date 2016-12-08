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


