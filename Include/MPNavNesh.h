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

#ifndef MPNAVMESH_H
#define MPNAVMESH_H

#include "MPTypes.h"

namespace mp
{
    class NavMesh {
    public:
        /// @param[in] min The lower left corner delimiting the bounding box of the NavMesh.
        /// @param[in] max The upper right corner delimiting the bounding box of the NavMesh.
        /// @param[in] margin The minimum distance between two points in order to be considered different.
        NavMesh( const Point2D& min, const Point2D& max, const float margin );
        ~NavMesh();

        /// @brief Adds a chunk of static obstacles into the nav mesh. 
        /// @param[in] vertices An array containing the vertices that form the obstacles. These must be in clockwise order.
        /// @param[in] indices An array indices indicating the first vertex that form the obstacle.
        /// @param[in] numObstacles The size of the array of indices.
        /// @return True if the addition was successful. False otherwise.
        bool AddStaticObstacles( const Point2D* vertices, const unsigned int numVertices,
                                 const unsigned int* indices, const unsigned int numObstacles );

    private:
        const Point2D   m_Min;          ///< @brief The lower left corner of the bounding box delimiting the NavMesh.
        const Point2D   m_Max;          ///< @brief The upper right corner of the bounding box delimiting the NavMesh.
        const float     m_Margin;       ///< @brief The margin to add to obstacles.
        Polygon*        m_Polygons;     ///< @brief The array of polygons that form the NavMesh.      
        Point2D*        m_Vertices;     ///< @brief The array of vertices that form the NavMesh.
    };
}

#endif
