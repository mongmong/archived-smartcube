#!/usr/bin/env python

'''
Calculate the contribution of matrix members.

Usage: xmatrix.contrib -- -g <group> -p <precision> <lambda> [<lambda> ...]

-g|--group=<group>            specify the number of group columns. [default: 1]
-p|--precision=<precision>    specify precision. [default:2]
-a|--absolute                 display absolute contribution.
-r|--relative                 display relative contribution. [default]
-t|--total                    display total difference.                  
<lambda>                      for example, be in following forms:
                                  1. full lambda:
                                        lambda x: x[0] + x[1]
                                  2. abbreviated lambda:
                                        x[0] + x[1]
'''
import getopt
import numpy as N

import smartcube

class MatrixContrib(smartcube.Routine):
    def __init__(self, config, args):
        super(MatrixContrib, self).__init__()

        opts, args = getopt.getopt(args, "g:p:art", ["group=", "precision=", "relative", "absolute", "total"])
        opts = dict(opts)

        self.groupby = 1
        if opts.has_key('-g'):
            self.groupby = int(opts['-g'])
        if opts.has_key('--group'):
            self.groupby = int(opts['--group'])

        self.precision = 2
        if opts.has_key('-p'):
            self.precision = int(opts['-p'])
        if opts.has_key('--precision'):
            self.precision = int(opts['--precision'])

        self.relative = True
        if opts.has_key('--absolute') or opts.has_key('-a'):
            self.relative = False

        self.total = False
        if opts.has_key('--total') or opts.has_key('-t'):
            self.total = True

        self.lambdas = []
        for i in args:
            if i.startswith('lambda'):
                self.lambdas.append(eval(i))
            else:
                self.lambdas.append(eval('lambda x: %s' % i))

        #print opts, args

    def handle(self, input, output):
        old = input.get_inputs()[0]
        new = input.get_inputs()[1]

        keys = set()
        mapold = {}
        mapnew = {}
        sumold = []
        sumnew = []

        # read old matrix
        l = old.pop()
        while l:
            key = '\t'.join(l[:self.groupby])
            values = l[self.groupby:]
            keys.add(key)
            mapold[key] = values

            if not len(sumold):
                sumold = N.array([0.0] * len(values))
            sumold = sumold + N.array(values, dtype = float)

            l = old.pop()

        sumoldex = list(sumold)
        for f in self.lambdas:
            sumoldex.append(f(sumold))
        sumoldex = N.array(sumoldex)
        #output.push(sumoldex)

        # read new matrix
        l = new.pop()
        while l:
            key = '\t'.join(l[:self.groupby])
            values = l[self.groupby:]
            keys.add(key)
            mapnew[key] = values

            if not len(sumnew):
                sumnew = N.array([0.0] * len(values))
            sumnew = sumnew + N.array(values, dtype = float)

            l = new.pop()

        sumnewex = list(sumnew)
        for f in self.lambdas:
            sumnewex.append(f(sumnew))
        sumnewex = N.array(sumnewex)
        #output.push(sumnewex)

        totaldiff = (sumnewex - sumoldex) / sumoldex

        if self.total:
            output.push(['-'] * self.groupby + list(N.round(totaldiff * 100, self.precision)))

        for key in keys:
            recold = []
            if mapold.has_key(key):
                recold = mapold[key]
            recnew = []
            if mapnew.has_key(key):
                recnew = mapnew[key]

            if not recold:
                recold = N.array([0.0] * len(recnew), dtype = float)
                recnew = N.array(recnew, dtype = float)
            elif not recnew:
                recold = N.array(recold, dtype = float)
                recnew = N.array([0.0] * len(recold), dtype = float)
            else:
                recold = N.array(recold, dtype = float)
                recnew = N.array(recnew, dtype = float)

            sum = sumold - recold + recnew

            sumex = list(sum)
            for f in self.lambdas:
                sumex.append(f(sum))
            sumex = N.array(sumex)
            #output.push(sumnewex)

            diff = (sumex - sumoldex) / sumoldex
            if self.relative:
                diff2 = diff / totaldiff
            else:
                diff2 = diff
            output.push(key.split('\t') + list(N.round(diff2 * 100, self.precision)))



__routine__ = MatrixContrib
