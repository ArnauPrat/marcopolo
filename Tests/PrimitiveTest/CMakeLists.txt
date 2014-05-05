cmake_minimum_required (VERSION 2.8)
project (PQTest)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -pg")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -NDEBUG")


find_package(CUnit)
include_directories(${CUNIT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CUNIT_LIBRARIES} marcopolo)

if(CUNIT_FOUND)

include_directories( ../../Include )
add_executable (PrimitiveTest PrimitiveTest.c)
set_target_properties (PrimitiveTest PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries(PrimitiveTest ${LIBS})
add_test (PrimitiveTest ${EXECUTABLE_OUTPUT_PATH}/PrimitiveTest)

endif(CUNIT_FOUND)
