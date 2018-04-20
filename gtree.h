// ============ GTREE.H ================

#ifndef GTREE_H
#define GTREE_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "pberr.h"
#include "gset.h"

// ----------- GTree

// ================= Define ==================

// ================= Data structure ===================

typedef struct GTree {
  // Parent node
  GTree* _parent;
  // Branches
  // Branch cannot be null, if the user tries to add a null branch 
  // nothing happen
  GSetGTree _subtrees;
  // User data
  void* _data;
} GTree;

// ================ Functions declaration ====================

// Create a new GTree
GTree* GTreeCreate(void);

// Create a new static GTree
GTree GTreeCreateStatic(void);

// Create a new GTree with user data 'data'
GTree* GTreeCreateData(void* data);

// Free the memory used by the GTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void GTreeFree(GTree** that);

// Free the memory used by the static GTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void GTreeFreeStatic(GTree* that);

// Get the user data of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
void* GTreeData(GTree* that);

// Set the user data of the GTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void GTreeSetData(GTree* that, void* data);

// Get the set of subtrees of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGTree* GTreeSubtrees(GTree* that);

// Disconnect the GTree 'that' from its parent
// If it has no parent, do nothing
void GTreeCut(GTree* that);

// Return true if the GTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool GTreeIsRoot(GTree* that);

// Return true if the GTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool GTreeIsLeaf(GTree* that);

// Return the parent of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GTree* GTreeParent(GTree* that);

// Return the number of subtrees of the GTree 'that' and their subtrees 
// recursively
int GTreeGetSize(GTree* that);

// Wrapping of GSet functions
inline GTree* GTreeSubtree(GTree* that, int iSubtree) {
  return GSetGet(GTreeSubtrees(that), iSubtree);
}
inline GTree* GTreeFirstSubtree(GTree* that) {
  return GSetGetFirst(GTreeSubtrees(that));
}
inline GTree* GTreeLastSubtree(GTree* that) {
  return GSetGetLast(GTreeSubtrees(that));
}
inline GTree* GTreePopSubtree(GTree* that) {
  return GSetPop(GTreeSubtrees(that));
}
inline GTree* GTreeDropSubtree(GTree* that) {
  return GSetDrop(GTreeSubtrees(that));
}
inline GTree* GTreeRemoveSubtree(GTree* that, int iSubtree) {
  return GSetRemove((GSet*)GTreeSubtrees(that), iSubtree);
}

