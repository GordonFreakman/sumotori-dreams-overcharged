#include "game_runtime.h"

// FUNCTION: SUMO 0x0040fd4c
// FUNCTION: EDITOR 0x0040fd6e
SumoF32 CalculateLimbAngleCosine(SumoF32 firstLength, SumoF32 secondLength, SumoF32 targetLength) {
  if (firstLength + secondLength <= targetLength) {
    return g_gameOne;
  }
  if (firstLength + targetLength < secondLength) {
    return g_gameBoxYScale;
  }

  firstLength = 1.0f / firstLength;
  SumoF32 scaledSecond = firstLength * secondLength;
  SumoF32 scaledTarget = firstLength * targetLength;
  return -(scaledSecond * scaledSecond - scaledTarget * scaledTarget +
           g_gameOne) /
         (scaledSecond + scaledSecond);
}
