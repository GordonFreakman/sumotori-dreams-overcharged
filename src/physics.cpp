#include "decomp_keywords.h"
#include "runtime.h"
#include "types.h"
#include "decomp.h"
#include "containers.h"
#include <new>
#include <math.h>
#include <string.h>

GameCollisionFeatureLink g_gameCollisionFeatureLinks[8192];

GameBox g_gameBoxes[2048];

GameRandomGenerator g_gameRandom;

GameCollisionCorrectionRecord g_gameCollisionCorrections[8192];

SumoU8 g_gameContactObjects[0xf400];

GameBox g_cutPlaneBox;

GameBox g_clipScratchBox;

GameCollisionPointRecord g_gameCollisionPoints[8192];

GameCollisionFeatureLink *g_gameCollisionFeatureLinksEnd;

SumoU8 *g_gameContactObjectsEnd;

GameBox *g_gameBoxesEnd;

SumoU8 *g_gameContactLinksEnd;

SumoU8 g_gameContactLinks[0x1800];

SumoS32 g_gameMenuSelection;

GameCollisionCorrectionRecord *g_gameCollisionCorrectionsEnd;

GameCollisionPointRecord *g_gameCollisionPointsEnd;

SumoU8 g_gameCollisionGroupSentinel;

SumoU8 g_gameBoxTextureTriangleCounts[0x100];
SumoU8 g_gameBoxLitVertexStorage[0x240000];
SumoU8 g_gameBoxShadowPositionStorage[0x120000];
SumoU8 g_gameBoxIndexPairStorage[0x20000];

SumoS16 g_gameBoxTriangleOrder[0x8000];

// GLOBAL: SUMO 0x00775dd8
// GLOBAL: EDITOR 0x007765f8
SumoU8 *g_gameBoxLitVertexCursor;

// GLOBAL: SUMO 0x00775ddc
// GLOBAL: EDITOR 0x007765fc
SumoU8 *g_gameBoxShadowPositionCursor;

// GLOBAL: SUMO 0x00ac5ef0
// GLOBAL: EDITOR 0x00ac6710
SumoU8 *g_gameBoxIndexPairCursor;

// GLOBAL: SUMO 0x00a45ee4
// GLOBAL: EDITOR 0x00a46704
Vector3 g_gameBoxLightDirection;

// GLOBAL: SUMO 0x0042c78c
// GLOBAL: EDITOR 0x0042c78c
extern const SumoF32 g_gameBoxLightScale = 127.0f;

// GLOBAL: SUMO 0x0042c790
// GLOBAL: EDITOR 0x0042c790
extern const SumoF32 g_gameBoxNegativeLightScale = -127.0f;

// GLOBAL: SUMO 0x00c06010
// GLOBAL: EDITOR 0x00c06830
RuntimeVector3Vector g_gameBoxTransformedPoints;

// GLOBAL: SUMO 0x0042c740
// GLOBAL: EDITOR 0x0042c740
extern const SumoF32 g_boxWaterSurfaceOffset = 1.3f;
// GLOBAL: SUMO 0x0042c73c
// GLOBAL: EDITOR 0x0042c73c
extern const SumoF32 g_boxWaterWaveScale = -0.023f;
// GLOBAL: SUMO 0x0042c738
// GLOBAL: EDITOR 0x0042c738
extern const SumoF32 g_boxWaterDiagonalScale = 1.5f;
// GLOBAL: SUMO 0x0042c734
// GLOBAL: EDITOR 0x0042c734
extern const SumoF32 g_boxWaterVerticalRetention = 0.93f;
// GLOBAL: SUMO 0x0042c730
// GLOBAL: EDITOR 0x0042c730
extern const SumoF32 g_boxWaterBuoyancyScale = 0.95f;
// GLOBAL: SUMO 0x0042c72c
// GLOBAL: EDITOR 0x0042c72c
extern const SumoF32 g_boxWaterLinearDamping = 0.995f;
// GLOBAL: SUMO 0x0042c728
// GLOBAL: EDITOR 0x0042c728
extern const SumoF32 g_boxWaterAngularDamping = 0.995f;

extern const SumoF32 g_gameOne;

// FUNCTION: SUMO 0x0040b776
// FUNCTION: EDITOR 0x0040b798
SumoF32 GameRandomGenerator::Next() {
  SumoF32 value = values[firstIndex] - values[secondIndex];
  if (value < g_vectorZero) {
    value += g_gameOne;
  }
  values[firstIndex] = value;

  if (--firstIndex == 0) {
    firstIndex = 97;
  }
  if (--secondIndex == 0) {
    secondIndex = 97;
  }

  carry = carry - decrement;
  if (carry < g_vectorZero) {
    carry += modulus;
  }

  value = value - carry;
  if (value < g_vectorZero) {
    value += g_gameOne;
  }
  return value;
}

// GLOBAL: SUMO 0x0042c744
// GLOBAL: EDITOR 0x0042c744
extern const SumoF32 g_gameActivityDecay = 0.94f;

// GLOBAL: SUMO 0x0042c748
// GLOBAL: EDITOR 0x0042c748
extern const SumoF32 g_gameSleepSpeedScale = 111111.11f;

// GLOBAL: SUMO 0x004536e0
// GLOBAL: EDITOR 0x004536e0
SumoF32 g_gameGravityStep = -0.0098f;

// FUNCTION: SUMO 0x00409a4a
// FUNCTION: EDITOR 0x00409a6c
void GameBox::IntegratePhysics() {
  if (!flag58 && !immovable) {
    if (!sleeping) {
      orientation.Rotate(angularVelocity);
      orientation.Orthonormalize();
      position += linearVelocity;
      ApplyWaterInteraction();

      if (!contactLinks) {
        SumoF32 linearSpeedSquared = linearVelocity.LengthSquared();
        if ((angularVelocity.LengthSquared() + linearSpeedSquared) *
                g_gameSleepSpeedScale <
            g_gameOne) {
          if (++sleepCounter > 30)
            sleeping = true;
        } else {
          sleepCounter = 0;
        }
      }

      if (!sleeping)
        linearVelocity.y += g_gameGravityStep;
    }
    activityValue *= g_gameActivityDecay;
  }
}

extern SumoF32 g_gameGravityStep;

DECOMP_SIZE_ASSERT(GameBoxContactLink, 0x0c);
DECOMP_SIZE_ASSERT(GameCollisionFeatureLink, 0xcc);
DECOMP_SIZE_ASSERT(GameCollisionPointRecord, 0x60);
DECOMP_SIZE_ASSERT(GameCollisionCorrectionRecord, 0x20);

// GLOBAL: SUMO 0x00511600
// GLOBAL: EDITOR 0x00511e20
//extern GameCollisionCorrectionRecord g_gameCollisionCorrections[2048];

// GLOBAL: SUMO 0x00530c00
// GLOBAL: EDITOR 0x00531420
//extern GameCollisionPointRecord g_gameCollisionPoints[2048];

// GLOBAL: SUMO 0x00562414
// GLOBAL: EDITOR 0x00562c34
extern GameCollisionCorrectionRecord *g_gameCollisionCorrectionsEnd;

// GLOBAL: SUMO 0x00562418
// GLOBAL: EDITOR 0x00562c38
extern GameCollisionPointRecord *g_gameCollisionPointsEnd;

// GLOBAL: SUMO 0x005ae428
// GLOBAL: EDITOR 0x005aec48
extern GameCollisionFeatureLink g_gameCollisionFeatureLinks[8192];

// GLOBAL: SUMO 0x00560c00
// GLOBAL: EDITOR 0x00561420
extern GameCollisionFeatureLink *g_gameCollisionFeatureLinksEnd;

// GLOBAL: SUMO 0x00562420
// GLOBAL: EDITOR 0x00562c40
extern SumoU8 g_gameCollisionGroupSentinel;

// GLOBAL: SUMO 0x005115f8
// GLOBAL: EDITOR 0x00511e18
void *g_gameCollisionGroupRoot;

// GLOBAL: SUMO 0x00765c32
// GLOBAL: EDITOR 0x00766452
SumoU8 g_gameCollisionPointScratchFlag;

// GLOBAL: SUMO 0x00765dd4
// GLOBAL: EDITOR 0x007665f4
SumoF32 g_gameCollisionScale = g_gameGravityStep * -0.050000001f;

SumoU32 GetGameCollisionStorageAddressChecksum() {
  return (SumoU32)(SumoUIntPtr)g_gameCollisionCorrections +
         (SumoU32)(SumoUIntPtr)g_gameCollisionPoints +
         (SumoU32)(SumoUIntPtr)g_gameCollisionCorrectionsEnd +
         (SumoU32)(SumoUIntPtr)g_gameCollisionPointsEnd +
         (SumoU32)(SumoUIntPtr)g_gameCollisionFeatureLinks +
         (SumoU32)(SumoUIntPtr)g_gameCollisionFeatureLinksEnd +
         (SumoU32)(SumoUIntPtr)&g_gameCollisionGroupSentinel;
}

DECOMP_SIZE_ASSERT(GameBoxPoint, 0x10);

// FUNCTION: SUMO 0x00407dfa
// FUNCTION: EDITOR 0x00407e1c
void GameBoxPoint::SubtractOffset(Vector3 &offset) {
  position.x -= offset.x;
  position.y -= offset.y;
  position.z -= offset.z;
}

DECOMP_SIZE_ASSERT(GameBoxFace, 0x24);

// FUNCTION: SUMO 0x004087f0
// FUNCTION: EDITOR 0x00408812
void GameBox::UpdateFacePlane(GameBoxFace &face) {
  Vector3 initialNormal;
  initialNormal.x = 0.0f;
  initialNormal.y = 0.0f;
  initialNormal.z = 0.0f;
  Vector3 normal = initialNormal;

  SumoS32 index = 2;
  if (face.pointCount > 2) {
    GameBoxPointReference *references = face.pointReferences;
    do {
      normal.AddInline(
          (references[index].point->position - references[0].point->position)
              .Cross(references[index - 1].point->position -
                     references[0].point->position));
      ++index;
    } while (index < face.pointCount);
  }

  face.normal = normal;
  Vector3 *basePoint = &face.pointReferences[0].point->position;
  face.planeDistance = basePoint->x * face.normal.x +
                       face.normal.y * basePoint->y +
                       face.normal.z * basePoint->z;
}

// FUNCTION: SUMO 0x00408e89
// FUNCTION: EDITOR 0x00408eab
bool GameBox::ContainsPoint(Vector3 &point) {
  GameBoxFace *face = facesBegin;
  while (face < facesEnd) {
    if (face->normal.Dot(point) < face->planeDistance) {
      return false;
    }
    ++face;
  }
  return true;
}

