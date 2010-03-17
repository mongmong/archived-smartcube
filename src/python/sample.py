#!/usr/bin/env python

'''
Sample module for SmartCube xpython.
'''

import math
import smartcube

class SampleRoutine(smartcube.Routine):
    '''
    SampleRoutine
    '''
    def __init__(self, options, args):
        super(SampleRoutine, self).__init__()

        print options, args
        #print config

    def handle(self, input, output):
        print input.get_inputs()
        input = input.get_inputs()[1]
        linenum = 1
        a = input.pop()
        count = 0;
        while a:
            count = count + 1
            a.insert(0, False)
            a.insert(0, count)
            linenum += 1
            output.push(a)

            a = input.pop()


__routine__ = SampleRoutine


# vim:expandtab
