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
#include <assert.h>

  /// @brief  This struct represents a sweep event in the Plane Sweep based algorithm
  ///         for boolean operations. The algorithm is based no that proposed in:
  ///         "A new algorithm for computing Boolean operations on polygons" by
  ///         Francisco Martínez, Antonio Jesús Rueda and Francisco Ramón Feito.
  struct mpSweepEvent {
    unsigned short  m_Point;
    mpSweepEvent*   m_Other;
    bool            m_Left;
    mpPolygon*      m_Polygon;
  };


  mpPolygon* mpPolygonUnion( const mpPolygon* polygonA, const mpPolygon* polygonB ) {
    assert(false);
    return NULL;
  }

  mpPolygon* mpPolygonUnion( const mpPolygon* polygons, const unsigned int numPolygons) {
    assert(false);
    return NULL;
  }

