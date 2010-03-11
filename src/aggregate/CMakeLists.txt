cmake_minimum_required(VERSION 2.6)

#
# aggregate operators
#

# xcount
add_executable(xagg.count
    ${COMMON_SRCS}
    AggCount.h
    AggCount.cpp
    AggCountApp.h
    AggCountApp.cpp
    )
target_link_libraries(xagg.count
    ${COMMON_LIBS}
    )
 
# xsum
add_executable(xagg.sum
    ${COMMON_SRCS}
    AggSum.h
    AggSum.cpp
    AggSumApp.h
    AggSumApp.cpp
    )
target_link_libraries(xagg.sum
    ${COMMON_LIBS}
    )
     
# xagg.avg
add_executable(xagg.avg
    ${COMMON_SRCS}
    AggAverage.h
    AggAverage.cpp
    AggAverageApp.h
    AggAverageApp.cpp
    )
target_link_libraries(xagg.avg
    ${COMMON_LIBS}
    )
     
# xagg.median
add_executable(xagg.quantile
    ${COMMON_SRCS}
    AggQuantile.h
    AggQuantile.cpp
    AggQuantileApp.h
    AggQuantileApp.cpp
    )
target_link_libraries(xagg.quantile
    ${COMMON_LIBS}
    )

# xagg.max
add_executable(xagg.max
    ${COMMON_SRCS}
    AggMax.h
    AggMax.cpp
    AggMaxApp.h
    AggMaxApp.cpp
    )
target_link_libraries(xagg.max
    ${COMMON_LIBS}
    )
    
# xagg.min
add_executable(xagg.min
    ${COMMON_SRCS}
    AggMin.h
    AggMin.cpp
    AggMinApp.h
    AggMinApp.cpp
    )
target_link_libraries(xagg.min
    ${COMMON_LIBS}
    )
    
# xhead
add_executable(xagg.head
    ${COMMON_SRCS}
    Head.h
    Head.cpp
    HeadApp.h
    HeadApp.cpp
    )
target_link_libraries(xagg.head
    ${COMMON_LIBS}
    )
    
# xtail
add_executable(xagg.tail
    ${COMMON_SRCS}
    Tail.h
    Tail.cpp
    TailApp.h
    TailApp.cpp
    )
target_link_libraries(xagg.tail
    ${COMMON_LIBS}
    )
    
