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
#include "vector"


namespace mp 
{
    void PolygonUnion( const Point2D* vertices, const unsigned int numVertices,
                       const unsigned int* indices, const unsigned int numPolygons ) {

        /// Extract vertices and edges from the polygons.
        std::vector< Point2D > points(numVertices);
        for( unsigned int i = 0; i < numVertices; ++i ) {
            points.push_back( vertices[i] );
        }

        std::vector< Edge > edges;
        for ( unsigned int i = 0; i < (numPolygons - 1); ++i ) {
            for( unsigned int j = indices[i]; j < indices[i+1]; ++j ) {
                Edge edge;
                edge.m_A = j;
                edge.m_B = j+1;
                edges.push_back(edge);
            } 
        }

        for( unsigned int j = indices[numPolygons - 1]; j < numVertices; ++j ) {
                Edge edge;
                edge.m_A = j;
                edge.m_B = j+1;
                edges.push_back(edge);
        } 

        for( unsigned int i = 0; i < )
    }
}  
