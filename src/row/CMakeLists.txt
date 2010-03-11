cmake_minimum_required(VERSION 2.6)

#
# row operatoers
#

# xfilter
add_executable(xrow.filter
    ${COMMON_SRCS}
    Filter.h
    Filter.cpp
    FilterApp.h
    FilterApp.cpp
    )
target_link_libraries(xrow.filter
    ${COMMON_LIBS}
    )
    
   