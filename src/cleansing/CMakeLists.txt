cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# column operators
#

# xbackfill
add_executable(xcls.backfill
    ${COMMON_SRCS}
    Backfill.h
    Backfill.cpp
    BackfillApp.h
    BackfillApp.cpp
    )
target_link_libraries(xcls.backfill
    ${COMMON_LIBS}
    )
    
