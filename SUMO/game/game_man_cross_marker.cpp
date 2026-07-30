#include "containers.h"

extern const SumoF32 g_gameBoxYScale;
void GameAudioNoOpCallback();

static __forceinline Vector3 MakeGameManCrossMarkerVector3(SumoF32 x, SumoF32 y,
                                                           SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}
