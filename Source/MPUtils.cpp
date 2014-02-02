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

  #include "MPUtils.h"
  #include <stdlio.h>
  #include <assert.h>


  mpAABB  ExtractBoundingBox( const mpPolygon* polygon ) {
    assert(polygon != NULL);
    assert(polygon->m_NumVertices > 0);
    assert(polygon->m_Vertices != NULL);
    mpPoint min, 
            max;
    min.m_X = polygon->m_Vertices[0].m_X;
    min.m_Y = polygon->m_Vertices[0].m_Y;
    max.m_X = polygon->m_Vertices[0].m_X;
    max.m_Y = polygon->m_Vertices[0].m_Y;
    for ( unsigned int i = 1; i < polygon->m_NumVertices; ++i ) {
      if( polygon->m_Vertices[i].m_X < min.m_X ) min.m_X = polygon->m_Vertices[i].m_X;
      if( polygon->m_Vertices[i].m_Y < min.m_Y ) min.m_Y = polygon->m_Vertices[i].m_Y;
      if( polygon->m_Vertices[i].m_X > max.m_X ) max.m_X = polygon->m_Vertices[i].m_X;
      if( polygon->m_Vertices[i].m_Y > max.m_Y ) max.m_Y = polygon->m_Vertices[i].m_Y;
    }
    mpAABB aabb;
    aabb.m_ExtX = abs((max.m_X - min.m_X) / 2.0f);
    aabb.m_ExtY = abs((max.m_Y - min.m_Y) / 2.0f);
    aabb.m_Center.m_X = min.m_X + aabb.m_ExtX ;
    aabb.m_Center.m_Y = min.m_Y + aabb.m_ExtY;
    return aabb;
  }
