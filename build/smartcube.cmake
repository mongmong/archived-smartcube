
#set(CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(output_dir ${PROJECT_SOURCE_DIR}/output)
#set(output_dir ${CMAKE_CURRENT_SOURCE_DIR}/../output)
set(LIBRARY_OUTPUT_PATH ${output_dir}/lib)
set(EXECUTABLE_OUTPUT_PATH ${output_dir}/bin)

set(cmd_cxxtestgen
    python ${PROJECT_SOURCE_DIR}/contrib/cxxtest/cxxtestgen.py
    )
set(cmd_antlr
    sh ${PROJECT_SOURCE_DIR}/contrib/antlr/antlr.sh
    )

add_definitions(
    -finline-functions
    -m128bit-long-double
    -pipe
    -Wall
    -Wno-unused-parameter
    -Wformat
    -Wconversion
    -Wdeprecated
    )
    