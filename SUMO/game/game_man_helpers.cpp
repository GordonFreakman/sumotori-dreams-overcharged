#include "game_runtime.h"

// GLOBAL: SUMO 0x0042c964
// GLOBAL: EDITOR 0x0042c964
extern const SumoF32 g_gameMaximumCenterDistanceSquared = 1000000.0f;

// FUNCTION: SUMO 0x0040e7a6
// FUNCTION: EDITOR 0x0040e7c8
Vector3 GameMan::CalculateCenterOfMassPosition() {
  Vector3 zero;
  zero.x = 0.0f;
  zero.y = 0.0f;
  zero.z = 0.0f;
  Vector3 weightedPosition = zero;
  SumoF32 totalMass = 0.0f;

  for (SumoS32 index = 0; index < 15; ++index) {
    GameBox *bodyPart = bodyParts[index];
    totalMass += bodyPart->mass;
    weightedPosition.AddInline(bodyPart->position.Scale(bodyPart->mass));
  }

  SumoF32 inverseMass = 1.0f / totalMass;
  weightedPosition.x *= inverseMass;
  weightedPosition.y *= inverseMass;
  weightedPosition.z *= inverseMass;
  SumoF32 horizontalDistanceSquared = weightedPosition.z * weightedPosition.z +
                                      weightedPosition.x * weightedPosition.x;
  if (horizontalDistanceSquared + weightedPosition.y * weightedPosition.y >
      g_gameMaximumCenterDistanceSquared) {
    weightedPosition.z = 0.0f;
    weightedPosition.y = 0.0f;
    weightedPosition.x = 0.0f;
  }
  return weightedPosition;
}


// FUNCTION: SUMO 0x0040e8ce
// FUNCTION: EDITOR 0x0040e8f0
Vector3 GameMan::CalculateCenterOfMassVelocity() {
  Vector3 zero;
  zero.x = 0.0f;
  zero.y = 0.0f;
  zero.z = 0.0f;
  Vector3 weightedVelocity = zero;
  SumoF32 totalMass = 0.0f;

  for (SumoS32 index = 0; index < 15; ++index) {
    GameBox *bodyPart = bodyParts[index];
    totalMass += bodyPart->mass;
    weightedVelocity.AddInline(bodyPart->linearVelocity.Scale(bodyPart->mass));
  }

  SumoF32 inverseMass = 1.0f / totalMass;
  weightedVelocity.x *= inverseMass;
  weightedVelocity.y *= inverseMass;
  weightedVelocity.z *= inverseMass;
  return weightedVelocity;
}
