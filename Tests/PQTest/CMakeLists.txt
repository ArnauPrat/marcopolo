cmake_minimum_required (VERSION 2.8)
project (PQTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -pg")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -NDEBUG")


find_package(CUnit)
include_directories(${CUNIT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CUNIT_LIBRARIES})

if(CUNIT_FOUND)

set (SOURCES ../../Source/MPPriorityQueue.c)
include_directories( ../../Include )
add_executable (PQTest PQTest.c ${SOURCES})
set_target_properties (PQTest PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(PQTest ${LIBS})
add_test (PQTest ${EXECUTABLE_OUTPUT_PATH}/PQTest)

endif(CUNIT_FOUND)