// FUNCTION: SUMO 0x004089bc
// FUNCTION: EDITOR 0x004089de
void GameBox::BuildEdges() {
  edgesBegin = (GameBoxEdge *)operator new(
      (pointReferencesEnd - pointReferencesBegin) * sizeof(GameBoxEdge));
  edgesEnd = edgesBegin;

  GameBoxFace *face = facesBegin;
  while (face < facesEnd) {
    SumoS32 previousIndex = face->pointCount - 1;
    SumoS32 index = 0;
    while (index < face->pointCount) {
      if (face->pointReferences[index].index >
          face->pointReferences[previousIndex].index) {
        edgesEnd->firstIndex = face->pointReferences[index].index;
        edgesEnd->secondIndex = face->pointReferences[previousIndex].index;
        edgesEnd->firstFace = face;
        edgesEnd->secondFace = NULL;
        ++edgesEnd;
      }

      previousIndex = index;
      ++index;
    }

    ++face;
  }

  face = facesBegin;
  while (face < facesEnd) {
    SumoS32 previousIndex = face->pointCount - 1;
    SumoS32 index = 0;
    while (index < face->pointCount) {
      if (face->pointReferences[index].index <
          face->pointReferences[previousIndex].index) {
        GameBoxEdge *edge = edgesBegin;
        while (edge->firstIndex != face->pointReferences[previousIndex].index ||
               edge->secondIndex != face->pointReferences[index].index) {
          ++edge;
        }
        edge->secondFace = face;
      }

      previousIndex = index;
      ++index;
    }

    ++face;
  }
}

DECOMP_SIZE_ASSERT(MassAccumulator, 0x10);

// FUNCTION: SUMO 0x004080ea
// FUNCTION: EDITOR 0x0040810c
MassAccumulator::MassAccumulator() {
  volume = 0.0f;

  Vector3 zero;
  zero.x = 0.0f;
  zero.y = 0.0f;
  zero.z = 0.0f;
  weightedCenter = zero;
}

void MassAccumulator::AddTriangle(Vector3 &first, Vector3 &second,
                                  Vector3 &third, SumoF32 faceState) {
  (void)faceState;

  Vector3 flatFirst = first;
  flatFirst.z = 0.0f;
  Vector3 flatSecond = second;
  flatSecond.z = 0.0f;
  Vector3 flatThird = third;
  flatThird.z = 0.0f;

  SumoF32 quarter = 0.25f;

  Vector3 edge = flatFirst - second;
  Vector3 cross = (flatThird - second).Cross(flatSecond - second);
  SumoF32 term = edge.z * cross.z + edge.y * cross.y + edge.x * cross.x;
  Vector3 centroid =
      (((flatThird + second) + flatFirst) + flatSecond).Scale(quarter);
  volume = term + volume;
  weightedCenter += centroid.Scale(term);

  edge = flatFirst - second;
  cross = (first - second).Cross(flatThird - second);
  term = edge.z * cross.z + edge.y * cross.y + edge.x * cross.x;
  centroid = (((first + second) + flatThird) + flatFirst).Scale(quarter);
  volume = term + volume;
  weightedCenter += centroid.Scale(term);

  edge = flatThird - second;
  cross = (first - second).Cross(third - second);
  term = edge.z * cross.z + edge.y * cross.y + edge.x * cross.x;
  centroid = (((first + second) + flatThird) + third).Scale(quarter);
  volume = term + volume;
  weightedCenter += centroid.Scale(term);
}

// FUNCTION: SUMO 0x00408893
// FUNCTION: EDITOR 0x004088b5
void GameBox::ScaleMassProperties(SumoF32 scale) {
  mass *= scale;
  SumoF32 inverseScale = 1.0f / scale;
  inverseMass *= inverseScale;
  damping *= scale;
  inertia *= scale;
  inverseInertia *= inverseScale;
}

// FUNCTION: SUMO 0x00408aac
// FUNCTION: EDITOR 0x00408ace
void GameBox::FinalizeMassProperties() {
  BuildEdges();

  inverseMass = 1.0f / mass;
  inverseInertia = 1.0f / inertia;

  boundingRadius = 0.0f;
  GameBoxPoint *point = pointsBegin;
  while (point < pointsEnd) {
    if (point->position.LengthSquared() > boundingRadius) {
      boundingRadius = point->position.LengthSquared();
    }
    ++point;
  }

  boundingRadius = (SumoF32)sqrt(boundingRadius);
}

// GLOBAL: SUMO 0x0042b284
// GLOBAL: EDITOR 0x0042b284
extern const SumoF32 g_inertiaRadiusScale = 0.4f;

// FUNCTION: SUMO 0x00408b12
// FUNCTION: EDITOR 0x00408b34
void GameBox::InitializePhysics() {
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
  m_pOwner = NULL;

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

  immovable = false;
  collisionFeatures = 0;
  breakability = 100000.0f;
  contactLinks = 0;
  unknownC0 = 0;
  unknownC4 = 0.0f;
  unknownC8 = 170.0f;
  fractureSound = 1;
}

// GLOBAL: SUMO 0x0042c720
// GLOBAL: EDITOR 0x0042c720
extern volatile const SumoF32 g_immovableMass = 1.0e36f;

// FUNCTION: SUMO 0x0040844b
// FUNCTION: EDITOR 0x0040846d
void GameBox::ApplyAngularImpulse(Vector3 &contactOffset, Vector3 &impulse) {
  if (!immovable) {
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
  immovable = true;
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

// FUNCTION: SUMO 0x004083df
// FUNCTION: EDITOR 0x00408401
Vector3 GameBox::VelocityAtPoint(Vector3 &point) {
  if (immovable) {
    Vector3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    return zero;
  }

  return linearVelocity + (point - position).Cross(angularVelocity);
}

// FUNCTION: SUMO 0x00408481
// FUNCTION: EDITOR 0x004084a3
Vector3 GameBox::CalculateImpulseResponse(Vector3 &impulsePoint,
                                          Vector3 &impulse,
                                          Vector3 &samplePoint) {
  return impulse.Scale(inverseMass) + (impulsePoint - position)
                                          .Cross(impulse)
                                          .Cross(samplePoint - position)
                                          .Scale(inverseInertia);
}

// FUNCTION: SUMO 0x004084fe
// FUNCTION: EDITOR 0x00408520
Matrix3 GameBox::CalculateImpulseResponseMatrix(Vector3 &impulsePoint,
                                                Vector3 &samplePoint) {
  Matrix3 matrix;
  Vector3 response;
  response.x = 1.0f;
  response.y = 0.0f;
  response.z = 0.0f;
  Vector3 impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m00 = response.x;
  matrix.m01 = response.y;
  matrix.m02 = response.z;

  response.x = 0.0f;
  response.y = 1.0f;
  response.z = 0.0f;
  impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m10 = response.x;
  matrix.m11 = response.y;
  matrix.m12 = response.z;

  response.x = 0.0f;
  response.y = 0.0f;
  response.z = 1.0f;
  impulse = response;
  response = CalculateImpulseResponse(impulsePoint, impulse, samplePoint);
  matrix.m20 = response.x;
  matrix.m21 = response.y;
  matrix.m22 = response.z;
  return matrix;
}

// FUNCTION: SUMO 0x004085f0
// FUNCTION: EDITOR 0x00408612
void GameBox::ApplyImpulseAtPoint(Vector3 &point, Vector3 &impulse) {
  if (!immovable) {
    Vector3 angularDelta;
    angularDelta = (point - position).Cross(impulse).Scale(inverseInertia);
    Vector3 *angular = &angularVelocity;
    angular->x -= angularDelta.x;
    angular->y -= angularDelta.y;
    angular->z -= angularDelta.z;

    linearVelocity += impulse.Scale(inverseMass);
  }
}

// FUNCTION: SUMO 0x00408684
// FUNCTION: EDITOR 0x004086a6
void ApplyPairedAngularImpulse(GameBox **boxes, Vector3 &impulse) {
  Vector3 opposed = -impulse;
  boxes[0]->ApplyAngularImpulse(opposed, opposed);
  boxes[1]->ApplyAngularImpulse(opposed, impulse);
}

void AlignGameBoxJointTransform(GameBoxJoint *joint, SumoS32 side) {
  GameBox *box = joint->boxes[side];
  GameBox *other = joint->boxes[side ^ 1];
  other->orientation = box->orientation;
  Vector3 world =
      joint->localAnchors[side].Transform(box->orientation) + box->position;
  other->position =
      world - other->orientation.Transform(joint->localAnchors[side ^ 1]);
}

// FUNCTION: SUMO 0x00408389
// FUNCTION: EDITOR 0x004083ab
void GameBox::DestroyGeometry() {
  operator delete(pointsBegin);
  operator delete(pointReferencesBegin);
  operator delete(facesBegin);
  operator delete(edgesBegin);
}

// FUNCTION: SUMO 0x004083b0
// FUNCTION: EDITOR 0x004083d2
void ResetGameBoxes() {
  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    box->DestroyGeometry();
    ++box;
  }
  g_gameBoxesEnd = g_gameBoxes;
}

// FUNCTION: SUMO 0x00408e08
// FUNCTION: EDITOR 0x00408e2a
void RenderGameBoxes(SumoS32) {
  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    box->Render();
    ++box;
  }
}

// FUNCTION: SUMO 0x00408ec7
// FUNCTION: EDITOR 0x00408ee9
void LimitDynamicBoxes() {
  SumoF32 smallestMass = g_immovableMass;
  GameBox *smallestBox = 0;
  SumoS32 dynamicCount = 0;

  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    if (box->contactLinks == 0 && !box->immovable && !box->flag58 && !box->m_pOwner) {
      if (smallestMass > box->mass) {
        smallestBox = box;
        smallestMass = box->mass;
      }
      ++dynamicCount;
    }
    ++box;
  }

  if (dynamicCount > 256 && smallestBox != 0) {
    smallestBox->flag58 = true;
  }
}

// FUNCTION: SUMO 0x00408c14
// FUNCTION: EDITOR 0x00408c36
void ResetGameContactLists() {
  GameBox *boxesEnd = g_gameBoxesEnd;
  GameBox *box = g_gameBoxes;
  while (box < boxesEnd) {
    box->contactLinks = NULL;
    ++box;
  }

  GameBoxJoint *joint = (GameBoxJoint *)g_gameContactObjects;
  g_gameContactLinksEnd = g_gameContactLinks;
  while ((SumoU8 *)joint < g_gameContactObjectsEnd) {

   if (!joint->boxes[0] || !joint->boxes[1]) 
   {
      ++joint;
      continue;
    }

    Vector3 &unknown64 = joint->unknown64;
    Vector3 &unknownC4 = joint->unknownC4;
    Vector3 &initialImpulse = joint->initialImpulse;

    joint->limitFlags = 0;
    joint->unknown5C = 0.0f;
    joint->firstLimitImpulse = 0.0f;
    joint->secondLimitImpulse = 0.0f;
    unknown64.z = 0.0f;
    unknown64.y = 0.0f;
    unknown64.x = 0.0f;
    unknownC4.z = 0.0f;
    unknownC4.y = 0.0f;
    unknownC4.x = 0.0f;
    initialImpulse.z = 0.0f;
    initialImpulse.y = 0.0f;
    initialImpulse.x = 0.0f;

    ((GameBoxContactLink *)g_gameContactLinksEnd)->other = joint->boxes[1];
    ((GameBoxContactLink *)g_gameContactLinksEnd)->owner = joint;
    GameBoxContactLink *link = (GameBoxContactLink *)g_gameContactLinksEnd;
    GameBoxContactLink **boxContactLinks = &joint->boxes[0]->contactLinks;
    link->next = *boxContactLinks;
    *boxContactLinks = link;
    g_gameContactLinksEnd += sizeof(GameBoxContactLink);

    ((GameBoxContactLink *)g_gameContactLinksEnd)->other = joint->boxes[0];
    ((GameBoxContactLink *)g_gameContactLinksEnd)->owner = joint;
    link = (GameBoxContactLink *)g_gameContactLinksEnd;
    boxContactLinks = &joint->boxes[1]->contactLinks;
    link->next = *boxContactLinks;
    *boxContactLinks = link;
    g_gameContactLinksEnd += sizeof(GameBoxContactLink);

    ++joint;
  }
}

