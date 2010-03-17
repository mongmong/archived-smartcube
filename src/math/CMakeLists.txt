cmake_minimum_required(VERSION 2.6)

#
# math operators
#

# xadd
add_executable(xmath.add
    ${COMMON_SRCS}
    Add.h
    Add.cpp
    AddApp.h
    AddApp.cpp
    )
target_link_libraries(xmath.add
    ${COMMON_LIBS}
    )

# xsub
add_executable(xmath.sub
    ${COMMON_SRCS}
    Sub.h
    Sub.cpp
    SubApp.h
    SubApp.cpp
    )
target_link_libraries(xmath.sub
    ${COMMON_LIBS}
    )

# xmul
add_executable(xmath.mul
    ${COMMON_SRCS}
    Mul.h
    Mul.cpp
    MulApp.h
    MulApp.cpp
    )
target_link_libraries(xmath.mul
    ${COMMON_LIBS}
    )

# xdiv
add_executable(xmath.div
    ${COMMON_SRCS}
    Div.h
    Div.cpp
    DivApp.h
    DivApp.cpp
    )
target_link_libraries(xmath.div
    ${COMMON_LIBS}
    )


# xfloor
add_executable(xmath.floor
    ${COMMON_SRCS}
    Floor.h
    Floor.cpp
    FloorApp.h
    FloorApp.cpp
    )
target_link_libraries(xmath.floor
    ${COMMON_LIBS}
    )

# xceil
add_executable(xmath.ceil
    ${COMMON_SRCS}
    Ceil.h
    Ceil.cpp
    CeilApp.h
    CeilApp.cpp
    )
target_link_libraries(xmath.ceil
    ${COMMON_LIBS}
    )
    
# xround
add_executable(xmath.round
    ${COMMON_SRCS}
    Round.h
    Round.cpp
    RoundApp.h
    RoundApp.cpp
    )
target_link_libraries(xmath.round
    ${COMMON_LIBS}
    )
    
# xgrade
add_executable(xmath.grade
    ${COMMON_SRCS}
    Grade.h
    Grade.cpp
    GradeApp.h
    GradeApp.cpp
    )
target_link_libraries(xmath.grade
    ${COMMON_LIBS}
    )
    
# xlog
add_executable(xmath.log
    ${COMMON_SRCS}
    Log.h
    Log.cpp
    LogApp.h
    LogApp.cpp
    )
target_link_libraries(xmath.log
    ${COMMON_LIBS}
    )

# xexp
add_executable(xmath.exp
    ${COMMON_SRCS}
    Exp.h
    Exp.cpp
    ExpApp.h
    ExpApp.cpp
    )
target_link_libraries(xmath.exp
    ${COMMON_LIBS}
    )
    
add_executable(xmath.sign
    Sign.h
    Sign.cpp
    SignApp.h
    SignApp.cpp
    )
target_link_libraries(xmath.sign
    ${COMMON_LIBS}
    )
    