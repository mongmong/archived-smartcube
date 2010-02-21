cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# row operatoers
#

# xenc.b64dec
add_executable(xenc.b64dec
    ${COMMON_SRCS}
    Base64Dec.h
    Base64Dec.cpp
    Base64DecApp.h
    Base64DecApp.cpp
    )
target_link_libraries(xenc.b64dec
    ${COMMON_LIBS}
    )
    
# xenc.b64enc
add_executable(xenc.b64enc
    ${COMMON_SRCS}
    Base64Enc.h
    Base64Enc.cpp
    Base64EncApp.h
    Base64EncApp.cpp
    )
target_link_libraries(xenc.b64enc
    ${COMMON_LIBS}
    )
    
# xenc.hexenc
add_executable(xenc.hexdec
    ${COMMON_SRCS}
    HexDec.h
    HexDec.cpp
    HexDecApp.h
    HexDecApp.cpp
    )
target_link_libraries(xenc.hexdec
    ${COMMON_LIBS}
    )
    
# xenc.b64enc
add_executable(xenc.hexenc
    ${COMMON_SRCS}
    HexEnc.h
    HexEnc.cpp
    HexEncApp.h
    HexEncApp.cpp
    )
target_link_libraries(xenc.hexenc
    ${COMMON_LIBS}
    )
    
   