// FUNCTION: SUMO 0x00408dda
// FUNCTION: EDITOR 0x00408dfc
void RefreshGameContactLists() { ResetGameContactLists(); }

extern GameBox g_cutPlaneBox;
extern GameBox g_clipScratchBox;
extern GameBox *g_gameBoxesEnd;
extern GameBox *g_gameBoxesLimit;
extern SumoU8 g_gameContactObjects[0xf400];
extern SumoU8 *g_gameContactObjectsEnd;
extern SumoS32 g_gameMenuSelection;
extern SumoU8 g_gameBoxesInitialized;
extern GameRandomGenerator g_gameRandom;
extern const SumoF32 g_randomHalf;

SumoS32 LogGameDebugValue(const char *text, SumoS32 value);

SumoU8 FractureGameBoxAtPoint(Vector3 &position, GameBox *box) {
  if (box->flag58)
    return 0;
  //if (g_gameBoxesEnd > (GameBox *)((SumoU8 *)g_gameBoxesLimit - 0x9d8))
//    return 0;
  if (box->unknownC0 == 4 || box->unknownC0 == 3) {
    box->fractureSound = 7;
  }
  GameBox *destination = &g_cutPlaneBox;
  GameBox *spare = &g_clipScratchBox;
  Vector3 localPoint = box->orientation.Transform(position - box->position);
  PlayGameSound(
      box->fractureSound,
      (SumoF32)exp(log((SumoF64)box->volume * 0.0071428572f) * -0.25f),
      exp(log((SumoF64)box->volume * 0.0071428572f)) / 2.f, // 0.25f,
      0, position);
  if (g_gameMenuSelection == 0)
    g_gameMenuSelection = box->unknownBC;

  Vector3 seeds[5];
  SumoS32 seedCount = 0;
  SumoF32 seedScale = 0.3f;
  while (seedCount < 5) {
    SumoF32 firstValue = g_gameRandom.Next();
    SumoF32 depth = (SumoF32)((SumoF64)firstValue + firstValue - g_gameOne);
    SumoF32 secondValue = g_gameRandom.Next();
    SumoF32 lateral = (SumoF32)((SumoF64)secondValue + secondValue - g_gameOne);
    SumoF32 thirdValue = g_gameRandom.Next();
    SumoF32 forward = (SumoF32)((SumoF64)thirdValue + thirdValue - g_gameOne);
    Vector3 random3 = MakeVector3(forward, lateral, depth);
    seeds[seedCount] =
        localPoint + random3.Scale(box->boundingRadius).Scale(seedScale);
    if (!box->ContainsPoint(seeds[seedCount]))
      continue;
    ++seedCount;
  }
  GameBox *biggestBox = NULL;
  for (SumoS32 fragment = 0; fragment < 5; ++fragment) {
    GameBox *newBox = g_gameBoxesEnd;
    GameBox *source = box;
    for (SumoS32 other = 0; other < 5; ++other) {
      if (other == fragment)
        continue;
      GameBox *target = destination;
      if (other == 4 || (other == 3 && fragment == 4)) {
        newBox->ReserveGeometry(0x100, 0x400, 0x100);
        target = newBox;
      }
      Vector3 normal = -seeds[other] + seeds[fragment];
      Vector3 midpoint = seeds[other] + seeds[fragment];
      SumoF32 distance = (SumoF32)(((SumoF64)normal.y * midpoint.y +
                                    (SumoF64)normal.z * midpoint.z +
                                    (SumoF64)normal.x * midpoint.x) *
                                   g_randomHalf);
      target->ClipGeometry(*source, normal, distance);
      source = destination;
      GameBox *swap = spare;
      spare = destination;
      destination = swap;
      newBox = g_gameBoxesEnd;
    }

    if (newBox->facesEnd == newBox->facesBegin) {
      LogGameDebugValue("halott", 0);
      continue;
    }

    newBox->type = box->type;
    newBox->defaultValue = box->defaultValue;
    newBox->InitializePhysics();
    newBox->FinishContacts(-1);
    Vector3 offset = newBox->accumulatedOffset;
    SumoF32 separationScale = 1.01f;
    newBox->position =
        box->position +
        offset.Scale(separationScale).Transform(box->orientation);
    newBox->InitializePhysics();
    newBox->ScaleMassProperties(box->damping);
    newBox->linearVelocity = box->linearVelocity;
    newBox->angularVelocity = box->angularVelocity;
    newBox->orientation = box->orientation;
    newBox->collisionFeatures = 0;
    newBox->accumulatedForce = box->accumulatedForce + offset;
    newBox->modeE0 = box->modeE0;
    newBox->unknownC0 = box->unknownC0;
    newBox->unknownC4 = box->unknownC4;
    newBox->m_pOwner = box->m_pOwner;
    if (g_gameBoxesInitialized)
      newBox->breakability = box->breakability * 3.0f;

      if (box->m_pOwner && newBox->volume > 5) {
      box->m_pOwner->m_bLobotomized++;
    }

   if (!biggestBox || newBox->volume >= biggestBox->volume)
      biggestBox = newBox;

    for (GameBoxJoint *joint = (GameBoxJoint *)g_gameContactObjects;
         (SumoU8 *)joint < g_gameContactObjectsEnd; ++joint) {
      for (SumoS32 side = 0; side < 2; ++side) {
        if (joint->boxes[side] != box)
          continue;
        SumoS32 bestSeed = -1;
        SumoF32 bestDistance = 1e36f;
        for (SumoS32 candidate = 0; candidate < 5; ++candidate) {
          SumoF32 candidateDistance =
              (seeds[candidate] - joint->localAnchors[side]).LengthSquared();
          if (!(candidateDistance > bestDistance)) {
            bestSeed = candidate;
            bestDistance = candidateDistance;
          }
        }
        if (bestSeed == fragment) {
          joint->boxes[side] = newBox;
          joint->localAnchors[side].x = joint->localAnchors[side].x - offset.x;
          joint->localAnchors[side].y = joint->localAnchors[side].y - offset.y;
          joint->localAnchors[side].z = joint->localAnchors[side].z - offset.z;
        }
      }
    }

    g_gameBoxesEnd = newBox + 1;
  }

  if (box->m_pOwner) 
  {
    for (size_t i = 0; i < 14; i++) 
    {
    if (box->m_pOwner->bodyParts[i] == box) 
    {
        box->m_pOwner->bodyParts[i] = biggestBox;
        break;
    }
    }
  }
  box->flag58 = 1;

  RefreshGameContactLists();

  return 1;
}

extern SumoF32 g_gameArenaExtent;
extern SumoU8 *g_gameBoxIndexPairCursor;
extern Vector3 g_gameBoxLightDirection;
extern const SumoF32 g_gameBoxLightScale;
extern SumoU8 *g_gameBoxLitVertexCursor;
extern const SumoF32 g_gameBoxNegativeLightScale;
extern SumoU8 *g_gameBoxShadowPositionCursor;
extern SumoU8 g_gameBoxTextureTriangleCounts[0x100];
extern RuntimeVector3Vector g_gameBoxTransformedPoints;
extern const SumoF32 g_textureCenterFloat;

struct GameBoxLitVertex {
  Vector3 position;
  SumoS32 color;
  SumoF32 u;
  SumoF32 v;
};

DECOMP_SIZE_ASSERT(GameBoxLitVertex, 0x18);

void GameBox::Render() {
  if (flag58 != 0)
    return;

  g_gameBoxTransformedPoints.Resize((SumoS32)(pointsEnd - pointsBegin) + 1);
  Vector3 *transformed = &g_gameBoxTransformedPoints[0];
  for (GameBoxPoint *point = pointsBegin; point < pointsEnd; ++point) {
    *transformed = point->position.Transform(orientation) + position;
    ++transformed;
  }

  Vector3 lightLocal = orientation.Transform(g_gameBoxLightDirection);

  SumoS16 *triangleCounts = (SumoS16 *)&g_gameBoxTextureTriangleCounts;
  for (GameBoxFace *face = facesBegin; face < facesEnd; ++face) {
    if (lightLocal.y * face->normal.y + lightLocal.z * face->normal.z +
            lightLocal.x * face->normal.x >
        g_vectorZero)
      face->visible20 = 1;
    else
      face->visible20 = 0;

    Vector3 normal = face->normal;
    normal.Normalize();

    Vector3 axis;
    if (normal.x * normal.x > normal.y * normal.y) {
      axis.x = 0.0f;
      axis.y = 1.0f;
      axis.z = 0.0f;
    } else {
      axis.x = 1.0f;
      axis.y = 0.0f;
      axis.z = 0.0f;
      if (normal.z * normal.z > normal.y * normal.y) {
        axis.x = 0.0f;
        axis.y = 1.0f;
        axis.z = 0.0f;
      }
    }

    Vector3 uAxis = axis.Cross(normal);
    uAxis.Normalize();
    Vector3 vAxis = uAxis.Cross(normal);

    SumoS32 red = (SumoS32)((lightLocal.z * normal.z + lightLocal.y * normal.y +
                             lightLocal.x * normal.x) *
                                g_gameBoxNegativeLightScale +
                            g_textureCenterFloat);
    SumoS32 green = (SumoS32)((vAxis.y * lightLocal.y + vAxis.z * lightLocal.z +
                               lightLocal.x * vAxis.x) *
                                  g_gameBoxLightScale -
                              g_textureCenterFloat);
    SumoS32 blue = (SumoS32)(g_textureCenterFloat -
                             (uAxis.y * lightLocal.y + uAxis.z * lightLocal.z +
                              uAxis.x * lightLocal.x) *
                                 g_gameBoxLightScale);
    SumoS32 color = blue - (((-red << 8) + green) << 8);

    uAxis.x = uAxis.x * defaultValue;
    uAxis.y = uAxis.y * defaultValue;
    uAxis.z = uAxis.z * defaultValue;
    vAxis.x = vAxis.x * defaultValue;
    vAxis.y = vAxis.y * defaultValue;
    vAxis.z = vAxis.z * defaultValue;

    if (face->pointCount > 2) {
      SumoS32 corners[3];
      corners[0] = 0;
      for (SumoS32 fanIndex = 2; fanIndex < face->pointCount; ++fanIndex) {
        corners[1] = fanIndex - 1;
        corners[2] = fanIndex;

        *(SumoS16 *)g_gameBoxIndexPairCursor = triangleCounts[type];
        ++triangleCounts[type];
        *(SumoS16 *)(g_gameBoxIndexPairCursor + 2) = (SumoS16)type;
        g_gameBoxIndexPairCursor += 4;

        for (SumoS32 corner = 0; corner < 3; ++corner) {
          SumoS32 referenceIndex = corners[corner];
          GameBoxLitVertex *vertex =
              (GameBoxLitVertex *)g_gameBoxLitVertexCursor;
          vertex->position =
              g_gameBoxTransformedPoints[face->pointReferences[referenceIndex]
                                             .index];

          Vector3 shifted =
              pointsBegin[face->pointReferences[referenceIndex].index]
                  .position +
              accumulatedForce;
          vertex->u =
              uAxis.z * shifted.z + uAxis.y * shifted.y + uAxis.x * shifted.x;
          shifted = pointsBegin[face->pointReferences[referenceIndex].index]
                        .position +
                    accumulatedForce;
          vertex->v =
              vAxis.z * shifted.z + vAxis.y * shifted.y + vAxis.x * shifted.x;

          vertex->color = color;
          g_gameBoxLitVertexCursor += sizeof(GameBoxLitVertex);
        }
      }
    }
  }

  SumoF32 negatedExtent = -g_gameArenaExtent;
  Vector3 shadowOffset = g_gameBoxLightDirection.Scale(negatedExtent);

  for (GameBoxEdge *edge = edgesBegin; edge < edgesEnd; ++edge) {
    SumoU8 firstLit = edge->firstFace->visible20;
    SumoS32 flip;
    if (firstLit == 0 && edge->secondFace->visible20 == 1) {
      flip = 0;
    } else {
      if (edge->secondFace->visible20 != 0 || firstLit != 1)
        continue;
      flip = 1;
    }

    Vector3 corners[4];
    corners[flip ^ 1] = g_gameBoxTransformedPoints[edge->firstIndex];
    corners[flip] = g_gameBoxTransformedPoints[edge->secondIndex];
    corners[2 + (flip ^ 1)] =
        g_gameBoxTransformedPoints[edge->secondIndex] + shadowOffset;
    corners[2 + flip] =
        g_gameBoxTransformedPoints[edge->firstIndex] + shadowOffset;

    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[0];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[1];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[2];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[0];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[2];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
    *(Vector3 *)g_gameBoxShadowPositionCursor = corners[3];
    g_gameBoxShadowPositionCursor += sizeof(Vector3);
  }
}

