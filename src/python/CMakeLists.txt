cmake_minimum_required(VERSION 2.6)

#
# aggregate operators
#

# xpython
add_executable(xpython
    ${COMMON_SRCS}
    InputWrapper.h
    InputWrapper.cpp
    Module.h
    Module.cpp
    OutputWrapper.h
    OutputWrapper.cpp
    PythonWrapperApp.h
    PythonWrapperApp.cpp
    RecordHelper.h
    RecordHelper.cpp
    RoutineWrapper.h
    RoutineWrapper.cpp
    )
target_link_libraries(xpython
    ${COMMON_LIBS}
    boost_python
    python2.6
    )


    