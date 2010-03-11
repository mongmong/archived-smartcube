#!/usr/bin/env python

import math
import smartcube

class SampleRoutine(smartcube.Routine):
    def __init__(self, config):
        super(SampleRoutine, self).__init__()

        print config

    def handle(self, input, output):
        linenum = 1
        a = input.pop()
        while a:
            a.insert(0, False)
            linenum += 1
            output.push(a)
            a = input.pop()


__routine__ = SampleRoutine



