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

#ifndef MPTYPES_H
#define MPTYPES_H

#ifndef MP_MAX_POLY_SIZE 
#define MP_MAX_POLY_SIZE 6
#endif

#define MP_INVALID_ID 0xffff

namespace mp
{
    #typedef MPId unsigned short ///@brief The internal identifier type.

    /// @brief Represents a two-dimensional vector.
    struct Vector2D {
        float m_X;  ///< @brief The x coordinate of the vector.
        float m_Y;  ///< @brief The y coordinate of the vector.
    };

    struct Polygon {
        MPId m_Vertices[MP_MAX_POLY_SIZE];    ///@brief The ids of the vertices that form the polygon in clockwise order.
        MPId m_Adjacencies[MP_MAX_POLY_SIZE]; ///@brief The polygon id adjacent to each edge of the polygon.
    };

    #typedef Vector2D Point2D
}

#endif 