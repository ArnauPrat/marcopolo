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

bool    TestAABBvsAABB( const mpAABB& a, const mpAABB& b ) {
        if( (a.m_Center.m_X + a.m_ExtX) < (b.m_Center.m_X - b.m_ExtX) ||
            (b.m_Center.m_X + b.m_ExtX) < (a.m_Center.m_X - a.m_ExtX) ) return false;
        if( (a.m_Center.m_Y + a.m_ExtY) < (b.m_Center.m_Y - b.m_ExtY) ||
            (b.m_Center.m_Y + b.m_ExtY) < (a.m_Center.m_Y - a.m_ExtY) ) return false;
        return true;
}
