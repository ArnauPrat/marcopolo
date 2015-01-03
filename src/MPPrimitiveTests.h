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


/*  @brief Tests if two AABBs specified by min/max points intersect.
    @param[in] minA The lower left corner of the first AABB.
    @param[in] maxA The upper right corner of the first AABB.
    @param[in] minB The lower left corner of the second AABB.
    @param[in] maxB The upper right corner of the second AABB.
    @return 1 if the two bounding boxes intersect. 0 otherwise.*/
int mpTestAABBvsAABB( const mpAABB* a, const mpAABB* b );

/*   @brief Tests if two segments intersect.
    @param[in] a1 The first point of the first segment.
    @param[in] a2 The second point of the first segment.
    @param[in] b1 The first point of the second segment.
    @param[in] b2 The second point of the second segment.
    @param[out] intersection The point at which the two segments intersect.
    @return 1 if the segments intersect. 0 Otherwise.*/
int mpTestSegvsSeg(const mpPoint* a1, const mpPoint* a2, const mpPoint* b1, const mpPoint* b2, mpPoint* intersection); 

/*  @brief Tests if a point is contained inside a polygon.
    @param[in] point The point to test.
    @param[in] poly The polygon to test.
    @return 1 if the point is inside the polygon. 0 otherwise.*/
int mpTestPointvsPoly(const mpPoint* point, const mpPolygon* poly);


float mpPseudoCrossProduct( const mpVector* v1, const mpVector* v2 );

float mpDotProduct( const mpVector* v1, const mpVector* v2 );

#endif
