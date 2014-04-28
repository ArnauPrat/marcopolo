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

/// @brief Computes the union of two polygons.
/// @param[in] polygonA The first polygon of the union.
/// @param[in] polygonB The second polygon of the union.
/// @param[out] polygonOut A polygon containing the union.
/// @return 1 if the two polygons were intersecting. 
int mpPolygonUnion( const mpPolygon* polygonA, const mpPolygon* polygonB, mpPolygon* polygonOut );

/// @brief Computes the union of a set of polygons.
/// @param[in] polygons The array of polygons to compute the union.
/// @param[in] numPolygons The number of polygons in the array.
/// @return A new polygon containing the union.
//mpPolygon* mpPolygonUnion( const mpPolygon* polygons, const unsigned int numPolygons);

#endif

