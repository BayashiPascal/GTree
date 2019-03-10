// ============ GTREE.C ================

// ================= Include =================

#include "gtree.h"
#if BUILDMODE == 0
#include "gtree-inline.c"
#endif

// ================ Functions declaration ====================

// Free the memory used by 'subtrees' recursively 
void GenTreeFreeRec(GSetGenTree* subtrees);

// ================ Functions implementation ====================

// Create a new GenTree
GenTree* GenTreeCreate(void) {
  // Declare the new tree
  GenTree *that = PBErrMalloc(GenTreeErr, sizeof(GenTree));
  // Set properties
  that->_parent = NULL;
  that->_subtrees = GSetGenTreeCreateStatic();
  that->_data = NULL;
  // Return the tree
  return that;  
}

// Create a new static GenTree
GenTree GenTreeCreateStatic(void) {
  // Declare the new tree
  GenTree that;
  // Set properties
  that._parent = NULL;
  that._subtrees = GSetGenTreeCreateStatic();
  that._data = NULL;
  // Return the tree
  return that;  
}

// Create a new GenTree with user data 'data'
GenTree* GenTreeCreateData(void* const data) {
  // Declare the new tree
  GenTree *that = PBErrMalloc(GenTreeErr, sizeof(GenTree));
  // Set properties
  that->_parent = NULL;
  that->_subtrees = GSetGenTreeCreateStatic();
  that->_data = data;
  // Return the tree
  return that;  
}

// Free the memory used by the GenTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void _GenTreeFree(GenTree** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // If it's not a root node
  if (!GenTreeIsRoot(*that))
    // Cut the tree
    GenTreeCut(*that);
  // Free recursively the memory
  GenTreeFreeRec(GenTreeSubtrees(*that));
  free(*that);
  *that = NULL;
}

// Free the memory used by 'subtrees' recursively 
void GenTreeFreeRec(GSetGenTree* subtrees) {
  while (GSetNbElem(subtrees) > 0) {
    GenTree* tree = GSetPop(subtrees);
    GenTreeFreeRec(GenTreeSubtrees(tree));
    free(tree);
  }
}

// Free the memory used by the static GenTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void _GenTreeFreeStatic(GenTree* that) {
  // Check argument
  if (that == NULL)
    // Nothing to do
    return;
  // If it's not a root node
  if (!GenTreeIsRoot(that))
    // Cut the tree
    GenTreeCut(that);
  // Free memory
  GenTreeFreeRec(GenTreeSubtrees(that));
}

// Disconnect the GenTree 'that' from its parent
// If it has no parent, do nothing
void _GenTreeCut(GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // If there is no parent
  if (GenTreeParent(that) == NULL)
    // Nothing to do
    return;
  // Remove the tree from the parent's subtrees
  GSetRemoveAll(GenTreeSubtrees(GenTreeParent(that)), that);
  // Cut the link to the parent
  that->_parent = NULL;
}

// Return the number of subtrees of the GenTree 'that' and their subtrees 
// recursively
int _GenTreeGetSize(const GenTree* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare a variable to memorize the result and initialize it with 
  // the number of subtrees
  int nb = GSetNbElem(GenTreeSubtrees(that));
  // If there are subtrees
  if (nb > 0) {
    // Recursion on the subtrees
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GenTreeSubtrees(that));
    do {
      GenTree* subtree = GSetIterGet(&iter);
      nb += GenTreeGetSize(subtree);
    } while (GSetIterStep(&iter));
  }
  // Return the result
  return nb;
}

// Append a new node with 'data' to the first node containing 'node'
// in the GenTree 'that'
// Uses the iterator 'iter' to search the node
// Return true if we could find 'node', false else
bool _GenTreeAppendToNode(GenTree* const that, 
  void* const data, void* const node, GenTreeIter* const iter) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
  if (iter == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iter' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare a variable to memorize the result
  bool res = false;
  // Search the node where to append the data
  GenTree* nodeTree = GenTreeSearch(that, node, iter);
  // If we could find the node
  if (nodeTree != NULL) {
    // Append the data
    GenTreeAppendData(nodeTree, data);
    // Update the result
    res = true;
  }
  // Return the result
  return res;
}

