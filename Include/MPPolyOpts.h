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


#ifndef MPPOLYOPTS_H
#define MPPOLYOPTS_H

#include "MPTypes.h"

namespace mp
{

         /// @brief Given a set of polygons, this operation returns the union of the polygons.
         /// @param[in] vertices An array containing the vertices that form the polygons. These must be in clockwise order.
         /// @param[in] indices An array indices indicating the first vertex that form the polygon.
         /// @param[in] numPolygons The size of the array of indices.
    void PolygonUnion( const Point2D* vertices, const unsigned int numVertices,
                       const unsigned int* indices, const unsigned int numPolygons );


         /// @brief Computes the union of two polygons.
         /// @param[in] verticesA The vertices of the first polygon in clockwise order.
         /// @param[in] numVerticesA The number of vertices of the first polygon.
         /// @param[in] verticesB The vertices of the second polygon in clockwise order.
         /// @param[in] numVerticesB The number of vertices of the second polygon.
    void PolygonUnion( const Point2D* verticesA, const unsigned int numVerticesA
                       const Point2D* verticesB, const unsigned int numVerticesB) {
        
    }
}

#endif

