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
void _GTreeFree(GTree** that);

// Free the memory used by the static GTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void _GTreeFreeStatic(GTree* that);

// Get the user data of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
void* _GTreeData(GTree* that);

// Set the user data of the GTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void _GTreeSetData(GTree* that, void* data);

// Get the set of subtrees of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGTree* _GTreeSubtrees(GTree* that);

// Disconnect the GTree 'that' from its parent
// If it has no parent, do nothing
void _GTreeCut(GTree* that);

// Return true if the GTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GTreeIsRoot(GTree* that);

// Return true if the GTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GTreeIsLeaf(GTree* that);

// Return the parent of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GTree* _GTreeParent(GTree* that);

// Return the number of subtrees of the GTree 'that' and their subtrees 
// recursively
int _GTreeGetSize(GTree* that);

// Wrapping of GSet functions
inline GTree* _GTreeSubtree(GTree* that, int iSubtree) {
  return GSetGet(_GTreeSubtrees(that), iSubtree);
}
inline GTree* _GTreeFirstSubtree(GTree* that) {
  return GSetGetFirst(_GTreeSubtrees(that));
}
inline GTree* _GTreeLastSubtree(GTree* that) {
  return GSetGetLast(_GTreeSubtrees(that));
}
inline GTree* _GTreePopSubtree(GTree* that) {
  return GSetPop(_GTreeSubtrees(that));
}
inline GTree* _GTreeDropSubtree(GTree* that) {
  return GSetDrop(_GTreeSubtrees(that));
}
inline GTree* _GTreeRemoveSubtree(GTree* that, int iSubtree) {
  return GSetRemove((GSet*)_GTreeSubtrees(that), iSubtree);
}