// Search the first node containing 'data' in the GenTree 'that'
// Uses the iterator 'iter' to search the node. Do not reset the 
// iterator, thus several calls with the same iterator will return 
// eventual successive nodes containing the same data. If one want to 
// loop on these nodes, the proper stopping condition is 
// while(GenTreeSearch() != NULL && GenTreeIterIsLast() == false)
// Return the node if we could find 'data', null else
GenTree* _GenTreeSearch(const GenTree* const that, 
  const void* const data, GenTreeIter* const iter) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  } 
  if (iter == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'iter' is null");
    PBErrCatch(GSetErr);
  }
#endif
  (void)that;
  // Declare a variable to memorize the result
  GenTree* res = NULL;
  // Loop until we have found or reached the end
  do {
    // If we have found the searched data
    if (GenTreeIterGetData(iter) == data)
      // Memorize the node containing the data
      res = GenTreeIterGetGenTree(iter);
  } while (GenTreeIterStep(iter) && res == NULL);
  // Return the result
  return res;
}

// ----------- GenTreeIter

// ================ Functions declaration ====================

// Create recursively the sequence of an iterator for depth first
void GenTreeIterCreateSequenceDepthFirst(GSetGenTree* seq, GenTree* tree);

// Create recursively the sequence of an iterator for breadth first
void GenTreeIterCreateSequenceBreadthFirst(GSetGenTree* seq, GenTree* tree,
  int lvl);

// Create recursively the sequence of an iterator for value first
void GenTreeIterCreateSequenceValueFirst(GSetGenTree* seq, GenTree* tree, 
  float val);

// ================ Functions implementation ====================

