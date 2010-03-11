cmake_minimum_required(VERSION 2.6)

#
# bitwise operators
#

# xbit.and
add_executable(xbit.and
    ${COMMON_SRCS}
    BitAnd.h
    BitAnd.cpp
    BitAndApp.h
    BitAndApp.cpp
    )
target_link_libraries(xbit.and
    ${COMMON_LIBS}
    )
    
# xbit.or
add_executable(xbit.or
    ${COMMON_SRCS}
    BitOr.h
    BitOr.cpp
    BitOrApp.h
    BitOrApp.cpp
    )
target_link_libraries(xbit.or
    ${COMMON_LIBS}
    )
    
# xbit.xor
add_executable(xbit.xor
    ${COMMON_SRCS}
    BitXor.h
    BitXor.cpp
    BitXorApp.h
    BitXorApp.cpp
    )
target_link_libraries(xbit.xor
    ${COMMON_LIBS}
    )
    
# xbit.not
add_executable(xbit.not
    ${COMMON_SRCS}
    BitNot.h
    BitNot.cpp
    BitNotApp.h
    BitNotApp.cpp
    )
target_link_libraries(xbit.not
    ${COMMON_LIBS}
    ) 