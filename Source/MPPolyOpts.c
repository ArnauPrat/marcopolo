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
#include "MPPrimitiveTests.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/// @brief  This struct represents a chain of points. It is used to construct
//          the final polygon containing the final obstacle mesh.
typedef struct _mpPointChain {
    mpPoint*        m_Points;       ///< @brief An array of points forming the chain.
    unsigned short  m_Begin;        ///< @brief The index of the first point in the chain.
    unsigned short  m_Size;         ///< @brief The number of elements in the chain.
    unsigned short  m_Capacity;     ///< @brief The capacity of the chain.

} mpPointChain;

/// @brief Allocates a point chain. Initializes the chain with two points
/// @param[in] point1 The first point of the chain.
//  @param[in] point2 The second point of the chain.
static mpPointChain*  mpAllocatePointChain(const mpPoint* point1, const mpPoint* point2) {
    mpPointChain* chain = (mpPointChain*)malloc(sizeof(mpPointChain));
    assert(chain);
    chain->m_Capacity = 4;
    chain->m_Points = (mpPoint*)malloc(sizeof(mpPoint)*chain->m_Capacity);
    chain->m_Size = 2;
    chain->m_Begin = 0; 
    chain->m_Points[0] = *point1; 
    chain->m_Points[1] = *point2; 
    return chain;
}

/// @brief Frees the resources used by a point chain.
/// @param[in] chain The chain to free.
static void mpFreePointChain(mpPointChain* chain) {
    free(chain->m_Points);
    free(chain);
}

/// @brief Inserts a point into the begining of the chain.
/// @param[in] The chain to add the point to.
/// @param[in] The point to add to the chain.
static void mpInsertBegin(mpPointChain* chain, const mpPoint* point) {
       if( chain->m_Capacity == chain->m_Size ) {
           mpPoint* newPoints = (mpPoint*)malloc(sizeof(mpPoint)*chain->m_Capacity*2);
           memcpy(newPoints+1,chain->m_Points,sizeof(mpPoint)*chain->m_Size);
           free(chain->m_Points);
           chain->m_Points = newPoints;
           chain->m_Capacity *= 2;
           chain->m_Points[0] = *point;
           chain->m_Size++;
       } else {
           short i;
           for( i = chain->m_Size-1; i>=0; --i ) {
                chain->m_Points[i+1] = chain->m_Points[i]; 
           }
           chain->m_Points[0] = *point;
           chain->m_Size++;
       }
}

/// @brief Inserts a point into the end of the chain.
/// @param[in] The chain to add the point to.
/// @param[in] The point to add to the chain.
static void mpInsertEnd(mpPointChain* chain, const mpPoint* point) {
       if( chain->m_Capacity == chain->m_Size ) {
           mpPoint* newPoints = (mpPoint*)malloc(sizeof(mpPoint)*chain->m_Capacity*2);
           memcpy(newPoints,chain->m_Points,sizeof(mpPoint)*chain->m_Size);
           free(chain->m_Points);
           chain->m_Points = newPoints;
           chain->m_Capacity *= 2;
           chain->m_Points[chain->m_Size] = *point;
           chain->m_Size++;
       } else {
           chain->m_Points[chain->m_Size] = *point;
           chain->m_Size++;
       }
}

/// @brief Adds a segment into the chain if one of the extremes of the chain is
///        the same as one of the segment.
/// @param[in] chain The chain to add the segment to.
/// @param[in] point1 The first point of the segment.
/// @param[in] point2 The second point of the segment.
/// @return 1 If the segment was successfully added. 0 otherwise.
static int mpAddSegment(mpPointChain* chain, const mpPoint* point1, const mpPoint* point2 ) {
    if(mpComparePoints(&chain->m_Points[chain->m_Begin],point1)) {
        mpInsertBegin(chain,point2);
        return 1;
    }
    if(mpComparePoints(&chain->m_Points[chain->m_Begin],point2)) {
        mpInsertBegin(chain,point1);
        return 1;
    }
    if(mpComparePoints(&chain->m_Points[chain->m_Begin+chain->m_Size-1],point1)) {
        mpInsertEnd(chain,point2);
        return 1;
    }
    if(mpComparePoints(&chain->m_Points[chain->m_Begin+chain->m_Size-1],point2)) {
        mpInsertEnd(chain,point1);
        return 1;
    }
    return 0;
}



typedef struct _mpSweepEvent mpSweepEvent;

