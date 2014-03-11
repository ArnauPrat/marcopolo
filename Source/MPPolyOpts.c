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
#include "MPSortedSet.h"
#include <assert.h>

  /// @brief  This struct represents a sweep event in the Plane Sweep based algorithm
  ///         for boolean operations. The algorithm is based no that proposed in:
  ///         "A new algorithm for computing Boolean operations on polygons" by
  ///         Francisco Martínez, Antonio Jesús Rueda and Francisco Ramón Feito.
  typedef struct _mpSweepEvent {
    unsigned short  m_Point;
    mpSweepEvent*   m_Other;
    int             m_Left;
    mpPolygon*      m_Polygon;
  } mpSweepEvent;

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

  static int CompareSweepEventsByY( void* a, void* b ) {
      const mpSweepEvent* eventA = (mpSweepEvent*)a;
      const mpSweepEvent* eventB = (mpSweepEvent*)b;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_Y < 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_Y) return 1;
      if(eventA->m_Polygon->m_Vertices[eventA->m_Point].m_Y > 
         eventB->m_Polygon->m_Vertices[eventB->m_Point].m_Y) return 0;
      return 1;
  }

    static void ExtractAndPushEvents( mpPriorityQueue* pq, const mpPolygon* poly ) {
        for( int i = 0; i < poly->m_NumVertices; ++i ) {
            mpSweepEvent* eventL = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
            mpSweepEvent* eventR = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
            int lIndex = i;
            int rIndex = (i+1)%poly->m_NumVertices;
            if( poly->m_Vertices[lIndex].m_X > poly->m_Vertices[rIndex].m_X ||  
                    (poly->m_Vertices[lIndex].m_X == poly->m_Vertices[rIndex].m_X &&  
                     poly->m_Vertices[lIndex].m_Y > poly->m_Vertices[lIndex].m_Y) ) {
                lIndex = rIndex;
                rIndex = i;
            }
            eventL->m_Points = poly->m_Vertices[lIndex];
            eventL->m_Other = eventR;
            eventL->m_Left = 1;
            eventL->m_Polygon = poly;
            eventR->m_Points = poly->m_Vertices[rIndex];
            eventR->m_Other = eventL;
            eventL->m_Left = 0;
            eventL->m_Polygon = poly;
            mpPushPQ(pq,eventL);
            mpPushPQ(pq,eventR);
        }
    }

  mpPolygon* mpPolygonUnion( const mpPolygon* polygonA, const mpPolygon* polygonB ) {
    assert(false);
    unsigned short numEventsA = polygonA->m_NumVertices*2;
    unsigned short numEventsB = polygonB->m_NumVertices*2;
    mpPriorityQueue* pq = mpAllocatePQ( (numEventsA + numEventsB) * 2, CompareSweepEvents );
    // We first extract the events from the polygons.
    ExtractAndPushEvents(pq,polygonA);
    ExtractAndPushEvents(pq,polygonB);

    MPSortedSet* ss = mpAllocateSS(CompareSweepEventsByY);
    mpSweepEvent* currentEvent = NULL;
    while( (currentEvent = mpPopPQ(pq)) != NULL ) {
        if(currentEvent->m_Left) {
            mpInsertSS(ss,currentEvent);
            mpSweepEvent* previous = mpPreviousSS(ss,currentEvent);
            mpSweepEvent* next = mpNextSS(ss,currentEvent);
            // Check for intersection with previous
            // Check for intersection with next 
        } else { // The event is a right endpoint.
            mpSweepEvent* leftEndpoint = currentEvent->m_Other;
            mpSweepEvent* previous = mpPreviousSS(ss,leftEndpoint);
            mpSweepEvent* next = mpNextSS(ss,leftEndpoint);
            // Check for intersection between previous and next 
            mpRemoveSS(leftEndpoint);
        }
    }
    mpFreeSS(ss);
    mpFreePQ(pq);
    return NULL;
  }

  mpPolygon* mpPolygonUnion( const mpPolygon* polygons, const unsigned int numPolygons) {
    assert(false);
    return NULL;
  }

