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

#include "../../Include/MPSortedSet.h"
#include <stdlib.h>
#include <CUnit/Basic.h>


static mpSortedSet* ss;

static int mpCompareInt( void* a, void* b) {
    return *(int*)a - *(int*)b <= 0;
}

//static int values[10] = {1,2,3,4,5,6,7,8,9,10};
static int* values = NULL;
static int size = 30000;

void mpAllocateSSTest() {
    ss = mpAllocateSS( mpCompareInt ); 
    CU_ASSERT( ss != NULL );
}

void mpInsertSSTest() {
    int i =0;
    for(;i < size; ++i) {
        mpInsertSS(ss, &values[i]); 
    }
}


void mpRemoveSSTest() {
    int i =0;
    for(;i < size; ++i) {
        mpRemoveSS(ss, &values[i]); 
    }
}

void mpFreeSSTest() {
    mpFreeSS( ss ); 
    CU_ASSERT( 1 );
}


int main( int argc, char** argv ) {

    values = (int*)malloc(sizeof(int)*size);
    int i = 0;
    for(;i<size;++i) values[i]= i;

    CU_pSuite pSuite = NULL;
    ss = NULL;

    /* initialize the CUnit test registry */ 
    if (CUE_SUCCESS != CU_initialize_registry()){
        free(values);
        return CU_get_error();
    }

    /* add a suite to the registry */ 
    pSuite = CU_add_suite("SSTest", NULL, NULL);
    if (NULL == pSuite) goto error;

    /* add the tests to the suite */ 
    if (NULL == CU_add_test(pSuite, "MPSortedSet.h: mpAllocateSS()", mpAllocateSSTest )) 
        goto error;


    if (NULL == CU_add_test(pSuite, "MPSortedSet.h: mpPushSS()", mpInsertSSTest ))
        goto error;

    if (NULL == CU_add_test(pSuite, "MPSortedSet.h: mpPopSS()", mpRemoveSSTest ))
        goto error;

    if (NULL == CU_add_test(pSuite, "MPSortedSet.h: mpFreeSS()", mpFreeSSTest ))
        goto error;

    /* Run all tests using the CUnit Basic interface */ 
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();

error:
    free(values);
    CU_cleanup_registry();
    return CU_get_error();
}


