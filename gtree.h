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
GTree* GTreeCreateData(void* const data);

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
void* _GTreeData(const GTree* const that);

// Set the user data of the GTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void _GTreeSetData(GTree* const that, void* const data);

// Get the set of subtrees of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGTree* _GTreeSubtrees(const GTree* const that);

// Disconnect the GTree 'that' from its parent
// If it has no parent, do nothing
void _GTreeCut(GTree* const that);

// Return true if the GTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GTreeIsRoot(const GTree* const that);

// Return true if the GTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GTreeIsLeaf(const GTree* const that);

// Return the parent of the GTree 'that'
#if BUILDMODE != 0
inline
#endif
GTree* _GTreeParent(const GTree* const that);

// Return the number of subtrees of the GTree 'that' and their subtrees 
// recursively
int _GTreeGetSize(const GTree* const that);

// Wrapping of GSet functions
inline GTree* _GTreeSubtree(const GTree* const that, const int iSubtree) {
  return GSetGet(_GTreeSubtrees(that), iSubtree);
}
inline GTree* _GTreeFirstSubtree(const GTree* const that) {
  return GSetGetFirst(_GTreeSubtrees(that));
}
inline GTree* _GTreeLastSubtree(const GTree* const that) {
  return GSetGetLast(_GTreeSubtrees(that));
}
inline GTree* _GTreePopSubtree(GTree* const that) {
  return GSetPop(_GTreeSubtrees(that));
}
inline GTree* _GTreeDropSubtree(GTree* const that) {
  return GSetDrop(_GTreeSubtrees(that));
}
inline GTree* _GTreeRemoveSubtree(GTree* const that, const int iSubtree) {
  return GSetRemove((GSet*)_GTreeSubtrees(that), iSubtree);
}

