#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "pberr.h"
#include "gtree.h"

#define RANDOMSEED 0

void UnitTestGTreeCreateFree() {
  GTree* tree = GTreeCreate();
  if (tree == NULL ||
    tree->_parent != NULL ||
    GSetNbElem(&(tree->_subtrees)) != 0 ||
    tree->_data != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeCreate failed");
    PBErrCatch(GTreeErr);
  }
  GTreeFree(&tree);
  if (tree != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeFree failed");
    PBErrCatch(GTreeErr);
  }
  int data = 1;
  tree = GTreeCreateData(&data);
  if (tree == NULL ||
    tree->_parent != NULL ||
    GSetNbElem(&(tree->_subtrees)) != 0 ||
    tree->_data != &data) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeCreateData failed");
    PBErrCatch(GTreeErr);
  }
  GTreeFree(&tree);
  GTree treeStatic = GTreeCreateStatic();
  if (treeStatic._parent != NULL ||
    GSetNbElem(&(treeStatic._subtrees)) != 0 ||
    treeStatic._data != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeCreateStatic failed");
    PBErrCatch(GTreeErr);
  }
  GTreeFreeStatic(&treeStatic);
  printf("UnitTestGTreeCreateFree OK\n");
}

void UnitTestGTreeGetSet() {
  GTree tree = GTreeCreateStatic();
  int data = 1;
  tree._data = &data;
  if (GTreeData(&tree) != &data) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeData failed");
    PBErrCatch(GTreeErr);
  }
  int data2 = 1;
  GTreeSetData(&tree, &data2);
  if (GTreeData(&tree) != &data2) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeSetData failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeSubtrees(&tree) != &(tree._subtrees)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeSubTrees failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIsRoot(&tree) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIsRoot failed");
    PBErrCatch(GTreeErr);
  }
  tree._parent = &tree;
  if (GTreeIsRoot(&tree) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIsRoot failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeParent(&tree) != &tree) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeParent failed");
    PBErrCatch(GTreeErr);
  }
  tree._parent = NULL;
  if (GTreeIsLeaf(&tree) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIsLeaf failed");
    PBErrCatch(GTreeErr);
  }
  GTreeAppendData(&tree, &data);
  if (GTreeIsLeaf(&tree) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIsLeaf failed");
    PBErrCatch(GTreeErr);
  }
  GTreeFreeStatic(&tree);
  printf("UnitTestGTreeGetSet OK\n");
}

void UnitTestGTreeCutGetSize() {
  GTree tree = GTreeCreateStatic();
  int data = 1;
  GTreeAppendData(&tree, &data);
  GTreeAppendData(&tree, &data);
  GTreeAppendData(GTreeSubtree(&tree, 1), &data);
  if (GTreeGetSize(&tree) != 3) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeGetSize failed");
    PBErrCatch(GTreeErr);
  }
  GTree* cuttree = GTreeSubtree(&tree, 1);
  GTreeCut(cuttree);
  if (GTreeGetSize(&tree) != 1 ||
    GTreeGetSize(cuttree) != 1) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeCut failed");
    PBErrCatch(GTreeErr);
  }
  GTreeFreeStatic(&tree);
  GTreeFree(&cuttree);
  printf("UnitTestGTreeCutGetSize OK\n");
}

void UnitTestGTree() {
  UnitTestGTreeCreateFree();
  UnitTestGTreeGetSet();
  UnitTestGTreeCutGetSize();
  printf("UnitTestGTree OK\n");
}

int dataExampleTree[10] = {0,1,2,3,4,5,6,7,8,9};
GTree* GetExampleTree() {
  GTree* tree = GTreeCreate();
  GTreeAddSortData(tree, dataExampleTree + 0, 0);
  GTreeAddSortData(tree, dataExampleTree + 9, 9);
  GTree* subtree = GTreeSubtree(tree, 0);
  GTreeAddSortData(subtree, dataExampleTree + 1, 1);
  GTreeAddSortData(subtree, dataExampleTree + 2, 2);
  subtree = GTreeSubtree(tree, 1);
  GTreeAddSortData(subtree, dataExampleTree + 3, 3);
  GTreeAddSortData(subtree, dataExampleTree + 4, 4);
  subtree = GTreeSubtree(subtree, 0);
  GTreeAddSortData(subtree, dataExampleTree + 8, 8);
  GTreeAddSortData(subtree, dataExampleTree + 6, 6);
  subtree = GTreeSubtree(subtree, 1);
  GTreeAddSortData(subtree, dataExampleTree + 7, 7);
  GTreeAddSortData(subtree, dataExampleTree + 5, 5);
  return tree;
}

void funApply(void* data, void* param) {
  printf("%d%c", *(int*)data,*(char*)param);
}

