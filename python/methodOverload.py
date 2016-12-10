#Don't work!

class Test():
    def method(self, a):
        print("first method ({})".format(a))

    def method(self, a, b):
        print("second method({}, {})".format(a, b))

test = Test()
test.method(1)
test.method(1, 2)