extern const SumoF32 g_randomHalf = 0.5f;

// GLOBAL: SUMO 0x0042cd30
// GLOBAL: EDITOR 0x0042cd30
extern const double g_waterInitialWaveAmplitude = 0.04;

// GLOBAL: SUMO 0x0042c9a4
// GLOBAL: EDITOR 0x0042c9a4
extern const SumoF32 g_waterNeighborCoupling = 0.09f;

// GLOBAL: SUMO 0x0042cd28
// GLOBAL: EDITOR 0x0042cd28
extern const SumoF32 g_waterVelocityDamping = 0.997f;

// GLOBAL: SUMO 0x0042ca58
// GLOBAL: EDITOR 0x0042ca58
extern const double g_waterCorrectionScale = 0.1f;

extern SumoS32 g_waterGridWidth;

extern SumoS32 g_waterGridHeight;

// GLOBAL: SUMO 0x00453cd4
// GLOBAL: EDITOR 0x00453cd4
SumoF32 g_waterBaseHeight = -2000.0f;

// GLOBAL: SUMO 0x00d0ebb4
// GLOBAL: EDITOR 0x00d0f3d4
SumoF32 g_waterHeightCorrection;

// GLOBAL: SUMO 0x00d0ebb8
// GLOBAL: EDITOR 0x00d0f3d8
SumoU8 g_waterFieldActive;

// GLOBAL: SUMO 0x00d0ebbc
// GLOBAL: EDITOR 0x00d0f3dc
FloatVector g_waterHeights;

// GLOBAL: SUMO 0x00d0ebc8
// GLOBAL: EDITOR 0x00d0f3e8
FloatVector g_waterVelocities;

extern SumoS32 g_screenTintLevel;

// FUNCTION: SUMO 0x004167ee
// FUNCTION: EDITOR 0x00416810
void InitializeWaterField() {
  SumoS32 cellCount = g_waterGridWidth * g_waterGridHeight;
  g_waterBaseHeight = -50.0f;
  g_waterFieldActive = 1;
  g_waterHeights.Resize(cellCount);
  g_waterVelocities.Resize(g_waterGridWidth * g_waterGridHeight);

  for (SumoS32 index = 0; index < g_waterGridWidth * g_waterGridHeight;
       ++index) {
    SumoF32 wave = (SumoF32)sin(index * g_randomHalf);
    g_waterHeights[index] =
        wave * g_waterInitialWaveAmplitude + g_waterBaseHeight;
    g_waterVelocities[index] = 0.0f;
  }
}

extern SumoS32 g_screenTintLevel;
extern FloatVector g_waterHeights;
extern FloatVector g_waterVelocities;
extern SumoS32 g_waterGridWidth;
extern SumoS32 g_waterGridHeight;
extern const SumoF32 g_waterNeighborCoupling;
extern const SumoF32 g_waterVelocityDamping;
extern const SumoF64 g_waterCorrectionScale;
extern SumoF32 g_waterBaseHeight;
extern SumoF32 g_waterHeightCorrection;

void UpdateWaterField() {
  if (g_screenTintLevel % 3 != 0)
    return;
  //if (!g_waterHeights.HasElements())
    return;

  SumoS32 width = g_waterGridWidth;
  SumoS32 height = g_waterGridHeight;
  for (SumoS32 row = 0; row < height - 1; ++row) {
    for (SumoS32 column = 0; column < width - 1; ++column) {
      SumoS32 cell = row * width + column;
      SumoF32 rightDelta =
          (SumoF32)(((SumoF64)g_waterHeights[cell] - g_waterHeights[cell + 1]) *
                    g_waterNeighborCoupling);
      g_waterVelocities[cell] = g_waterVelocities[cell] - rightDelta;
      g_waterVelocities[cell + 1] = rightDelta + g_waterVelocities[cell + 1];
      SumoF32 downDelta =
          (SumoF32)(((SumoF64)g_waterHeights[cell] -
                     g_waterHeights[(row + 1) * width + column]) *
                    g_waterNeighborCoupling);
      g_waterVelocities[cell] = g_waterVelocities[cell] - downDelta;
      g_waterVelocities[(row + 1) * width + column] =
          downDelta + g_waterVelocities[(row + 1) * width + column];
    }
  }

  SumoF64 total = 0.0;
  SumoS32 cellCount = width * height;
  for (SumoS32 cell = 0; cell < cellCount; ++cell) {
    total = (SumoF64)g_waterHeights[cell] + total;
    g_waterHeights[cell] =
        (SumoF32)((SumoF64)g_waterHeights[cell] + g_waterVelocities[cell] +
                  g_waterHeightCorrection);
    g_waterVelocities[cell] = g_waterVelocities[cell] * g_waterVelocityDamping;
  }

  g_waterHeightCorrection =
      (SumoF32)(((SumoF64)g_waterBaseHeight - total / cellCount) *
                g_waterCorrectionScale);
}

extern SumoU8 g_waterFieldActive;
extern SumoF32 g_waterBaseHeight;
extern SumoS32 g_waterGridWidth;
extern SumoS32 g_waterGridHeight;
extern FloatVector g_waterHeights;
extern FloatVector g_waterVelocities;
extern SumoF32 g_gameGravityStep;
extern SumoF32 g_gameInverseSimulationStep;
extern const SumoF32 g_boxWaterAngularDamping;
extern const SumoF32 g_boxWaterBuoyancyScale;
extern const SumoF32 g_boxWaterDiagonalScale;
extern const SumoF32 g_boxWaterLinearDamping;
extern const SumoF32 g_boxWaterSurfaceOffset;
extern const SumoF32 g_boxWaterVerticalRetention;
extern const SumoF32 g_boxWaterWaveScale;

void GameBox::ApplyWaterInteraction() {
  if (!g_waterFieldActive)
    return;
  if (!(g_waterBaseHeight + 3.0f > position.y))
    return;
  SumoS32 gridX = (SumoS32)((SumoF64)g_gameInverseSimulationStep * position.x);
  SumoS32 gridZ = (SumoS32)((SumoF64)g_gameInverseSimulationStep * position.z);
  gridX += g_waterGridWidth / 2;
  gridZ += g_waterGridHeight / 2;
  if (gridX >= g_waterGridWidth || gridX < 0 || gridZ >= g_waterGridHeight ||
      gridZ < 0)
    return;

  SumoF64 depthWide =
      (SumoF64)g_waterHeights[gridZ * g_waterGridWidth + gridX] - position.y +
      g_boxWaterSurfaceOffset;
  SumoF32 depth = (SumoF32)depthWide;
  if (depthWide > (SumoF64)g_gameOne)
    depth = 1.0f;
  if (!(depth > g_vectorZero))
    return;

  if (depth < g_gameOne) {
    SumoF64 waveWide = sqrt((SumoF64)volume) * depth * g_boxWaterWaveScale;
    SumoF32 wave = (SumoF32)waveWide;
    SumoF32 diagonal = (SumoF32)(waveWide * g_boxWaterDiagonalScale);
    SumoS32 width = g_waterGridWidth;
    SumoS32 height = g_waterGridHeight;
    SumoS32 nextRow = gridZ + 1;
    SumoS32 nextColumn = gridX + 1;
    g_waterVelocities[(nextRow % height) * width + nextColumn % width] =
        g_waterVelocities[(nextRow % height) * width + nextColumn % width] +
        wave * linearVelocity.y;
    g_waterVelocities[(nextRow % height) * width +
                      (gridX + width - 1) % width] =
        g_waterVelocities[(nextRow % height) * width +
                          (gridX + width - 1) % width] +
        wave * linearVelocity.y;
    g_waterVelocities[((gridZ + height - 1) % height) * width +
                      nextColumn % width] =
        g_waterVelocities[((gridZ + height - 1) % height) * width +
                          nextColumn % width] +
        wave * linearVelocity.y;
    g_waterVelocities[((gridZ + height - 1) % height) * width +
                      (gridX + width - 1) % width] =
        g_waterVelocities[((gridZ + height - 1) % height) * width +
                          (gridX + width - 1) % width] +
        wave * linearVelocity.y;
    g_waterVelocities[(gridZ % height) * width + nextColumn % width] =
        g_waterVelocities[(gridZ % height) * width + nextColumn % width] +
        diagonal * linearVelocity.y;
    g_waterVelocities[(gridZ % height) * width + (gridX + width - 1) % width] =
        g_waterVelocities[(gridZ % height) * width +
                          (gridX + width - 1) % width] +
        diagonal * linearVelocity.y;
    g_waterVelocities[((gridZ + height - 1) % height) * width + gridX % width] =
        g_waterVelocities[((gridZ + height - 1) % height) * width +
                          gridX % width] +
        diagonal * linearVelocity.y;
    g_waterVelocities[(nextRow % height) * width + gridX % width] =
        g_waterVelocities[(nextRow % height) * width + gridX % width] +
        diagonal * linearVelocity.y;
    linearVelocity.y = linearVelocity.y * g_boxWaterVerticalRetention;
  }

  linearVelocity.y =
      (SumoF32)(linearVelocity.y -
                (SumoF64)g_gameGravityStep * depth * g_boxWaterBuoyancyScale);
  linearVelocity.x = linearVelocity.x * g_boxWaterLinearDamping;
  linearVelocity.y = linearVelocity.y * g_boxWaterLinearDamping;
  linearVelocity.z = linearVelocity.z * g_boxWaterLinearDamping;

  Vector3 probe;
  probe.x = 0.01f;
  probe.y = 0.0f;
  probe.z = 0.0f;
  Vector3 gravityAxis;
  gravityAxis.x = 0.0f;
  gravityAxis.y = g_gameGravityStep;
  gravityAxis.z = 0.0f;
  Vector3 torque = gravityAxis.Cross(probe.Transform(orientation));
  angularVelocity += torque;
  angularVelocity.x = angularVelocity.x * g_boxWaterAngularDamping;
  angularVelocity.y = angularVelocity.y * g_boxWaterAngularDamping;
  angularVelocity.z = angularVelocity.z * g_boxWaterAngularDamping;
}