void UnitTestGTreeIterDepth() {
  GTree* tree = GetExampleTree();
  GTreeIterDepth* iter = GTreeIterDepthCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterDepthCreate failed");
    PBErrCatch(GTreeErr);
  }
  int check[10] = {0,1,2,9,3,6,8,5,7,4};
  int iCheck = 0;
  do {
    int* data = GTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterDepth failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(iter));
  GTreeIterFree(&iter);
  if (iter != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterFree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterDepth iterstatic = GTreeIterDepthCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterDepthCreateStatic failed");
    PBErrCatch(GTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterDepth failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  check[3] = 12;
  dataExampleTree[9] = 12;
  GTreeIterDepthUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterUpdate failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterReset failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGetGTree(&iterstatic) != GTreeSubtree(tree, 0)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterToEnd failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterStepBack failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGTree(&iterstatic) != tree) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGTree failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSeq failed");
    PBErrCatch(GTreeErr);
  }
  char c = ',';
  GTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GTree* treeB = GTreeCreate();
  GTreeIterSetGTree(&iterstatic, treeB);
  if (GTreeIterGTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterFreeStatic(&iterstatic);
  GTreeFree(&tree);
  GTreeFree(&treeB);
  printf("UnitTestGTreeIterDepth OK\n");
}

void UnitTestGTreeIterBreadth() {
  GTree* tree = GetExampleTree();
  GTreeIterBreadth* iter = GTreeIterBreadthCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterBreadthCreate failed");
    PBErrCatch(GTreeErr);
  }
  int check[10] = {0,9,1,2,3,4,6,8,5,7};
  int iCheck = 0;
  do {
    int* data = GTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterBreadth failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(iter));
  GTreeIterFree(&iter);
  if (iter != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterFree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterBreadth iterstatic = GTreeIterBreadthCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterBreadthCreateStatic failed");
    PBErrCatch(GTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterBreadth failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  check[1] = 12;
  dataExampleTree[9] = 12;
  GTreeIterBreadthUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterUpdate failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterReset failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGetGTree(&iterstatic) != GTreeSubtree(tree, 0)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterToEnd failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterStepBack failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGTree(&iterstatic) != tree) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGTree failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSeq failed");
    PBErrCatch(GTreeErr);
  }
  char c = ',';
  GTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GTree* treeB = GTreeCreate();
  GTreeIterSetGTree(&iterstatic, treeB);
  if (GTreeIterGTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterFreeStatic(&iterstatic);
  GTreeFree(&tree);
  GTreeFree(&treeB);
  printf("UnitTestGTreeIterBreadth OK\n");
}

void UnitTestGTreeIterValue() {
  GTree* tree = GetExampleTree();
  GTreeIterValue* iter = GTreeIterValueCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterValueCreate failed");
    PBErrCatch(GTreeErr);
  }
  int check[10] = {0,1,2,3,4,5,6,7,8,9};
  int iCheck = 0;
  do {
    int* data = GTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterValue failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(iter));
  GTreeIterFree(&iter);
  if (iter != NULL) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterFree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterValue iterstatic = GTreeIterValueCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterValueCreateStatic failed");
    PBErrCatch(GTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterValue failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  check[9] = 12;
  dataExampleTree[9] = 12;
  GTreeIterValueUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GTreeErr->_msg, "GTreeIterUpdate failed");
      PBErrCatch(GTreeErr);
    }
    ++iCheck;
  } while (GTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterReset failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGetGTree(&iterstatic) != GTreeSubtree(tree, 0)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterToEnd failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsFirst(&iterstatic) == true) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsFirst failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterIsLast(&iterstatic) == false) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterIsLast failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterStepBack failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterGTree(&iterstatic) != tree) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterGTree failed");
    PBErrCatch(GTreeErr);
  }
  if (GTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSeq failed");
    PBErrCatch(GTreeErr);
  }
  char c = ',';
  GTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GTree* treeB = GTreeCreate();
  GTreeIterSetGTree(&iterstatic, treeB);
  if (GTreeIterGTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GTreeErr->_msg, "GTreeIterSetGTree failed");
    PBErrCatch(GTreeErr);
  }
  GTreeIterFreeStatic(&iterstatic);
  GTreeFree(&tree);
  GTreeFree(&treeB);
  printf("UnitTestGTreeIterValue OK\n");
}

void UnitTestGTreeIter() {
  UnitTestGTreeIterDepth();
  UnitTestGTreeIterBreadth();
  UnitTestGTreeIterValue();
  printf("UnitTestGTreeIter OK\n");
}

void UnitTestAll() {
  UnitTestGTree();
  UnitTestGTreeIter();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();
  // Return success code
  return 0;
}

