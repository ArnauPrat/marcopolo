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

#include "MPPriorityQueue.h"
#include <stdlib.h>
#include <assert.h>


mpPriorityQueue* mpAllocatePriorityQueue( unsigned short capacity, int (*comparator)( void*, void* ) ) {
    assert( comparator != NULL ); 
    assert( capacity > 0 );
    mpPriorityQueue* pq = (mpPriorityQueue*)malloc(sizeof(mpPriorityQueue));
    pq->m_Capacity = capacity; 
    pq->m_Size = 0;
    pq->m_Data = (void**)malloc(sizeof(void*)*pq->m_Capacity);
    pq->m_Comparator = comparator;
    return pq;
}

void mpFreePriorityQueue( mpPriorityQueue* pq ) {
    assert( pq != NULL );
    if( pq->m_Data != NULL ) free(pq->m_Data);
    free(pq);
}

void* mpPopPQ( mpPriorityQueue* pq ) {
    assert( pq != NULL )
    if( pq->m_Size == 0 ) return NULL;
    void* ret = pq->m_Data[0];
    pq->m_Size -= 1;                        // reduce the size of the queue.    
    pq->m_Data[0] = m_Data[m_Size];         // put the last element into the first position.
    if( pq->m_Size > 0 ) {                  // if the size is greater than 0, then recompute the position of the first element.
        unsigned short inPlace = 0;
        unsigned short pos = 0;
        while( !inPlace ) {
            inPlace = 1;
            if( 2*pos+1 <pq->m_Size && !pq->m_Comparator( pq->m_Data[pos], pq->m_Data[2*pos+1]) ) {
                newPos = 2*pos + 1;
                void* tmp = pq->m_Data[pos];
                pq->m_Data[pos] = pq->m_Data[newPos];
                pq->m_Data[newPos] = tmp;
                pos = newPos;
                inPlace = 0;
            } else if( 2*pos+2 < pq->m_Size && !pq->m_Comparator( pq->m_Data[pos], pq->m_Data[2*pos+2]) ) {
                newPos = 2*pos + 2;
                void* tmp = pq->m_Data[pos];
                pq->m_Data[pos] = pq->m_Data[newPos];
                pq->m_Data[newPos] = tmp;
                pos = newPos;
                inPlace = 0;
            }
        }
    }
    return ret; 
}

void* mpPeekPQ( mpPriorityQueue* pq ) {
    if( pq->m_Size > 0 ) return pq->m_Data[0];
    return NULL;
}

void mpInsertPQ( mpPriorityQueue* pq, void* element ) {
    assert( pq != NULL );
    assert( pq->m_Size < pq->m_Capacity );
    pq->m_Data[pq->m_Size] = element;
    pq->m_Size += 1;
    unsigned short pos = pq->m_Size-1;
    int inPlace = 0;
    while( !inPlace && pos > 0) {
        inPlace = 1;
        unsigned short parent = (pos-1)/2;
        if( (pos-1)/2 >= 0 && pq->m_Comparator( pq->m_Data[pos], pq->m_Data[parent]) ) {
                void* tmp = pq->m_Data[pos];
                pq->m_Data[pos] = pq->m_Data[parent];
                pq->m_Data[parent] = tmp;
                pos = parent;
                inPlace = 0;
        }
    }
}

void mpClearPQ( mpPriorityQueue* pq ) {
    assert( pq != NULL )
    pq->m_Size = 0;
}
