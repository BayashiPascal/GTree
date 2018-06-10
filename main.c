#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "genbrush.h"

#define RANDOMSEED 0



void UnitTestGBPixelBlendNormal() {
  GBPixel pixA;
  GBPixel pixB;
  pixA = (GBPixel){._rgba[GBPixelRed]=100, ._rgba[GBPixelGreen]=0, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=100};
  pixB = (GBPixel){._rgba[GBPixelRed]=0, ._rgba[GBPixelGreen]=100, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=100};
  GBPixelBlendNormal(&pixA, &pixB);
  if (pixA._rgba[GBPixelRed] != 50 ||
    pixA._rgba[GBPixelGreen] != 50 ||
    pixA._rgba[GBPixelBlue] != 0 ||
    pixA._rgba[GBPixelAlpha] != 200) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPixelBlendNormal failed");
    PBErrCatch(GenBrushErr);
  }
  pixA = (GBPixel){._rgba[GBPixelRed]=100, ._rgba[GBPixelGreen]=0, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=255};
  pixB = (GBPixel){._rgba[GBPixelRed]=0, ._rgba[GBPixelGreen]=100, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=255};
  GBPixelBlendNormal(&pixA, &pixB);
  if (pixA._rgba[GBPixelRed] != 50 ||
    pixA._rgba[GBPixelGreen] != 50 ||
    pixA._rgba[GBPixelBlue] != 0 ||
    pixA._rgba[GBPixelAlpha] != 255) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPixelBlendNormal failed");
    PBErrCatch(GenBrushErr);
  }
  pixA = (GBPixel){._rgba[GBPixelRed]=100, ._rgba[GBPixelGreen]=0, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=255};
  pixB = (GBPixel){._rgba[GBPixelRed]=0, ._rgba[GBPixelGreen]=100, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=25};
  GBPixelBlendNormal(&pixA, &pixB);
  if (pixA._rgba[GBPixelRed] != 5 ||
    pixA._rgba[GBPixelGreen] != 95 ||
    pixA._rgba[GBPixelBlue] != 0 ||
    pixA._rgba[GBPixelAlpha] != 255) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPixelBlendNormal failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBPixelBlendNormal OK\n");
}

void UnitTestGBPixelBlendOver() {
  GBPixel pixA;
  GBPixel pixB;
  pixA = (GBPixel){._rgba[GBPixelRed]=100, ._rgba[GBPixelGreen]=0, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=100};
  pixB = (GBPixel){._rgba[GBPixelRed]=0, ._rgba[GBPixelGreen]=100, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=25};
  GBPixelBlendOver(&pixA, &pixB);
  if (pixA._rgba[GBPixelRed] != 61 ||
    pixA._rgba[GBPixelGreen] != 39 ||
    pixA._rgba[GBPixelBlue] != 0 ||
    pixA._rgba[GBPixelAlpha] != 125) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPixelBlendOver failed");
    PBErrCatch(GenBrushErr);
  }
  pixA = (GBPixel){._rgba[GBPixelRed]=100, ._rgba[GBPixelGreen]=0, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=255};
  pixB = (GBPixel){._rgba[GBPixelRed]=0, ._rgba[GBPixelGreen]=100, 
    ._rgba[GBPixelBlue]=0, ._rgba[GBPixelAlpha]=255};
  GBPixelBlendOver(&pixA, &pixB);
  if (pixA._rgba[GBPixelRed] != 0 ||
    pixA._rgba[GBPixelGreen] != 100 ||
    pixA._rgba[GBPixelBlue] != 0 ||
    pixA._rgba[GBPixelAlpha] != 255) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPixelBlendOver failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBPixelBlendOver OK\n");
}

void UnitTestGBPixel() {
  UnitTestGBPixelBlendNormal();
  UnitTestGBPixelBlendOver();
  printf("UnitTestGBPixel OK\n");
}

void UnitTestGBLayerCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBLayer* layer = GBLayerCreate(&dim);
  VecShort2D v = VecShortCreateStatic2D();
  if (VecIsEqual(&(layer->_pos), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(&(layer->_prevPos), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(&(layer->_dim), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (layer->_pix == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (layer->_blendMode != GBLayerBlendModeDefault) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (layer->_modified == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (layer->_stackPos != GBLayerStackPosBg) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerFree(&layer);
  printf("UnitTestGBLayerCreateFree OK\n");
}

void UnitTestGBLayerArea() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBLayer* layer = GBLayerCreate(&dim);
  if (GBLayerArea(layer) != 12) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerArea failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerFree(&layer);
  printf("UnitTestGBLayerArea OK\n");
}

void UnitTestGBLayerGetSet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBLayer* layer = GBLayerCreate(&dim);
  if (GBLayerPos(layer) != &(layer->_pos)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPos failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D p = VecShortCreateStatic2D();
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  GBLayerSetPos(layer, &p);
  if (VecIsEqual(GBLayerPos(layer), &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetPos failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 0); VecSet(&p, 1, 0); 
  if (VecIsEqual(&(layer->_prevPos), &p) == false || 
    layer->_modified == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetPos failed");
    PBErrCatch(GenBrushErr);
  }
  layer->_modified = false;
  VecSet(&p, 0, 3); VecSet(&p, 1, 4); 
  GBLayerSetPos(layer, &p);
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  if (VecIsEqual(&(layer->_prevPos), &p) == false || 
    layer->_modified == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetPos failed");
    PBErrCatch(GenBrushErr);
  }
  p = GBLayerGetPos(layer);
  if (VecIsEqual(GBLayerPos(layer), &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetPos failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerPrevPos(layer) != &(layer->_prevPos)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPrevPos failed");
    PBErrCatch(GenBrushErr);
  }
  p = GBLayerGetPrevPos(layer);
  if (VecIsEqual(GBLayerPrevPos(layer), &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetPrevPos failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerDim(layer) != &(layer->_dim)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerDim failed");
    PBErrCatch(GenBrushErr);
  }
  p = GBLayerGetDim(layer);
  if (VecIsEqual(GBLayerDim(layer), &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetDim failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerGetBlendMode(layer) != layer->_blendMode) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBlendMode failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerSetBlendMode(layer, GBLayerBlendModeNormal);
  if (GBLayerGetBlendMode(layer) != GBLayerBlendModeNormal) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetBlendMode failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerIsModified(layer) != true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerIsModified failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerSetModified(layer, false);
  if (GBLayerIsModified(layer) != false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetModified failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerGetStackPos(layer) != GBLayerStackPosBg) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetStackPos failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerSetStackPos(layer, GBLayerStackPosFg);
  if (GBLayerGetStackPos(layer) != GBLayerStackPosFg ||
    GBLayerIsModified(layer) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerSetStackPos failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerPixels(layer) != layer->_pix) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPixels failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, -1); VecSet(&p, 1, 2); 
  if (GBLayerPixelSafe(layer, &p) != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  if (GBLayerPixel(layer, &p) != layer->_pix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPixel failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerPixelSafe(layer, &p) != layer->_pix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel pix = GBColorWhite;
  float depth = 1.0;
  GBLayerAddPixel(layer, &p, &pix, depth);
  if (GSetNbElem(GBLayerPixel(layer, &p)) != 1) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerAddPixel failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, -1); VecSet(&p, 1, 2);
  GBLayerAddPixelSafe(layer, &p, &pix, depth);
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  GBLayerAddPixelSafe(layer, &p, &pix, depth);
  if (GSetNbElem(GBLayerPixel(layer, &p)) != 2) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerAddPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayerIsPosInside(layer, &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 10); VecSet(&p, 1, 2); 
  if (GBLayerIsPosInside(layer, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, -2); 
  if (GBLayerIsPosInside(layer, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerFlush(layer);
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  if (GSetNbElem(GBLayerPixel(layer, &p)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerFlush failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerFree(&layer);
  printf("UnitTestGBLayerGetSet OK\n");
}

void UnitTestGBLayerCreateFromFile() {
  GBLayer* layer = GBLayerCreateFromFile("./testBottomLeft.tga");
  if (layer == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 4); 
  if (VecIsEqual(&dim, GBLayerDim(layer)) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  unsigned char check[48] = {
    91,0,163,192, 52,0,202,194, 23,0,231,205, 
    153,0,102,200, 106,0,148,192, 64,0,190,193, 
    211,0,43,221, 168,0,86,204, 121,0,133,193, 
    255,0,0,255, 226,0,28,230, 184,0,70,209
  };
  for (int iPix = 0; iPix < 12; iPix++) {
    GBPixel pix = 
      ((GBStackedPixel*)GSetGet(layer->_pix + iPix, 0))->_val; 
    if (pix._rgba[GBPixelRed] != check[4 * iPix] ||
      pix._rgba[GBPixelGreen] != check[4 * iPix + 1] ||
      pix._rgba[GBPixelBlue] != check[4 * iPix + 2] ||
      pix._rgba[GBPixelAlpha] != check[4 * iPix + 3]) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile1 failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBLayerFree(&layer);
  layer = GBLayerCreateFromFile("./testTopLeft.tga");
  if (layer == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(&dim, GBLayerDim(layer)) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  for (int iPix = 0; iPix < 12; iPix++) {
    GBPixel pix = 
      ((GBStackedPixel*)GSetGet(layer->_pix + iPix, 0))->_val; 
    if (pix._rgba[GBPixelRed] != check[4 * iPix] ||
      pix._rgba[GBPixelGreen] != check[4 * iPix + 1] ||
      pix._rgba[GBPixelBlue] != check[4 * iPix + 2] ||
      pix._rgba[GBPixelAlpha] != check[4 * iPix + 3]) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBLayerCreateFromFile2 failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBLayerFree(&layer);
  printf("UnitTestGBLayerCreateFromFile OK\n");
}

void UnitTestGBLayerGetBoundaryInSurface() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  VecSet(&dim, 0, 200); VecSet(&dim, 1, 100); 
  GBLayer* layer = GBLayerCreate(&dim);
  VecShort2D pos = VecShortCreateStatic2D();
  VecSet(&pos, 0, 10); VecSet(&pos, 1, 10); 
  GBLayerSetPos(layer, &pos);
  Facoid* bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  VecFloat2D p = VecFloatCreateStatic2D();
  VecFloat2D u = VecFloatCreateStatic2D();
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&p, 0, 10); VecSet(&p, 1, 10); 
  VecSet(&u, 0, 200); VecSet(&u, 1, 0); 
  VecSet(&v, 0, 0); VecSet(&v, 1, 100); 
  if (VecIsEqual(ShapoidPos(bound), &p) == false ||
    VecIsEqual(ShapoidAxis(bound, 0), &u) == false ||
    VecIsEqual(ShapoidAxis(bound, 1), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&bound);
  VecSet(&pos, 0, 700); VecSet(&pos, 1, 10); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  VecSet(&p, 0, 700); VecSet(&p, 1, 10); 
  VecSet(&u, 0, 100); VecSet(&u, 1, 0); 
  VecSet(&v, 0, 0); VecSet(&v, 1, 100); 
  if (VecIsEqual(ShapoidPos(bound), &p) == false ||
    VecIsEqual(ShapoidAxis(bound, 0), &u) == false ||
    VecIsEqual(ShapoidAxis(bound, 1), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&bound);
  VecSet(&pos, 0, -100); VecSet(&pos, 1, 10); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  VecSet(&p, 0, 0); VecSet(&p, 1, 10); 
  VecSet(&u, 0, 100); VecSet(&u, 1, 0); 
  VecSet(&v, 0, 0); VecSet(&v, 1, 100); 
  if (VecIsEqual(ShapoidPos(bound), &p) == false ||
    VecIsEqual(ShapoidAxis(bound, 0), &u) == false ||
    VecIsEqual(ShapoidAxis(bound, 1), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&bound);
  VecSet(&pos, 0, 10); VecSet(&pos, 1, 550); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  VecSet(&p, 0, 10); VecSet(&p, 1, 550); 
  VecSet(&u, 0, 200); VecSet(&u, 1, 0); 
  VecSet(&v, 0, 0); VecSet(&v, 1, 50); 
  if (VecIsEqual(ShapoidPos(bound), &p) == false ||
    VecIsEqual(ShapoidAxis(bound, 0), &u) == false ||
    VecIsEqual(ShapoidAxis(bound, 1), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&bound);
  VecSet(&pos, 0, 10); VecSet(&pos, 1, -50); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  VecSet(&p, 0, 10); VecSet(&p, 1, 0); 
  VecSet(&u, 0, 200); VecSet(&u, 1, 0); 
  VecSet(&v, 0, 0); VecSet(&v, 1, 50); 
  if (VecIsEqual(ShapoidPos(bound), &p) == false ||
    VecIsEqual(ShapoidAxis(bound, 0), &u) == false ||
    VecIsEqual(ShapoidAxis(bound, 1), &v) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&bound);
  VecSet(&pos, 0, -300); VecSet(&pos, 1, -150); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  if (bound != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&pos, 0, 1000); VecSet(&pos, 1, 1000); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  if (bound != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&pos, 0, 0); VecSet(&pos, 1, 1000); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  if (bound != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&pos, 0, 1000); VecSet(&pos, 1, 0); 
  GBLayerSetPos(layer, &pos);
  bound = GBLayerGetBoundaryInSurface(layer, surf, false);
  if (bound != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBLayerGetBoundaryInSurface failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayerFree(&layer);
  GBSurfaceFree(&surf);
  printf("UnitTestGBLayerGetBoundaryInSurface OK\n");
}

void UnitTestGBLayer() {
  UnitTestGBLayerCreateFree();
  UnitTestGBLayerArea();
  UnitTestGBLayerGetSet();
  UnitTestGBLayerCreateFromFile();
  UnitTestGBLayerGetBoundaryInSurface();
  
  printf("UnitTestGBLayer OK\n");
}

void UnitTestGBPostProcessingCreateFree() {
  GBPostProcessing pp = 
    GBPostProcessingCreateStatic(GBPPTypeNormalizeHue);
  if (pp._type != GBPPTypeNormalizeHue) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPostProcessingCreateStatic failed");
    PBErrCatch(GenBrushErr);
  }
  GBPostProcessing* pp2 = 
    GBPostProcessingCreate(GBPPTypeNormalizeHue);
  if (pp2->_type != GBPPTypeNormalizeHue) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPostProcessingCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBPostProcessingFree(&pp2);
  if (pp2 != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPostProcessingFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBPostProcessingCreateFree OK\n");
}

void UnitTestGBPostProcessingGetSet() {
  GBPostProcessing pp = 
    GBPostProcessingCreateStatic(GBPPTypeNormalizeHue);
  if (GBPostProcessingGetType(&pp) != GBPPTypeNormalizeHue) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBPostProcessingGetType failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBPostProcessingGetSet OK\n");
}

void UnitTestGBPostProcessing() {
  UnitTestGBPostProcessingCreateFree();
  UnitTestGBPostProcessingGetSet();
  
  printf("UnitTestGBPostProcessing OK\n");
}

void UnitTestGBSurfaceCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  if (surf->_type != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(&(surf->_dim), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel white = GBColorWhite;
  if (memcmp(&(surf->_bgColor), &white, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (surf->_finalPix == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (GSetNbElem(&(surf->_layers)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFree(&surf);
  printf("UnitTestGBSurfaceCreateFree OK\n");
}

void UnitTestGBSurfaceGetSet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  if (GBSurfaceGetType(&surf) != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceGetType failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D d = GBSurfaceGetDim(&surf);
  if (VecIsEqual(&d, &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceGetDim failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBSurfaceDim(&surf), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceDim failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceFinalPixels(&surf) != surf._finalPix) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceFinalPix failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel black = GBColorBlack;
  GBSurfaceSetBgColor(&surf, &black);
  if (memcmp(&(surf._bgColor), &black, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceSetBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  if (memcmp(GBSurfaceBgColor(&surf), &black, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel bgCol = GBSurfaceGetBgColor(&surf);
  if (memcmp(&(surf._bgColor), &bgCol, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceGetBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D p = VecShortCreateStatic2D();
  VecSet(&p, 0, 1); VecSet(&p, 1, 2);
  if (GBSurfaceFinalPixel(&surf, &p) != surf._finalPix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceFinalPixelSafe(&surf, &p) != surf._finalPix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel white = GBColorWhite;
  GBSurfaceSetFinalPixel(&surf, &p, &white);
  if (memcmp(GBSurfaceFinalPixel(&surf, &p), &white, 
    sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceSetFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel pix = GBSurfaceGetFinalPixel(&surf, &p);
  if (memcmp(&pix, &white, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceGetFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceIsPosInside(&surf, &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, -1); VecSet(&p, 1, 2);
  if (GBSurfaceIsPosInside(&surf, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel transparent = GBColorTransparent;
  pix = GBSurfaceGetFinalPixelSafe(&surf, &p);
  if (memcmp(&pix, &transparent, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceGetFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceFinalPixelSafe(&surf, &p) != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, 10);
  if (GBSurfaceIsPosInside(&surf, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceSetFinalPixelSafe(&surf, &p, &white);
  VecSet(&p, 0, 2); VecSet(&p, 1, 1);
  GBPixel blue = GBColorBlue;
  GBSurfaceSetFinalPixelSafe(&surf, &p, &blue);
  if (memcmp(GBSurfaceFinalPixel(&surf, &p), &blue, 
    sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceSetFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceLayers(&surf) != &(surf._layers)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceLayers failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceGetSet OK\n");
}

void UnitTestGBSurfaceArea() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  if (GBSurfaceArea(&surf) != 12) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceArea failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceArea OK\n");
}

void UnitTestGBSurfaceClone() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBSurface clone = GBSurfaceClone(&surf);
  if (GBSurfaceGetType(&surf) != GBSurfaceGetType(&clone)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceClone failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBSurfaceDim(&surf), GBSurfaceDim(&clone)) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceClone failed");
    PBErrCatch(GenBrushErr);
  }
  if (memcmp(&(surf._bgColor), &(clone._bgColor), 
    sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceClone failed");
    PBErrCatch(GenBrushErr);
  }
  if (surf._finalPix == clone._finalPix) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceClone failed");
    PBErrCatch(GenBrushErr);
  }
  if (memcmp(surf._finalPix, clone._finalPix, 
    sizeof(GBPixel) * GBSurfaceArea(&surf)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceClone failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFreeStatic(&surf);
  GBSurfaceFreeStatic(&clone);
  printf("UnitTestGBSurfaceClone OK\n");
}

void UnitTestGBSurfaceAddRemoveLayer() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBLayer* layerA = GBSurfaceAddLayer(&surf, &dim);
  if (layerA == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  if (GSetNbElem(GBSurfaceLayers(&surf)) != 1) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBLayerDim(layerA), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayer* layerB = GBSurfaceAddLayer(&surf, &dim);
  GBSurfaceRemoveLayer(&surf, layerA);
  if ((GBLayer*)(surf._layers._head->_data) != layerB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceRemoveLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceAddRemoveLayer OK\n");
}

void UnitTestGBSurfaceGetLayerNbLayer() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBLayer* layers[3] = {NULL};
  for (int iLayer = 0; iLayer< 3; ++iLayer)
    layers[iLayer] = GBSurfaceAddLayer(&surf, &dim);
  if (GBSurfaceNbLayer(&surf) != 3) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceNbLayer failed");
    PBErrCatch(GenBrushErr);
  }
  for (int iLayer = 0; iLayer< 3; ++iLayer) {
    if (GBSurfaceGetLayer(&surf, iLayer) != layers[iLayer]) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBSurfaceGetLayer failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceGetLayer OK\n");
}

void UnitTestGBSurfaceSetLayersModified() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBLayer* layers[3] = {NULL};
  for (int iLayer = 0; iLayer< 3; ++iLayer)
    layers[iLayer] = GBSurfaceAddLayer(&surf, &dim);
  GBSurfaceSetLayersModified(&surf, false);
  for (int iLayer = 0; iLayer< 3; ++iLayer) {
    if (GBLayerIsModified(layers[iLayer]) != false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBSurfaceSetLayersModified failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBSurfaceSetLayersModified(&surf, true);
  for (int iLayer = 0; iLayer< 3; ++iLayer) {
    if (GBLayerIsModified(layers[iLayer]) != true) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBSurfaceSetLayersModified failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceSetLayersModified OK\n");
}

void UnitTestGBSurfaceSetLayerPos() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBLayer* layers[3] = {NULL};
  for (int iLayer = 0; iLayer< 3; ++iLayer)
    layers[iLayer] = GBSurfaceAddLayer(&surf, &dim);
  GBSurfaceSetLayerPos(&surf, layers[2], 0);
  GBSurfaceSetLayerPos(&surf, layers[0], 2);
  if (GBSurfaceGetLayer(&surf, 0) != layers[2] ||
    GBSurfaceGetLayer(&surf, 1) != layers[1] ||
    GBSurfaceGetLayer(&surf, 2) != layers[0] ||
    GBLayerIsModified(layers[0]) != true ||
    GBLayerIsModified(layers[1]) != true ||
    GBLayerIsModified(layers[2]) != true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceSetLayerPos failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceSetLayerPos OK\n");
}

void UnitTestGBSurfaceGetModifiedArea() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 100); VecSet(&dim, 1, 100); 
  GBSurface surf = GBSurfaceCreateStatic(GBSurfaceTypeImage, &dim);
  GBLayer* layers[4] = {NULL};
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  for (int iLayer = 0; iLayer < 4; ++iLayer)
    layers[iLayer] = GBSurfaceAddLayer(&surf, &dim);
  VecShort2D pos = VecShortCreateStatic2D();
  VecSet(&pos, 0, -2); VecSet(&pos, 1, 5); 
  GBLayerSetPos(layers[0], &pos);
  VecSet(&pos, 0, 5); VecSet(&pos, 1, 5); 
  GBLayerSetPos(layers[1], &pos);
  VecSet(&pos, 0, 10); VecSet(&pos, 1, 8); 
  GBLayerSetPos(layers[2], &pos);
  VecSet(&pos, 0, 20); VecSet(&pos, 1, 20); 
  GBLayerSetPos(layers[3], &pos);
  GBLayerSetModified(layers[3], false);
  GSetShapoid* set = GBSurfaceGetModifiedArea(&surf);
  if (GSetNbElem(set) != 5) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, 
      "GBSurfaceGetModifiedArea failed");
    PBErrCatch(ShapoidErr);
  }
  int iCheck = 0;
  float checkp[10] = {
      0.0, 5.0, 0.0, 0.0, 8.0, 5.0, 10.0, 15.0, 15.0, 8.0};
  float checku[5] = {8.0, 10.0, 7.0, 10.0, 5.0};
  float checkv[5] = {10.0, 5.0, 10.0, 3.0, 7.0};
  VecFloat2D p = VecFloatCreateStatic2D();
  VecFloat2D u = VecFloatCreateStatic2D();
  VecFloat2D v = VecFloatCreateStatic2D();
  do {
    Facoid* fac = (Facoid*)GSetPop(set);
    VecSet(&p, 0, checkp[2 * iCheck]); 
    VecSet(&p, 1, checkp[2 * iCheck + 1]); 
    VecSet(&u, 0, checku[iCheck]); VecSet(&v, 1, checkv[iCheck]); 
    if (VecIsEqual(ShapoidPos(fac), &p) == false ||
      VecIsEqual(ShapoidAxis(fac, 0), &u) == false ||
      VecIsEqual(ShapoidAxis(fac, 1), &v) == false) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, 
        "GBSurfaceGetModifiedArea failed");
      PBErrCatch(ShapoidErr);
    }
    ShapoidFree(&fac);
    ++iCheck;
  } while(GSetNbElem(set) > 0);
  GSetFree(&set);
  GBSurfaceFreeStatic(&surf);
  printf("UnitTestGBSurfaceGetModifiedArea OK\n");
}

void UnitTestGBSurfaceUpdate() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  GBLayer* layers[4] = {NULL};
  VecSet(&dim, 0, 5); VecSet(&dim, 1, 5); 
  for (int iLayer = 0; iLayer < 4; ++iLayer) {
    layers[iLayer] = GBSurfaceAddLayer(surf, &dim);
    GBLayerSetBlendMode(layers[iLayer], GBLayerBlendModeOver);
  }
  GBLayerSetStackPos(layers[1], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[2], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[3], GBLayerStackPosFg);
  VecShort2D pos = VecShortCreateStatic2D();
  VecSet(&pos, 0, 1); VecSet(&pos, 1, 1); 
  GBLayerSetPos(layers[0], &pos);
  VecSet(&pos, 0, 3); VecSet(&pos, 1, 3); 
  GBLayerSetPos(layers[1], &pos);
  VecSet(&pos, 0, 4); VecSet(&pos, 1, 4); 
  GBLayerSetPos(layers[2], &pos);
  VecSet(&pos, 0, 7); VecSet(&pos, 1, 7); 
  GBLayerSetPos(layers[3], &pos);
  VecSetNull(&pos);
  GBPixel col;
  float depth;
  do {
    col = GBColorGreen;
    depth = 0.0;
    GBLayerAddPixel(layers[0], &pos, &col, depth);
    col._rgba[GBPixelRed] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = 0;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 1) * 30;
    depth = VecGet(&pos, 0);
    GBLayerAddPixel(layers[1], &pos, &col, depth);
    col._rgba[GBPixelRed] = 0;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 0) * 30;
    depth = VecGet(&pos, 1);
    GBLayerAddPixel(layers[2], &pos, &col, depth);
    col = GBColorBlue;
    depth = 0.0;
    GBLayerAddPixel(layers[3], &pos, &col, depth);
  } while (VecStep(&pos, &dim));
  GBSurfaceUpdate(surf);
  unsigned char check[400] = {
    255,255,255,255, 255,255,255,255, 255,255,255,255, 255,255,255,
    255, 255,255,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 255,255,255,255, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    255,255,255,255, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    255,255,255,255, 0,255,0,255, 0,255,0,255, 0,0,0,255, 0,30,0,255, 
    0,60,0,255, 0,90,0,255, 0,120,0,255, 0,0,0,0, 0,0,0,0, 
    255,255,255,255, 0,255,0,255, 0,255,0,255, 26,30,0,255, 
    0,0,0,255, 4,34,0,255, 7,67,0,255, 11,101,0,255, 120,184,120,255, 
    0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 46,60,0,255, 
    0,0,30,255, 7,34,26,255, 14,67,23,255, 21,101,19,255, 
    120,184,136,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    148,90,90,255, 0,0,60,255, 11,34,53,255, 21,67,46,255, 
    32,101,39,255, 120,184,152,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 184,120,120,255, 0,0,90,255, 14,34,79,255, 28,67,69,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,120,255, 30,56,136,255, 60,106,152,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBSurfaceUpdate failed");
      //PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceFree(&surf);
  printf("UnitTestGBSurfaceUpdate OK\n");
}

void UnitTestGBSurfaceAddLayerFromFile() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  GBLayer* layer = GBSurfaceAddLayerFromFile(surf, "./ImageRef.tga");
  (void)layer;
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBSurfaceUpdate(surf);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,255,0,255, 0,255,0,255, 0,0,0,255, 0,30,0,255, 
    0,60,0,255, 0,90,0,255, 0,120,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 26,30,0,255, 0,0,0,255, 4,34,0,255, 
    7,67,0,255, 11,101,0,255, 120,184,120,255, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 46,60,0,255, 0,0,30,255, 7,34,26,255, 
    14,67,23,255, 21,101,19,255, 120,184,136,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 148,90,90,255, 0,0,60,255, 11,34,53,255, 
    21,67,46,255, 32,101,39,255, 120,184,152,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 184,120,120,255, 0,0,90,255, 14,34,79,255, 
    28,67,69,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,120,255, 30,56,136,255, 
    60,106,152,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBSurfaceAddLayerFromFile failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceFree(&surf);
  printf("UnitTestGBSurfaceAddLayerFromFile OK\n");
}

void UnitTestGBSurfaceFlush() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBLayerSetModified(layer, false);
  GBPixel blue = GBColorBlue;
  GBSurfaceSetBgColor(surf, &blue);
  GBSurfaceFlush(surf);
  if (GBLayerIsModified(layer) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBSurfaceFlush failed");
    PBErrCatch(ShapoidErr);
  }
  for (int iPix = GBSurfaceArea(surf); iPix--;)
    if (memcmp(surf->_finalPix + iPix, &blue, sizeof(GBPixel)) != 0) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBSurfaceFlush failed");
      PBErrCatch(ShapoidErr);
    }
  GBSurfaceFree(&surf);
  printf("UnitTestGBSurfaceFlush OK\n");
}

void UnitTestGBSurfaceIsSameAs() {
  char* fileName = "./ImageRef.tga";
  GBSurface* surfA = (GBSurface*)GBSurfaceImageCreateFromFile(fileName);
  GBSurface* surfB = (GBSurface*)GBSurfaceImageCreateFromFile(fileName);
  if (GBSurfaceIsSameAs(surfA, surfB) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBSurfaceIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(GBSurfaceDim(surfA), 0, 0);
  if (GBSurfaceIsSameAs(surfA, surfB) == true) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBSurfaceIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(GBSurfaceDim(surfA), 0, 10);
  GBSurfaceFinalPixels(surfA)->_rgba[GBPixelAlpha] = 255;
  if (GBSurfaceIsSameAs(surfA, surfB) == true) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBSurfaceIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  GBSurfaceFree(&surfA);
  GBSurfaceFree(&surfB);
  printf("UnitTestGBSurfaceIsSameAs OK\n");
}

void UnitTestGBSurfaceNormalizeHue() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 3); 
  GBSurface* surf = GBSurfaceCreate(GBSurfaceTypeImage, &dim);
  unsigned char in[27] = {
    20,20,20, 10,20,30, 60,50,40,
    30,30,30, 20,30,40, 50,40,30,
    40,40,40, 30,40,50, 40,30,20
    };
  VecShort2D p = VecShortCreateStatic2D();
  int iPix = 0;
  do {
    GBPixel* pix = GBSurfaceFinalPixel(surf, &p);
    pix->_rgba[GBPixelRed] = in[iPix * 3];
    pix->_rgba[GBPixelGreen] = in[iPix * 3 + 1];
    pix->_rgba[GBPixelBlue] = in[iPix * 3 + 2];
    ++iPix;
  } while (VecStep(&p, GBSurfaceDim(surf)));
  GBPostProcessing post = 
    GBPostProcessingCreateStatic(GBPPTypeNormalizeHue);
  GBSurfacePostProcess(surf, &post);
  VecSetNull(&p);
  iPix = 0;
  unsigned char out[27] = {
    51,51,51, 0,51,102, 255,204,153, 
    102,102,102, 51,102,153, 204,153,102, 
    153,153,153, 102,153,204, 153,102,51
    };
  do {
    GBPixel* pix = GBSurfaceFinalPixel(surf, &p);
    if (pix->_rgba[GBPixelRed] != out[iPix * 3] ||
      pix->_rgba[GBPixelGreen] != out[iPix * 3 + 1] ||
      pix->_rgba[GBPixelBlue] != out[iPix * 3 + 2]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "UnitTestGBSurfaceNormalizeHue failed");
      PBErrCatch(ShapoidErr);
    }
    ++iPix;
  } while (VecStep(&p, GBSurfaceDim(surf)));
  GBSurfaceFree(&surf);
  GBSurfaceImage* img = GBSurfaceImageCreateFromFile(
    "./GBSurfaceNormalizeHueTest.tga");
  GBSurfacePostProcess((GBSurface*)img, &post);
  GBSurfaceImage* ref = GBSurfaceImageCreateFromFile(
    "./GBSurfaceNormalizeHueRef.tga");
  if (GBSurfaceIsSameAs((GBSurface*)img, (GBSurface*)ref) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "UnitTestGBSurfaceNormalizeHue failed");
    PBErrCatch(ShapoidErr);
  }
  GBSurfaceFree(&surf);
  GBSurfaceImageFree(&img);
  GBSurfaceImageFree(&ref);
  printf("UnitTestGBSurfaceNormalizeHue OK\n");
}

void UnitTestGBSurface() {
  UnitTestGBSurfaceCreateFree();
  UnitTestGBSurfaceGetSet();
  UnitTestGBSurfaceArea();
  UnitTestGBSurfaceClone();
  UnitTestGBSurfaceAddRemoveLayer();
  UnitTestGBSurfaceGetLayerNbLayer();
  UnitTestGBSurfaceSetLayersModified();
  UnitTestGBSurfaceSetLayerPos();
  UnitTestGBSurfaceGetModifiedArea();
  UnitTestGBSurfaceUpdate();
  UnitTestGBSurfaceAddLayerFromFile();
  UnitTestGBSurfaceFlush();
  UnitTestGBSurfaceIsSameAs();
  UnitTestGBSurfaceNormalizeHue();
  printf("UnitTestGBSurface OK\n");
}

void UnitTestGBSurfaceImageCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GBSurfaceImage* surf = GBSurfaceImageCreate(&dim);
  if (GBSurfaceGetType((GBSurface*)surf) != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBSurfaceDim((GBSurface*)surf), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (surf->_fileName != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceImageFree(&surf);
  printf("UnitTestGBSurfaceImageCreateFree OK\n");
}

void UnitTestGBSurfaceImageGetSet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GBSurfaceImage* surf = GBSurfaceImageCreate(&dim);
  if (GBSurfaceImageFileName(surf) != surf->_fileName) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageFileName failed");
    PBErrCatch(GenBrushErr);
  }
  char* fileName = "./";
  GBSurfaceImageSetFileName(surf, fileName);
  if (strcmp(surf->_fileName, fileName) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageSetFileName failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceImageFree(&surf);
  printf("UnitTestGBSurfaceImageGetSet OK\n");
}

void UnitTestGBSurfaceImageClone() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GBSurfaceImage* surf = GBSurfaceImageCreate(&dim);
  char* fileName = "./";
  GBSurfaceImageSetFileName(surf, fileName);
  GBSurfaceImage* clone = GBSurfaceImageClone(surf);
  if (GBSurfaceGetType((GBSurface*)clone) != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBSurfaceDim((GBSurface*)clone), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (strcmp(clone->_fileName, fileName) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageClone failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceImageFree(&surf);
  GBSurfaceImageFree(&clone);
  printf("UnitTestGBSurfaceImageClone OK\n");
}

void UnitTestGBSurfaceImageSave() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurfaceImage* surfImage = GBSurfaceImageCreate(&dim);
  GBSurface* surf = (GBSurface*)surfImage;

GBPixel t = GBColorTransparent;
GBSurfaceSetBgColor(surf, &t);
GBSurfaceFlush(surf);

  GBLayer* layers[4] = {NULL};
  VecSet(&dim, 0, 5); VecSet(&dim, 1, 5); 
  for (int iLayer = 0; iLayer < 4; ++iLayer) {
    layers[iLayer] = GBSurfaceAddLayer(surf, &dim);
    GBLayerSetBlendMode(layers[iLayer], GBLayerBlendModeOver);
  }
  GBLayerSetStackPos(layers[0], GBLayerStackPosBg);
  GBLayerSetStackPos(layers[1], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[2], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[3], GBLayerStackPosFg);
  VecShort2D pos = VecShortCreateStatic2D();
  VecSet(&pos, 0, 1); VecSet(&pos, 1, 1); 
  GBLayerSetPos(layers[0], &pos);
  VecSet(&pos, 0, 3); VecSet(&pos, 1, 3); 
  GBLayerSetPos(layers[1], &pos);
  VecSet(&pos, 0, 4); VecSet(&pos, 1, 4); 
  GBLayerSetPos(layers[2], &pos);
  VecSet(&pos, 0, 7); VecSet(&pos, 1, 7); 
  GBLayerSetPos(layers[3], &pos);
  VecSetNull(&pos);
  GBPixel col;
  float depth;
  do {
    col = GBColorGreen;
    depth = 0.0;
    GBLayerAddPixel(layers[0], &pos, &col, depth);
    col._rgba[GBPixelRed] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = 0;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 1) * 30;
    depth = VecGet(&pos, 0);
    GBLayerAddPixel(layers[1], &pos, &col, depth);
    col._rgba[GBPixelRed] = 0;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 0) * 30;
    depth = VecGet(&pos, 1);
    GBLayerAddPixel(layers[2], &pos, &col, depth);
    col = GBColorBlue;
    depth = 0.0;
    GBLayerAddPixel(layers[3], &pos, &col, depth);
  } while (VecStep(&pos, &dim));
  GBSurfaceUpdate(surf);
  GBSurfaceImageSetFileName(surfImage, "./GBSurfaceImageSave.tga");
  if (GBSurfaceImageSave(surfImage) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageSave failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceImageFree(&surfImage);
  printf("UnitTestGBSurfaceImageSave OK\n");
}

void UnitTestGBSurfaceImageCreateFromFile() {
  char* fileName = "./ImageRef.tga";
  GBSurfaceImage* surfImage = GBSurfaceImageCreateFromFile(fileName);
  if (surfImage == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceImageCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurface* surf = (GBSurface*)surfImage;
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,255,0,255, 0,255,0,255, 0,0,0,255, 0,30,0,255, 
    0,60,0,255, 0,90,0,255, 0,120,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 26,30,0,255, 0,0,0,255, 4,34,0,255, 
    7,67,0,255, 11,101,0,255, 120,184,120,255, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 46,60,0,255, 0,0,30,255, 7,34,26,255, 
    14,67,23,255, 21,101,19,255, 120,184,136,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 148,90,90,255, 0,0,60,255, 11,34,53,255, 
    21,67,46,255, 32,101,39,255, 120,184,152,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 184,120,120,255, 0,0,90,255, 14,34,79,255, 
    28,67,69,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,120,255, 30,56,136,255, 
    60,106,152,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBSurfaceCreateFromFile failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageFree(&surfImage);
  printf("UnitTestGBSurfaceImageCreateFromFile OK\n");
}

void UnitTestGBSurfaceImage() {
  UnitTestGBSurfaceImageCreateFree();
  UnitTestGBSurfaceImageGetSet();
  UnitTestGBSurfaceImageClone();
  UnitTestGBSurfaceImageSave();
  UnitTestGBSurfaceImageCreateFromFile();
  printf("UnitTestGBSurfaceImage OK\n");
}

void UnitTestGBEyeOrthoCreateFree() {
  GBEyeOrthoView view = GBEyeOrthoViewFront;
  GBEyeOrtho* eye = GBEyeOrthoCreate(view);
  if (eye->_view != GBEyeOrthoViewFront) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeOrthoCreate failed");
    PBErrCatch(GenBrushErr);
  }
  float check[9] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  VecShort2D index = VecShortCreateStatic2D();
  VecShort2D dim = MatGetDim(GBEyeProj(eye));
  int iCheck = 0;
  do {
    if (ISEQUALF(MatGet(GBEyeProj(eye), &index), 
      check[iCheck]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoCreate failed");
      PBErrCatch(GenBrushErr);
    }
    ++iCheck;
  } while (VecStep(&index, &dim));
  GBEyeFree(&eye);
  if (eye != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeOrthoFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBEyeOrthoCreateFree OK\n"); 
}

void UnitTestGBEyeOrthoGetSet() {
  GBEyeOrthoView view = GBEyeOrthoViewFront;
  GBEyeOrtho* eye = GBEyeOrthoCreate(view);
  VecShort2D index = VecShortCreateStatic2D();
  VecFloat3D scale = VecFloatCreateStatic3D();
  VecSet(&scale, 0, 2.0); VecSet(&scale, 1, 3.0); 
  VecSet(&scale, 2, 1.0);
  GBEyeSetScale(eye, &scale);
  VecFloat2D orig = VecFloatCreateStatic2D();
  VecSet(&orig, 0, 4.0); VecSet(&orig, 1, 5.0);
  GBEyeSetOrig(eye, &orig);
  float theta = PBMATH_QUARTERPI;
  GBEyeSetRot(eye, theta);
  VecShort2D dim = MatGetDim(GBEyeProj(eye));
  float check[6][9] = {
    {1.414214, 1.414214, 0.0, -2.121320, 2.121320, 0.0, 0.0, 
      0.0, 1.0},
    {-1.414214, -1.414214, 0.0, -2.121320, 2.121320, 0.0, 0.0,
      0.0, -1.0},
    {1.414214, 1.414214, 0.0, 0.0, 0.0, -1.0, -2.121320, 2.121320,
      0.0},
    {1.414214, 1.414214, 0.0, 0.0, 0.0, 1.0, 2.121320, -2.121320,
      0.0},
    {0.0, 0.0, 1.0, -2.121320, 2.121320, 0.0, -1.414214, -1.414214,
      0.0},
    {0.0, 0.0, -1.0, -2.121320, 2.121320, 0.0, 1.414214, 1.414214,
      0.0}
    };
  for (int iView = 6; iView--;) {
    int iCheck = 0;
    VecSetNull(&index);
    GBEyeOrthoSetView(eye, (GBEyeOrthoView)iView);
    do {
      if (ISEQUALF(MatGet(GBEyeProj(eye), &index), 
        check[iView][iCheck]) == false) {
        GenBrushErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GenBrushErr->_msg, "GBEyeOrthoSetView failed");
        PBErrCatch(GenBrushErr);
      }
      ++iCheck;
    } while (VecStep(&index, &dim));
  }
  GBEyeFree(&eye);
  printf("UnitTestGBEyeOrthoGetSet OK\n"); 
}

void UnitTestGBEyeOrthoProcessPoint() {
  VecFloat2D v2d = VecFloatCreateStatic2D();
  VecSet(&v2d, 0, 0.0); VecSet(&v2d, 1, 1.0); 
  VecFloat3D v3d = VecFloatCreateStatic3D();
  VecSet(&v3d, 0, 1.0); VecSet(&v3d, 1, 0.0); VecSet(&v3d, 2, 1.0); 
  VecFloat* v4d = VecFloatCreate(4);
  VecSet(v4d, 0, 1.0); VecSet(v4d, 1, 2.0); 
  VecSet(v4d, 2, 3.0); VecSet(v4d, 3, 4.0); 
  float check2d[6][2] = {
    {1.0,5.0},
    {1.0,5.0},
    {4.0,5.0},
    {4.0,5.0},
    {1.0,5.0},
    {1.0,5.0}};
  float check3d[6][3] = {
    {4.0,7.0,1.0},
    {4.0,3.0,-1.0},
    {1.0,7.0,0.0},
    {7.0,7.0,0.0},
    {4.0,3.0,1.0},
    {4.0,7.0,-1.0}};
  float check4d[6][4] = {
    {-2.0,7.0,3.0,4.0},
    {-2.0,3.0,-3.0,4.0},
    {-5.0,7.0,-2.0,4.0},
    {13.0,7.0,2.0,4.0},
    {-2.0,-1.0,1.0,4.0},
    {-2.0,11.0,-1.0,4.0}};
  GBHandDefault* hand = GBHandDefaultCreate();
  for (int iView = 6; iView--;) {
    GBEyeOrthoView view = (GBEyeOrthoView)iView;
    GBEyeOrtho* eye = GBEyeOrthoCreate(view);
    VecFloat3D scale = VecFloatCreateStatic3D();
    VecSet(&scale, 0, 2.0); VecSet(&scale, 1, 3.0); 
    VecSet(&scale, 2, 1.0);
    GBEyeSetScale(eye, &scale);
    VecFloat2D orig = VecFloatCreateStatic2D();
    VecSet(&orig, 0, 4.0); VecSet(&orig, 1, 5.0);
    GBEyeSetOrig(eye, &orig);
    float theta = PBMATH_HALFPI;
    GBEyeSetRot(eye, theta);
    GBLayer layer;
    GBInk ink;
    GBTool tool;
    GBObjPod* pod = GBObjPodCreatePoint((VecFloat*)&v2d, eye, 
      hand, &tool, &ink, &layer);
    VecFloat* proj = GBObjPodGetEyeObjAsPoint(pod);
    if (VecGetDim(proj) != VecGetDim(pod->_srcPoint)) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
      PBErrCatch(GenBrushErr);
    }
    for (int i = VecGetDim(proj); i--;) {
      if (ISEQUALF(VecGet(proj, i), check2d[iView][i]) == false) {
        GenBrushErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
        PBErrCatch(GenBrushErr);
      }
    }
    pod->_srcPoint = (VecFloat*)&v3d;
    GBEyeProcess((GBEye*)eye, pod);
    proj = GBObjPodGetEyeObjAsPoint(pod);
    if (VecGetDim(proj) != 3) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
      PBErrCatch(GenBrushErr);
    }
    for (int i = VecGetDim(proj); i--;) {
      if (ISEQUALF(VecGet(proj, i), check3d[iView][i]) == false) {
        GenBrushErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
        PBErrCatch(GenBrushErr);
      }
    }
    pod->_srcPoint = v4d;
    GBEyeProcess((GBEye*)eye, pod);
    proj = GBObjPodGetEyeObjAsPoint(pod);
    if (VecGetDim(proj) != 4) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
      PBErrCatch(GenBrushErr);
    }
    for (int i = VecGetDim(proj); i--;) {
      if (ISEQUALF(VecGet(proj, i), check4d[iView][i]) == false) {
        GenBrushErr->_type = PBErrTypeUnitTestFailed;
        sprintf(GenBrushErr->_msg, "GBEyeOrthoProcess failed");
        PBErrCatch(GenBrushErr);
      }
    }
    GBEyeFree(&eye);
    GBObjPodFree(&pod);
  }
  GBHandDefaultFree(&hand);
  VecFree(&v4d);
  printf("UnitTestGBEyeOrthoProcessPoint OK\n"); 
}

void UnitTestGBEyeOrthoProcessCurve() {
  SCurve* curve = SCurveCreate(1, 2, 2);
  for (int iCtrl = SCurveGetNbCtrl(curve); iCtrl--;) {
    SCurveCtrlSet(curve, iCtrl, 0, (float)iCtrl);
    SCurveCtrlSet(curve, iCtrl, 1, (float)iCtrl * 2.0);
  }
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  float theta = PBMATH_HALFPI;
  GBEyeSetRot((GBEye*)eye, theta);
  SCurve* projCurve = GBEyeGetProjectedCurve((GBEye*)eye, curve);
  if (SCurveGetDim(projCurve) != SCurveGetDim(curve)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeOrthoGetProjectedCurve failed");
    PBErrCatch(GenBrushErr);
  }
  for (int iCtrl = SCurveGetNbCtrl(curve); iCtrl--;) {
    if (ISEQUALF(SCurveCtrlGet(projCurve, iCtrl, 0), 
      (float)iCtrl * -2.0) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoGetProjectedCurve failed");
      PBErrCatch(GenBrushErr);
    }
    if (ISEQUALF(SCurveCtrlGet(projCurve, iCtrl, 1), 
      (float)iCtrl) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeOrthoGetProjectedCurve failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeFree(&eye);
  SCurveFree(&curve);
  SCurveFree(&projCurve);
  printf("UnitTestGBEyeOrthoProcessCurve OK\n"); 
}

void UnitTestGBEyeOrthoProcessShapoid() {
  Facoid* facoid = FacoidCreate(2);
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 2.0); 
  ShapoidTranslate(facoid, &v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 3.0);
  ShapoidScale(facoid, (VecFloat*)&v);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  Shapoid* shap = 
    GBEyeGetProjectedShapoid((GBEye*)eye, (Shapoid*)facoid);
  VecFloat2D checka = VecFloatCreateStatic2D();
  VecSet(&checka, 0, 1.0); VecSet(&checka, 1, 2.0); 
  VecFloat2D checkb = VecFloatCreateStatic2D();
  VecSet(&checkb, 0, 2.0); VecSet(&checkb, 1, 0.0); 
  VecFloat2D checkc = VecFloatCreateStatic2D();
  VecSet(&checkc, 0, 0.0); VecSet(&checkc, 1, 3.0); 
  if (VecIsEqual(ShapoidPos(shap), &checka) == false ||
    VecIsEqual(ShapoidAxis(shap, 0), &checkb) == false ||
    VecIsEqual(ShapoidAxis(shap, 1), &checkc) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeOrthoGetProjectedShapoid failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&shap);
  GBEyeFree(&eye);
  ShapoidFree(&facoid);

  Spheroid* spheroid = SpheroidCreate(3);
  VecFloat3D u = VecFloatCreateStatic3D();
  VecSet(&u, 0, 1.0); VecSet(&u, 1, 2.0); VecSet(&u, 2, 3.0); 
  ShapoidTranslate(spheroid, &u);
  VecSet(&u, 0, 2.0); VecSet(&u, 1, 3.0); VecSet(&u, 1, 4.0);
  ShapoidScale(spheroid, (VecFloat*)&u);
  VecFloat3D checkd[6];
  VecFloat3D checke[6];
  VecFloat3D checkf[6];
  VecFloat3D checkg[6];
  for (int iView = 6; iView--;) {
    checkd[iView] = VecFloatCreateStatic3D();
    checke[iView] = VecFloatCreateStatic3D();
    checkf[iView] = VecFloatCreateStatic3D();
    checkg[iView] = VecFloatCreateStatic3D();
  }
  VecSet(checkd, 0, 3.0); VecSet(checkd, 1, 2.0); 
  VecSet(checkd, 2, -1.0); 
  VecSet(checke, 0, 0.0); VecSet(checke, 1, 0.0); 
  VecSet(checke, 2, -2.0); 
  VecSet(checkf, 0, 0.0); VecSet(checkf, 1, 4.0); 
  VecSet(checkf, 2, 0.0); 
  VecSet(checkg, 0, 3.0); VecSet(checkg, 1, 0.0); 
  VecSet(checkg, 2, 0.0); 
  VecSet(checkd + 1, 0, -3.0); VecSet(checkd + 1, 1, 2.0); 
  VecSet(checkd + 1, 2, 1.0); 
  VecSet(checke + 1, 0, 0.0); VecSet(checke + 1, 1, 0.0); 
  VecSet(checke + 1, 2, 2.0); 
  VecSet(checkf + 1, 0, 0.0); VecSet(checkf + 1, 1, 4.0); 
  VecSet(checkf + 1, 2, 0.0); 
  VecSet(checkg + 1, 0, -3.0); VecSet(checkg + 1, 1, 0.0); 
  VecSet(checkg + 1, 2, 0.0); 
  VecSet(checkd + 2, 0, 1.0); VecSet(checkd + 2, 1, -3.0); 
  VecSet(checkd + 2, 2, 2.0); 
  VecSet(checke + 2, 0, 2.0); VecSet(checke + 2, 1, 0.0); 
  VecSet(checke + 2, 2, 0.0); 
  VecSet(checkf + 2, 0, 0.0); VecSet(checkf + 2, 1, 0.0); 
  VecSet(checkf + 2, 2, 4.0); 
  VecSet(checkg + 2, 0, 0.0); VecSet(checkg + 2, 1, -3.0); 
  VecSet(checkg + 2, 2, 0.0); 
  VecSet(checkd + 3, 0, 1.0); VecSet(checkd + 3, 1, 3.0); 
  VecSet(checkd + 3, 2, -2.0); 
  VecSet(checke + 3, 0, 2.0); VecSet(checke + 3, 1, 0.0); 
  VecSet(checke + 3, 2, 0.0); 
  VecSet(checkf + 3, 0, 0.0); VecSet(checkf + 3, 1, 0.0); 
  VecSet(checkf + 3, 2, -4.0); 
  VecSet(checkg + 3, 0, 0.0); VecSet(checkg + 3, 1, 3.0); 
  VecSet(checkg + 3, 2, 0.0); 
  VecSet(checkd + 4, 0, -1.0); VecSet(checkd + 4, 1, 2.0); 
  VecSet(checkd + 4, 2, -3.0); 
  VecSet(checke + 4, 0, -2.0); VecSet(checke + 4, 1, 0.0); 
  VecSet(checke + 4, 2, 0.0); 
  VecSet(checkf + 4, 0, 0.0); VecSet(checkf + 4, 1, 4.0); 
  VecSet(checkf + 4, 2, 0.0); 
  VecSet(checkg + 4, 0, 0.0); VecSet(checkg + 4, 1, 0.0); 
  VecSet(checkg + 4, 2, -3.0); 
  VecSet(checkd + 5, 0, 1.0); VecSet(checkd + 5, 1, 2.0); 
  VecSet(checkd + 5, 2, 3.0); 
  VecSet(checke + 5, 0, 2.0); VecSet(checke + 5, 1, 0.0); 
  VecSet(checke + 5, 2, 0.0); 
  VecSet(checkf + 5, 0, 0.0); VecSet(checkf + 5, 1, 4.0); 
  VecSet(checkf + 5, 2, 0.0); 
  VecSet(checkg + 5, 0, 0.0); VecSet(checkg + 5, 1, 0.0); 
  VecSet(checkg + 5, 2, 3.0); 
  for (int iView = 6; iView--;) {
    GBEyeOrthoView view = (GBEyeOrthoView)iView;
    GBEyeOrtho* eye = GBEyeOrthoCreate(view);
    Shapoid* shap = 
      GBEyeGetProjectedShapoid((GBEye*)eye, (Shapoid*)spheroid);
    if (VecIsEqual(ShapoidPos(shap), checkd + 5 - iView) == false ||
      VecIsEqual(ShapoidAxis(shap, 0), checke + 5 - iView) == false ||
      VecIsEqual(ShapoidAxis(shap, 1), checkf + 5 - iView) == false ||
      VecIsEqual(ShapoidAxis(shap, 2), checkg + 5 - iView) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, 
        "GBEyeOrthoGetProjectedShapoid failed");
      PBErrCatch(GenBrushErr);
    }
    ShapoidFree(&shap);
    GBEyeFree(&eye);
  }
  ShapoidFree(&spheroid);
  printf("UnitTestGBEyeOrthoProcessShapoid OK\n"); 
}

void UnitTestGBEyeOrtho() {
  UnitTestGBEyeOrthoCreateFree();
  UnitTestGBEyeOrthoGetSet();
  UnitTestGBEyeOrthoProcessPoint();
  UnitTestGBEyeOrthoProcessCurve();
  UnitTestGBEyeOrthoProcessShapoid();
  printf("UnitTestGBEyeOrtho OK\n"); 
}

void UnitTestGBEyeIsometricCreateFree() {
  GBEyeIsometric* eye = GBEyeIsometricCreate();
  if (GBEyeGetType(eye) != GBEyeTypeIsometric ||
    ISEQUALF(eye->_thetaRight, PBMATH_QUARTERPI) == false ||
    ISEQUALF(eye->_thetaY, PBMATH_QUARTERPI) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricCreate failed");
    PBErrCatch(GenBrushErr);
  }
  float check[9] = {
    0.707107, -0.00000, -0.707107, 
    0.50000, 0.707107, 0.50000, 
    0.50000, -0.707107, 0.50000
    };
  for (int iVal = 9; iVal--;) {
    if (ISEQUALF(eye->_eye._proj->_val[iVal], check[iVal]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricCreate failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeFree(&eye);
  if (eye != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBEyeIsometricCreateFree OK\n"); 
}

void UnitTestGBEyeIsometricGetSet() {
  GBEyeIsometric* eye = GBEyeIsometricCreate();
  if (ISEQUALF(GBEyeIsometricGetRotY(eye), eye->_thetaY) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricGetRotY failed");
    PBErrCatch(GenBrushErr);
  }
  if (ISEQUALF(GBEyeIsometricGetRotRight(eye), 
    eye->_thetaRight) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricGetRotRight failed");
    PBErrCatch(GenBrushErr);
  }
  GBEyeIsometricSetRotRight(eye, 0.5 * PBMATH_QUARTERPI);
  if (ISEQUALF(GBEyeIsometricGetRotRight(eye), 
    0.5 * PBMATH_QUARTERPI) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricSetRotRight failed");
    PBErrCatch(GenBrushErr);
  }
  float checka[9] = {
    0.707107, -0.000000, -0.707107,
    0.270598, 0.923880, 0.270598,
    0.653282, -0.382683, 0.653281
    };
  for (int iVal = 9; iVal--;) {
    if (ISEQUALF(eye->_eye._proj->_val[iVal], checka[iVal]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricSetRotRight failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeIsometricSetRotY(eye, 0.5 * PBMATH_QUARTERPI);
  float checkb[9] = {
    0.923880, -0.000000, -0.382683,
    0.146447, 0.923880, 0.353553,
    0.353553, -0.382683, 0.853553
    };
  if (ISEQUALF(GBEyeIsometricGetRotY(eye), 
    0.5 * PBMATH_QUARTERPI) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricSetRotY failed");
    PBErrCatch(GenBrushErr);
  }
  for (int iVal = 9; iVal--;) {
    if (ISEQUALF(eye->_eye._proj->_val[iVal], checkb[iVal]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricSetRotY failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeFree(&eye);
  printf("UnitTestGBEyeIsometricGetSet OK\n"); 
}

void UnitTestGBEyeIsometricProcessPoint() {
  VecFloat2D v2d = VecFloatCreateStatic2D();
  VecSet(&v2d, 0, 0.0); VecSet(&v2d, 1, 1.0); 
  VecFloat3D v3d = VecFloatCreateStatic3D();
  VecSet(&v3d, 0, 1.0); VecSet(&v3d, 1, 0.0); VecSet(&v3d, 2, 1.0); 
  VecFloat* v4d = VecFloatCreate(4);
  VecSet(v4d, 0, 1.0); VecSet(v4d, 1, 2.0); 
  VecSet(v4d, 2, 3.0); VecSet(v4d, 3, 4.0); 
  float check2d[2] = {1.878680,5.0};
  float check3d[3] = {1.0,5.0,1.0};
  float check4d[4] = {-6.242640,2.171572,0.585786,4.0};
  GBHandDefault* hand = GBHandDefaultCreate();
  GBEyeIsometric* eye = GBEyeIsometricCreate();
  VecFloat3D scale = VecFloatCreateStatic3D();
  VecSet(&scale, 0, 2.0); VecSet(&scale, 1, 3.0);
  VecSet(&scale, 2, 1.0);
  GBEyeSetScale(eye, &scale);
  VecFloat2D orig = VecFloatCreateStatic2D();
  VecSet(&orig, 0, 4.0); VecSet(&orig, 1, 5.0);
  GBEyeSetOrig(eye, &orig);
  float theta = PBMATH_HALFPI;
  GBEyeSetRot(eye, theta);
  GBLayer layer;
  GBInk ink;
  GBTool tool;
  GBObjPod* pod = GBObjPodCreatePoint((VecFloat*)&v2d, eye, 
    hand, &tool, &ink, &layer);
  VecFloat* proj = GBObjPodGetEyeObjAsPoint(pod);
  if (VecGetDim(proj) != VecGetDim(pod->_srcPoint)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
    PBErrCatch(GenBrushErr);
  }
  for (int i = VecGetDim(proj); i--;) {
    if (ISEQUALF(VecGet(proj, i), check2d[i]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
      PBErrCatch(GenBrushErr);
    }
  }
  pod->_srcPoint = (VecFloat*)&v3d;
  GBEyeProcess((GBEye*)eye, pod);
  proj = GBObjPodGetEyeObjAsPoint(pod);
  if (VecGetDim(proj) != 3) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
    PBErrCatch(GenBrushErr);
  }
  for (int i = VecGetDim(proj); i--;) {
    if (ISEQUALF(VecGet(proj, i), check3d[i]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
      PBErrCatch(GenBrushErr);
    }
  }
  pod->_srcPoint = v4d;
  GBEyeProcess((GBEye*)eye, pod);
  proj = GBObjPodGetEyeObjAsPoint(pod);
  if (VecGetDim(proj) != 4) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
    PBErrCatch(GenBrushErr);
  }
  for (int i = VecGetDim(proj); i--;) {
    if (ISEQUALF(VecGet(proj, i), check4d[i]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBEyeIsometricProcess failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeFree(&eye);
  GBObjPodFree(&pod);
  GBHandDefaultFree(&hand);
  VecFree(&v4d);
  printf("UnitTestGBEyeIsometricProcessPoint OK\n"); 
}

void UnitTestGBEyeIsometricProcessCurve() {
  SCurve* curve = SCurveCreate(1, 2, 2);
  for (int iCtrl = SCurveGetNbCtrl(curve); iCtrl--;) {
    SCurveCtrlSet(curve, iCtrl, 0, (float)iCtrl);
    SCurveCtrlSet(curve, iCtrl, 1, (float)iCtrl * 2.0);
  }
  GBEyeIsometric* eye = GBEyeIsometricCreate();
  SCurve* projCurve = GBEyeGetProjectedCurve((GBEye*)eye, curve);
  if (SCurveGetDim(projCurve) != SCurveGetDim(curve)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, 
      "GBEyeIsometricGetProjectedCurve failed");
    PBErrCatch(GenBrushErr);
  }
  float check[3][2]={
    {0.0,0.0},
    {0.707107,1.914214},
    {1.414214,3.828427}
    };
  for (int iCtrl = SCurveGetNbCtrl(curve); iCtrl--;) {
    if (ISEQUALF(SCurveCtrlGet(projCurve, iCtrl, 0), 
      check[iCtrl][0]) == false ||
      ISEQUALF(SCurveCtrlGet(projCurve, iCtrl, 1), 
      check[iCtrl][1]) == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, 
        "GBEyeIsometricGetProjectedCurve failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBEyeFree(&eye);
  SCurveFree(&curve);
  SCurveFree(&projCurve);
  printf("UnitTestGBEyeIsometricProcessCurve OK\n"); 
}

void UnitTestGBEyeIsometricProcessShapoid() {
  Facoid* facoid = FacoidCreate(3);
  VecFloat3D v = VecFloatCreateStatic3D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 2.0); VecSet(&v, 2, 3.0); 
  ShapoidTranslate(facoid, &v);
  VecSet(&v, 0, 3.0); VecSet(&v, 1, 2.0); VecSet(&v, 2, 1.0); 
  ShapoidScale(facoid, (VecFloat*)&v);
  GBEyeIsometric* eye = GBEyeIsometricCreate();
  Shapoid* shap = 
    GBEyeGetProjectedShapoid((GBEye*)eye, (Shapoid*)facoid);
  VecFloat3D checka = VecFloatCreateStatic3D();
  VecSet(&checka, 0, -1.414214); VecSet(&checka, 1, 3.414214); 
  VecSet(&checka, 2, 0.585786); 
  VecFloat3D checkb = VecFloatCreateStatic3D();
  VecSet(&checkb, 0, 2.121320); VecSet(&checkb, 1, 1.500000); 
  VecSet(&checkb, 2, 1.500000); 
  VecFloat3D checkc = VecFloatCreateStatic3D();
  VecSet(&checkc, 0, 0.000000); VecSet(&checkc, 1, 1.414214); 
  VecSet(&checkc, 2, -1.414214); 
  VecFloat3D checkd = VecFloatCreateStatic3D();
  VecSet(&checkd, 0, -0.707107); VecSet(&checkd, 1, 0.500000); 
  VecSet(&checkd, 2, 0.500000); 
  if (VecIsEqual(ShapoidPos(shap), &checka) == false ||
    VecIsEqual(ShapoidAxis(shap, 0), &checkb) == false ||
    VecIsEqual(ShapoidAxis(shap, 1), &checkc) == false ||
    VecIsEqual(ShapoidAxis(shap, 2), &checkd) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, 
      "GBEyeIsometricGetProjectedShapoid failed");
    PBErrCatch(GenBrushErr);
  }
  ShapoidFree(&shap);
  GBEyeFree(&eye);
  ShapoidFree(&facoid);
  printf("UnitTestGBEyeIsometricProcessShapoid OK\n"); 
}

void UnitTestGBEyeIsometric() {
  UnitTestGBEyeIsometricCreateFree();
  UnitTestGBEyeIsometricGetSet();
  UnitTestGBEyeIsometricProcessPoint();
  UnitTestGBEyeIsometricProcessCurve();
  UnitTestGBEyeIsometricProcessShapoid();
  printf("UnitTestGBEyeIsometric OK\n"); 
}

void UnitTestGBEyeCreateFree() {
  VecFloat3D v = VecFloatCreateStatic3D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0); VecSet(&v, 2, 1.0);
  VecFloat2D w = VecFloatCreateStatic2D();
  GBEye eye = GBEyeCreateStatic(GBEyeTypeOrtho);
  if (eye._type != GBEyeTypeOrtho ||
    VecIsEqual(&(eye._scale), &v) == false ||
    VecIsEqual(&(eye._orig), &w) == false ||
    eye._proj == NULL) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeCreateStatic failed");
    PBErrCatch(ShapoidErr);
  }
  GBEyeFreeStatic(&eye);
  if (eye._proj != NULL) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeFreeStatic failed");
    PBErrCatch(ShapoidErr);
  }
  printf("UnitTestGBEyeCreateFree OK\n");
}

void UnitTestGBEyeGetSet() {
  GBEye eye = GBEyeCreateStatic(GBEyeTypeOrtho);
  if (GBEyeGetType(&eye) != GBEyeTypeOrtho) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeGetType failed");
    PBErrCatch(ShapoidErr);
  }
  if (GBEyeScale(&eye) != &(eye._scale)) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeScale failed");
    PBErrCatch(ShapoidErr);
  }
  VecFloat3D v = GBEyeGetScale(&eye);
  if (VecIsEqual(&v, &(eye._scale)) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeGetScale failed");
    PBErrCatch(ShapoidErr);
  }
  if (GBEyeOrig(&eye) != &(eye._orig)) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeOrig failed");
    PBErrCatch(ShapoidErr);
  }
  VecFloat2D w = GBEyeGetOrig(&eye);
  if (VecIsEqual(&w, &(eye._orig)) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeGetOrig failed");
    PBErrCatch(ShapoidErr);
  }
  if (GBEyeGetRot(&eye) != eye._theta) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeGetRot failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 3.0); VecSet(&v, 2, 4.0);
  GBEyeSetScale(&eye, &v);
  if (VecIsEqual(&v, &(eye._scale)) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeSetScale failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(&v, 0, 3.0); VecSet(&v, 1, 3.0); VecSet(&v, 2, 3.0);
  GBEyeSetScale(&eye, (float)3.0);
  if (VecIsEqual(&v, &(eye._scale)) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeSetScale failed");
    PBErrCatch(ShapoidErr);
  }
  GBEyeSetOrig(&eye, &w);
  if (VecIsEqual(&w, &(eye._orig)) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeSetOrig failed");
    PBErrCatch(ShapoidErr);
  }
  float theta = 1.0;
  GBEyeSetRot(&eye, theta);
  if (ISEQUALF(eye._theta, theta) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeSetRot failed");
    PBErrCatch(ShapoidErr);
  }
  if (GBEyeProj(&eye) != eye._proj) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBEyeProj failed");
    PBErrCatch(ShapoidErr);
  }
  GBEyeFreeStatic(&eye);
  printf("UnitTestGBEyeGetSet OK\n");
}

void UnitTestGBEye() {
  UnitTestGBEyeCreateFree();
  UnitTestGBEyeGetSet();
  UnitTestGBEyeOrtho();
  UnitTestGBEyeIsometric();
  printf("UnitTestGBEye OK\n");
}

void UnitTestGBHandDefaultCreateFree() {
  GBHandDefault* hand = GBHandDefaultCreate();
  if (GBHandGetType(hand) != GBHandTypeDefault) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBHandDefaultCreate failed");
    PBErrCatch(ShapoidErr);
  }
  GBHandDefaultFree(&hand);
  if (hand != NULL) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBHandDefaultFree failed");
    PBErrCatch(ShapoidErr);
  }
  printf("UnitTestGBHandDefaultCreateFree OK\n");
}

void UnitTestGBHandDefaultProcess() {
  VecFloat3D point = VecFloatCreateStatic3D();
  VecSet(&point, 0, 1.0); VecSet(&point, 1, 2.0); 
  VecSet(&point, 2, 3.0);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHandDefault* hand = GBHandDefaultCreate();
  GBTool tool;
  GBInk ink;
  GBLayer layer;
  GBObjPod* pod = 
    GBObjPodCreatePoint(&point, &eye, hand, &tool, &ink, &layer);
  GBHandProcess(hand, pod);
  if (GSetNbElem(&(pod->_handPoints)) == 0 ||
    VecIsEqual(GSetHead(&(pod->_handPoints)), 
      &point) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBHandDefaultProcess failed");
    PBErrCatch(ShapoidErr);
  }
  GBEyeOrthoFree(&eye);
  GBObjPodFree(&pod);
  GBHandDefaultFree(&hand);
  printf("UnitTestGBHandDefaultProcess OK\n");
}

void UnitTestGBHandDefault() {
  UnitTestGBHandDefaultCreateFree();
  UnitTestGBHandDefaultProcess();
  printf("UnitTestGBHandDefault OK\n");
}

void UnitTestGBHandCreateFree() {
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  if (hand._type != GBHandTypeDefault) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBHandCreateStatic failed");
    PBErrCatch(ShapoidErr);
  }
  GBHandFreeStatic(&hand);
  printf("UnitTestGBHandCreateFree OK\n");
}

void UnitTestGBHandGetSet() {
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  if (GBHandGetType(&hand) != GBHandTypeDefault) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBHandGetType failed");
    PBErrCatch(ShapoidErr);
  }
  GBHandFreeStatic(&hand);
  printf("UnitTestGBHandCreateFree OK\n");
}

void UnitTestGBHand() {
  UnitTestGBHandCreateFree();
  UnitTestGBHandGetSet();
  UnitTestGBHandDefault();
  printf("UnitTestGBHand OK\n");
}

void UnitTestGBToolPlotterCreateFree() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  if (tool->_tool._type != GBToolTypePlotter) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBToolPlotterCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBToolPlotterFree(&tool);
  if (tool != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBToolPlotterFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBToolPlotterCreateFree OK\n");
}

void UnitTestGBToolPlotterDrawPoint() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBPixel red = GBColorRed;
  GBInkSolid* ink = GBInkSolidCreate(&red);
  VecFloat* pos = VecFloatCreate(3);
  VecSet(pos, 0, 4.0); VecSet(pos, 1, 4.0); VecSet(pos, 2, 0.0);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreatePoint(pos, &eye, &hand, tool, ink, layer);
  GSetAppend(&(pod->_handPoints), VecClone(pos));
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 255,0,0,255, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawPoint.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  GBEyeOrthoFree(&eye);
  VecFree(&pos);
  printf("UnitTestGBToolPlotterDrawPoint OK\n");
}

void UnitTestGBToolPlotterDrawFacoid() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBPixel blue = GBColorBlue;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  Facoid* facoid = FacoidCreate(2);
  Shapoid* shap = (Shapoid*)facoid;
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 7.0); VecSet(&v, 1, 4.0);
  ShapoidScale(shap, (VecFloat*)&v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 4.0);
  ShapoidTranslate(shap, (VecFloat*)&v);
  ShapoidRotStart(shap, PBMATH_QUARTERPI);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreateShapoid(shap, &eye, &hand, tool, ink, layer);
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawFacoid.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  ShapoidFree(&facoid);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBToolPlotterDrawFacoid OK\n");
}

void UnitTestGBToolPlotterDrawPyramidoid() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBPixel blue = GBColorBlue;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  Pyramidoid* pyramidoid = PyramidoidCreate(2);
  Shapoid* shap = (Shapoid*)pyramidoid;
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 7.0); VecSet(&v, 1, 4.0);
  ShapoidScale(shap, (VecFloat*)&v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 4.0);
  ShapoidTranslate(shap, (VecFloat*)&v);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreateShapoid(shap, &eye, &hand, tool, ink, layer);
  GSetAppend(&(pod->_handShapoids), shap);
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char checka[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      checka[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      checka[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      checka[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      checka[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawPyramidoid.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBToolPlotterDrawPyramidoid OK\n");
}

void UnitTestGBToolPlotterDrawSpheroid() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBPixel blue = GBColorBlue;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  Spheroid* spheroid = SpheroidCreate(2);
  Shapoid* shap = (Shapoid*)spheroid;
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 10.0); VecSet(&v, 1, 8.0);
  ShapoidScale(shap, (VecFloat*)&v);
  VecSet(&v, 0, 5.0); VecSet(&v, 1, 5.0);
  ShapoidTranslate(shap, (VecFloat*)&v);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreateShapoid(shap, &eye, &hand, tool, ink, layer);
  GSetAppend(&(pod->_handShapoids), shap);
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char checka[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      checka[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      checka[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      checka[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      checka[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawSpheroid.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBToolPlotterDrawSpheroid OK\n");
}

void UnitTestGBToolPlotterDrawFacoid3D() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBLayerSetStackPos(layer, GBLayerStackPosInside);
  GBLayerSetBlendMode(layer, GBLayerBlendModeOver);
  GBPixel blue = GBColorBlue;
  blue._rgba[GBPixelAlpha] = 10;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  Facoid* facoid = FacoidCreate(3);
  Shapoid* shap = (Shapoid*)facoid;
  VecFloat3D v = VecFloatCreateStatic3D();
  VecSet(&v, 0, 7.0); VecSet(&v, 1, 4.0); VecSet(&v, 2, 4.0);
  ShapoidScale(shap, (VecFloat*)&v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 4.0); VecSet(&v, 2, 0.0);
  ShapoidTranslate(shap, (VecFloat*)&v);
  ShapoidRotYStart(shap, PBMATH_QUARTERPI);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreateShapoid(shap, &eye, &hand, tool, ink, layer);
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char checka[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,235,20, 0,0,195,60, 
    0,0,195,60, 0,0,205,50, 0,0,215,40, 0,0,235,20, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,235,20, 0,0,195,60, 
    0,0,195,60, 0,0,205,50, 0,0,215,40, 0,0,235,20, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,235,20, 0,0,195,60, 
    0,0,195,60, 0,0,205,50, 0,0,215,40, 0,0,235,20, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,235,20, 0,0,195,60, 
    0,0,195,60, 0,0,205,50, 0,0,215,40, 0,0,235,20, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      checka[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      checka[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      checka[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      checka[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawFacoid3D.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  ShapoidFree(&facoid);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBToolPlotterDrawFacoid3D OK\n");
}

void UnitTestGBToolPlotterDrawSCurve() {
  GBToolPlotter* tool = GBToolPlotterCreate();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GBSurface* surf = (GBSurface*)GBSurfaceImageCreate(&dim);
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBLayerSetStackPos(layer, GBLayerStackPosInside);
  GBLayerSetBlendMode(layer, GBLayerBlendModeOver);
  GBPixel blue = GBColorBlue;
  blue._rgba[GBPixelAlpha] = 10;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  SCurve* curve = SCurveCreate(3, 3, 1);
  VecFloat3D v = VecFloatCreateStatic3D();
  SCurveSetCtrl(curve, 0, (VecFloat*)&v);
  VecSet(&v, 0, 10.0); VecSet(&v, 1, 10.0); VecSet(&v, 2, 10.0);
  SCurveSetCtrl(curve, 1, (VecFloat*)&v);
  VecSet(&v, 0, 10.0); VecSet(&v, 1, 0.0); VecSet(&v, 2, -10.0);
  SCurveSetCtrl(curve, 2, (VecFloat*)&v);
  VecSet(&v, 0, 0.0); VecSet(&v, 1, 10.0); VecSet(&v, 2, 0.0);
  SCurveSetCtrl(curve, 3, (VecFloat*)&v);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBObjPod* pod = 
    GBObjPodCreateSCurve(curve, &eye, &hand, tool, ink, layer);
  GBToolPlotterDraw(tool, pod);
  GBSurfaceUpdate(surf);
  unsigned char checka[400] = {
    0,0,245,10, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,235,20, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,245,10, 0,0,245,10, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,245,10, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,245,10, 
    0,0,245,10, 0,0,245,10, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,215,40, 0,0,195,60, 0,0,245,10, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,245,10, 
    0,0,245,10, 0,0,245,10, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,235,20, 0,0,245,10, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,245,10, 0,0,245,10, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,235,20, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      checka[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      checka[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      checka[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      checka[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBToolPlotterDraw failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBSurfaceImageSetFileName((GBSurfaceImage*)surf, 
    "./GBToolPlotterDrawSCurve.tga");
  GBSurfaceImageSave((GBSurfaceImage*)surf);
  GBObjPodFree(&pod);
  GBToolPlotterFree(&tool);
  GBSurfaceImageFree((GBSurfaceImage**)&surf);
  GBInkSolidFree(&ink);
  SCurveFree(&curve);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBToolPlotterDrawSCurve OK\n");
}

void UnitTestGBToolPlotter() {
  UnitTestGBToolPlotterCreateFree();
  UnitTestGBToolPlotterDrawPoint();
  UnitTestGBToolPlotterDrawFacoid();
  UnitTestGBToolPlotterDrawPyramidoid();
  UnitTestGBToolPlotterDrawSpheroid();
  UnitTestGBToolPlotterDrawFacoid3D();
  UnitTestGBToolPlotterDrawSCurve();

  printf("UnitTestGBToolPlotter OK\n");
}

void UnitTestGBToolCreateFree() {
  GBTool tool = GBToolCreateStatic(GBToolTypePlotter);
  if (tool._type != GBToolTypePlotter) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBToolCreateStatic failed");
    PBErrCatch(GenBrushErr);
  }
  GBToolFreeStatic(&tool);
  printf("UnitTestGBToolCreateFree OK\n");
}

void UnitTestGBToolGetSet() {
  GBTool tool = GBToolCreateStatic(GBToolTypePlotter);
  if (GBToolGetType(&tool) != GBToolTypePlotter) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBToolGetType failed");
    PBErrCatch(GenBrushErr);
  }
  GBToolFreeStatic(&tool);
  printf("UnitTestGBToolGetSet OK\n");
}

void UnitTestGBTool() {
  UnitTestGBToolCreateFree();
  UnitTestGBToolGetSet();
  UnitTestGBToolPlotter();
  printf("UnitTestGBTool OK\n");
}

void UnitTestGBInkSolidCreateFree() {
  GBPixel green = GBColorGreen;
  GBInkSolid* ink = GBInkSolidCreate(&green);
  if (memcmp(&(ink->_color), &green, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkSolidCreate failed");
    PBErrCatch(GenBrushErr);
  }
  if (ink->_ink._type != GBInkTypeSolid) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkSolidCreate failed");
    PBErrCatch(GenBrushErr);
  }
  GBInkSolidFree(&ink);
  if (ink != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkSolidFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGBInkSolidCreateFree OK\n");
}

void UnitTestGBInkSolidGetSet() {
  GBPixel green = GBColorGreen;
  GBInkSolid* ink = GBInkSolidCreate(&green);
  GBPixel col = GBInkSolidGet(ink);
  if (memcmp(&col, &green, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkSolidGet failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel blue = GBColorBlue;
  GBInkSolidSet(ink, &blue);
  if (memcmp(&(ink->_color), &blue, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkSolidSet failed");
    PBErrCatch(GenBrushErr);
  }
  col = GBInkGet(ink, NULL, NULL, NULL, NULL, NULL);
  if (memcmp(&col, &blue, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkGet failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBInkGetType(ink) != GBInkTypeSolid) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBInkGetType failed");
    PBErrCatch(GenBrushErr);
  }
  GBInkSolidFree(&ink);
  printf("UnitTestGBInkSolidGetSet OK\n");
}

void UnitTestGBInkSolid() {
  UnitTestGBInkSolidCreateFree();
  UnitTestGBInkSolidGetSet();
  printf("UnitTestGBInkSolid OK\n");
}

void UnitTestGBInk() {
  UnitTestGBInkSolid();
  printf("UnitTestGBInk OK\n");
}

void UnitTestGBObjPodCreateFree() {
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBTool tool;
  GBLayer layer;
  GBInk ink;
  VecFloat3D pos = VecFloatCreateStatic3D();
  GBObjPod* pod = 
    GBObjPodCreatePoint(&pos, eye, &hand, &tool, &ink, &layer);
  if (pod->_type != GBObjTypePoint ||
    pod->_srcPoint != (VecFloat*)&pos ||
    pod->_eyePoint == NULL ||
    GSetNbElem(&(pod->_handPoints)) != 1 ||
    GSetNbElem(&(pod->_handShapoids)) != 0 ||
    GSetNbElem(&(pod->_handSCurves)) != 0 ||
    pod->_eye != (GBEye*)eye ||
    pod->_hand != &hand ||
    pod->_tool != &tool ||
    pod->_ink != &ink ||
    pod->_layer != &layer) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodCreatePoint failed");
    PBErrCatch(GenBrushErr);
  }
  GBObjPodFree(&pod);
  if (pod != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodFree failed");
    PBErrCatch(GenBrushErr);
  }
  Facoid* facoid = FacoidCreate(2);
  pod = GBObjPodCreateShapoid(facoid, eye, &hand, &tool, &ink, &layer);
  if (pod->_type != GBObjTypeShapoid ||
    pod->_srcShapoid != (Shapoid*)facoid ||
    pod->_eyeShapoid == NULL ||
    GSetNbElem(&(pod->_handPoints)) != 0 ||
    GSetNbElem(&(pod->_handShapoids)) != 1 ||
    GSetNbElem(&(pod->_handSCurves)) != 0 ||
    pod->_eye != (GBEye*)eye ||
    pod->_hand != &hand ||
    pod->_tool != &tool ||
    pod->_ink != &ink ||
    pod->_layer != &layer) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodCreateShapoid failed");
    PBErrCatch(GenBrushErr);
  }
  GBObjPodFree(&pod);
  SCurve* curve = SCurveCreate(2, 2, 1);
  pod = GBObjPodCreateSCurve(curve, eye, &hand, &tool, &ink, &layer);
  if (pod->_type != GBObjTypeSCurve ||
    pod->_srcSCurve != curve ||
    pod->_eyeSCurve == NULL ||
    GSetNbElem(&(pod->_handPoints)) != 0 ||
    GSetNbElem(&(pod->_handShapoids)) != 0 ||
    GSetNbElem(&(pod->_handSCurves)) != 1 ||
    pod->_eye != (GBEye*)eye ||
    pod->_hand != &hand ||
    pod->_tool != &tool ||
    pod->_ink != &ink ||
    pod->_layer != &layer) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodCreateSCurve failed");
    PBErrCatch(GenBrushErr);
  }
  GBObjPodFree(&pod);
  SCurveFree(&curve);
  ShapoidFree(&facoid);
  GBEyeOrthoFree(&eye);
  printf("UnitTestGBObjPodCreateFree OK\n");
}

void UnitTestGBObjPodGetSet() {
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHandDefault* hand = GBHandDefaultCreate();
  GBTool* tool = PBErrMalloc(GenBrushErr, sizeof(GBTool));
  GBLayer* layer = PBErrMalloc(GenBrushErr, sizeof(GBLayer));
  GBInk* ink = PBErrMalloc(GenBrushErr, sizeof(GBInk));
  VecFloat2D pos = VecFloatCreateStatic2D();
  GBObjPod* pod = 
    GBObjPodCreatePoint(&pos, eye, hand, tool, ink, layer);
  if (GBObjPodGetType(pod) != GBObjTypePoint) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetType failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetObjAsPoint(pod) != (VecFloat*)&pos) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetObjAsPoint failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetHandObjAsPoints(pod) != &(pod->_handPoints)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetHandObjAsPoints failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetHandObjAsShapoids(pod) != &(pod->_handShapoids)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetHandObjAsShapoids failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetHandObjAsSCurves(pod) != &(pod->_handSCurves)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetHandObjAsSCurves failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetEyeObjAsPoint(pod) != pod->_eyePoint) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetEyeObjAsPoint failed");
    PBErrCatch(GenBrushErr);
  }
  VecFloat* posEyeB = VecFloatCreate(2);
  GBObjPodSetEyePoint(pod, posEyeB);
  if (GBObjPodGetEyeObjAsPoint(pod) != posEyeB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetEyePoint failed");
    PBErrCatch(GenBrushErr);
  }
  GBObjPodFree(&pod);
  Facoid* shap = FacoidCreate(2);
  pod = GBObjPodCreateShapoid(shap, eye, hand, tool, ink, layer);
  if (GBObjPodGetType(pod) != GBObjTypeShapoid) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetType failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetObjAsShapoid(pod) != (Shapoid*)shap) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetObjAsShapoid failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetEyeObjAsShapoid(pod) != pod->_eyeShapoid) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetEyeObjAsShapoid failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetEye(pod) != (GBEye*)eye) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetEye failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetHand(pod) != (GBHand*)hand) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetHand failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetTool(pod) != tool) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetTool failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetInk(pod) != ink) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetInk failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetLayer(pod) != layer) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodGetLayer failed");
    PBErrCatch(GenBrushErr);
  }
  Facoid* shapEyeB = FacoidCreate(2);
  GBEyeOrtho* eyeB = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHandDefault* handB = GBHandDefaultCreate();
  GBTool* toolB = PBErrMalloc(GenBrushErr, sizeof(GBTool));
  GBLayer* layerB = PBErrMalloc(GenBrushErr, sizeof(GBLayer));
  GBInk* inkB = PBErrMalloc(GenBrushErr, sizeof(GBInk));
  GBObjPodSetEyeShapoid(pod, shapEyeB);
  if (GBObjPodGetEyeObjAsShapoid(pod) != (Shapoid*)shapEyeB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetEyeShap failed");
    PBErrCatch(GenBrushErr);
  }
  GBObjPodSetEye(pod, eyeB);
  GBObjPodSetHand(pod, handB);
  GBObjPodSetTool(pod, toolB);
  GBObjPodSetInk(pod, inkB);
  GBObjPodSetLayer(pod, layerB);
  if (GBObjPodGetEye(pod) != (GBEye*)eyeB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetEye failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetHand(pod) != (GBHand*)handB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetHand failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetTool(pod) != toolB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetTool failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetInk(pod) != inkB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetInk failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBObjPodGetLayer(pod) != layerB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBObjPodSetLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBEyeOrthoFree(&eye);
  GBHandDefaultFree(&hand);
  free(tool);
  free(ink);
  free(layer);
  GBEyeOrthoFree(&eyeB);
  GBHandDefaultFree(&handB);
  free(toolB);
  free(inkB);
  free(layerB);
  ShapoidFree(&shap);
  GBObjPodFree(&pod);
  printf("UnitTestGBObjPodGetSet OK\n");
}

void UnitTestGBObjPod() {
  UnitTestGBObjPodCreateFree();
  UnitTestGBObjPodGetSet();
  
  printf("UnitTestGBObjPod OK\n");
}

void UnitTestGenBrushCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 800); VecSet(&dim, 1, 600); 
  GenBrush* gb = GBCreateImage(&dim);
  if (VecIsEqual(GBSurfaceDim(gb->_surf), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBCreateImage failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurfaceGetType(gb->_surf) != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBCreateImage failed");
    PBErrCatch(GenBrushErr);
  }
  if (GSetNbElem(&(gb->_pods)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBCreateImage failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  if (gb != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFree failed");
    PBErrCatch(GenBrushErr);
  }
  printf("UnitTestGenBrushCreateFree OK\n");
}

void UnitTestGenBrushGetSet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GenBrush* gb = GBCreateImage(&dim);
  if (VecIsEqual(GBDim(gb), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBDim failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D d = GBGetDim(gb);
  if (VecIsEqual(&d, &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetDim failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBSurf(gb) != gb->_surf) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurf failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBFinalPixels(gb) != gb->_surf->_finalPix) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFinalPix failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBGetType(gb) != GBSurfaceTypeImage) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetType failed");
    PBErrCatch(GenBrushErr);
  }
  VecFloat2D v = VecFloatCreateStatic2D();
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBTool tool;
  GBLayer layer;
  GBInk ink;
  GSetAppend(&(gb->_pods), GBObjPodCreatePoint(&v, &eye, &hand, 
    &tool, &ink, &layer));
  if (GBGetNbPod(gb) != 1) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetNbPod failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel black = GBColorBlack;
  GBSetBgColor(gb, &black);
  if (memcmp(&(gb->_surf->_bgColor), &black, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  if (memcmp(GBBgColor(gb), &black, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel bgCol = GBGetBgColor(gb);
  if (memcmp(&(gb->_surf->_bgColor), &bgCol, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetBgColor failed");
    PBErrCatch(GenBrushErr);
  }
  char* fileName = "./";
  GBSetFileName(gb, fileName);
  if (strcmp(((GBSurfaceImage*)(gb->_surf))->_fileName, 
    fileName) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetFileName failed");
    PBErrCatch(GenBrushErr);
  }
  if (strcmp(GBFileName(gb), fileName) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFileName failed");
    PBErrCatch(GenBrushErr);
  }
  VecShort2D p = VecShortCreateStatic2D();
  VecSet(&p, 0, 1); VecSet(&p, 1, 2);
  if (GBFinalPixel(gb, &p) != gb->_surf->_finalPix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBFinalPixelSafe(gb, &p) != gb->_surf->_finalPix + 9) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, -2);
  if (GBFinalPixelSafe(gb, &p) != NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, 2);
  GBPixel white = GBColorWhite;
  GBSetFinalPixel(gb, &p, &white);
  if (memcmp(GBFinalPixel(gb, &p), &white, 
    sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel pix = GBGetFinalPixel(gb, &p);
  if (memcmp(&pix, &white, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetFinalPixel failed");
    PBErrCatch(GenBrushErr);
  }
  GBPixel blue = GBColorBlue;
  GBSetFinalPixelSafe(gb, &p, &blue);
  pix = GBGetFinalPixel(gb, &p);
  if (memcmp(&pix, &blue, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, -2);
  GBSetFinalPixelSafe(gb, &p, &white);
  pix = GBGetFinalPixelSafe(gb, &p);
  GBPixel transparent = GBColorTransparent;
  if (memcmp(&pix, &transparent, sizeof(GBPixel)) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetFinalPixelSafe failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBArea(gb) != 12) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBArea failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, 2); 
  if (GBIsPosInside(gb, &p) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 10); VecSet(&p, 1, 2); 
  if (GBIsPosInside(gb, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  VecSet(&p, 0, 1); VecSet(&p, 1, -2); 
  if (GBIsPosInside(gb, &p) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBIsPosInside failed");
    PBErrCatch(GenBrushErr);
  }
  if (GBLayers(gb) != &(gb->_surf->_layers)) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSurfaceLayers failed");
    PBErrCatch(GenBrushErr);
  }
  GBEyeOrthoFree(&eye);
  GBFree(&gb);
  printf("UnitTestGenBrushGetSet OK\n");
}

void UnitTestGenBrushUpdate() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  GBSurface* surf = GBSurf(gb);
  GBLayer* layer = GBAddLayer(gb, &dim);
  GBToolPlotter* tool = GBToolPlotterCreate();
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBPixel blue = GBColorBlue;
  GBInkSolid* ink = GBInkSolidCreate(&blue);
  Facoid* facoid = FacoidCreate(2);
  Shapoid* shap = (Shapoid*)facoid;
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 7.0); VecSet(&v, 1, 4.0);
  ShapoidScale(shap, (VecFloat*)&v);
  VecSet(&v, 0, 2.0); VecSet(&v, 1, 4.0);
  ShapoidTranslate(shap, (VecFloat*)&v);
  GBEyeOrtho* eye = GBEyeOrthoCreate(GBEyeOrthoViewFront);
  GBHand hand = GBHandCreateStatic(GBHandTypeDefault);
  GBAddShapoid(gb, shap, &eye, &hand, tool, ink, layer);
  GBUpdate(gb);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,255,255, 0,0,255,255, 0,0,255,255, 
    0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBUpdate failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBToolPlotterFree(&tool);
  GBInkSolidFree(&ink);
  ShapoidFree(&shap);
  GBEyeOrthoFree(&eye);
  GBFree(&gb);
  printf("UnitTestGenBrushUpdate OK\n");
}

void UnitTestGenBrushRender() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  GBSurface* surf = GBSurf(gb);
  GBLayer* layers[4] = {NULL};
  VecSet(&dim, 0, 5); VecSet(&dim, 1, 5); 
  for (int iLayer = 0; iLayer < 4; ++iLayer) {
    layers[iLayer] = GBSurfaceAddLayer(surf, &dim);
    GBLayerSetBlendMode(layers[iLayer], GBLayerBlendModeOver);
  }
  GBLayerSetStackPos(layers[1], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[2], GBLayerStackPosInside);
  GBLayerSetStackPos(layers[3], GBLayerStackPosFg);
  VecShort2D pos = VecShortCreateStatic2D();
  VecSet(&pos, 0, 1); VecSet(&pos, 1, 1); 
  GBLayerSetPos(layers[0], &pos);
  VecSet(&pos, 0, 3); VecSet(&pos, 1, 3); 
  GBLayerSetPos(layers[1], &pos);
  VecSet(&pos, 0, 4); VecSet(&pos, 1, 4); 
  GBLayerSetPos(layers[2], &pos);
  VecSet(&pos, 0, 7); VecSet(&pos, 1, 7); 
  GBLayerSetPos(layers[3], &pos);
  VecSetNull(&pos);
  GBPixel col;
  float depth;
  do {
    col = GBColorGreen;
    depth = 0.0;
    GBLayerAddPixel(layers[0], &pos, &col, depth);
    col._rgba[GBPixelRed] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = 0;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 1) * 30;
    depth = VecGet(&pos, 0);
    GBLayerAddPixel(layers[1], &pos, &col, depth);
    col._rgba[GBPixelRed] = 0;
    col._rgba[GBPixelGreen] = VecGet(&pos, 0) * 30;
    col._rgba[GBPixelBlue] = VecGet(&pos, 1) * 30;
    col._rgba[GBPixelAlpha] = 255 - VecGet(&pos, 0) * 30;
    depth = VecGet(&pos, 1);
    GBLayerAddPixel(layers[2], &pos, &col, depth);
    col = GBColorBlue;
    depth = 0.0;
    GBLayerAddPixel(layers[3], &pos, &col, depth);
  } while (VecStep(&pos, &dim));
  GBUpdate(gb);
  GBSetFileName(gb, "./UnitTestGenBrushRender.tga");
  GBRender(gb);
  GBFree(&gb);
  printf("UnitTestGenBrushRender OK\n");
}

void UnitTestGenBrushAddRemoveLayer() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GenBrush* gb = GBCreateImage(&dim);
  GBLayer* layerA = GBAddLayer(gb, &dim);
  if (layerA == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  if (GSetNbElem(GBSurfaceLayers(GBSurf(gb))) != 1) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  if (VecIsEqual(GBLayerDim(layerA), &dim) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBAddLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBLayer* layerB = GBAddLayer(gb, &dim);
  GBRemoveLayer(gb, layerA);
  if ((GBLayer*)(GBSurf(gb)->_layers._head->_data) != layerB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemoveLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  printf("UnitTestGenBrushAddRemoveLayer OK\n");
}

void UnitTestGenBrushGetLayerNbLayer() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GenBrush* gb = GBCreateImage(&dim);
  GBLayer* layers[3] = {NULL};
  for (int iLayer = 0; iLayer< 3; ++iLayer)
    layers[iLayer] = GBAddLayer(gb, &dim);
  if (GBGetNbLayer(gb) != 3) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBGetNbLayer failed");
    PBErrCatch(GenBrushErr);
  }
  for (int iLayer = 0; iLayer< 3; ++iLayer) {
    if (GBGetLayer(gb, iLayer) != layers[iLayer]) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBGetLayer failed");
      PBErrCatch(GenBrushErr);
    }
  }
  GBFree(&gb);
  printf("UnitTestGenBrushGetLayer OK\n");
}

void UnitTestGenBrushSetLayerPos() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 4); VecSet(&dim, 1, 3); 
  GenBrush* gb = GBCreateImage(&dim);
  GBLayer* layers[3] = {NULL};
  for (int iLayer = 0; iLayer< 3; ++iLayer)
    layers[iLayer] = GBAddLayer(gb, &dim);
  GBSetLayerPos(gb, layers[2], 0);
  GBSetLayerPos(gb, layers[0], 2);
  if (GBGetLayer(gb, 0) != layers[2] ||
    GBGetLayer(gb, 1) != layers[1] ||
    GBGetLayer(gb, 2) != layers[0] ||
    GBLayerIsModified(layers[0]) != true ||
    GBLayerIsModified(layers[1]) != true ||
    GBLayerIsModified(layers[2]) != true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetLayerPos failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  printf("UnitTestGenBrushSetLayerPos OK\n");
}

void UnitTestGenBrushAddLayerFromFile() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  GBSurface* surf = GBSurf(gb);
  GBLayer* layer = GBAddLayerFromFile(gb, "./ImageRef.tga");
  (void)layer;
  GBPixel transparent = GBColorTransparent;
  GBSurfaceSetBgColor(surf, &transparent);
  GBSurfaceUpdate(surf);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,255,0,255, 0,255,0,255, 0,0,0,255, 0,30,0,255, 
    0,60,0,255, 0,90,0,255, 0,120,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 26,30,0,255, 0,0,0,255, 4,34,0,255, 
    7,67,0,255, 11,101,0,255, 120,184,120,255, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 46,60,0,255, 0,0,30,255, 7,34,26,255, 
    14,67,23,255, 21,101,19,255, 120,184,136,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 148,90,90,255, 0,0,60,255, 11,34,53,255, 
    21,67,46,255, 32,101,39,255, 120,184,152,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 184,120,120,255, 0,0,90,255, 14,34,79,255, 
    28,67,69,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,120,255, 30,56,136,255, 
    60,106,152,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBAddLayerFromFile failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBFree(&gb);
  printf("UnitTestGenBrushAddLayerFromFile OK\n");
}

void UnitTestGenBrushAddRemoveObj() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  VecFloat2D posA = VecFloatCreateStatic2D();
  VecFloat2D posB = VecFloatCreateStatic2D();
  GBEye eyeA = GBEyeCreateStatic(GBEyeTypeOrtho);
  GBEye eyeB = GBEyeCreateStatic(GBEyeTypeOrtho);
  GBHand handA = GBHandCreateStatic(GBHandTypeDefault);
  GBHand handB = GBHandCreateStatic(GBHandTypeDefault);
  GBTool toolA;
  GBTool toolB;
  GBLayer layerA;
  GBLayer layerB;
  GBInk inkA;
  GBInk inkB;
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolA, &inkA, &layerA);
  GBAddPoint(gb, &posB, &eyeA, &handA, &toolA, &inkB, &layerA);
  if (GBGetNbPod(gb) != 2 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
    (VecFloat*)&posA ||
    ((GBObjPod*)(gb->_pods._head->_next->_data))->_srcPoint != 
    (VecFloat*)&posB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBAddPoint failed");
    PBErrCatch(GenBrushErr);
  }
  GBRemovePod(gb, &posA, NULL, NULL, NULL, NULL, NULL);
  if (GBGetNbPod(gb) != 1 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
      (VecFloat*)&posB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolA, &inkA, &layerA);
  GBRemovePod(gb, NULL, &eyeA, NULL, NULL, NULL, NULL);
  if (GBGetNbPod(gb) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolA, &inkA, &layerA);
  GBAddPoint(gb, &posB, &eyeB, &handA, &toolA, &inkA, &layerA);
  GBRemovePod(gb, NULL, &eyeA, &handA, NULL, NULL, NULL);
  if (GBGetNbPod(gb) != 1 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
      (VecFloat*)&posB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolB, &inkA, &layerA);
  GBRemovePod(gb, NULL, NULL, NULL, &toolB, NULL, NULL);
  if (GBGetNbPod(gb) != 1 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
      (VecFloat*)&posB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBAddPoint(gb, &posA, &eyeA, &handB, &toolB, &inkA, &layerB);
  GBRemovePod(gb, NULL, NULL, NULL, NULL, NULL, &layerB);
  if (GBGetNbPod(gb) != 1 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
      (VecFloat*)&posB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBRemovePod(gb, NULL, NULL, NULL, NULL, NULL, NULL);
  if (GBGetNbPod(gb) != 0) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBAddPoint(gb, &posA, &eyeA, &handB, &toolB, &inkA, &layerA);
  GBAddPoint(gb, &posB, &eyeB, &handB, &toolB, &inkB, &layerB);
  GBRemovePod(gb, NULL, NULL, NULL, NULL, &inkB, NULL);
  if (GBGetNbPod(gb) != 1 ||
    ((GBObjPod*)(gb->_pods._head->_data))->_srcPoint != 
      (VecFloat*)&posA) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBRemovePod failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  GBEyeFreeStatic(&eyeA);
  GBEyeFreeStatic(&eyeB);
  printf("UnitTestGenBrushAddRemoveObj OK\n");
}

void UnitTestGenBrushSetPod() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  VecFloat2D posA = VecFloatCreateStatic2D();
  VecFloat2D posB = VecFloatCreateStatic2D();
  GBEye eyeA = GBEyeCreateStatic(GBEyeTypeOrtho);
  GBEye eyeB = GBEyeCreateStatic(GBEyeTypeOrtho);
  GBHand handA = GBHandCreateStatic(GBHandTypeDefault);
  GBHand handB = GBHandCreateStatic(GBHandTypeDefault);
  GBTool toolA;
  GBTool toolB;
  GBLayer layerA;
  GBLayer layerB;
  GBInk inkA;
  GBInk inkB;
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolA, &inkA, &layerA);
  GBAddPoint(gb, &posB, &eyeA, &handB, &toolB, &inkA, &layerB);
  GBSetPodEye(gb, &eyeB, &posA, NULL, NULL, NULL, NULL, NULL);
  if (((GBObjPod*)(gb->_pods._head->_data))->_eye != &eyeB) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetPodEye failed");
    PBErrCatch(GenBrushErr);
  }
  GBSetPodHand(gb, &handA, NULL, NULL, NULL, NULL, NULL, &layerB);
  if (((GBObjPod*)(gb->_pods._head->_next->_data))->_hand != &handA) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetPodHand failed");
    PBErrCatch(GenBrushErr);
  }
  GBSetPodTool(gb, &toolA, NULL, NULL, &handA, NULL, NULL, NULL);
  if (((GBObjPod*)(gb->_pods._head->_data))->_tool != &toolA ||
    ((GBObjPod*)(gb->_pods._head->_next->_data))->_tool != &toolA) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetPodTool failed");
    PBErrCatch(GenBrushErr);
  }
  GBSetPodInk(gb, &inkA, NULL, NULL, NULL, NULL, &inkB, NULL);
  if (((GBObjPod*)(gb->_pods._head->_data))->_ink != &inkA ||
    ((GBObjPod*)(gb->_pods._head->_next->_data))->_ink != &inkA) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetPodTool failed");
    PBErrCatch(GenBrushErr);
  }
  GBSetPodLayer(gb, &layerA, &posB, NULL, NULL, &toolA, NULL, NULL);
  if (((GBObjPod*)(gb->_pods._head->_next->_data))->_layer != &layerA) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBSetPodLayer failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  GBEyeFreeStatic(&eyeA);
  GBEyeFreeStatic(&eyeB);
  printf("UnitTestGenBrushSetPod OK\n");
}

void UnitTestGenBrushFlush() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  GBSurface* surf = GBSurf(gb);
  GBLayer* layer = GBSurfaceAddLayer(surf, &dim);
  GBLayerSetModified(layer, false);
  GBPixel blue = GBColorBlue;
  GBSurfaceSetBgColor(surf, &blue);
  GBFlush(gb);
  if (GBLayerIsModified(layer) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBSurfaceFlush failed");
    PBErrCatch(ShapoidErr);
  }
  for (int iPix = GBSurfaceArea(surf); iPix--;)
    if (memcmp(surf->_finalPix + iPix, &blue, sizeof(GBPixel)) != 0) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBSurfaceFlush failed");
      PBErrCatch(ShapoidErr);
    }
  GBFree(&gb);
  printf("UnitTestGenBrushFlush OK\n");
}

void UnitTestGenBrushTouchLayers() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 10); VecSet(&dim, 1, 10); 
  GenBrush* gb = GBCreateImage(&dim);
  VecFloat2D posA = VecFloatCreateStatic2D();
  VecFloat2D posB = VecFloatCreateStatic2D();
  GBEye eyeA = GBEyeCreateStatic(GBEyeTypeOrtho);
  GBHand handA = GBHandCreateStatic(GBHandTypeDefault);
  GBHand handB = GBHandCreateStatic(GBHandTypeDefault);
  GBTool toolA;
  GBTool toolB;
  GBLayer* layerA = GBAddLayer(gb, &dim);
  GBLayer* layerB = GBAddLayer(gb, &dim);
  GBInk inkA;
  GBAddPoint(gb, &posA, &eyeA, &handA, &toolA, &inkA, layerA);
  GBAddPoint(gb, &posB, &eyeA, &handB, &toolB, &inkA, layerB);
  GBSurfaceSetLayersModified(GBSurf(gb), false);
  GBNotifyChangeFromObj(gb, &posA);
  if (GBLayerIsModified(layerA) == false ||
    GBLayerIsModified(layerB) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBNotifyChangeFromObj failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceSetLayersModified(GBSurf(gb), false);
  GBNotifyChangeFromEye(gb, &eyeA);
  if (GBLayerIsModified(layerA) == false ||
    GBLayerIsModified(layerB) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBNotifyChangeFromEye failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceSetLayersModified(GBSurf(gb), false);
  GBNotifyChangeFromHand(gb, &handA);
  if (GBLayerIsModified(layerA) == false ||
    GBLayerIsModified(layerB) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBNotifyChangeFromHand failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceSetLayersModified(GBSurf(gb), false);
  GBNotifyChangeFromTool(gb, &toolA);
  if (GBLayerIsModified(layerA) == false ||
    GBLayerIsModified(layerB) == true) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBNotifyChangeFromTool failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurfaceSetLayersModified(GBSurf(gb), false);
  GBNotifyChangeFromInk(gb, &inkA);
  if (GBLayerIsModified(layerA) == false ||
    GBLayerIsModified(layerB) == false) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBNotifyChangeFromInk failed");
    PBErrCatch(GenBrushErr);
  }
  GBFree(&gb);
  GBEyeFreeStatic(&eyeA);
  printf("UnitTestGenBrushTouchLayers OK\n");
}

void UnitTestGenBrushCreateFromFile() {
  char* fileName = "./ImageRef.tga";
  GenBrush* gb = GBCreateFromFile(fileName);
  if (gb == NULL) {
    GenBrushErr->_type = PBErrTypeUnitTestFailed;
    sprintf(GenBrushErr->_msg, "GBCreateFromFile failed");
    PBErrCatch(GenBrushErr);
  }
  GBSurface* surf = GBSurf(gb);
  unsigned char check[400] = {
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,255,0,255, 0,255,0,255, 0,255,0,255, 
    0,255,0,255, 0,255,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,255,0,255, 0,255,0,255, 0,0,0,255, 0,30,0,255, 
    0,60,0,255, 0,90,0,255, 0,120,0,255, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 26,30,0,255, 0,0,0,255, 4,34,0,255, 
    7,67,0,255, 11,101,0,255, 120,184,120,255, 0,0,0,0, 0,0,0,0, 
    0,255,0,255, 0,255,0,255, 46,60,0,255, 0,0,30,255, 7,34,26,255, 
    14,67,23,255, 21,101,19,255, 120,184,136,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 148,90,90,255, 0,0,60,255, 11,34,53,255, 
    21,67,46,255, 32,101,39,255, 120,184,152,255, 0,0,0,0, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 184,120,120,255, 0,0,90,255, 14,34,79,255, 
    28,67,69,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,120,255, 30,56,136,255, 
    60,106,152,255, 0,0,255,255, 0,0,255,255, 0,0,255,255, 0,0,0,0, 
    0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 
    0,0,255,255, 0,0,255,255, 0,0,255,255
    };
  for (int iPix = 0; iPix < GBSurfaceArea(surf); ++iPix) {
    if (surf->_finalPix[iPix]._rgba[GBPixelRed] != 
      check[iPix * 4] ||
      surf->_finalPix[iPix]._rgba[GBPixelGreen] !=
      check[iPix * 4 + 1] ||
      surf->_finalPix[iPix]._rgba[GBPixelBlue] !=
      check[iPix * 4 + 2] ||
      surf->_finalPix[iPix]._rgba[GBPixelAlpha] !=
      check[iPix * 4 + 3]) {
      ShapoidErr->_type = PBErrTypeUnitTestFailed;
      sprintf(ShapoidErr->_msg, "GBCreateFromFile failed");
      PBErrCatch(ShapoidErr);
    }
  }
  GBFree(&gb);
  printf("UnitTestGenBrushCreateFromFile OK\n");
}

void UnitTestGenBrushIsSameAs() {
  char* fileName = "./ImageRef.tga";
  GenBrush* gbA = GBCreateFromFile(fileName);
  GenBrush* gbB = GBCreateFromFile(fileName);
  if (GBIsSameAs(gbA, gbB) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(GBSurfaceDim(GBSurf(gbA)), 0, 0);
  if (GBIsSameAs(gbA, gbB) == true) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  VecSet(GBSurfaceDim(GBSurf(gbA)), 0, 10);
  GBSurfaceFinalPixels(GBSurf(gbA))->_rgba[GBPixelAlpha] = 255;
  if (GBIsSameAs(gbA, gbB) == true) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBIsSameAs failed");
    PBErrCatch(ShapoidErr);
  }
  GBFree(&gbA);
  GBFree(&gbB);
  printf("UnitTestGenBrushIsSameAs OK\n");
}

void UnitTestGenBrushAddRemovePostProcessing() {
  GenBrush* gb = GBCreateFromFile("./GBSurfaceNormalizeHueTest.tga");
  if (GBPostProcs(gb) != &(gb->_postProcs)) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBPostProcs failed");
    PBErrCatch(ShapoidErr);
  }
  GBPostProcessing* postA = GBAddPostProcess(gb, GBPPTypeNormalizeHue);
  if (gb->_postProcs._head->_data != (void*)postA) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBAddPostProcess failed");
    PBErrCatch(ShapoidErr);
  }
  if (GBGetPostProcess(gb, 0) != (void*)postA) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBGetPostProcess failed");
    PBErrCatch(ShapoidErr);
  }
  GBUpdate(gb);
  GBSurfaceImage* ref = GBSurfaceImageCreateFromFile(
    "./GBSurfaceNormalizeHueRef.tga");
  if (GBSurfaceIsSameAs(GBSurf(gb), (GBSurface*)ref) == false) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBUpdate failed");
    PBErrCatch(ShapoidErr);
  }
  GBRemovePostProcess(gb, postA);
  if (GSetNbElem(GBPostProcs(gb)) != 0) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBRemovePostProcess failed");
    PBErrCatch(ShapoidErr);
  }
  postA = GBAddPostProcess(gb, GBPPTypeNormalizeHue);
  postA = GBAddPostProcess(gb, GBPPTypeNormalizeHue);
  if (GBGetNbPostProcs(gb) != 2) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBGetNbPostProcs failed");
    PBErrCatch(ShapoidErr);
  }
  GBRemoveAllPostProcess(gb);
  if (GSetNbElem(GBPostProcs(gb)) != 0) {
    ShapoidErr->_type = PBErrTypeUnitTestFailed;
    sprintf(ShapoidErr->_msg, "GBRemoveAllPostProcess failed");
    PBErrCatch(ShapoidErr);
  }
  postA = GBAddPostProcess(gb, GBPPTypeNormalizeHue);
  GBFree(&gb);
  GBSurfaceImageFree(&ref);
  printf("UnitTestGenBrushAddRemovePostProcessing\n");
}
void UnitTestGenBrush() {
  UnitTestGenBrushCreateFree();
  UnitTestGenBrushGetSet();
  UnitTestGenBrushUpdate();
  UnitTestGenBrushRender();
  UnitTestGenBrushAddRemoveLayer();
  UnitTestGenBrushGetLayerNbLayer();
  UnitTestGenBrushSetLayerPos();
  UnitTestGenBrushUpdate();
  UnitTestGenBrushAddLayerFromFile();
  UnitTestGenBrushAddRemoveObj();
  UnitTestGenBrushSetPod();
  UnitTestGenBrushFlush();
  UnitTestGenBrushTouchLayers();
  UnitTestGenBrushCreateFromFile();
  UnitTestGenBrushIsSameAs();
  UnitTestGenBrushAddRemovePostProcessing();
  
  printf("UnitTestGenBrush OK\n");
}

void UnitTestAll() {
  UnitTestGBPixel();
  UnitTestGBLayer();
  UnitTestGBPostProcessing();
  UnitTestGBSurface();
  UnitTestGBSurfaceImage();
  UnitTestGBEye();
  UnitTestGBHand();
  UnitTestGBTool();
  UnitTestGBInk();
  UnitTestGBObjPod();
  UnitTestGenBrush();
  printf("UnitTestAll OK\n");
}

#if BUILDWITHGRAPHICLIB == 0

  int main() {
    UnitTestAll();
    // Return success code
    return 0;
  }

#elif BUILDWITHGRAPHICLIB == 1

  void UnitTestPaintSurface(GBSurface* surf, VecShort2D* dim, 
    int green) {
    // Declare a vector to memorize position in the surface
    VecShort2D pos = VecShortCreateStatic2D();
    // Set the surface to a shade of red and blue
    do {
      GBPixel pixel;
      pixel._rgba[GBPixelAlpha] = 255;
      pixel._rgba[GBPixelRed] = MIN(255, VecGet(&pos, 0));
      pixel._rgba[GBPixelGreen] = MIN(255, green);
      pixel._rgba[GBPixelBlue] = MIN(255, VecGet(&pos, 1));
      GBSurfaceSetFinalPixel(surf, &pos, &pixel);
    } while (VecStep(&pos, dim));
  }
  
  gint UnitTestGBSurfaceAppCB(gpointer data) {
    // Declare a variable to convert the data into the GBSurfaceApp
    GBSurfaceApp* GBApp = (GBSurfaceApp*)data;
    // Paint again the surface
    UnitTestPaintSurface((GBSurface*)GBApp, 
      GBSurfaceDim((GBSurface*)GBApp), 0);
    // Refresh the displayed surface
    GBSurfaceAppRefresh(GBApp);
    // Kill the app
    GBSurfaceAppClose(GBApp);
    // Return false to continue the callback chain
    return FALSE;
  }

  void UnitTestGBSurfaceApp() {
    // Declare variable ot memorize the parameters of the app
    VecShort2D dim = VecShortCreateStatic2D();
    VecSet(&dim, 0, 300); VecSet(&dim, 1, 200);
    char* title = "UnitTestGBSurfaceApp";
    // Create the app
    GenBrush* app = GBCreateApp(&dim, title);
    // Set the idle function of the surface
    GBSetIdle(app, &UnitTestGBSurfaceAppCB, 1000);
    // Paint some content on the surface
    UnitTestPaintSurface(app->_surf, &dim, 0);
    // Render the app
    bool status = GBRender(app);
    // If the render of the app failed
    if (status == false) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "GBSurfaceAppCreate failed");
      PBErrCatch(GenBrushErr);
    }
    // Free the memory used by the app
    GBFree(&app);
    printf("UnitTestGBSurfaceApp OK\n");
  }

  GtkWidget* UnitTestGBSurfaceWidgetWindow;
  gint UnitTestGBSurfaceWidgetCB(gpointer data) {
    static int green = 0;
    // Declare a variable to convert the data into the GenBrush
    GenBrush* GBWidget = (GenBrush*)data;
    // Paint again the surface
    UnitTestPaintSurface(GBWidget->_surf, 
      GBSurfaceDim(GBWidget->_surf), green);
    ++green;
    // Refresh the displayed surface
    GBRender(GBWidget);
    if (green == 255)
      gtk_window_close(GTK_WINDOW(UnitTestGBSurfaceWidgetWindow));
    // Return true to stop the callback chain
    return TRUE;
  }
  
  gboolean UnitTestGBSurfaceWidgetCloseCB(GtkWidget* widget,
    GdkEventConfigure* event, gpointer data) {
      (void)widget;(void)event;
    // Declare a variable to convert the data into the GenBrush
    GenBrush* GBWidget = (GenBrush*)data;
    // Free memory
    GBFree(&GBWidget);
    // Return false to continue the callback chain
    return FALSE;
  }
  
  void UnitTestGBSurfaceWidgetActivateCB(GtkApplication* app, 
    gpointer user_data) {
    (void)user_data;
    // Create a GTK application
    GtkWidget* window = gtk_application_window_new(app);
    UnitTestGBSurfaceWidgetWindow = window;
    // Set the title
    gtk_window_set_title(GTK_WINDOW(window), "UnitTestGBSurfaceWidget");
    // Declare a variable to memorize the size
    VecShort2D dim = VecShortCreateStatic2D();
    VecSet(&dim, 0, 300); VecSet(&dim, 1, 200); 
    // Set the size
    gtk_window_set_default_size(GTK_WINDOW(window), VecGet(&dim, 0),
      VecGet(&dim, 1));
    // Avoid window resizing
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    // Create the GenBrush with a GBSurfaceWidget
    GenBrush* GBWidget = GBCreateWidget(&dim);
    // Get the widget of the drawing area
    GtkWidget* drawingArea = GBGetGtkWidget(GBWidget);
    // Add the widget to the window
    gtk_container_add(GTK_CONTAINER(window), drawingArea);
    // Connect to the delete event
    g_signal_connect(window, "delete-event",
      G_CALLBACK(UnitTestGBSurfaceWidgetCloseCB), GBWidget);
    // Connect the idle function
    g_timeout_add(40, UnitTestGBSurfaceWidgetCB, GBWidget);
    // Display the window
    gtk_widget_show_all(window);
  }

  void UnitTestGBSurfaceWidget(int argc, char** argv) {
    // Create a GTK application
    GtkApplication* app = 
      gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
    // Connect the activate callback
    g_signal_connect(app, "activate", 
      G_CALLBACK(UnitTestGBSurfaceWidgetActivateCB), NULL);
    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // If the application failed
    if (status != 0) {
      GenBrushErr->_type = PBErrTypeUnitTestFailed;
      sprintf(GenBrushErr->_msg, "Application failed");
      PBErrCatch(GenBrushErr);
    }
    // Unreference the application
    g_object_unref(app);
    printf("UnitTestGBSurfaceWidget OK\n");
  }

  void UnitTestAllGTK(int argc, char** argv) {
    UnitTestGBSurfaceApp();
    UnitTestGBSurfaceWidget(argc, argv);
    printf("UnitTestAllGTK OK\n");
  }

  int main(int argc, char** argv) {
    UnitTestAll();
    UnitTestAllGTK(argc, argv);
    // Return success code
    return 0;
  }

#endif

