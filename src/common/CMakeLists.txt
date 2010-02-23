cmake_minimum_required(VERSION 2.6)

include(${PROJECT_SOURCE_DIR}/build/poco.cmake)
include(${PROJECT_SOURCE_DIR}/build/boost.cmake)
include(${PROJECT_SOURCE_DIR}/build/smartcube.cmake)
include(${PROJECT_SOURCE_DIR}/src/common/common.cmake)

#
# group operators
#
    
# xgroup
add_library(xcommon
    ../common/ConsoleApp.h
    ../common/ConsoleApp.cpp
    ../common/DummyInput.h
    ../common/DummyInput.cpp
    ../common/DummyOutput.h
    ../common/DummyOutput.cpp
    ../common/Error.h
    ../common/Error.cpp
    ../common/FileInput.h
    ../common/FileInput.cpp
    ../common/FileOutput.h
    ../common/FileOutput.cpp
    ../common/ForkOutput.h
    ../common/ForkOutput.cpp
    ../common/Input.h
    ../common/Input.cpp
    ../common/JoinInput.h
    ../common/JoinInput.cpp
    ../common/MemoryInput.h
    ../common/MemoryInput.cpp
    ../common/MemoryOutput.h
    ../common/MemoryOutput.cpp
    ../common/Output.h
    ../common/Output.cpp
    ../common/Routine.h
    ../common/Routine.cpp
    ../common/Record.h
    ../common/Record.cpp
    ../common/SharedQueue.h
    ../common/SharedQueue.cpp
    )
    