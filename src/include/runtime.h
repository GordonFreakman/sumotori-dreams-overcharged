#ifndef SUMO_GAME_RUNTIME_H
#define SUMO_GAME_RUNTIME_H

#include "containers.h"
#include "types.h"

struct GameBoxPoint {
  Vector3 position;
  SumoU8 clipSide;
  SumoU8 flag0D;
  SumoS16 clipIndex;

  void SubtractOffset(Vector3 &offset);

  void SubtractOffset(const Vector3 &offset) {
    SubtractOffset(const_cast<Vector3 &>(offset));
  }
};

void *PlayGameSound(SumoS32 soundIndex, SumoF32 frequencyScale,
                    SumoF32 volumeScale, SumoS32 channel, Vector3 origin);
void *GameAudioUpdateOrigin(Vector3 origin, Vector3 angle);

struct GameBoxPointReference;
struct GameBox;
struct GameCollisionFeatureLink;
struct GameBoxContactLink;

struct GameBoxFace {
  Vector3 normal;
  SumoF32 planeDistance;
  GameBoxPointReference *pointReferences;
  SumoF32 state;
  SumoS32 preserveState;
  SumoS32 pointCount;
  SumoU8 visible20;
  SumoU8 unknown21[3];
};

struct GameBoxPointReference {
  GameBoxPoint *point;
  SumoS32 index;
};

struct GameBoxEdge {
  SumoS32 firstIndex;
  SumoS32 secondIndex;
  GameBoxFace *firstFace;
  GameBoxFace *secondFace;
};

struct MassAccumulator {
  SumoF32 volume;
  Vector3 weightedCenter;

  MassAccumulator();
  void AddTriangle(Vector3 &first, Vector3 &second, Vector3 &third,
                   SumoF32 faceState);
};

struct GameCollisionCandidate {
  SumoF32 distance;
  Vector3 point;
};

struct GameCollisionCandidateHeap {
  GameCollisionCandidate entries[512];
  SumoS32 count;

  void Push(SumoF32 distance, Vector3 point);
  Vector3 Pop();
};

struct GameBoxJoint {
  GameBox *boxes[2];
  Vector3 localAnchors[2];
  Vector3 firstPoseDirection;
  Vector3 secondAnchorDirection;
  Vector3 secondPoseDirection;
  Vector3 secondAxis;
  SumoF32 state;
  SumoF32 minimumAngle;
  SumoF32 maximumAngle;
  SumoF32 unknown5C;
  SumoU8 mode60;
  Vector3 unknown64;
  Matrix3 inverseResponse;
  Vector3 initialImpulse;
  Vector3 unknownC4;
  Vector3 firstLimitAxis;
  Vector3 secondLimitAxis;
  SumoF32 firstLimitImpulse;
  SumoF32 secondLimitImpulse;
  SumoU32 limitFlags;
};

struct GameMan;

struct GameBox {
  GameBoxPoint *pointsBegin;
  GameBoxPoint *pointsEnd;
  GameBoxPointReference *pointReferencesBegin;
  GameBoxPointReference *pointReferencesEnd;
  GameBoxFace *facesBegin;
  GameBoxFace *facesEnd;
  GameBoxEdge *edgesBegin;
  GameBoxEdge *edgesEnd;
  Vector3 accumulatedForce;
  SumoF32 boundingRadius;
  SumoS32 type;
  SumoF32 defaultValue;
  SumoF32 volume;
  Vector3 accumulatedOffset;
  Vector3 faceNormalSum;
  SumoF32 breakability;
  bool inactive;
  bool sleeping;
  SumoS32 sleepCounter;
  Matrix3 orientation;
  Vector3 position;
  Vector3 angularVelocity;
  Vector3 linearVelocity;
  SumoF32 damping;
  SumoF32 mass;
  SumoF32 inverseMass;
  SumoF32 inertia;
  SumoF32 inverseInertia;
  SumoS32 unknownBC;
  SumoS32 unknownC0;
  SumoF32 unknownC4;
  SumoF32 unknownC8;
  SumoF32 activityValue;
  bool immovable;
  bool limb;
  SumoS32 unknownD4;
  SumoS32 unknownD8;
  SumoS32 unknownDC;
  SumoS32 modeE0;
  GameCollisionFeatureLink *collisionFeatures;
  GameBoxContactLink *contactLinks;
  bool replayPresent;
  Vector3 replayPosition;
  GameMan *m_pOwner;
  SumoS32 fractureSound;
  void FinishContacts(SumoS32 preserveState);
  void RecalculateMass();
  void ClearForces();
  void UpdateFacePlane(GameBoxFace &face);
  bool ContainsPoint(Vector3 &point);
  void ReserveGeometry(SumoS32 pointCapacity, SumoS32 referenceCapacity,
                       SumoS32 faceCapacity);
  void InitializeGeometry(Vector3 *points, SumoS32 pointCount,
                          SumoS32 *faceIndices, SumoS32 indexCount);
  void ResetStorage();
  void DestroyGeometry();
  void BuildEdges();
  void ScaleMassProperties(SumoF32 scale);
  void FinalizeMassProperties();
  void InitializePhysics();
  void MakeImmovable();
  void ApplyAngularImpulse(Vector3 &contactOffset, Vector3 &impulse);
  Vector3 VelocityAtPoint(Vector3 &point);
  Vector3 CalculateImpulseResponse(Vector3 &impulsePoint, Vector3 &impulse,
                                   Vector3 &samplePoint);
  Matrix3 CalculateImpulseResponseMatrix(Vector3 &impulsePoint,
                                         Vector3 &samplePoint);
  void ApplyImpulseAtPoint(Vector3 &point, Vector3 &impulse);
  void ApplyWaterInteraction();
  void IntegratePhysics();
  void Render();
  void ClipGeometry(GameBox &other, Vector3 &normal, SumoF32 distance);
  void CutPlane(Vector3 &plane, SumoF32 distance);
};

