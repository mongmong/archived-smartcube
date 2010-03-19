cmake_minimum_required(VERSION 2.6)

#
# aggregate operators
#

# xmatrix.sql
add_custom_target(xmatrix.sql ALL 
    COMMAND cp MatrixSQL.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xmatrix.sql.sh ${EXECUTABLE_OUTPUT_PATH}/xmatrix.sql
    )
    
add_custom_target(xmatrix.contrib ALL
    COMMAND cp MatrixContrib.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xmatrix.contrib.sh ${EXECUTABLE_OUTPUT_PATH}/xmatrix.contrib
    )
    
add_custom_target(xmatrix.diff ALL
    COMMAND cp MatrixDiff.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xmatrix.diff.sh ${EXECUTABLE_OUTPUT_PATH}/xmatrix.diff
    )
    
    