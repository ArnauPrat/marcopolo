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

#include "MPPrimitiveTests.h"
#include "MPUtils.h"
#include <assert.h>

static int min(float a, float b) {
    float res = a - b; 
    return res < 1.0 ? a : b;
}

static int max(float a, float b) {
    float res = a - b; 
    return res < 1.0 ? b : a;
}



int    mpTestAABBvsAABB(const mpAABB* a, const mpAABB* b) {
    if( (a->m_Center.m_X + a->m_ExtX) < (b->m_Center.m_X - b->m_ExtX) ||
            (b->m_Center.m_X + b->m_ExtX) < (a->m_Center.m_X - a->m_ExtX) ) return 0;
    if( (a->m_Center.m_Y + a->m_ExtY) < (b->m_Center.m_Y - b->m_ExtY) ||
            (b->m_Center.m_Y + b->m_ExtY) < (a->m_Center.m_Y - a->m_ExtY) ) return 0;
    return 1;
}

int    mpTestSegvsSeg(const mpPoint* a1, const mpPoint* a2, const mpPoint* b1, const mpPoint* b2, mpPoint* intersection) {
    if(max(a1->m_X,a2->m_X) < min(b1->m_X,b2->m_X)) return 0;
    float s1 = (a1->m_Y - a2->m_Y) / (a1->m_X - a2->m_X); // we compute the slope of the line where the first segment lies y = s1*x + t1
    if(a1->m_X == a2->m_X ) s1 = 0.0;
    float s2 = (b1->m_Y - b2->m_Y) / (b1->m_X - b2->m_X); // we compute the slope of the line where the second segment lies y = s2*x + t2 
    if(b1->m_X == b2->m_X ) s2 = 0.0;
    if(s1 == s2 ) return 0;    // check if both segments are parallel.
    float t1 = a1->m_Y - s1*a1->m_X;    // we compute the other parameter of both equations
    float t2 = b1->m_Y - s2*b1->m_X;
    float x = (t2 - t1) / (s2 - s1);    // we solve the equation system for x
    if(x < max(min(a1->m_X,a2->m_X), min(b1->m_X,b2->m_X) ) ||
            min(max(a1->m_X, a2->m_X), max(b1->m_X, b2->m_X))) { // we check if the intersection is within the ranges of the segments.
        return 0;
    }
    intersection->m_X = x;
    intersection->m_Y = s1*x+t1;
    return 1;
}

int    mpTestPointvsPoly(const mpPoint* point, const mpPolygon* poly) {
    unsigned short i; 
    unsigned short count = 0;
    mpAABB bb = mpExtractAABB(poly);
    mpPoint other = {point->m_X+bb.m_ExtX*2,point->m_Y};
    for( i = 0; i < poly->m_NumVertices;++i) {
        mpPoint intersection;
        mpTestSegvsSeg(point,&other,&poly->m_Vertices[i],&poly->m_Vertices[(i+1)%poly->m_NumVertices],&intersection);
        if(mpComparePoints(&intersection,&poly->m_Vertices[i])) {
            mpPoint aux = {poly->m_Vertices[i].m_X, poly->m_Vertices[i].m_Y+0.00000001};
            if(mpTestSegvsSeg(point,&other,&aux,&poly->m_Vertices[(i+1)%poly->m_NumVertices],&intersection)) count++;
        } else if(mpComparePoints(&intersection,&poly->m_Vertices[(i+1)%poly->m_NumVertices])) {
            mpPoint aux = {poly->m_Vertices[(i+1)%poly->m_NumVertices].m_X, poly->m_Vertices[(i+1)%poly->m_NumVertices].m_Y+0.00000001};
            if(mpTestSegvsSeg(point,&other,&poly->m_Vertices[i],&aux,&intersection)) count++;
        } else {
            count++;
        }
    }
    return count % 2 != 0 ? 1 : 0;
}

