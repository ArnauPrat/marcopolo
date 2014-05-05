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
    return ( a-b ) < 0.0 ? a : b;
}

static int max(float a, float b) {
    return ( a-b ) < 0.0 ? b : a;
}

int    mpTestAABBvsAABB(const mpAABB* a, const mpAABB* b) {
    if( (a->m_Center.m_X + a->m_ExtX) < (b->m_Center.m_X - b->m_ExtX) ||
            (b->m_Center.m_X + b->m_ExtX) < (a->m_Center.m_X - a->m_ExtX) ) return 0;
    if( (a->m_Center.m_Y + a->m_ExtY) < (b->m_Center.m_Y - b->m_ExtY) ||
            (b->m_Center.m_Y + b->m_ExtY) < (a->m_Center.m_Y - a->m_ExtY) ) return 0;
    return 1;
}

float mpPseudoCrossProduct( const mpVector* v1, const mpVector* v2 ) {
    return v1->m_X*v2->m_Y - v1->m_Y*v2->m_X;
}

float mpDotProduct( const mpVector* v1, const mpVector* v2 ) {
    return v1->m_X*v2->m_X + v1->m_Y*v2->m_Y;
}

int    mpTestSegvsSeg(const mpPoint* a1, const mpPoint* a2, const mpPoint* b1, const mpPoint* b2, mpPoint* intersection) {
    if(max(a1->m_X,a2->m_X) < min(b1->m_X,b2->m_X) && max(b1->m_X,b2->m_X) < min(a1->m_X,a2->m_X) ) return 0; // early check if the intersection is possible. X projection of both segments have to overlapp.
    mpVector r = { a2->m_X-a1->m_X, a2->m_Y - a1->m_Y};
//    printf("r: %f %f\n", r.m_X, r.m_Y);
    mpVector s = { b2->m_X-b1->m_X, b2->m_Y - b1->m_Y};
//    printf("s: %f %f\n", s.m_X, s.m_Y);
    mpVector pq = { b1->m_X-a1->m_X, b1->m_Y - a1->m_Y};
//    printf("pq:  %f %f\n", pq.m_X, pq.m_Y);
    float uNumerator = mpPseudoCrossProduct(&pq,&r);
    float denominator = mpPseudoCrossProduct(&r,&s);
    if( (uNumerator == 0) && (denominator == 0) ) {
        float tmp1, tmp2;
        tmp1 = mpDotProduct(&pq,&r);
        mpVector qp = { a1->m_X-b1->m_X, a1->m_Y - b1->m_Y};
        tmp2 = mpDotProduct(&qp,&s);
        float rdotr, sdots;
        rdotr = mpDotProduct(&r, &r);
        sdots = mpDotProduct(&s, &s);
        if( !(((tmp1 >= 0) && (tmp2 <= rdotr)) || ((tmp2 >= 0) && (tmp2 <= sdots))) ) {
            return 0;
        }
    }

    if( denominator == 0 ) return 0;

    float u = uNumerator / denominator;
    float t = mpPseudoCrossProduct(&pq,&s) / denominator;
//    printf("t %f\n", t);
    if( (t <= 1) && (t>= 0) && (u<=1) && (u>=0) ) {
        intersection->m_X = a1->m_X + t*r.m_X;
        intersection->m_Y = a1->m_Y + t*r.m_Y;
        return 1;
    }
    return 0;
}


int    mpTestPointvsPoly(const mpPoint* point, const mpPolygon* poly) {
    short i; 
    short count = 0;
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

