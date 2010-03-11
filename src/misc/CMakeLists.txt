cmake_minimum_required(VERSION 2.6)

#
# misc operators
#

# xnorm
add_executable(xnorm
    ${COMMON_SRCS}
    Norm.h
    Norm.cpp
    NormApp.h
    NormApp.cpp
    )
target_link_libraries(xnorm
    ${COMMON_LIBS}
    )

# xmisc.tablecomparer
add_executable(xmisc.tablecomparer
    ${COMMON_SRCS}
    TableComparer.h
    TableComparer.cpp
    TableComparerApp.h
    TableComparerApp.cpp
    )
target_link_libraries(xmisc.tablecomparer
    ${COMMON_LIBS}
    )
  