inline void GTreePushSubtree(GTree* that, GTree* tree) {
  if (!tree) return;
  GSetPush(GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void GTreeAddSortSubTree(GTree* that, GTree* tree, 
  float sortVal) {
  if (!tree) return;
  GSetAddSort(GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void GTreeInsertSubtree(GTree* that, GTree* tree, int pos) {
  if (!tree) return;
  GSetInsert(GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void GTreeAppendSubtree(GTree* that, GTree* tree) {
  if (!tree) return;
  GSetAppend(GTreeSubtrees(that), tree);
  tree->_parent = that;
}

inline void GTreePushData(GTree* that, void* data) {
  GTree* tree = GTreeCreateData(data);
  GSetPush(GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void GTreeAddSortData(GTree* that, void* data, 
  float sortVal) {
  GTree* tree = GTreeCreateData(data);
  GSetAddSort(GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void GTreeInsertData(GTree* that, void* data, int pos) {
  GTree* tree = GTreeCreateData(data);
  GSetInsert(GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void GTreeAppendData(GTree* that, void* data) {
  GTree* tree = GTreeCreateData(data);
  GSetAppend(GTreeSubtrees(that), tree);
  tree->_parent = that;
}

// ----------- GTreeIter

// ================= Define ==================

// ================= Data structure ===================

typedef struct GTreeIter {
  // Attached tree
  GTree* _tree;
  // Current position
  GSetElem* _curPos;
  // GSet to memorize nodes sequence
  // The node sequence doesn't include the root node of the attached tree
  GSetGTree _seq;
} GTreeIter;

typedef struct GTreeIterDepth {GTreeIter _iter;} GTreeIterDepth;
typedef struct GTreeIterBreadth {GTreeIter _iter;} GTreeIterBreadth;
typedef struct GTreeIterValue {GTreeIter _iter;} GTreeIterValue;

// ================ Functions declaration ====================

// Create a new GTreeIterDepth for the GTree 'tree'
GTreeIterDepth* GTreeIterDepthCreate(GTree* tree);

// Create a new static GTreeIterDepth for the GTree 'tree'
GTreeIterDepth GTreeIterDepthCreateStatic(GTree* tree);

// Create a new GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth* GTreeIterBreadthCreate(GTree* tree);

// Create a new static GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth GTreeIterBreadthCreateStatic(GTree* tree);

// Create a new GTreeIterValue for the GTree 'tree'
GTreeIterValue* GTreeIterValueCreate(GTree* tree);

// Create a new static GTreeIterValue for the GTree 'tree'
GTreeIterValue GTreeIterValueCreateStatic(GTree* tree);

// Update the GTreeIterDepth 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterDepthUpdate(GTreeIterDepth* that);

// Update the GTreeIterBreadth 'that' in case its attached GTree has 
// been modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterBreadthUpdate(GTreeIterBreadth* that);

// Update the GTreeIterValue 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterValueUpdate(GTreeIterValue* that);

// Free the memory used by the iterator 'that'
void _GTreeIterFree(GTreeIter** that);

// Free the memory used by the static iterator 'that'
void _GTreeIterFreeStatic(GTreeIter* that);

// Reset the iterator 'that' at its start position
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterReset(GTreeIter* that);

// Reset the iterator 'that' at its end position
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterToEnd(GTreeIter* that);

// Step the iterator 'that' at its next position
// Return true if it could move to the next position
// Return false if it's already at the last position
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterStep(GTreeIter* that);

// Step back the iterator 'that' at its next position
// Return true if it could move to the previous position
// Return false if it's already at the first position
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterStepBack(GTreeIter* that);

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
  void(*fun)(void* data, void* param), void* param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsFirst(GTreeIter* that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsLast(GTreeIter* that);

// Change the attached tree of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterDepthSetGTree(GTreeIterDepth* that, GTree* tree);
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterBreadthSetGTree(GTreeIterBreadth* that, GTree* tree);
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterValueSetGTree(GTreeIterValue* that, GTree* tree);

// Return the user data of the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* _GTreeIterGetData(GTreeIter* that);

// Return the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGetGTree(GTreeIter* that);

// Return the tree associated to the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGTree(GTreeIter* that);

// Return the sequence of the iterator
#if BUILDMODE != 0
inline
#endif 
GSetGTree* _GTreeIterSeq(GTreeIter* that);

// ================ Polymorphism ====================

#define GTreeIterFree(RefIter) _Generic(RefIter, \
  GTreeIter**: _GTreeIterFree, \
  GTreeIterDepth**: _GTreeIterFree, \
  GTreeIterBreadth**: _GTreeIterFree, \
  GTreeIterValue**: _GTreeIterFree, \
  default: PBErrInvalidPolymorphism) ((GTreeIter**)(RefIter))

#define GTreeIterFreeStatic(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterFreeStatic, \
  GTreeIterDepth*: _GTreeIterFreeStatic, \
  GTreeIterBreadth*: _GTreeIterFreeStatic, \
  GTreeIterValue*: _GTreeIterFreeStatic, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterReset(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterReset, \
  GTreeIterDepth*: _GTreeIterReset, \
  GTreeIterBreadth*: _GTreeIterReset, \
  GTreeIterValue*: _GTreeIterReset, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterToEnd(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterToEnd, \
  GTreeIterDepth*: _GTreeIterToEnd, \
  GTreeIterBreadth*: _GTreeIterToEnd, \
  GTreeIterValue*: _GTreeIterToEnd, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterStep(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterStep, \
  GTreeIterDepth*: _GTreeIterStep, \
  GTreeIterBreadth*: _GTreeIterStep, \
  GTreeIterValue*: _GTreeIterStep, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterStepBack(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterStepBack, \
  GTreeIterDepth*: _GTreeIterStepBack, \
  GTreeIterBreadth*: _GTreeIterStepBack, \
  GTreeIterValue*: _GTreeIterStepBack, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterApply(Iter, Fun, Param) _Generic(Iter, \
  GTreeIter*: _GTreeIterApply, \
  GTreeIterDepth*: _GTreeIterApply, \
  GTreeIterBreadth*: _GTreeIterApply, \
  GTreeIterValue*: _GTreeIterApply, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter), Fun, Param)

#define GTreeIterIsFirst(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterIsFirst, \
  GTreeIterDepth*: _GTreeIterIsFirst, \
  GTreeIterBreadth*: _GTreeIterIsFirst, \
  GTreeIterValue*: _GTreeIterIsFirst, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterIsLast(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterIsLast, \
  GTreeIterDepth*: _GTreeIterIsLast, \
  GTreeIterBreadth*: _GTreeIterIsLast, \
  GTreeIterValue*: _GTreeIterIsLast, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterSetGTree(Iter, Tree) _Generic(Iter, \
  GTreeIterDepth*: _GTreeIterDepthSetGTree, \
  GTreeIterBreadth*: _GTreeIterBreadthSetGTree, \
  GTreeIterValue*: _GTreeIterValueSetGTree, \
  default: PBErrInvalidPolymorphism) (Iter, Tree)

#define GTreeIterGetData(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGetData, \
  GTreeIterDepth*: _GTreeIterGetData, \
  GTreeIterBreadth*: _GTreeIterGetData, \
  GTreeIterValue*: _GTreeIterGetData, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterGTree(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGTree, \
  GTreeIterDepth*: _GTreeIterGTree, \
  GTreeIterBreadth*: _GTreeIterGTree, \
  GTreeIterValue*: _GTreeIterGTree, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterGetGTree(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGetGTree, \
  GTreeIterDepth*: _GTreeIterGetGTree, \
  GTreeIterBreadth*: _GTreeIterGetGTree, \
  GTreeIterValue*: _GTreeIterGetGTree, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterSeq(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterSeq, \
  GTreeIterDepth*: _GTreeIterSeq, \
  GTreeIterBreadth*: _GTreeIterSeq, \
  GTreeIterValue*: _GTreeIterSeq, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gtree-inline.c"
#endif


#endif
