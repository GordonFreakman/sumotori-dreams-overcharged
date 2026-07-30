#include "game_runtime.h"

#include <math.h>

extern const SumoF32 g_gameCameraMinimumDistanceScale;

// FUNCTION: SUMO 0x004103fb
// FUNCTION: EDITOR 0x0041041d
GameMan *GameMan::FindNearestOpponent(Vector3 &facingAxis,
                                      Vector3 &lateralAxis) {
  GameMan *nearest = NULL;
  SumoF32 bestScore = 9.9999996e35f;
  for (GameMan *candidate = g_gameMen; candidate < g_nextGameMan; ++candidate) {
    if (candidate == this)
      continue;
    Vector3 delta = candidate->bodyParts[0]->position - bodyParts[0]->position;
    volatile SumoF32 facingPenalty =
        -(delta.x * facingAxis.x + delta.z * facingAxis.z +
          delta.y * facingAxis.y);
    SumoF32 lateralPenalty =
        (SumoF32)fabs(delta.x * lateralAxis.x + delta.z * lateralAxis.z +
                      delta.y * lateralAxis.y) *
        g_gameCameraMinimumDistanceScale;
    if (facingPenalty > lateralPenalty)
      lateralPenalty = facingPenalty;
    SumoF32 score = (SumoF32)sqrt(delta.x * delta.x + delta.z * delta.z +
                                  delta.y * delta.y) +
                    lateralPenalty;
    if (score < bestScore) {
      bestScore = score;
      nearest = candidate;
    }
  }
  return nearest;
}
