cmake_minimum_required(VERSION 2.6)

#
# logic operators
#

# xand
add_executable(xand
    ${COMMON_SRCS}
    And.h
    And.cpp
    AndApp.h
    AndApp.cpp
    )
target_link_libraries(xand
    ${COMMON_LIBS}
    )
    
# xor
add_executable(xor
    ${COMMON_SRCS}
    Or.h
    Or.cpp
    OrApp.h
    OrApp.cpp
    )
target_link_libraries(xor
    ${COMMON_LIBS}
    )
    
      