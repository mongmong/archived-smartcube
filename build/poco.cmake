find_path(POCO_INCLUDE_DIR Poco/Poco.h
    /usr/include
    /usr/local/include
    /opt/include
    /opt/local/include
    )
    
find_library(POCO_LIBRARY_PATH libPocoXML.8.dylib
    /usr/lib
    /usr/local/lib
    /opt/lib
    /opt/local/lib
    )    
    
if(POCO_INCLUDE_DIR)
    message(STATUS "Poco header files found at ${POCO_INCLUDE_DIR}")
else(POCO_INCLUDE_DIR)
    message(FATAL_ERROR "Cound not found Poco header files.")
endif(POCO_INCLUDE_DIR)

if(POCO_LIBRARY_DIR)
    message(STATUS "Poco library files found at ${POCO_LIBRARY_PATH}")
else(POCO_LIBRARY_DIR)
    #message(FATAL_ERROR "Cound not found Poco library files.")
endif(POCO_LIBRARY_DIR)

include_directories(${POCO_INCLUDE_DIR})
link_directories(/opt/local/lib)
