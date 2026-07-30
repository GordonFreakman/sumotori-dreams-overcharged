#include "game_runtime.h"

#include "decomp.h"


// GLOBAL: SUMO 0x0042c720
// GLOBAL: EDITOR 0x0042c720
extern volatile const SumoF32 g_immovableMass = 1.0e36f;

// FUNCTION: SUMO 0x0040844b
// FUNCTION: EDITOR 0x0040846d
void GameBox::ApplyAngularImpulse(Vector3 &contactOffset, Vector3 &impulse) {
  if (!flagD0) {
    ((GameBoxPoint *)&angularVelocity)
        ->SubtractOffset(impulse.Scale(inverseInertia));
  }
}

// FUNCTION: SUMO 0x004086b8
// FUNCTION: EDITOR 0x004086da
void GameBox::RecalculateMass() {
  MassAccumulator accumulator;

  Vector3 zero;
  zero.x = 0.0f;
  zero.y = 0.0f;
  zero.z = 0.0f;
  faceNormalSum = zero;

  GameBoxFace *face = facesBegin;
  while (face < facesEnd) {
    SumoF32 &state = face->state;
    faceNormalSum += face->normal.Scale(state);

    if (face->pointCount > 2) {
      GameBoxPointReference *references = face->pointReferences;
      GameBoxPoint *first = references[0].point;
      GameBoxPointReference *reference = references + 2;
      SumoS32 remaining = face->pointCount - 2;
      do {
        accumulator.AddTriangle(first->position,
                                (reference - 1)->point->position,
                                reference->point->position, state);
        ++reference;
      } while (--remaining != 0);
    }

    ++face;
  }

  SumoF32 inverseVolume = 1.0f / accumulator.volume;
  accumulator.weightedCenter.x *= inverseVolume;
  accumulator.weightedCenter.y *= inverseVolume;
  accumulator.weightedCenter.z *= inverseVolume;

  volume = accumulator.volume;
  accumulatedOffset = accumulator.weightedCenter;
}

// FUNCTION: SUMO 0x00408782
// FUNCTION: EDITOR 0x004087a4
void GameBox::ClearForces() {
  GameBoxPoint *point = pointsBegin;
  while (point < pointsEnd) {
    point->SubtractOffset(accumulatedOffset);
    ++point;
  }

  accumulatedOffset.z = 0.0f;
  accumulatedOffset.y = 0.0f;
  accumulatedOffset.x = 0.0f;
}

// FUNCTION: SUMO 0x00408992
// FUNCTION: EDITOR 0x004089b4
void GameBox::MakeImmovable() {
  flagD0 = true;
  inverseMass = 0.0f;
  mass = g_immovableMass;
  inverseInertia = 0.0f;
  inertia = mass;
}

// FUNCTION: SUMO 0x00408e2f
// FUNCTION: EDITOR 0x00408e51
void GameBox::FinishContacts(SumoS32 preserveState) {
  GameBoxPoint *point = pointsBegin;
  while (point < pointsEnd) {
    point->SubtractOffset(accumulatedOffset);
    ++point;
  }

  GameBoxFace *face = facesBegin;
  while (face < facesEnd) {
    if (face->state < g_vectorZero) {
      face->preserveState = preserveState;
    }
    face->state = 1.0f;
    g_gameBoxesEnd->UpdateFacePlane(*face);
    ++face;
  }
}
