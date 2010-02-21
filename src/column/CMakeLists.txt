cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# column operators
#

# xexpand
add_executable(xcol.expand
    ${COMMON_SRCS}
    Expand.h
    Expand.cpp
    ExpandApp.h
    ExpandApp.cpp
    )
target_link_libraries(xcol.expand
    ${COMMON_LIBS}
    )
    
# xselect
add_executable(xcol.select
    ${COMMON_SRCS}
    Select.h
    Select.cpp
    SelectApp.h
    SelectApp.cpp
    )
target_link_libraries(xcol.select
    ${COMMON_LIBS}
    )
    
# xsplit
add_executable(xcol.split
    ${COMMON_SRCS}
    Split.h
    Split.cpp
    SplitApp.h
    SplitApp.cpp
    )
target_link_libraries(xcol.split
    ${COMMON_LIBS}
    )
  
# xxsplit
add_executable(xcol.xsplit
    ${COMMON_SRCS}
    ReSplit.h
    ReSplit.cpp
    ReSplitApp.h
    ReSplitApp.cpp
    )
target_link_libraries(xcol.xsplit
    ${COMMON_LIBS}
    )
  
# xcombine
add_executable(xcol.combine
    ${COMMON_SRCS}
    Combine.h
    Combine.cpp
    CombineApp.h
    CombineApp.cpp
    )
target_link_libraries(xcol.combine
    ${COMMON_LIBS}
    )