/// @brief  This struct represents a sweep event in the Plane Sweep based algorithm
///         for boolean operations. The algorithm is based no that proposed in:
///         "A new algorithm for computing Boolean operations on polygons" by
///         Francisco Martínez, Antonio Jesús Rueda and Francisco Ramón Feito.
typedef struct _mpSweepEvent {
    mpPoint         m_Point;        ///< @brief The point this sweepevent represents.
    mpSweepEvent*   m_Other;        ///< @brief A pointer to the other sweepevent with the point at the other extreme of the segment.
    int             m_Left;         ///< @brief 1 if this event represents the left point of a segment.
    mpPolygon*      m_Polygon;      ///< @brief A pointer to the polygon this point belongs to.
} mpSweepEvent;

/// @brief Compares two sweep events by their Y coordinate.
/// @param[in] a The first sweepevent.
/// @param[in] b The second sweepevent.
/// @return 1 if a goes before b. 0 Otherwise. 
static int CompareSweepEventsByY( void* a, void* b ) {
    const mpSweepEvent* eventA = (mpSweepEvent*)a;
    const mpSweepEvent* eventB = (mpSweepEvent*)b;
    if(eventA->m_Point.m_Y < eventB->m_Point.m_Y) return 1;
    if(eventA->m_Point.m_Y > eventB->m_Point.m_Y) return 0;
    return 0;
}

/// @brief Compares two sweep events, first by the X coordinate of its point
///        and then by its Y coordinate.
/// @param[in] a The first sweepevent.
/// @param[in] b The second sweepevent.
/// @return 1 if a goes before b. 0 Otherwise. 
static int CompareSweepEvents( void* a, void* b ) {
    const mpSweepEvent* eventA = (mpSweepEvent*)a;
    const mpSweepEvent* eventB = (mpSweepEvent*)b;
    if(eventA->m_Point.m_X < eventB->m_Point.m_X) return 1;
    if(eventA->m_Point.m_X > eventB->m_Point.m_X) return 0;
    return CompareSweepEventsByY(a,b);
}

/// @brief Extracts the sweepevents from a polygon and adds them into a
///        priority queue.
/// @param[in] pq The priority queue to add the events to.
/// @param[in] poly The polygon to extract the events from.
static void ExtractAndPushEvents( mpPriorityQueue* pq, const mpPolygon* poly ) {
    int i;
    for( i = 0; i < poly->m_NumVertices; ++i ) {
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
        eventL->m_Point = poly->m_Vertices[lIndex];
        eventL->m_Other = eventR;
        eventL->m_Left = 1;
        eventL->m_Polygon = (mpPolygon*)poly;
        eventR->m_Point = poly->m_Vertices[rIndex];
        eventR->m_Other = eventL;
        eventR->m_Left = 0;
        eventR->m_Polygon = (mpPolygon*)poly;
        mpPushPQ(pq,eventL);
        mpPushPQ(pq,eventR);
//        printf("%p %p %p %p \n", (void*)eventL, (void*)eventR, (void*)eventL->m_Other, (void*)eventR->m_Other);
    }
}

/// @brief Tests if two segments represented by four sweep events intersect. If so, new
///        new segments are created and inserted into a priority queue. 
/// @param[in] pq The priority queue to add the events to.
/// @param[in] a1 The sweepevent representing the left point of the first segment. 
/// @param[in] a2 The sweepevent representing the right point of the first segment. 
/// @param[in] b1 The sweepevent representing the right point of the second segment. 
/// @param[in] b2 The sweepevent representing the right point of the second segment. 
static void mpTestIntersection(mpPriorityQueue* pq, mpSweepEvent* a1, mpSweepEvent* a2, mpSweepEvent* b1, mpSweepEvent* b2) {

    mpPoint intersectionPoint;
    if(!mpTestSegvsSeg(&a1->m_Point,&a2->m_Point,&b1->m_Point,&b2->m_Point,&intersectionPoint)) return;

    // Creating segment a1 <-> intersectionPoint
    mpSweepEvent* interEvent = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
    interEvent->m_Point = intersectionPoint;
    interEvent->m_Other = a1;
    interEvent->m_Left = 0;
    interEvent->m_Polygon = a1->m_Polygon;
    a1->m_Other = interEvent;
    mpPushPQ(pq,interEvent);

    // Creating segment intersectionPoint <-> a2 
    interEvent = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
    interEvent->m_Point = intersectionPoint;
    interEvent->m_Other = a2;
    interEvent->m_Left = 1;
    interEvent->m_Polygon = a2->m_Polygon;
    a2->m_Other = interEvent;
    mpPushPQ(pq,interEvent);

    // Creating segment b1 <-> intersectionPoint
    interEvent = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
    interEvent->m_Point = intersectionPoint;
    interEvent->m_Other = b1;
    interEvent->m_Left = 0;
    interEvent->m_Polygon = a1->m_Polygon;
    b1->m_Other = interEvent;
    mpPushPQ(pq,interEvent);

    // Creating segment intersectionPoint <-> b2 
    interEvent = (mpSweepEvent*)malloc(sizeof(mpSweepEvent));
    interEvent->m_Point = intersectionPoint;
    interEvent->m_Other = b2;
    interEvent->m_Left = 1;
    interEvent->m_Polygon = b2->m_Polygon;
    b2->m_Other = interEvent;
    mpPushPQ(pq,interEvent);
}

