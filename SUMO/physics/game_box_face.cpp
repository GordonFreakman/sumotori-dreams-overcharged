#include "game_runtime.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GameBoxFace, 0x24);

// FUNCTION: SUMO 0x004087f0
// FUNCTION: EDITOR 0x00408812
void GameBox::UpdateFacePlane(GameBoxFace& face)
{
  Vector3 initialNormal;
  initialNormal.x = 0.0f;
  initialNormal.y = 0.0f;
  initialNormal.z = 0.0f;
  Vector3 normal = initialNormal;

  SumoS32 index = 2;
  if (face.pointCount > 2) {
    GameBoxPointReference* references = face.pointReferences;
    do {
      normal.AddInline(
          (references[index].point->position -
           references[0].point->position).Cross(
              references[index - 1].point->position -
              references[0].point->position));
      ++index;
    } while (index < face.pointCount);
  }

  face.normal = normal;
  Vector3* basePoint = &face.pointReferences[0].point->position;
  face.planeDistance =
      basePoint->x * face.normal.x +
      face.normal.y * basePoint->y +
      face.normal.z * basePoint->z;
}

// FUNCTION: SUMO 0x00408e89
// FUNCTION: EDITOR 0x00408eab
bool GameBox::ContainsPoint(Vector3& point)
{
  GameBoxFace* face = facesBegin;
  while (face < facesEnd) {
    if (face->normal.Dot(point) < face->planeDistance) {
      return false;
    }
    ++face;
  }
  return true;
}
