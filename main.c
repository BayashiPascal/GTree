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

void UnitTestGenTreeCreateFree() {
  GenTree* tree = GenTreeCreate();
  if (tree == NULL ||
    tree->_parent != NULL ||
    GSetNbElem(&(tree->_subtrees)) != 0 ||
    tree->_data != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeCreate failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeFree(&tree);
  if (tree != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeFree failed");
    PBErrCatch(GenTreeErr);
  }
  int data = 1;
  tree = GenTreeCreateData(&data);
  if (tree == NULL ||
    tree->_parent != NULL ||
    GSetNbElem(&(tree->_subtrees)) != 0 ||
    tree->_data != &data) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeCreateData failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeFree(&tree);
  GenTree treeStatic = GenTreeCreateStatic();
  if (treeStatic._parent != NULL ||
    GSetNbElem(&(treeStatic._subtrees)) != 0 ||
    treeStatic._data != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeCreateStatic failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeFreeStatic(&treeStatic);
  printf("UnitTestGenTreeCreateFree OK\n");
}

void UnitTestGenTreeGetSet() {
  GenTree tree = GenTreeCreateStatic();
  int data = 1;
  tree._data = &data;
  if (GenTreeData(&tree) != &data) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeData failed");
    PBErrCatch(GenTreeErr);
  }
  int data2 = 1;
  GenTreeSetData(&tree, &data2);
  if (GenTreeData(&tree) != &data2) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeSetData failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeSubtrees(&tree) != &(tree._subtrees)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeSubTrees failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIsRoot(&tree) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIsRoot failed");
    PBErrCatch(GenTreeErr);
  }
  tree._parent = &tree;
  if (GenTreeIsRoot(&tree) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIsRoot failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeParent(&tree) != &tree) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeParent failed");
    PBErrCatch(GenTreeErr);
  }
  tree._parent = NULL;
  if (GenTreeIsLeaf(&tree) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIsLeaf failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeAppendData(&tree, &data);
  if (GenTreeIsLeaf(&tree) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIsLeaf failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeFreeStatic(&tree);
  printf("UnitTestGenTreeGetSet OK\n");
}

void UnitTestGenTreeCutGetSize() {
  GenTree tree = GenTreeCreateStatic();
  int data = 1;
  GenTreeAppendData(&tree, &data);
  GenTreeAppendData(&tree, &data);
  GenTreeAppendData(GenTreeSubtree(&tree, 1), &data);
  if (GenTreeGetSize(&tree) != 3) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeGetSize failed");
    PBErrCatch(GenTreeErr);
  }
  GenTree* cuttree = GenTreeSubtree(&tree, 1);
  GenTreeCut(cuttree);
  if (GenTreeGetSize(&tree) != 1 ||
    GenTreeGetSize(cuttree) != 1) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeCut failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeFreeStatic(&tree);
  GenTreeFree(&cuttree);
  printf("UnitTestGenTreeCutGetSize OK\n");
}

void UnitTestGenTree() {
  UnitTestGenTreeCreateFree();
  UnitTestGenTreeGetSet();
  UnitTestGenTreeCutGetSize();
  printf("UnitTestGenTree OK\n");
}

int dataExampleTree[10] = {0,1,2,3,4,5,6,7,8,9};
GenTree* GetExampleTree() {
  GenTree* tree = GenTreeCreate();
  GenTreeAddSortData(tree, dataExampleTree + 0, 0);
  GenTreeAddSortData(tree, dataExampleTree + 9, 9);
  GenTree* subtree = GenTreeSubtree(tree, 0);
  GenTreeAddSortData(subtree, dataExampleTree + 1, 1);
  GenTreeAddSortData(subtree, dataExampleTree + 2, 2);
  subtree = GenTreeSubtree(tree, 1);
  GenTreeAddSortData(subtree, dataExampleTree + 3, 3);
  GenTreeAddSortData(subtree, dataExampleTree + 4, 4);
  subtree = GenTreeSubtree(subtree, 0);
  GenTreeAddSortData(subtree, dataExampleTree + 8, 8);
  GenTreeAddSortData(subtree, dataExampleTree + 6, 6);
  subtree = GenTreeSubtree(subtree, 1);
  GenTreeAddSortData(subtree, dataExampleTree + 7, 7);
  GenTreeAddSortData(subtree, dataExampleTree + 5, 5);
  return tree;
}

void funApply(void* data, void* param) {
  printf("%d%c", *(int*)data,*(char*)param);
}

void UnitTestGenTreeIterDepth() {
  GenTree* tree = GetExampleTree();
  GenTreeIterDepth* iter = GenTreeIterDepthCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterDepthCreate failed");
    PBErrCatch(GenTreeErr);
  }
  int check[10] = {0,1,2,9,3,6,8,5,7,4};
  int iCheck = 0;
  do {
    int* data = GenTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterDepth failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(iter));
  GenTreeIterFree(&iter);
  if (iter != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterFree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterDepth iterstatic = GenTreeIterDepthCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterDepthCreateStatic failed");
    PBErrCatch(GenTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterDepth failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  check[3] = 12;
  dataExampleTree[9] = 12;
  GenTreeIterDepthUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterUpdate failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GenTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterReset failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGetGenTree(&iterstatic) != GenTreeSubtree(tree, 0)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterToEnd failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterStepBack failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGenTree(&iterstatic) != tree) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSeq failed");
    PBErrCatch(GenTreeErr);
  }
  char c = ',';
  GenTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GenTree* treeB = GenTreeCreate();
  GenTreeIterSetGenTree(&iterstatic, treeB);
  if (GenTreeIterGenTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterFreeStatic(&iterstatic);
  GenTreeFree(&tree);
  GenTreeFree(&treeB);
  printf("UnitTestGenTreeIterDepth OK\n");
}