struct GameBoxContactLink {
  GameBoxContactLink *next;
  GameBoxJoint *owner;
  GameBox *other;
};

struct GameCollisionFeatureLink {
  GameBox *other;
  SumoS32 featureCount;
  Vector3 features[16];
  GameCollisionFeatureLink *next;
};

struct GameCollisionPointRecord {
  Vector3 point;
  Vector3 normal;
  Vector3 accumulatedImpulse;
  GameBox *boxes[2];
  Matrix3 inverseResponse;
  SumoS32 iterationCount;
  SumoU8 hasFeature;
  SumoU8 unknown55[3];
  void *groupFirst;
  void *groupLast;
};

struct GameCollisionCorrectionRecord {
  Vector3 point;
  Vector3 impulse;
  GameBox *boxes[2];
};

GameBox *CreateGameBox(Vector3 halfSize, Vector3 position, SumoS32 type,
                       SumoF32 defaultValue);
void LaunchGameBoxProjectile(Vector3 position, Vector3 target,
                             SumoF32 flightTime, SumoS32 type);
void InitializeClipBoxes();
void ResetGameBoxes();
void LimitDynamicBoxes();
void RenderGameBoxes(SumoS32);
void ApplyPairedAngularImpulse(GameBox **boxes, Vector3 &impulse);
void ApplyWaterInteractionToMovingBoxes();
SumoS32 UpdateHiddenGameScreen();
void UpdateGameMenuScreen(SumoU8 drawOverlay);
void StartGameRound();

struct GameRandomGenerator {
  SumoF32 values[98];
  SumoF32 carry;
  SumoF32 decrement;
  SumoF32 modulus;
  SumoS32 firstIndex;
  SumoS32 secondIndex;

  GameRandomGenerator();
  void Initialize(SumoS32 firstSeed, SumoS32 secondSeed);
  SumoF32 Next();
};

void InitializeRandomFromClock();
void ApplyGameManPoseConstraints();
void ResolveGameCollisions();
void ResolveGameCollisions();
void AdvanceGameSimulation();
void AlignGameBoxJointTransform(GameBoxJoint *joint, SumoS32 sourceIndex);

struct GameManJointPose {
  SumoU8 unknown000[0x18];
  Vector3 firstDirection;
  Vector3 secondDirection;
  SumoF32 maximumCorrection;
};

struct GameManPose {
  GameManJointPose joints[14];