//extern GameBox g_gameBoxes[512];
extern GameBox *g_gameBoxesEnd;
extern SumoF32 g_gameSimulationStep;
extern SumoF32 g_gameInverseSimulationStep;
extern const SumoF32 g_waterMotionThreshold;

void ApplyWaterInteractionToMovingBoxes() {
  g_gameInverseSimulationStep = 1.0f / g_gameSimulationStep;
  for (GameBox *box = g_gameBoxes; box < g_gameBoxesEnd; ++box) {
    //if (box->linearVelocity.LengthSquared() > g_waterMotionThreshold)
      box->ApplyWaterInteraction();
  }
}

extern SumoF32 g_gameGravityStep;

extern const SumoF32 g_randomHalf;

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

void GameCollisionCandidateHeap::Push(SumoF32 distance, Vector3 point) {
  GameCollisionCandidate candidate;
  candidate.distance = distance;
  candidate.point = point;
  entries[count] = candidate;
  ++count;

  SumoS32 index = count - 1;
  if (index == 0)
    return;
  do {
    SumoS32 parent = (index - 1) / 2;
    if (!(entries[parent].distance > entries[index].distance))
      return;
    GameCollisionCandidate swap = entries[parent];
    entries[parent] = entries[index];
    entries[index] = swap;
    index = parent;
  } while (index != 0);
}

Vector3 GameCollisionCandidateHeap::Pop() {
  Vector3 result;
  if (count <= 1) {
    result = entries[0].point;
    if (count != 0)
      --count;
    return result;
  }

  result = entries[0].point;
  entries[0] = entries[count - 1];

  SumoS32 parent = 0;
  SumoS32 child = 1;
  while (child < count) {
    if (child < count - 1) {
      if (entries[child].distance > entries[child + 1].distance)
        ++child;
    }
    if (entries[child].distance < entries[parent].distance) {
      GameCollisionCandidate swap = entries[parent];
      entries[parent] = entries[child];
      entries[child] = swap;
      parent = child;
    } else {
      break;
    }
    child = 2 * parent + 1;
  }

  --count;
  return result;
}

struct GameClipEdgeRecord {
  SumoS32 key;
  SumoS32 pointIndex;
  GameClipEdgeRecord *link;
};

void GameBox::ClipGeometry(GameBox &other, Vector3 &normal, SumoF32 distance) {
  GameClipEdgeRecord edgeScratch[1030];

  if (((SumoS32)((SumoU8 *)other.pointsEnd - (SumoU8 *)other.pointsBegin) &
       ~0xf) > 0x1000 ||
      (SumoS32)(other.facesEnd - other.facesBegin) > 0x100) {
    facesEnd = facesBegin;
    pointsEnd = pointsBegin;
    return;
  }

  SumoU8 anyInside = 0;
  if (other.pointsBegin >= other.pointsEnd) {
    facesEnd = facesBegin;
    return;
  }
  for (GameBoxPoint *point = other.pointsBegin; point < other.pointsEnd;
       ++point) {
    SumoU8 inside = 1;
    if (!(point->position.z * normal.z + point->position.y * normal.y +
              point->position.x * normal.x >
          distance))
      inside = 0;
    point->clipIndex = (SumoS16)-1;
    point->clipSide = inside;
    anyInside |= inside;
  }
  if (anyInside == 0) {
    facesEnd = facesBegin;
    return;
  }

  GameBoxPoint *pointCursor = pointsBegin;
  GameBoxPointReference *referenceCursor = pointReferencesBegin;
  GameBoxFace *faceCursor = facesBegin;
  SumoS32 newPointCount = 0;
  GameClipEdgeRecord *edgeCursor = edgeScratch;
  if (referenceCursor == 0)
    return;

  for (GameBoxFace *sourceFace = other.facesBegin; sourceFace < other.facesEnd;
       ++sourceFace) {
    GameBoxPointReference *reference = sourceFace->pointReferences;
    GameBoxPointReference *previous =
        &sourceFace->pointReferences[sourceFace->pointCount - 1];
    GameClipEdgeRecord *enterRecord = 0;
    GameClipEdgeRecord *exitRecord = 0;
    faceCursor->pointReferences = referenceCursor;
    SumoS32 emitted = 0;

    for (SumoS32 referenceIndex = 0; referenceIndex < sourceFace->pointCount;
         ++referenceIndex) {
      if ((reference->point->clipSide ^ previous->point->clipSide) != 0) {
        SumoS32 searchKey = (reference->index << 16) + previous->index;
        GameClipEdgeRecord *record = edgeScratch;
        while (record < edgeCursor && record->key != searchKey)
          ++record;

        if (record == edgeCursor) {
          record->key = (previous->index << 16) + reference->index;
          record->pointIndex = newPointCount;
          record->link = 0;
          ++edgeCursor;

          GameBoxPoint *start = previous->point;
          GameBoxPoint *end = reference->point;
          SumoF32 fraction =
              (start->position.z * normal.z + start->position.y * normal.y +
               start->position.x * normal.x - distance) /
              (start->position.z * normal.z + start->position.y * normal.y +
               normal.x * start->position.x -
               (end->position.z * normal.z + end->position.y * normal.y +
                normal.x * end->position.x));
          pointCursor->position =
              start->position -
              (start->position - end->position).Scale(fraction);
          pointCursor->flag0D = 1;
          ++pointCursor;
          ++newPointCount;
        }

        if (reference->point->clipSide != 0)
          enterRecord = record;
        else
          exitRecord = record;
        referenceCursor->index = record->pointIndex;
        referenceCursor->point = pointsBegin + record->pointIndex;
        ++referenceCursor;
        ++emitted;
      }

      if (reference->point->clipSide != 0) {
        if (reference->point->clipIndex == (SumoS16)-1) {
          *pointCursor = *reference->point;
          ++pointCursor;
          reference->point->clipIndex = (SumoS16)newPointCount;
          ++newPointCount;
        }
        referenceCursor->index = reference->point->clipIndex;
        referenceCursor->point = pointsBegin + reference->point->clipIndex;
        ++referenceCursor;
        ++emitted;
      }

      previous = reference;
      ++reference;
    }

    if (emitted >= 3) {
      faceCursor->pointCount = emitted;
      faceCursor->preserveState = sourceFace->preserveState;
      faceCursor->normal = sourceFace->normal;
      faceCursor->planeDistance = sourceFace->planeDistance;
      faceCursor->state = sourceFace->state;
      if (enterRecord != 0) {
        enterRecord->link = exitRecord;
        UpdateFacePlane(*faceCursor);
      }
      ++faceCursor;
    }
  }

  if (edgeCursor != edgeScratch) {
    GameBoxFace *capFace = faceCursor;
    SumoS32 capCount = 0;
    capFace->pointReferences = referenceCursor;
    for (GameClipEdgeRecord *record = edgeScratch; record < edgeCursor;
         ++record) {
      if (record->pointIndex == -1)
        continue;
      GameClipEdgeRecord *chain = record;
      do {
        referenceCursor->index = chain->pointIndex;
        referenceCursor->point = pointsBegin + chain->pointIndex;
        ++referenceCursor;
        ++capCount;
        chain->pointIndex = -1;
        chain = chain->link;
      } while (chain != record && chain != 0);
      if (chain == 0) {
        facesEnd = facesBegin;
        return;
      }
    }
    capFace->pointCount = capCount;
    UpdateFacePlane(*capFace);
    capFace->state = -1.0f;
    ++faceCursor;
  }

  facesEnd = faceCursor;
  pointReferencesEnd = referenceCursor;
  pointsEnd = pointCursor;
}

extern GameBox g_cutPlaneBox;
extern GameBox g_clipScratchBox;
extern GameCollisionPointRecord *g_gameCollisionPointsEnd;
extern GameCollisionCorrectionRecord *g_gameCollisionCorrectionsEnd;
extern SumoF32 g_gameCollisionScale;
extern SumoF32 g_gameDecorationHeight;
extern const SumoF32 g_gameOne;
extern SumoS32 g_screenTintLevel;

