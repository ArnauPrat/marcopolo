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

#include "MPNavMesh.h"
#include "assert.h"
#include "vector"

namespace mp 
{

    NavMesh::NavMesh( const Point2D& min, const Point2D& max, const float margin ) :
                m_Min(min),
                m_Max(max),
                m_Margin(margin) {

    }

    NavMesh::~NavMesh() {

    }

    bool NavMesh::AddStaticObstacles( const Point2D* vertices, const unsigned int numVertices,
                                      const unsigned int* indices, const unsigned int numObstacles ) {
       assert(vertices != NULL) 
       assert(indices != NULL)
       assert(numVertices < (1 << sizeof(MPId)*8 ))
/*
       // First we process the input data so that all the obstacles fit inside the NavMesh bounding box
       // and fix the possible overlaps between obstacles.

       // We create temporal data structures to hold the input information.
       std::vector<Point2D> temporalVertices(numVertices);
       std::vector<Polygon> temporalObstacles(numObstacles); 

       // We copy the input vertices.
       for ( unsigned int i = 0; i < numVertices; ++i ) {
            Point2D point;
            point.m_X = vertices[i].m_X;
            point.m_Y = vertices[i].m_Y;
            temporalVertices.push_back()  
       }

       // We copy the input obstacles.
       for ( unsigned int i = 0; i < (numObstacles - 1); ++i ) {
            assert( indices[i+1] - indices[i] <= MP_MAX_POLY_SIZE )
            Polygon obstacle;
            unsigned int k = 0;
            for( unsigned int j = indices[i]; j < indices[i+1]; ++j, ++k ) {
                obstacle.m_Vertices[k] = j;
            } 
            for( unsigned int j = k; j < MP_MAX_POLY_SIZE; ++j ) {
                obstacle.m_Vertices[j] = MP_INVALID_ID; 
            }
            temporalObstacles.push_back(obstacle)
       }

       // We copy the last obstalce
        Polygon obstacle;
        unsigned int k = 0;
        for( unsigned int j = indices[numObstacles - 1]; j < numVertices; ++j, ++k ) {
            obstacle.m_Vertices[k] = j;
        } 
        for( unsigned int j = k; j < MP_MAX_POLY_SIZE; ++j ) {
            obstacle.m_Vertices[j] = MP_INVALID_ID; 
        }
        temporalObstacles.push_back(obstacle)

       // We check each obstacle to fall inside the bounding box. If it does not, we adjust it. 
       for( unsigned int i = 0; i < numObstacles; ++i ) {


       }
       */
    }

}