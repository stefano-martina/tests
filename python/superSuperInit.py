#!/usr/bin/env python

class Grandmother:
    def __init__(self):
        print("I am the grandmother")

class Mother(Grandmother):
    def __init__(self):
        super(Mother, self).__init__()

        print("I am the mother")

class Daughter(Mother):
    def __init__(self):
        #super(Daughter, self).__init__()
        super(Mother, self).__init__()
        print("I am the daughter")

c = Daughter()

