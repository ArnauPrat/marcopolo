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

#include "MPSortedSet.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


mpSortedSet* mpAllocateSS( int (*comparator)( void*, void* ) ) {
    assert( comparator!=NULL );
    mpSortedSet* ss = (mpSortedSet*)malloc(sizeof(mpSortedSet));
    ss->m_Comparator = comparator;
    return ss;
}

static void _mpFreeSS( mpSortedSetNode* node ) {
  if( node != NULL ) {
    _mpFreeSS( node->m_Left );
    _mpFreeSS( node->m_Right );
    free(node);
  }
}

void mpFreeSS( mpSortedSet* ss ) {
    assert( ss!=NULL );
    _mpFreeSS(ss->m_Root);
    free(ss);
}

static void _mpInsertSS( mpSortedSet* ss, mpSortedSetNode* root, void* element ) {
    assert( ss!=NULL );
    assert( root!=NULL );
    assert( element!=NULL );
    if( ss->m_Comparator( root->m_Data, element ) < 0 ) {
        if( root->m_Right != NULL ) { 
            _mpInsertSS( ss, root->m_Right, element );
        }
        else {
            mpSortedSetNode* node = (mpSortedSetNode*)malloc(sizeof(mpSortedSetNode));
            node->m_Data = element;
            node->m_Left = NULL;
            node->m_Right = NULL;
            node->m_Parent = root;
            root->m_Right = node;
        }
    } else if( root->m_Left != NULL ) { 
        _mpInsertSS( ss, root->m_Left, element );
    } else {
        mpSortedSetNode* node = (mpSortedSetNode*)malloc(sizeof(mpSortedSetNode));
        node->m_Data = element;
        node->m_Left = NULL;
        node->m_Right = NULL;
        node->m_Parent = root;
        root->m_Left = node;
    }
}

void mpInsertSS( mpSortedSet* ss, void* element) {
    assert( ss!=NULL );
    assert( element!=NULL );
    if( ss->m_Root == NULL ) {
      mpSortedSetNode* node = (mpSortedSetNode*)malloc(sizeof(mpSortedSetNode));
      node->m_Data = element;
      node->m_Left = NULL;
      node->m_Right = NULL;
      node->m_Parent = NULL;
      ss->m_Root = node; 
    } else {
      _mpInsertSS( ss, ss->m_Root, element );
    }
}


static mpSortedSetNode* _mpMinSS( mpSortedSetNode* root ) {
  assert(root!=NULL);
  if( root->m_Left == NULL ) { return root; }
  else { return _mpMinSS( root->m_Left ); }
}

void* mpMinSS( mpSortedSet* ss ) {
  assert(ss!=NULL);
  return _mpMinSS( ss->m_Root )->m_Data;
}

static mpSortedSetNode* _mpMaxSS( mpSortedSetNode* root ) {
  assert(root!=NULL);
  if( root->m_Right == NULL ) { return root; }
  else { return _mpMaxSS( root->m_Right ); }
}

void* mpMaxSS( mpSortedSet* ss ) {
  assert(ss!=NULL);
  return _mpMaxSS( ss->m_Root )->m_Data;
}

static mpSortedSetNode* mpFindSS( mpSortedSet* ss, mpSortedSetNode* root, void* element ) {
  assert(ss!=NULL);
  assert(root!=NULL);
  assert(element!=NULL);
  int comp = ss->m_Comparator( root->m_Data, element );
  if( comp == 0 )  {
    return root; 
  } else if( comp > 0  && root->m_Left != NULL ) { return mpFindSS( ss, root->m_Left, element ); }
    else if( comp < 0 && root->m_Right != NULL ) { return mpFindSS( ss, root->m_Right, element ); }
  return NULL;
}

void* mpNextSS( mpSortedSet* ss, void* element ) {
  mpSortedSetNode* node = mpFindSS( ss, ss->m_Root, element );
  assert(node);
  if( node->m_Right != NULL ) { 
      mpSortedSetNode* res = _mpMinSS( node->m_Right ); 
      return res->m_Data != element ? res->m_Data : NULL;
  }  else if( node->m_Parent!=NULL && node->m_Parent->m_Right!=node ) { 
      mpSortedSetNode* res = node->m_Parent;
      return res->m_Data != element ? res->m_Data : NULL;
  }
  return NULL;
}

void* mpPreviousSS( mpSortedSet* ss, void* element ) {
  mpSortedSetNode* node = mpFindSS( ss,ss->m_Root,element );
  assert( node );
  if( node->m_Left != NULL ) { 
      mpSortedSetNode* res = _mpMaxSS( node->m_Left );
      return res->m_Data != element ? res->m_Data : NULL;
  } else if( node->m_Parent!=NULL && node->m_Parent->m_Left!=node) { 
      mpSortedSetNode* res = node->m_Parent;
      return res->m_Data != element ? res->m_Data : NULL;
  }
  return NULL;
}

static mpSortedSetNode* _mpRemoveSS( mpSortedSet* ss, mpSortedSetNode* root, void* element ) {
    if( ss->m_Comparator(root->m_Data, element ) == 0 ) {
      assert( root->m_Data == element );
      if( (root->m_Left != NULL) && (root->m_Right != NULL) ) {
          mpSortedSetNode* min = _mpMinSS( root->m_Right );
          root->m_Data = min->m_Data;
          root->m_Right = _mpRemoveSS( ss, root->m_Right, min->m_Data );
      } else if( root->m_Right != NULL ) {
          mpSortedSetNode* ret = root->m_Right;
          ret->m_Parent = root->m_Parent;
          free(root);
          return ret;    
      } else if( root->m_Left != NULL ){
          mpSortedSetNode* ret = root->m_Left;
          ret->m_Parent = root->m_Parent;
          free(root);
          return ret;    
      } else {
          free(root);
          return NULL;
      }
    } else if( root->m_Left != NULL && ss->m_Comparator( root->m_Data, element ) > 0 ) { 
            root->m_Left = _mpRemoveSS( ss, root->m_Left, element ); }
      else if( root->m_Right != NULL &&  ss->m_Comparator( root->m_Data, element ) < 0 ) { 
            root->m_Right = _mpRemoveSS( ss, root->m_Right, element ); } 
    return root;
}

void mpRemoveSS( mpSortedSet* ss, void* element ) {
    assert( ss!=NULL );
    assert( element!=NULL );
    if( ss->m_Root == NULL ) return;
    ss->m_Root = _mpRemoveSS( ss, ss->m_Root, element);
}
