cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

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
    
   