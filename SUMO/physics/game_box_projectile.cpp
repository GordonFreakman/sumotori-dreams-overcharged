#include "game_runtime.h"

extern SumoF32 g_gameGravityStep;

static const SumoF32 g_randomHalf = 0.5f;

// GLOBAL: SUMO 0x0042c9a8
// GLOBAL: EDITOR 0x0042c9a8
extern const SumoF32 g_gameProjectileHalfSize = 1.2f;

// GLOBAL: SUMO 0x0042c63c
// GLOBAL: EDITOR 0x0042c63c
extern const SumoF32 g_gameProjectileDefaultValue = 0.125f;

// GLOBAL: SUMO 0x0042b2ec
// GLOBAL: EDITOR 0x0042b2ec
extern const SumoF32 g_gameProjectileSpin = 0.1f;

// FUNCTION: SUMO 0x00410320
// FUNCTION: EDITOR 0x00410342
void LaunchGameBoxProjectile(Vector3 position, Vector3 target,
                             SumoF32 flightTime, SumoS32 type) {
  GameBox *box;
  {
    Vector3 halfSize;
    halfSize.x = g_gameProjectileHalfSize;
    halfSize.z = g_gameProjectileHalfSize;
    halfSize.y = -g_gameProjectileHalfSize;
    box = CreateGameBox(halfSize, position, type, g_gameProjectileDefaultValue);
  }
  box->ScaleMassProperties(3.0f);

  SumoF32 inverseFlightTime = 1.0f / flightTime;
  box->linearVelocity = (target - box->position).Scale(inverseFlightTime);
  box->linearVelocity.y -= g_gameGravityStep * flightTime * g_randomHalf;

  box->unknownC0 = 6;
  box->unknownC4 = 0.01f;
  Vector3 spin;
  spin.x = g_gameProjectileSpin;
  spin.y = g_gameProjectileSpin;
  spin.z = g_gameProjectileSpin;
  box->angularVelocity = spin;
}