SumoS32 GenerateGameBoxCollisionContacts(GameBox *first, GameBox *second) {
  for (GameBoxContactLink *link = first->contactLinks; link != 0;
       link = link->next) {
    if (link->other == second)
      return 0;
  }

  GameCollisionCandidateHeap heap;
  heap.count = 0;
  GameBox *destination = &g_cutPlaneBox;
  GameBox *spare = &g_clipScratchBox;

  Matrix3 relativeOrientation = second->orientation.Transposed().Multiply(
      first->orientation.Transposed());
  Vector3 relativePosition =
      second->orientation.Transform(first->position - second->position);

  for (GameBoxFace *face = second->facesBegin; face < second->facesEnd;
       ++face) {
    heap.Push(-(face->planeDistance - (relativePosition.y * face->normal.y +
                                       relativePosition.z * face->normal.z +
                                       relativePosition.x * face->normal.x)),
              relativeOrientation.Transform(face->normal));
  }

  GameBox *source = first;
  while (heap.count != 0) {
    SumoF32 planeDistance = -heap.entries[0].distance;
    Vector3 planeNormal = heap.entries[0].point;
    heap.Pop();
    destination->ClipGeometry(*source, planeNormal, planeDistance);
    if (destination->facesEnd == destination->facesBegin)
      return 0;
    source = destination;
    GameBox *swap = spare;
    spare = destination;
    destination = swap;
  }
  GameBox *clipped = source;

  clipped->RecalculateMass();
  Vector3 worldNormal = clipped->faceNormalSum.Transform(first->orientation);
  if (worldNormal.z * worldNormal.z + worldNormal.y * worldNormal.y +
          worldNormal.x * worldNormal.x <
      1e-20f)
    return 1;
  worldNormal.Normalize();

  Vector3 *warmStart = 0;
  SumoS32 warmCount = 0;
  for (GameCollisionFeatureLink *feature = first->collisionFeatures;
       feature != 0; feature = feature->next) {
    if (feature->other == second) {
      warmStart = feature->features;
      warmCount = feature->featureCount;
      break;
    }
  }

  for (GameBoxPoint *point = clipped->pointsBegin; point < clipped->pointsEnd;
       ++point) {
    if (point->flag0D == 0)
      continue;
    GameCollisionPointRecord *record = g_gameCollisionPointsEnd;
    record->point =
        point->position.Transform(first->orientation) + first->position;
    record->normal = -worldNormal;
    Vector3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    record->accumulatedImpulse = zero;
    record->boxes[0] = first;
    record->boxes[1] = second;
    SumoS32 iterationCount = first->modeE0;
    if (iterationCount <= second->modeE0)
      iterationCount = second->modeE0;
    record->iterationCount = iterationCount;
    record->hasFeature = 0;
    if (warmCount != 0) {
      record->hasFeature = 1;
      --warmCount;
      record->accumulatedImpulse = *warmStart;
      ++warmStart;
    }
    g_gameCollisionPointsEnd = record + 1;
  }

  if (g_gameCollisionCorrectionsEnd > g_gameCollisionCorrections + 8192)
    return 1;

  if (!(clipped->volume > 1e-9f))
    return 1;

  Vector3 worldCenter =
      clipped->accumulatedOffset.Transform(first->orientation) +
      first->position;
  SumoF32 impulseScale = clipped->volume /
                         (first->inverseMass + second->inverseMass) *
                         g_gameCollisionScale;
  GameCollisionCorrectionRecord *correction = g_gameCollisionCorrectionsEnd;
  correction->impulse = worldNormal.Scale(impulseScale);
  correction->point = worldCenter;
  correction->boxes[0] = first;
  correction->boxes[1] = second;
  g_gameCollisionCorrectionsEnd = correction + 1;

  if (second->contactLinks == 0 && second->volume > 200.0f) {
    Vector3 probe;
    probe.x = 0.0f;
    probe.y = 5.0f;
    probe.z = 0.0f;
    SumoF32 threshold = g_gameDecorationHeight + g_gameOne;
    if ((worldCenter - probe).LengthSquared() > threshold * threshold)
      first->unknownDC = g_screenTintLevel;
    first->unknownD8 = g_screenTintLevel;
  }
  if (first->contactLinks == 0 && first->volume > 200.0f) {
    Vector3 probe;
    probe.x = 0.0f;
    probe.y = 5.0f;
    probe.z = 0.0f;
    SumoF32 threshold = g_gameDecorationHeight + g_gameOne;
    if ((worldCenter - probe).LengthSquared() > threshold * threshold)
      second->unknownDC = g_screenTintLevel;
    second->unknownD8 = g_screenTintLevel;
  }

  first->unknownD4 = g_screenTintLevel;
  second->unknownD4 = g_screenTintLevel;
  if (second->immovable == 0)
    first->sleepCounter = 0;
  if (first->immovable == 0)
    second->sleepCounter = 0;
  first->sleeping = 0;
  second->sleeping = 0;
  return 1;
}

extern GameBox g_gameBoxes[2048];
extern GameBox *g_gameBoxesEnd;
extern SumoU8 g_gameContactObjects[0xf400];
extern SumoU8 *g_gameContactObjectsEnd;
//extern GameCollisionPointRecord g_gameCollisionPoints[8192];
extern GameCollisionPointRecord *g_gameCollisionPointsEnd;
//extern GameCollisionCorrectionRecord g_gameCollisionCorrections[2048];
extern GameCollisionCorrectionRecord *g_gameCollisionCorrectionsEnd;
extern GameCollisionFeatureLink g_gameCollisionFeatureLinks[8192];
extern GameCollisionFeatureLink *g_gameCollisionFeatureLinksEnd;
extern void *g_gameCollisionGroupRoot;
extern SumoU8 g_gameCollisionGroupSentinel;
extern SumoU8 g_gameCollisionPointScratchFlag;
extern const SumoF32 g_gameOne;
extern const SumoF32 g_gameNegativeHalf;
extern const SumoF32 g_gameCameraHeightScale;
extern const SumoF32 g_gameCameraInputDamping;

SumoS32 GenerateGameBoxCollisionContacts(GameBox *first, GameBox *second);

SumoU8 FractureGameBoxAtPoint(Vector3 &position, GameBox *box);
SumoF64 ParserAtan2(SumoF32 y, SumoF32 x);

