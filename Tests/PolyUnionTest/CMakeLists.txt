cmake_minimum_required (VERSION 2.8)
project (PQTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -pg")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -NDEBUG")


find_package(CUnit)
include_directories(${CUNIT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CUNIT_LIBRARIES} marcopolo)

if(CUNIT_FOUND)

include_directories( ../../Include )
add_executable (PolyUnionTest PolyUnionTest.c)
set_target_properties (PolyUnionTest PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(PolyUnionTest ${LIBS})
add_test (PolyUnionTest ${EXECUTABLE_OUTPUT_PATH}/PolyUnionTest)

endif(CUNIT_FOUND)
