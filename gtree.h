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

// ----------- GenTree

// ================= Define ==================

// ================= Data structure ===================
struct GenTree;
typedef struct GenTree {
  // Parent node
  struct GenTree* _parent;
  // Branches
  // Branch cannot be null, if the user tries to add a null branch 
  // nothing happen
  GSetGenTree _subtrees;
  // User data
  void* _data;
} GenTree;

// ================ Functions declaration ====================

// Create a new GenTree
GenTree* GenTreeCreate(void);

// Create a new static GenTree
GenTree GenTreeCreateStatic(void);

// Create a new GenTree with user data 'data'
GenTree* GenTreeCreateData(void* const data);

// Free the memory used by the GenTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void _GenTreeFree(GenTree** that);

// Free the memory used by the static GenTree 'that'
// If 'that' is not a root node it is cut prior to be freed
// Subtrees are recursively freed
// User data must be freed by the user
void _GenTreeFreeStatic(GenTree* that);

// Get the user data of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
void* _GenTreeData(const GenTree* const that);

// Set the user data of the GenTree 'that' to 'data'
#if BUILDMODE != 0
inline
#endif
void _GenTreeSetData(GenTree* const that, void* const data);

// Get the set of subtrees of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
GSetGenTree* _GenTreeSubtrees(const GenTree* const that);

// Disconnect the GenTree 'that' from its parent
// If it has no parent, do nothing
void _GenTreeCut(GenTree* const that);

// Return true if the GenTree 'that' is a root
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GenTreeIsRoot(const GenTree* const that);

// Return true if the GenTree 'that' is a leaf
// Return false else
#if BUILDMODE != 0
inline
#endif
bool _GenTreeIsLeaf(const GenTree* const that);

// Return the parent of the GenTree 'that'
#if BUILDMODE != 0
inline
#endif
GenTree* _GenTreeParent(const GenTree* const that);

// Return the number of subtrees of the GenTree 'that' and their subtrees 
// recursively
int _GenTreeGetSize(const GenTree* const that);

// Wrapping of GSet functions
inline GenTree* _GenTreeSubtree(const GenTree* const that, const int iSubtree) {
  return GSetGet(_GenTreeSubtrees(that), iSubtree);
}
inline GenTree* _GenTreeFirstSubtree(const GenTree* const that) {
  return GSetHead(_GenTreeSubtrees(that));
}
inline GenTree* _GenTreeLastSubtree(const GenTree* const that) {
  return GSetTail(_GenTreeSubtrees(that));
}
inline GenTree* _GenTreePopSubtree(GenTree* const that) {
  return GSetPop(_GenTreeSubtrees(that));
}
inline GenTree* _GenTreeDropSubtree(GenTree* const that) {
  return GSetDrop(_GenTreeSubtrees(that));
}
inline GenTree* _GenTreeRemoveSubtree(GenTree* const that, const int iSubtree) {
  return GSetRemove((GSet*)_GenTreeSubtrees(that), iSubtree);
}

