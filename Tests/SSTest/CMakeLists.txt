cmake_minimum_required (VERSION 2.8)
project (SSTest)


set (SOURCES ../../Source/MPSortedSet.c)

include_directories( ../../Include )

add_executable (SSTest SSTest.c ${SOURCES})

set_target_properties (SSTest PROPERTIES LINK_FLAGS -Wl,-lcunit)

add_test (SSTest ${EXECUTABLE_OUTPUT_PATH}/SSTest)
