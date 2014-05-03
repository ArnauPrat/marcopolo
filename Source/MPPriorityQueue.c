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
#include <string.h>
#include <assert.h>


mpPriorityQueue* mpAllocatePQ( unsigned short capacity, int (*comparator)( void*, void* ) ) {
    assert( comparator != NULL ); 
    assert( capacity > 0 );
    mpPriorityQueue* pq = (mpPriorityQueue*)malloc(sizeof(mpPriorityQueue));
    assert( pq != NULL );
    pq->m_Capacity = capacity; 
    pq->m_Size = 0;
    pq->m_Data = (void**)malloc(sizeof(void*)*pq->m_Capacity);
    assert( pq->m_Data != NULL );
    pq->m_Comparator = comparator;
    return pq;
}

void mpFreePQ( mpPriorityQueue* pq ) {
    assert( pq != NULL );
    if( pq->m_Data != NULL ) free(pq->m_Data);
    free(pq);
}

void* mpPopPQ( mpPriorityQueue* pq ) {
    assert( pq != NULL );
    if( pq->m_Size == 0 ) return NULL;
    void* ret = pq->m_Data[0];
    pq->m_Size -= 1;                         // reduce the size of the queue.    
    pq->m_Data[0] = pq->m_Data[pq->m_Size];  // put the last element into the first position.
    if( pq->m_Size > 0 ) {                   // if the size is greater than 0, then recompute the position of the first element.
        short inPlace = 0;
        short pos = 0;
        while( !inPlace ) {
            inPlace = 1;
            int newPos = 2*pos+1;
            if( newPos < pq->m_Size ) {
                int rightChild = newPos+1;
                if( rightChild < pq->m_Size && pq->m_Comparator( pq->m_Data[rightChild], pq->m_Data[newPos]) < 0) {
                    newPos=rightChild;
                }
                if( pq->m_Comparator( pq->m_Data[pos], pq->m_Data[newPos]) > 0 ) {
                    void* tmp = pq->m_Data[pos];
                    pq->m_Data[pos] = pq->m_Data[newPos];
                    pq->m_Data[newPos] = tmp;
                    pos = newPos;
                    inPlace = 0;
                }
            }
        }
    }
    return ret; 
}

void* mpPeekPQ( mpPriorityQueue* pq ) {
    if( pq->m_Size > 0 ) return pq->m_Data[0];
    return NULL;
}

void mpPushPQ( mpPriorityQueue* pq, void* element ) {
    assert( pq != NULL );
    if( pq->m_Size == pq->m_Capacity ) {
        int newCapacity = pq->m_Capacity*2;
        void** temp = (void**)malloc(sizeof(void*)*newCapacity);
        memcpy(temp, pq->m_Data, sizeof(void*)*pq->m_Capacity);
        free(pq->m_Data);
        pq->m_Data = temp;
        pq->m_Capacity = newCapacity;
    }
    unsigned short pos = pq->m_Size;
    pq->m_Data[pos] = element;
    pq->m_Size += 1;
    int inPlace = 0;
    while( !inPlace && pos > 0) {
        inPlace = 1;
        unsigned short parent = (pos-1)/2;
        if( (pos-1)/2 >= 0 && pq->m_Comparator( pq->m_Data[pos], pq->m_Data[parent]) < 0)  {
                void* tmp = pq->m_Data[pos];
                pq->m_Data[pos] = pq->m_Data[parent];
                pq->m_Data[parent] = tmp;
                pos = parent;
                inPlace = 0;
        }
    }
}

void mpClearPQ( mpPriorityQueue* pq ) {
    assert( pq != NULL );
    pq->m_Size = 0;
}
