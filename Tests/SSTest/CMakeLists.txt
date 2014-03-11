cmake_minimum_required (VERSION 2.8)
project (SSTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -pg")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -NDEBUG")



find_package(CUnit)
include_directories(${CUNIT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CUNIT_LIBRARIES})

if(CUNIT_FOUND)

set (SOURCES ../../Source/MPSortedSet.c)
include_directories( ../../Include )
add_executable (SSTest SSTest.c ${SOURCES})
set_target_properties (SSTest PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(SSTest ${LIBS})
add_test (SSTest ${EXECUTABLE_OUTPUT_PATH}/SSTest)

endif(CUNIT_FOUND)
