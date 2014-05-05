/**
  Copyright notice:

  (C) 2014 Arnau Prat-Perez

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
 **/


#include "Marcopolo.h"
#include "MPPrimitiveTests.h"

#include <stdlib.h>
#include <CUnit/Basic.h>

mpPoint verticesA[4] = {{0.0, 0.0},{0.0, 1.0},{1.0, 1.0},{1.0, 0.0}};
mpPoint point = {0.0,0.0};
mpPolygon* polygon = NULL;

void mpPointvsPolyTest() {
    CU_ASSERT( mpTestPointvsPoly(&point, polygon) );
}


int main( int argc, char** argv ) {

    polygon = mpAllocatePolygon(verticesA,4);   

    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */ 
    if (CUE_SUCCESS != CU_initialize_registry()){
        mpFreePolygon(polygon);
        return CU_get_error();
    }

    /* add a suite to the registry */ 
    pSuite = CU_add_suite("SSTest", NULL, NULL);
    if (NULL == pSuite) goto error;

    /* add the tests to the suite */ 
    if (NULL == CU_add_test(pSuite, "Testing mpTestPointvsPoly()", mpPointvsPolyTest )) 
        goto error;

    /* Run all tests using the CUnit Basic interface */ 
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
error:
    CU_cleanup_registry();
    mpFreePolygon(polygon);
    return CU_get_error();

}


