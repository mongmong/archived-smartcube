FIND_PACKAGE(PythonLibs)

if(PYTHONLIBS_FOUND)
    message(STATUS "Python header files found at ${PYTHON_INCLUDE_DIRS}")
    message(STATUS "Python library files foundat at ${PYTHON_LIBRARIES}")
else(Boost_FOUND)
    message(fatal_error "Could not found Python libs.")
endif(PYTHONLIBS_FOUND)

include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})
