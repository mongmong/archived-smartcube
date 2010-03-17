cmake_minimum_required(VERSION 2.6)

#
# aggregate operators
#

# xmatrix.sql
add_custom_target(xmatrix.sql ALL 
    cp MatrixSQL.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xmatrix.sql ${EXECUTABLE_OUTPUT_PATH}
    )
    
add_custom_target(xmatrix.diff ALL
    COMMAND cp MatrixDiff.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xmatrix.diff ${EXECUTABLE_OUTPUT_PATH}
    )