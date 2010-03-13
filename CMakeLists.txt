cmake_minimum_required(VERSION 2.6)

project(smartcube CXX)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/python.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)
include(${PROJECT_SOURCE_DIR}/src/io/io.cmake)

set(COMMON_LIBS
    xcommon
    xio
    PocoUtil
    PocoFoundation
    boost_iostreams
    boost_regex
    )
    
add_subdirectory(src)
