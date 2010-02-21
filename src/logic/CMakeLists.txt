cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# logic operators
#

# xlog.and
add_executable(xlog.and
    ${COMMON_SRCS}
    And.h
    And.cpp
    AndApp.h
    AndApp.cpp
    )
target_link_libraries(xlog.and
    ${COMMON_LIBS}
    )
    
# xlog.or
add_executable(xlog.or
    ${COMMON_SRCS}
    Or.h
    Or.cpp
    OrApp.h
    OrApp.cpp
    )
target_link_libraries(xlog.or
    ${COMMON_LIBS}
    )
    
# xlog.xor
add_executable(xlog.xor
    ${COMMON_SRCS}
    Xor.h
    Xor.cpp
    XorApp.h
    XorApp.cpp
    )
target_link_libraries(xlog.xor
    ${COMMON_LIBS}
    )
    
# xlog.not
add_executable(xlog.not
    ${COMMON_SRCS}
    Not.h
    Not.cpp
    NotApp.h
    NotApp.cpp
    )
target_link_libraries(xlog.not
    ${COMMON_LIBS}
    )
    
# xlog.cmp
add_executable(xlog.cmp
    ${COMMON_SRCS}
    Cmp.h
    Cmp.cpp
    CmpApp.h
    CmpApp.cpp
    )
target_link_libraries(xlog.cmp
    ${COMMON_LIBS}
    )
    
# xlog.eq
add_executable(xlog.eq
    ${COMMON_SRCS}
    Eq.h
    Eq.cpp
    EqApp.h
    EqApp.cpp
    )
target_link_libraries(xlog.eq
    ${COMMON_LIBS}
    )

# xlog.ne
add_executable(xlog.ne
    ${COMMON_SRCS}
    Ne.h
    Ne.cpp
    NeApp.h
    NeApp.cpp
    )
target_link_libraries(xlog.ne
    ${COMMON_LIBS}
    )

# xlog.ge
add_executable(xlog.ge
    ${COMMON_SRCS}
    Ge.h
    Ge.cpp
    GeApp.h
    GeApp.cpp
    )
target_link_libraries(xlog.ge
    ${COMMON_LIBS}
    )

# xlog.gt
add_executable(xlog.gt
    ${COMMON_SRCS}
    Gt.h
    Gt.cpp
    GtApp.h
    GtApp.cpp
    )
target_link_libraries(xlog.gt
    ${COMMON_LIBS}
    )

# xlog.le
add_executable(xlog.le
    ${COMMON_SRCS}
    Le.h
    Le.cpp
    LeApp.h
    LeApp.cpp
    )
target_link_libraries(xlog.le
    ${COMMON_LIBS}
    )

# xlog.lt
add_executable(xlog.lt
    ${COMMON_SRCS}
    Lt.h
    Lt.cpp
    LtApp.h
    LtApp.cpp
    )
target_link_libraries(xlog.lt
    ${COMMON_LIBS}
    )

        
      