cmake_minimum_required(VERSION 2.6)

#
# column operators
#

# xbackfill
add_executable(xcls.backfill
    ${COMMON_SRCS}
    Backfill.h
    Backfill.cpp
    BackfillApp.h
    BackfillApp.cpp
    )
target_link_libraries(xcls.backfill
    ${COMMON_LIBS}
    )
    
# xbackfill
add_executable(xcls.default
    ${COMMON_SRCS}
    Default.h
    Default.cpp
    DefaultApp.h
    DefaultApp.cpp
    )
target_link_libraries(xcls.default
    ${COMMON_LIBS}
    )
    
add_custom_target(xcls.htmltable ALL
    COMMAND cp HtmlTable.py ${EXECUTABLE_OUTPUT_PATH}
    COMMAND cp xcls.htmltable.sh ${EXECUTABLE_OUTPUT_PATH}/xcls.htmltable
    )
    
    
    