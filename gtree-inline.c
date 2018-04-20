// ============ GTREE-INLINE.C ================

// ================ Functions declaration ====================

// ================ Functions implementation ====================

// Get the user data of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
void* GTreeData(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return that->_data;
}

// Get the parent of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GTree* GTreeParent(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return that->_parent;
}

// Set the user data of the GTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void GTreeSetData(GTree* that, void* data) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  that->_data = data;
}

// Get the set of subtrees of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGTree* GTreeSubtrees(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return &(that->_subtrees);
}

// Return true if the GTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool GTreeIsRoot(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (that->_parent == NULL ? true : false);
}

// Return true if the GTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool GTreeIsLeaf(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GSetNbElem(&(that->_subtrees)) == 0 ? true : false);
}

// ----------- GTreeIter

// ================ Functions declaration ====================

// ================ Functions implementation ====================

// Reset the iterator 'that' at its start position
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterReset(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
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
void _GTreeIterToEnd(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
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
bool _GTreeIterStep(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GTreeErr->_type = PBErrTypeInvalidArg;
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
bool _GTreeIterStepBack(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GTreeErr->_type = PBErrTypeInvalidArg;
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

// Apply a function to all elements' data of the GTree of the iterator
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterApply(GTreeIter* that, 
  void(*fun)(void* data, void* param), void* param) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (fun == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'fun' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Reset the iterator;
  GTreeIterReset(that);
  // If the associated tree is not empty
  if (GSetNbElem(&(that->_seq)) > 0) {
    // For each node of the tree
    do {
      // Apply the user function
      fun(GTreeIterGetData(that), param);
    } while (GTreeIterStep(that));
  }
}

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsFirst(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (that->_curPos == ((GSet*)&(that->_seq))->_head);
}

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsLast(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
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
void _GTreeIterDepthSetGTree(GTreeIterDepth* that, GTree* tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GTreeIter*)that)->_tree = tree;
  // Update the sequence
  GTreeIterDepthUpdate(that);
  // Reset the iterator
  GTreeIterReset(that);
}
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterBreadthSetGTree(GTreeIterBreadth* that, GTree* tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GTreeIter*)that)->_tree = tree;
  // Update the sequence
  GTreeIterBreadthUpdate(that);
  // Reset the iterator
  GTreeIterReset(that);
}
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterValueSetGTree(GTreeIterValue* that, GTree* tree) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Set the tree
  ((GTreeIter*)that)->_tree = tree;
  // Update the sequence
  GTreeIterValueUpdate(that);
  // Reset the iterator
  GTreeIterReset(that);
}

// Return the user data of the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* _GTreeIterGetData(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (that->_curPos == NULL) {
    GTreeErr->_type = PBErrTypeInvalidArg;
    sprintf(GSetErr->_msg, "'that->_curPos' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return ((GTree*)(that->_curPos->_data))->_data;
}

// Return the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGetGTree(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return (GTree*)(that->_curPos->_data);
}

// Return the tree associated to the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGTree(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
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
GSetGTree* _GTreeIterSeq(GTreeIter* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  return &(that->_seq);
}