void UnitTestGenTreeIterBreadth() {
  GenTree* tree = GetExampleTree();
  GenTreeIterBreadth* iter = GenTreeIterBreadthCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterBreadthCreate failed");
    PBErrCatch(GenTreeErr);
  }
  int check[10] = {0,9,1,2,3,4,6,8,5,7};
  int iCheck = 0;
  do {
    int* data = GenTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterBreadth failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(iter));
  GenTreeIterFree(&iter);
  if (iter != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterFree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterBreadth iterstatic = GenTreeIterBreadthCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterBreadthCreateStatic failed");
    PBErrCatch(GenTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterBreadth failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  check[1] = 12;
  dataExampleTree[9] = 12;
  GenTreeIterBreadthUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterUpdate failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GenTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterReset failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGetGenTree(&iterstatic) != GenTreeSubtree(tree, 0)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterToEnd failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterStepBack failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGenTree(&iterstatic) != tree) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSeq failed");
    PBErrCatch(GenTreeErr);
  }
  char c = ',';
  GenTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GenTree* treeB = GenTreeCreate();
  GenTreeIterSetGenTree(&iterstatic, treeB);
  if (GenTreeIterGenTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterFreeStatic(&iterstatic);
  GenTreeFree(&tree);
  GenTreeFree(&treeB);
  printf("UnitTestGenTreeIterBreadth OK\n");
}

void UnitTestGenTreeIterValue() {
  GenTree* tree = GetExampleTree();
  GenTreeIterValue* iter = GenTreeIterValueCreate(tree);
  if (iter == NULL ||
    iter->_iter._tree != tree ||
    GSetNbElem(&(iter->_iter._seq)) != 10 ||
    iter->_iter._curPos != iter->_iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterValueCreate failed");
    PBErrCatch(GenTreeErr);
  }
  int check[10] = {0,1,2,3,4,5,6,7,8,9};
  int iCheck = 0;
  do {
    int* data = GenTreeIterGetData(iter);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterValue failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(iter));
  GenTreeIterFree(&iter);
  if (iter != NULL) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterFree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterValue iterstatic = GenTreeIterValueCreateStatic(tree);
  if (iterstatic._iter._tree != tree ||
    GSetNbElem(&(iterstatic._iter._seq)) != 10 ||
    iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterValueCreateStatic failed");
    PBErrCatch(GenTreeErr);
  }
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterValue failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  check[9] = 12;
  dataExampleTree[9] = 12;
  GenTreeIterValueUpdate(&iterstatic);
  iCheck = 0;
  do {
    int* data = GenTreeIterGetData(&iterstatic);
    if (*data != check[iCheck]) {
      GenTreeErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenTreeErr->_msg, "GenTreeIterUpdate failed");
      PBErrCatch(GenTreeErr);
    }
    ++iCheck;
  } while (GenTreeIterStep(&iterstatic));
  dataExampleTree[9] = 9;
  GenTreeIterReset(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._head) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterReset failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGetGenTree(&iterstatic) != GenTreeSubtree(tree, 0)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterToEnd(&iterstatic);
  if (iterstatic._iter._curPos != iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterToEnd failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsFirst(&iterstatic) == true) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsFirst failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterIsLast(&iterstatic) == false) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterIsLast failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterStepBack(&iterstatic);
  if (iterstatic._iter._curPos->_next != 
    iterstatic._iter._seq._set._tail) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterStepBack failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterGenTree(&iterstatic) != tree) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  if (GenTreeIterSeq(&iterstatic) != &(iterstatic._iter._seq)) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSeq failed");
    PBErrCatch(GenTreeErr);
  }
  char c = ',';
  GenTreeIterApply(&iterstatic, &funApply, &c);
  printf("\n");
  GenTree* treeB = GenTreeCreate();
  GenTreeIterSetGenTree(&iterstatic, treeB);
  if (GenTreeIterGenTree(&iterstatic) != treeB ||
    GSetNbElem(&(iterstatic._iter._seq)) != 0) {
    GenTreeErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenTreeErr->_msg, "GenTreeIterSetGenTree failed");
    PBErrCatch(GenTreeErr);
  }
  GenTreeIterFreeStatic(&iterstatic);
  GenTreeFree(&tree);
  GenTreeFree(&treeB);
  printf("UnitTestGenTreeIterValue OK\n");
}

void UnitTestGenTreeIter() {
  UnitTestGenTreeIterDepth();
  UnitTestGenTreeIterBreadth();
  UnitTestGenTreeIterValue();
  printf("UnitTestGenTreeIter OK\n");
}

void UnitTestAll() {
  UnitTestGenTree();
  UnitTestGenTreeIter();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();
  // Return success code
  return 0;
}