// Create a new GenTreeIterDepth for the GenTree 'tree'
GenTreeIterDepth* _GenTreeIterDepthCreate(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterDepth *iter = PBErrMalloc(GenTreeErr, sizeof(GenTreeIterDepth));
  // Set properties
  ((GenTreeIter*)iter)->_tree = tree;
  ((GenTreeIter*)iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterDepthUpdate(iter);
  GenTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GenTreeIterDepth for the GenTree 'tree'
GenTreeIterDepth _GenTreeIterDepthCreateStatic(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterDepth iter;
  // Set properties
  ((GenTreeIter*)&iter)->_tree = tree;
  ((GenTreeIter*)&iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterDepthUpdate(&iter);
  GenTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Create a new GenTreeIterBreadth for the GenTree 'tree'
GenTreeIterBreadth* _GenTreeIterBreadthCreate(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterBreadth *iter = 
    PBErrMalloc(GenTreeErr, sizeof(GenTreeIterBreadth));
  // Set properties
  ((GenTreeIter*)iter)->_tree = tree;
  ((GenTreeIter*)iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterBreadthUpdate(iter);
  GenTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GenTreeIterBreadth for the GenTree 'tree'
GenTreeIterBreadth _GenTreeIterBreadthCreateStatic(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterBreadth iter;
  // Set properties
  ((GenTreeIter*)&iter)->_tree = tree;
  ((GenTreeIter*)&iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterBreadthUpdate(&iter);
  GenTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Create a new GenTreeIterValue for the GenTree 'tree'
GenTreeIterValue* _GenTreeIterValueCreate(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterValue *iter = PBErrMalloc(GenTreeErr, sizeof(GenTreeIterValue));
  // Set properties
  ((GenTreeIter*)iter)->_tree = tree;
  ((GenTreeIter*)iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterValueUpdate(iter);
  GenTreeIterReset(iter);
  // Return the iterator
  return iter;  
}

// Create a new static GenTreeIterValue for the GenTree 'tree' with 
// 'rootval' the value of its root node
GenTreeIterValue _GenTreeIterValueCreateStatic(GenTree* const tree) {
#if BUILDMODE == 0
  if (tree == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'tree' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Declare the new iterator
  GenTreeIterValue iter;
  // Set properties
  ((GenTreeIter*)&iter)->_tree = tree;
  ((GenTreeIter*)&iter)->_seq = GSetGenTreeCreateStatic();
  GenTreeIterValueUpdate(&iter);
  GenTreeIterReset(&iter);
  // Return the iterator
  return iter;
}

// Update the GenTreeIterDepth 'that' in case its attached GenTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterDepthUpdate(GenTreeIterDepth* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GenTreeIterSeq(that));
  // Create the sequence with a Depth First run through nodes of the tree
  GenTreeIterCreateSequenceDepthFirst(GenTreeIterSeq(that), 
    GenTreeIterGenTree(that));
  // Reset the current position
  GenTreeIterReset(that);
}

// Create recursively the sequence of an iterator for depth first
void GenTreeIterCreateSequenceDepthFirst(GSetGenTree* seq, GenTree* tree) {
  // Append the current tree to the sequence if it's not root
  if (!GenTreeIsRoot(tree)) GSetAppend(seq, tree);
  // If there are subtrees
  if (GSetNbElem(GenTreeSubtrees(tree)) > 0) {
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GenTreeSubtrees(tree));
    do {
      GenTree* subtree = GSetIterGet(&iter);
      GenTreeIterCreateSequenceDepthFirst(seq, subtree);
    } while (GSetIterStep(&iter));
  }
}

// Update the GenTreeIterBreadth 'that' in case its attached GenTree has 
// been modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterBreadthUpdate(GenTreeIterBreadth* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GenTreeIterSeq(that));
  // Create the sequence with a Breadth First run through nodes of 
  // the tree
  GenTreeIterCreateSequenceBreadthFirst(GenTreeIterSeq(that), 
    GenTreeIterGenTree(that), 0);
  // Reset the current position
  GenTreeIterReset(that);
}

// Create recursively the sequence of an iterator for breadth first
void GenTreeIterCreateSequenceBreadthFirst(GSetGenTree* seq, GenTree* tree,
  int lvl) {
  // Append the current tree to the sequence if it's not root
  if (!GenTreeIsRoot(tree)) GSetAddSort(seq, tree, lvl);
  // If there are subtrees
  if (GSetNbElem(GenTreeSubtrees(tree)) > 0) {
    // Declare a variable to memorize the next lvl
    int nextLvl = lvl + 1;
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GenTreeSubtrees(tree));
    do {
      GenTree* subtree = GSetIterGet(&iter);
      GenTreeIterCreateSequenceBreadthFirst(seq, subtree, nextLvl);
    } while (GSetIterStep(&iter));
  }
}

// Update the GenTreeIterValue 'that' in case its attached GenTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterValueUpdate(GenTreeIterValue* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    GenTreeErr->_type = PBErrTypeNullPointer;
    sprintf(GSetErr->_msg, "'that' is null");
    PBErrCatch(GSetErr);
  }
#endif
  // Flush the sequence
  GSetFlush(GenTreeIterSeq(that));
  // Create the sequence with a Value First run through nodes of the tree
  GenTreeIterCreateSequenceValueFirst(GenTreeIterSeq(that), 
    GenTreeIterGenTree(that), 0.0);
  // Reset the current position
  GenTreeIterReset(that);
}

// Create recursively the sequence of an iterator for value first
void GenTreeIterCreateSequenceValueFirst(GSetGenTree* seq, GenTree* tree, 
  float val) {
  // Append the current tree to the sequence if it's not root
  if (!GenTreeIsRoot(tree)) GSetAddSort(seq, tree, val);
  // If there are subtrees
  if (GSetNbElem(GenTreeSubtrees(tree)) > 0) {
    // Append the subtrees recursively
    GSetIterForward iter = 
      GSetIterForwardCreateStatic(GenTreeSubtrees(tree));
    do {
      GenTree* subtree = GSetIterGet(&iter);
      GenTreeIterCreateSequenceValueFirst(seq, subtree, 
        GSetIterGetSortVal(&iter));
    } while (GSetIterStep(&iter));
  }
}

// Free the memory used by the iterator 'that'
void _GenTreeIterFree(GenTreeIter** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  GSetFlush(GenTreeIterSeq(*that));
  free(*that);
  *that = NULL;
}

// Free the memory used by the static iterator 'that'
void _GenTreeIterFreeStatic(GenTreeIter* const that) {
  // Check argument
  if (that == NULL)
    // Nothing to do
    return;
  // Free memory
  GSetFlush(GenTreeIterSeq(that));
}

