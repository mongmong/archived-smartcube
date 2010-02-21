cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# aggregate operators
#

# xcount
add_executable(xagg.count
    ${COMMON_SRCS}
    Count.h
    Count.cpp
    CountApp.h
    CountApp.cpp
    )
target_link_libraries(xagg.count
    ${COMMON_LIBS}
    )
 
# xsum
add_executable(xagg.sum
    ${COMMON_SRCS}
    Sum.h
    Sum.cpp
    SumApp.h
    SumApp.cpp
    )
target_link_libraries(xagg.sum
    ${COMMON_LIBS}
    )
    
# xhead
add_executable(xagg.head
    ${COMMON_SRCS}
    Head.h
    Head.cpp
    HeadApp.h
    HeadApp.cpp
    )
target_link_libraries(xagg.head
    ${COMMON_LIBS}
    )
    
# xtail
add_executable(xagg.tail
    ${COMMON_SRCS}
    Tail.h
    Tail.cpp
    TailApp.h
    TailApp.cpp
    )
target_link_libraries(xagg.tail
    ${COMMON_LIBS}
    )
    
