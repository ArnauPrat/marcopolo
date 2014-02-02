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

#ifndef MPUTILS_H
#define MPUTILS_H

#include "MPTypes.h"

namespace mp
{
            /// @brief Extracs the bounding box of a polygon.
            /// @param[in] vertices The vertices that form the polygon.
            /// @param[in] numVertices The number of vertices of the polygon.
            /// @param[out] min The lower left corner of the boundfing box containing the whole polygon.
            /// @param[out] max The lower left corner of the boundfing box containing the whole polygon.
    void    ExtractBoundingBox( const Point2D* vertices, const unsigned int numVertices, Point2D& min, Point2D& max );

            /// @brief Extracs the bounding box of a polygon.
            /// @param[in] vertices The vertices that form the polygon.
            /// @param[in] numVertices The number of vertices of the polygon.
            /// @param[out] min The lower left corner of the boundfing box containing the whole polygon.
            /// @param[out] max The lower left corner of the boundfing box containing the whole polygon.
            /// @param[in] margin The size of the margin to add to bounding boxes. 
    void    ExtractBoundingBox( const Point2D* vertices, const unsigned int numVertices, Point2D& min, Point2D& max, const float margin );


    


}

#endif

