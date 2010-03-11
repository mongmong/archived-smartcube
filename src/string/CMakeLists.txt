cmake_minimum_required(VERSION 2.6)

#
# string operatoers
#

    
# xlen
add_executable(xstr.len
    ${COMMON_SRCS}
    Len.h
    Len.cpp
    LenApp.h
    LenApp.cpp
    )
target_link_libraries(xstr.len
    ${COMMON_LIBS}
    )

# xxformat
add_executable(xstr.xformat
    ${COMMON_SRCS}
    ReFormat.h
    ReFormat.cpp
    ReFormatApp.h
    ReFormatApp.cpp
    )
target_link_libraries(xstr.xformat
    ${COMMON_LIBS}
    )
    
# xxreplace
add_executable(xstr.xreplace
    ${COMMON_SRCS}
    ReReplace.h
    ReReplace.cpp
    ReReplaceApp.h
    ReReplaceApp.cpp
    )
target_link_libraries(xstr.xreplace
    ${COMMON_LIBS}
    )
    
# xstrip
add_executable(xstr.strip
    ${COMMON_SRCS}
    Strip.h
    Strip.cpp
    StripApp.h
    StripApp.cpp
    )
target_link_libraries(xstr.strip
    ${COMMON_LIBS}
    )
    
# xsubstr
add_executable(xstr.substr
    ${COMMON_SRCS}
    Substr.h
    Substr.cpp
    SubstrApp.h
    SubstrApp.cpp
    )
target_link_libraries(xstr.substr
    ${COMMON_LIBS}
    )
  
   