void ResolveGameCollisions() {
  g_gameCollisionPointsEnd = g_gameCollisionPoints;
  g_gameCollisionCorrectionsEnd = g_gameCollisionCorrections;

  for (GameBox *outer = g_gameBoxes; outer < g_gameBoxesEnd; ++outer) {
    if (outer->flag58)
      continue;
    if (outer->immovable == 0 && outer->sleeping == 0) {
      if (outer <= g_gameBoxes)
        continue;
      for (GameBox *inner = g_gameBoxes; inner < outer; ++inner) {
        if (inner->flag58)
          continue;
        if (outer->immovable)
          continue;
        SumoF32 radiusSum = inner->boundingRadius + outer->boundingRadius;
        Vector3 difference = outer->position - inner->position;
        if ((SumoF64)radiusSum * radiusSum > difference.LengthSquared())
          GenerateGameBoxCollisionContacts(outer, inner);
      }
    } else {
      if (outer <= g_gameBoxes)
        continue;
      for (GameBox *inner = g_gameBoxes; inner < outer; ++inner) {
        if (inner->flag58)
          continue;
        if (inner->sleeping)
          continue;
        if (inner->immovable)
          continue;
        SumoF32 radiusSum = inner->boundingRadius + outer->boundingRadius;
        Vector3 difference = outer->position - inner->position;
        if ((SumoF64)radiusSum * radiusSum > difference.LengthSquared())
          GenerateGameBoxCollisionContacts(outer, inner);
      }
    }
  }

  for (GameBoxJoint *joint = (GameBoxJoint *)g_gameContactObjects;
       (SumoU8 *)joint < g_gameContactObjectsEnd; ++joint) {

    if (!joint->boxes[0] || !joint->boxes[1])
      continue;
    GameBox *first = joint->boxes[0];
    if (first->flag58)
      continue;
    GameBox *second = joint->boxes[1];
    if (second->flag58)
      continue;

    Vector3 angularDifference =
        first->angularVelocity - second->angularVelocity;
    SumoF32 dampScale = (SumoF32)(-0.2f / ((SumoF64)first->inverseInertia +
                                           second->inverseInertia));
    Vector3 dampImpulse = angularDifference.Scale(dampScale);
    ApplyPairedAngularImpulse(joint->boxes, dampImpulse);

    first = joint->boxes[0];
    joint->limitFlags = 0;
    Vector3 firstAnchor =
        joint->localAnchors[0].Transform(first->orientation) + first->position;
    second = joint->boxes[1];
    Vector3 secondAnchor =
        joint->localAnchors[1].Transform(second->orientation) +
        second->position;

    Matrix3 secondResponse =
        second->CalculateImpulseResponseMatrix(secondAnchor, secondAnchor);
    Matrix3 firstResponse =
        first->CalculateImpulseResponseMatrix(firstAnchor, firstAnchor);
    joint->inverseResponse = (firstResponse + secondResponse).Inverted();

    SumoF32 unitScale = 1.0f;
    Vector3 impulse = joint->initialImpulse.Scale(unitScale);
    if (first->immovable == 0) {
      Vector3 negativeImpulse = -impulse;
      first->ApplyImpulseAtPoint(firstAnchor, negativeImpulse);
    }
    if (joint->boxes[1]->immovable == 0)
      joint->boxes[1]->ApplyImpulseAtPoint(secondAnchor, impulse);

    Vector3 firstDirection =
        joint->firstPoseDirection.Transform(joint->boxes[0]->orientation);
    Vector3 secondDirection =
        joint->secondAnchorDirection.Transform(joint->boxes[1]->orientation);
    Vector3 anchorCross = firstDirection.Cross(secondDirection);
    SumoF32 anchorCrossLengthSquared =
        (SumoF32)((SumoF64)anchorCross.x * anchorCross.x +
                  (SumoF64)anchorCross.z * anchorCross.z +
                  (SumoF64)anchorCross.y * anchorCross.y);
    Vector3 anchorAxis = anchorCross;
    anchorAxis.Normalize();
    Vector3 poseDirection =
        joint->secondPoseDirection.Transform(joint->boxes[0]->orientation);
    Vector3 axisDirection =
        joint->secondAxis.Transform(joint->boxes[1]->orientation);
    Vector3 poseCross = poseDirection.Cross(axisDirection);

    if (joint->state != 0.0f) {
      SumoF32 hingeScale = 0.01f;
      Vector3 hingeImpulse = poseCross.Scale(hingeScale);
      joint->boxes[0]->ApplyAngularImpulse(firstAnchor, hingeImpulse);
      Vector3 negativeHinge = (-poseCross).Scale(hingeScale);
      joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeHinge);
      joint->limitFlags |= 4;
      poseCross.Normalize();
      SumoF32 warmImpulse = joint->secondLimitImpulse;
      joint->secondLimitAxis = poseCross;
      Vector3 warmScaled = poseCross.Scale(warmImpulse);
      joint->boxes[0]->ApplyAngularImpulse(firstAnchor, warmScaled);
      Vector3 negativeWarm = (-poseCross).Scale(warmImpulse);
      joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeWarm);
    } else {
      SumoF32 crossLength = (SumoF32)sqrt((SumoF64)anchorCrossLengthSquared);
      SumoF32 directionDot =
          (SumoF32)((SumoF64)secondDirection.x * firstDirection.x +
                    (SumoF64)secondDirection.z * firstDirection.z +
                    (SumoF64)secondDirection.y * firstDirection.y);
      SumoF64 angleFull = -ParserAtan2(crossLength, directionDot);
      SumoF32 angle = (SumoF32)angleFull;
      SumoF32 cosine = (SumoF32)cos(angleFull);
      SumoF32 sine = (SumoF32)sin((SumoF64)angle);
      poseDirection.Rotate(anchorAxis, cosine, sine);
      SumoF64 poseCrossSquared = (SumoF64)poseCross.x * poseCross.x +
                                 (SumoF64)poseCross.z * poseCross.z +
                                 (SumoF64)poseCross.y * poseCross.y;
      volatile SumoF32 poseCrossSquaredRounded = (SumoF32)poseCrossSquared;
      if (!(poseCrossSquared > joint->maximumAngle)) {
        joint->secondLimitImpulse = 0.0f;
      } else {
        joint->limitFlags |= 2;
        Vector3 twistAxis = poseDirection.Cross(axisDirection);
        SumoF32 halfAngle = (SumoF32)(angle * g_gameNegativeHalf);
        SumoF32 halfCosine = (SumoF32)cos((SumoF64)halfAngle);
        SumoF32 halfSine = (SumoF32)sin((SumoF64)halfAngle);
        twistAxis.Rotate(anchorAxis, halfCosine, halfSine);
        twistAxis.Normalize();
        SumoF32 limitRoot = (SumoF32)sqrt((SumoF64)joint->maximumAngle);
        joint->secondLimitAxis = twistAxis;
        SumoF32 magnitude =
            (SumoF32)((sqrt((SumoF64)poseCrossSquaredRounded) - limitRoot) *
                          0.04f /
                          ((SumoF64)joint->boxes[0]->inverseInertia +
                           joint->boxes[1]->inverseInertia) +
                      joint->secondLimitImpulse);
        Vector3 twistImpulse = twistAxis.Scale(magnitude);
        joint->boxes[0]->ApplyAngularImpulse(firstAnchor, twistImpulse);
        Vector3 negativeTwist = (-twistAxis).Scale(magnitude);
        joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeTwist);
      }
    }

    if (anchorCrossLengthSquared >= joint->minimumAngle) {
      joint->limitFlags |= 1;
      joint->firstLimitAxis = anchorAxis;
      SumoF32 swingRoot = (SumoF32)sqrt((SumoF64)joint->minimumAngle);
      SumoF32 swingMagnitude =
          (SumoF32)((sqrt((SumoF64)anchorCrossLengthSquared) - swingRoot) *
                        0.2f /
                        ((SumoF64)joint->boxes[0]->inverseInertia +
                         joint->boxes[1]->inverseInertia) +
                    joint->firstLimitImpulse);
      Vector3 swingImpulse = anchorAxis.Scale(swingMagnitude);
      joint->boxes[0]->ApplyAngularImpulse(firstAnchor, swingImpulse);
      Vector3 negativeSwing = (-anchorAxis).Scale(swingMagnitude);
      joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeSwing);
    }
  }

  g_gameCollisionGroupRoot = &g_gameCollisionGroupSentinel;
  for (GameCollisionPointRecord *record = g_gameCollisionPoints;
       record < g_gameCollisionPointsEnd; ++record) {
    record->groupFirst = &g_gameCollisionGroupSentinel;
    Matrix3 firstResponse = record->boxes[0]->CalculateImpulseResponseMatrix(
        record->point, record->point);
    Matrix3 secondResponse = record->boxes[1]->CalculateImpulseResponseMatrix(
        record->point, record->point);
    Matrix3 responseSum = firstResponse + secondResponse;
    record->groupLast = &g_gameCollisionGroupSentinel;
    g_gameCollisionPointScratchFlag = 0;
    record->inverseResponse = responseSum.Inverted();
  }

  for (SumoS32 iteration = 0; iteration < 40; ++iteration) {
    for (GameCollisionPointRecord *record = g_gameCollisionPoints;
         record < g_gameCollisionPointsEnd; ++record) {
      SumoS32 remaining = record->iterationCount;
      if (remaining == 0)
        continue;
      record->iterationCount = remaining - 1;

      Vector3 delta;
      if (iteration != 0) {
        Vector3 secondVelocity =
            record->boxes[1]->VelocityAtPoint(record->point);
        Vector3 relative =
            record->boxes[0]->VelocityAtPoint(record->point) - secondVelocity;
        Vector3 accumulated = relative.Transform(record->inverseResponse);
        accumulated.x = accumulated.x + record->accumulatedImpulse.x;
        accumulated.y = accumulated.y + record->accumulatedImpulse.y;
        accumulated.z = accumulated.z + record->accumulatedImpulse.z;
        volatile SumoF32 normalComponentPin =
            (SumoF32)((SumoF64)accumulated.z * record->normal.z +
                      (SumoF64)accumulated.y * record->normal.y +
                      (SumoF64)accumulated.x * record->normal.x);
        SumoF32 normalComponent = normalComponentPin;
        Vector3 tangential =
            accumulated - record->normal.Scale(normalComponent);
        Vector3 updated;
        if (normalComponent >= g_vectorZero) {
          SumoF64 tangentialLengthSquared =
              (SumoF64)tangential.z * tangential.z +
              (SumoF64)tangential.y * tangential.y +
              (SumoF64)tangential.x * tangential.x;
          if (tangentialLengthSquared != 0.0) {
            if ((SumoF64)normalComponent * normalComponent *
                    0.809999942779541f <
                tangentialLengthSquared) {
              SumoF64 frictionScale = normalComponent /
                                      sqrt(tangentialLengthSquared) *
                                      g_gameCameraInputDamping;
              tangential.x = (SumoF32)(tangential.x * frictionScale);
              tangential.y = (SumoF32)(tangential.y * frictionScale);
              tangential.z = (SumoF32)(tangential.z * frictionScale);
            }
          }
          updated = tangential + record->normal.Scale(normalComponent);
        } else {
          updated.x = 0.0f;
          updated.y = 0.0f;
          updated.z = 0.0f;
        }
        volatile SumoF32 deltaXPin = updated.x - record->accumulatedImpulse.x;
        delta.x = deltaXPin;
        record->accumulatedImpulse.x = delta.x + record->accumulatedImpulse.x;
        volatile SumoF32 deltaYPin = updated.y - record->accumulatedImpulse.y;
        delta.y = deltaYPin;
        record->accumulatedImpulse.y = delta.y + record->accumulatedImpulse.y;
        volatile SumoF32 deltaZPin = updated.z - record->accumulatedImpulse.z;
        delta.z = deltaZPin;
        record->accumulatedImpulse.z = delta.z + record->accumulatedImpulse.z;
      } else {
        delta = record->accumulatedImpulse;
      }

      GameBox *first = record->boxes[0];
      if (first->immovable == 0) {
        Vector3 negativeDelta = -delta;
        first->ApplyImpulseAtPoint(record->point, negativeDelta);
      }
      if (record->boxes[1]->immovable == 0)
        record->boxes[1]->ApplyImpulseAtPoint(record->point, delta);
      record->boxes[0]->collisionFeatures = 0;
    }

    for (GameBoxJoint *joint = (GameBoxJoint *)g_gameContactObjects;
         (SumoU8 *)joint < g_gameContactObjectsEnd; ++joint) {
      GameBox *first = joint->boxes[0];
      if (!joint->boxes[0] || !joint->boxes[1])
          continue;

      if (first->flag58)
        continue;
      GameBox *second = joint->boxes[1];
      if (second->flag58)
        continue;

      Vector3 firstAnchor =
          joint->localAnchors[0].Transform(first->orientation) +
          first->position;
      Vector3 secondAnchor =
          joint->localAnchors[1].Transform(second->orientation) +
          second->position;
      Vector3 secondVelocity = second->VelocityAtPoint(secondAnchor);
      Vector3 relative = first->VelocityAtPoint(firstAnchor) - secondVelocity;
      SumoF32 biasScale = 0.03f;
      Vector3 impulse =
          (relative - (secondAnchor - firstAnchor).Scale(biasScale))
              .Transform(joint->inverseResponse);
      if (first->immovable == 0) {
        Vector3 negativeImpulse = -impulse;
        first->ApplyImpulseAtPoint(firstAnchor, negativeImpulse);
      }
      if (joint->boxes[1]->immovable == 0)
        joint->boxes[1]->ApplyImpulseAtPoint(secondAnchor, impulse);

      if (joint->limitFlags & 4) {
        GameBox *limitSecond = joint->boxes[1];
        GameBox *limitFirst = joint->boxes[0];
        Vector3 angularDifference =
            limitFirst->angularVelocity - limitSecond->angularVelocity;
        SumoF64 responseScale =
            g_gameCameraInputDamping /
            ((SumoF64)limitFirst->inverseInertia + limitSecond->inverseInertia);
        SumoF64 target =
            ((SumoF64)angularDifference.y * joint->secondLimitAxis.y +
             (SumoF64)angularDifference.z * joint->secondLimitAxis.z +
             (SumoF64)angularDifference.x * joint->secondLimitAxis.x) *
                responseScale +
            joint->secondLimitImpulse;
        if (target < g_vectorZero)
          target = 0.0;
        SumoF64 change = target - joint->secondLimitImpulse;
        SumoF32 changeRounded = (SumoF32)change;
        joint->secondLimitImpulse =
            (SumoF32)(change + joint->secondLimitImpulse);
        Vector3 scaled = joint->secondLimitAxis.Scale(changeRounded);
        limitFirst->ApplyAngularImpulse(firstAnchor, scaled);
        SumoF32 negativeChange = -changeRounded;
        Vector3 negativeScaled = joint->secondLimitAxis.Scale(negativeChange);
        joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeScaled);
      }

      if (joint->limitFlags & 1) {
        GameBox *limitSecond = joint->boxes[1];
        GameBox *limitFirst = joint->boxes[0];
        Vector3 angularDifference =
            limitFirst->angularVelocity - limitSecond->angularVelocity;
        SumoF64 responseScale =
            g_gameCameraInputDamping /
            ((SumoF64)limitFirst->inverseInertia + limitSecond->inverseInertia);
        SumoF64 target =
            ((SumoF64)joint->firstLimitAxis.z * angularDifference.z +
             (SumoF64)angularDifference.y * joint->firstLimitAxis.y +
             (SumoF64)angularDifference.x * joint->firstLimitAxis.x) *
                responseScale +
            joint->firstLimitImpulse;
        if (target < g_vectorZero)
          target = 0.0;
        SumoF64 change = target - joint->firstLimitImpulse;
        SumoF32 changeRounded = (SumoF32)change;
        joint->firstLimitImpulse = (SumoF32)(change + joint->firstLimitImpulse);
        Vector3 scaled = joint->firstLimitAxis.Scale(changeRounded);
        limitFirst->ApplyAngularImpulse(firstAnchor, scaled);
        SumoF32 negativeChange = -changeRounded;
        Vector3 negativeScaled = joint->firstLimitAxis.Scale(negativeChange);
        joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeScaled);
      }

      if (joint->limitFlags & 2) {
        GameBox *limitSecond = joint->boxes[1];
        GameBox *limitFirst = joint->boxes[0];
        Vector3 angularDifference =
            limitFirst->angularVelocity - limitSecond->angularVelocity;
        SumoF64 responseScale =
            g_gameCameraInputDamping /
            ((SumoF64)limitFirst->inverseInertia + limitSecond->inverseInertia);
        SumoF64 target =
            ((SumoF64)angularDifference.y * joint->secondLimitAxis.y +
             (SumoF64)angularDifference.z * joint->secondLimitAxis.z +
             (SumoF64)joint->secondLimitAxis.x * angularDifference.x) *
                responseScale +
            joint->secondLimitImpulse;
        if (target < g_vectorZero)
          target = 0.0;
        SumoF64 change = target - joint->secondLimitImpulse;
        SumoF32 changeRounded = (SumoF32)change;
        joint->secondLimitImpulse =
            (SumoF32)(change + joint->secondLimitImpulse);
        Vector3 scaled = joint->secondLimitAxis.Scale(changeRounded);
        limitFirst->ApplyAngularImpulse(firstAnchor, scaled);
        SumoF32 negativeChange = -changeRounded;
        Vector3 negativeScaled = joint->secondLimitAxis.Scale(negativeChange);
        joint->boxes[1]->ApplyAngularImpulse(secondAnchor, negativeScaled);
      }
    }

    ApplyGameManPoseConstraints();
  }

  for (GameBox *box = g_gameBoxes; box < g_gameBoxesEnd; ++box)
    box->collisionFeatures = 0;
  g_gameCollisionFeatureLinksEnd = g_gameCollisionFeatureLinks;
  g_gameCollisionPointsEnd->boxes[1] = 0;

  if (g_gameCollisionPoints < g_gameCollisionPointsEnd) {
    Vector3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    GameCollisionPointRecord *record = g_gameCollisionPoints;
    do {
      g_gameCollisionFeatureLinksEnd->featureCount = 0;
      SumoF32 magnitudeSum = 0.0f;
      GameBox *secondBox = record->boxes[1];
      Vector3 positionSum = zero;
      GameBox *firstBox = record->boxes[0];
      SumoS32 sampleCount = 0;
      SumoU8 decorationFlag = record->hasFeature;
      GameCollisionPointRecord *runStart = record;
      for (;;) {
        if (record->boxes[0] != firstBox)
          break;
        if (g_gameCollisionFeatureLinksEnd->featureCount >= 16)
          break;
        volatile SumoF32 magnitudePin =
            (SumoF32)(sqrt(
                          (SumoF64)record->accumulatedImpulse.LengthSquared()) +
                      magnitudeSum);
        magnitudeSum = magnitudePin;
        ++sampleCount;
        GameCollisionFeatureLink *link = g_gameCollisionFeatureLinksEnd;
        positionSum.x = positionSum.x + record->point.x;
        positionSum.y = positionSum.y + record->point.y;
        positionSum.z = positionSum.z + record->point.z;
        link->features[link->featureCount] = record->accumulatedImpulse;
        ++g_gameCollisionFeatureLinksEnd->featureCount;
        ++record;
        if (record->boxes[1] != secondBox)
          break;
      }
      GameCollisionPointRecord *lastRecord = record - 1;

      if (magnitudeSum > g_gameCameraHeightScale && decorationFlag == 0) {
        GameBox *soundBox = lastRecord->boxes[0];
        if ((SumoF64)soundBox->mass * 0.04f < magnitudeSum &&
            soundBox->unknownC0 != 0 &&
            (SumoF64)soundBox->activityValue * 3.0f < magnitudeSum) {
          SumoF32 frequency = (SumoF32)exp(
              log((SumoF64)soundBox->volume / soundBox->unknownC8) * -0.25f);
          soundBox = lastRecord->boxes[0];
          SumoF32 soundVolume =
              (SumoF32)((SumoF64)magnitudeSum * soundBox->unknownC4);
          PlayGameSound(soundBox->unknownC0, frequency, soundVolume, 0,
                        soundBox->position);
        }
        soundBox = lastRecord->boxes[0];
        if (magnitudeSum > soundBox->activityValue)
          soundBox->activityValue = magnitudeSum;
        soundBox = lastRecord->boxes[1];
        if ((SumoF64)soundBox->mass * 0.04f < magnitudeSum &&
            soundBox->unknownC0 != 0 &&
            (SumoF64)soundBox->activityValue * 3.0f < magnitudeSum) {
          SumoF32 frequency = (SumoF32)exp(
              log((SumoF64)soundBox->volume / soundBox->unknownC8) * -0.25f);
          soundBox = lastRecord->boxes[1];
          SumoF32 soundVolume =
              (SumoF32)((SumoF64)magnitudeSum * soundBox->unknownC4);
          PlayGameSound(soundBox->unknownC0, frequency, soundVolume, 0,
                        soundBox->position);
        }
        soundBox = lastRecord->boxes[1];
        if (magnitudeSum > soundBox->activityValue)
          soundBox->activityValue = magnitudeSum;
      }

      GameCollisionPointRecord *shed = runStart;
      if (magnitudeSum > lastRecord->boxes[0]->breakability) {
        if (shed < lastRecord) {
          SumoF32 quarter = 0.25f;
          SumoF32 negativeQuarter = 0.25f;
          do {
            Vector3 scaled = shed->accumulatedImpulse.Scale(quarter);
            shed->boxes[0]->ApplyImpulseAtPoint(shed->point, scaled);
            Vector3 negativeScaled =
                (-shed->accumulatedImpulse).Scale(negativeQuarter);
            shed->boxes[1]->ApplyImpulseAtPoint(shed->point, negativeScaled);
            ++shed;
          } while (shed < lastRecord);
        }
        SumoF32 inverseCount = (SumoF32)(g_gameOne / (SumoF64)sampleCount);
        Vector3 meanPosition = positionSum.Scale(inverseCount);
        FractureGameBoxAtPoint(meanPosition, lastRecord->boxes[0]);
      }

      if (magnitudeSum > lastRecord->boxes[1]->breakability) {
        if (shed < lastRecord) {
          SumoF32 quarter = 0.25f;
          SumoF32 negativeQuarter = 0.25f;
          do {
            Vector3 scaled = shed->accumulatedImpulse.Scale(quarter);
            shed->boxes[0]->ApplyImpulseAtPoint(shed->point, scaled);
            Vector3 negativeScaled =
                (-shed->accumulatedImpulse).Scale(negativeQuarter);
            shed->boxes[1]->ApplyImpulseAtPoint(shed->point, negativeScaled);
            ++shed;
          } while (shed < lastRecord);
        }
        SumoF32 inverseCount = (SumoF32)(g_gameOne / (SumoF64)sampleCount);
        Vector3 meanPosition = positionSum.Scale(inverseCount);
        FractureGameBoxAtPoint(meanPosition, lastRecord->boxes[1]);
      }

      GameCollisionFeatureLink *link = g_gameCollisionFeatureLinksEnd;
      link->next = lastRecord->boxes[0]->collisionFeatures;
      link->other = lastRecord->boxes[1];
      lastRecord->boxes[0]->collisionFeatures = link;
      g_gameCollisionFeatureLinksEnd = link + 1;
      record = lastRecord + 1;
    } while (record < g_gameCollisionPointsEnd);
  }

  for (GameCollisionCorrectionRecord *correction = g_gameCollisionCorrections;
       correction < g_gameCollisionCorrectionsEnd; ++correction) {
    correction->boxes[0]->ApplyImpulseAtPoint(correction->point,
                                              correction->impulse);
    Vector3 negativeImpulse = -correction->impulse;
    correction->boxes[1]->ApplyImpulseAtPoint(correction->point,
                                              negativeImpulse);
  }
}

