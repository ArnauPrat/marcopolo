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

#ifndef MPPRIMITIVETESTS_H
#define MPPRIMITIVETESTS_H

#include "MPTypes.h"

namespace mp
{

            /// @brief Tests if two AABBs specified by min/max points intersect.
            /// @param[in] minA The lower left corner of the first AABB.
            /// @param[in] maxA The upper right corner of the first AABB.
            /// @param[in] minB The lower left corner of the second AABB.
            /// @param[in] maxB The upper right corner of the second AABB.
    bool    TestAABBvsAABB( const Point2D& minA, const Point2D& maxA, const Point2D minB, const Point2D maxB );

}

#endif
