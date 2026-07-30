#include "game_runtime.h"

// GLOBAL: SUMO 0x0042b284
// GLOBAL: EDITOR 0x0042b284
extern const SumoF32 g_inertiaRadiusScale = 0.4f;

// FUNCTION: SUMO 0x00408b12
// FUNCTION: EDITOR 0x00408b34
void GameBox::InitializePhysics()
{
  RecalculateMass();
  FinalizeMassProperties();

  damping = 1.0f;
  unknownBC = 0;
  mass = volume;

  SumoF32 radius = boundingRadius;
  radius *= g_inertiaRadiusScale;
  replayPresent = false;
  modeE0 = 3;
  flag58 = false;
  SumoF32 radiusSquared = radius * radius;
  inertia = radiusSquared * mass;
  inverseMass = 1.0f / mass;
  inverseInertia = 1.0f / inertia;

  Vector3 value;
  value.x = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
  angularVelocity = value;

  value.x = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
  linearVelocity = value;

  orientation.SetIdentity();

  value.x = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
  accumulatedForce = value;

  flagD0 = false;
  collisionFeatures = 0;
  breakability = 100000.0f;
  contactLinks = 0;
  unknownC0 = 0;
  unknownC4 = 0.0f;
  unknownC8 = 170.0f;
}
