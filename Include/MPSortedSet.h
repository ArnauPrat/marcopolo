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

#ifndef MPSORTEDSET_H
#define MPSORTEDSET_H

  /// @brief Represents a node in the binary tree used to implement the sorted set.
  struct mpSortedSetNode{
    mpSortedSetNode*   m_Left;     ///< @brief A pointer to the left children of the binary tree.
    mpSortedSetNode*   m_Right;    ///< @brief A pointer to the left node of the binary tree.
    mpSortedSetNode*   m_Parent;   ///< @brief A pointer to the parent.
    void*              m_Data;     ///< @brief A pointer to the data.

  };

  /// @brief Represents a sorted set of elements.
  struct mpSortedSet {
    mpSortedSetNode*   m_Root;                          ///< @brief A pointer to the root node.
    int                 (*m_Comparator)( void*, void*); ///< @brief The comparator function.
  };


  /// @brief    Allocates a sorted set.
  /// @return   A pointer to the created sorted set.
  mpSortedSet* mpAllocateSS( int (*comparator)( void*, void* ) );

  /// @brief            Frees a sorted set.
  /// @param[in,out] ss The sorted set to free.
  void mpFreeSS( mpSortedSet* ss );

  /// @brief               Inserts an element into the sorted set.
  /// @param[in,out] ss    The sorted set to insert into.
  /// @param[in] element   The element to insert.
  void mpInsertSS( mpSortedSet* ss, void* element);


  /// @brief               Removes an element from a sorted set.
  /// @param[in,out] ss    The sorted set to remove the element from.
  /// @param[in] element   The element to remove.
  void mpRemoveSS( mpSortedSet* ss, void* element );

  /// @brief               Returns the minimum element.
  /// @param[in] ss        The sorted set where the node belongs to.
  /// @return              The minimum element stored into the set.
  void* mpMinSS( mpSortedSet* ss );

  /// @brief               Returns the maximum element.
  /// @param[in] ss        The sorted set where the node belongs to.
  /// @return              The maximum element stored into the set.
  void* mpMaxSS( mpSortedSet* ss );

  /// @brief               Returns the next element in the set with respect to the specified element.
  /// @param[in] ss        The sorted set where the node belongs to.
  /// @param[in] element   The element in the set.
  /// @return              The next element stored into the set.
  void* mpNextSS( mpSortedSet* ss, void* element );

  /// @brief               Returns the previous element in the set with respect to the specified element.
  /// @param[in] ss        The sorted set where the node belongs to.
  /// @param[in] element   The element in the set.
  /// @return              The previous element stored into the set.
  void* mpPreviousSS( mpSortedSet* ss, void* element );

#endif
