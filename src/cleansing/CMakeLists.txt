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
    
