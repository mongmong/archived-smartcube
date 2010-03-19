#!/bin/sh

xpython=`dirname $0`/xpython
module=HtmlTable

export PYTHONPATH=".:`dirname $0`:${PYTHONPATH}"

exec ${xpython} -m${module} "$@"
