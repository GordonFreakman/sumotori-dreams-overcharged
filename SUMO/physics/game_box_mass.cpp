#include "game_runtime.h"

#include <math.h>

// FUNCTION: SUMO 0x00408893
// FUNCTION: EDITOR 0x004088b5
void GameBox::ScaleMassProperties(SumoF32 scale)
{
  mass *= scale;
  SumoF32 inverseScale = 1.0f / scale;
  inverseMass *= inverseScale;
  damping *= scale;
  inertia *= scale;
  inverseInertia *= inverseScale;
}

// FUNCTION: SUMO 0x00408aac
// FUNCTION: EDITOR 0x00408ace
void GameBox::FinalizeMassProperties()
{
  BuildEdges();

  inverseMass = 1.0f / mass;
  inverseInertia = 1.0f / inertia;

  boundingRadius = 0.0f;
  GameBoxPoint* point = pointsBegin;
  while (point < pointsEnd) {
    if (point->position.LengthSquared() > boundingRadius) {
      boundingRadius = point->position.LengthSquared();
    }
    ++point;
  }

  boundingRadius = (SumoF32) sqrt(boundingRadius);
}