  void InitializeJointTransforms(GameMan *p_man);
};
enum {
  Pelvis,
  Chest,
  Head,
  FootL,
  CalfL,
  ThighL,
  FootR,
  CalfR,
  ThighR,
  UpperArmR,
  ForearmR,
  HandR,
  UpperArmL,
  ForearmL,
  HandL,
};
struct GameMan {
  GameBox *bodyParts[15];
  GameBoxJoint *joints[14];
  SumoF32 firstLimbLength;
  SumoF32 secondLimbLength;
  Vector3 firstFootTarget;
  Vector3 secondFootTarget;
  SumoU8 unknown094[0x08];
  SumoS32 supportSide;
  SumoS32 postureTick;
  SumoS32 postureState;
  SumoF32 stepMagnitude;
  Vector3 locomotionOffset;
  SumoF32 bodyLean;
  Vector3 stepDirection;
  Vector3 centerOfMass;
  SumoF32 activityOffset;
  SumoF32 balancePitch;
  SumoF32 balancePitchVelocity;
  SumoF32 balancePitchIntegral;
  SumoF32 balanceRoll;
  SumoF32 balanceRollVelocity;
  SumoF32 stanceBlend;
  SumoF32 standingHeight;
  SumoU8 unknown0F4[0x0c];
  Vector3 locomotionForce;
  SumoF32 recoveryDrive;
  SumoF32 recoveryAngle;
  SumoF32 recoveryLateral;
  SumoS32 recoverySide;
  SumoF32 balanceStrength;
  SumoF32 balanceTurn;
  Vector3 motionVector;
  SumoS32 actionMode;
  SumoS32 actionTick;
  SumoS32 actionSide;
  SumoS32 actionCooldown;
  SumoS32 active;
  SumoS32 state144;
  SumoF32 activityBlend;
  GameManPose primaryPose;
  GameManPose secondaryPose;
  SumoS32 mode;
  SumoIntPtr state700;
  SumoF32 smoothedTurn;
  SumoU8 unknown708[0x08];
  SumoS32 eliminated;
  SumoS32 approachTicks;
  SumoS32 decisionTickA;
  SumoS32 decisionTickB;
  SumoS32 unknown720;
  SumoS32 alternateBehavior;
  SumoS32 randomHeading;
  SumoS32 randomActionDelay;
  bool dead;
  int fragmentCount;
  void Initialize(Vector3 &position, SumoF32 angle, SumoS32 type,
                  SumoIntPtr flags);
  void Render(void *poseState);
  void Update(SumoIntPtr state);
  SumoF32 CalculateKineticEnergy();
  Vector3 CalculateCenterOfMassPosition();
  Vector3 CalculateCenterOfMassVelocity();
  Vector3 CalculateAngularMomentum(Vector3 &referencePosition,
                                   Vector3 &referenceVelocity);
  GameMan *FindNearestOpponent(Vector3 &facingAxis, Vector3 &lateralAxis);
  SumoU32 ChooseAiInput(GameMan *opponent);
  void CalculateLimbFracture(GameBox *box);
};

void SetGameManAudioState(GameMan *man, SumoS32 channel);
SumoF32 CalculateLimbAngleCosine(SumoF32 firstLength, SumoF32 secondLength,
                                 SumoF32 targetLength);
void UpdateGameMen();

GameBox *AllocateBox();

extern const SumoF32 g_parserMinimumBreakability;
extern const SumoF32 g_inertiaRadiusScale;
extern const SumoF32 g_gameOne;
extern const SumoF32 g_gameBoxDefaultValue;
extern const SumoF32 g_gameBoxYScale;
extern volatile const SumoF32 g_immovableMass;
extern const SumoF32 g_cutPlaneFloor;
extern GameBox *g_currentBox;
extern GameBox g_cutPlaneBox;
extern GameBox g_clipScratchBox;
extern GameBox g_gameBoxes[4096];
extern GameBox *g_gameBoxesEnd;
extern GameBoxJoint g_gameContactObjects[0xf400];
extern GameBoxJoint *g_gameContactObjectsEnd;
extern GameBoxContactLink g_gameContactLinks[0x1800];
extern GameBoxContactLink *g_gameContactLinksEnd;
extern GameRandomGenerator g_gameRandom;
extern GameRandomGenerator g_simulationRandom;
extern GameMan g_gameMen[4];
extern SumoU8 g_gameMenEnd;
extern GameMan *g_nextGameMan;
extern SumoS32 g_gameIsRunning;
extern SumoU32 g_screenTintColor;
extern SumoS32 g_screenTintLevel;

void UpdateScreenTint(SumoS32 intensity);
void RefreshScreenTint();
Vector3 TransformWavyTextPoint(Vector3 &point);
void ResetGameContactLists();
void RefreshGameContactLists();
bool SumoShouldMoveCamera();
extern SumoU32 g_pendingManCount;
extern Vector3 g_pendingManPositions[9];
extern SumoF32 g_pendingManAngles[9];

#endif
