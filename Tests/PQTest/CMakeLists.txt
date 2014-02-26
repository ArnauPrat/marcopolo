cmake_minimum_required (VERSION 2.8)
project (PQTest)


set (SOURCES ../../Source/MPPriorityQueue.c)

include_directories( ../../Include )

add_executable (PQTest PQTest.c ${SOURCES})

set_target_properties (PQTest PROPERTIES LINK_FLAGS -Wl,-lcunit)

add_test (PQTest ${EXECUTABLE_OUTPUT_PATH}/PQTest)
