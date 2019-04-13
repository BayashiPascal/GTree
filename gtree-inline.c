// ============ GTREE-INLINE.C ================

// ================ Functions declaration ====================

// ================ Functions implementation ====================

// Get the user data of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
void* _GenTreeData(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return that->_data;
}

// Get the parent of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
GenTree* _GenTreeParent(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return that->_parent;
}

// Set the user data of the GenTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void _GenTreeSetData(GenTree* const that, void* const data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_data = data;
}

// Get the set of subtrees of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGenTree* _GenTreeSubtrees(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GSetGenTree*)&(that->_subtrees);
}

// Return true if the GenTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GenTreeIsRoot(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (that->_parent == NULL ? true : false);
}

// Return true if the GenTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GenTreeIsLeaf(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GSetNbElem(&(that->_subtrees)) == 0 ? true : false);
}

// Return true if the GenTree 'that' is the last of its brotherhood
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GenTreeIsLastBrother(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_parent == NULL)
    return true;
  else {
    return (GSetTail(&(that->_parent->_subtrees)) == that);
  }
}

// ----------- GenTreeIter

// ================ Functions declaration ====================

// ================ Functions implementation ====================

// Reset the iterator 'that' at its start position
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterReset(GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_curPos = ((GSet*)&(that->_seq))->_head;
}

// Reset the iterator 'that' to its end position
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterToEnd(GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_curPos = ((GSet*)&(that->_seq))->_tail;
}

// Step the iterator 'that' at its next position
// Return true if it could move to the next position
// Return false if it's already at the last position
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterStep(GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GenTreeErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'that->_curPos' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curPos->_next != NULL) {
    that->_curPos = that->_curPos->_next;
    return true;
  }
  return false;
}

// Step back the iterator 'that' at its next position
// Return true if it could move to the previous position
// Return false if it's already at the first position
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterStepBack(GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GenTreeErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'that->_curPos' is null");
    PBErrCatch(GSetErr);
  }
#endif
  if (that->_curPos->_prev != NULL) {
    that->_curPos = that->_curPos->_prev;
    return true;
  }
  return false;
}

// Apply a function to all elements' data of the GenTree of the iterator
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterApply(GenTreeIter* const that, 
  void(*fun)(void* const data, void* const param), void* const param) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (fun == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'fun' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset the iterator;
  GenTreeIterReset(that);
  // If the associated tree is not empty
  if (GSetNbElem(&(that->_seq)) > 0) {
    // For each node of the tree
    do {
      // Apply the user function
      fun(GenTreeIterGetData(that), param);
    } while (GenTreeIterStep(that));
  }
}

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GenTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterIsFirst(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (that->_curPos == ((GSet*)&(that->_seq))->_head);
}

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GenTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterIsLast(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (that->_curPos == ((GSet*)&(that->_seq))->_tail);
}

// Change the attached tree of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterDepthSetGenTree(GenTreeIterDepth* const that, 
  GenTree* const tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GenTreeIter*)that)->_tree = tree;
  // Update the sequence
  GenTreeIterDepthUpdate(that);
  // Reset the iterator
  GenTreeIterReset(that);
}
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterBreadthSetGenTree(GenTreeIterBreadth* const that, 
  GenTree* tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GenTreeIter*)that)->_tree = tree;
  // Update the sequence
  GenTreeIterBreadthUpdate(that);
  // Reset the iterator
  GenTreeIterReset(that);
}
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterValueSetGenTree(GenTreeIterValue* const that, 
  GenTree* const tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GenTreeIter*)that)->_tree = tree;
  // Update the sequence
  GenTreeIterValueUpdate(that);
  // Reset the iterator
  GenTreeIterReset(that);
}

// Return the user data of the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* _GenTreeIterGetData(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GenTreeErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'that->_curPos' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return ((GenTree*)(that->_curPos->_data))->_data;
}

// Return the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GenTree* _GenTreeIterGetGenTree(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GenTreeErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'that->_curPos' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GenTree*)(that->_curPos->_data);
}

// Return the tree associated to the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GenTree* _GenTreeIterGenTree(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return that->_tree;
}

// Return the sequaence of the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GSetGenTree* _GenTreeIterSeq(const GenTreeIter* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GSetGenTree*)&(that->_seq);
}

