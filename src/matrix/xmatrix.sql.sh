#!/bin/sh

xpython=`dirname $0`/xpython
module=MatrixSQL

export PYTHONPATH=".:`dirname $0`:${PYTHONPATH}"

exec ${xpython} -m${module} "$@"
