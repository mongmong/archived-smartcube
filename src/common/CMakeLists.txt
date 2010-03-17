cmake_minimum_required(VERSION 2.6)

#
# group operators
#
    
# xgroup
add_library(xcommon
    Cell.h
    Cell.cpp
    ConsoleApp.h
    ConsoleApp.cpp
    Error.h
    Error.cpp
    Input.h
    Input.cpp
    Output.h
    Output.cpp
    Routine.h
    Routine.cpp
    Record.h
    Record.cpp
    RecordPool.h
    RecordPool.cpp
    SharedQueue.h
    SharedQueue.cpp
    )
    
add_executable(testcompare
    TestCompare.cpp
    )
    
target_link_libraries(testcompare
    xcommon
    ${COMMON_LIBS}
    )
    