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


#include "Marcopolo.h"
#include <stdlib.h>
#include <CUnit/Basic.h>



int main( int argc, char** argv ) {
    mpPoint verticesA[4] = {{0.0, 0.0},{1.0, 0.0},{1.0, 1.0},{0.0, 1.0}};
    mpPoint verticesB[4] = {{2.0, 0.0},{3.0, 0.0},{3.0, 1.0},{2.0, 1.0}};
    mpPoint verticesC[4] = {{0.5, 0.0},{1.5, 0.0},{1.5, 1.0},{0.5, 1.0}};

    mpPolygon* polygonA = mpAllocatePolygon(verticesA,4);   
    mpPolygon* polygonB = mpAllocatePolygon(verticesB,4);   
    mpPolygon* polygonC = mpAllocatePolygon(verticesC,4);   
    mpPolygon* polygonOut;

/*    mpPolygonUnion(polygonA,polygonB,&polygonOut);*/
    mpPolygonUnion(polygonA,polygonC,&polygonOut);

    mpFreePolygon(polygonA);
    mpFreePolygon(polygonB);
    mpFreePolygon(polygonC);
    return 0;
}


