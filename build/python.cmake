FIND_PACKAGE(PythonLibs)

if(PYTHONLIBS_FOUND)
    message(STATUS "Python header files found at ${PYTHON_INCLUDE_DIRS}")
    message(STATUS "Python library files foundat at ${PYTHON_LIBRARIES}")
    
    include_directories(${PYTHON_INCLUDE_DIRS})
    link_directories(${PYTHON_LIBRARIES})
else(PYTHONLIBS_FOUND)
    message(fatal_error "Cannot find Python libs.")
    
    include_directories("/usr/include")
    link_directories("/usr/lib")
endif(PYTHONLIBS_FOUND)

