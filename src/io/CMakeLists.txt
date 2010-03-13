cmake_minimum_required(VERSION 2.6)

#
# group operators
#
    
# xgroup
add_library(xio
    DummyInput.h
    DummyInput.cpp
    DummyOutput.h
    DummyOutput.cpp
    SimpleInput.h
    SimpleInput.cpp
    SimpleOutput.h
    SimpleOutput.cpp
    ForkOutput.h
    ForkOutput.cpp
    JoinInput.h
    JoinInput.cpp
    MemoryInput.h
    MemoryInput.cpp
    MemoryOutput.h
    MemoryOutput.cpp
    )
    