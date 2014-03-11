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

#ifndef MPPRIORITYQUEUE_H
#define MPPRIORITYQUEUE_H

///< @brief This struct represents a priority queue.
typedef struct _mpPriorityQueue {
  void**            m_Data;                         ///< @brief The array containing the data.  
  unsigned short    m_Capacity;                     ///< @brief The capacity of the priority queue.
  unsigned short    m_Size;                         ///< @brief The size of the priority queue. 
  int               (*m_Comparator)( void*, void*); ///< @brief The comparator function.
} mpPriorityQueue;

/// @brief Allocates a priority queue.
/// @param[in] capacity The initial capacity of the priority queue.
/// @param[in] comparator The comparator function used to set the priority between elements.
mpPriorityQueue* mpAllocatePQ( unsigned short capacity, int (*comparator)( void*, void* ) ); 

/// @brief            Frees a priority queue.
/// @param[in,out] pq The priority queue frees.
void mpFreePQ( mpPriorityQueue* pq );

/// @brief        Pops and returns the element at the top of the priority queue.
/// @param[in,out] pq The priority queue to pop from.
/// @return       The element at the top of the queue.
void* mpPopPQ( mpPriorityQueue* pq );

/// @brief        Returns the element at the top of the queue.
/// @param[in] pq The priority queue to peek from.
/// @return       The element at the top of the queue.
void* mpPeekPQ( mpPriorityQueue* pq );

/// @brief        Inserts an element into the priorit queue.
/// @param[in,out] pq The priority queue to insert to.
/// @param[in]    element The element to insert.
void mpPushPQ( mpPriorityQueue* pq, void* element );

/// @brief Clears a priority queue.
/// @param[in,out] pq The priority queue to clear.
void mpClearPQ( mpPriorityQueue* pq );

#endif

