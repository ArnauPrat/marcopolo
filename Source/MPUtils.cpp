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

 namespace mp 
 {

    void    ExtractBoundingBox( const Point2D* vertices, const unsigned int numVertices, Point2D& min, Point2D& max ) {
        assert(numVertices > 0)
        min.m_X = vertices[0].m_X;
        min.m_Y = vertices[0].m_Y;
        max.m_X = vertices[0].m_X;
        max.m_Y = vertices[0].m_Y;
        for ( unsigned int i = 1; i < numVertices; ++i ) {
            if( vertices[i].m_X < min.m_X ) min.m_X = vertices[i].m_X;
            if( vertices[i].m_Y < min.m_Y ) min.m_Y = vertices[i].m_Y;
            if( vertices[i].m_X > max.m_X ) max.m_X = vertices[i].m_X;
            if( vertices[i].m_Y > max.m_Y ) max.m_Y = vertices[i].m_Y;
        }
        return;
    }

 } 
