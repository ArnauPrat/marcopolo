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

#include <MPPriorityQueue.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <limits.h>


static mpPriorityQueue* pq;

static int mpCompareInt( void* a, void* b) {
    return *(int*)a - *(int*)b;
}

static int* values = NULL;
static const int size = 100000;
static int capacity = 100000;

void mpAllocatePQTest() {
    pq = mpAllocatePQ( capacity, mpCompareInt ); 
    CU_ASSERT( pq != NULL );
}

void mpPushPQTest() {
    int i = 0;
    int min = INT_MAX;
    for( i = 0; i < size; ++i ) {
        mpPushPQ( pq, &values[i] ); 
        /*printf("Push %d\n",values[i]);*/
        if( values[i] < min ) min = values[i];
        CU_ASSERT( pq->m_Size == i+1 );
        CU_ASSERT( *(int*)mpPeekPQ(pq) == min );
    }
}

void mpPeekPQTest() {
    int value = *(int*)mpPeekPQ( pq ); 
    CU_ASSERT( pq->m_Size == size );
    CU_ASSERT( value == 0 );
}

void mpPopPQTest() {
    int i = 0;
    for( i = 0; i < size; ++i ) {
        int value = *(int*)mpPopPQ( pq ); 
        CU_ASSERT(pq->m_Size == (size - (i+1)));
        /*printf("Pop %d\n",value);*/
        CU_ASSERT(value == i);
    }
}

void mpFreePQTest() {
    mpFreePQ( pq ); 
    CU_ASSERT( 1 );
}

/* Arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
void shuffle(int *array, int n) {
    srand(1);
    if (n > 1)  {
        int i;
        for (i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}


int main( int argc, char** argv ) {

    values = (int*)malloc(sizeof(int)*size);
    int i = 0;
    for(;i<size;++i) values[i]= i;
    shuffle(values, size);

    CU_pSuite pSuite = NULL;
    pq = NULL;

    /* initialize the CUnit test registry */ 
    if (CUE_SUCCESS != CU_initialize_registry()){
        free(values);
        return CU_get_error();
    }

    /* add a suite to the registry */ 
    pSuite = CU_add_suite("PQTest", NULL, NULL);
    if (NULL == pSuite) goto error;

    /* add the tests to the suite */ 
    if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpAllocatePQ()", mpAllocatePQTest )) 
        goto error;

    if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpPushPQ()", mpPushPQTest ))
        goto error;

    if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpPopPQ()", mpPopPQTest ))
        goto error;

    if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpFreePQ()", mpFreePQTest ))
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