inline void _GTreePushSubtree(GTree* const that, GTree* const tree) {
  if (!tree) return;
  GSetPush(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GTreeAddSortSubTree(GTree* const that, GTree* const tree, 
  const float sortVal) {
  if (!tree) return;
  GSetAddSort(_GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GTreeInsertSubtree(GTree* const that, GTree* const tree, 
  const int pos) {
  if (!tree) return;
  GSetInsert(_GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GTreeAppendSubtree(GTree* const that, GTree* const tree) {
  if (!tree) return;
  GSetAppend(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}

inline void _GTreePushData(GTree* const that, void* const data) {
  GTree* tree = GTreeCreateData(data);
  GSetPush(_GTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GTreeAddSortData(GTree* const that, void* const data, 
  const float sortVal) {
  GTree* tree = GTreeCreateData(data);
  GSetAddSort(_GTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GTreeInsertData(GTree* const that, void* const data, 
  const int pos) {
  GTree* tree = GTreeCreateData(data);
  GSetInsert(_GTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GTreeAppendData(GTree* const that, void* const data) {
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
GTreeIterDepth* _GTreeIterDepthCreate(GTree* const tree);

// Create a new static GTreeIterDepth for the GTree 'tree'
GTreeIterDepth _GTreeIterDepthCreateStatic(GTree* const tree);

// Create a new GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth* _GTreeIterBreadthCreate(GTree* const tree);

// Create a new static GTreeIterBreadth for the GTree 'tree'
GTreeIterBreadth _GTreeIterBreadthCreateStatic(GTree* const tree);

// Create a new GTreeIterValue for the GTree 'tree'
GTreeIterValue* _GTreeIterValueCreate(GTree* const tree);

// Create a new static GTreeIterValue for the GTree 'tree'
GTreeIterValue _GTreeIterValueCreateStatic(GTree* const tree);

// Update the GTreeIterDepth 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterDepthUpdate(GTreeIterDepth* const that);

// Update the GTreeIterBreadth 'that' in case its attached GTree has 
// been modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterBreadthUpdate(GTreeIterBreadth* const that);

// Update the GTreeIterValue 'that' in case its attached GTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GTreeIterValueUpdate(GTreeIterValue* const that);

// Free the memory used by the iterator 'that'
void _GTreeIterFree(GTreeIter** that);

// Free the memory used by the static iterator 'that'
void _GTreeIterFreeStatic(GTreeIter* const that);

// Reset the iterator 'that' at its start position
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterReset(GTreeIter* const that);

// Reset the iterator 'that' at its end position
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterToEnd(GTreeIter* const that);

// Step the iterator 'that' at its next position
// Return true if it could move to the next position
// Return false if it's already at the last position
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterStep(GTreeIter* const that);

// Step back the iterator 'that' at its next position
// Return true if it could move to the previous position
// Return false if it's already at the first position
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterStepBack(GTreeIter* const that);

// Apply a function to all elements' data of the GTree of the iterator
// The iterator is first reset, then the function is apply sequencially
// using the Step function of the iterator
// The applied function takes to void* arguments: 'data' is the _data
// property of the nodes, 'param' is a hook to allow the user to pass
// parameters to the function through a user-defined structure
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterApply(GTreeIter* const that, 
  void(*fun)(void* const data, void* const param), void* const param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsFirst(const GTreeIter* const that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GTreeIterIsLast(const GTreeIter* const that);

// Change the attached tree of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterDepthSetGTree(GTreeIterDepth* const that, 
  GTree* const tree);
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterBreadthSetGTree(GTreeIterBreadth* const that, 
  GTree* const tree);
#if BUILDMODE != 0
inline
#endif 
void _GTreeIterValueSetGTree(GTreeIterValue* const that, 
  GTree* const tree);

// Return the user data of the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* _GTreeIterGetData(const GTreeIter* const that);

// Return the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGetGTree(const GTreeIter* const that);

// Return the tree associated to the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GTree* _GTreeIterGTree(const GTreeIter* const that);

// Return the sequence of the iterator
#if BUILDMODE != 0
inline
#endif 
GSetGTree* _GTreeIterSeq(const GTreeIter* const that);

// ================= Typed GTree ==================

typedef struct GTreeStr {GTree _tree;} GTreeStr;
#define GTreeStrCreate() ((GTreeStr*)GTreeCreate())
inline GTreeStr GTreeStrCreateStatic(void) 
  {GTreeStr ret = {._tree=GTreeCreateStatic()}; return ret;}
#define GTreeStrCreateData(Data) ((GTreeStr*)GTreeCreateData(Data))
inline char* _GTreeStrData(const GTreeStr* const that) {
  return (char*)_GTreeData((const GTree* const)that);
}
inline void _GTreeStrSetData(GTreeStr* const that, char* const data) {
  _GTreeSetData((GTree* const)that, (void* const)data);
}
inline GSetGTreeStr* _GTreeStrSubtrees(const GTreeStr* const that) {
  return (GSetGTreeStr*)_GTreeSubtrees((const GTree* const)that);
}
inline GTreeStr* _GTreeStrParent(const GTreeStr* const that) {
  return (GTreeStr*)_GTreeParent((const GTree* const)that);
}
inline void _GTreeStrPushData(GTreeStr* const that, char* const data) {
  _GTreePushData((GTree* const)that, (void* const)data);
}
inline void _GTreeStrAddSortData(GTreeStr* const that, char* const data, 
  const float sortVal) {
  _GTreeAddSortData((GTree* const)that, (void* const)data, sortVal);
}
inline void _GTreeStrInsertData(GTreeStr* const that, char* const data, 
  const int pos) {
  _GTreeInsertData((GTree* const)that, (void* const)data, pos);
}
inline void _GTreeStrAppendData(GTreeStr* const that, char* const data) {
  _GTreeAppendData((GTree* const)that, (void* const)data);
}
inline GTreeStr* _GTreeStrSubtree(const GTreeStr* const that, 
  const int iSubtree) {
  return (GTreeStr*)_GTreeSubtree((const GTree* const)that, iSubtree);
}
inline GTreeStr* _GTreeStrFirstSubtree(const GTreeStr* const that) {
  return (GTreeStr*)_GTreeFirstSubtree((const GTree* const)that);
}
inline GTreeStr* _GTreeStrLastSubtree(const GTreeStr* const that) {
  return (GTreeStr*)_GTreeLastSubtree((const GTree* const)that);
}
inline GTreeStr* _GTreeStrPopSubtree(GTreeStr* const that) {
  return (GTreeStr*)_GTreePopSubtree((GTree* const)that);
}
inline GTreeStr* _GTreeStrDropSubtree(GTreeStr* const that) {
  return (GTreeStr*)_GTreeDropSubtree((GTree* const)that);
}
inline GTreeStr* _GTreeStrRemoveSubtree(GTreeStr* const that, 
  const int iSubtree) {
  return (GTreeStr*)_GTreeRemoveSubtree((GTree* const)that, iSubtree);
}
inline void _GTreeStrPushSubtree(GTreeStr* const that, 
  GTreeStr* const tree) {
  _GTreePushSubtree((GTree* const)that, (GTree* const)tree);
}
inline void _GTreeStrAddSortSubTree(GTreeStr* const that, 
  GTreeStr* const tree, const float sortVal) {
  _GTreeAddSortSubTree((GTree* const)that, (GTree* const)tree, sortVal);
}
inline void _GTreeStrInsertSubtree(GTreeStr* const that, 
  GTreeStr* const tree, const int pos) {
  _GTreeInsertSubtree((GTree* const)that, (GTree* const)tree, pos);
}
inline void _GTreeStrAppendSubtree(GTreeStr* const that, 
  GTreeStr* const tree) {
  _GTreeAppendSubtree((GTree* const)that, (GTree* const)tree);
}

// ================ Polymorphism ====================

#define GTreeFree(RefTree) _Generic(RefTree, \
  GTree**: _GTreeFree, \
  GTreeStr**: _GTreeFree, \
  default: PBErrInvalidPolymorphism) ((GTree**)(RefTree))

#define GTreeFreeStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeFreeStatic, \
  const GTree*: _GTreeFreeStatic, \
  GTreeStr*: _GTreeFreeStatic, \
  const GTreeStr*: _GTreeFreeStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeParent(Tree) _Generic(Tree, \
  GTree*: _GTreeParent, \
  const GTree*: _GTreeParent, \
  GTreeStr*: _GTreeStrParent, \
  const GTreeStr*: _GTreeStrParent, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeSubtrees(Tree) _Generic(Tree, \
  GTree*: _GTreeSubtrees, \
  const GTree*: _GTreeSubtrees, \
  GTreeStr*: _GTreeStrSubtrees, \
  const GTreeStr*: _GTreeStrSubtrees, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeData(Tree) _Generic(Tree, \
  GTree*: _GTreeData, \
  const GTree*: _GTreeData, \
  GTreeStr*: _GTreeStrData, \
  const GTreeStr*: _GTreeStrData, \
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
  const GTree*: _GTreeIsRoot, \
  GTreeStr*: _GTreeIsRoot, \
  const GTreeStr*: _GTreeIsRoot, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIsLeaf(Tree) _Generic(Tree, \
  GTree*: _GTreeIsLeaf, \
  const GTree*: _GTreeIsLeaf, \
  GTreeStr*: _GTreeIsLeaf, \
  const GTreeStr*: _GTreeIsLeaf, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeGetSize(Tree) _Generic(Tree, \
  GTree*: _GTreeGetSize, \
  const GTree*: _GTreeGetSize, \
  GTreeStr*: _GTreeGetSize, \
  const GTreeStr*: _GTreeGetSize, \
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
  const GTree*: _GTreeSubtree, \
  GTreeStr*: _GTreeStrSubtree, \
  const GTreeStr*: _GTreeStrSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, ISubtree)

#define GTreeFirstSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreeFirstSubtree, \
  const GTree*: _GTreeFirstSubtree, \
  GTreeStr*: _GTreeStrFirstSubtree, \
  const GTreeStr*: _GTreeStrFirstSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GTreeLastSubtree(Tree) _Generic(Tree, \
  GTree*: _GTreeLastSubtree, \
  const GTree*: _GTreeLastSubtree, \
  GTreeStr*: _GTreeStrLastSubtree, \
  const GTreeStr*: _GTreeStrLastSubtree, \
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
  const GTree*: _GTreeIterDepthCreate, \
  GTreeStr*: _GTreeIterDepthCreate, \
  const GTreeStr*: _GTreeIterDepthCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterDepthCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterDepthCreateStatic, \
  const GTree*: _GTreeIterDepthCreateStatic, \
  GTreeStr*: _GTreeIterDepthCreateStatic, \
  const GTreeStr*: _GTreeIterDepthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterBreadthCreate(Tree) _Generic(Tree, \
  GTree*: _GTreeIterBreadthCreate, \
  const GTree*: _GTreeIterBreadthCreate, \
  GTreeStr*: _GTreeIterBreadthCreate, \
  const GTreeStr*: _GTreeIterBreadthCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterBreadthCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterBreadthCreateStatic, \
  const GTree*: _GTreeIterBreadthCreateStatic, \
  GTreeStr*: _GTreeIterBreadthCreateStatic, \
  const GTreeStr*: _GTreeIterBreadthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterValueCreate(Tree) _Generic(Tree, \
  GTree*: _GTreeIterValueCreate, \
  const GTree*: _GTreeIterValueCreate, \
  GTreeStr*: _GTreeIterValueCreate, \
  const GTreeStr*: _GTreeIterValueCreate, \
  default: PBErrInvalidPolymorphism) ((GTree*)(Tree))

#define GTreeIterValueCreateStatic(Tree) _Generic(Tree, \
  GTree*: _GTreeIterValueCreateStatic, \
  const GTree*: _GTreeIterValueCreateStatic, \
  GTreeStr*: _GTreeIterValueCreateStatic, \
  const GTreeStr*: _GTreeIterValueCreateStatic, \
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
  const GTreeIter*: _GTreeIterIsFirst, \
  GTreeIterDepth*: _GTreeIterIsFirst, \
  const GTreeIterDepth*: _GTreeIterIsFirst, \
  GTreeIterBreadth*: _GTreeIterIsFirst, \
  const GTreeIterBreadth*: _GTreeIterIsFirst, \
  GTreeIterValue*: _GTreeIterIsFirst, \
  const GTreeIterValue*: _GTreeIterIsFirst, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterIsLast(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterIsLast, \
  const GTreeIter*: _GTreeIterIsLast, \
  GTreeIterDepth*: _GTreeIterIsLast, \
  const GTreeIterDepth*: _GTreeIterIsLast, \
  GTreeIterBreadth*: _GTreeIterIsLast, \
  const GTreeIterBreadth*: _GTreeIterIsLast, \
  GTreeIterValue*: _GTreeIterIsLast, \
  const GTreeIterValue*: _GTreeIterIsLast, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterSetGTree(Iter, Tree) _Generic(Iter, \
  GTreeIterDepth*: _GTreeIterDepthSetGTree, \
  GTreeIterBreadth*: _GTreeIterBreadthSetGTree, \
  GTreeIterValue*: _GTreeIterValueSetGTree, \
  default: PBErrInvalidPolymorphism) (Iter, Tree)

#define GTreeIterGetData(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGetData, \
  const GTreeIter*: _GTreeIterGetData, \
  GTreeIterDepth*: _GTreeIterGetData, \
  const GTreeIterDepth*: _GTreeIterGetData, \
  GTreeIterBreadth*: _GTreeIterGetData, \
  const GTreeIterBreadth*: _GTreeIterGetData, \
  GTreeIterValue*: _GTreeIterGetData, \
  const GTreeIterValue*: _GTreeIterGetData, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterGTree(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGTree, \
  const GTreeIter*: _GTreeIterGTree, \
  GTreeIterDepth*: _GTreeIterGTree, \
  const GTreeIterDepth*: _GTreeIterGTree, \
  GTreeIterBreadth*: _GTreeIterGTree, \
  const GTreeIterBreadth*: _GTreeIterGTree, \
  GTreeIterValue*: _GTreeIterGTree, \
  const GTreeIterValue*: _GTreeIterGTree, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterGetGTree(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterGetGTree, \
  const GTreeIter*: _GTreeIterGetGTree, \
  GTreeIterDepth*: _GTreeIterGetGTree, \
  const GTreeIterDepth*: _GTreeIterGetGTree, \
  GTreeIterBreadth*: _GTreeIterGetGTree, \
  const GTreeIterBreadth*: _GTreeIterGetGTree, \
  GTreeIterValue*: _GTreeIterGetGTree, \
  const GTreeIterValue*: _GTreeIterGetGTree, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

#define GTreeIterSeq(Iter) _Generic(Iter, \
  GTreeIter*: _GTreeIterSeq, \
  const GTreeIter*: _GTreeIterSeq, \
  GTreeIterDepth*: _GTreeIterSeq, \
  const GTreeIterDepth*: _GTreeIterSeq, \
  GTreeIterBreadth*: _GTreeIterSeq, \
  const GTreeIterBreadth*: _GTreeIterSeq, \
  GTreeIterValue*: _GTreeIterSeq, \
  const GTreeIterValue*: _GTreeIterSeq, \
  default: PBErrInvalidPolymorphism) ((GTreeIter*)(Iter))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gtree-inline.c"
#endif


#endif
