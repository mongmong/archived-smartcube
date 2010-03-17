#!/bin/sh

xpython=`dirname $0`/xpython
module=MatrixSQL

exec ${xpython} -m${module} "$@"
