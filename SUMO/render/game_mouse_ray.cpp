#include "containers.h"

extern SumoS32 g_gameMouseX;
extern SumoS32 g_gameMouseY;
extern SumoF32 g_gameProjectionOffsetX;
extern SumoF32 g_gameProjectionOffsetY;
extern SumoF32 g_gameProjectionScaleX;
extern SumoF32 g_gameProjectionScaleY;

// GLOBAL: SUMO 0x00c06154
// GLOBAL: EDITOR 0x00c06974
Matrix3 g_gameInverseViewMatrix;

// FUNCTION: SUMO 0x00407772
// FUNCTION: EDITOR 0x00407794
Vector3 GetGameMouseRayDirection()
{
  Vector3 direction = MakeVector3(
      (g_gameMouseX + g_gameProjectionOffsetX) * g_gameProjectionScaleX,
      -(g_gameMouseY + g_gameProjectionOffsetY) * g_gameProjectionScaleY,
      1.0f);
  direction = direction.Transform(g_gameInverseViewMatrix);
  direction.Normalize();
  return direction;
}
