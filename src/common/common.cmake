cmake_minimum_required(VERSION 2.6)

set(COMMON_SRCS
    )
    
set(COMMON_LIBS
    xcommon
    PocoUtil
    PocoFoundation
    boost_iostreams
    boost_regex
    )
    
cmake_policy(SET CMP0011 NEW)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
