// ============ GTREE.C ================

// ================= Include =================

#include "gtree.h"
#if BUILDMODE == 0
#include "gtree-inline.c"
#endif

// ================ Functions declaration ====================

// Free the memory used by 'subtrees' recursively 
void GTreeFreeRec(GSetGTree* subtrees);

// ================ Functions implementation ====================

// Create a new GTree
GTree* GTreeCreate(void) {
  // Declare the new tree
  GTree *that = PBErrMalloc(GTreeErr, sizeof(GTree));
  // Set properties
  that->_parent = NULL;
  that->_subtrees = GSetGTreeCreateStatic();
  that->_data = NULL;
  // Return the tree
  return that;  
}

// Create a new static GTree
GTree GTreeCreateStatic(void) {
  // Declare the new tree
  GTree that;
  // Set properties
  that._parent = NULL;
  that._subtrees = GSetGTreeCreateStatic();
  that._data = NULL;
  // Return the tree
  return that;  
}

// Create a new GTree with user data 'data'
GTree* GTreeCreateData(void* data) {
  // Declare the new tree
  GTree *that = PBErrMalloc(GTreeErr, sizeof(GTree));
  // Set properties
  that->_parent = NULL;
  that->_subtrees = GSetGTreeCreateStatic();
  that->_data = data;
  // Return the tree
  return that;  
}

// Free the memory used by the GTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void GTreeFree(GTree** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // If it's not a root node
  if (!GTreeIsRoot(*that))
    // Cut the tree
    GTreeCut(*that);
  // Free recursively the memory
  GTreeFreeRec(GTreeSubtrees(*that));
  free(*that);
  *that = NULL;
}

// Free the memory used by 'subtrees' recursively 
void GTreeFreeRec(GSetGTree* subtrees) {
  while (GSetNbElem(subtrees) > 0) {
    GTree* tree = GSetPop(subtrees);
    GTreeFreeRec(GTreeSubtrees(tree));
    free(tree);
  }
}

// Free the memory used by the static GTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void GTreeFreeStatic(GTree* that) {
  // Check argument
  if (that == NULL)
    // Nothing to do
    return;
  // If it's not a root node
  if (!GTreeIsRoot(that))
    // Cut the tree
    GTreeCut(that);
  // Free memory
  GTreeFreeRec(GTreeSubtrees(that));
}

// Disconnect the GTree 'that' from its parent
// If it has no parent, do nothing
void GTreeCut(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If there is no parent
  if (GTreeParent(that) == NULL)
    // Nothing to do
    return;
  // Remove the tree from the parent's subtrees
  GSetRemoveAll(GTreeSubtrees(GTreeParent(that)), that);
  // Cut the link to the parent
  that->_parent = NULL;
}

// Return the number of subtrees of the GTree 'that' and their subtrees 
// recursively
int GTreeGetSize(GTree* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare a variable to memorize the result and initialize it with 
  // the number of subtrees
  int nb = GSetNbElem(GTreeSubtrees(that));
  // If there are subtrees
  if (nb > 0) {
    // Recursion on the subtrees
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GTreeSubtrees(that));
    do {
      GTree* subtree = GSetIterGet(&iter);
      nb += GTreeGetSize(subtree);
    } while (GSetIterStep(&iter));
  }
  // Return the result
  return nb;
}

// ----------- GTreeIter

// ================ Functions declaration ====================

// Create recursively the sequence of an iterator for depth first
void GTreeIterCreateSequenceDepthFirst(GSetGTree* seq, GTree* tree);

// Create recursively the sequence of an iterator for breadth first
void GTreeIterCreateSequenceBreadthFirst(GSetGTree* seq, GTree* tree,
  int lvl);

// Create recursively the sequence of an iterator for value first
void GTreeIterCreateSequenceValueFirst(GSetGTree* seq, GTree* tree, 
  float val);

// ================ Functions implementation ====================