inline void _GTreePushSubtree(GTree* that, GTree* tree) {
  if (!tree) return;
  GSetPush(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GTreeAddSortSubTree(GTree* that, GTree* tree, 
  float sortVal) {
  if (!tree) return;
  GSetAddSort(_GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GTreeInsertSubtree(GTree* that, GTree* tree, int pos) {
  if (!tree) return;
  GSetInsert(_GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GTreeAppendSubtree(GTree* that, GTree* tree) {
  if (!tree) return;
  GSetAppend(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}

inline void _GTreePushData(GTree* that, void* data) {
  GTree* tree = GTreeCreateData(data);
  GSetPush(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GTreeAddSortData(GTree* that, void* data, 
  float sortVal) {
  GTree* tree = GTreeCreateData(data);
  GSetAddSort(_GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GTreeInsertData(GTree* that, void* data, int pos) {
  GTree* tree = GTreeCreateData(data);
  GSetInsert(_GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GTreeAppendData(GTree* that, void* data) {
  GTree* tree = GTreeCreateData(data);
  GSetAppend(_GTreeSubtrees(that), tree);
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
GTreeIterDepth* _GTreeIterDepthCreate(GTree* tree);

// Create a new static GTreeIterDepth for the GTree 'tree'
GTreeIterDepth _GTreeIterDepthCreateStatic(GTree* tree);

// Create a new GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth* _GTreeIterBreadthCreate(GTree* tree);

// Create a new static GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth _GTreeIterBreadthCreateStatic(GTree* tree);

// Create a new GTreeIterValue for the GTree 'tree'
GTreeIterValue* _GTreeIterValueCreate(GTree* tree);

// Create a new static GTreeIterValue for the GTree 'tree'
GTreeIterValue _GTreeIterValueCreateStatic(GTree* tree);

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

// ================= Typed GTree ==================

typedef struct GTreeStr {GTree _tree;} GTreeStr;
#define GTreeStrCreate() ((GTreeStr*)GTreeCreate())
inline GTreeStr GTreeStrCreateStatic(void) 
  {GTreeStr ret = {._tree=GTreeCreateStatic()}; return ret;}
#define GTreeStrCreateData(Data) ((GTreeStr*)GTreeCreateData(Data))
inline char* _GTreeStrData(GTreeStr* that) {
  return (char*)_GTreeData((GTree*)that);
}
inline void _GTreeStrSetData(GTreeStr* that, char* data) {
  _GTreeSetData((GTree*)that, (void*)data);
}
inline GSetGTreeStr* _GTreeStrSubtrees(GTreeStr* that) {
  return (GSetGTreeStr*)_GTreeSubtrees((GTree*)that);
}
inline GTreeStr* _GTreeStrParent(GTreeStr* that) {
  return (GTreeStr*)_GTreeParent((GTree*)that);
}
inline void _GTreeStrPushData(GTreeStr* that, char* data) {
  _GTreePushData((GTree*)that, (void*)data);
}
inline void _GTreeStrAddSortData(GTreeStr* that, char* data, 
  float sortVal) {
  _GTreeAddSortData((GTree*)that, (void*)data, sortVal);
}
inline void _GTreeStrInsertData(GTreeStr* that, char* data, int pos) {
  _GTreeInsertData((GTree*)that, (void*)data, pos);
}
inline void _GTreeStrAppendData(GTreeStr* that, char* data) {
  _GTreeAppendData((GTree*)that, (void*)data);
}
inline GTreeStr* _GTreeStrSubtree(GTreeStr* that, int iSubtree) {
  return (GTreeStr*)_GTreeSubtree((GTree*)that, iSubtree);
}
inline GTreeStr* _GTreeStrFirstSubtree(GTreeStr* that) {
  return (GTreeStr*)_GTreeFirstSubtree((GTree*)that);
}
inline GTreeStr* _GTreeStrLastSubtree(GTreeStr* that) {
  return (GTreeStr*)_GTreeLastSubtree((GTree*)that);
}
inline GTreeStr* _GTreeStrPopSubtree(GTreeStr* that) {
  return (GTreeStr*)_GTreePopSubtree((GTree*)that);
}
inline GTreeStr* _GTreeStrDropSubtree(GTreeStr* that) {
  return (GTreeStr*)_GTreeDropSubtree((GTree*)that);
}
inline GTreeStr* _GTreeStrRemoveSubtree(GTreeStr* that, int iSubtree) {
  return (GTreeStr*)_GTreeRemoveSubtree((GTree*)that, iSubtree);
}
inline void _GTreeStrPushSubtree(GTreeStr* that, GTreeStr* tree) {
  _GTreePushSubtree((GTree*)that, (GTree*)tree);
}
inline void _GTreeStrAddSortSubTree(GTreeStr* that, GTreeStr* tree, 
  float sortVal) {
  _GTreeAddSortSubTree((GTree*)that, (GTree*)tree, sortVal);
}
inline void _GTreeStrInsertSubtree(GTreeStr* that, GTreeStr* tree, 
  int pos) {
  _GTreeInsertSubtree((GTree*)that, (GTree*)tree, pos);
}
inline void _GTreeStrAppendSubtree(GTreeStr* that, GTreeStr* tree) {
  _GTreeAppendSubtree((GTree*)that, (GTree*)tree);
}

// ================ Polymorphism ====================

#define GTreeFree(RefTree) _Generic(RefTree, \
  GTree**: _GTreeFree, \
  GTreeStr**: _GTreeFree, \
  default: PBErrInvalidPolymorphism) ((GTree**)(RefTree))

#define GTreeFreeStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeFreeStatic, \
  GTreeStr*: _GTreeFreeStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeParent(Tree) _Generic(Tree, \
  GTree*: _GTreeParent, \
  GTreeStr*: _GTreeStrParent, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeSubtrees(Tree) _Generic(Tree, \
  GTree*: _GTreeSubtrees, \
  GTreeStr*: _GTreeStrSubtrees, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeData(Tree) _Generic(Tree, \
  GTree*: _GTreeData, \
  GTreeStr*: _GTreeStrData, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeSetData(Tree, Data) _Generic(Tree, \
  GTree*: _GTreeSetData, \
  GTreeStr*: _GTreeStrSetData, \
  default: PBErrInvalidPolymorphism) (Tree, Data)

#define GTreeCut(Tree) _Generic(Tree, \
  GTree*: _GTreeCut, \
  GTreeStr*: _GTreeCut, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIsRoot(Tree) _Generic(Tree, \
  GTree*: _GTreeIsRoot, \
  GTreeStr*: _GTreeIsRoot, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIsLeaf(Tree) _Generic(Tree, \
  GTree*: _GTreeIsLeaf, \
  GTreeStr*: _GTreeIsLeaf, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeGetSize(Tree) _Generic(Tree, \
  GTree*: _GTreeGetSize, \
  GTreeStr*: _GTreeGetSize, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreePushData(Tree, Data) _Generic(Tree, \
  GTree*: _GTreePushData, \
  GTreeStr*: _GTreeStrPushData, \
  default: PBErrInvalidPolymorphism) (Tree, Data);

#define GTreeAddSortData(Tree, Data, SortVal) _Generic(Tree, \
  GTree*: _GTreeAddSortData, \
  GTreeStr*: _GTreeStrAddSortData, \
  default: PBErrInvalidPolymorphism) (Tree, Data, SortVal);

#define GTreeInsertData(Tree, Data, Pos) _Generic(Tree, \
  GTree*: _GTreeInsertData, \
  GTreeStr*: _GTreeStrInsertData, \
  default: PBErrInvalidPolymorphism) (Tree, Data, Pos);

#define GTreeAppendData(Tree, Data) _Generic(Tree, \
  GTree*: _GTreeAppendData, \
  GTreeStr*: _GTreeStrAppendData, \
  default: PBErrInvalidPolymorphism) (Tree, Data);

#define GTreeSubtree(Tree, ISubtree) _Generic(Tree, \
  GTree*: _GTreeSubtree, \
  GTreeStr*: _GTreeStrSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, ISubtree)

#define GTreeFirstSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreeFirstSubtree, \
  GTreeStr*: _GTreeStrFirstSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeLastSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreeLastSubtree, \
  GTreeStr*: _GTreeStrLastSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreePopSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreePopSubtree, \
  GTreeStr*: _GTreeStrPopSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeDropSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreeDropSubtree, \
  GTreeStr*: _GTreeStrDropSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeRemoveSubtree(Tree, ISubTree) _Generic(Tree, \
  GTree*: _GTreeRemoveSubtree, \
  GTreeStr*: _GTreeStrRemoveSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, ISubTree)

#define GTreePushSubtree(Tree, SubTree) _Generic(Tree, \
  GTree*: _GTreePushSubtree, \
  GTreeStr*: _GTreeStrPushSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree)

#define GTreeAddSortSubtree(Tree, SubTree, SortVal) _Generic(Tree, \
  GTree*: _GTreeAddSortSubtree, \
  GTreeStr*: _GTreeStrAddSortSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree, SortVal)

#define GTreeInsertSubtree(Tree, SubTree, Pos) _Generic(Tree, \
  GTree*: _GTreeInsertSubtree, \
  GTreeStr*: _GTreeStrInsertSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree, Pos)

#define GTreeAppendSubtree(Tree, SubTree) _Generic(Tree, \
  GTree*: _GTreeAppendSubtree, \
  GTreeStr*: _GTreeStrAppendSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree)

#define GTreeIterDepthCreate(Tree) _Generic(Tree, \
  GTree*: _GTreeIterDepthCreate, \
  GTreeStr*: _GTreeIterDepthCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterDepthCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterDepthCreateStatic, \
  GTreeStr*: _GTreeIterDepthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterBreadthCreate(Tree) _Generic(Tree, \
  GTree*: _GTreeIterBreadthCreate, \
  GTreeStr*: _GTreeIterBreadthCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterBreadthCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterBreadthCreateStatic, \
  GTreeStr*: _GTreeIterBreadthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterValueCreate(Tree) _Generic(Tree, \
  GTree*: _GTreeIterValueCreate, \
  GTreeStr*: _GTreeIterValueCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterValueCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterValueCreateStatic, \
  GTreeStr*: _GTreeIterValueCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

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