inline void _GenTreePushSubtree(GenTree* const that, GenTree* const tree) {
  if (!tree) return;
  GSetPush(_GenTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GenTreeAddSortSubTree(GenTree* const that, GenTree* const tree, 
  const float sortVal) {
  if (!tree) return;
  GSetAddSort(_GenTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GenTreeInsertSubtree(GenTree* const that, GenTree* const tree, 
  const int pos) {
  if (!tree) return;
  GSetInsert(_GenTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GenTreeAppendSubtree(GenTree* const that, GenTree* const tree) {
  if (!tree) return;
  GSetAppend(_GenTreeSubtrees(that), tree);
  tree->_parent = that;
}

inline void _GenTreePushData(GenTree* const that, void* const data) {
  GenTree* tree = GenTreeCreateData(data);
  GSetPush(_GenTreeSubtrees(that), tree);
  tree->_parent = that;
}
inline void _GenTreeAddSortData(GenTree* const that, void* const data, 
  const float sortVal) {
  GenTree* tree = GenTreeCreateData(data);
  GSetAddSort(_GenTreeSubtrees(that), tree, sortVal);
  tree->_parent = that;
}
inline void _GenTreeInsertData(GenTree* const that, void* const data, 
  const int pos) {
  GenTree* tree = GenTreeCreateData(data);
  GSetInsert(_GenTreeSubtrees(that), tree, pos);
  tree->_parent = that;
}
inline void _GenTreeAppendData(GenTree* const that, void* const data) {
  GenTree* tree = GenTreeCreateData(data);
  GSetAppend(_GenTreeSubtrees(that), tree);
  tree->_parent = that;
}

// ----------- GenTreeIter

// ================= Define ==================

// ================= Data structure ===================

typedef struct GenTreeIter {
  // Attached tree
  GenTree* _tree;
  // Current position
  GSetElem* _curPos;
  // GSet to memorize nodes sequence
  // The node sequence doesn't include the root node of the attached tree
  GSetGenTree _seq;
} GenTreeIter;

typedef struct GenTreeIterDepth {GenTreeIter _iter;} GenTreeIterDepth;
typedef struct GenTreeIterBreadth {GenTreeIter _iter;} GenTreeIterBreadth;
typedef struct GenTreeIterValue {GenTreeIter _iter;} GenTreeIterValue;

// ================ Functions declaration ====================

// Create a new GenTreeIterDepth for the GenTree 'tree'
GenTreeIterDepth* _GenTreeIterDepthCreate(GenTree* const tree);

// Create a new static GenTreeIterDepth for the GenTree 'tree'
GenTreeIterDepth _GenTreeIterDepthCreateStatic(GenTree* const tree);

// Create a new GenTreeIterBreadth for the GenTree 'tree'
GenTreeIterBreadth* _GenTreeIterBreadthCreate(GenTree* const tree);

// Create a new static GenTreeIterBreadth for the GenTree 'tree'
GenTreeIterBreadth _GenTreeIterBreadthCreateStatic(GenTree* const tree);

// Create a new GenTreeIterValue for the GenTree 'tree'
GenTreeIterValue* _GenTreeIterValueCreate(GenTree* const tree);

// Create a new static GenTreeIterValue for the GenTree 'tree'
GenTreeIterValue _GenTreeIterValueCreateStatic(GenTree* const tree);

// Update the GenTreeIterDepth 'that' in case its attached GenTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterDepthUpdate(GenTreeIterDepth* const that);

// Update the GenTreeIterBreadth 'that' in case its attached GenTree has 
// been modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterBreadthUpdate(GenTreeIterBreadth* const that);

// Update the GenTreeIterValue 'that' in case its attached GenTree has been 
// modified
// The node sequence doesn't include the root node of the attached tree
void GenTreeIterValueUpdate(GenTreeIterValue* const that);

// Free the memory used by the iterator 'that'
void _GenTreeIterFree(GenTreeIter** that);

// Free the memory used by the static iterator 'that'
void _GenTreeIterFreeStatic(GenTreeIter* const that);

// Reset the iterator 'that' at its start position
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterReset(GenTreeIter* const that);

// Reset the iterator 'that' at its end position
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterToEnd(GenTreeIter* const that);

// Step the iterator 'that' at its next position
// Return true if it could move to the next position
// Return false if it's already at the last position
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterStep(GenTreeIter* const that);

// Step back the iterator 'that' at its next position
// Return true if it could move to the previous position
// Return false if it's already at the first position
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterStepBack(GenTreeIter* const that);

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
  void(*fun)(void* const data, void* const param), void* const param);

// Return true if the iterator is at the start of the elements (from
// its point of view, not the order in the GenTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterIsFirst(const GenTreeIter* const that);

// Return true if the iterator is at the end of the elements (from
// its point of view, not the order in the GenTree)
// Return false else
#if BUILDMODE != 0
inline
#endif 
bool _GenTreeIterIsLast(const GenTreeIter* const that);

// Change the attached tree of the iterator, and reset it
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterDepthSetGenTree(GenTreeIterDepth* const that, 
  GenTree* const tree);
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterBreadthSetGenTree(GenTreeIterBreadth* const that, 
  GenTree* const tree);
#if BUILDMODE != 0
inline
#endif 
void _GenTreeIterValueSetGenTree(GenTreeIterValue* const that, 
  GenTree* const tree);

// Return the user data of the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
void* _GenTreeIterGetData(const GenTreeIter* const that);

// Return the tree currently pointed to by the iterator
#if BUILDMODE != 0
inline
#endif 
GenTree* _GenTreeIterGetGenTree(const GenTreeIter* const that);

// Return the tree associated to the iterator 'that'
#if BUILDMODE != 0
inline
#endif 
GenTree* _GenTreeIterGenTree(const GenTreeIter* const that);

// Return the sequence of the iterator
#if BUILDMODE != 0
inline
#endif 
GSetGenTree* _GenTreeIterSeq(const GenTreeIter* const that);

// ================= Typed GenTree ==================

typedef struct GenTreeStr {GenTree _tree;} GenTreeStr;
#define GenTreeStrCreate() ((GenTreeStr*)GenTreeCreate())
inline GenTreeStr GenTreeStrCreateStatic(void) 
  {GenTreeStr ret = {._tree=GenTreeCreateStatic()}; return ret;}
#define GenTreeStrCreateData(Data) ((GenTreeStr*)GenTreeCreateData(Data))
inline char* _GenTreeStrData(const GenTreeStr* const that) {
  return (char*)_GenTreeData((const GenTree* const)that);
}
inline void _GenTreeStrSetData(GenTreeStr* const that, char* const data) {
  _GenTreeSetData((GenTree* const)that, (void* const)data);
}
inline GSetGenTreeStr* _GenTreeStrSubtrees(const GenTreeStr* const that) {
  return (GSetGenTreeStr*)_GenTreeSubtrees((const GenTree* const)that);
}
inline GenTreeStr* _GenTreeStrParent(const GenTreeStr* const that) {
  return (GenTreeStr*)_GenTreeParent((const GenTree* const)that);
}
inline void _GenTreeStrPushData(GenTreeStr* const that, char* const data) {
  _GenTreePushData((GenTree* const)that, (void* const)data);
}
inline void _GenTreeStrAddSortData(GenTreeStr* const that, char* const data, 
  const float sortVal) {
  _GenTreeAddSortData((GenTree* const)that, (void* const)data, sortVal);
}
inline void _GenTreeStrInsertData(GenTreeStr* const that, char* const data, 
  const int pos) {
  _GenTreeInsertData((GenTree* const)that, (void* const)data, pos);
}
inline void _GenTreeStrAppendData(GenTreeStr* const that, char* const data) {
  _GenTreeAppendData((GenTree* const)that, (void* const)data);
}
inline GenTreeStr* _GenTreeStrSubtree(const GenTreeStr* const that, 
  const int iSubtree) {
  return (GenTreeStr*)_GenTreeSubtree((const GenTree* const)that, iSubtree);
}
inline GenTreeStr* _GenTreeStrFirstSubtree(const GenTreeStr* const that) {
  return (GenTreeStr*)_GenTreeFirstSubtree((const GenTree* const)that);
}
inline GenTreeStr* _GenTreeStrLastSubtree(const GenTreeStr* const that) {
  return (GenTreeStr*)_GenTreeLastSubtree((const GenTree* const)that);
}
inline GenTreeStr* _GenTreeStrPopSubtree(GenTreeStr* const that) {
  return (GenTreeStr*)_GenTreePopSubtree((GenTree* const)that);
}
inline GenTreeStr* _GenTreeStrDropSubtree(GenTreeStr* const that) {
  return (GenTreeStr*)_GenTreeDropSubtree((GenTree* const)that);
}
inline GenTreeStr* _GenTreeStrRemoveSubtree(GenTreeStr* const that, 
  const int iSubtree) {
  return (GenTreeStr*)_GenTreeRemoveSubtree((GenTree* const)that, iSubtree);
}
inline void _GenTreeStrPushSubtree(GenTreeStr* const that, 
  GenTreeStr* const tree) {
  _GenTreePushSubtree((GenTree* const)that, (GenTree* const)tree);
}
inline void _GenTreeStrAddSortSubTree(GenTreeStr* const that, 
  GenTreeStr* const tree, const float sortVal) {
  _GenTreeAddSortSubTree((GenTree* const)that, (GenTree* const)tree, sortVal);
}
inline void _GenTreeStrInsertSubtree(GenTreeStr* const that, 
  GenTreeStr* const tree, const int pos) {
  _GenTreeInsertSubtree((GenTree* const)that, (GenTree* const)tree, pos);
}
inline void _GenTreeStrAppendSubtree(GenTreeStr* const that, 
  GenTreeStr* const tree) {
  _GenTreeAppendSubtree((GenTree* const)that, (GenTree* const)tree);
}

// ================ Polymorphism ====================

#define GenTreeFree(RefTree) _Generic(RefTree, \
  GenTree**: _GenTreeFree, \
  GenTreeStr**: _GenTreeFree, \
  default: PBErrInvalidPolymorphism) ((GenTree**)(RefTree))

#define GenTreeFreeStatic(Tree) _Generic(Tree, \
  GenTree*: _GenTreeFreeStatic, \
  const GenTree*: _GenTreeFreeStatic, \
  GenTreeStr*: _GenTreeFreeStatic, \
  const GenTreeStr*: _GenTreeFreeStatic, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeParent(Tree) _Generic(Tree, \
  GenTree*: _GenTreeParent, \
  const GenTree*: _GenTreeParent, \
  GenTreeStr*: _GenTreeStrParent, \
  const GenTreeStr*: _GenTreeStrParent, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeSubtrees(Tree) _Generic(Tree, \
  GenTree*: _GenTreeSubtrees, \
  const GenTree*: _GenTreeSubtrees, \
  GenTreeStr*: _GenTreeStrSubtrees, \
  const GenTreeStr*: _GenTreeStrSubtrees, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeData(Tree) _Generic(Tree, \
  GenTree*: _GenTreeData, \
  const GenTree*: _GenTreeData, \
  GenTreeStr*: _GenTreeStrData, \
  const GenTreeStr*: _GenTreeStrData, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeSetData(Tree, Data) _Generic(Tree, \
  GenTree*: _GenTreeSetData, \
  GenTreeStr*: _GenTreeStrSetData, \
  default: PBErrInvalidPolymorphism) (Tree, Data)

#define GenTreeCut(Tree) _Generic(Tree, \
  GenTree*: _GenTreeCut, \
  GenTreeStr*: _GenTreeCut, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIsRoot(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIsRoot, \
  const GenTree*: _GenTreeIsRoot, \
  GenTreeStr*: _GenTreeIsRoot, \
  const GenTreeStr*: _GenTreeIsRoot, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIsLeaf(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIsLeaf, \
  const GenTree*: _GenTreeIsLeaf, \
  GenTreeStr*: _GenTreeIsLeaf, \
  const GenTreeStr*: _GenTreeIsLeaf, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeGetSize(Tree) _Generic(Tree, \
  GenTree*: _GenTreeGetSize, \
  const GenTree*: _GenTreeGetSize, \
  GenTreeStr*: _GenTreeGetSize, \
  const GenTreeStr*: _GenTreeGetSize, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreePushData(Tree, Data) _Generic(Tree, \
  GenTree*: _GenTreePushData, \
  GenTreeStr*: _GenTreeStrPushData, \
  default: PBErrInvalidPolymorphism) (Tree, Data);

#define GenTreeAddSortData(Tree, Data, SortVal) _Generic(Tree, \
  GenTree*: _GenTreeAddSortData, \
  GenTreeStr*: _GenTreeStrAddSortData, \
  default: PBErrInvalidPolymorphism) (Tree, Data, SortVal);

#define GenTreeInsertData(Tree, Data, Pos) _Generic(Tree, \
  GenTree*: _GenTreeInsertData, \
  GenTreeStr*: _GenTreeStrInsertData, \
  default: PBErrInvalidPolymorphism) (Tree, Data, Pos);

#define GenTreeAppendData(Tree, Data) _Generic(Tree, \
  GenTree*: _GenTreeAppendData, \
  GenTreeStr*: _GenTreeStrAppendData, \
  default: PBErrInvalidPolymorphism) (Tree, Data);

#define GenTreeSubtree(Tree, ISubtree) _Generic(Tree, \
  GenTree*: _GenTreeSubtree, \
  const GenTree*: _GenTreeSubtree, \
  GenTreeStr*: _GenTreeStrSubtree, \
  const GenTreeStr*: _GenTreeStrSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, ISubtree)

#define GenTreeFirstSubtree(Tree) _Generic(Tree, \
  GenTree*: _GenTreeFirstSubtree, \
  const GenTree*: _GenTreeFirstSubtree, \
  GenTreeStr*: _GenTreeStrFirstSubtree, \
  const GenTreeStr*: _GenTreeStrFirstSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeLastSubtree(Tree) _Generic(Tree, \
  GenTree*: _GenTreeLastSubtree, \
  const GenTree*: _GenTreeLastSubtree, \
  GenTreeStr*: _GenTreeStrLastSubtree, \
  const GenTreeStr*: _GenTreeStrLastSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreePopSubtree(Tree) _Generic(Tree, \
  GenTree*: _GenTreePopSubtree, \
  GenTreeStr*: _GenTreeStrPopSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeDropSubtree(Tree) _Generic(Tree, \
  GenTree*: _GenTreeDropSubtree, \
  GenTreeStr*: _GenTreeStrDropSubtree, \
  default: PBErrInvalidPolymorphism) (Tree)

#define GenTreeRemoveSubtree(Tree, ISubTree) _Generic(Tree, \
  GenTree*: _GenTreeRemoveSubtree, \
  GenTreeStr*: _GenTreeStrRemoveSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, ISubTree)

#define GenTreePushSubtree(Tree, SubTree) _Generic(Tree, \
  GenTree*: _GenTreePushSubtree, \
  GenTreeStr*: _GenTreeStrPushSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree)

#define GenTreeAddSortSubtree(Tree, SubTree, SortVal) _Generic(Tree, \
  GenTree*: _GenTreeAddSortSubtree, \
  GenTreeStr*: _GenTreeStrAddSortSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree, SortVal)

#define GenTreeInsertSubtree(Tree, SubTree, Pos) _Generic(Tree, \
  GenTree*: _GenTreeInsertSubtree, \
  GenTreeStr*: _GenTreeStrInsertSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree, Pos)

#define GenTreeAppendSubtree(Tree, SubTree) _Generic(Tree, \
  GenTree*: _GenTreeAppendSubtree, \
  GenTreeStr*: _GenTreeStrAppendSubtree, \
  default: PBErrInvalidPolymorphism) (Tree, SubTree)

#define GenTreeIterDepthCreate(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterDepthCreate, \
  const GenTree*: _GenTreeIterDepthCreate, \
  GenTreeStr*: _GenTreeIterDepthCreate, \
  const GenTreeStr*: _GenTreeIterDepthCreate, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterDepthCreateStatic(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterDepthCreateStatic, \
  const GenTree*: _GenTreeIterDepthCreateStatic, \
  GenTreeStr*: _GenTreeIterDepthCreateStatic, \
  const GenTreeStr*: _GenTreeIterDepthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterBreadthCreate(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterBreadthCreate, \
  const GenTree*: _GenTreeIterBreadthCreate, \
  GenTreeStr*: _GenTreeIterBreadthCreate, \
  const GenTreeStr*: _GenTreeIterBreadthCreate, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterBreadthCreateStatic(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterBreadthCreateStatic, \
  const GenTree*: _GenTreeIterBreadthCreateStatic, \
  GenTreeStr*: _GenTreeIterBreadthCreateStatic, \
  const GenTreeStr*: _GenTreeIterBreadthCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterValueCreate(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterValueCreate, \
  const GenTree*: _GenTreeIterValueCreate, \
  GenTreeStr*: _GenTreeIterValueCreate, \
  const GenTreeStr*: _GenTreeIterValueCreate, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterValueCreateStatic(Tree) _Generic(Tree, \
  GenTree*: _GenTreeIterValueCreateStatic, \
  const GenTree*: _GenTreeIterValueCreateStatic, \
  GenTreeStr*: _GenTreeIterValueCreateStatic, \
  const GenTreeStr*: _GenTreeIterValueCreateStatic, \
  default: PBErrInvalidPolymorphism) ((GenTree*)(Tree))

#define GenTreeIterFree(RefIter) _Generic(RefIter, \
  GenTreeIter**: _GenTreeIterFree, \
  GenTreeIterDepth**: _GenTreeIterFree, \
  GenTreeIterBreadth**: _GenTreeIterFree, \
  GenTreeIterValue**: _GenTreeIterFree, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter**)(RefIter))

#define GenTreeIterFreeStatic(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterFreeStatic, \
  GenTreeIterDepth*: _GenTreeIterFreeStatic, \
  GenTreeIterBreadth*: _GenTreeIterFreeStatic, \
  GenTreeIterValue*: _GenTreeIterFreeStatic, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterReset(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterReset, \
  GenTreeIterDepth*: _GenTreeIterReset, \
  GenTreeIterBreadth*: _GenTreeIterReset, \
  GenTreeIterValue*: _GenTreeIterReset, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterToEnd(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterToEnd, \
  GenTreeIterDepth*: _GenTreeIterToEnd, \
  GenTreeIterBreadth*: _GenTreeIterToEnd, \
  GenTreeIterValue*: _GenTreeIterToEnd, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterStep(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterStep, \
  GenTreeIterDepth*: _GenTreeIterStep, \
  GenTreeIterBreadth*: _GenTreeIterStep, \
  GenTreeIterValue*: _GenTreeIterStep, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterStepBack(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterStepBack, \
  GenTreeIterDepth*: _GenTreeIterStepBack, \
  GenTreeIterBreadth*: _GenTreeIterStepBack, \
  GenTreeIterValue*: _GenTreeIterStepBack, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterApply(Iter, Fun, Param) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterApply, \
  GenTreeIterDepth*: _GenTreeIterApply, \
  GenTreeIterBreadth*: _GenTreeIterApply, \
  GenTreeIterValue*: _GenTreeIterApply, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter), Fun, Param)

#define GenTreeIterIsFirst(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterIsFirst, \
  const GenTreeIter*: _GenTreeIterIsFirst, \
  GenTreeIterDepth*: _GenTreeIterIsFirst, \
  const GenTreeIterDepth*: _GenTreeIterIsFirst, \
  GenTreeIterBreadth*: _GenTreeIterIsFirst, \
  const GenTreeIterBreadth*: _GenTreeIterIsFirst, \
  GenTreeIterValue*: _GenTreeIterIsFirst, \
  const GenTreeIterValue*: _GenTreeIterIsFirst, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterIsLast(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterIsLast, \
  const GenTreeIter*: _GenTreeIterIsLast, \
  GenTreeIterDepth*: _GenTreeIterIsLast, \
  const GenTreeIterDepth*: _GenTreeIterIsLast, \
  GenTreeIterBreadth*: _GenTreeIterIsLast, \
  const GenTreeIterBreadth*: _GenTreeIterIsLast, \
  GenTreeIterValue*: _GenTreeIterIsLast, \
  const GenTreeIterValue*: _GenTreeIterIsLast, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterSetGenTree(Iter, Tree) _Generic(Iter, \
  GenTreeIterDepth*: _GenTreeIterDepthSetGenTree, \
  GenTreeIterBreadth*: _GenTreeIterBreadthSetGenTree, \
  GenTreeIterValue*: _GenTreeIterValueSetGenTree, \
  default: PBErrInvalidPolymorphism) (Iter, Tree)

#define GenTreeIterGetData(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterGetData, \
  const GenTreeIter*: _GenTreeIterGetData, \
  GenTreeIterDepth*: _GenTreeIterGetData, \
  const GenTreeIterDepth*: _GenTreeIterGetData, \
  GenTreeIterBreadth*: _GenTreeIterGetData, \
  const GenTreeIterBreadth*: _GenTreeIterGetData, \
  GenTreeIterValue*: _GenTreeIterGetData, \
  const GenTreeIterValue*: _GenTreeIterGetData, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterGenTree(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterGenTree, \
  const GenTreeIter*: _GenTreeIterGenTree, \
  GenTreeIterDepth*: _GenTreeIterGenTree, \
  const GenTreeIterDepth*: _GenTreeIterGenTree, \
  GenTreeIterBreadth*: _GenTreeIterGenTree, \
  const GenTreeIterBreadth*: _GenTreeIterGenTree, \
  GenTreeIterValue*: _GenTreeIterGenTree, \
  const GenTreeIterValue*: _GenTreeIterGenTree, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterGetGenTree(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterGetGenTree, \
  const GenTreeIter*: _GenTreeIterGetGenTree, \
  GenTreeIterDepth*: _GenTreeIterGetGenTree, \
  const GenTreeIterDepth*: _GenTreeIterGetGenTree, \
  GenTreeIterBreadth*: _GenTreeIterGetGenTree, \
  const GenTreeIterBreadth*: _GenTreeIterGetGenTree, \
  GenTreeIterValue*: _GenTreeIterGetGenTree, \
  const GenTreeIterValue*: _GenTreeIterGetGenTree, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

#define GenTreeIterSeq(Iter) _Generic(Iter, \
  GenTreeIter*: _GenTreeIterSeq, \
  const GenTreeIter*: _GenTreeIterSeq, \
  GenTreeIterDepth*: _GenTreeIterSeq, \
  const GenTreeIterDepth*: _GenTreeIterSeq, \
  GenTreeIterBreadth*: _GenTreeIterSeq, \
  const GenTreeIterBreadth*: _GenTreeIterSeq, \
  GenTreeIterValue*: _GenTreeIterSeq, \
  const GenTreeIterValue*: _GenTreeIterSeq, \
  default: PBErrInvalidPolymorphism) ((GenTreeIter*)(Iter))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "gtree-inline.c"
#endif


#endif
