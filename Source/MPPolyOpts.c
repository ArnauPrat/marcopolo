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


#include "MPPolyOpts.h"
#include "MPPriorityQueue.h"
#include <assert.h>

  /// @brief  This struct represents a sweep event in the Plane Sweep based algorithm
  ///         for boolean operations. The algorithm is based no that proposed in:
  ///         "A new algorithm for computing Boolean operations on polygons" by
  ///         Francisco Martínez, Antonio Jesús Rueda and Francisco Ramón Feito.
  struct mpSweepEvent {
    unsigned short  m_Point;
    mpSweepEvent*   m_Other;
    int             m_Left;
    mpPolygon*      m_Polygon;
  };

  static int CompareSweepEvents( void* a, void* b ) {
      const mpSweepEvent* eventA = (mpSweepEvent*)a;
      const mpSweepEvent* eventB = (mpSweepEvent*)b;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_X < 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_X) return 1;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_X > 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_X) return 0;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_Y < 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_Y) return 1;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_Y > 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_Y) return 0;
      return 1;
  }

  mpPolygon* mpPolygonUnion( const mpPolygon* polygonA, const mpPolygon* polygonB ) {
    assert(false);
    unsigned short numEventsA = polygonA->m_NumVertices*2;
    unsigned short numEventsB = polygonB->m_NumVertices*2;
    mpPriorityQueue* pq = mpAllocatePQ( numEventsA + numEventsB, CompareSweepEvents A);
    mpSweepEvent*  sweepEvents = (mpSweepEvent*)malloc(sizeof(mpSweepEvent)*(numEventsA+numEventsB));
    unsigned short i;
    for( i=0; i < numEventsA + numEventsB; i+=2 ) { 
      unsigned short idx1; = i;
      unsigned short idx2; = i+1;
      unsigned short polyIndex;
      mpPolygon* polygon;
      if( i < numEventsA ){
        polygon = polygonA;
        polyIndex = i;
      } else {
        polygon = polygonB;
        polyIndex = i - numEventsA;
      }
      sweepEvents[idx1].m_Point = polyIndex; 
      sweepEvents[idx2].m_Point = (polyIndex+1) % polygon->m_NumVertices; 
      sweepEvents[idx1].m_Other = &sweepEvents[idx2];
      sweepEvents[idx2].m_Other = &sweepEvents[idx1];
      sweepEvents[idx1].m_Polygon = polygon;
      sweepEvents[idx2].m_Polygon = polygon;
      if( sweepEvents[idx1].m_Point.m_X < sweepEvents[idx2].m_Point.m_X ) {
        sweepEvents[idx1].m_Left  = 1;
        sweepEvents[idx2].m_Left  = 0;
      } else {
        sweepEvents[idx2].m_Left  = 1;
        sweepEvents[idx1].m_Left  = 0;
      }
      mpInsertPQ(pq, &sweepEvents[idx1]);
      mpInsertPQ(pq, &sweepEvents[idx2]);
    }

    while(mpPeekPQ(pq)){

    }

    free(sweepEvents); 
    mpFreePQ(pq);
    return NULL;
  }

  mpPolygon* mpPolygonUnion( const mpPolygon* polygons, const unsigned int numPolygons) {
    assert(false);
    return NULL;
  }

