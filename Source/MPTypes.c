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


#include "MPTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


mpPolygon* mpAllocatePolygon() {
    mpPolygon* polyon = (mpPolygon*)malloc(sizeof(mpPolygon));
    memset(polygon,0,sizeof(mpPolygon));
    return polygon;
}

void mpFreePolygon( mpPolygon* polygon ) {
    assert( polygon != NULL );
    if( polygon->m_Vertices != NULL ) free( polygon->m_Vertices );
    return free(polygon);
}

int mpComparePoints(const mpPoint* point1, const mpPoint* point2) {
    assert(0);
    return 0;
}
