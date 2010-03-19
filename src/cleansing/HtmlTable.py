#!/usr/bin/env python

'''
Extract table content from html codes.

Usage: xcls.htmltable -- [-l|--list] <xpath> [<index>]

-l|--list                     list all available tables.                 
<xpath>                       specify the xpath.
<index>                       specify the index of element.
'''
import getopt
import lxml.html
import lxml.html.soupparser
import sys

import smartcube

reload(sys)
sys.setdefaultencoding('utf-8')

class HtmlTable(smartcube.Routine):
    def __init__(self, config, args):
        super(HtmlTable, self).__init__()

        opts, args = getopt.getopt(args, "l", ["list"])
        opts = dict(opts)

        self.list = False
        if opts.has_key('-l'):
            self.list = True
        if opts.has_key('--list'):
            self.list = True

        self.xpath = args[0]
        self.index = 0
        if len(args) > 1:
            self.index = int(args[1])

    def get_path(self, node):
        l = []
        while node is not None:
            l.append(node.tag)
            node = node.getparent()

        l.reverse()
        return '.'.join(l)

    def handle(self, input, output):
        lines = []
        l = input.pop()
        while l:
            lines.append('\t'.join(l))
            l = input.pop()

        html = '\n'.join(lines)

        root = None
        try:
            root = lxml.html.fromstring(html)
        except:
            root = lxml.html.soupparser.fromstring(html)

        table = root.xpath(self.xpath)

        if self.list:
            for i, t in enumerate(table):

                l = [i, t.tag, '%s[%s]' % (self.get_path(t), '|'.join(['%s=%s' % (k, t.attrib[k]) for k in t.attrib]))]
                output.push(l)
        else:
            for tr in table[self.index].xpath('tr'):
                l = []
                for td in tr.xpath('td|th'):
                    l.append(td.text)
                output.push(l)


__routine__ = HtmlTable
