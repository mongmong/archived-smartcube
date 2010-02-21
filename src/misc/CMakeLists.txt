cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

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
  