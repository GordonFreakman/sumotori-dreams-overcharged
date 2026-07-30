#include "game_runtime.h"

#include "decomp.h"

#include <new>
#include <string.h>

#pragma intrinsic(memset)

DECOMP_SIZE_ASSERT(GameBox, 0xfc);
DECOMP_SIZE_ASSERT(GameBoxPoint, 0x10);
DECOMP_SIZE_ASSERT(GameBoxPointReference, 0x08);
DECOMP_SIZE_ASSERT(GameBoxFace, 0x24);

// GLOBAL: SUMO 0x00453708
// GLOBAL: EDITOR 0x00453708
SumoS32 g_boxFaceIndices[30] = {
  2, 3, 7, 6, -1,
  3, 1, 5, 7, -1,
  0, 1, 3, 2, -1,
  0, 2, 6, 4, -1,
  1, 0, 4, 5, -1,
  6, 7, 5, 4, -1
};

// FUNCTION: SUMO 0x004087b4
// FUNCTION: EDITOR 0x004087d6
void GameBox::ReserveGeometry(SumoS32 pointCapacity,
                              SumoS32 referenceCapacity,
                              SumoS32 faceCapacity)
{
  pointsBegin = (GameBoxPoint*) operator new(pointCapacity << 6);
  pointReferencesBegin =
      (GameBoxPointReference*) operator new(referenceCapacity << 5);
  facesBegin = (GameBoxFace*) operator new(faceCapacity * 144);
}

// FUNCTION: SUMO 0x004088dc
// FUNCTION: EDITOR 0x004088fe
void GameBox::InitializeGeometry(Vector3* sourcePoints,
                                 SumoS32 pointCount,
                                 SumoS32* faceIndices,
                                 SumoS32 indexCount)
{
  ReserveGeometry(512, 2048, 512);

  GameBoxPoint* point = pointsBegin;
  SumoS32 remainingPoints = pointCount;
  if (remainingPoints > 0) {
    do {
      point->position = *sourcePoints;
      point->flag0D = 0;
      ++point;
      ++sourcePoints;
      --remainingPoints;
    } while (remainingPoints != 0);
  }
  pointsEnd = point;

  GameBoxPointReference* reference = pointReferencesBegin;
  GameBoxFace* face = facesBegin;
  SumoS32 facePointCount = 0;
  SumoS32* cursor = faceIndices;
  SumoS32* end = faceIndices + indexCount;
  while (cursor < end) {
    if (*cursor < 0) {
      face->pointCount = facePointCount;
      face->state = 1.0f;
      face->pointReferences = reference - facePointCount;
      face->preserveState = 1;
      UpdateFacePlane(*face);
      ++cursor;
      ++face;
      facePointCount = 0;
    }
    else {
      reference->index = *cursor;
      reference->point = pointsBegin + *cursor;
      ++facePointCount;
      ++reference;
      ++cursor;
    }
  }

  pointReferencesEnd = reference;
  facesEnd = face;
}

// FUNCTION: SUMO 0x00408d15
// FUNCTION: EDITOR 0x00408d37
void GameBox::ResetStorage()
{
  memset(this, 0, sizeof(GameBox));
  unknownD4 = 0;
  unknownD8 = 0;
  unknownDC = 0;
}

// FUNCTION: SUMO 0x00408d35
// FUNCTION: EDITOR 0x00408d57
GameBox* CreateGameBox(Vector3 halfSize, Vector3 position,
                       SumoS32 type, SumoF32 defaultValue)
{
  GameBox* box = g_gameBoxesEnd;
  box->ResetStorage();

  Vector3 points[8];
  SumoS32 index = 0;
  do {
    Vector3 point = halfSize;
    if ((index & 1) != 0) {
      point.x *= g_gameBoxYScale;
    }
    if ((index & 2) == 0) {
      point.y *= g_gameBoxYScale;
    }
    if ((index & 4) != 0) {
      point.z *= g_gameBoxYScale;
    }
    points[index] = point;
    ++index;
  } while (index < 8);

  box->InitializeGeometry(points, 8, g_boxFaceIndices, 30);
  box->InitializePhysics();
  box->position = position;
  box->type = type;
  box->defaultValue = defaultValue;
  ++g_gameBoxesEnd;
  return box;
}

// FUNCTION: SUMO 0x00408ddf
// FUNCTION: EDITOR 0x00408e01
void InitializeClipBoxes()
{
  g_cutPlaneBox.ReserveGeometry(512, 2048, 512);
  g_clipScratchBox.ReserveGeometry(512, 2048, 512);
}