// Create a new GTreeIterDepth for the GTree 'tree'
GTreeIterDepth* GTreeIterDepthCreate(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterDepth *iter = PBErrMalloc(GTreeErr, sizeof(GTreeIterDepth));
  // Set properties
  ((GTreeIter*)iter)->_tree = tree;
  ((GTreeIter*)iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterDepthUpdate(iter);
  GTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GTreeIterDepth for the GTree 'tree'
GTreeIterDepth GTreeIterDepthCreateStatic(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterDepth iter;
  // Set properties
  ((GTreeIter*)&iter)->_tree = tree;
  ((GTreeIter*)&iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterDepthUpdate(&iter);
  GTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Create a new GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth* GTreeIterBreadthCreate(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterBreadth *iter = 
    PBErrMalloc(GTreeErr, sizeof(GTreeIterBreadth));
  // Set properties
  ((GTreeIter*)iter)->_tree = tree;
  ((GTreeIter*)iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterBreadthUpdate(iter);
  GTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth GTreeIterBreadthCreateStatic(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterBreadth iter;
  // Set properties
  ((GTreeIter*)&iter)->_tree = tree;
  ((GTreeIter*)&iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterBreadthUpdate(&iter);
  GTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Create a new GTreeIterValue for the GTree 'tree'
GTreeIterValue* GTreeIterValueCreate(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterValue *iter = PBErrMalloc(GTreeErr, sizeof(GTreeIterValue));
  // Set properties
  ((GTreeIter*)iter)->_tree = tree;
  ((GTreeIter*)iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterValueUpdate(iter);
  GTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GTreeIterValue for the GTree 'tree' with 
// 'rootval' the value of its root node
GTreeIterValue GTreeIterValueCreateStatic(GTree* tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GTreeIterValue iter;
  // Set properties
  ((GTreeIter*)&iter)->_tree = tree;
  ((GTreeIter*)&iter)->_seq = GSetGTreeCreateStatic();
  GTreeIterValueUpdate(&iter);
  GTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Update the GTreeIterDepth 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterDepthUpdate(GTreeIterDepth* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GTreeIterSeq(that));
  // Create the sequence with a Depth First run through nodes of the tree
  GTreeIterCreateSequenceDepthFirst(GTreeIterSeq(that), 
    GTreeIterGTree(that));
  // Reset the current position
  GTreeIterReset(that);
}

// Create recursively the sequence of an iterator for depth first
void GTreeIterCreateSequenceDepthFirst(GSetGTree* seq, GTree* tree) {
  // Append the current tree to the sequence if it's not root
  if (!GTreeIsRoot(tree)) GSetAppend(seq, tree);
  // If there are subtrees
  if (GSetNbElem(GTreeSubtrees(tree)) > 0) {
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GTreeSubtrees(tree));
    do {
      GTree* subtree = GSetIterGet(&iter);
      GTreeIterCreateSequenceDepthFirst(seq, subtree);
    } while (GSetIterStep(&iter));
  }
}

// Update the GTreeIterBreadth 'that' in case its attached GTree has 
// been modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterBreadthUpdate(GTreeIterBreadth* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GTreeIterSeq(that));
  // Create the sequence with a Breadth First run through nodes of 
  // the tree
  GTreeIterCreateSequenceBreadthFirst(GTreeIterSeq(that), 
    GTreeIterGTree(that), 0);
  // Reset the current position
  GTreeIterReset(that);
}

// Create recursively the sequence of an iterator for breadth first
void GTreeIterCreateSequenceBreadthFirst(GSetGTree* seq, GTree* tree,
  int lvl) {
  // Append the current tree to the sequence if it's not root
  if (!GTreeIsRoot(tree)) GSetAddSort(seq, tree, lvl);
  // If there are subtrees
  if (GSetNbElem(GTreeSubtrees(tree)) > 0) {
    // Declare a variable to memorize the next lvl
    int nextLvl = lvl + 1;
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GTreeSubtrees(tree));
    do {
      GTree* subtree = GSetIterGet(&iter);
      GTreeIterCreateSequenceBreadthFirst(seq, subtree, nextLvl);
    } while (GSetIterStep(&iter));
  }
}

// Update the GTreeIterValue 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterValueUpdate(GTreeIterValue* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GTreeIterSeq(that));
  // Create the sequence with a Value First run through nodes of the tree
  GTreeIterCreateSequenceValueFirst(GTreeIterSeq(that), 
    GTreeIterGTree(that), 0.0);
  // Reset the current position
  GTreeIterReset(that);
}

// Create recursively the sequence of an iterator for value first
void GTreeIterCreateSequenceValueFirst(GSetGTree* seq, GTree* tree, 
  float val) {
  // Append the current tree to the sequence if it's not root
  if (!GTreeIsRoot(tree)) GSetAddSort(seq, tree, val);
  // If there are subtrees
  if (GSetNbElem(GTreeSubtrees(tree)) > 0) {
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GTreeSubtrees(tree));
    do {
      GTree* subtree = GSetIterGet(&iter);
      GSetElem* elem = GSetIterGetElem(&iter);
      GTreeIterCreateSequenceValueFirst(seq, subtree, elem->_sortVal);
    } while (GSetIterStep(&iter));
  }
}

// Free the memory used by the iterator 'that'
void _GTreeIterFree(GTreeIter** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  GSetFlush(GTreeIterSeq(*that));
  free(*that);
  *that = NULL;
}

// Free the memory used by the static iterator 'that'
void _GTreeIterFreeStatic(GTreeIter* that) {
  // Check argument
  if (that == NULL)
    // Nothing to do
    return;
  // Free memory
  GSetFlush(GTreeIterSeq(that));
}

