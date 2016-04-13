#!/bin/python

class Mamma:
    def __init__(self, primo):
        self.a = primo

class Figlia(Mamma):
    def __init__(self, primo, secondo):
        super(Figlia, self).__init__(primo)
        self.b = secondo


figlia = Figlia('uno', 'due')
print('a: {}; b: {}'.format(figlia.a, figlia.b))