int mpPolygonUnion( const mpPolygon* polygonA, const mpPolygon* polygonB, mpPolygon** polygonOut ) {
    unsigned short numEventsA = polygonA->m_NumVertices*2;
    unsigned short numEventsB = polygonB->m_NumVertices*2;
    mpPriorityQueue* pq = mpAllocatePQ( (numEventsA + numEventsB) * 2, CompareSweepEvents );
    // We first extract the events from the polygons.
    ExtractAndPushEvents(pq,polygonA);
    ExtractAndPushEvents(pq,polygonB);

    unsigned short chainsCapacity=8;
    mpPointChain** chains = (mpPointChain**)malloc(sizeof(mpPointChain*)*chainsCapacity);
    unsigned short chainsSize=0;

    mpSortedSet* ss = mpAllocateSS(CompareSweepEventsByY);
    mpSweepEvent* currentEvent = NULL;
    while( (currentEvent = mpPopPQ(pq)) != NULL ) {
        if(currentEvent->m_Left) {
            mpInsertSS(ss,currentEvent);
            mpSweepEvent* previous = mpPreviousSS(ss,currentEvent);
            mpSweepEvent* next = mpNextSS(ss,currentEvent);
            // Check for intersection with previous

            printf("Insert %p\n",currentEvent);

            if(previous){
                printf("Previous %p\n",previous);
                mpTestIntersection(pq,previous, previous->m_Other, currentEvent, currentEvent->m_Other);
            }

            // Check for intersection with next 
            if(next){ 
                printf("Next %p\n",next);
                mpTestIntersection(pq, next, next->m_Other, currentEvent, currentEvent->m_Other);
            }
            printf("End actions %p\n",currentEvent);


        } else { // The event is a right endpoint.
            mpSweepEvent* leftEndpoint = currentEvent->m_Other;
            mpSweepEvent* previous = mpPreviousSS(ss,leftEndpoint);
            mpSweepEvent* next = mpNextSS(ss,leftEndpoint);
            // Check for intersection between previous and next 
            if( previous && next ) mpTestIntersection(pq,previous, previous->m_Other, next, next->m_Other);

            printf("Remove %p\n",leftEndpoint);
            mpRemoveSS(ss,leftEndpoint);
            // Test if leftEndpoint <-> currentEvent segment is inside the other polygon.
            mpPolygon* poly = leftEndpoint->m_Polygon == polygonA ? (mpPolygon*)polygonB : (mpPolygon*)polygonA;
            if(!mpTestPointvsPoly(&leftEndpoint->m_Point, poly) || !mpTestPointvsPoly(&currentEvent->m_Point, poly)) {
                int i;
                int found = 0;
                for( i = 0; i < chainsSize; ++i) {
                    if(mpAddSegment(chains[i],&leftEndpoint->m_Point, &currentEvent->m_Point)) {
                        found=1;
                        break;
                    } 
                }
                if(!found) {
                    if(chainsCapacity==chainsSize) {
                        mpPointChain** newChains = (mpPointChain**)malloc(sizeof(mpPointChain)*chainsCapacity*2);
                        memcpy(newChains,chains,sizeof(mpPointChain*)*chainsCapacity);
                        free(chains);
                        chains = newChains;
                        chainsCapacity*=2;
                    }
                    chains[chainsSize]=mpAllocatePointChain(&leftEndpoint->m_Point, &currentEvent->m_Point);
                }
            }
            // Free leftEndpoint and currentEvent
            free(leftEndpoint);
            free(currentEvent);
        }
    }
    // Create result.
    int i;
    for(i=0; i < chainsSize; ++i) {
        printf("Chain %d\n",i);
        int j;
        for(j=0; j<chains[i]->m_Size; ++j) {
            printf("%f %f\n",chains[i]->m_Points[j].m_X, chains[i]->m_Points[j].m_Y);
        }
    }

    // Free memory
    for(i=0; i < chainsSize; ++i) {
        mpFreePointChain(chains[i]);
    }
    free(chains);
    mpFreeSS(ss);
    mpFreePQ(pq);
    return 0;
}


/*mpPolygon* mpPolygonUnion( const mpPolygon* polygons, const unsigned int numPolygons) {
    assert(false);
    return NULL;
}*/

