#!/usr/bin/env python

import os
import sqlite3
import uuid
import smartcube

class MatrixSQL(smartcube.Routine):
    def __init__(self, config, args):
        super(MatrixSQL, self).__init__()

        self.sql = args[0]
        if config.has_key('smartcube.matrix.sql.db'):
            self.dbfile = config['smartcube.matrix.sql.db']
        else:
            self.dbfile = ''

    def handle(self, input, output):
        head = input.pop()

        create_sql = [
                     'create',
                     'table',
                     'T',
                     '(',
                     ]
        for i in xrange(len(head)):
            head[i] = head[i].replace('@', ' ')
        #    cname = fields[0]
        #    ctype = 'str'
        #    if len(fields) > 1:
        #        ctype = fields[1]
        #    create_sql.append("%s," % (cname));
        create_sql.append(','.join(head))

        create_sql.append(');')
        create_sql = '\n'.join(create_sql)

        if not self.dbfile:
            self.dbfile = '/tmp/%d.%s.sqlite' % (os.getpid(), str(uuid.uuid4()))
        try:
            conn = sqlite3.connect(self.dbfile)

            create_cur = conn.cursor()
            create_cur.execute(create_sql)
            create_cur.close()

            insert_sql = 'insert into T values (%s);' % ','.join(['?'] * len(head))
            insert_cur = conn.cursor()

            while True:
                cache = []
                rec = None
                for i in xrange(10000):
                    rec = input.pop()
                    if not rec:
                        break
                    cache.append(rec)

                insert_cur.executemany(insert_sql, cache)

                cache = []
                if not rec:
                    break

            insert_cur.close()

            select_cur = conn.cursor()
            select_cur.execute(self.sql)

            for rec in select_cur:
                output.push(rec)

            select_cur.close()

        except:
            raise
        finally:
            if self.dbfile and os.path.isfile(self.dbfile):
                os.unlink(self.dbfile);


__routine__ = MatrixSQL