#pragma intrinsic(memset)

DECOMP_SIZE_ASSERT(GameBox, 0xfc);
DECOMP_SIZE_ASSERT(GameBoxPoint, 0x10);
DECOMP_SIZE_ASSERT(GameBoxPointReference, 0x08);
DECOMP_SIZE_ASSERT(GameBoxFace, 0x24);

// GLOBAL: SUMO 0x00453708
// GLOBAL: EDITOR 0x00453708
SumoS32 g_boxFaceIndices[30] = {2, 3, 7, 6, -1, 3, 1, 5, 7, -1, 0, 1, 3, 2, -1,
                                0, 2, 6, 4, -1, 1, 0, 4, 5, -1, 6, 7, 5, 4, -1};

// FUNCTION: SUMO 0x004087b4
// FUNCTION: EDITOR 0x004087d6
void GameBox::ReserveGeometry(SumoS32 pointCapacity, SumoS32 referenceCapacity,
                              SumoS32 faceCapacity) {
  pointsBegin = (GameBoxPoint *)operator new(pointCapacity << 6);
  pointReferencesBegin =
      (GameBoxPointReference *)operator new(referenceCapacity << 5);
  facesBegin = (GameBoxFace *)operator new(faceCapacity * 144);
}

// FUNCTION: SUMO 0x004088dc
// FUNCTION: EDITOR 0x004088fe
void GameBox::InitializeGeometry(Vector3 *sourcePoints, SumoS32 pointCount,
                                 SumoS32 *faceIndices, SumoS32 indexCount) {
  ReserveGeometry(512, 2048, 512);

  GameBoxPoint *point = pointsBegin;
  SumoS32 remainingPoints = pointCount;
  if (remainingPoints > 0) {
    do {
      point->position = *sourcePoints;
      point->flag0D = 0;
      ++point;
      ++sourcePoints;
      --remainingPoints;
    } while (remainingPoints != 0);
  }
  pointsEnd = point;

  GameBoxPointReference *reference = pointReferencesBegin;
  GameBoxFace *face = facesBegin;
  SumoS32 facePointCount = 0;
  SumoS32 *cursor = faceIndices;
  SumoS32 *end = faceIndices + indexCount;
  while (cursor < end) {
    if (*cursor < 0) {
      face->pointCount = facePointCount;
      face->state = 1.0f;
      face->pointReferences = reference - facePointCount;
      face->preserveState = 1;
      UpdateFacePlane(*face);
      ++cursor;
      ++face;
      facePointCount = 0;
    } else {
      reference->index = *cursor;
      reference->point = pointsBegin + *cursor;
      ++facePointCount;
      ++reference;
      ++cursor;
    }
  }

  pointReferencesEnd = reference;
  facesEnd = face;
}

// FUNCTION: SUMO 0x00408d15
// FUNCTION: EDITOR 0x00408d37
void GameBox::ResetStorage() {
  memset(this, 0, sizeof(GameBox));
  unknownD4 = 0;
  unknownD8 = 0;
  unknownDC = 0;
}

// FUNCTION: SUMO 0x00408d35
// FUNCTION: EDITOR 0x00408d57
GameBox *CreateGameBox(Vector3 halfSize, Vector3 position, SumoS32 type,
                       SumoF32 defaultValue) {
  GameBox *box = g_gameBoxesEnd;
  box->ResetStorage();

  Vector3 points[8];
  SumoS32 index = 0;
  do {
    Vector3 point = halfSize;
    if ((index & 1) != 0) {
      point.x *= g_gameBoxYScale;
    }
    if ((index & 2) == 0) {
      point.y *= g_gameBoxYScale;
    }
    if ((index & 4) != 0) {
      point.z *= g_gameBoxYScale;
    }
    points[index] = point;
    ++index;
  } while (index < 8);

  box->InitializeGeometry(points, 8, g_boxFaceIndices, 30);
  box->InitializePhysics();
  box->position = position;
  box->type = type;
  box->defaultValue = defaultValue;
  ++g_gameBoxesEnd;
  return box;
}

// FUNCTION: SUMO 0x00408ddf
// FUNCTION: EDITOR 0x00408e01
void InitializeClipBoxes() {
  g_cutPlaneBox.ReserveGeometry(2048, 2048 * 4, 2048);
  g_clipScratchBox.ReserveGeometry(2048, 2048 * 4, 2048);
}
