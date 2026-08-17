#include "decomp_keywords.h"
#include "runtime.h"
#include "replay.h"
#include "decomp.h"
#include "sumo_portable.h"
#include "types.h"
#include "containers.h"
#include "input.h"
#include "parser.h"
#include "big_integer.h"
#include "sumo_assert.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <new>
#include <stdlib.h>


SumoS32 g_sumoMode = 0;

SumoS32 CheckStoredGameSettings();
void SetGameCursorVisible(SumoU8 visible);
void StartGameLevelEditor(char *source);
void RestartGameMusic(SumoS32 playbackMode);
void ResetAndSetSceneTransform(Vector3 &position, SumoF32 angle);
typedef void(__cdecl *ResetSceneTransformLegacyCall)(Vector3 &, SumoF32,
                                                     SumoS32);
void InitializeWaterField();
static __forceinline void ResetAndSetSceneTransformLegacy(Vector3 &position,
                                                          SumoF32 angle) {
  ((ResetSceneTransformLegacyCall)ResetAndSetSceneTransform)(position, angle,
                                                             0);
}
Vector3 *ResetGameRoundState();
void ResetSceneTransform();
SumoS32 InitializeGameTextures();
SumoS32 InitializeGameVertexBuffers();
char *GetLevelScript(SumoS32 index);
void BuildDefaultGameArena(SumoS32 type);
extern SumoS32 g_gameMouseX;
extern SumoS32 g_gameAlternateCameraMode;
extern SumoF32 g_gameArenaExtent;
extern SumoS32 g_gameLevelEditorCloseRequested;
extern SumoS32 g_gamePrimaryInputPressed;
extern SumoS32 g_selectedLevelScript;
extern char *g_externalLevelScriptOverride;
extern SumoU32 g_gameTimeScaleNumerator;
extern SumoS32 g_gameEditorControlMode;
extern Vector3 g_gameCameraWorldPosition;
extern Matrix3 g_gameInverseViewMatrix;
extern const SumoF32 g_gameProjectionMinimum;
extern const SumoF32 g_gameCameraInputOffsetScale;
extern const SumoF32 g_gameCameraHeightScale;
extern const SumoF32 g_gameCameraInputDamping;
extern const SumoF32 g_gameNegativeHalf;
Vector3 GetGameMouseRayDirection();
char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color);

DECOMP_SIZE_ASSERT(GameBox, 0xfc);
DECOMP_SIZE_ASSERT(GameRandomGenerator, 0x19c);
DECOMP_SIZE_ASSERT(GameMan, 0x730);

// GLOBAL: SUMO 0x0042b28c
extern const SumoF32 g_parserMinimumBreakability = 10.0f;

// GLOBAL: SUMO 0x0042b2b0
extern const SumoF32 g_gameOne = 1.0f;

// GLOBAL: SUMO 0x0042c2d0
extern const SumoF32 g_gameBoxDefaultValue = 0.0625f;

// GLOBAL: SUMO 0x0042c724
extern const SumoF32 g_cutPlaneFloor = -1000.0f;

// GLOBAL: SUMO 0x0042c630
static const SumoF32 g_randomHalf = 0.5f;

SumoS32 InitializeGameRuntimeState();

// GLOBAL: SUMO 0x0042c9b8
extern const SumoF32 g_gameManEventVolume = 0.75f;

// GLOBAL: SUMO 0x0042c9bc
extern const SumoF32 g_gameAiPushDistanceThreshold = 7.5f;

// GLOBAL: SUMO 0x0042c9c0
extern const SumoF32 g_gameAiForwardDistanceSquaredLimit = 64.0f;

// GLOBAL: SUMO 0x0042c9c4
extern const SumoF32 g_gameAiVelocityProjectionScale = 50.0f;

// GLOBAL: SUMO 0x0042c9c8
extern const SumoF32 g_gameAiStateScale = 0.0015384615f;

// GLOBAL: SUMO 0x0042c9cc
extern const SumoF32 g_gameAiLateralRecoveryThreshold = -2.0f;

// GLOBAL: SUMO 0x0042c9d0
extern const SumoF32 g_gameAiMotionSquaredLimit = 16.0f;

// GLOBAL: SUMO 0x0042c9d4
extern const SumoF32 g_gameAiStabilitySquaredLimit = 0.040000001f;

// GLOBAL: SUMO 0x0042c9d8
extern const SumoF32 g_gameAiOpponentMotionSquaredLimit = 25.0f;

extern const SumoF32 g_gameProjectileDefaultValue;
extern const SumoF32 g_gameRampStep32;
extern const SumoF32 g_boxWaterDiagonalScale;
extern const SumoF32 g_gameTwo;

// GLOBAL: SUMO 0x0042c770
extern const SumoF32 g_waterMotionThreshold = 0.00001f;

// GLOBAL: SUMO 0x0042c788
extern const SumoF32 g_gameArenaHalfExtent = 31.0f;

// GLOBAL: SUMO 0x0042c960
extern const SumoF32 g_gameWallSegmentSpacing = 18.0f;

extern const SumoF32 g_gameFloorHalfExtent;

// GLOBAL: SUMO 0x0042c9dc
extern const SumoF32 g_gameRimTiltAngle = -0.78539819f;

// GLOBAL: SUMO 0x0042c9e0
extern const SumoF32 g_gameRimAngleStep = 0.2026834f;

// GLOBAL: SUMO 0x0042c9e4
extern const SumoF32 g_gameWallCenterSegment = 2.5f;

// GLOBAL: SUMO 0x0042c9e8
extern const SumoF32 g_gameWallQuarterTurn = 1.5707964f;

// GLOBAL: SUMO 0x0042c9ec
extern const SumoF32 g_gameArenaLowerPointScale = 1.1548387f;

extern const SumoF32 g_gameArenaVerticalHalfSize;

// GLOBAL: SUMO 0x00453cd0
SumoF32 g_gameSimulationStep = 1.0f;

// GLOBAL: SUMO 0x005ae420
SumoF32 g_gameInverseSimulationStep;

// GLOBAL: SUMO 0x0046734c
GameBox *g_currentBox = 0;

// GLOBAL: SUMO 0x00530a00
extern GameBox g_cutPlaneBox;

// GLOBAL: SUMO 0x00530b00
extern GameBox g_clipScratchBox;

// GLOBAL: SUMO 0x00746430
extern GameBox g_gameBoxes[4096];

// GLOBAL: SUMO 0x004536e4
GameBox *g_gameBoxesLimit = g_gameBoxes + 4000;

// GLOBAL: SUMO 0x00560c08
extern GameBox *g_gameBoxesEnd;

// GLOBAL: SUMO 0x00521600
extern GameBoxJoint g_gameContactObjects[0xf400];

// GLOBAL: SUMO 0x00560c04
extern GameBoxJoint *g_gameContactObjectsEnd;

// GLOBAL: SUMO 0x00560c10
extern GameBoxContactLink g_gameContactLinks[0x1800];

// GLOBAL: SUMO 0x00560c0c
extern GameBoxContactLink *g_gameContactLinksEnd;

// GLOBAL: SUMO 0x00765c38
extern GameRandomGenerator g_gameRandom;

// GLOBAL: SUMO 0x00c06188
GameRandomGenerator g_simulationRandom;

// GLOBAL: SUMO 0x00c06360
extern GameMan g_gameMen[4];

// GLOBAL: SUMO 0x00c08020
extern SumoU8 g_gameMenEnd;

// GLOBAL: SUMO 0x00453858
GameMan *g_nextGameMan = g_gameMen;

// GLOBAL: SUMO 0x00d0f1f8
SumoS32 g_gameIsRunning = 0;

// GLOBAL: SUMO 0x00ac5ef4
SumoU32 g_screenTintColor;

// GLOBAL: SUMO 0x00c06178
SumoS32 g_screenTintLevel;

// GLOBAL: SUMO 0x004e73b0
SumoU32 g_pendingManCount = 0;

// GLOBAL: SUMO 0x00c06340
SumoS32 g_levelLoadState[8];

// GLOBAL: SUMO 0x00467350
Vector3 g_pendingManPositions[9];

// GLOBAL: SUMO 0x004e73b4
SumoF32 g_pendingManAngles[9];

// GLOBAL: SUMO 0x00c09ce4
SumoS32 g_gameManUpdateCounter;

// GLOBAL: SUMO 0x00c09ce0
SumoF32 g_unk0x00c09ce0;

// GLOBAL: SUMO 0x00c06184
SumoS32 g_gameRuntimeMode;

// GLOBAL: SUMO 0x004535f8
SumoS32 g_gamePlayerCount = 3;

// GLOBAL: SUMO 0x00453600
char g_gameMenuWarningText[] =
    "WARNING: The characters in the game were performed by\n"
    "trained professionals!!! Do not try this at home!!!\n \n"
    "Rules: When you hit the ground, you lose\n"
    "winner is the one, who stays on feet for the longest\n \n"
    "Original game created by Peter Soltesz.\n"
    "Please purchase the original version of the game if you haven't already.\n \n"
    "Original decompile & portable version created by siohaza\n"
    "https://github.com/siohaza/sumotori-dreams-re\n"
    "Sumotori Dreams: Overcharged by Gordon Freakman\n \n"
    "Features:\n - Directional audio\n - Increased engine limits\n - More textures to work with\n - Extra gamemodes \n \n"
    
    "OpenGL shadow map impelmentation taken from \nJoey de Vries' LearnOpenGL article.\n";

// GLOBAL: SUMO 0x004ea480
SumoS32 g_gameHumanPlayerCount;

// GLOBAL: SUMO 0x00c06180
SumoS32 g_gameResetScores;

// GLOBAL: SUMO 0x00c06328
SumoS32 g_gameScores[2];

// GLOBAL: SUMO 0x00c0633c
SumoS32 g_gameRoundPlayerCount;

// GLOBAL: SUMO 0x0045385c
SumoF32 g_gameDecorationHeight = 27.0f;

// GLOBAL: SUMO 0x004ea47c
SumoS32 __declspec(align(16)) g_gameMenuPage;

// GLOBAL: SUMO 0x004ea478
SumoS32 g_gameMenuTransitionTicks;

// GLOBAL: SUMO 0x004ea484
SumoS32 g_gameMenuAlternateLayout;

// GLOBAL: SUMO 0x00453860
SumoU8 g_gameUsesScriptedArena = 1;

// GLOBAL: SUMO 0x004ea488
SumoU8 g_gameLevelEditorActive;

// GLOBAL: SUMO 0x004ea474
SumoS32 g_gameProjectileCooldown;

// GLOBAL: SUMO 0x00765c34
SumoS32 g_gameSkipPhysicsStep;

// GLOBAL: SUMO 0x004536e8
SumoU8 g_gameCollisionPassActive = 1;

// GLOBAL: SUMO 0x00746428
SumoU8 g_gameBoxesInitialized;

// GLOBAL: SUMO 0x005115ec
SumoS32 g_gameSimulationTick;

// GLOBAL: SUMO 0x00562410
extern SumoS32 g_gameMenuSelection;

static __forceinline void AddGameMenuConstraint(
    GameBox *first, GameBox *second, const Vector3 &firstAnchor,
    const Vector3 &secondAnchor, const Vector3 &firstDirection,
    const Vector3 &secondAnchorDirection, const Vector3 &secondDirection,
    const Vector3 &secondAxis, const Vector3 *firstDirectionOverride,
    SumoF32 minimumAngle) {
  g_gameContactObjectsEnd->boxes[0] = first;
  g_gameContactObjectsEnd->localAnchors[0] = firstAnchor;
  g_gameContactObjectsEnd->firstPoseDirection =firstDirection;
  if (firstDirectionOverride != 0) {
    g_gameContactObjectsEnd->firstPoseDirection = *firstDirectionOverride;
  }
  g_gameContactObjectsEnd->secondPoseDirection =
      secondDirection;
  g_gameContactObjectsEnd->boxes[1] = g_gameBoxesEnd - 1;
  g_gameContactObjectsEnd->localAnchors[1] = secondAnchor;
  g_gameContactObjectsEnd->secondAnchorDirection =
      secondAnchorDirection;
  g_gameContactObjectsEnd->secondAxis = secondAxis;
  g_gameContactObjectsEnd->minimumAngle = minimumAngle;
  g_gameContactObjectsEnd->maximumAngle = 1.21f;
  g_gameContactObjectsEnd->state = 0.0f;
  g_gameContactObjectsEnd ++;
}

static __forceinline Vector3 MakeGameRuntimeVector3(SumoF32 x, SumoF32 y,
                                                    SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

// FUNCTION: SUMO 0x0040776d
SumoS32 InvokeGameRuntimeState() { return InitializeGameRuntimeState(); }

static const char *volatile g_hiddenScreenStringAnchors[] = {
    "Hidden Part",
    "Controls:\nHome/PageUp = Move Camera\nMouse Click = Punish!!!\nEsc      = "
    "leave"};

static __forceinline void LaunchGameMenuProjectile(Vector3 &direction,
                                                   SumoF32 distance) {
  Vector3 target = g_gameCameraWorldPosition - direction.Scale(distance);
  direction.z = 0.0f;
  direction.x = -120.0f;
  direction.y = 10.0f;
  LaunchGameBoxProjectile(direction, target, 30.0f, 2);
}

// FUNCTION: SUMO 0x0040793d
void UpdateGameMenuScreen(SumoU8 drawOverlay) {
  if (g_gameBoxesEnd > g_gameBoxes + 400) {
    InitializeGameRuntimeState();
  }

  if (g_gameMenuSelection != 0) {
    g_gameMenuTransitionTicks -= 2;
    if (g_gameMenuTransitionTicks <= 0) {
      switch (g_gameMenuPage) {
      case 3:
          g_gameMenuPage = 0;
        InitializeGameRuntimeState();
          break;
      case 1:
        g_externalLevelScriptOverride = 0;
        g_gameMenuPage = 0;
        g_selectedLevelScript =
            g_gameMenuSelection % 16 + 4 * (g_gameMenuSelection / 16) - 1;
        InitializeGameRuntimeState();
        break;
      case 2:
        g_gameMenuPage = 0;
        switch (g_gameMenuSelection)
        {
        case 17:
          g_gameHumanPlayerCount = 0;
          g_gamePlayerCount = 1;
          StartGameRound();
          break;
        case 18:
          g_gameHumanPlayerCount = 1;
          g_gamePlayerCount = 1;
          StartGameRound();
          break;
        default:
          g_sumoMode = g_gameMenuSelection % 16 + 4 * (g_gameMenuSelection / 16) - 1;
          InitializeGameRuntimeState();
          break;
        }
        break;

      case 0:
        switch (g_gameMenuSelection) {
        case 1:
          g_gameHumanPlayerCount = 2;
          g_gamePlayerCount = 2;
          StartGameRound();
          break;
        case 2:
          g_gameHumanPlayerCount = 2;
          g_gamePlayerCount = 3;
          StartGameRound();
          break;
        case 3:
          g_gameHumanPlayerCount = 2;
          g_gamePlayerCount = 4;
          StartGameRound();
          break;
        case 4:
          g_gameHumanPlayerCount = 0;
          g_gamePlayerCount = 4;
          StartGameRound();
          break;
        case 6:
          g_gameHumanPlayerCount = 0;
          g_gamePlayerCount = 1;
          StartGameRound();
          break;
        case 17:
          g_gamePlayerCount = 2;
          g_gameHumanPlayerCount = 1;
          StartGameRound();
          break;
        case 18:
          g_gamePlayerCount = 3;
          g_gameHumanPlayerCount = 1;
          StartGameRound();
          break;
        case 19:
          g_gamePlayerCount = 4;
          g_gameHumanPlayerCount = 1;
          StartGameRound();
          break;
        case 20:
          g_gameHumanPlayerCount = 0;
          g_gamePlayerCount = 2;
          StartGameRound();
          break;
        case 33:
          g_gameMenuPage = 1;
          InitializeGameRuntimeState();
          break;
        case 34:
          g_gameMenuAlternateLayout ^= 1;
          InitializeGameRuntimeState();
          break;
        case 37: g_gameLevelEditorCloseRequested = 1; break;
        case 35:
          g_gameMenuPage = 2;
            InitializeGameRuntimeState();
            break;
        case 36:
          g_gameMenuPage = 3;
          InitializeGameRuntimeState();
          break;
        }
        break;
      }
    }

    SumoS32 tintComponent =
        (SumoS32)sqrt((SumoF64)(g_gameMenuTransitionTicks << 8));
    g_screenTintColor = (SumoU32)tintComponent * 0x10101u;
  } else {
    g_gameMenuTransitionTicks = 255;
  }

  --g_gameProjectileCooldown;
  if (g_gameMouseX != -1) {
    if (g_gameProjectileCooldown <= 0) {
      g_gameProjectileCooldown = 60;
      Vector3 direction = GetGameMouseRayDirection();
      SumoF32 distance = (g_gameCameraWorldPosition.x + 84.0f) / direction.x;
      LaunchGameMenuProjectile(direction, distance);
    }
    g_gameMouseX = -1;
  }

  if (g_gamePrimaryInputPressed) {
      if (g_gameMenuPage == 0)
    g_gameLevelEditorCloseRequested = 1;
     else
     {
        g_gameMenuPage = 0;
        InitializeGameRuntimeState();
     }
     g_gamePrimaryInputPressed = 0;
  }

  if (drawOverlay) {
    if (g_gameMenuPage == 3) {
      DrawGameText(-0.85000002f, g_inertiaRadiusScale, g_gameMenuWarningText,
                   0xc0ffffff);
      g_screenTintColor =
          (0x007f007f & ((SumoS32)g_screenTintColor / 2)) +
          ((3 * ((SumoS32)g_screenTintColor & 0xff00) / 4) & 0xff00);
    }
    DrawGameText(-0.4f, 0.56f, "Sumotori Dreams: Overcharged v0.05", 0xc08080ff);
    DrawGameText(0.27000001f, -0.5, "\"Tested on party animals\"",
                 0xc0ffffff);
    DrawGameText(-0.85000002f, -0.5,
                 "www.gravitysensation.com/sumotori/", 0xc0ffffff);
  }
}

// FUNCTION: SUMO 0x00407db6
void UpdateScreenTint(SumoS32 intensity) {
  if (intensity > 255) {
    intensity = 255;
  }
  if (g_gameIsRunning) {
    intensity = 255;
  }

  SumoS32 greenBlue = (intensity * intensity) >> 8;
  g_screenTintColor = (intensity << 16) + greenBlue * 257;
}

// FUNCTION: SUMO 0x00407dea
void RefreshScreenTint() { UpdateScreenTint(g_screenTintLevel * 8); }

// FUNCTION: SUMO 0x00409657
void GameBox::CutPlane(Vector3 &plane, SumoF32 distance) {
  Vector3 initialNormal;
  initialNormal.x = 0.0f;
  initialNormal.y = 0.0f;
  initialNormal.z = 1.0f;
  Vector3 normal = initialNormal;

  g_cutPlaneBox.ClipGeometry(*this, normal, g_cutPlaneFloor);
  ClipGeometry(g_cutPlaneBox, plane, distance);
}

void UpdateWaterField();

// FUNCTION: SUMO 0x0040b5d5
void AdvanceGameSimulation() {
  LimitDynamicBoxes();
  RefreshScreenTint();
  if (g_gameMode < 2) {
    if (!g_gameSkipPhysicsStep) {
      g_gameCollisionPassActive = 1;
      g_gameInverseSimulationStep = 1.0f / g_gameSimulationStep;
      ResolveGameCollisions();
      GameBox *box = g_gameBoxes;
      while (box < g_gameBoxesEnd) {
        box->IntegratePhysics();
        ++box;
      }
      UpdateGameMen();
    }
    g_gameSkipPhysicsStep = 0;
    g_gameBoxesInitialized = 1;
  }
  if (g_sumoMode == 1 || g_gameMode >= 2) {
    ApplyWaterInteractionToMovingBoxes();
  }
  UpdateGameReplay();
  UpdateWaterField();
  ++g_gameSimulationTick;
}

// FUNCTION: SUMO 0x0040b663
void GameRandomGenerator::Initialize(SumoS32 firstSeed, SumoS32 secondSeed) {
  if (firstSeed < 0 || firstSeed > 31328 || secondSeed < 0 ||
      secondSeed > 30081) {
    firstSeed = 1231;
    secondSeed = 7354;
  }

  SumoS32 i = (firstSeed / 177) % 177 + 2;
  SumoS32 j = firstSeed % 177 + 2;
  SumoS32 k = (secondSeed / 169) % 178 + 1;
  SumoS32 l = secondSeed % 169;

  SumoS32 index = 1;
  do {
    SumoF32 value = 0.0f;
    SumoF32 bitValue = g_randomHalf;
    SumoS32 remainingBits = 24;
    do {
      SumoS32 next = ((i * j) % 179) * k % 179;
      i = j;
      j = k;
      k = next;
      l = (53 * l + 1) % 169;
      if ((l * k) % 64 >= 32) {
        value += bitValue;
      }
      bitValue *= g_randomHalf;
      --remainingBits;
    } while (remainingBits != 0);

    values[index] = value;
    ++index;
  } while (index <= 97);

  carry = 0.021602869f;
  decrement = 0.45623308f;
  modulus = 0.99999982f;
  firstIndex = 97;
  secondIndex = 33;
}

// FUNCTION: SUMO 0x0040b807
GameRandomGenerator::GameRandomGenerator() { Initialize(0x4641, 0x535a); }

// FUNCTION: SUMO 0x0040e166
void InitializeRandomFromClock() {
  SumoS32 milliseconds = timeGetTime();
  g_simulationRandom.Initialize(milliseconds & 0x3fff,
                                ((milliseconds >> 8) + 1000) & 0x3fff);
}

// FUNCTION: SUMO 0x0040e18d
SumoS32 StartGameRuntime() {
  InitializeRandomFromClock();
  ResetSceneTransform();
  InitializeGameTextures();
  InitializeGameVertexBuffers();
  InitializeClipBoxes();
  ResetGameRoundState();
  RestartGameMusic(3);
  return InitializeGameRuntimeState();
}

static __forceinline Vector3 MakeGameManVector3(SumoF32 x, SumoF32 y,
                                                SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

// FUNCTION: SUMO 0x0040fd20
void ApplyGameManPoseConstraints() {
  GameMan *man = g_gameMen;
  while (man < g_nextGameMan) {
    man->Render(&man->primaryPose);
    ++man;
  }
}

// FUNCTION: SUMO 0x0040fef1
void SetGameManAudioState(GameMan *man, SumoS32 channel) {
  man->state144 &= 0;
  man->active = 8;
  PlayGameSound(5, 1.0f, g_gameManEventVolume, channel ^ 3, man->centerOfMass);
}

// FUNCTION: SUMO 0x00410863
GameMan *CreateGameMen() {
  SumoS32 playerCount = g_gamePlayerCount;
  SumoS32 humanCount = g_gameHumanPlayerCount;
  if (g_gameResetScores) {
    g_gameScores[0] = 0;
    g_gameScores[1] = 0;
    g_gameResetScores = false;
  }

  g_levelLoadState[0] = -1;
  g_levelLoadState[1] = -1;
  g_levelLoadState[2] = -1;
  g_levelLoadState[3] = -1;
  g_gameRoundPlayerCount = playerCount;
  ReplayWriteBoundary();
  g_screenTintLevel = 0;

  GameMan *next = g_gameMen;
  for (SumoS32 index = 0; index < playerCount; ++index) {
    Vector3 position = MakeGameManVector3(0.0f, 5.0f, -15.0f);
    SumoS32 playerTypes[4] = {2, 3, 1, 9};
    SumoF32 angle = (SumoF32)index / (SumoF32)playerCount * 6.2831855f;
    Vector3 rotation = MakeGameManVector3(0.0f, angle, 0.0f);
    position.Rotate(rotation);

    SumoS32 opponentIndex;
    if (index < humanCount) {
      opponentIndex = index + humanCount;
      if (opponentIndex >= playerCount)
        opponentIndex = playerCount - 1;
    } else {
      opponentIndex = 0;
    }
    if (playerCount == 4) {
      opponentIndex = (index - 2) & 3;
      if (humanCount == 1 && index > 0)
        opponentIndex = 0;
    }

    bool skip = false;
    if (g_selectedLevelScript != 0) {
      SumoS32 pendingCount = (SumoS32)g_pendingManCount;
      if (index >= pendingCount) {
        skip = true;
      } else {
        position = g_pendingManPositions[index];
        angle = -g_pendingManAngles[index];
      }
      opponentIndex %= pendingCount;
      if (opponentIndex == index)
        opponentIndex = (opponentIndex + 1) % pendingCount;
      opponentIndex %= playerCount;
    }

    if (!skip) {
      next->Initialize(position, -angle, playerTypes[index],
                       (SumoIntPtr)(g_gameMen + opponentIndex));
      next->active = 4;
      if (g_levelLoadState[4] != 0)
        next->active = 0;
      if (index < humanCount)
        next->mode = index;
      else
        next->mode = 2;
      ++next;
    }
  }

  g_nextGameMan = next;
  g_gameTimeScaleNumerator = 120;
  return next;
}

// FUNCTION: SUMO 0x00410a5c
void StartGameRound() {
  SetGameCursorVisible(0);
  g_gameEditorControlMode = 4;
  if (g_sumoMode == 2)
    RestartGameMusic(10);
     else
  RestartGameMusic(6);

  Vector3 position;
  Vector3 initialPosition = {40.0f, 35.0f, -100.0f};
  position = initialPosition;
  ResetAndSetSceneTransformLegacy(position, 0.0f);
  ResetGameRoundState();
  g_gameRandom.Initialize(0x59a, 0x191f);

  g_levelLoadState[4] = 0;
  if (g_gamePlayerCount == 1 && g_gameHumanPlayerCount == 0) {
    g_levelLoadState[4] = 11;
    SetGameCursorVisible(1);
  }

  if (g_selectedLevelScript != 0) {
    StartGameLevelEditor(GetLevelScript(g_selectedLevelScript));
    if (g_gamePlayerCount == 1 && g_gameHumanPlayerCount == 0) {
      g_levelLoadState[4] = 11;
    }
  } else {
    g_gameUsesScriptedArena = 0;
    BuildDefaultGameArena(0);
  }
  if (g_sumoMode == 1)
    InitializeWaterField();

    if (g_gamePlayerCount == 1 && g_gameHumanPlayerCount == 1)
    g_levelLoadState[4] = 2;

  CreateGameMen();
  RefreshGameContactLists();
}

// FUNCTION: SUMO 0x00414eb9
void UpdateGameMen() {
  GameMan *man = g_gameMen;
  while (man < g_nextGameMan) {
    man->Update(man->state700);
    ++man;
    ++g_gameManUpdateCounter;
    if (g_gameManUpdateCounter == 0x708 && !CheckStoredGameSettings()) {
      g_gameRuntimeMode = 2;
    }
  }
}

GameMan g_gameMen[4];
SumoU8 g_gameMenEnd;

// GLOBAL: SUMO 0x00c06030
// GLOBAL: EDITOR 0x00c06850
ReplayStream g_replayPlaybackStream;

// GLOBAL: SUMO 0x00c0604c
// GLOBAL: EDITOR 0x00c0686c
ReplayStream g_replayStream;

char g_gameLevelEditBuffer[0x80000];

// GLOBAL: SUMO 0x0042b308
// GLOBAL: EDITOR 0x0042b308
extern const SumoF32 g_gameManPoseImpulseGain = 0.7f;

extern const char g_gameScreenshotReadMode[];

// GLOBAL: SUMO 0x0042bd68
// GLOBAL: EDITOR 0x0042bd68
extern const char g_builtinLevelScript1[] =
    "mainbox()={addbox(vec(60,5,60),vec(0,-5,0),3,1);};chair0(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);"
    "\taddbox(vec(1,3,3),pos+vec(3,9,0),1,0); breakability(80);\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);\taddbo"
    "x(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};chair2(pos)={\taddbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability("
    "80);\taddbox(vec(1,3,3),pos+vec(-3,9,0),1,0); breakability(80);\taddbox(vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);\t"
    "addbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};table(pos)={\tbr=100;\taddbox(vec(10,1,10),pos+vec(0,9,0),0,0);"
    " breakability(br);\taddbox(vec(1,4,1),pos+vec(9,4,-9 ),0,1); breakability(br);\taddbox(vec(1,4,1),pos+vec(9,4,9  ),0,1); b"
    "reakability(br);\taddbox(vec(1,4,1),pos+vec(-9,4,-9),0,1); breakability(br);\taddbox(vec(1,4,1),pos+vec(-9,4,9 ),0,1); bre"
    "akability(br);};walls()={\tbr=150;\taddbox(vec(55,8,1),vec(0,8,-56),2,1);breakability(br);\taddbox(vec(55,8,1),vec(0,8,56),"
    "2,1);breakability(br);\taddbox(vec(1,8,55),vec(-56,8,0),2,1);breakability(br);\taddbox(vec(1,8,55),vec(56,8,0),2,1);breaka"
    "bility(br);};walls();table(vec(0,0,0));chair2(vec(-15,0,0));chair0(vec(15,0,0));mainbox();man(vec(0,0,-25),vec(0,0,1),2)"
    ";man(vec(0,0,25),vec(0,0,-1),3);man(vec(25,0,0),vec(-1,0,0),0);man(vec(-25,0,0),vec(1,0,0),1);";

// GLOBAL: SUMO 0x0042b8d0
// GLOBAL: EDITOR 0x0042b8d0
extern const char g_builtinLevelScript2[] =
    "mainbox()={\taddbox(vec(3,10.5,3),vec(0,0.5,0),5,1); \taddbox(vec(30,2,3),vec(0,12.98,0),5,1); \taddbox(vec(3,2,30),vec(0,1"
    "3,0),5,1);}; mainbox();table(pos)={\tbr=100;\taddbox(vec(10,1,10),pos+vec(0,9,0),0,0); breakability(br);\taddbox(vec(1,4,1)"
    ",pos+vec(9,4,-9 ),0,1); breakability(br);\taddbox(vec(1,4,1),pos+vec(9,4,9  ),0,1); breakability(br);\taddbox(vec(1,4,1),p"
    "os+vec(-9,4,-9),0,1); breakability(br);\taddbox(vec(1,4,1),pos+vec(-9,4,9 ),0,1); breakability(br);};chair0(pos)={\taddbox"
    "(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);\taddbox(vec(1,3,3),pos+vec(3,9,0),1,0); breakability(80);\taddbox(vec(1"
    ",2,3),pos+vec(3,2,0),1,1); breakability(80);\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};chair2(pos)={\tad"
    "dbox(vec(4,1,3),pos+vec(0,5,0),1,1); breakability(80);\taddbox(vec(1,3,3),pos+vec(-3,9,0),1,0); breakability(80);\taddbox("
    "vec(1,2,3),pos+vec(3,2,0),1,1); breakability(80);\taddbox(vec(1,2,3),pos+vec(-3,2,0),1,1); breakability(80);};table(vec(1"
    "4,-10,20));table(vec(-14,-10,-20));chair0(vec(15,-10,-15));chair2(vec(-15,-10,15));man(vec(0,20,-20),vec(0,0,1),4);man(v"
    "ec(0,20,20),vec(0,0,-1),5);man(vec(20,20,0),vec(-1,0,0),4);man(vec(-20,20,0),vec(1,0,0),5);";

// GLOBAL: SUMO 0x0042b6f8
// GLOBAL: EDITOR 0x0042b6f8
extern const char g_builtinLevelScript3[] =
    "addbox( vec(20,2,50),vec(0,-8,0), 0,1);addbox( vec(3,4,8),vec(-7,-6,0), 10,1);addbox( vec(3,4,8),vec(7,-6,0), 10,1);addb"
    "ox( vec(8,17,10),vec(0,0,0), 6,1);p=vec(0,1,0);repeat(33) {\tp=rot(p,vec(pi*2/33,0,0));\tcutplane( p, -6);};addbox( vec(6,"
    "1,30),vec(0,7,0), 0,0);addbox( vec(2,1,1),vec(3,10,0), 0,0);addbox( vec(2,1,1),vec(-3,10,0), 0,0);man(vec(0,8,-28),vec(0"
    ",0,1),2); man(vec(0,8,28),vec(0,0,-1),3); man(vec(0,8,-18),vec(0,0,1),0);man(vec(0,8,18),vec(0,0,-1),1); ";

// GLOBAL: SUMO 0x0042b560
// GLOBAL: EDITOR 0x0042b560
extern const char g_builtinLevelScript4[] =
    "addbox( vec(8,8,3), vec(0,-2,-33),10,1);addbox( vec(8,8,3), vec(0,-2,33),10,1);addbox( vec(6,1,35),vec(0,7,0), 0,1); bre"
    "akability(210);addbox( vec(3,2,8), vec(33,-8,-0),10,1);addbox( vec(3,2,8), vec(-33,-8,0),10,1);addbox( vec(35,1.5,6),vec"
    "(0,-4.5,0), 0,0); breakability(270);man(vec(0,8,-20),vec(0,0,1),0);man(vec(0,8,20),vec(0,0,-1),1); man(vec(0,8,-30),vec("
    "0,0,1),0);man(vec(0,8,30),vec(0,0,-1),1); ";

// GLOBAL: SUMO 0x0042b338
// GLOBAL: EDITOR 0x0042b338
extern const char g_builtinLevelScript5[] =
    "p=vec(-50,-8,0);br=100000;repeat(13){\taddbox(vec(3,1,30),p,0,1); breakability(250);\taddbox(vec(5,1,30),p+vec(2,-2,0),10,"
    "1);\tp=p+vec(6,4,0);}addbox(vec(15,1,30),p+vec(12,-2,0),10,1);p=p+vec(6,4,0);p=p+vec(6,-4,0);addbox(vec(15,1,30),p,0,1);a"
    "ddbox(vec(1,7,28),p+vec(15,8,0),1,1); breakability(200);addbox(vec(15,7,1),p+vec(0,8,29),1,1); breakability(200);addbox("
    "vec(15,7,1),p+vec(0,8,-29),1,1); breakability(200);man(vec(-11,8,-15)+p,vec(0,0,1),2);man(vec(-11,8,15)+p,vec(0,0,-1),3)"
    ";man(vec(6,8,-15)+p,vec(-1,0,0),0);man(vec(6,8,15)+p,vec(-1,0,0),1);";

// GLOBAL: SUMO 0x00453408
// GLOBAL: EDITOR 0x00453408
char *g_builtinLevelScripts[9] = {0,
                                  (char *)g_builtinLevelScript1,
                                  (char *)g_builtinLevelScript2,
                                  (char *)g_builtinLevelScript3,
                                  (char *)g_builtinLevelScript4,
                                  (char *)g_builtinLevelScript5,
                                  0,
                                  0,
                                  0};

// GLOBAL: SUMO 0x00457340
// GLOBAL: EDITOR 0x00457360
char g_externalLevelScript[0x10000];

// GLOBAL: SUMO 0x00467340
// GLOBAL: EDITOR 0x00467360
char *g_externalLevelScriptOverride;

// GLOBAL: SUMO 0x004ea470
// GLOBAL: EDITOR 0x004eac90
SumoS32 g_selectedLevelScript;

// FUNCTION: SUMO 0x00403fa8
// FUNCTION: EDITOR 0x00403fa8
char *GetLevelScript(SumoS32 index) {
  if (g_externalLevelScriptOverride != 0) {
    return g_externalLevelScriptOverride;
  }
  return g_builtinLevelScripts[index];
}

// FUNCTION: SUMO 0x00403fbd
// FUNCTION: EDITOR 0x00403fbd
void LoadLevelScriptFile(char *fileName) {
  FILE *stream = fopen(fileName, g_gameScreenshotReadMode);
  if (stream != 0) {
    SumoU32 size = fread(g_externalLevelScript, 1, 0xffff, stream);
    g_externalLevelScript[size] = 0;
    fclose(stream);
    g_selectedLevelScript = -1;
    g_externalLevelScriptOverride = g_externalLevelScript;
  }
}

extern Matrix3 g_gameInverseViewMatrix;
extern Vector3 g_gameCameraWorldPosition;
extern SumoS32 g_gameMode;
extern SumoS32 g_gameAlternateCameraMode;
extern SumoS32 g_levelLoadState[8];
extern SumoF32 g_gameCameraDistanceScale;
extern SumoF32 g_gameCameraMoveScale;
extern SumoF32 g_gameCameraTurnScale;
extern Vector3 g_gameCameraPosition;
extern Vector3 g_gameCameraAngles;
extern Vector3 g_gameCameraAcceleration;
extern Vector3 g_gameCameraVelocity;
extern Vector3 g_gameCameraAngularVelocity;
extern SumoF32 g_gameCameraInputB;
extern const SumoF32 g_gameManPoseImpulseGain;
extern const SumoF32 g_gameProjectileSpin;
extern const SumoF32 g_wavyTextCosineRate;
extern const SumoF32 g_wavyTextTimeScale;
extern const SumoF32 g_wavyTextPhaseScale;

static __forceinline void AddGameSceneVector(Vector3 &p_destination,
                                             const Vector3 &p_source) {
  p_destination.x += p_source.x;
  p_destination.y += p_source.y;
  p_destination.z += p_source.z;
}

// GLOBAL: SUMO 0x0042b278
// GLOBAL: EDITOR 0x0042b278
extern const SumoF32 g_freeCameraAngleRecordScale = 40.743664f;

// GLOBAL: SUMO 0x0042b27c
// GLOBAL: EDITOR 0x0042b27c
extern const SumoF32 g_freeCameraPositionRecordScale = 32.0f;

// GLOBAL: SUMO 0x0042b288
// GLOBAL: EDITOR 0x0042b288
extern const SumoF32 g_freeCameraAimScale = -0.1f;

// GLOBAL: SUMO 0x0042b2a4
// GLOBAL: EDITOR 0x0042b2a4
extern const SumoF32 g_gameCameraPitchResponse = -0.016f;

// GLOBAL: SUMO 0x0042b2a8
// GLOBAL: EDITOR 0x0042b2a8
extern const SumoF32 g_gameCameraAimDamping = 0.8f;

// GLOBAL: SUMO 0x0042b2ac
// GLOBAL: EDITOR 0x0042b2ac
extern const SumoF32 g_gameCameraYawResponse = 0.016f;

// GLOBAL: SUMO 0x0042b2b4
// GLOBAL: EDITOR 0x0042b2b4
extern const SumoF32 g_gameCameraVelocityDamping = 0.98f;

// GLOBAL: SUMO 0x0042b2b8
// GLOBAL: EDITOR 0x0042b2b8
extern const SumoF32 g_gameCameraInputOffsetScale = 0.6f;

// GLOBAL: SUMO 0x0042b2c0
// GLOBAL: EDITOR 0x0042b2c0
extern const SumoF64 g_gameCameraFastSpringDistanceSquared = 100.0;

// GLOBAL: SUMO 0x0042b2c8
// GLOBAL: EDITOR 0x0042b2c8
extern const SumoF32 g_gameCameraHeightOffset = 11.0f;

// GLOBAL: SUMO 0x0042b2cc
// GLOBAL: EDITOR 0x0042b2cc
extern const SumoF32 g_gameCameraHeightScale = 0.3f;

// GLOBAL: SUMO 0x0042b2d0
// GLOBAL: EDITOR 0x0042b2d0
extern const SumoF32 g_gameCameraHeightBaseline = 45.0f;

// GLOBAL: SUMO 0x0042b2d4
// GLOBAL: EDITOR 0x0042b2d4
extern const SumoF32 g_gameCameraFacingEpsilon = 0.0001f;

// GLOBAL: SUMO 0x0042b2d8
// GLOBAL: EDITOR 0x0042b2d8
extern const SumoF32 g_gameCameraMinimumDistanceScale = 4.0f;

// GLOBAL: SUMO 0x0042b2dc
// GLOBAL: EDITOR 0x0042b2dc
extern const SumoF32 g_gameCameraDistanceBias = 20.0f;

// GLOBAL: SUMO 0x0042b2e8
// GLOBAL: EDITOR 0x0042b2e8
extern const SumoF32 g_gameCameraGroupRadiusScale = 2.8f;

// GLOBAL: SUMO 0x0042b2f0
// GLOBAL: EDITOR 0x0042b2f0
extern const SumoF32 g_gameCameraMinimumDistance = 5.0f;

// GLOBAL: SUMO 0x0042b2f4
// GLOBAL: EDITOR 0x0042b2f4
extern const SumoF32 g_gameCameraInputDamping = 0.9f;

// GLOBAL: SUMO 0x0042b2f8
// GLOBAL: EDITOR 0x0042b2f8
extern const SumoF32 g_gameCameraZoomStep = 0.017f;

// GLOBAL: SUMO 0x0042b300
// GLOBAL: EDITOR 0x0042b300
extern const SumoF32 g_gameCameraNormalTurnStep = 0.008f;

// GLOBAL: SUMO 0x00454fec
// GLOBAL: EDITOR 0x0045500c
Vector3 g_scenePosition;

// GLOBAL: SUMO 0x00454ff8
// GLOBAL: EDITOR 0x00455018
Matrix3 g_sceneOrientation;

// GLOBAL: SUMO 0x00455034
// GLOBAL: EDITOR 0x00455054
SumoF32 g_sceneAngle;

// GLOBAL: SUMO 0x00455058
// GLOBAL: EDITOR 0x00455078
SumoF32 g_scenePhaseA;

// GLOBAL: SUMO 0x00455084
// GLOBAL: EDITOR 0x004550a4
SumoF32 g_scenePhaseB;

// GLOBAL: SUMO 0x004533b0
// GLOBAL: EDITOR 0x004533b0
SumoF32 g_freeCameraRotationDamping = 0.9950000048f;

// GLOBAL: SUMO 0x004533b4
// GLOBAL: EDITOR 0x004533b4
SumoF32 g_freeCameraRotationAcceleration = 0.0000199999995f;

// GLOBAL: SUMO 0x004533b8
// GLOBAL: EDITOR 0x004533b8
SumoF32 g_freeCameraTranslationDamping = 0.9950000048f;

// GLOBAL: SUMO 0x004533bc
// GLOBAL: EDITOR 0x004533bc
SumoF32 g_freeCameraTranslationAcceleration = 0.000140000004f;

// GLOBAL: SUMO 0x004533c0
// GLOBAL: EDITOR 0x004533c0
SumoS8 g_freeCameraScanCodes[20] = {0x48, 0x50, 0x4b, 0x4d, 0x47, 0x49, 0x1e,
                                    0x20, 0x11, 0x1f, 0x1c, 0x52, 0x21, 0x23,
                                    0x14, 0x22, 0x13, 0x15, 0x12, 0};

// GLOBAL: SUMO 0x004533d4
// GLOBAL: EDITOR 0x004533d4
SumoS32 g_freeCameraRecordTicks = -1;

// GLOBAL: SUMO 0x0045505c
// GLOBAL: EDITOR 0x0045507c
SumoF32 g_freeCameraYawVelocity;

// GLOBAL: SUMO 0x00455060
// GLOBAL: EDITOR 0x00455080
SumoF32 g_freeCameraRollVelocity;

// GLOBAL: SUMO 0x00455080
// GLOBAL: EDITOR 0x004550a0
SumoF32 g_freeCameraPitchVelocity;

// GLOBAL: SUMO 0x0045501c
// GLOBAL: EDITOR 0x0045503c
Vector3 g_freeCameraVelocity;

// GLOBAL: SUMO 0x00455088
// GLOBAL: EDITOR 0x004550a8
SumoS32 g_freeCameraFileInitialized;

// GLOBAL: SUMO 0x00c06020
// GLOBAL: EDITOR 0x00c06840
Vector3 g_freeCameraTarget;

// GLOBAL: SUMO 0x00455074
// GLOBAL: EDITOR 0x00455094
Vector3 g_gameCameraFocus;

// GLOBAL: SUMO 0x00455090
// GLOBAL: EDITOR 0x004550b0
SumoF32 g_gameCameraZoomVelocity;

// FUNCTION: SUMO 0x00402784
// FUNCTION: EDITOR 0x00402784
void ResetSceneTransform() {
  g_sceneAngle = 1.5707964f;
  g_sceneOrientation.m00 = 1.0f;
  g_scenePhaseB = 0.15707964f;
  g_scenePosition.x = -30.0f;
  g_sceneOrientation.m01 = 0.0f;
  g_scenePosition.y = 40.0f;
  g_sceneOrientation.m02 = 0.0f;
  g_sceneOrientation.m10 = 0.0f;
  g_sceneOrientation.m11 = 1.0f;
  g_sceneOrientation.m12 = 0.0f;
  g_sceneOrientation.m20 = 0.0f;
  g_sceneOrientation.m21 = 0.0f;
  g_sceneOrientation.m22 = 1.0f;
  g_scenePosition.z = 0.0f;
}

// FUNCTION: SUMO 0x004027fd
// FUNCTION: EDITOR 0x004027fd
void SetSceneTransform(Vector3 &position, SumoF32 angle) {
  g_scenePhaseA = 0.0f;
  g_scenePhaseB = 0.0f;
  g_scenePosition = position;
  g_sceneAngle = angle;
}

// FUNCTION: SUMO 0x00402827
// FUNCTION: EDITOR 0x00402827
void ResetAndSetSceneTransform(Vector3 &position, SumoF32 angle) {
  ResetSceneTransform();
  g_scenePosition = position;
  g_sceneAngle = angle;
}

static __forceinline Vector3 &ReuseVector3Storage(Vector3 &p_object,
                                                  Vector3 &p_value) {
  p_object.~Vector3();
  return p_value;
}

static __forceinline Vector3 &ReuseVector3Storage(Vector3 &p_object,
                                                  const Vector3 &p_value) {
  return ReuseVector3Storage(p_object, const_cast<Vector3 &>(p_value));
}

// FUNCTION: SUMO 0x00402846
// FUNCTION: EDITOR 0x00402846
void UpdateFreeGameCamera(SumoS32 p_tickCount) {
  SumoS32 zero = 0;
  if (g_freeCameraFileInitialized == zero) {
    FILE *stream = fopen(
        // STRING: SUMO 0x0042b290
        // STRING: EDITOR 0x0042b290
        "camera.dat", "w");
    fclose(stream);
    g_freeCameraFileInitialized = 1;
  }

  volatile SumoF32 ticks = (SumoF32)p_tickCount;
  struct CameraDamping {
    SumoF32 m_rotation;
    SumoF32 m_translation;
  } damping;
  damping.m_rotation = (SumoF32)exp(log(g_freeCameraRotationDamping) * ticks);
  damping.m_translation =
      (SumoF32)exp(log(g_freeCameraTranslationDamping) * ticks);
  SumoF32 rotationStep = ticks * g_freeCameraRotationAcceleration;
  SumoF32 translationStep = ticks * g_freeCameraTranslationAcceleration;

  SumoU8 pressed[32];
  for (SumoU32 index = 0; index < 19; ++index) {
    pressed[index] = g_gameKeyDown[g_freeCameraScanCodes[index]] != zero;
  }
  if (pressed[18] != zero)
    translationStep = translationStep * g_parserMinimumBreakability;

  if (pressed[0] != zero)
    g_freeCameraPitchVelocity += rotationStep;
  if (pressed[1] != zero)
    g_freeCameraPitchVelocity -= rotationStep;
  if (pressed[4] != zero)
    g_freeCameraRollVelocity -= rotationStep;
  if (pressed[5] != zero)
    g_freeCameraRollVelocity += rotationStep;
  if (pressed[3] != zero)
    g_freeCameraYawVelocity -= rotationStep;
  if (pressed[2] != zero)
    g_freeCameraYawVelocity += rotationStep;

  Vector3 relativeTarget = g_freeCameraTarget;
  new (&relativeTarget) Vector3(g_sceneOrientation.Transform(
      ReuseVector3Storage(relativeTarget, relativeTarget - g_scenePosition)));
  g_freeCameraRollVelocity *= damping.m_rotation;
  g_freeCameraPitchVelocity =
      ((relativeTarget.y / relativeTarget.z * g_freeCameraAimScale -
        g_freeCameraPitchVelocity) *
           g_inertiaRadiusScale +
       g_freeCameraPitchVelocity) *
      damping.m_rotation;
  g_freeCameraYawVelocity =
      ((relativeTarget.x / relativeTarget.z * g_freeCameraAimScale -
        g_freeCameraYawVelocity) *
           g_inertiaRadiusScale +
       g_freeCameraYawVelocity) *
      damping.m_rotation;

  g_scenePhaseA -= ticks * g_freeCameraRollVelocity;
  g_scenePhaseB += ticks * g_freeCameraPitchVelocity;
  g_sceneAngle -= ticks * g_freeCameraYawVelocity;
  g_sceneOrientation.SetIdentity();
  g_sceneOrientation.RotateRows02(g_sceneAngle);
  g_sceneOrientation.RotateRows12(g_scenePhaseB);
  g_sceneOrientation.RotateRows01(g_scenePhaseA);

  if (pressed[6] != zero) {
    g_freeCameraVelocity.x -= g_sceneOrientation.m00 * translationStep;
    g_freeCameraVelocity.y -= g_sceneOrientation.m01 * translationStep;
    g_freeCameraVelocity.z -= g_sceneOrientation.m02 * translationStep;
  }
  if (pressed[7] != zero) {
    g_freeCameraVelocity.x += g_sceneOrientation.m00 * translationStep;
    g_freeCameraVelocity.y += g_sceneOrientation.m01 * translationStep;
    g_freeCameraVelocity.z += g_sceneOrientation.m02 * translationStep;
  }
  if (pressed[8] != zero) {
    g_freeCameraVelocity.x += g_sceneOrientation.m20 * translationStep;
    g_freeCameraVelocity.y += g_sceneOrientation.m21 * translationStep;
    g_freeCameraVelocity.z += g_sceneOrientation.m22 * translationStep;
  }
  if (pressed[9] != zero) {
    g_freeCameraVelocity.x -= g_sceneOrientation.m20 * translationStep;
    g_freeCameraVelocity.y -= g_sceneOrientation.m21 * translationStep;
    g_freeCameraVelocity.z -= g_sceneOrientation.m22 * translationStep;
  }
  if (pressed[11] != zero) {
    g_freeCameraVelocity.x -= g_sceneOrientation.m10 * translationStep;
    g_freeCameraVelocity.y -= g_sceneOrientation.m11 * translationStep;
    g_freeCameraVelocity.z -= g_sceneOrientation.m12 * translationStep;
  }
  if (pressed[10] != zero) {
    g_freeCameraVelocity.x += g_sceneOrientation.m10 * translationStep;
    g_freeCameraVelocity.y += g_sceneOrientation.m11 * translationStep;
    g_freeCameraVelocity.z += g_sceneOrientation.m12 * translationStep;
  }

  ++g_freeCameraRecordTicks;
  g_freeCameraVelocity.x *= damping.m_translation;
  g_freeCameraVelocity.y *= damping.m_translation;
  g_freeCameraVelocity.z *= damping.m_translation;
  g_gameInverseViewMatrix = g_sceneOrientation;
  g_scenePosition.x += ticks * g_freeCameraVelocity.x;
  g_scenePosition.y += ticks * g_freeCameraVelocity.y;
  g_scenePosition.z += ticks * g_freeCameraVelocity.z;
  g_gameCameraWorldPosition = g_scenePosition;

  if (g_gameKeyDown[c_gameFreeCameraRecordInput] == zero &&
      g_freeCameraRecordTicks % 50 != zero)
    return;

  g_gameKeyDown[c_gameFreeCameraRecordInput] = (SumoU8)zero;
  FILE *stream = fopen("camera.dat", "a");
  fprintf(stream,
          // STRING: SUMO 0x0042b25c
          // STRING: EDITOR 0x0042b25c
          "{%d,%d,%d,%d,%d,%d,%d},\n",
          (SumoS32)(g_scenePhaseA * g_freeCameraAngleRecordScale),
          (SumoS32)(g_scenePhaseB * g_freeCameraAngleRecordScale),
          (SumoS32)(g_sceneAngle * g_freeCameraAngleRecordScale),
          (SumoS32)(g_scenePosition.x * g_freeCameraPositionRecordScale),
          (SumoS32)(g_scenePosition.y * g_freeCameraPositionRecordScale),
          (SumoS32)(g_scenePosition.z * g_freeCameraPositionRecordScale),
          g_freeCameraRecordTicks);
  fclose(stream);
  g_freeCameraRecordTicks = zero;
}

extern HWND g_gameLevelEditorEditControl;
extern HWND g_gameLevelEditorStatusWindow;
extern const char g_gameScreenshotWriteMode[];
extern SumoS32 g_levelLoadState[8];

extern const char g_gameLevelEditedFilename[] = "edited.txt";

extern char g_gameLevelEditBuffer[0x80000];

// GLOBAL: SUMO 0x0042c5b8
// GLOBAL: EDITOR 0x0042c5b8
SumoF32 g_gameLevelArenaExtent = 100.0f;

// FUNCTION: SUMO 0x00406985
// FUNCTION: EDITOR 0x004069a7
void LoadGameLevel(char *source) {
  g_pendingManCount = 0;
  g_levelLoadState[4] = 0;
  g_levelLoadState[6] = 0;
  g_screenTintLevel = 0;
  g_levelLoadState[7] = 0;
  g_levelLoadState[0] = -1;
  g_levelLoadState[1] = -1;
  g_levelLoadState[2] = -1;
  g_levelLoadState[3] = -1;

  ResetGameBoxes();
  memset(g_gameContactObjects, 0, sizeof(g_gameContactObjects));
  g_gameContactObjectsEnd = g_gameContactObjects;

  Vector3 position;
  position.x = 0.0f;
  position.z = 0.0f;
  position.y = -20.0f;

  Vector3 halfSize;
  halfSize.x = g_gameLevelArenaExtent;
  halfSize.y = -10.0f;
  halfSize.z = g_gameLevelArenaExtent;
  g_nextGameMan = g_gameMen;
  g_currentBox = CreateGameBox(halfSize, position, 1, g_gameBoxDefaultValue);
  g_currentBox->MakeImmovable();
  g_currentBox = NULL;

  if (g_gameIsRunning) {
    char *editBuffer = g_gameLevelEditBuffer;
    GetWindowText(g_gameLevelEditorEditControl, editBuffer, 0x80000);
    FILE *stream = fopen(g_gameLevelEditedFilename, g_gameScreenshotWriteMode);
    fwrite(editBuffer, 1, strlen(editBuffer), stream);
    fclose(stream);
    source = editBuffer;
  }

  g_gameParser.Reset();
  g_gameParser.AddStandardConstants();
  g_gameParser.m_globalVariables = NULL;
  g_gameParser.CompileStatements(source);

  if (g_gameIsRunning) {
    if (g_gameParser.m_hasError) {
      SetWindowText(g_gameLevelEditorStatusWindow, g_gameParser.m_errorMessage);
    } else {
      SetWindowText(g_gameLevelEditorStatusWindow,
                    "Sumotori Dreams level editor");
      g_gameParser.PrepareEvaluation();
      g_gameParser.Evaluate();
    }
  } else if (g_gameParser.m_hasError) {
    MessageBox(NULL, g_gameParser.m_errorMessage, "Error in MOD file",
               MB_ICONEXCLAMATION);
  }

  if (g_currentBox != NULL) {
    Matrix3 savedOrientation = g_currentBox->orientation;
    SumoF32 savedBreakability = g_currentBox->breakability;
    bool wasImmovable = g_currentBox->immovable;

    g_currentBox->FinishContacts(1);
    g_currentBox->RecalculateMass();
    g_currentBox->ClearForces();
    g_currentBox->InitializePhysics();
    if (wasImmovable) {
      g_currentBox->MakeImmovable();
    }

    g_currentBox->orientation = savedOrientation;
    g_currentBox->breakability = savedBreakability;
  }

  GameMan *man = g_gameMen;
  if (man < g_nextGameMan) {
    Vector3 lateralAxis;
    lateralAxis.x = 0.0f;
    lateralAxis.y = 0.0f;
    lateralAxis.z = 0.0f;
    Vector3 facingAxis;
    facingAxis.x = 0.0f;
    facingAxis.y = 0.0f;
    facingAxis.z = 0.0f;

    do {
      Vector3 lateral = lateralAxis;
      Vector3 facing = facingAxis;
      man->state700 = (SumoIntPtr)man->FindNearestOpponent(facing, lateral);
      ++man;
    } while (man < g_nextGameMan);
  }

  if (g_gameParser.m_hasError) {
    g_gameContactObjectsEnd = g_gameContactObjects;
    g_nextGameMan = g_gameMen;
    g_gameBoxesEnd = g_gameBoxes;
  }

  RefreshGameContactLists();
}

extern GameMan g_gameMen[];
extern GameMan *g_nextGameMan;
extern GameBox g_gameBoxes[];
extern GameBox *g_gameBoxesEnd;
extern const SumoF32 g_gameFloorHalfExtent;
extern const SumoF32 g_gameRampStep32;
extern const SumoF32 g_gameArenaHalfExtent;
extern const SumoF32 g_gameArenaVerticalHalfSize;
extern const SumoF32 g_gameBoxDefaultValue;
extern const SumoF32 g_gameArenaLowerPointScale;
extern const SumoF32 g_gameWallQuarterTurn;
extern const SumoF32 g_gameWallCenterSegment;
extern const SumoF32 g_gameWallSegmentSpacing;
extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_gameMenuPage;
extern SumoF32 g_gameDecorationHeight;
extern const SumoF32 g_gameProjectileDefaultValue;
extern const SumoF32 g_gameRimAngleStep;
extern const SumoF32 g_gameRimTiltAngle;
extern SumoS32 g_gameIsRunning;
extern SumoF32 g_gameArenaExtent;

void BuildDefaultGameArena(SumoS32 type) {
  memset(g_gameContactObjects, 0, sizeof(g_gameContactObjects));
  g_gameContactObjectsEnd = g_gameContactObjects;

  g_nextGameMan = g_gameMen;
  g_gameBoxesEnd = g_gameBoxes;

  Vector3 floorPosition;
  floorPosition.x = 0.0f;
  floorPosition.z = 0.0f;
  floorPosition.y = -4.0f;
  Vector3 floorHalfSize;
  if (g_sumoMode != 4) {
    if (g_sumoMode == 1) {
      floorHalfSize.x = g_gameFloorHalfExtent / 4;
      floorHalfSize.y = -3.0f;
      floorHalfSize.z = g_gameFloorHalfExtent / 4;
    } else {
      floorHalfSize.x = g_gameFloorHalfExtent;
      floorHalfSize.y = -3.0f;
      floorHalfSize.z = g_gameFloorHalfExtent;
    }
    CreateGameBox(floorHalfSize, floorPosition, 1, g_gameRampStep32)->MakeImmovable();
  }

  Vector3 platformPosition;
  platformPosition.x = 0.0f;
  platformPosition.y = 2.0f;
  platformPosition.z = 0.0f;
  GameBox *platform = CreateGameBox(
      MakeVector3(g_gameArenaHalfExtent, g_gameArenaVerticalHalfSize,
                  g_gameArenaHalfExtent),
      platformPosition, type, g_gameBoxDefaultValue);

  for (SumoS32 index = 0; index < 8; ++index) {
    GameBoxPoint &point = platform->pointsBegin[index];
    if (point.position.y < g_vectorZero)
      point.position.z = point.position.z * g_gameArenaLowerPointScale;
  }

  platform->FinishContacts(1);
  platform->InitializePhysics();
  platform->MakeImmovable();

  Vector3 wallHalfSize;
  wallHalfSize.x = 8.0f;
  wallHalfSize.y = -4.0f;
  wallHalfSize.z = 0.5f;
  Vector3 wallPosition;
  wallPosition.y = 3.0f;
  wallPosition.z = 54.0f;

  for (SumoS32 side = 0; side < 4; ++side) {
    SumoF32 sideAngle = (SumoF32)side * g_gameWallQuarterTurn;
    Vector3 positionRotation;
    positionRotation.x = 0.0f;
    positionRotation.y = sideAngle;
    positionRotation.z = 0.0f;

    for (SumoS32 segment = 0; segment < 6; ++segment) {
      wallPosition.x = ((SumoF32)segment - g_gameWallCenterSegment) *
                       g_gameWallSegmentSpacing;
      GameBox *wall = CreateGameBox(wallHalfSize, wallPosition, type,
                                    g_gameBoxDefaultValue);
      Vector3 orientationRotation;
      orientationRotation.x = 0.0f;
      orientationRotation.y = sideAngle;
      orientationRotation.z = 0.0f;
      wall->orientation.Rotate(orientationRotation);
      wall->position.Rotate(positionRotation);
      wall->MakeImmovable();
      wall->breakability = 40.0f;
      wall->damping = 3.0f;
      wall->unknownC0 = 2;
      wall->unknownC4 = 0.6f;
      if (g_levelLoadState[4] == 10 && side == 2 && segment == 4 &&
          g_gameMenuPage == 0)
        wall->unknownBC = 6;
    }
  }

  Vector3 rimPosition;
  rimPosition.x = 0.0f;
  rimPosition.y = 5.0f;
  rimPosition.z = g_gameDecorationHeight;
  Vector3 rimHalfSize;
  rimHalfSize.x = 2.6f;
  rimHalfSize.y = -0.2f;
  rimHalfSize.z = 0.45f;

  for (SumoS32 rim = 0; rim < 31; ++rim) {
    GameBox *decoration = CreateGameBox(rimHalfSize, rimPosition, type,
                                        g_gameProjectileDefaultValue);
    SumoF32 rimAngle = (SumoF32)rim * g_gameRimAngleStep;
    Vector3 orientationRotation;
    orientationRotation.x = 0.0f;
    orientationRotation.y = rimAngle;
    orientationRotation.z = 0.0f;
    decoration->orientation.Rotate(orientationRotation);
    Vector3 positionRotation;
    positionRotation.x = 0.0f;
    positionRotation.y = rimAngle;
    positionRotation.z = 0.0f;
    decoration->position.Rotate(positionRotation);
    decoration->orientation.RotateRows12(g_gameRimTiltAngle);
    decoration->MakeImmovable();
  }

  g_gameArenaExtent = 40.0f;
  if (g_gameIsRunning != 0)
    g_gameArenaExtent = 200.0f;

    if (g_sumoMode == 1)
    g_gameArenaExtent = 2000.0f;
}

// FUNCTION: SUMO 0x0040e718
// FUNCTION: EDITOR 0x0040e73a
void GameManPose::InitializeJointTransforms(GameMan *p_man) {
  for (SumoS32 index = 0; index < sizeof(joints) / sizeof(joints[0]); ++index) {
    joints[index].firstDirection =
        p_man->joints[index]->boxes[1]->orientation.Transform(
            p_man->joints[index]->firstPoseDirection.Transform(
                p_man->joints[index]->boxes[0]->orientation));
    joints[index].secondDirection =
        p_man->joints[index]->boxes[1]->orientation.Transform(
            p_man->joints[index]->secondPoseDirection.Transform(
                p_man->joints[index]->boxes[0]->orientation));
  }
}

// FUNCTION: SUMO 0x0040fd4c
// FUNCTION: EDITOR 0x0040fd6e
SumoF32 CalculateLimbAngleCosine(SumoF32 firstLength, SumoF32 secondLength,
                                 SumoF32 targetLength) {
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

void GameAudioNoOpCallback();

void RenderGameCrossMarker(Vector3 *center, void *context) {
  (void)context;
  Vector3 nearCorner;
  nearCorner.x = g_gameBoxYScale;
  nearCorner.y = 0.0f;
  nearCorner.z = g_gameBoxYScale;
  Vector3 farCorner;
  farCorner.x = 1.0f;
  farCorner.y = 0.0f;
  farCorner.z = 1.0f;
  Vector3 firstStart = *center + nearCorner;
  Vector3 firstEnd = *center + farCorner;
  GameAudioNoOpCallback();
  (void)firstStart;
  (void)firstEnd;

  Vector3 leftCorner;
  leftCorner.x = g_gameBoxYScale;
  leftCorner.y = 0.0f;
  leftCorner.z = 1.0f;
  Vector3 rightCorner;
  rightCorner.x = 1.0f;
  rightCorner.y = 0.0f;
  rightCorner.z = g_gameBoxYScale;
  Vector3 secondStart = *center + leftCorner;
  Vector3 secondEnd = *center + rightCorner;
  GameAudioNoOpCallback();
  (void)secondStart;
  (void)secondEnd;
}

extern GameBox *g_gameBoxesEnd;
extern const SumoF32 g_gameOne;
extern const SumoF32 g_randomHalf;
extern const SumoF32 g_gameProjectileDefaultValue;

void GameMan::Initialize(Vector3 &position, SumoF32 angle, SumoS32 type,
                         SumoIntPtr flags) {
  memset(this, 0, sizeof(GameMan));

  decisionTickA = (SumoS32)((g_simulationRandom.Next() + g_gameOne) * 300.0f);
  decisionTickB = (SumoS32)((g_simulationRandom.Next() + g_gameOne) * 300.0f);
  randomHeading = (SumoS32)(g_simulationRandom.Next() * 180.0f);
  randomActionDelay = 0;
  if (g_simulationRandom.Next() < g_randomHalf && flags != 0 &&
      ((GameMan *)flags)->mode == 2)
    randomActionDelay = (SumoS32)(g_simulationRandom.Next() * 120.0f);
  alternateBehavior = g_simulationRandom.Next() < 0.3f ? 1 : 0;

  Vector3 pelvisOffset = MakeVector3(0.0f, 13.8f, 0.0f);
  GameBox *pelvis =
      CreateGameBox(MakeVector3(2.8f, -2.2f, 2.0f), pelvisOffset + position,
                    type, g_gameProjectileDefaultValue);

  if (g_sumoMode == 2)
  {
    pelvis->breakability = 550;
  }
  pelvis->modeE0 = 0x28;
  pelvis->orientation.RotateRows02(angle);
  Vector3 nudge = MakeVector3(0.0f, 0.0f, 0.1f);
  pelvis->linearVelocity += pelvis->orientation.Transform(nudge);
  pelvis->unknownC0 = 4;
  pelvis->unknownC4 = 0.01f;
  pelvis->m_pOwner = this;
  GameBox *chest = CreateGameBox(MakeVector3(2.7f, -2.2f, 1.5f),
                                 MakeVector3(0.0f, 30.0f, 0.0f), type,
                                 g_gameProjectileDefaultValue);
  chest->modeE0 = 0x28;
  chest->unknownC0 = 4;
  chest->unknownC4 = 0.01f;
  chest->m_pOwner = this;
    if (g_sumoMode == 2) 
    {
    chest->breakability = 300;
    }

  GameBox *head = CreateGameBox(MakeVector3(1.2f, -1.5f, 1.2f),
                                MakeVector3(0.0f, 36.0f, 0.0f), type,
                                g_gameProjectileDefaultValue);
  head->modeE0 = 0x28;
  head->m_pOwner = this;
    if (g_sumoMode == 2) {
    head->breakability = 150;
  }

  GameBoxJoint *joint = g_gameContactObjectsEnd;
  joint->boxes[0] = pelvis;
  joint->localAnchors[0] = MakeVector3(0.0f, 2.4f, 0.0f);
  joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
  joint->secondPoseDirection = MakeVector3(1.0f, 0.0f, 0.0f);
  joint->boxes[1] = chest;
  joint->localAnchors[1] = MakeVector3(0.0f, -2.2f, 0.0f);
  joint->secondAnchorDirection = MakeVector3(0.0f, -1.0f, 0.0f);
  joint->secondAxis = MakeVector3(1.0f, 0.0f, 0.0f);
  joint->minimumAngle = 0.3f * 0.3f;
  joint->maximumAngle = 0.4f * 0.4f;
  joint->state = 0.0f;
  joint->mode60 = 1;
  AlignGameBoxJointTransform(joint, 0);
  g_gameContactObjectsEnd++;

  joint = g_gameContactObjectsEnd;
  joint->boxes[0] = chest;
  joint->localAnchors[0] = MakeVector3(0.0f, 2.7f, 0.0f);
  joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
  joint->secondPoseDirection = MakeVector3(1.0f, 0.0f, 0.0f);
  joint->boxes[1] = head;
  joint->localAnchors[1] = MakeVector3(0.0f, -1.5f, 0.0f);
  joint->secondAnchorDirection = MakeVector3(0.0f, -1.0f, 0.0f);
  joint->secondAxis = MakeVector3(1.0f, 0.0f, 0.0f);
  joint->minimumAngle = 0.7f * 0.7f;
  joint->maximumAngle = 0.9f * 0.9f;
  joint->state = 0.0f;
  joint->mode60 = 0;
  AlignGameBoxJointTransform(joint, 0);
  g_gameContactObjectsEnd++;

  SumoF32 facing = 1.0f;
  Vector3 footSize = MakeVector3(1.2f, -0.7f, 2.0f);
  for (SumoS32 side = 2; side != 0; --side) {
    SumoF32 legReach = facing * 1.5f;
    Vector3 footOffset = MakeVector3(legReach, 0.7f, 1.0f);
    GameBox *foot = CreateGameBox(footSize, footOffset + position, type,
                                  g_gameProjectileDefaultValue);
    foot->ScaleMassProperties(3.0f);
    foot->modeE0 = 0x28;
    foot->unknownC0 = 3;
    foot->unknownC4 = 0.002f;
    foot->inertia = foot->inertia * g_randomHalf;
    foot->unknownC8 = 400.0f;
    foot->inverseInertia = foot->inverseInertia + foot->inverseInertia;
    if (g_sumoMode == 2) {
      //foot->breakability = 550;
    }
    Vector3 shinOffset = MakeVector3(legReach, 2.2f, 0.0f);
    GameBox *shin =
        CreateGameBox(MakeVector3(1.0f, -2.3f, 1.0f), shinOffset + position,
                      type, g_gameProjectileDefaultValue);
    shin->ScaleMassProperties(1.7f);
    shin->modeE0 = 0x28;
    shin->unknownC0 = 4;
    shin->unknownC4 = 0.005f;
    if (g_sumoMode == 2) {
      //shin->breakability = 500;
    }
    Vector3 thighOffset = MakeVector3(facing * 3.0f, 2.2f, 0.0f);
    GameBox *thigh =
        CreateGameBox(MakeVector3(1.2f, -3.0f, 1.2f), thighOffset + position,
                      type, g_gameProjectileDefaultValue);
    thigh->modeE0 = 0x28;
    thigh->unknownC0 = 4;
    thigh->unknownC4 = 0.005f;

    if (g_sumoMode == 2) {
      //thigh->breakability = 750;
    }

    joint = g_gameContactObjectsEnd;
    joint->boxes[0] = thigh;
    joint->localAnchors[0] = MakeVector3(0.0f, 2.2f, 0.0f);
    joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
    joint->secondPoseDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->boxes[1] = pelvis;
    Vector3 hipAnchor = joint->localAnchors[0];
    joint->localAnchors[1] = MakeVector3(legReach, -2.0f, 0.0f);
    joint->secondAnchorDirection = MakeVector3(facing * 0.8f, -1.0f, 0.1f);
    joint->secondAnchorDirection.Normalize();
    joint->secondAxis = MakeVector3(facing, 0.0f, -0.6f);
    joint->secondAxis.Normalize();
    joint->minimumAngle = 0.8f * 0.8f;
    joint->maximumAngle = 0.6f * 0.6f;
    joint->state = 0.0f;
    joint->mode60 = 0;
    AlignGameBoxJointTransform(joint, 1);
    g_gameContactObjectsEnd++;

    joint = g_gameContactObjectsEnd;
    joint->boxes[0] = shin;
    joint->localAnchors[0] = MakeVector3(0.0f, 2.3f, 0.0f);
    joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
    joint->secondPoseDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->boxes[1] = thigh;
    Vector3 kneeAnchor = joint->localAnchors[0];
    joint->localAnchors[1] = MakeVector3(0.0f, -2.5f, 0.0f);
    joint->secondAnchorDirection = MakeVector3(0.0f, -0.2f, -1.0f);
    joint->secondAnchorDirection.Normalize();
    joint->secondAxis = MakeVector3(facing, 0.0f, 0.0f);
    joint->minimumAngle = 0.98f * 0.98f;
    joint->maximumAngle = 0.5f * 0.5f;
    joint->state = 1.0f;
    joint->mode60 = 0;
    Vector3 thighSpan = hipAnchor - joint->localAnchors[1];
    firstLimbLength = (SumoF32)sqrt(thighSpan.LengthSquared());
    AlignGameBoxJointTransform(joint, 1);
    g_gameContactObjectsEnd ++;

    joint = g_gameContactObjectsEnd;
    joint->boxes[0] = foot;
    joint->localAnchors[0] = MakeVector3(0.0f, 1.0f, -1.0f);
    joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
    joint->secondPoseDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->boxes[1] = shin;
    joint->localAnchors[1] = MakeVector3(0.0f, -1.8f, 0.0f);
    joint->secondAnchorDirection = MakeVector3(0.0f, -1.0f, 0.0f);
    joint->secondAxis = MakeVector3(facing, 0.0f, 0.0f);
    joint->minimumAngle = 0.7f * 0.7f;
    joint->maximumAngle = 0.5f * 0.5f;
    joint->state = 0.0f;
    joint->mode60 = 0;
    Vector3 shinSpan = kneeAnchor - joint->localAnchors[1];
    secondLimbLength = (SumoF32)sqrt(shinSpan.LengthSquared());
    AlignGameBoxJointTransform(joint, 1);
    g_gameContactObjectsEnd++;

    facing = -1.0f;
  }

  facing = 1.0f;
  Vector3 upperArmSize = MakeVector3(1.9f, -0.8f, 1.1f);
  Vector3 forearmSize = MakeVector3(1.9f, -0.7f, 0.8f);
  Vector3 handSize = MakeVector3(1.4f, -0.3f, 1.1f);
  Vector3 armOrigin = MakeVector3(0.0f, 0.0f, 0.0f);
  for (SumoS32 side = 2; side != 0; --side) {
    GameBox *upperArm = CreateGameBox(upperArmSize, armOrigin, type,
                                      g_gameProjectileDefaultValue);
    upperArm->modeE0 = 0x28;
    GameBox *forearm = CreateGameBox(forearmSize, armOrigin, type,
                                     g_gameProjectileDefaultValue);
    forearm->modeE0 = 0x28;
    GameBox *hand =
        CreateGameBox(handSize, armOrigin, type, g_gameProjectileDefaultValue);
    hand->unknownC4 = 0.005f;
    hand->unknownC0 = 4;
    hand->modeE0 = 0x28;
    forearm->unknownC4 = 0.005f;
    forearm->unknownC0 = 4;
    upperArm->unknownC4 = 0.005f;
    upperArm->unknownC0 = 4;
    hand->ScaleMassProperties(2.0f);
    forearm->ScaleMassProperties(1.5f);

    joint = g_gameContactObjectsEnd;
    joint->boxes[1] = chest;
    joint->localAnchors[1] = MakeVector3(facing * 3.2f, 2.0f, 0.1f);
    joint->secondAnchorDirection = MakeVector3(facing, 0.0f, 0.2f);
    joint->secondAxis = MakeVector3(facing * g_vectorZero, 1.0f, 0.0f);
    joint->secondAxis.Normalize();
    joint->boxes[0] = upperArm;
    joint->localAnchors[0] = MakeVector3(facing * -1.5f, 0.0f, 0.0f);
    joint->firstPoseDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->secondPoseDirection = MakeVector3(facing * 0.5f, 1.0f, 0.0f);
    joint->secondPoseDirection.Normalize();
    joint->minimumAngle = 0.98f * 0.98f;
    joint->maximumAngle = 0.7f * 0.7f;
    joint->state = 0.0f;
    joint->mode60 = 0;
    AlignGameBoxJointTransform(joint, 1);
    g_gameContactObjectsEnd ++;

    SumoF32 armReach = facing * 1.5f;
    joint = g_gameContactObjectsEnd;
    joint->boxes[0] = upperArm;
    joint->localAnchors[0] = MakeVector3(armReach, 0.0f, -0.3f);
    joint->firstPoseDirection = MakeVector3(facing * 0.6f, 0.0f, 1.0f);
    joint->firstPoseDirection.Normalize();
    joint->secondPoseDirection = MakeVector3(0.0f, 1.0f, 0.0f);
    joint->boxes[1] = forearm;
    joint->localAnchors[1] = MakeVector3(-1.8f * facing, 0.0f, 0.0f);
    joint->secondAnchorDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->secondAxis = MakeVector3(0.0f, 1.0f, 0.0f);
    joint->minimumAngle = 0.87f * 0.87f;
    joint->maximumAngle = 0.5f * 0.5f;
    joint->state = 1.0f;
    joint->mode60 = 0;
    AlignGameBoxJointTransform(joint, 0);
    g_gameContactObjectsEnd++;

    joint = g_gameContactObjectsEnd;
    joint->boxes[0] = forearm;
    joint->localAnchors[0] = MakeVector3(armReach, 0.0f, 0.1f);
    joint->firstPoseDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->secondPoseDirection = MakeVector3(0.0f, 1.0f, 0.0f);
    joint->boxes[1] = hand;
    joint->localAnchors[1] = MakeVector3(-1.1f * facing, 0.0f, 0.0f);
    joint->secondAnchorDirection = MakeVector3(facing, 0.0f, 0.0f);
    joint->secondAxis = MakeVector3(0.0f, 1.0f, 0.0f);
    joint->minimumAngle = 0.5f * 0.5f;
    joint->maximumAngle = 0.8f * 0.8f;
    joint->state = 0.0f;
    joint->mode60 = 0;
    AlignGameBoxJointTransform(joint, 0);
    g_gameContactObjectsEnd++;

    facing = -1.0f;
  }

  for (SumoS32 index = 0; index < 15; ++index) 
  {
    bodyParts[index] = g_gameBoxesEnd - 15 + index;
    bodyParts[index]->m_pOwner = this;
  }
  GameBoxJoint *jointBase = g_gameContactObjectsEnd - 14;
  for (SumoS32 index = 0; index < 14; ++index)
    joints[index] = jointBase + index;

  standingHeight = -7.9f;
  firstFootTarget = MakeVector3(0.5f, -7.9f, 0.0f);
  secondFootTarget = MakeVector3(-0.5f, -7.9f, 0.0f);
  primaryPose.InitializeJointTransforms(this);
  secondaryPose.InitializeJointTransforms(this);
  state700 = flags;
}

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

    if (m_bLobotomized) break;
  }

  SumoF32 inverseMass = 1.0f / totalMass;
  weightedPosition.x *= inverseMass;
  weightedPosition.y *= inverseMass;
  weightedPosition.z *= inverseMass;
  if (!(g_gamePlayerCount == 1 && g_gameHumanPlayerCount == 1)) 
  {
    SumoF32 horizontalDistanceSquared =
        weightedPosition.z * weightedPosition.z +
        weightedPosition.x * weightedPosition.x;
    if (horizontalDistanceSquared + weightedPosition.y * weightedPosition.y >
        g_gameMaximumCenterDistanceSquared) {
      if (m_bLobotomized == 0 && weightedPosition.y < 0.f)
        m_bLobotomized++;
      weightedPosition.z = 0.0f;
      weightedPosition.y = 0.0f;
      weightedPosition.x = 0.0f;
    }
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

SumoF32 GameMan::CalculateKineticEnergy() {
  SumoF32 energy = 0.0f;
  for (SumoS32 index = 0; index < 15; ++index) {
    GameBox *part = bodyParts[index];
    SumoF32 linearTerm =
        (SumoF32)((SumoF64)part->linearVelocity.LengthSquared() * part->mass);
    energy = (SumoF32)((SumoF64)part->angularVelocity.LengthSquared() *
                           part->inertia +
                       linearTerm + energy);
  }
  return energy;
}

Vector3 GameMan::CalculateAngularMomentum(Vector3 &referencePosition,
                                          Vector3 &referenceVelocity) {
  Vector3 sum;
  sum.x = 0.0f;
  sum.y = 0.0f;
  sum.z = 0.0f;
  for (SumoS32 index = 0; index < 15; ++index) {
    GameBox *part = bodyParts[index];
    Vector3 spinTerm = part->angularVelocity.Scale(part->inertia);
    Vector3 offset = part->position - referencePosition;
    Vector3 contribution = (part->linearVelocity - referenceVelocity)
                               .Cross(offset)
                               .Scale(part->mass) +
                           spinTerm;
    sum.x = sum.x + contribution.x;
    sum.y = sum.y + contribution.y;
    sum.z = sum.z + contribution.z;
  }
  return sum;
}

extern SumoU8 g_gameKeyDown[256];

// FUNCTION: SUMO 0x0040fe79
// FUNCTION: EDITOR 0x0040fe9b
SumoS32 __fastcall ReadGameManInputMask(SumoS32 p_playerIndex) {
  SumoS8 scanCodes[2][8] = {
      {0x4b, 0x4d, 0x48, 0x50, 0x0e, 0x1c},
      {0x1e, 0x20, 0x11, 0x1f, 0x2a, 0x1d},
  };
  SumoS32 flag = 1;
  SumoS32 index = 0;
  SumoS8 *playerScanCodes = scanCodes[p_playerIndex];
  p_playerIndex = 0;
  do {
    if (g_gameKeyDown[playerScanCodes[index]]) {
      p_playerIndex |= flag;
    }
    flag += flag;
    ++index;
  } while (index < 6);
  return p_playerIndex;
}

extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gameMenuAlternateLayout;
extern const SumoF32 g_gameNegativeHalf;
extern const SumoF32 g_gameAiForwardDistanceSquaredLimit;
extern const SumoF32 g_gameAiLateralRecoveryThreshold;
extern const SumoF32 g_gameAiMotionSquaredLimit;
extern const SumoF32 g_gameAiOpponentMotionSquaredLimit;
extern const SumoF32 g_gameAiPushDistanceThreshold;
extern const SumoF32 g_gameAiStabilitySquaredLimit;
extern const SumoF32 g_gameAiStateScale;
extern const SumoF32 g_gameAiVelocityProjectionScale;

SumoU32 GameMan::ChooseAiInput(GameMan *opponent) {
  if (g_levelLoadState[4] == 11) {
    if (bodyParts[0]->unknownD4 == g_screenTintLevel &&
        g_screenTintLevel > 10 && postureState == 0 && active == 0)
      SetGameManAudioState(this, 1);
    return 0;
  }

  Vector3 ownVelocity = CalculateCenterOfMassVelocity();
  Vector3 opponentVelocity = opponent->CalculateCenterOfMassVelocity();
  SumoU32 input = 0;

  Vector3 forward;
  forward.x = 1.0f;
  forward.y = 0.0f;
  forward.z = 0.0f;
  Vector3 facing = forward.Transform(bodyParts[0]->orientation);
  facing.y = 0.0f;
  facing.Normalize();
  Vector3 up;
  up.x = 0.0f;
  up.y = 1.0f;
  up.z = 0.0f;
  Vector3 lateral = facing.Cross(up);
  Vector3 toOpponent =
      opponent->bodyParts[0]->position - bodyParts[0]->position;

  SumoF32 lateralMotion = (SumoF32)((SumoF64)lateral.y * motionVector.y +
                                    (SumoF64)lateral.z * motionVector.z +
                                    (SumoF64)lateral.x * motionVector.x);
  SumoF32 forwardDistance = (SumoF32)((SumoF64)facing.z * toOpponent.z +
                                      (SumoF64)facing.x * toOpponent.x +
                                      (SumoF64)facing.y * g_vectorZero);
  SumoU8 opponentActing = opponent->actionMode != 0;
  SumoF32 lateralDistance = (SumoF32)((SumoF64)toOpponent.z * lateral.z +
                                      (SumoF64)toOpponent.x * lateral.x +
                                      (SumoF64)lateral.y * g_vectorZero);
  SumoU8 opponentMoving = opponent->motionVector.LengthSquared() >
                          g_gameAiOpponentMotionSquaredLimit;
  SumoU8 opponentSteady =
      opponent->locomotionForce.LengthSquared() < g_gameAiStabilitySquaredLimit;

  SumoF64 forwardSquared = (SumoF64)forwardDistance * forwardDistance;
  volatile SumoF32 forwardSquaredRounded = (SumoF32)forwardSquared;
  SumoF64 quarterSpan = ((SumoF64)toOpponent.z * toOpponent.z +
                         (SumoF64)toOpponent.x * toOpponent.x) *
                        0.25f;

  do {
    if (!(forwardSquared < quarterSpan)) {
      if (forwardSquared > g_gameAiMotionSquaredLimit)
        break;
    }
    if (motionVector.LengthSquared() > g_gameAiMotionSquaredLimit)
      break;
    if (!(lateralDistance > g_vectorZero))
      break;
    if (opponentMoving)
      break;
    if (approachTicks >= 0xa0) {
      SumoF64 ownLateralMotion = (SumoF64)lateral.y * motionVector.y +
                                 (SumoF64)lateral.z * motionVector.z +
                                 (SumoF64)lateral.x * motionVector.x;
      if (!(ownLateralMotion > g_gameAiLateralRecoveryThreshold))
        break;
    }
    SumoF32 walkDistance = 1.6f;
    if (opponentSteady)
      walkDistance = 1.4f;
    if (active == 3)
      walkDistance =
          (SumoF32)((SumoF64)state144 * walkDistance * g_gameAiStateScale);
    SumoS32 elapsed = g_screenTintLevel - g_levelLoadState[6];
    if (randomHeading < elapsed) {
      if ((SumoF64)walkDistance * walkDistance >
          locomotionForce.LengthSquared())
        input = 4;
    } else if (randomActionDelay > elapsed) {
      input = 1;
    }
  } while (0);

  SumoF32 pushDistance = 5.1f;
  if (opponentSteady) {
    pushDistance = 4.8f;
    if (opponentActing)
      pushDistance = 8.0f;
  }

  Vector3 firstRelative = opponentVelocity - ownVelocity;
  Vector3 secondRelative = opponentVelocity - ownVelocity;
  SumoF64 firstTerm = ((SumoF64)lateral.y * firstRelative.y +
                       (SumoF64)lateral.z * firstRelative.z +
                       (SumoF64)lateral.x * firstRelative.x) *
                          g_gameAiVelocityProjectionScale +
                      lateralDistance;
  SumoF64 secondTerm = ((SumoF64)lateral.y * secondRelative.y +
                        (SumoF64)lateral.z * secondRelative.z +
                        (SumoF64)lateral.x * secondRelative.x) *
                           g_gameAiVelocityProjectionScale +
                       lateralDistance;
  SumoF64 closing = firstTerm * secondTerm;

  if ((SumoF64)pushDistance * pushDistance > closing &&
      lateralMotion > g_gameNegativeHalf &&
      !(forwardSquaredRounded > g_gameAiForwardDistanceSquaredLimit)) {
    SumoS32 ticks = approachTicks;
    if (ticks > 10 || pushDistance > g_gameAiPushDistanceThreshold ||
        alternateBehavior != 0)
      input |= 0x20;
    else
      input |= 0x10;
    if (opponentSteady)
      input &= ~4u;
    approachTicks = ticks + 8;
  } else {
    --approachTicks;
    if (approachTicks < 0)
      approachTicks = 0;
  }

  SumoS32 level = g_levelLoadState[4];
  SumoS32 tint = g_screenTintLevel;
  if (level == 0) {
    if (tint > decisionTickA) {
      input = 8;
    } else {
      SumoS32 windowStart = decisionTickB;
      if (tint <= windowStart || tint >= windowStart + 8)
        return input;
      input = 8;
    }
  }
  if (level == 2) {
    if (g_gameMenuAlternateLayout != 0 || g_sumoMode == 3) {
      input &= ~4u;
    } else if (tint % 0x190 > 0xc8) {
      input |= 4;
    }
  }
  return input;
}

extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_gameRoundPlayerCount;
extern SumoS32 g_gameMode;
extern SumoS32 g_selectedLevelScript;
extern SumoU8 g_gameKeyDown[256];
extern SumoF32 g_gameDecorationHeight;
extern SumoF32 g_waterBaseHeight;
extern SumoF32 g_unk0x00c09ce0;
extern const SumoF32 g_boxWaterBuoyancyScale;
extern const SumoF32 g_boxWaterDiagonalScale;
extern const SumoF32 g_boxWaterSurfaceOffset;
extern const SumoF32 g_freeCameraAimScale;
extern const SumoF32 g_gameActivityDecay;
extern const SumoF32 g_gameAiLateralRecoveryThreshold;
extern const SumoF32 g_gameAiMotionSquaredLimit;
extern const SumoF32 g_gameCameraAimDamping;
extern const SumoF32 g_gameCameraDistanceBias;
extern const SumoF32 g_gameCameraHeightScale;
extern const SumoF32 g_gameCameraInputDamping;
extern const SumoF32 g_gameCameraInputOffsetScale;
extern const SumoF32 g_gameCameraMinimumDistance;
extern const SumoF32 g_gameCameraMinimumDistanceScale;
extern const SumoF32 g_gameManPoseImpulseGain;
extern const SumoF32 g_gameNegativeHalf;
extern const SumoF32 g_gameProjectileHalfSize;
extern const SumoF32 g_gameProjectileSpin;
extern const SumoF32 g_gameTwo;
extern const SumoF32 g_gameWallCenterSegment;
extern const SumoF32 g_gameWallSegmentSpacing;
extern const SumoF32 g_parserPi;
extern const SumoF32 g_randomHalf;
extern const SumoF32 g_waterNeighborCoupling;
extern const SumoF32 g_wavyTextDisplacement;
extern const SumoF32 g_wavyTextPhaseScale;
extern const SumoF32 g_wavyTextTimeScale;
extern const SumoF64 g_textureHalf;
extern const SumoF64 g_waterCorrectionScale;

SumoS32 __fastcall ReadGameManInputMask(SumoS32 p_playerIndex);
void RenderGameCrossMarker(Vector3 *center, void *context);

void GameMan::Update(SumoIntPtr state) {
  GameMan *opponent;
  Vector3 *footTargets = &firstFootTarget;
  Vector3 comPosition;
  Vector3 comVelocity;
  Vector3 angularMomentum;
  Vector3 forwardAxis;
  Vector3 lateralAxis;
  Vector3 supportPoint;
  Vector3 predictedCom;
  Vector3 handTargetWorld[2];
  Vector3 armAimLocal[2];
  Vector3 footContactPoint[2];
  SumoU32 inputMask;
  SumoS32 audioChannel;
  SumoF32 poseLift = 0.0f;
  SumoF32 poseSway = 0.0f;
  SumoF32 poseCrouch;
  SumoF32 poseGain;
  SumoF32 footTurnBlend;
  SumoF32 smoothedTurnInput;
  SumoF32 stanceBlendCopy;
  SumoF32 supportSign;
  SumoF32 balanceStrengthNew;
  SumoF32 armExtend[2];
  SumoF32 armCurl[2];
  SumoF32 armRaise[2];
  SumoU8 footHomeFlag;
  SumoU8 poseOverride;
  SumoU8 actionRerun;
  if (m_bLobotomized)
  {
    postureState = 3;
    postureTick = 0;
    balancePitch = 0.0f;
    stanceBlend = 0.5f;
    balanceRoll = 0.0f;
    balancePitchIntegral = 0.0f;
    balancePitchVelocity = 0.0f;
    balanceRollVelocity = 0.0f;
  }
  handTargetWorld[0].x = 0.0f;
  handTargetWorld[0].y = 0.0f;
  handTargetWorld[0].z = 0.0f;
  handTargetWorld[1] = handTargetWorld[0];
  armAimLocal[0] = handTargetWorld[0];
  armAimLocal[1] = handTargetWorld[0];

  comPosition = CalculateCenterOfMassPosition();
  comVelocity = CalculateCenterOfMassVelocity();
  angularMomentum = CalculateAngularMomentum(comPosition, comVelocity);
  centerOfMass = comPosition;

  audioChannel = 1;
  if ((state - (SumoIntPtr)this) / (SumoIntPtr)sizeof(GameMan) > 1)
    audioChannel = 2;
  opponent = (GameMan *)state;
  if (opponent == 0)
    opponent = this;

  if (g_levelLoadState[6] < g_screenTintLevel - 50) {
    for (SumoS32 part = 0; part < 15; ++part) {
      GameBox *box = bodyParts[part];

      if (g_sumoMode != 2) 
      {
        if (box->unknownD8 < g_screenTintLevel - 1)
          continue;
        if (part == 3 || part == 6 || part == 4 || part == 7)
          continue;
        if (g_levelLoadState[4] == 0)
          continue;
      }
      else
      {
          if (!m_bLobotomized)
              continue;

          box->breakability = 250;
          
      }

      if (g_levelLoadState[4] == 11)
      continue;

      if (eliminated == 0) 
      {
        eliminated = 1;
        if (g_sumoMode == 3)
        {
          opponent->eliminated = -1;
          g_gameScores[&g_gameMen[0] == this]++;
          mode = 2;
          RestartGameMusic(9);
          g_levelLoadState[7] = 0;
          g_levelLoadState[4] = 2;
        } 
        else 
        {
          SumoS32 placement = g_gameRoundPlayerCount - 1;
          g_gameRoundPlayerCount = placement;
          g_levelLoadState[placement] = (SumoS32)(this - g_gameMen);
          if (placement <= 1) 
          {
            g_levelLoadState[7] = 0;
            g_levelLoadState[4] = 2;
          }
        }
      }
      active = 5;
      opponent->active = 5;
    }
  }
  if (g_levelLoadState[4] == 2 && eliminated == 0)
    g_levelLoadState[0] = (SumoS32)(this - g_gameMen);

  ++g_levelLoadState[7];
  if (m_bLobotomized)
      return;
  {
    Vector3 unit;
    unit.x = 1.0f;
    unit.y = 0.0f;
    unit.z = 0.0f;
    forwardAxis = unit.Transform(bodyParts[0]->orientation);
    forwardAxis.y = 0.0f;
    forwardAxis.Normalize();
    unit.x = 0.0f;
    unit.y = 1.0f;
    unit.z = 0.0f;
    lateralAxis = forwardAxis.Cross(unit);
  }

  if (g_screenTintLevel - g_levelLoadState[6] > 360) {
    GameMan *nearest = FindNearestOpponent(lateralAxis, forwardAxis);
    if (nearest != 0) {
      opponent = nearest;
      state700 = (SumoIntPtr)nearest;
    }
  }

  {
    SumoS32 controlMode = mode;
    inputMask = 0;
    if (controlMode >= 0) {
      if (controlMode <= 1)
        inputMask = (SumoU32)ReadGameManInputMask(controlMode);
      else if (controlMode == 2)
        inputMask = ChooseAiInput(opponent);
    }
  }

  {
    SumoS32 roundState = g_levelLoadState[4];
    if (g_gameMode != 1) {
      SumoS32 activeNow = active;
      if (activeNow != 0 && activeNow != 3 && activeNow != 5)
        inputMask &= 8;
    } else if (mode == 2 && roundState != 1) {
      inputMask = (SumoU32)ReadGameManInputMask(1);
    }

    SumoU8 approach = g_levelLoadState[7] < 200 && roundState == 2;
    if (!approach)
      approach =
          opponent != 0 && opponent->postureState == 3 && roundState == 0;
    if (approach) {
      Vector3 opponentCom = opponent->CalculateCenterOfMassPosition();
      Vector3 toOpponent = opponentCom - comPosition;
      toOpponent.y = 0.0f;
      SumoF32 approachSpeed = 0.0f;
      if ((SumoF64)toOpponent.x * toOpponent.x +
              (SumoF64)toOpponent.z * toOpponent.z <
          1600.0f) {
        if (motionVector.LengthSquared() > 0.1600000113248825f)
          approachSpeed = 3.5f;
      }
      volatile SumoF32 approachScalePin =
          (SumoF32)((SumoF64)approachSpeed * 0.04000002145767212f);
      SumoF32 approachScale = approachScalePin;
      locomotionForce += toOpponent.Normalized().Scale(approachScale);
    }
  }

  SumoF32 edgeGain = 0.0f;
  {
    do {
      if (!((SumoF64)g_gameDecorationHeight - g_gameCameraMinimumDistance >=
            fabs((SumoF64)comPosition.x))) {
        if ((SumoF64)g_gameDecorationHeight + g_gameWallSegmentSpacing >
            fabs((SumoF64)comPosition.x))
          break;
      }
      if ((SumoF64)g_gameDecorationHeight - g_gameCameraMinimumDistance >=
          fabs((SumoF64)comPosition.z))
        goto edgeBandDone;
      if ((SumoF64)g_gameDecorationHeight + g_gameWallSegmentSpacing <=
          fabs((SumoF64)comPosition.z))
        goto edgeBandDone;
    } while (0);
    edgeGain = 1.5f;
  }
edgeBandDone:
  if (g_levelLoadState[4] == 2 && g_levelLoadState[7] > 300) {
    if (motionVector.LengthSquared() > 0.64000004529953f) {
      SumoS32 postureNow = postureState;
      if (postureNow != 12 && postureNow != 13)
        edgeGain = 0.6000000238418579f;
    }
  }

  {
    Vector3 horizontalCom = comPosition;
    horizontalCom.y = 0.0f;
    if (g_gameIsRunning == 0 && g_selectedLevelScript == 0) {
      SumoF32 driftScale = 0.04000002145767212f;
      locomotionForce +=
          horizontalCom.Normalized().Scale(edgeGain).Scale(driftScale);
    }
  }

  poseGain = 0.1f;
  for (SumoS32 joint = 0; joint < 14; ++joint)
    primaryPose.joints[joint].maximumCorrection =
        joint < 8 ? g_gameProjectileSpin : g_wavyTextTimeScale;
  primaryPose.joints[10].maximumCorrection = g_wavyTextTimeScale;
  primaryPose.joints[13].maximumCorrection = g_wavyTextTimeScale;
  {
    Vector3 spinAxis;
    spinAxis.x = 0.0f;
    spinAxis.y = -9.999999747378752e-06f;
    spinAxis.z = 0.0f;
    Vector3 spinCopy = spinAxis;
    primaryPose.joints[1].maximumCorrection = 0.003000000026077032f;
    Vector3 spinKick = angularMomentum.Cross(spinCopy);
    comVelocity.x = comVelocity.x + spinKick.x;
    comVelocity.y = comVelocity.y + spinKick.y;
    comVelocity.z = comVelocity.z + spinKick.z;
  }
  poseCrouch = 0.0f;
  if (inputMask & 4) {
    SumoF32 sidleScale = 0.032000016421079636f;
    locomotionForce += lateralAxis.Scale(sidleScale);
  }
  {
    SumoF64 turnInput = 0.0;
    if (inputMask & 1)
      turnInput = 0.05999999865889549f;
    if (inputMask & 2)
      turnInput = turnInput - 0.05999999865889549f;
    SumoF64 filtered =
        (turnInput - smoothedTurn) * g_gameProjectileSpin + smoothedTurn;
    smoothedTurn = (SumoF32)filtered;
    smoothedTurnInput = (SumoF32)filtered;
  }
  footHomeFlag = 0;
  poseOverride = 0;
  armExtend[0] = 0.0f;
  armExtend[1] = 0.0f;
  armRaise[0] = g_boxWaterDiagonalScale;
  armRaise[1] = g_boxWaterDiagonalScale;
  armCurl[0] = 0.20000000298023224f;
  armCurl[1] = 0.20000000298023224f;
  if (postureState == 3) {
    if (active < 5)
      active = 0;
  }
  footTurnBlend = 0.0f;

  switch (active) {
  case 4: {
    inputMask = 0;
    if (motionVector.LengthSquared() >= 0.36000001430511475f) {
      state144 = 0;
    } else if (state144 > 100) {
      active = 1;
      state144 = 0;
    }
    ++state144;
    goto actionMachine;
  }
  case 1: {
    SumoS32 riseTick = state144;
    inputMask = 0;
    poseOverride = 1;
    volatile SumoF32 risePhase =
        (SumoF32)((SumoF64)riseTick * 0.01666666753590107f);
    if (riseTick > 60)
      risePhase = 1.0f;
    if (riseTick == 70 || riseTick == 4) {
      Vector3 home;
      home.x = 1.2999999523162842f;
      home.y = standingHeight;
      home.z = 0.0f;
      Vector3 homeCopy = home;
      Vector3 homeDelta = firstFootTarget - homeCopy;
      if (homeDelta.LengthSquared() > 0.1600000113248825f)
        footHomeFlag = 1;
    }
    if (riseTick == 80) {
      state144 = 0;
      actionMode = 3;
      active = 2;
    }
    SumoF64 riseSquared = (SumoF64)risePhase * risePhase;
    SumoF64 riseSmooth = 3.0f * riseSquared;
    SumoF64 riseCubed = riseSquared * risePhase;
    riseCubed += riseCubed;
    riseSmooth = riseSmooth - riseCubed;
    poseCrouch = (SumoF32)(riseSmooth * g_gameProjectileHalfSize);
    volatile SumoF32 swayScalePin = (SumoF32)((1.0 - (SumoF64)risePhase) *
                                              risePhase * g_inertiaRadiusScale);
    SumoF32 swayScale = swayScalePin;
    Vector3 sway = lateralAxis.Scale(swayScale);
    comPosition.x = comPosition.x - sway.x;
    comPosition.y = comPosition.y - sway.y;
    comPosition.z = comPosition.z - sway.z;
    if (postureState == 0)
      goto dispatch0Tick;
    SumoS32 riseNow = state144;
    if (riseNow > 90) {
      state144 = 90;
      goto actionMachine;
    }
    if (riseNow > 0)
      state144 = riseNow - 1;
    goto actionMachine;
  }
  case 2: {
    SumoS32 standTick = state144;
    poseOverride = 1;
    SumoF64 standPhaseWide = (SumoF64)standTick * 0.011111111380159855f;
    volatile SumoF32 standPhase = (SumoF32)standPhaseWide;
    if (standTick > 90) {
      standPhaseWide = 1.0;
      standPhase = 1.0f;
    }
    state144 = standTick + 1;
    SumoF64 standSquared = standPhaseWide * standPhaseWide;
    poseCrouch = 1.25f;
    SumoF32 swayScale = -0.017000000923871994f;
    SumoF64 standSmooth = 3.0f * standSquared;
    SumoF64 standCubed = standSquared * standPhaseWide;
    standCubed += standCubed;
    standSmooth = standSmooth - standCubed;
    poseGain = (SumoF32)(g_gameManPoseImpulseGain * standSmooth);
    poseLift = (SumoF32)(standSmooth * g_wavyTextPhaseScale);
    Vector3 sway = lateralAxis.Scale(swayScale);
    comVelocity.x = comVelocity.x + sway.x;
    comVelocity.y = comVelocity.y + sway.y;
    comVelocity.z = comVelocity.z + sway.z;
    armAimLocal[0].x = -0.10000000149011612f;
    armAimLocal[0].y = 0.0f;
    armAimLocal[0].z = 1.0f;
    armAimLocal[0].Normalize();
    armAimLocal[1].x = 0.10000000149011612f;
    armAimLocal[1].y = 0.0f;
    armAimLocal[1].z = 1.0f;
    armAimLocal[1].Normalize();
    armRaise[0] = 0.0f;
    armRaise[1] = 0.0f;
    SumoF64 standTarget = 0.0;
    if ((inputMask & 8) || state144 > 700)
      standTarget = 1.0;
    if (g_levelLoadState[4] == 1) {
      actionMode = 0;
      state144 = 0;
      active = 3;
    }
    SumoS32 grabTick = g_screenTintLevel - 20;
    if (bodyParts[11]->unknownD4 > grabTick ||
        bodyParts[14]->unknownD8 > grabTick) {
      if (opponent->bodyParts[11]->unknownD8 > grabTick ||
          opponent->bodyParts[14]->unknownD8 > grabTick) {
        g_levelLoadState[4] = 1;
        g_levelLoadState[6] = g_screenTintLevel;
      }
    }
    inputMask = 0;
    SumoF64 blend =
        (standTarget - activityBlend) * 0.1599999964237213f + activityBlend;
    activityBlend = (SumoF32)blend;
    SumoF64 blendSquared = blend * blend;
    volatile SumoF32 curlPair =
        (SumoF32)((g_gameOne - blendSquared * blendSquared) *
                  g_boxWaterDiagonalScale);
    armCurl[0] = curlPair;
    armCurl[1] = curlPair;
    volatile SumoF32 extendPair =
        (SumoF32)((SumoF64)standPhase * g_gameCameraInputOffsetScale);
    armExtend[0] = extendPair;
    armExtend[1] = extendPair;
    goto actionMachine;
  }
  case 3: {
    inputMask = inputMask & 0xfffffff7;
    SumoF32 zeroScale = 0.0f;
    Vector3 zeroSway = lateralAxis.Scale(zeroScale);
    comVelocity.x = comVelocity.x - zeroSway.x;
    comVelocity.y = comVelocity.y - zeroSway.y;
    comVelocity.z = comVelocity.z - zeroSway.z;
    SumoS32 windTick = state144;
    SumoF64 windPhase = (SumoF64)windTick * 0.015384615398943424f;
    if (windTick > 65) {
      active = 0;
      windPhase = 1.0;
    }
    SumoF64 windSquared = windPhase * windPhase;
    SumoF64 windSmooth = 3.0f * windSquared;
    SumoF64 windCubed = windSquared * windPhase;
    windCubed += windCubed;
    SumoF64 windInverse = g_gameOne - (windSmooth - windCubed);
    poseCrouch = (SumoF32)(g_gameProjectileHalfSize * windInverse);
    poseGain = (SumoF32)(g_gameManPoseImpulseGain * windInverse);
    poseLift = (SumoF32)(windInverse * g_wavyTextPhaseScale);
    state144 = windTick + 1;
    goto actionMachine;
  }
  case 5: {
    if (motionVector.LengthSquared() >= 0.36000001430511475f ||
        postureState != 0)
      state144 = 0;
    GameMan *other = opponent;
    SumoU8 riseTogether;
    if (state144 > 100 && (other->state144 > 100 ||
                           (other->state144 < -10 && other->state144 > -200)))
      riseTogether = other->active != 7;
    else
      riseTogether = other->active == 6;
    if (riseTogether) {
      state144 = 0;
      active = 6;
    }
    if (state144 > 700) {
      state144 = 0;
      active = 7;
    }
    goto dispatch0Tick;
  }
  case 6: {
    SumoF64 wavePhase =
        cos((SumoF64)state144 * 0.0071428571827709675f * 6.2831854820251465f);
    SumoS32 waveTick = state144;
    SumoF64 waveLift = (g_gameOne - wavePhase) * g_inertiaRadiusScale;
    poseLift = (SumoF32)waveLift;
    activityOffset = (SumoF32)((SumoF64)g_boxWaterDiagonalScale * waveLift);
    waveLift = waveLift * g_gameBoxYScale;
    poseSway = (SumoF32)waveLift;
    if (waveTick > 140) {
      active = 0;
      poseLift = 0.0f;
      activityOffset = 0.0f;
    }
    state144 = waveTick + 1;
    goto actionMachine;
  }
  case 7: {
    SumoF64 wavePhase =
        sin((SumoF64)state144 * 0.0071428571827709675f * 12.566370964050293f);
    SumoF64 waveDip = wavePhase * g_gameNegativeHalf;
    poseLift = (SumoF32)waveDip;
    activityOffset = (SumoF32)((SumoF64)1.7999999523162842f * waveDip);
    waveDip = waveDip * g_gameBoxYScale;
    poseSway = (SumoF32)waveDip;
    if (state144 <= 140)
      goto dispatch0Tick;
    active = 5;
    poseLift = 0.0f;
    state144 = -500;
    activityOffset = 0.0f;
    goto dispatch0Tick;
  }
  case 8: {
    SumoF64 hopPhase =
        cos((SumoF64)state144 * 0.013333333656191826f * 25.132741928100586f);
    SumoF64 hopLift = (hopPhase - g_gameOne) * -0.15000000596046448f;
    poseCrouch = (SumoF32)hopLift;
    activityOffset = (SumoF32)(-hopLift);
    hopLift = hopLift - 0.15000000596046448f;
    hopLift += hopLift;
    poseSway = (SumoF32)hopLift;
    if (state144 <= 75)
      goto dispatch0Tick;
    active = 5;
    if (g_levelLoadState[4] == 11 || g_gameIsRunning != 0)
      active = 0;
    state144 = -200;
    activityOffset = 0.0f;
    poseCrouch = 0.0f;
    goto dispatch0Tick;
  }
  case 0: goto dispatch0Tick;
  default: goto actionMachine;
  }

dispatch0Tick:
  ++state144;

actionMachine:
  actionRerun = 0;
  if (actionMode == 0)
    goto actionIdle;
  if (actionMode == 1)
    goto actionReach;
  if (actionMode != 2)
    goto actionUpdateDone;
  {
    SumoS32 strikeSide = actionSide;
    primaryPose.joints[8].maximumCorrection = 0.05999999865889549f;
    primaryPose.joints[9].maximumCorrection = 0.05999999865889549f;
    primaryPose.joints[11].maximumCorrection = 0.05999999865889549f;
    primaryPose.joints[12].maximumCorrection = 0.05999999865889549f;
    SumoF32 strikePull = -0.699999988079071f;
    Vector3 pull = lateralAxis.Scale(strikePull);
    comPosition.x = comPosition.x + pull.x;
    comPosition.y = comPosition.y + pull.y;
    comPosition.z = comPosition.z + pull.z;
    SumoS32 strikeTick = actionTick;
    SumoF64 strikePhase = (SumoF64)strikeTick * 0.05000000074505806f;
    if (strikeTick > 20) {
      actionMode = 0;
      actionTick = 0;
      actionCooldown = 10;
      actionRerun = 1;
    }
    volatile SumoF32 strikePhaseSquared = (SumoF32)(strikePhase * strikePhase);
    SumoF64 strikeRemainWide = 1.0 - strikePhase;
    volatile SumoF32 strikeRemain = (SumoF32)strikeRemainWide;
    poseLift = (SumoF32)(strikeRemainWide * strikePhase * g_gameProjectileSpin +
                         poseLift);
    armExtend[strikeSide] = (SumoF32)(strikePhase * g_gameCameraHeightScale +
                                      g_gameManPoseImpulseGain);
    armCurl[strikeSide] =
        (SumoF32)((1.0 - strikePhaseSquared) * 2.700000047683716f);
    armRaise[strikeSide] = g_boxWaterSurfaceOffset;
    Vector3 drop;
    drop.x = 0.0f;
    drop.y = -2.0f;
    drop.z = 0.0f;
    Vector3 dropCopy = drop;
    Vector3 strikeTarget = opponent->bodyParts[2]->position + dropCopy;
    handTargetWorld[strikeSide] = strikeTarget;
    if (actionCooldown > 200) {
      SumoS32 offSide = 1 - strikeSide;
      handTargetWorld[offSide] = strikeTarget;
      armExtend[offSide] =
          (SumoF32)((SumoF64)strikeRemain * g_gameCameraHeightScale +
                    g_gameManPoseImpulseGain);
      armCurl[offSide] =
          (SumoF32)((SumoF64)strikePhaseSquared * 2.700000047683716f);
      armRaise[offSide] = g_boxWaterSurfaceOffset;
    }
    ++actionTick;
    goto actionRerunCheck;
  }
actionIdle:
  if (inputMask & 0x10) {
    actionTick = 0;
    actionMode = 1;
  }
  if (!(inputMask & 0x20))
    goto actionUpdateDone;
  {
    actionTick = 0;
    actionMode = 2;
    actionSide = 1;
    Vector3 handDelta = bodyParts[11]->position - bodyParts[14]->position;
    SumoF64 handDot = (SumoF64)lateralAxis.y * handDelta.y +
                      (SumoF64)lateralAxis.z * handDelta.z +
                      (SumoF64)lateralAxis.x * handDelta.x;
    if (handDot < g_vectorZero)
      actionSide = 0;
    if (actionCooldown <= 0)
      goto actionUpdateDone;
    actionCooldown = 1000;
  }
actionRerunCheck:
  if (actionRerun != 0)
    goto actionMachine;
  goto actionUpdateDone;
actionReach: {
  primaryPose.joints[8].maximumCorrection = 0.14000000059604645f;
  primaryPose.joints[9].maximumCorrection = 0.14000000059604645f;
  primaryPose.joints[11].maximumCorrection = 0.14000000059604645f;
  primaryPose.joints[12].maximumCorrection = 0.14000000059604645f;
  footTurnBlend = 0.5f;
  SumoF32 reachPull = -1.2999999523162842f;
  Vector3 toward = opponent->bodyParts[1]->position - bodyParts[1]->position;
  toward.y = 0.0f;
  toward.Normalize();
  (void)toward;
  SumoS32 touchTick = g_screenTintLevel - 10;
  if (bodyParts[14]->unknownD4 > touchTick)
    reachPull = -2.0f;
  if (bodyParts[11]->unknownD4 > touchTick)
    reachPull = (SumoF32)((SumoF64)reachPull - g_gameManPoseImpulseGain);
  Vector3 pull = lateralAxis.Scale(reachPull);
  comPosition.x = comPosition.x + pull.x;
  comPosition.y = comPosition.y + pull.y;
  comPosition.z = comPosition.z + pull.z;
  SumoS32 reachTick = actionTick;
  SumoF64 reachPhase = (SumoF64)(reachTick - 8) * 0.03333333507180214f;
  if (reachTick < 8)
    reachPhase = 0.0;
  if (reachTick > 38) {
    reachPhase = 1.0;
    if (reachTick > 43) {
      actionMode = 0;
      actionTick = 0;
    }
  }
  SumoF64 reachSquaredWide = reachPhase * reachPhase;
  volatile SumoF32 reachSquared = (SumoF32)reachSquaredWide;
  poseLift = (SumoF32)(reachSquaredWide * g_inertiaRadiusScale + poseLift);
  volatile SumoF32 extendAmount =
      (SumoF32)(reachPhase * g_gameCameraHeightScale +
                g_gameManPoseImpulseGain);
  SumoF64 curlWide = 1.0 - reachSquared;
  volatile SumoF32 curlAmount = (SumoF32)(2.700000047683716f * curlWide);
  SumoF32 dragScale = -4.0f;
  Vector3 lift;
  lift.x = 0.0f;
  lift.y = (SumoF32)(g_gameTwo - curlWide * g_gameCameraMinimumDistanceScale);
  lift.z = 0.0f;
  Vector3 liftCopy = lift;
  for (SumoS32 reachSide = 0; reachSide < 2; ++reachSide) {
    armExtend[reachSide] = extendAmount;
    armCurl[reachSide] = curlAmount;
    armRaise[reachSide] = g_boxWaterDiagonalScale;
    Vector3 drag = motionVector.Scale(dragScale);
    Vector3 liftTarget = opponent->bodyParts[1]->position + liftCopy;
    Vector3 combined = liftTarget + drag;
    handTargetWorld[reachSide] = combined;
  }
  ++actionTick;
}
actionUpdateDone:
  --actionCooldown;
  if (actionMode != 3) {
    Vector3 anchor;
    anchor.x = 3.5f;
    anchor.y = 2.4000000953674316f;
    anchor.z = 1.0f;
    Vector3 anchorCopy = anchor;
    GameBox *chest = bodyParts[1];
    Vector3 rotated = anchorCopy.Transform(chest->orientation);
    Vector3 shoulderWorld = chest->position + rotated;
    Vector3 reachDelta = handTargetWorld[0] - shoulderWorld;
    Vector3 localDir = chest->orientation.Transform(reachDelta);
    armAimLocal[0] = localDir;
    if (armAimLocal[0].z < g_vectorZero)
      armAimLocal[0].z = 0.0f;
    armAimLocal[0].Normalize();
    anchor.x = -3.5f;
    anchor.y = 2.4000000953674316f;
    anchor.z = 1.0f;
    anchorCopy = anchor;
    chest = bodyParts[1];
    rotated = anchorCopy.Transform(chest->orientation);
    shoulderWorld = chest->position + rotated;
    reachDelta = handTargetWorld[1] - shoulderWorld;
    localDir = chest->orientation.Transform(reachDelta);
    armAimLocal[1] = localDir;
    if (armAimLocal[1].z < g_vectorZero)
      armAimLocal[1].z = 0.0f;
    armAimLocal[1].Normalize();
  }

  {
    SumoF32 decayRate = 0.10000000149011612f;
    Vector3 decay = locomotionForce.Scale(decayRate);
    comVelocity.x = comVelocity.x - decay.x;
    comVelocity.y = comVelocity.y - decay.y;
    comVelocity.z = comVelocity.z - decay.z;
    locomotionForce.x = locomotionForce.x * 0.9599999785423279f;
    locomotionForce.y = locomotionForce.y * 0.9599999785423279f;
    locomotionForce.z = locomotionForce.z * 0.9599999785423279f;
    Vector3 markerPosition = CalculateCenterOfMassPosition();
    markerPosition.y = 5.0f;
    RenderGameCrossMarker(&markerPosition, (void *)0xff0000);
    stanceBlendCopy = stanceBlend;
    Vector3 heel;
    heel.x = 0.0f;
    heel.y = 0.0f;
    heel.z = -0.4000000059604645f;
    Vector3 heelCopy = heel;
    GameBoxJoint *ankleLeft = joints[4];
    GameBox *footBoxLeft = ankleLeft->boxes[0];
    Vector3 heelWorld = heelCopy.Transform(footBoxLeft->orientation);
    footContactPoint[0] = footBoxLeft->position + heelWorld;
    heel.x = 0.0f;
    heel.y = 0.0f;
    heel.z = -0.4000000059604645f;
    heelCopy = heel;
    GameBoxJoint *ankleRight = joints[7];
    GameBox *footBoxRight = ankleRight->boxes[0];
    heelWorld = heelCopy.Transform(footBoxRight->orientation);
    footContactPoint[1] = footBoxRight->position + heelWorld;
    volatile SumoF32 inverseBlendPin = (SumoF32)(1.0 - stanceBlendCopy);
    SumoF32 inverseBlend = inverseBlendPin;
    Vector3 instep;
    instep.x = 0.0f;
    instep.y = g_gameBoxYScale;
    instep.z = g_wavyTextTimeScale;
    Vector3 instepA = instep;
    Vector3 instepB = instep;
    footBoxRight = joints[7]->boxes[0];
    Vector3 upRight = instepA.Transform(footBoxRight->orientation);
    Vector3 pointRight = footBoxRight->position + upRight;
    Vector3 weightedRight = pointRight.Scale(inverseBlend);
    footBoxLeft = ankleLeft->boxes[0];
    Vector3 upLeft = instepB.Transform(footBoxLeft->orientation);
    Vector3 pointLeft = footBoxLeft->position + upLeft;
    Vector3 weightedLeft = pointLeft.Scale(stanceBlendCopy);
    supportPoint = weightedLeft + weightedRight;
    markerPosition = supportPoint;
    markerPosition.y = 5.0f;
    RenderGameCrossMarker(&markerPosition, (void *)0xffff00);
  }

  {
    SumoF64 sideOffset = (SumoF64)supportSide - g_randomHalf;
    supportSign = (SumoF32)(sideOffset + sideOffset);
    SumoF64 forceDot = (SumoF64)lateralAxis.y * locomotionForce.y +
                       (SumoF64)lateralAxis.z * locomotionForce.z +
                       (SumoF64)lateralAxis.x * locomotionForce.x;
    poseGain = (SumoF32)((SumoF64)poseGain - forceDot * 0.15000000596046448f);
    balanceTurn = 0.0f;
    GameBox *head = bodyParts[2];
    if ((SumoF64)supportPoint.y + 9.300000190734863f > head->position.y) {
      SumoS32 postureNow = postureState;
      if (postureNow != 12 && postureNow != 13 && postureNow != 14 &&
          postureNow != 3) {
        postureState = 3;
        if (g_nextGameMan > g_gameMen) {
          for (GameMan *man = g_gameMen; man < g_nextGameMan; ++man) {
            if (man == this)
              continue;
            GameBox *manFootRight = man->bodyParts[6];
            GameBox *manFootLeft = man->bodyParts[3];
            GameBox *manHead = man->bodyParts[2];
            SumoF64 footLevel =
                ((SumoF64)manFootRight->position.y + manFootLeft->position.y) *
                    g_randomHalf +
                3.0f;
            if (!(footLevel < manHead->position.y)) {
              if (g_gameIsRunning == 0)
                continue;
              if (!((SumoF64)g_waterBaseHeight - g_gameOne >
                    manHead->position.y))
                continue;
            }
            if (g_levelLoadState[4] != 2 && g_gameIsRunning == 0)
              continue;
            SumoS32 manActive = man->active;
            if (manActive != 5 && manActive != 7 && g_gameIsRunning == 0)
              continue;
            if (man->motionVector.LengthSquared() < 1.959999918937683f)
              SetGameManAudioState(man, audioChannel);
          }
        }
      }
    }
  }
  if ((SumoF64)g_waterBaseHeight + g_boxWaterDiagonalScale >
      bodyParts[0]->position.y)
    postureState = 14;

  switch (postureState) {
  case 0: {
    stanceBlend = 0.5f;
    if (g_gameKeyDown[3] != 0)
      stanceBlend = 1.0f;
    SumoF32 heightNow = standingHeight;
    ++postureTick;
    firstFootTarget.y = heightNow;
    secondFootTarget.y = heightNow;
    SumoF32 nineteen = 19.0f;
    Vector3 drift19 = comVelocity.Scale(nineteen);
    Vector3 predicted19 = comPosition + drift19;
    Vector3 stepLean = supportPoint - predicted19;
    SumoF32 three = 3.0f;
    Vector3 lever = locomotionForce.Scale(three);
    stepLean.x = stepLean.x - lever.x;
    SumoF32 leverHeight = -lever.y;
    stepLean.z = stepLean.z - lever.z;
    SumoS32 tintNow = g_screenTintLevel;
    if (tintNow <= 250) {
      if (g_gameIsRunning == 0)
        goto raiseBalanceFlag;
      if (tintNow <= 100)
        goto raiseBalanceFlag;
    }
    SumoS32 contactTick = tintNow - 30;
    if (!(bodyParts[3]->unknownD4 > contactTick)) {
      if (bodyParts[6]->unknownD4 <= contactTick)
        goto raiseBalanceFlag;
    }
    SumoF32 leanLimit = g_gameCameraInputDamping;
    if (g_levelLoadState[4] == 2)
      leanLimit = g_boxWaterDiagonalScale;
    if ((SumoF64)leanLimit * leanLimit >= (SumoF64)leverHeight * leverHeight +
                                              (SumoF64)stepLean.x * stepLean.x +
                                              (SumoF64)stepLean.z * stepLean.z)
      goto checkReplant;
    if (poseOverride != 0)
      goto checkReplant;
    {
      SumoF32 ten = 10.0f;
      Vector3 drift10 = comVelocity.Scale(ten);
      Vector3 predicted10 = comPosition + drift10;
      Vector3 lean10 = supportPoint - predicted10;
      stepLean = lean10;
      SumoF64 leanDistSquared =
          (SumoF64)stepLean.x * stepLean.x + (SumoF64)stepLean.z * stepLean.z;
      volatile SumoF32 leanDistSquaredRounded = (SumoF32)leanDistSquared;
      SumoF64 scaledLength = sqrt(leanDistSquared) * g_boxWaterDiagonalScale;
      volatile SumoF32 stepScale = (SumoF32)scaledLength;
      if (!(scaledLength >= g_boxWaterBuoyancyScale))
        stepScale = 1.399999976158142f;
      postureTick = 0;
      postureState = 8;
      volatile SumoF32 leanDistanceRounded =
          (SumoF32)sqrt((SumoF64)leanDistSquaredRounded);
      SumoF64 leanDistanceWide = sqrt((SumoF64)leanDistSquaredRounded);
      SumoF32 forwardPieceX = forwardAxis.x * stepLean.x;
      volatile SumoF32 forwardPieceY =
          (SumoF32)((SumoF64)forwardAxis.y * g_vectorZero);
      SumoF32 forwardPieceZ = forwardAxis.z * stepLean.z;
      SumoF64 sideDot = (SumoF64)stepLean.x * lateralAxis.x +
                        (SumoF64)stepLean.z * lateralAxis.z +
                        (SumoF64)lateralAxis.y * g_vectorZero;
      volatile SumoF32 stepZ =
          (SumoF32)(sideDot * -((SumoF64)stepScale / leanDistanceRounded));
      SumoF64 forwardSum =
          (SumoF64)forwardPieceY + forwardPieceZ + forwardPieceX;
      volatile SumoF32 stepX = (SumoF32)((SumoF64)stepScale / leanDistanceWide *
                                         -0.6000000238418579f * forwardSum);
      Vector3 stepBuild = MakeVector3(stepX, 0.0f, stepZ);
      Vector3 stepCopy = stepBuild;
      stepDirection = stepCopy;
      stepMagnitude = (SumoF32)(sqrt((SumoF64)stepDirection.LengthSquared()) *
                                    g_gameCameraAimDamping +
                                g_randomHalf);
      Vector3 footDelta = secondFootTarget - firstFootTarget;
      SumoF64 stepDot = (SumoF64)footDelta.z * stepDirection.z +
                        (SumoF64)footDelta.y * stepDirection.y +
                        (SumoF64)footDelta.x * stepDirection.x;
      SumoF64 sideBias = ((SumoF64)supportSide - g_randomHalf) * g_vectorZero +
                         forwardPieceY + forwardPieceZ + forwardPieceX;
      supportSide = sideBias > stepDot ? 1 : 0;
      if (supportSide != 0) {
        if (!((SumoF64)firstFootTarget.x - stepDirection.x >= 0.25f))
          stepDirection.x = firstFootTarget.x - 0.25f;
      } else {
        if (!((SumoF64)firstFootTarget.x + stepDirection.x >= 0.25f))
          stepDirection.x = (SumoF32)(0.25f - (SumoF64)firstFootTarget.x);
      }
      SumoF64 stepBias =
          ((SumoF64)firstFootTarget.x - g_randomHalf) * 0.20000000298023224f -
          0.1599999964237213f;
      if (supportSide != 0)
        stepDirection.x = (SumoF32)(stepBias + stepDirection.x);
      else
        stepDirection.x = (SumoF32)((SumoF64)stepDirection.x - stepBias);
    }
  checkReplant: {
    SumoS32 tickNow = postureTick;
    if (tickNow != 90) {
      if (tickNow > 10) {
        if (firstFootTarget.x < 0.25f)
          goto doReplant;
      }
      if (footHomeFlag == 0)
        goto raiseBalanceFlag;
    }
  doReplant:
    Vector3 home;
    home.x = 1.100000023841858f;
    home.y = standingHeight;
    home.z = 0.0f;
    Vector3 homeCopy = home;
    Vector3 replant = homeCopy - firstFootTarget;
    stepDirection = replant;
    if (!(stepDirection.LengthSquared() > 0.1600000113248825f)) {
      if (footHomeFlag == 0)
        goto raiseBalanceFlag;
    }
    supportSide = 0;
    postureState = 8;
    stepMagnitude = (SumoF32)(sqrt((SumoF64)stepDirection.LengthSquared()) *
                                  g_gameCameraHeightScale +
                              g_randomHalf);
    if (stepDirection.z < g_gameProjectileSpin) {
      supportSide = 1;
      stepDirection.x = stepDirection.x * g_gameBoxYScale;
      stepDirection.y = stepDirection.y * g_gameBoxYScale;
      stepDirection.z = stepDirection.z * g_gameBoxYScale;
    }
  }
    goto raiseBalanceFlag;
  }
  case 2: {
    GameBox *pelvis = bodyParts[0];
    if ((SumoF64)supportSide > stanceBlend)
      stanceBlend = stanceBlend + 0.009999999776482582f;
    if ((SumoF64)supportSide < stanceBlend)
      stanceBlend = stanceBlend - 0.009999999776482582f;
    SumoF32 thirty = 30.0f;
    Vector3 drift30 = comVelocity.Scale(thirty);
    Vector3 predicted30 = comPosition + drift30;
    Vector3 glideLean = supportPoint - predicted30;
    --postureTick;
    glideLean.y = 0.0f;
    SumoS32 glideTick = postureTick;
    if (!(stanceBlend < g_gameProjectileSpin)) {
      if (stanceBlend <= g_gameCameraInputDamping)
        goto glideChase;
    }
    if ((SumoF64)glideLean.x * glideLean.x +
            (SumoF64)glideLean.z * glideLean.z <
        1.6899998188018799f)
      goto glideMaybeStep;
    {
      Vector3 localLean = pelvis->orientation.Transform(glideLean);
      if (localLean.z >= -0.20000000298023224f)
        goto glideResetTick;
    }
  glideMaybeStep:
    if (glideTick > 0)
      goto glideChase;
    postureState = 1;
  glideResetTick:
    postureTick = 0;
  glideChase: {
    Vector3 probe;
    probe.x = 0.0f;
    probe.y = 0.0f;
    probe.z = 0.009999999776482582f;
    Vector3 probeCopy = probe;
    Vector3 probeWorld = probeCopy.Transform(pelvis->orientation);
    SumoF32 chaseRate = 0.05999999865889549f;
    probeWorld.y = 0.0f;
    Vector3 chaseDelta = probeWorld - locomotionOffset;
    Vector3 chaseStep = chaseDelta.Scale(chaseRate);
    locomotionOffset += chaseStep;
    comVelocity.x = comVelocity.x - locomotionOffset.x;
    comVelocity.y = comVelocity.y - locomotionOffset.y;
    comVelocity.z = comVelocity.z - locomotionOffset.z;
  }
    goto tailJoin;
  }
  case 1: {
    SumoF64 swingPhaseWide = (SumoF64)postureTick * 0.09239978343248367f;
    volatile SumoF32 swingPhase = (SumoF32)swingPhaseWide;
    if (swingPhaseWide > g_parserPi) {
      supportSide ^= 1;
      postureTick = 0;
      postureState = 2;
    }
    SumoF32 probeSign;
    if (supportSide == 0) {
      stanceBlend = (SumoF32)((SumoF64)postureTick * 0.01764705963432789f);
      probeSign = 1.0f;
    } else {
      stanceBlend =
          (SumoF32)(1.0 - (SumoF64)postureTick * 0.01764705963432789f);
      probeSign = g_gameBoxYScale;
    }
    Vector3 probe;
    probe.x = (SumoF32)((SumoF64)0.029999999329447746f * probeSign);
    probe.y = 0.0f;
    probe.z = 0.029999999329447746f;
    Vector3 probeCopy = probe;
    Vector3 probeWorld = probeCopy.Transform(bodyParts[0]->orientation);
    SumoF32 chaseRate = 0.05999999865889549f;
    probeWorld.y = 0.0f;
    Vector3 chaseDelta = probeWorld - locomotionOffset;
    Vector3 chaseStep = chaseDelta.Scale(chaseRate);
    locomotionOffset += chaseStep;
    comVelocity.x = comVelocity.x - locomotionOffset.x;
    comVelocity.y = comVelocity.y - locomotionOffset.y;
    comVelocity.z = comVelocity.z - locomotionOffset.z;
    SumoS32 side = supportSide;
    footTargets[side].z = footTargets[side].z + 0.05882352963089943f;
    SumoF32 doublePhase = swingPhase + swingPhase;
    footTargets[side].y =
        (SumoF32)((1.0 - cos((SumoF64)doublePhase)) * g_wavyTextPhaseScale -
                  8.5f);
    footTargets[side ^ 1].y =
        (SumoF32)(-8.5f -
                  (1.0 - cos((SumoF64)doublePhase)) * g_gameCameraHeightScale);
    footTargets[side ^ 1].z = footTargets[side ^ 1].z - 0.05882352963089943f;
    goto tailTick;
  }
  case 3: {
    Vector3 zero;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    for (SumoS32 joint = 0; joint < 14; ++joint) {
      primaryPose.joints[joint].maximumCorrection = 0.0f;
      primaryPose.joints[joint].firstDirection = zero;
      primaryPose.joints[joint].secondDirection = zero;
    }
    if (postureTick >= 8000 || CalculateKineticEnergy() < g_gameTwo) {
      postureTick = 0;
      postureState = 12;
    }
    SumoS32 restTick = g_screenTintLevel - 100;
    if (bodyParts[1]->unknownD8 < restTick &&
        bodyParts[2]->unknownD8 < restTick) {
      volatile SumoF32 propLimit = (SumoF32)((SumoF64)supportPoint.y + 3.0f);
      for (SumoS32 armSide = 0; armSide < 2; ++armSide) {
        GameBox *hand = bodyParts[11 + 3 * armSide];
        if (hand->position.y < propLimit) {
          primaryPose.joints[8 + 3 * armSide].maximumCorrection =
              0.009999999776482582f;
          primaryPose.joints[9 + 3 * armSide].maximumCorrection =
              0.009999999776482582f;
          Vector3 up;
          up.x = 0.0f;
          up.y = 1.0f;
          up.z = 0.0f;
          Vector3 upCopy = up;
          Vector3 propDirection = bodyParts[1]->orientation.Transform(upCopy);
          primaryPose.joints[8 + 3 * armSide].firstDirection = propDirection;
          primaryPose.joints[9 + 3 * armSide].firstDirection =
              secondaryPose.joints[9 + 3 * armSide].firstDirection;
        }
      }
    }
    ++postureTick;
    return;
  }
  case 4: {
    ++postureTick;
    SumoF64 crouchWide = (SumoF64)postureTick * 0.03999999910593033f;
    poseCrouch = (SumoF32)crouchWide;
    if (crouchWide > g_gameProjectileHalfSize) {
      postureTick = 0;
      postureState = 5;
    }
    goto lateralPush;
  }
  case 5: {
    ++postureTick;
    Vector3 push;
    push.x = (SumoF32)((SumoF64)supportSign * 0.20000000298023224f);
    push.y = 0.0f;
    push.z = 0.0f;
    Vector3 pushCopy = push;
    poseCrouch = 1.2f;
    Vector3 pushWorld = pushCopy.Transform(bodyParts[0]->orientation);
    comVelocity.x = comVelocity.x - pushWorld.x;
    comVelocity.z = comVelocity.z - pushWorld.z;
    if (postureTick <= 10)
      goto tailJoin;
    postureTick = 0;
    postureState = 6;
    goto tailJoin;
  }
  case 6: {
    {
      ++postureTick;
      SumoF64 swingTick = (SumoF64)postureTick;
      SumoS32 side = supportSide;
      poseCrouch = (SumoF32)(g_gameProjectileHalfSize -
                             swingTick * swingTick * 0.02027999982237816f);
      footTargets[side].y = -8.0f;
      if (poseCrouch < g_vectorZero) {
        postureState = 0;
        postureTick = 0;
        footTargets[side].y = -8.699999809265137f;
      }
    }
  lateralPush: {
    Vector3 push;
    push.x = (SumoF32)((SumoF64)supportSign * 0.20000000298023224f);
    push.y = 0.0f;
    push.z = 0.0f;
    Vector3 pushCopy = push;
    Vector3 pushWorld = pushCopy.Transform(bodyParts[0]->orientation);
    comVelocity.x = comVelocity.x - pushWorld.x;
    comVelocity.z = comVelocity.z - pushWorld.z;
  }
    goto tailJoin;
  }
  case 7: {
    if (postureTick < 120)
      ++postureTick;
    else
      postureTick = 0;
    Vector3 push;
    push.x = 0.05000000074505806f;
    push.y = 0.0f;
    push.z = 0.0f;
    Vector3 pushCopy = push;
    Vector3 pushWorld = pushCopy.Transform(bodyParts[0]->orientation);
    comVelocity.x = comVelocity.x - pushWorld.x;
    comVelocity.z = comVelocity.z - pushWorld.z;
    SumoF32 half = 0.5f;
    SumoF32 forty = 40.0f;
    SumoS32 side = supportSide;
    Vector3 contactSum = footContactPoint[side] + footContactPoint[side ^ 1];
    Vector3 contactMid = contactSum.Scale(half);
    (void)contactMid;
    Vector3 drift40 = comVelocity.Scale(forty);
    Vector3 predicted40 = comPosition + drift40;
    (void)predicted40;
    footTargets[side].y =
        (SumoF32)(sin((SumoF64)postureTick * 0.02617993950843811f) -
                  8.699999809265137f);
    goto tailJoin;
  }
  case 8: {
    SumoS32 side = supportSide;
    footTargets[side].y =
        (SumoF32)(standingHeight - (SumoF64)postureTick * 0.05000000074505806f);
    ++postureTick;
    if (postureTick >= 6) {
      postureTick = 0;
      postureState = 9;
    }
    SumoF32 zeroScale = 0.0f;
    SumoF32 liftScale = 0.05000000074505806f;
    footTargets[side] += stepDirection.Scale(liftScale).Scale(zeroScale);
    zeroScale = 0.0f;
    liftScale = 0.05000000074505806f;
    ((GameBoxPoint *)&footTargets[side ^ 1])
        ->SubtractOffset(stepDirection.Scale(liftScale).Scale(zeroScale));
    volatile SumoF32 tickScalePin =
        (SumoF32)((SumoF64)postureTick * 0.04999999701976776f);
    SumoF32 tickScale = tickScalePin;
    Vector3 lateralShift = lateralAxis.Scale(stepDirection.z).Scale(tickScale);
    supportPoint.x = supportPoint.x - lateralShift.x;
    supportPoint.y = supportPoint.y - lateralShift.y;
    supportPoint.z = supportPoint.z - lateralShift.z;
    SumoF32 nudgeScale = -0.02500000037252903f;
    Vector3 nudge = lateralAxis.Scale(stepDirection.z).Scale(nudgeScale);
    comVelocity.x = comVelocity.x + nudge.x;
    comVelocity.y = comVelocity.y + nudge.y;
    comVelocity.z = comVelocity.z + nudge.z;
    if (g_levelLoadState[4] == 1)
      goto raiseBalanceFlag;
    goto tailJoin;
  }
  case 9: {
    SumoF64 walkX = (SumoF64)postureTick * 0.05000000074505806f;
    volatile SumoF32 swingEnvelopePin = (SumoF32)((1.0 - walkX) * walkX * 6.0f);
    SumoF32 swingEnvelope = swingEnvelopePin;
    SumoF64 walkSquared = walkX * walkX;
    SumoF64 walkSmooth = 3.0f * walkSquared;
    SumoF64 walkCubed = walkSquared * walkX;
    walkCubed += walkCubed;
    volatile SumoF32 walkCurve = (SumoF32)(walkSmooth - walkCubed);
    SumoF64 curvePiWide = (SumoF64)walkCurve * g_parserPi;
    volatile SumoF32 curvePi = (SumoF32)curvePiWide;
    SumoS32 side = supportSide;
    footTargets[side].y = (SumoF32)(sin(curvePiWide) * stepMagnitude +
                                    standingHeight - g_gameCameraHeightScale +
                                    (SumoF64)curvePi * 0.09549296647310257f);
    side = supportSide;
    footTargets[side ^ 1].y =
        (SumoF32)(standingHeight -
                  sin((SumoF64)curvePi) * stepMagnitude * 0.20000000298023224f);
    SumoF32 stepRate = 0.05000000074505806f;
    SumoF32 unitScale = 1.0f;
    footTargets[side] +=
        stepDirection.Scale(stepRate).Scale(unitScale).Scale(swingEnvelope);
    unitScale = 1.0f;
    stepRate = 0.05000000074505806f;
    ((GameBoxPoint *)&footTargets[side ^ 1])
        ->SubtractOffset(stepDirection.Scale(stepRate).Scale(unitScale).Scale(
            swingEnvelope));
    ++postureTick;
    if (postureTick >= 20) {
      supportSide ^= 1;
      postureState = 0;
      postureTick = 0;
      SumoS32 newSide = supportSide;
      footTargets[newSide].y = standingHeight;
      footTargets[newSide ^ 1].y = standingHeight;
    }
    volatile SumoF32 plantPullPin =
        (SumoF32)(((SumoF64)postureTick + 6.0f) * 0.03846153989434242f -
                  walkCurve);
    SumoF32 plantPull = plantPullPin;
    SumoF32 plantScale = 1.2999999523162842f;
    Vector3 plantShift =
        lateralAxis.Scale(stepDirection.z).Scale(plantPull).Scale(plantScale);
    supportPoint.x = supportPoint.x - plantShift.x;
    supportPoint.y = supportPoint.y - plantShift.y;
    supportPoint.z = supportPoint.z - plantShift.z;
    SumoF32 nudgeScale = -0.02500000037252903f;
    Vector3 nudge = lateralAxis.Scale(stepDirection.z).Scale(nudgeScale);
    comVelocity.x = comVelocity.x + nudge.x;
    comVelocity.y = comVelocity.y + nudge.y;
    comVelocity.z = comVelocity.z + nudge.z;
    footTurnBlend = 0.0f;
    goto tailJoin;
  }
  case 10: {
    stanceBlend = 0.5f;
    volatile SumoF32 lungePhase =
        (SumoF32)((SumoF64)postureTick * 0.03333333507180214f);
    SumoF64 lungePiWide = (SumoF64)lungePhase * g_parserPi;
    volatile SumoF32 lungePi = (SumoF32)lungePiWide;
    SumoS32 side = supportSide;
    SumoF64 lungeSin = sin(lungePiWide);
    footTargets[side].y =
        (SumoF32)(lungeSin + lungeSin + standingHeight + lungePhase);
    footTargets[side].x = footTargets[side].x + 0.10999999940395355f;
    footTargets[side ^ 1].x = footTargets[side ^ 1].x - 0.10999999940395355f;
    volatile SumoF32 lungeScalePin = (SumoF32)sin((SumoF64)lungePi);
    SumoF32 lungeScale = lungeScalePin;
    SumoF32 pushScale = -0.05000000074505806f;
    Vector3 lungePush = forwardAxis.Scale(lungeScale).Scale(pushScale);
    comVelocity.x = comVelocity.x + lungePush.x;
    comVelocity.y = comVelocity.y + lungePush.y;
    comVelocity.z = comVelocity.z + lungePush.z;
    ++postureTick;
    if (lungePhase > g_gameOne) {
      postureTick = 0;
      postureState = 11;
    }
    goto tailJoin;
  }
  case 11: {
    stanceBlend = 0.5f;
    SumoS32 side = supportSide;
    SumoF64 recoverPhase = (SumoF64)postureTick * g_gameProjectileSpin;
    footTargets[side].y = (SumoF32)((1.0 - recoverPhase) + standingHeight);
    footTargets[side].x = footTargets[side].x - 0.32999998331069946f;
    footTargets[side ^ 1].x = footTargets[side ^ 1].x + 0.32999998331069946f;
    if (recoverPhase > g_gameOne)
      postureState = 0;
    goto tailTick;
  }
  case 12: {
    SumoS32 fallTick;
    SumoF32 elbowLift;
    SumoF32 shoulderLift;
    SumoF32 shoulderTwist;
    SumoF32 kneeDrive;
    SumoF32 hipDrive;
    SumoF32 lateralDrift;
    SumoF32 newDrive;
    SumoU8 giveUp;
    {
      Vector3 zero;
      zero.x = 0.0f;
      zero.y = 0.0f;
      zero.z = 0.0f;
      locomotionForce = zero;
      SumoF64 maxCorrection = (SumoF64)postureTick * 0.0002500000118743628f;
      if (maxCorrection > 0.05000000074505806f)
        maxCorrection = 0.05000000074505806f;
      for (SumoS32 joint = 0; joint < 14; ++joint) {
        primaryPose.joints[joint] = secondaryPose.joints[joint];
        primaryPose.joints[joint].maximumCorrection = (SumoF32)maxCorrection;
      }
      fallTick = postureTick;
      SumoF64 elbowValue =
          (SumoF64)fallTick * 0.017999999225139618f - g_randomHalf;
      elbowLift = (SumoF32)elbowValue;
      if (elbowValue < g_vectorZero) {
        elbowLift = 0.0f;
        elbowValue = 0.0;
      }
      if (elbowValue > g_gameTwo)
        elbowLift = 2.0f;
      shoulderLift = 1.0f;
      giveUp = 0;
      shoulderTwist = 0.0f;
      kneeDrive = 0.0f;
      hipDrive = 0.0f;
      if (fallTick == 100) {
        Vector3 axis;
        axis.x = 0.0f;
        axis.y = 0.0f;
        axis.z = 1.0f;
        Vector3 axisCopy = axis;
        Vector3 pelvisForward = axisCopy.Transform(bodyParts[0]->orientation);
        if (pelvisForward.y > g_vectorZero) {
          recoverySide ^= 1;
          postureTick = 0;
          recoveryAngle = 0.0f;
          postureState = 13;
        }
      }
      fallTick = postureTick;
      if (fallTick <= 100)
        goto case12PoseTail;
      {
        Vector3 axis;
        axis.x = 1.0f;
        axis.y = 0.0f;
        axis.z = 0.0f;
        Vector3 axisCopyA = axis;
        Vector3 axisCopyB = axis;
        Vector3 uprightA = axisCopyB.Transform(bodyParts[0]->orientation);
        Vector3 uprightB = axisCopyA.Transform(bodyParts[0]->orientation);
        if ((SumoF64)uprightA.y * uprightB.y > 0.25f) {
          if (fallTick > 300)
            giveUp = 1;
        }
      }
      SumoF64 fallWide = (SumoF64)fallTick;
      SumoF64 nearRamp =
          (fallWide - g_gameLevelArenaExtent) * 0.009999999776482582f;
      if (nearRamp > g_gameOne)
        nearRamp = 1.0;
      SumoF64 nearSquared = nearRamp * nearRamp;
      SumoF64 nearSmooth = 3.0f * nearSquared;
      SumoF64 nearCubed = nearSquared * nearRamp;
      nearCubed += nearCubed;
      SumoF64 nearDrive = (nearSmooth - nearCubed) * g_gameWallCenterSegment;
      hipDrive = (SumoF32)nearDrive;
      kneeDrive = (SumoF32)nearDrive;
      if (fallTick <= 170)
        goto case12GiveUpCheck;
      SumoF64 deepRamp = (fallWide - 170.0f) * 0.006666666828095913f;
      if (deepRamp > g_gameOne)
        deepRamp = 1.0;
      SumoF64 deepSquared = deepRamp * deepRamp;
      SumoF64 deepSmooth = 3.0f * deepSquared;
      SumoF64 deepCubed = deepSquared * deepRamp;
      deepCubed += deepCubed;
      SumoF64 deepCurve = deepSmooth - deepCubed;
      elbowLift = (SumoF32)(g_gameTwo - 1.7999999523162842f * deepCurve);
      shoulderLift = (SumoF32)(g_gameOne - deepCurve * g_gameWallCenterSegment);
      if (fallTick <= 300) {
        recoveryDrive = kneeDrive;
        recoveryAngle = hipDrive;
        goto case12GiveUpCheck;
      }
      SumoF64 postFallWide = (fallWide - 300.0f) * 0.009999999776482582f;
      volatile SumoF32 postFall = (SumoF32)postFallWide;
      if (postFallWide > g_gameOne)
        postFall = 1.0f;
      SumoF32 chase200 = 200.0f;
      Vector3 overshoot200 =
          (comPosition + comVelocity.Scale(chase200)) - supportPoint;
      (void)overshoot200;
      SumoF32 chase20 = 20.0f;
      Vector3 overshoot20 =
          (comPosition + comVelocity.Scale(chase20)) - supportPoint;
      lateralDrift = (SumoF32)((SumoF64)lateralAxis.y * overshoot20.y +
                               (SumoF64)lateralAxis.z * overshoot20.z +
                               (SumoF64)lateralAxis.x * overshoot20.x);
      SumoF64 decay = exp((SumoF64)postFall * g_gameAiLateralRecoveryThreshold);
      hipDrive = recoveryAngle;
      fallTick = postureTick;
      SumoF64 driveWide = 1.0 - decay;
      driveWide = driveWide * recoveryDrive;
      driveWide = driveWide * g_wavyTextTimeScale;
      driveWide = (SumoF64)recoveryDrive - driveWide;
      newDrive = (SumoF32)driveWide;
      recoveryDrive = (SumoF32)driveWide;
      kneeDrive = (SumoF32)driveWide;
      if (fallTick <= 10000)
        goto case12DeadChains;
      {
        SumoF64 lateRamp =
            ((SumoF64)fallTick - 20000.0f) * 0.006666666828095913f;
        if (lateRamp > g_gameOne)
          lateRamp = 1.0;
        SumoF64 lateSquared = lateRamp * lateRamp;
        SumoF64 lateSmooth = 3.0f * lateSquared;
        SumoF64 lateCubed = lateSquared * lateRamp;
        lateCubed += lateCubed;
        SumoF64 lateCurve = lateSmooth - lateCubed;
        SumoS32 staleCutoff = g_screenTintLevel - 300;
        elbowLift =
            (SumoF32)((SumoF64)g_gameCameraInputOffsetScale * lateCurve +
                      elbowLift);
        shoulderLift =
            (SumoF32)((SumoF64)2.700000047683716f * lateCurve + shoulderLift);
        shoulderTwist = (SumoF32)(lateCurve * g_gameWallCenterSegment);
        if (bodyParts[3]->unknownD8 < staleCutoff ||
            bodyParts[6]->unknownD8 < staleCutoff)
          giveUp = 1;
        SumoF64 driveTerm =
            ((SumoF64)lateralDrift - recoveryLateral) * g_gameProjectileSpin;
        driveTerm = driveTerm + (SumoF64)lateralDrift * 0.0020000000949949026f;
        driveTerm = driveTerm - ((SumoF64)0.20000000298023224f - newDrive) *
                                    0.009999999776482582f;
        driveTerm = driveTerm + newDrive;
        volatile SumoF32 driveValue = (SumoF32)driveTerm;
        recoveryDrive = (SumoF32)driveTerm;
        if (driveTerm < g_gameProjectileSpin)
          giveUp = 1;
        if (recoveryAngle > 0.2199999988079071f) {
          SumoF64 damping =
              (SumoF64)g_gameOne /
              ((SumoF64)lateralDrift * lateralDrift * 3.0f + g_gameOne);
          SumoF64 decrement = ((SumoF64)recoveryAngle - 0.05000000074505806f) *
                              damping * lateRamp * lateRamp *
                              0.3499999940395355f;
          if (decrement > 0.05000000074505806f)
            decrement = 0.05000000074505806f;
          recoveryAngle = (SumoF32)((SumoF64)recoveryAngle - decrement);
        } else {
          giveUp = 1;
        }
        if (g_gameWallCenterSegment < recoveryAngle)
          recoveryAngle = g_gameWallCenterSegment;
        kneeDrive = driveValue;
        hipDrive = recoveryAngle;
        goto case12Merge;
      }
    }
  case12DeadChains: {
    SumoF32 chaseBias = g_gameCameraDistanceBias;
    SumoF32 chaseBiasCopy = g_gameCameraDistanceBias;
    Vector3 deadA = (comPosition + comVelocity.Scale(chaseBias)) - supportPoint;
    (void)deadA;
    Vector3 deadB =
        (comPosition + comVelocity.Scale(chaseBiasCopy)) - supportPoint;
    (void)deadB;
  }
  case12Merge: {
    SumoF32 chase20 = 20.0f;
    Vector3 futureCom = comPosition + comVelocity.Scale(chase20);
    Vector3 down;
    down.x = 0.0f;
    down.y = -5.0f;
    down.z = 0.0f;
    Vector3 downCopy = down;
    SumoF32 lateralBias = -0.10000000149011612f;
    Vector3 lateralAdjust = lateralAxis.Scale(lateralBias);
    Vector3 fallDirection =
        ((supportPoint - futureCom) + downCopy) + lateralAdjust;
    fallDirection.Normalize();
    SumoF64 fastForwardCosine = cos(g_waterCorrectionScale);
    if (fallDirection.y < -fastForwardCosine) {
      if (postureTick < 20000)
        postureTick = 20000;
    }
    SumoF64 coneCosine = cos((SumoF64)0.3f);
    if (fallDirection.y > -coneCosine) {
      volatile SumoF32 coneTangent = (SumoF32)tan((SumoF64)0.3f);
      fallDirection.y = (SumoF32)(sqrt(g_gameOne - (SumoF64)fallDirection.y *
                                                       fallDirection.y) *
                                  ((SumoF64)g_gameBoxYScale / coneTangent));
      fallDirection.Normalize();
      if (postureTick > 600)
        giveUp = 1;
    }
    for (SumoS32 ankleSide = 0; ankleSide < 2; ++ankleSide) {
      GameBoxJoint *ankle = joints[4 + 3 * ankleSide];
      Vector3 localFall = ankle->boxes[1]->orientation.Transform(fallDirection);
      SumoF64 ankleCosine = cos(g_textureHalf);
      if (localFall.y > -ankleCosine) {
        volatile SumoF32 ankleTangent = (SumoF32)tan(g_textureHalf);
        localFall.y =
            (SumoF32)(sqrt(g_gameOne - (SumoF64)localFall.y * localFall.y) *
                      ((SumoF64)g_gameBoxYScale / ankleTangent));
        localFall.Normalize();
      }
      primaryPose.joints[4 + 3 * ankleSide].firstDirection = localFall;
    }
    recoveryLateral = lateralDrift;
  }
  case12GiveUpCheck:
    if (giveUp) {
      balanceStrength = 0.0f;
      postureState = 0;
      Vector3 stance;
      stance.x = 0.30000001192092896f;
      stance.y = standingHeight;
      stance.z = 0.0f;
      firstFootTarget = stance;
      SumoF64 headLimit = (SumoF64)supportPoint.y + g_parserMinimumBreakability;
      stance.x = -0.30000001192092896f;
      stance.y = standingHeight;
      stance.z = 0.0f;
      secondFootTarget = stance;
      if (headLimit > bodyParts[2]->position.y)
        postureState = 3;
      postureTick = 0;
      balancePitch = 0.0f;
      stanceBlend = 0.5f;
      balanceRoll = 0.0f;
      balancePitchIntegral = 0.0f;
      balancePitchVelocity = 0.0f;
      balanceRollVelocity = 0.0f;
    }
  case12PoseTail: {
    SumoF32 mirrorSign = 1.0f;
    Vector3 axisY;
    axisY.x = 0.0f;
    axisY.z = 0.0f;
    Vector3 axisZ;
    axisZ.x = 0.0f;
    axisZ.y = 0.0f;
    Vector3 elbowAxis;
    elbowAxis.x = 0.0f;
    elbowAxis.z = 0.0f;
    Vector3 hipAxis;
    hipAxis.x = 0.0f;
    hipAxis.z = 0.0f;
    Vector3 armUnit;
    armUnit.x = 1.0f;
    armUnit.y = 0.0f;
    armUnit.z = 0.0f;
    SumoF32 kneeScale = -kneeDrive;
    Vector3 kneeUnit = armUnit;
    for (SumoS32 mirror = 0; mirror < 2; ++mirror) {
      volatile SumoF32 mirrorY =
          (SumoF32)((SumoF64)mirrorSign * g_gameBoxYScale);
      axisY.y = mirrorY;
      Vector3 shoulderAxis = axisY;
      Vector3 shoulderRotation = shoulderAxis.Scale(shoulderLift);
      primaryPose.joints[8 + 3 * mirror].firstDirection.Rotate(
          shoulderRotation);
      axisZ.z = mirrorSign;
      Vector3 twistAxis = axisZ;
      Vector3 twistRotation = twistAxis.Scale(shoulderTwist);
      primaryPose.joints[8 + 3 * mirror].firstDirection.Rotate(twistRotation);
      elbowAxis.y = mirrorY;
      Vector3 elbowCopy = elbowAxis;
      Vector3 elbowRotation = elbowCopy.Scale(elbowLift);
      primaryPose.joints[9 + 3 * mirror].firstDirection.Rotate(elbowRotation);
      hipAxis.y = (SumoF32)((SumoF64)mirrorSign * -0.30000001192092896f);
      Vector3 hipCopy = hipAxis;
      Vector3 hipScaled = armUnit.Scale(hipDrive);
      Vector3 hipRotation = hipScaled + hipCopy;
      primaryPose.joints[2 + 3 * mirror].firstDirection.Rotate(hipRotation);
      Vector3 kneeRotation = kneeUnit.Scale(kneeScale);
      primaryPose.joints[3 + 3 * mirror].firstDirection.Rotate(kneeRotation);
      mirrorSign = -1.0f;
    }
    goto tailTick;
  }
  }
  case 13: {
    SumoF64 correction = (SumoF64)postureTick * 0.0002500000118743628f;
    if (correction > 0.05000000074505806f)
      correction = 0.05000000074505806f;
    for (SumoS32 joint = 0; joint < 14; ++joint) {
      primaryPose.joints[joint] = secondaryPose.joints[joint];
      primaryPose.joints[joint].maximumCorrection = (SumoF32)correction;
    }
    Vector3 axis;
    axis.x = 0.0f;
    axis.y = 0.0f;
    axis.z = 1.0f;
    Vector3 axisCopy = axis;
    Vector3 rollForward = axisCopy.Transform(bodyParts[0]->orientation);
    if ((SumoF64)rollForward.x * rollForward.x +
            (SumoF64)rollForward.z * rollForward.z >
        0.36000001430511475f) {
      recoveryAngle = recoveryAngle + 0.03999999910593033f;
    } else if (recoveryAngle > g_vectorZero) {
      recoveryAngle = recoveryAngle - 0.07999999821186066f;
    }
    if (recoveryAngle > 4.599999904632568f || postureTick > 600) {
      postureTick = 0;
      postureState = 3;
    }
    volatile SumoF32 rollComplementPin = (SumoF32)(1.0 - recoveryAngle);
    SumoF32 rollComplement = rollComplementPin;
    volatile SumoF32 rollBoostPin =
        (SumoF32)((SumoF64)recoveryAngle * g_gameCameraHeightScale + g_gameOne);
    SumoF32 rollBoost = rollBoostPin;
    SumoF32 rollSign = 1.0f;
    SumoS32 raiseSide = 3;
    SumoS32 otherSide = 0;
    if (recoverySide == 0) {
      raiseSide = 0;
      otherSide = 3;
      rollSign = -1.0f;
    }
    Vector3 swing;
    swing.x = 0.0f;
    swing.y = (SumoF32)((SumoF64)rollSign * g_gameBoxYScale);
    swing.z = 0.0f;
    Vector3 swingCopy = swing;
    SumoF32 negativeOne = -1.0f;
    Vector3 swingFlipped = swingCopy.Scale(negativeOne);
    Vector3 swingRotation = swingFlipped.Scale(rollBoost);
    primaryPose.joints[8 + otherSide].firstDirection.Rotate(swingRotation);
    Vector3 tug = MakeVector3(
        (SumoF32)((SumoF64)rollSign * recoveryAngle * -0.20000000298023224f),
        (SumoF32)((SumoF64)recoveryAngle * g_textureHalf), 0.0f);
    Vector3 *swingDirection = &primaryPose.joints[8 + otherSide].firstDirection;
    swingDirection->x = swingDirection->x + tug.x;
    swingDirection->y = swingDirection->y + tug.y;
    swingDirection->z = swingDirection->z + tug.z;
    swingDirection->Normalize();
    swing.x = 0.0f;
    swing.y = rollSign;
    swing.z = 0.0f;
    swingCopy = swing;
    SumoF32 raiseScale = 1.100000023841858f;
    Vector3 raiseScaled = swingCopy.Scale(raiseScale);
    Vector3 raiseRotation = raiseScaled.Scale(rollComplement);
    primaryPose.joints[8 + raiseSide].firstDirection.Rotate(raiseRotation);
    Vector3 hipTug =
        MakeVector3((SumoF32)(0.9 - recoveryAngle),
                    (SumoF32)((SumoF64)rollSign * recoveryAngle * 1.5),
                    (SumoF32)((SumoF64)rollSign * -1.2));
    Vector3 hipCopy = hipTug;
    primaryPose.joints[2 + otherSide].firstDirection.Rotate(hipCopy);
    swing.x = -0.30000001192092896f;
    swing.y = 0.0f;
    swing.z = 0.0f;
    swingCopy = swing;
    Vector3 tuckRotation = swingCopy.Scale(rollComplement);
    primaryPose.joints[2 + raiseSide].firstDirection.Rotate(tuckRotation);
    if (postureTick > 100) {
      if (CalculateKineticEnergy() < g_randomHalf)
        postureTick = postureTick + 10;
    }
    goto tailTick;
  }
  case 14: {
    for (SumoS32 joint = 0; joint < 14; ++joint) {
      primaryPose.joints[joint] = secondaryPose.joints[joint];
      primaryPose.joints[joint].maximumCorrection = 0.004999999888241291f;
    }
    GameBox *head = bodyParts[2];
    SumoF32 headTilt = head->orientation.m21;
    recoveryAngle = (SumoF32)((SumoF64)recoveryAngle -
                              (SumoF64)headTilt * 0.05000000074505806f);
    SumoF32 swimLift = 0.0f;
    SumoF32 swimKick = 0.0f;
    SumoF32 swimTurn = 0.0f;
    if (fabs((SumoF64)headTilt) >= g_gameCameraHeightScale) {
      SumoF64 excess = (SumoF64)headTilt -
                       (SumoF64)headTilt / sqrt((SumoF64)headTilt * headTilt) *
                           g_gameCameraHeightScale;
      if (excess < g_vectorZero) {
        swimKick = (SumoF32)(-1.5f * excess);
        swimLift = (SumoF32)(g_inertiaRadiusScale * excess);
        swimTurn = (SumoF32)(g_gameCameraInputOffsetScale * excess);
      }
      if (excess > g_vectorZero) {
        swimKick = 0.0f;
        swimLift = (SumoF32)(g_boxWaterDiagonalScale * excess);
        swimTurn = (SumoF32)(excess * g_gameCameraHeightScale);
      }
    }
    SumoF32 kickSign = 1.0f;
    Vector3 kickAxis;
    kickAxis.x = 0.0f;
    kickAxis.z = 0.0f;
    Vector3 hipUnit;
    hipUnit.x = 1.0f;
    hipUnit.y = 0.0f;
    hipUnit.z = 0.0f;
    Vector3 kneeUnit = hipUnit;
    for (SumoS32 kick = 0; kick < 2; ++kick) {
      kickAxis.y = (SumoF32)((SumoF64)kickSign * -0.30000001192092896f);
      Vector3 kickCopy = kickAxis;
      volatile SumoF32 hipKickPin =
          (SumoF32)(sin((SumoF64)recoveryAngle) * kickSign * 0.3 + swimLift);
      SumoF32 hipKick = hipKickPin;
      Vector3 hipScaled = hipUnit.Scale(hipKick);
      Vector3 hipRotation = hipScaled + kickCopy;
      primaryPose.joints[2 + 3 * kick].firstDirection.Rotate(hipRotation);
      volatile SumoF32 kneeKickPin =
          (SumoF32)(sin((SumoF64)recoveryAngle) * kickSign * 0.3 - swimKick);
      SumoF32 kneeKick = kneeKickPin;
      Vector3 kneeRotation = kneeUnit.Scale(kneeKick);
      primaryPose.joints[3 + 3 * kick].firstDirection.Rotate(kneeRotation);
      kickSign = -1.0f;
    }
    volatile SumoF32 neckCosine = (SumoF32)cos((SumoF64)swimTurn);
    volatile SumoF32 neckSine = (SumoF32)sin((SumoF64)swimTurn);
    Vector3 neckDirection = MakeVector3(
        0.0f, (SumoF32)((SumoF64)neckCosine * g_gameBoxYScale), neckSine);
    Vector3 neckCopy = neckDirection;
    primaryPose.joints[1].firstDirection = neckCopy;
    primaryPose.joints[1].firstDirection.Normalize();
    primaryPose.joints[1].maximumCorrection = 0.0007999999797903001f;
    SumoF32 strokeSign = 1.0f;
    Vector3 strokeUnit;
    strokeUnit.y = 0.0f;
    strokeUnit.z = 0.0f;
    for (SumoS32 stroke = 0; stroke < 2; ++stroke) {
      armCurl[stroke] = 0.0f;
      SumoF32 strokeAngle = recoveryAngle;
      volatile SumoF32 strokeCosine = (SumoF32)cos((SumoF64)strokeAngle);
      volatile SumoF32 strokeSine = (SumoF32)sin((SumoF64)strokeAngle);
      Vector3 strokeDirection = MakeVector3(
          (SumoF32)((SumoF64)strokeSign * g_inertiaRadiusScale),
          (SumoF32)(-((SumoF64)strokeSign * strokeCosine)),
          (SumoF32)((SumoF64)g_randomHalf - (SumoF64)strokeSine * strokeSign));
      primaryPose.joints[8 + 3 * stroke].firstDirection = strokeDirection;
      primaryPose.joints[8 + 3 * stroke].firstDirection.Normalize();
      primaryPose.joints[8 + 3 * stroke].firstDirection.Normalize();
      strokeUnit.x = strokeSign;
      primaryPose.joints[10 + 3 * stroke].firstDirection = strokeUnit;
      primaryPose.joints[10 + 3 * stroke].firstDirection.Normalize();
      strokeSign = -1.0f;
    }
    goto tailTick;
  }
  default: goto tailJoin;
  }

raiseBalanceFlag:
  footTurnBlend = 1.0f;
  goto tailJoin;

tailTick:
  ++postureTick;
tailJoin: {
  SumoS32 postureNow = postureState;
  if (postureNow == 12 || postureNow == 13 || postureNow == 14)
    return;
}
  {
    Vector3 toOpponent =
        opponent->bodyParts[0]->position - bodyParts[0]->position;
    if ((SumoF64)firstFootTarget.z * firstFootTarget.z > 6.25f)
      footTurnBlend = 0.0f;
    SumoF64 opponentDistance = sqrt((SumoF64)toOpponent.x * toOpponent.x +
                                    (SumoF64)toOpponent.z * toOpponent.z +
                                    (SumoF64)toOpponent.y * toOpponent.y);
    SumoF64 inverseDistance = (SumoF64)g_gameOne / opponentDistance;
    SumoF64 turnWide = ((SumoF64)toOpponent.y * forwardAxis.y +
                        (SumoF64)toOpponent.x * forwardAxis.x +
                        (SumoF64)toOpponent.z * forwardAxis.z) *
                       inverseDistance * g_freeCameraAimScale;
    balanceTurn = (SumoF32)turnWide;
    volatile SumoF32 turnStoredPin = balanceTurn;
    if (turnWide * turnWide > 0.0015999999595806003f)
      balanceTurn = (SumoF32)((SumoF64)turnStoredPin / fabs(turnWide) *
                              0.03999999910593033f);
    if (!(balanceTurn < g_gameLevelArenaExtent) &&
        !(balanceTurn > g_gameLevelArenaExtent))
      balanceTurn = 0.0f;
    balanceTurn = smoothedTurnInput + balanceTurn;
    if (mode != 2 || active == 4 || active == 1 || active == 2)
      balanceTurn = smoothedTurnInput;
    SumoF64 turnAngleWide = (SumoF64)footTurnBlend * balanceTurn;
    Vector3 savedFirst = firstFootTarget;
    balanceTurn = (SumoF32)turnAngleWide;
    volatile SumoF32 turnAngle = (SumoF32)turnAngleWide;
    Vector3 savedSecond = secondFootTarget;
    volatile SumoF32 turnSineA = (SumoF32)sin(turnAngleWide);
    volatile SumoF32 rotatedX =
        (SumoF32)(cos((SumoF64)turnAngle) * firstFootTarget.x +
                  (SumoF64)turnSineA * firstFootTarget.z);
    volatile SumoF32 turnSineB = (SumoF32)sin((SumoF64)turnAngle);
    SumoF64 rotatedZ = cos((SumoF64)turnAngle) * firstFootTarget.z;
    SumoF64 crossTerm = (SumoF64)turnSineB * firstFootTarget.x;
    firstFootTarget.x = rotatedX;
    volatile SumoF32 rotatedZRounded = (SumoF32)(rotatedZ - crossTerm);
    firstFootTarget.z = rotatedZRounded;
    secondFootTarget.x = -rotatedX;
    secondFootTarget.z = -rotatedZRounded;
    if (rotatedX < 0.20000000298023224f) {
      firstFootTarget = savedFirst;
      secondFootTarget = savedSecond;
    }
    Vector3 supportCopy = supportPoint;
    SumoF64 crouchSpin = (SumoF64)poseCrouch * g_gameProjectileSpin;
    volatile SumoF32 crouchSpinRounded = (SumoF32)crouchSpin;
    poseGain = (SumoF32)(crouchSpin + poseGain);
    Vector3 marker = supportPoint;
    marker.y = 5.0f;
    RenderGameCrossMarker(&marker, (void *)0xff00);
    SumoF32 chase20 = 20.0f;
    predictedCom = comPosition + comVelocity.Scale(chase20);
    Vector3 motion = predictedCom - supportPoint;
    motion.y = 0.0f;
    motionVector = motion;
    SumoF64 strengthWide =
        (1.0 - balanceStrength) * 0.009999999776482582f + balanceStrength;
    balanceStrength = (SumoF32)strengthWide;
    balanceStrengthNew = (SumoF32)strengthWide;
    SumoF32 chase15 = 15.0f;
    Vector3 pitchError =
        (comPosition + comVelocity.Scale(chase15)) - supportCopy;
    SumoF64 pitchAccumulator =
        ((SumoF64)balancePitchVelocity * g_parserMinimumBreakability +
         balancePitch) *
        g_gameProjectileSpin;
    pitchAccumulator = pitchAccumulator + (SumoF64)lateralAxis.y * pitchError.y;
    pitchAccumulator = pitchAccumulator + (SumoF64)lateralAxis.z * pitchError.z;
    pitchAccumulator = pitchAccumulator + (SumoF64)lateralAxis.x * pitchError.x;
    pitchAccumulator = pitchAccumulator * 0.03999999910593033f;
    SumoF64 pitchMomentum = (SumoF64)angularMomentum.y * forwardAxis.y;
    pitchMomentum = pitchMomentum + (SumoF64)angularMomentum.x * forwardAxis.x;
    pitchMomentum = pitchMomentum + (SumoF64)angularMomentum.z * forwardAxis.z;
    pitchAccumulator =
        pitchAccumulator + pitchMomentum * 3.9999998989515007e-05f;
    SumoF64 pitchTerm = pitchAccumulator - balancePitchIntegral;
    SumoF64 pitchSquaredWide = pitchTerm * pitchTerm;
    volatile SumoF32 pitchSquared = (SumoF32)pitchSquaredWide;
    if (pitchSquaredWide > g_waterNeighborCoupling) {
      pitchTerm = sqrt((SumoF64)pitchSquared) * g_gameCameraHeightScale;
    }
    pitchTerm = pitchTerm * balanceStrengthNew;
    balancePitchVelocity =
        (SumoF32)((pitchTerm - balancePitchVelocity) * 0.009999999776482582f +
                  balancePitchVelocity);
    SumoF64 pitchWide =
        (pitchTerm + crouchSpinRounded + balancePitch) * g_gameCameraAimDamping;
    balancePitch = (SumoF32)pitchWide;
    balancePitchIntegral =
        (SumoF32)((pitchWide - poseGain - balancePitchIntegral) *
                      g_wavyTextDisplacement +
                  balancePitchIntegral);
    Vector3 rollError = comPosition - supportCopy;
    SumoF64 rollAccumulator = (SumoF64)forwardAxis.z * rollError.z;
    rollAccumulator = rollAccumulator + (SumoF64)forwardAxis.y * rollError.y;
    rollAccumulator = rollAccumulator + (SumoF64)forwardAxis.x * rollError.x;
    SumoF64 rollVelocity = (SumoF64)forwardAxis.x * comVelocity.x;
    rollVelocity = rollVelocity + (SumoF64)comVelocity.y * forwardAxis.y;
    rollVelocity = rollVelocity + (SumoF64)forwardAxis.z * comVelocity.z;
    rollAccumulator =
        (rollAccumulator + rollVelocity * g_gameCameraDistanceBias) *
        0.0020000000949949026f;
    SumoF64 rollMomentum = (SumoF64)angularMomentum.y * lateralAxis.y;
    rollMomentum = rollMomentum + (SumoF64)angularMomentum.z * lateralAxis.z;
    rollMomentum = rollMomentum + (SumoF64)angularMomentum.x * lateralAxis.x;
    rollAccumulator = rollAccumulator + rollMomentum * 2.9999999242136255e-05f;
    SumoF64 rollSquaredWide = rollAccumulator * rollAccumulator;
    volatile SumoF32 rollSquared = (SumoF32)rollSquaredWide;
    if (rollSquaredWide > g_waterNeighborCoupling)
      rollAccumulator = sqrt((SumoF64)rollSquared) * g_gameCameraHeightScale;
    rollAccumulator = rollAccumulator * balanceStrengthNew;
    rollAccumulator = rollAccumulator + balanceRoll;
    rollAccumulator = rollAccumulator * g_gameActivityDecay;
    rollAccumulator =
        rollAccumulator +
        ((SumoF64)stanceBlendCopy - g_randomHalf) * 0.004699999932199717f;
    rollAccumulator =
        rollAccumulator + (SumoF64)balanceTurn * 0.3760000169277191f;
    balanceRoll = (SumoF32)rollAccumulator;
    SumoF32 legSign = 1.0f;
    Vector3 legLift;
    legLift.x = 0.0f;
    SumoF32 crouchDouble = poseCrouch + poseCrouch;
    legLift.z = 0.0f;
    Vector3 basisX;
    basisX.x = 1.0f;
    basisX.y = 0.0f;
    basisX.z = 0.0f;
    Vector3 basisZ;
    basisZ.x = 0.0f;
    basisZ.y = 0.0f;
    basisZ.z = 1.0f;
    Vector3 basisUp;
    basisUp.x = 0.0f;
    basisUp.y = 1.0f;
    basisUp.z = 0.0f;
    for (SumoS32 legCursor = 0; legCursor <= 3; legCursor += 3) {
      volatile SumoF32 pitchCosine = (SumoF32)cos((SumoF64)balancePitch);
      volatile SumoF32 rollCosine = (SumoF32)cos((SumoF64)balanceRoll);
      volatile SumoF32 rollSine = (SumoF32)sin((SumoF64)balanceRoll);
      volatile SumoF32 pitchSine = (SumoF32)sin((SumoF64)balancePitch);
      Vector3 hipCandidate = MakeVector3(
          (SumoF32)((SumoF64)legSign * 0.03999999910593033f + rollSine),
          (SumoF32)(-((SumoF64)rollCosine * pitchCosine)), pitchSine);
      SumoS32 legSide = legCursor / 3;
      primaryPose.joints[2 + 3 * legSide].firstDirection = hipCandidate;
      Vector3 footTargetCopy = footTargets[legSide];
      Vector3 flatFoot = MakeVector3(footTargetCopy.x, 0.0f, footTargetCopy.z);
      Vector3 flatFootCopy = flatFoot;
      Vector3 pelvisColumn = bodyParts[0]->orientation.Column1();
      SumoF64 lift = (SumoF64)footTargetCopy.z * pelvisColumn.z +
                     (SumoF64)footTargetCopy.x * pelvisColumn.x;
      lift = lift * g_gameManPoseImpulseGain;
      lift = lift + (SumoF64)legSign * balanceRoll * g_randomHalf;
      lift = lift + (SumoF64)pelvisColumn.y * g_vectorZero;
      lift = lift - crouchDouble;
      SumoF64 flatLength = ((SumoF64)flatFootCopy.x * flatFootCopy.x +
                            (SumoF64)flatFootCopy.z * flatFootCopy.z) +
                           (SumoF64)flatFootCopy.y * flatFootCopy.y;
      lift = lift + flatLength * g_vectorZero;
      legLift.y = (SumoF32)lift;
      Vector3 legLiftCopy = legLift;
      Vector3 negatedFoot = -footTargets[legSide];
      Vector3 hipRelative = negatedFoot + legLiftCopy;
      if (legCursor != 0) {
        hipRelative.z = hipRelative.z - g_unk0x00c09ce0;
        hipRelative.y = hipRelative.y - g_unk0x00c09ce0;
      }
      volatile SumoF32 legReach =
          (SumoF32)sqrt((SumoF64)hipRelative.y * hipRelative.y +
                        (SumoF64)hipRelative.z * hipRelative.z +
                        (SumoF64)hipRelative.x * hipRelative.x);
      SumoF64 pitchAngleWide = (SumoF64)poseLift + balancePitch;
      volatile SumoF32 pitchAngle = (SumoF32)pitchAngleWide;
      volatile SumoF32 legPitchCosine = (SumoF32)cos(pitchAngleWide);
      volatile SumoF32 legPitchSine = (SumoF32)sin((SumoF64)pitchAngle);
      hipRelative.Rotate(basisX, legPitchCosine, legPitchSine);
      volatile SumoF32 legRollCosine = (SumoF32)cos((SumoF64)balanceRoll);
      volatile SumoF32 legRollSine = (SumoF32)(-sin((SumoF64)balanceRoll));
      hipRelative.Rotate(basisZ, legRollCosine, legRollSine);
      Vector3 hipDirection = -hipRelative;
      primaryPose.joints[2 + 3 * legSide].firstDirection = hipDirection;
      primaryPose.joints[2 + 3 * legSide].firstDirection.Normalize();
      SumoF32 kneeCosine =
          CalculateLimbAngleCosine(firstLimbLength, secondLimbLength, legReach);
      SumoF64 kneeSine =
          sqrt((SumoF64)g_gameOne - (SumoF64)kneeCosine * kneeCosine);
      Vector3 kneeDirection =
          MakeVector3(0.0f, -kneeCosine, (SumoF32)(-kneeSine));
      primaryPose.joints[3 + 3 * legSide].firstDirection = kneeDirection;
      primaryPose.joints[3 + 3 * legSide].firstDirection.Normalize();
      SumoF32 hipSecondCosine =
          CalculateLimbAngleCosine(firstLimbLength, legReach, secondLimbLength);
      primaryPose.joints[2 + 3 * legSide].secondDirection.x = legSign;
      primaryPose.joints[2 + 3 * legSide].secondDirection.y = 0.0f;
      primaryPose.joints[2 + 3 * legSide].secondDirection.z =
          -0.10000000149011612f;
      primaryPose.joints[2 + 3 * legSide].secondDirection.Normalize();
      volatile SumoF32 hipSwingSine = (SumoF32)sqrt(
          (SumoF64)g_gameOne - (SumoF64)hipSecondCosine * hipSecondCosine);
      Vector3 swingAxis =
          primaryPose.joints[2 + 3 * legSide].secondDirection.Scale(legSign);
      primaryPose.joints[2 + 3 * legSide].firstDirection.Rotate(
          swingAxis, -hipSecondCosine, hipSwingSine);
      primaryPose.joints[2 + 3 * legSide].firstDirection.Normalize();
      Vector3 ankleAim = (supportPoint - predictedCom) + basisUp;
      ankleAim.Normalize();
      SumoF64 aimCosine = cos((SumoF64)0.3f);
      if (ankleAim.y > -aimCosine) {
        volatile SumoF32 aimTangent = (SumoF32)tan((SumoF64)0.3f);
        ankleAim.y = (SumoF32)(((SumoF64)g_gameBoxYScale / aimTangent) *
                               sqrt(1.0 - (SumoF64)ankleAim.y * ankleAim.y));
        ankleAim.Normalize();
      }
      GameBoxJoint *ankle = joints[4 + 3 * legSide];
      Vector3 ankleDirection = ankle->boxes[1]->orientation.Transform(ankleAim);
      primaryPose.joints[4 + 3 * legSide].firstDirection = ankleDirection;
      legSign = -1.0f;
    }
    Vector3 footSplitVector = secondFootTarget - firstFootTarget;
    SumoF32 splitZ = footSplitVector.z;
    SumoF32 footSplit;
    if ((SumoF64)splitZ * splitZ <= g_gameAiMotionSquaredLimit)
      footSplit = splitZ;
    else if (splitZ >= g_vectorZero)
      footSplit = g_gameCameraMinimumDistanceScale;
    else
      footSplit = -4.0f;
    SumoF64 spinePitchWide = (SumoF64)balancePitch * 0.25f;
    volatile SumoF32 spinePitch = (SumoF32)spinePitchWide;
    volatile SumoF32 spinePitchCosine = (SumoF32)cos(spinePitchWide);
    volatile SumoF32 spineRollCosine =
        (SumoF32)cos((SumoF64)balanceRoll * 0.25f);
    volatile SumoF32 spineRollSine = (SumoF32)sin((SumoF64)balanceRoll * 0.25f);
    volatile SumoF32 spinePitchSine = (SumoF32)sin((SumoF64)spinePitch);
    Vector3 spineDirection =
        MakeVector3(spineRollSine,
                    (SumoF32)((SumoF64)spineRollCosine * spinePitchCosine *
                              g_gameBoxYScale),
                    spinePitchSine);
    Vector3 spineCopy = spineDirection;
    primaryPose.joints[0].firstDirection = spineCopy;
    primaryPose.joints[0].firstDirection.Normalize();
    primaryPose.joints[0].secondDirection.x = 40.0f;
    primaryPose.joints[0].secondDirection.y = 0.0f;
    primaryPose.joints[0].secondDirection.z = -footSplit;
    primaryPose.joints[0].secondDirection.Normalize();
    SumoF64 neckPitchWide = (SumoF64)balancePitch * 0.25f -
                            (SumoF64)poseLift * g_gameCameraInputDamping -
                            poseSway;
    volatile SumoF32 neckPitch = (SumoF32)neckPitchWide;
    volatile SumoF32 neckPitchCosine = (SumoF32)cos(neckPitchWide);
    volatile SumoF32 neckRollCosine =
        (SumoF32)cos((SumoF64)balanceRoll * 0.25f);
    volatile SumoF32 neckRollSine = (SumoF32)sin((SumoF64)balanceRoll * 0.25f);
    volatile SumoF32 neckPitchSine = (SumoF32)sin((SumoF64)neckPitch);
    Vector3 neckDirection = MakeVector3(
        neckRollSine,
        (SumoF32)((SumoF64)neckRollCosine * neckPitchCosine * g_gameBoxYScale),
        neckPitchSine);
    Vector3 neckCopy = neckDirection;
    primaryPose.joints[1].firstDirection = neckCopy;
    primaryPose.joints[1].firstDirection.Normalize();
    bodyLean = poseCrouch;
    SumoF32 armSign = 1.0f;
    SumoF32 armSpread = poseLift + poseLift;
    SumoF32 leanScaled = poseCrouch * g_inertiaRadiusScale;
    Vector3 wristUnit;
    wristUnit.y = 0.0f;
    wristUnit.z = 0.0f;
    for (SumoS32 armCursor = 0; armCursor <= 0xc; armCursor += 0xc) {
      SumoS32 armSide = armCursor / 0xc;
      SumoF64 shoulderAngleWide =
          ((SumoF64)balancePitch - 0.07999999821186066f) * 3.0f +
          activityOffset;
      shoulderAngleWide = shoulderAngleWide - armSpread;
      shoulderAngleWide = shoulderAngleWide - leanScaled;
      volatile SumoF32 shoulderAngle = (SumoF32)shoulderAngleWide;
      volatile SumoF32 shoulderCosine = (SumoF32)cos(shoulderAngleWide);
      volatile SumoF32 rollSwaySine =
          (SumoF32)sin((SumoF64)balanceRoll * g_gameCameraMinimumDistanceScale);
      SumoF64 spreadWide = (SumoF64)footSplit * armSign;
      volatile SumoF32 spread = (SumoF32)spreadWide;
      volatile SumoF32 spreadSmall =
          (SumoF32)(spreadWide * 0.05000000074505806f);
      volatile SumoF32 shoulderZ =
          (SumoF32)((SumoF64)spreadSmall - sin((SumoF64)shoulderAngle));
      volatile SumoF32 shoulderY =
          (SumoF32)(-(SumoF64)shoulderCosine - (SumoF64)rollSwaySine * armSign);
      Vector3 shoulderDirection =
          MakeVector3((SumoF32)((SumoF64)armSign * g_gameCameraHeightScale),
                      shoulderY, shoulderZ);
      primaryPose.joints[8 + 3 * armSide].firstDirection = shoulderDirection;
      primaryPose.joints[8 + 3 * armSide].firstDirection.Normalize();
      Vector3 armTargetCopy = armAimLocal[armSide];
      volatile SumoF32 rotateScalePin =
          (SumoF32)((SumoF64)armSign * armCurl[armSide] * -0.75f);
      SumoF32 rotateScale = rotateScalePin;
      Vector3 rotationVector =
          primaryPose.joints[8 + 3 * armSide].secondDirection.Scale(
              rotateScale);
      armTargetCopy.Rotate(rotationVector);
      SumoF64 blendWide = 1.0 - armExtend[armSide];
      volatile SumoF32 blendRemain = (SumoF32)blendWide;
      volatile SumoF32 blendRemainCopyPin = (SumoF32)blendWide;
      SumoF32 blendRemainCopy = blendRemainCopyPin;
      Vector3 blendTarget = armTargetCopy.Scale(armExtend[armSide]);
      Vector3 blendDirection =
          primaryPose.joints[8 + 3 * armSide].firstDirection.Scale(
              blendRemainCopy);
      Vector3 blended = blendDirection + blendTarget;
      primaryPose.joints[8 + 3 * armSide].firstDirection = blended;
      primaryPose.joints[8 + 3 * armSide].firstDirection.Normalize();
      volatile SumoF32 elbowBlend =
          (SumoF32)((SumoF64)0.6599999666213989f -
                    (SumoF64)spread * 0.20000000298023224f);
      if (!(elbowBlend <= 1.659999966621399f))
        elbowBlend = 1.659999966621399f;
      volatile SumoF32 curlCosineA = (SumoF32)cos((SumoF64)armCurl[armSide]);
      volatile SumoF32 curlSineA = (SumoF32)sin((SumoF64)armCurl[armSide]);
      volatile SumoF32 curlCosineB = (SumoF32)cos((SumoF64)armCurl[armSide]);
      SumoF64 curlSineWide = sin((SumoF64)armCurl[armSide]);
      volatile SumoF32 elbowY =
          (SumoF32)(((SumoF64)curlCosineA * 1.659999966621399f - curlSineA) *
                        armExtend[armSide] +
                    (SumoF64)blendRemain * elbowBlend);
      volatile SumoF32 elbowX =
          (SumoF32)(((curlSineWide * 1.659999966621399f + curlCosineB) *
                         armExtend[armSide] +
                     blendRemain) *
                    armSign);
      Vector3 elbowDirection = MakeVector3(elbowX, 0.0f, elbowY);
      primaryPose.joints[9 + 3 * armSide].firstDirection = elbowDirection;
      primaryPose.joints[9 + 3 * armSide].firstDirection.Normalize();
      wristUnit.x = armSign;
      primaryPose.joints[10 + 3 * armSide].firstDirection = wristUnit;
      volatile SumoF32 raiseCosine = (SumoF32)cos((SumoF64)armRaise[armSide]);
      volatile SumoF32 raiseSineNegated =
          (SumoF32)(-sin((SumoF64)armRaise[armSide]));
      Vector3 raiseDirection = MakeVector3(
          (SumoF32)((SumoF64)raiseCosine * armSign), raiseSineNegated, 0.0f);
      SumoF32 raiseRemain = blendRemain;
      Vector3 raiseCopy = raiseDirection;
      Vector3 raiseTarget = raiseCopy.Scale(armExtend[armSide]);
      Vector3 raiseBase =
          primaryPose.joints[10 + 3 * armSide].firstDirection.Scale(
              raiseRemain);
      Vector3 raiseBlended = raiseBase + raiseTarget;
      primaryPose.joints[10 + 3 * armSide].firstDirection = raiseBlended;
      primaryPose.joints[10 + 3 * armSide].firstDirection.Normalize();
      armSign = -1.0f;
    }
  }

  {
    SumoS32 finalActive = active;
    if ((finalActive == 0 || finalActive == 5) && (inputMask & 8)) {
      for (SumoS32 relax = 0; relax < 8; ++relax)
        primaryPose.joints[relax].maximumCorrection = 0.0f;
    }
  }
}

extern const SumoF32 g_gameManPoseImpulseGain;

void GameMan::Render(void *poseState) {

if (m_bLobotomized) 
{
    for (SumoS32 index = 0; index < 14; ++index) 
    {
      GameBoxJoint *joint = joints[index];
      if (m_bLobotomized > 7) // severely broken
      {
        //joint->boxes[0] = NULL;
        //joint->boxes[1] = NULL;
      }
    }
    return;
 }

  GameManJointPose *poseJoint = ((GameManPose *)poseState)->joints;
  SumoF32 primaryGain = 0.4f;
  SumoF32 secondaryGain = 0.25f;
  for (SumoS32 index = 0; index < 14; ++index, ++poseJoint) {
    GameBoxJoint *joint = joints[index];
    SumoF32 maximumCorrection = poseJoint->maximumCorrection;
    Vector3 firstTarget =
        poseJoint->firstDirection.Transform(joint->boxes[1]->orientation);
    Vector3 firstActual =
        joint->firstPoseDirection.Transform(joint->boxes[0]->orientation);
    Vector3 correction = firstTarget.Cross(firstActual).Scale(primaryGain);

    Vector3 secondTarget =
        poseJoint->secondDirection.Transform(joint->boxes[1]->orientation);
    Vector3 secondActual =
        joint->secondPoseDirection.Transform(joint->boxes[0]->orientation);
    Vector3 secondCorrection = secondTarget.Cross(secondActual)
                                   .Scale(primaryGain)
                                   .Scale(secondaryGain);
    correction.x = correction.x + secondCorrection.x;
    correction.y = correction.y + secondCorrection.y;
    correction.z = correction.z + secondCorrection.z;

    Vector3 angularDifference =
        joint->boxes[0]->angularVelocity - joint->boxes[1]->angularVelocity;
    SumoF64 differenceX = (SumoF64)correction.x - angularDifference.x;
    correction.x = (SumoF32)differenceX;
    SumoF64 differenceY = (SumoF64)correction.y - angularDifference.y;
    correction.y = (SumoF32)differenceY;
    SumoF64 differenceZ = (SumoF64)correction.z - angularDifference.z;
    correction.z = (SumoF32)differenceZ;
    SumoF64 lengthSquared = differenceZ * differenceZ +
                            differenceY * differenceY +
                            differenceX * differenceX;
    if (lengthSquared > (SumoF64)maximumCorrection * maximumCorrection) {
      SumoF64 normalizeScale = maximumCorrection / sqrt(lengthSquared);
      correction.x = (SumoF32)(correction.x * normalizeScale);
      correction.y = (SumoF32)(correction.y * normalizeScale);
      correction.z = (SumoF32)(correction.z * normalizeScale);
    }

    SumoF32 impulseScale = (SumoF32)(g_gameManPoseImpulseGain /
                                     ((SumoF64)joint->boxes[1]->inverseInertia +
                                      joint->boxes[0]->inverseInertia));
    Vector3 impulse = correction.Scale(impulseScale);
    ApplyPairedAngularImpulse(joint->boxes, impulse);
  }
}

extern SumoS32 g_gameIsRunning;
extern SumoU8 g_gameLevelEditorActive;
extern SumoS32 g_gameLevelEditorCloseRequested;
extern SumoS32 g_gameAlternateCameraMode;
extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gameMouseX;
extern SumoS32 g_levelLoadState[8];
extern SumoF32 g_gameArenaExtent;
extern SumoS32 g_gameMenuSelection;
extern SumoS32 g_gameMenuPage;
extern SumoS32 g_gameMenuAlternateLayout;
extern GameBox *g_gameBoxesEnd;
extern GameRandomGenerator g_gameRandom;
extern const SumoF32 g_gameProjectileDefaultValue;
extern const SumoF32 g_gameCameraInputOffsetScale;
extern const SumoF32 g_gameCameraInputDamping;
extern const SumoF32 g_gameCameraDistanceBias;
extern const SumoF32 g_randomHalf;

void SetGameCursorVisible(SumoU8 visible);
void StartGameLevelEditor(char *source);
void BuildDefaultGameArena(SumoS32 type);
void RefreshGameContactLists();

extern SumoS32 g_selectedLevelScript;

SumoS32 g_gameArenaPageRowCount = 2;

SumoS32 g_gameArenaPageChainLinks = 3;
void (*g_gameModFilePickerRequest)();

SumoS32 InitializeGameRuntimeState() {
  if (g_gameArenaPageRowCount > 2 && g_selectedLevelScript >= 8) {
    g_selectedLevelScript = 0;
    if (g_gameModFilePickerRequest != 0)
      g_gameModFilePickerRequest();
  }

  if (g_gameIsRunning) {
    if (g_gameLevelEditorActive)
      g_gameLevelEditorCloseRequested = 1;
    g_gameLevelEditorActive = 1;
    g_gameAlternateCameraMode = 0;
    StartGameLevelEditor(0);
    return 0;
  }

  g_screenTintLevel = 0;
  SetGameCursorVisible(1);
  g_gameMouseX = -1;
  g_levelLoadState[4] = 10;
  BuildDefaultGameArena(0);
  g_gameArenaExtent = 80.0f;
  g_gameMenuSelection = 0;
  g_gameResetScores = true;

  SumoF32 laneOffsets[3];
  laneOffsets[0] = -7.0f;
  laneOffsets[1] = 7.0f;
  laneOffsets[2] = 7.0f;
  SumoS32 rowCounts[3];
  rowCounts[0] = 3;
  rowCounts[1] = 3;
  rowCounts[2] = 3;
  SumoS32 stackCounts[3];
  stackCounts[0] = 4;
  stackCounts[1] = 4;
  stackCounts[2] = 4;

  for (SumoS32 slab = -4; slab < 5; ++slab) {
    Vector3 slabPosition = MakeVector3(-80.0f, 15.0f, (SumoF32)slab * 7.0f);
    Vector3 slabHalfSize = MakeVector3(1.0f, -25.0f, 1.0f);
    GameBox *slabBox = CreateGameBox(slabHalfSize, slabPosition, 1,
                                     g_gameProjectileDefaultValue);
    slabBox->MakeImmovable();
  }

  Vector3 backdropHalfSize = MakeVector3(4.0f, -1.5f, 30.0f);
  Vector3 backdropPosition = MakeVector3(-80.0f, 40.0f, 0.0f);
  GameBox *backdrop = CreateGameBox(backdropHalfSize, backdropPosition, 1,
                                    g_gameProjectileDefaultValue);
  backdrop->MakeImmovable();

  SumoS32 page = g_gameMenuPage;
  SumoS32 columnCount = 1;
  SumoS32 typeBase = page;
  SumoS32 selectBase = 0;
  Vector3 columnOffset = MakeVector3(0.0f, 0.0f, 0.0f);
  switch (page) {
  case 1:
    columnOffset.z = 10.0f;
    columnCount = 2;
    stackCounts[1] = g_gameArenaPageRowCount;
    rowCounts[1] = g_gameArenaPageChainLinks;
    selectBase = 0;
    typeBase = 3;
    break;
  case 2:
    columnOffset.z = 10.0f;
    columnCount = 2;
    stackCounts[0] = 5;
    rowCounts[0] = 2;
    stackCounts[1] = 2;
    selectBase = 0;
    typeBase = 5;
    break;
  case 3:
    columnCount = 2;
    stackCounts[0] = 0;
    stackCounts[1] = 1;
    rowCounts[1] = 4;
    selectBase = 5;
    typeBase = 5;
  break;

  default: 
  columnCount = 3; 
  columnOffset.z = 20.0f; 

  if (g_sumoMode == 3)
  {
    stackCounts[0] = 1;
    stackCounts[1] = 1;
  }
      stackCounts[2] = g_gameArenaPageRowCount;
  rowCounts[2] = g_gameArenaPageChainLinks;
  break;
  }
  for (SumoS32 column = 0; column < columnCount; ++column) {
    Vector3 laneAnchorPositions[2];
    laneAnchorPositions[0] = MakeVector3(-5.0f, 0.0f, -7.0f) + columnOffset;
    laneAnchorPositions[1] = MakeVector3(-5.0f, 0.0f, 7.0f) + columnOffset;
    GameBox *laneAnchorBoxes[2];
    laneAnchorBoxes[0] = backdrop;
    laneAnchorBoxes[1] = backdrop;
    SumoF32 towerHeight = 40.0f;

    SumoS32 stackCount = stackCounts[column];
    if (stackCount > 0) {
      SumoS32 rowCount = rowCounts[column];
      SumoS32 letterType = typeBase + column + MENU_START_INDEX;
      SumoS32 textureBase = column * 16 + 1;
      for (SumoS32 stack = 0; stack < stackCount; ++stack) {
        for (SumoS32 row = 0; row < rowCount; ++row) {
          SumoF32 rowCenter = towerHeight + g_gameCameraInputDamping;
          SumoF32 rotationAngle = (SumoF32)((SumoF64)row * g_vectorZero);
          for (SumoS32 lane = 0; lane < 2; ++lane) {
            Vector3 linkHalfSize =
                MakeVector3(g_randomHalf, -0.9f, g_randomHalf);
            Vector3 linkPosition =
                MakeVector3(-85.0f, rowCenter, laneOffsets[lane]) +
                columnOffset;
            GameBox *link = CreateGameBox(linkHalfSize, linkPosition, 0,
                                          g_gameProjectileDefaultValue);
            link->orientation.RotateColumns02(rotationAngle);
            link->inertia = link->inertia * 3.0f;
            link->inverseInertia = link->inverseInertia * 0.33333334f;

            GameBoxJoint *joint = g_gameContactObjectsEnd;
            joint->boxes[0] = laneAnchorBoxes[lane];
            joint->localAnchors[0] = laneAnchorPositions[lane];
            if (row == 0 && stack == 0)
              joint->firstPoseDirection = MakeVector3(0.0f, -1.0f, 0.0f);
            else
              joint->firstPoseDirection = MakeVector3(0.0f, 1.0f, 0.0f);
            joint->secondPoseDirection = MakeVector3(1.0f, 0.0f, 0.0f);
            joint->boxes[1] = link;
            joint->localAnchors[1] = MakeVector3(0.0f, -0.9f, 0.0f);
            laneAnchorPositions[lane] = MakeVector3(0.0f, 0.9f, 0.0f);
            joint->secondAnchorDirection = MakeVector3(0.0f, 1.0f, 0.0f);
            joint->secondAxis = MakeVector3(1.0f, 0.0f, 0.0f);
            joint->state = 0.0f;
            joint->minimumAngle = 0.81f;
            joint->maximumAngle = 1.21f;
            laneAnchorBoxes[lane] = link;
            g_gameContactObjectsEnd++;
          }
          towerHeight = towerHeight + 1.8f;
        }

        SumoF32 letterHalf = 1.8f;
        if (column == 2) {
          letterHalf = 1.9f;
          if (stack == 1 && g_gameMenuAlternateLayout != 0)
            selectBase = 1;
          if (stack == 2 && g_gameMenuAlternateLayout == 0)
            selectBase = 1;
        }
        Vector3 letterHalfSize =
            MakeVector3(g_gameCameraInputOffsetScale, -letterHalf, 9.0f);
        Vector3 letterPosition =
            MakeVector3(-85.0f, letterHalf + towerHeight, 0.0f) + columnOffset;
        GameBox *letter = CreateGameBox(letterHalfSize, letterPosition,
                                        letterType, -0.055555556f);
        letter->unknownBC = textureBase + stack;
        SumoS32 letterCell = stack + selectBase;
        Vector3 letterAnchor = MakeVector3(
            g_gameCameraInputOffsetScale,
            (SumoF32)(-(SumoF64)letterHalf - (SumoF64)letterCell * 2.953125f),
            9.0f);
        letter->accumulatedForce = -letterAnchor;
        letter->mass = letter->mass * 0.03f;
        letter->inverseMass = letter->inverseMass * 33.333336f;
        letter->damping = letter->damping * 0.03f;
        letter->inertia = letter->inertia * 0.03f;
        letter->inverseInertia = letter->inverseInertia * 33.333336f;
        letter->unknownC0 = 2;
        letter->unknownC4 = 3.0f;
        SumoF32 verticalKick = (SumoF32)((SumoF64)g_gameRandom.Next() * 0.26);
        SumoF32 lateralKick =
            (SumoF32)(((SumoF64)g_gameRandom.Next() + g_gameOne) * -0.04);
        letter->linearVelocity = MakeVector3(lateralKick, verticalKick, 0.0f);
        towerHeight = (SumoF32)((SumoF64)letterHalf * 2.0 + towerHeight);
        letter->breakability = 15.0f;

        for (SumoS32 lane = 0; lane < 2; ++lane) {
          GameBoxJoint *joint = g_gameContactObjectsEnd;
          joint->boxes[0] = laneAnchorBoxes[lane];
          joint->localAnchors[0] = laneAnchorPositions[lane];
          joint->firstPoseDirection = MakeVector3(0.0f, 1.0f, 0.0f);
          joint->secondPoseDirection = MakeVector3(1.0f, 0.0f, 0.0f);
          joint->boxes[1] = letter;
          joint->localAnchors[1] =
              MakeVector3(0.0f, -letterHalf, laneOffsets[lane]);
          joint->secondAnchorDirection = MakeVector3(0.0f, 1.0f, 0.0f);
          joint->secondAxis = MakeVector3(1.0f, 0.0f, 0.0f);
          joint->state = 0.0f;
          joint->minimumAngle = 0.809999942779541f;
          joint->maximumAngle = 1.21f;
          laneAnchorPositions[lane] =
              MakeVector3(0.0f, letterHalf, laneOffsets[lane]);
          laneAnchorBoxes[lane] = letter;
          g_gameContactObjectsEnd++;
        }
      }
    }
    columnOffset.z = columnOffset.z - g_gameCameraDistanceBias;
  }

  RefreshGameContactLists();
  return 0;
}

char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color);
Vector3 GetGameMouseRayDirection();
SumoS32 InitializeGameRuntimeState();

extern SumoS32 g_gameProjectileCooldown;
extern SumoS32 g_gameMouseX;
extern SumoS32 g_screenTintLevel;
extern Vector3 g_gameCameraWorldPosition;
extern Matrix3 g_gameInverseViewMatrix;
extern const SumoF32 g_gameProjectionMinimum;
extern const SumoF32 g_gameCameraInputOffsetScale;

SumoS32 UpdateHiddenGameScreen() {
  --g_gameProjectileCooldown;
  if (g_gameMouseX != -1) {
    if (g_gameProjectileCooldown <= 0) {
      g_gameProjectileCooldown = 60;
      Vector3 direction = GetGameMouseRayDirection();
      SumoF32 range = 50.0f;
      Vector3 target = g_gameCameraWorldPosition + direction.Scale(range);
      Vector3 start =
          g_gameCameraWorldPosition +
          MakeVector3(5.0f, 0.0f, 4.0f).Transform(g_gameInverseViewMatrix);
      if (g_sumoMode != 2)
      LaunchGameBoxProjectile(start, target, 30.0f, 2);
      else
        LaunchGameBoxProjectile(start, target, 10.0f, 2);  
    }
    g_gameMouseX = -1;
  }

  DrawGameText(-0.2f, g_gameProjectionMinimum, "Hidden Part",
               (SumoS32)0xb08f8fff);
  if (g_screenTintLevel < 1000) {
    DrawGameText(0.2f, g_gameCameraInputOffsetScale,
                 "Controls:\n"
                 "Home/PageUp = Move Camera\n"
                 "Mouse Click = Punish!!!\n"
                 "Esc      = leave",
                 (SumoS32)0xb0ffffff);
  }

  if (g_gameBoxesEnd > g_gameBoxes + 4000)
    InitializeGameRuntimeState();
  return 0;
}

BigInteger TransformEncodedGameSettings(BigInteger input, SumoS32 modulusValue,
                                        BigInteger bound) {
  SumoS32 seed = 0x666;
  BigInteger modulus(modulusValue);
  BigInteger residue = input % modulus;
  SumoS32 bitCount;
  {
    BigInteger two(2);
    bitCount = modulus.Log(two) + 1;
  }
  SumoS32 wordCount;
  {
    BigInteger wordBase(0x10000);
    wordCount = bound.Log(wordBase) + 1;
  }

  BigInteger candidate(0);
  for (SumoS32 bit = -1; bit < bitCount; ++bit) {
    SumoU8 bitSet;
    if (bit == -1)
      bitSet = 1;
    else
      bitSet = residue.TestBit(bit) != 0;
    BigInteger place(1);
    for (SumoS32 word = wordCount; word > 0; --word) {
      seed = seed * 0x343fd + 0x269ec3;
      SumoS32 randomWord = (seed >> 16) & 0x7fff;
      if (bitSet) {
        BigInteger randomValue(randomWord);
        BigInteger contribution = place * randomValue;
        candidate += contribution;
      }
      BigInteger wordBase(0x10000);
      BigInteger advanced = place * wordBase;
      place = advanced;
    }
  }

  {
    BigInteger reduced = candidate % bound;
    candidate = reduced;
  }
  BigInteger quotient = candidate / modulus;
  BigInteger snapped = quotient * modulus;
  BigInteger result = snapped + residue;
  candidate = result;
  return candidate;
}

extern const char g_gameScreenshotReadMode[];

DECOMP_SIZE_ASSERT(ReplayWordVector, 0x0c);
DECOMP_SIZE_ASSERT(ReplayStream, 0x18);

// FUNCTION: SUMO 0x0040d465
// FUNCTION: EDITOR 0x0040d487
void ReplayStream::ReadHeader(char *filename) {
  FILE *stream = fopen(filename, g_gameScreenshotReadMode);
  header = 0;
  if (stream != 0) {
    SumoS32 value;
    fread(&value, 1, sizeof(value), stream);
    header = value;
    fclose(stream);
  }
}

// FUNCTION: SUMO 0x0040d4a6
// FUNCTION: EDITOR 0x0040d4c8
void ReplayWriteBoundary() {
  if (g_replayRecording) {
    *g_replayStream.cursor = 4;
    ++g_replayStream.cursor;
  }
}

// FUNCTION: SUMO 0x0040d4c1
// FUNCTION: EDITOR 0x0040d4e3
void ReplayRecordCommand(SumoS32 first, SumoS32 second, SumoS32 third,
                         SumoS32 fourth) {

  if ((g_gameMode == 1 || g_gameMode == 3) && g_replayRecording) {
    *g_replayStream.cursor = 7;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = first;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = second;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = third;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = fourth;
    ++g_replayStream.cursor;
  }
}

// FUNCTION: SUMO 0x0040d59d
// FUNCTION: EDITOR 0x0040d5bf
void ReplayStream::AppendToFile(char *filename) {

  if (header != 0) {
    // STRING: SUMO 0x0042c798
    // STRING: EDITOR 0x0042c798
    FILE *stream = fopen(filename, "ab");
    ftell(stream);
    fwrite(&words[0], 1, (cursor - &words[0]) * sizeof(SumoU32), stream);
    fclose(stream);
  }
}

// FUNCTION: SUMO 0x0040d5f9
// FUNCTION: EDITOR 0x0040d61b
ReplayStream::~ReplayStream() {}

// FUNCTION: SUMO 0x0040d601
// FUNCTION: EDITOR 0x0040d623
void StopReplayRecording() {
  // STRING: SUMO 0x0042c79c
  // STRING: EDITOR 0x0042c79c
  g_replayStream.AppendToFile("out.dat");
  g_replayStream.cursor = g_replayStream.limit;
  g_replayRecording = false;
}

// FUNCTION: SUMO 0x0040d65f
// FUNCTION: EDITOR 0x0040d681
void ReplayStream::EnsureSpace(SumoU32 additionalWords) {
  SumoU32 cursorOffset = cursor - &words[0];
  SumoU32 requiredSize = cursorOffset + additionalWords;
  if (words.Size() < requiredSize) {
    words.Resize(requiredSize);
    cursor = &words[0] + cursorOffset;
    limit = 0;
  }
}

// FUNCTION: SUMO 0x0040d6ab
// FUNCTION: EDITOR 0x0040d6cd
void ReplayStream::LoadFile(char *filename) {
  FILE *stream = fopen(filename, g_gameScreenshotReadMode);
  fseek(stream, 0, SEEK_END);
  SumoS32 fileSize = ftell(stream);
  fseek(stream, 0, SEEK_SET);

  words.Resize(fileSize / sizeof(SumoU32));
  fread(&words[0], 1, fileSize, stream);
  fclose(stream);

  cursor = &words[0];
  limit = cursor + fileSize / sizeof(SumoU32);
}

// FUNCTION: SUMO 0x0040d729
// FUNCTION: EDITOR 0x0040d74b
void ReplayStream::Reset() {
  words.Clear();
  words.Resize(0x40000);
  cursor = &words[0];
  limit = 0;
  EnsureSpace(0x10000);
  header = 0;
}

// FUNCTION: SUMO 0x0040d763
// FUNCTION: EDITOR 0x0040d785
ReplayStream::ReplayStream() { Reset(); }

// FUNCTION: SUMO 0x0040d77a
// FUNCTION: EDITOR 0x0040d79c
void StartReplayRecording() {
  g_replayStream.Reset();
  g_replayRecording = true;
  g_replayStream.ReadHeader("out.dat");
  *g_replayStream.cursor = 4;
  ++g_replayStream.cursor;
}

// GLOBAL: SUMO 0x00c06064
// GLOBAL: EDITOR 0x00c06884
bool g_replayRecording;

// GLOBAL: SUMO 0x00c0602c
// GLOBAL: EDITOR 0x00c0684c
SumoS32 g_gameMode;
// GLOBAL: SUMO 0x00c0601c
// GLOBAL: EDITOR 0x00c0683c
SumoS32 g_gameReplayFrame;

extern SumoU8 g_gameKeyDown[256];
extern SumoU8 g_gameKeyPressed[256];
extern SumoS32 g_gameIsRunning;
extern SumoS32 g_screenTintLevel;
extern GameBox g_gameBoxes[4096];
extern GameBox *g_gameBoxesEnd;
extern Vector3 g_gameCameraWorldPosition;
extern Matrix3 g_gameInverseViewMatrix;
extern SumoS32 g_gameReplayFrame;
extern Vector3 g_freeCameraTarget;
extern char *g_gameCommandLineFile;
extern SumoS32 g_gameLevelEditorCloseRequested;

void GameAudioNoOpCallback();
void StartGameRound();
void SumoAssert(bool condition);
void BuildDefaultGameArena(SumoS32 type);
void SetSceneTransform(Vector3 &position, SumoF32 angle);

static SumoU32 ReadReplayWord() {
  SumoU32 value = *g_replayPlaybackStream.cursor;
  ++g_replayPlaybackStream.cursor;
  return value;
}

static void WriteReplayWord(SumoU32 value) {
  *g_replayStream.cursor = value;
  ++g_replayStream.cursor;
}

static void CrashOnCorruptReplay() {
  SumoU8 *invalidAddress = 0;
  for (;;) {
    *++invalidAddress = 0x7f;
  }
}

SumoS32 UpdateGameReplay() {
  if (g_gameKeyPressed[5]) {
    g_gameKeyPressed[5] = 0;
    if (g_replayRecording)
      StopReplayRecording();
    else
      StartReplayRecording();
  }
  if (g_gameKeyPressed[4] && g_gameMode == 1) {
    g_gameKeyPressed[4] = 0;
    if (g_gameIsRunning) {
      g_gameKeyPressed[0x3c] = 1;
      GameAudioNoOpCallback();
    } else {
      StartGameRound();
    }
    g_replayStream.Reset();
    g_replayStream.header = 0;
    g_replayRecording = 0;
  }
  if (g_gameKeyPressed[6]) {
    g_gameKeyPressed[6] = 0;
    if (g_replayRecording)
      StopReplayRecording();
    g_gameKeyPressed[0x3c] = 1;
    GameAudioNoOpCallback();
    StartReplayRecording();
  }

  if ((g_gameMode == 1 || g_gameMode == 3) && g_replayRecording) {
    g_replayStream.EnsureSpace(0x10000);
    SumoS32 boxIndex = 0;
    for (GameBox *box = g_gameBoxes; box < g_gameBoxesEnd; ++box, ++boxIndex) {
      if (box->flag58) {
        if (box->replayPresent == 1) {
          box->replayPresent = 0;
          WriteReplayWord(5);
          WriteReplayWord((SumoU32)boxIndex);
        }
        continue;
      }
      if (!box->replayPresent) {
        box->replayPresent = 1;
        WriteReplayWord(3);
        WriteReplayWord((SumoU32)boxIndex);
        SumoS32 pointCount = (SumoS32)(box->pointsEnd - box->pointsBegin);
        WriteReplayWord((SumoU32)pointCount);
        for (SumoS32 point = 0; point < pointCount; ++point) {
          const SumoU32 *words =
              (const SumoU32 *)&box->pointsBegin[point].position;
          WriteReplayWord(words[0]);
          WriteReplayWord(words[1]);
          WriteReplayWord(words[2]);
        }
        WriteReplayWord(
            (SumoU32)(box->pointReferencesEnd - box->pointReferencesBegin));
        SumoS32 faceCount = (SumoS32)(box->facesEnd - box->facesBegin);
        WriteReplayWord((SumoU32)faceCount);
        for (SumoS32 face = 0; face < faceCount; ++face) {
          GameBoxFace *currentFace = &box->facesBegin[face];
          WriteReplayWord((SumoU32)currentFace->pointCount);
          for (SumoS32 reference = 0; reference < currentFace->pointCount;
               ++reference)
            WriteReplayWord(
                (SumoU32)currentFace->pointReferences[reference].index);
        }
        WriteReplayWord((SumoU32)box->type);
        WriteReplayWord(*(const SumoU32 *)&box->defaultValue);
        const SumoU32 *forceWords = (const SumoU32 *)&box->accumulatedForce;
        WriteReplayWord(forceWords[0]);
        WriteReplayWord(forceWords[1]);
        WriteReplayWord(forceWords[2]);
        WriteReplayWord(*(const SumoU32 *)&box->breakability);
      }
      if ((box->replayPosition - box->position).LengthSquared() >
          1.0000000116860974e-06f) {
        box->replayPosition = box->position;
        WriteReplayWord(2);
        WriteReplayWord((SumoU32)boxIndex);
        const SumoU32 *positionWords = (const SumoU32 *)&box->position;
        for (SumoS32 word = 0; word < 3; ++word)
          WriteReplayWord(positionWords[word]);
        const SumoU32 *orientationWords = (const SumoU32 *)&box->orientation;
        for (SumoS32 word = 0; word < 9; ++word)
          WriteReplayWord(orientationWords[word]);
      }
    }
    WriteReplayWord(1);
    WriteReplayWord(6);
    const SumoU32 *cameraWords = (const SumoU32 *)&g_gameCameraWorldPosition;
    for (SumoS32 word = 0; word < 3; ++word)
      WriteReplayWord(cameraWords[word]);
    const SumoU32 *viewWords = (const SumoU32 *)&g_gameInverseViewMatrix;
    for (SumoS32 word = 0; word < 9; ++word)
      WriteReplayWord(viewWords[word]);
    ++g_replayStream.header;
  }

  if (g_gameMode == 2 || g_gameMode == 3) {
    if ((g_screenTintLevel + 1) % 2 != 0 && g_gameKeyDown[0x3d]) {
      g_gameReplayFrame = g_replayStream.header;
      return g_replayStream.header;
    }
    SumoS32 passes = g_gameKeyDown[0x3e] ? 2 : 1;
    do {
      if (g_replayPlaybackStream.cursor >= g_replayPlaybackStream.limit) {
        if (g_gameCommandLineFile[0] != 0)
          g_replayPlaybackStream.LoadFile(g_gameCommandLineFile);
        else
          g_replayPlaybackStream.LoadFile((char *)"in.dat");
      }
      SumoF32 averageX = 0.0f;
      SumoF32 averageY = 0.0f;
      SumoF32 averageZ = 0.0f;
      SumoF32 sampleCount = 0.0f;
      for (;;) {
        SumoS32 tag = 1;
        if (g_replayPlaybackStream.cursor >= g_replayPlaybackStream.limit) {
          g_gameLevelEditorCloseRequested = 1;
        } else {
          tag = (SumoS32)ReadReplayWord();
          if (tag < 0 || tag > 7)
            g_replayPlaybackStream.cursor = g_replayPlaybackStream.limit;
        }

        if (tag == 7) {
          SumoS32 soundIndex = (SumoS32)ReadReplayWord();
          SumoU32 frequencyBits = ReadReplayWord();
          SumoU32 volumeBits = ReadReplayWord();
          SumoS32 channel = (SumoS32)ReadReplayWord();
         // PlayGameSound(soundIndex, *(SumoF32 *)&frequencyBits,
       //                 *(SumoF32 *)&volumeBits, channel);
          continue;
        }
        if (tag == 6) {
          if (g_gameMode == 3) {
            for (SumoS32 word = 0; word < 12; ++word)
              ReadReplayWord();
          } else {
            SumoU32 *cameraWords = (SumoU32 *)&g_gameCameraWorldPosition;
            for (SumoS32 word = 0; word < 3; ++word)
              cameraWords[word] = ReadReplayWord();
            SumoU32 *viewWords = (SumoU32 *)&g_gameInverseViewMatrix;
            for (SumoS32 word = 0; word < 9; ++word)
              viewWords[word] = ReadReplayWord();
          }
          continue;
        }
        if (tag == 5) {
          SumoS32 boxIndex = (SumoS32)ReadReplayWord();
          g_gameBoxes[boxIndex].flag58 = 1;
          continue;
        }
        if (tag == 4) {
          InitializeWaterField();
          BuildDefaultGameArena(0);
          g_screenTintLevel = 0;
          ReplayWriteBoundary();
          Vector3 scenePosition = MakeVector3(40.0f, 35.0f, -10.0f);
          SetSceneTransform(scenePosition, 0.0f);
          continue;
        }
        if (tag == 3) {
          SumoS32 boxIndex = (SumoS32)ReadReplayWord();
          GameBox *box = &g_gameBoxes[boxIndex];
          if (g_gameBoxesEnd <= box) {
            do {
              g_gameBoxesEnd->flag58 = 1;
              ++g_gameBoxesEnd;
            } while (g_gameBoxesEnd <= box);
          }
          box->flag58 = 0;
          SumoS32 pointCount = (SumoS32)ReadReplayWord();
          if (pointCount > 100 || pointCount < 0)
            CrashOnCorruptReplay();
          box->pointsBegin = (GameBoxPoint *)malloc(pointCount * 0x10);
          SumoAssert(box->pointsBegin != 0);
          box->pointsEnd = box->pointsBegin + pointCount;
          for (SumoS32 point = 0; point < pointCount; ++point) {
            SumoU32 *words = (SumoU32 *)&box->pointsBegin[point].position;
            words[0] = ReadReplayWord();
            words[1] = ReadReplayWord();
            words[2] = ReadReplayWord();
            box->pointsBegin[point].clipSide = 0;
            box->pointsBegin[point].flag0D = 0;
            box->pointsBegin[point].clipIndex = 0;
          }
          SumoS32 referenceTotal = (SumoS32)ReadReplayWord();
          SumoS32 faceCount = (SumoS32)ReadReplayWord();
          if (referenceTotal > 100 || referenceTotal < 0)
            CrashOnCorruptReplay();
          if (faceCount > 100 || faceCount < 0)
            CrashOnCorruptReplay();
          box->facesBegin = (GameBoxFace *)malloc(faceCount * 0x24);
          box->facesEnd = box->facesBegin + faceCount;
          box->pointReferencesBegin =
              (GameBoxPointReference *)malloc(referenceTotal * 8);
          box->pointReferencesEnd = box->pointReferencesBegin + referenceTotal;
          GameBoxPointReference *referenceCursor = box->pointReferencesBegin;
          for (SumoS32 face = 0; face < faceCount; ++face) {
            GameBoxFace *currentFace = &box->facesBegin[face];
            currentFace->pointCount = (SumoS32)ReadReplayWord();
            currentFace->pointReferences = referenceCursor;
            currentFace->normal.z = 0.0f;
            currentFace->normal.y = 0.0f;
            currentFace->normal.x = 0.0f;
            for (SumoS32 reference = 0; reference < currentFace->pointCount;
                 ++reference) {
              referenceCursor->index = (SumoS32)ReadReplayWord();
              SumoAssert(referenceCursor->index >= 0);
              SumoAssert(referenceCursor->index <
                         (SumoS32)(box->pointsEnd - box->pointsBegin));
              referenceCursor->point =
                  box->pointsBegin + referenceCursor->index;
              ++referenceCursor;
            }
            box->UpdateFacePlane(*currentFace);
          }
          box->type = (SumoS32)ReadReplayWord();
          *(SumoU32 *)&box->defaultValue = ReadReplayWord();
          box->InitializePhysics();
          SumoU32 *forceWords = (SumoU32 *)&box->accumulatedForce;
          for (SumoS32 word = 0; word < 3; ++word)
            forceWords[word] = ReadReplayWord();
          *(SumoU32 *)&box->breakability = ReadReplayWord();
          box->position =
              MakeVector3((SumoF32)(boxIndex * 2 + 12),
                          (SumoF32)(boxIndex + 12), (SumoF32)(boxIndex + 12));
          box->orientation.SetIdentity();
          box->immovable = 1;
          continue;
        }
        if (tag == 2) {
          SumoS32 boxIndex = (SumoS32)ReadReplayWord();
          GameBox *box = &g_gameBoxes[boxIndex];
          Vector3 previousPosition = box->position;
          SumoU32 *positionWords = (SumoU32 *)&box->position;
          for (SumoS32 word = 0; word < 3; ++word)
            positionWords[word] = ReadReplayWord();
          SumoU32 *orientationWords = (SumoU32 *)&box->orientation;
          for (SumoS32 word = 0; word < 9; ++word)
            orientationWords[word] = ReadReplayWord();
          box->linearVelocity = box->position - previousPosition;
          averageX = averageX + box->position.x;
          averageY = averageY + box->position.y;
          averageZ = averageZ + box->position.z;
          sampleCount = sampleCount + g_gameOne;
          continue;
        }

        if (tag == 1) {
          SumoF64 inverseCount = 1.0 / sampleCount;
          SumoF32 blendScale = 0.02f;
          Vector3 average;
          average.x = (SumoF32)(averageX * inverseCount);
          average.y = (SumoF32)(averageY * inverseCount);
          average.z = (SumoF32)(averageZ * inverseCount);
          Vector3 correction = (average - g_freeCameraTarget).Scale(blendScale);
          g_freeCameraTarget.x = g_freeCameraTarget.x + correction.x;
          g_freeCameraTarget.y = g_freeCameraTarget.y + correction.y;
          g_freeCameraTarget.z = g_freeCameraTarget.z + correction.z;
          break;
        }
      }
      --passes;
    } while (passes > 0);
  }

  g_gameReplayFrame = g_replayStream.header;
  return g_replayStream.header;
}

void SetGameFpuControlWord();
void UpdateGameCamera();
void UpdateFreeGameCamera(SumoS32 p_tickCount);
void ResetRenderVertexScratch();
void AdvanceGameSimulation();
SumoS32 UpdateHiddenGameScreen();
void GameAudioNoOpCallback();
void RestartGameMusic(SumoS32 playbackMode);
SumoS32 InitializeGameRuntimeState();
void StartGameRound();
char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color);
HRESULT RenderGameScene();
SumoS32 SaveGameScreenshot(char *prefix, SumoS32 index);

extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gamePrimaryInputPressed;
extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_gameScores[2];
extern SumoS32 g_gameHumanPlayerCount;
extern SumoS32 g_gameAlternateCameraMode;
extern SumoS32 g_gameRenderQualityCode;
extern SumoS32 g_gameRenderQualityEnabled;
extern SumoS32 g_gameReplayFrame;
extern SumoS32 g_gameRuntimeMode;
extern SumoU8 g_gameLineVertexScratch[0x80000];
extern SumoU8 *g_gameLineVertexCursor;
extern const SumoF32 g_freeCameraAimScale;
extern const SumoF32 g_gameProjectileSpin;
extern const SumoF32 g_gameProjectionMinimum;
extern const SumoF32 g_gameCameraInputOffsetScale;

// GLOBAL: SUMO 0x00d0f210
// GLOBAL: EDITOR 0x00d0fa2c
SumoS32 g_gameSimulationPaused;

// GLOBAL: SUMO 0x00453780
// GLOBAL: EDITOR 0x00453780
char g_gameDemoTimeoutText[] = "              demo time out\n"
                               "      please purchase a licence at\n"
                               "http://www.gravitysensation.com/sumotori/\n"
                               " \n"
                               " \n"
                               " \n"
                               "Copy the licence-key from the e-mail into the\n"
                               "box in the settings dialog at startup.\n"
                               "press ESC to quit\n";

static __forceinline void DrawNormalGameOverlay() 
{
  char computerNames[4][25] = {"Blue guy", "Grey guy", "Brown guy",
                               "Green guy"};
  SumoS32 colors[4] = {(SumoS32)0xe08080ff, (SumoS32)0xc0ffffff,
                       (SumoS32)0xe0c08000, (SumoS32)0xc020e020};
  char playerNames[2][25] = {"Blue guy (player)", "Grey guy (player2)"};
  char deadState[4][35] = {"[dead]", "[very dead]", "[overwhelmingly dead]", "[grounded meat]"};
  SumoF32 y = 0.5f;
  if (g_levelLoadState[4] != 11) 
  {
    if (g_sumoMode != 3)
    {
      for (SumoS32 slot = 0; slot < g_nextGameMan - g_gameMen; ++slot) {
        SumoS32 *player = &g_levelLoadState[slot];
        if (*player != -1) {
          char number[2];
          number[1] = 0;
          number[0] = (char)('1' + slot);
          DrawGameText(-0.2f, y, number, colors[*player]);
          char *name = g_gameMen[*player].mode == 1 ? playerNames[*player]
                                                    : computerNames[*player];
          DrawGameText(-0.15000001f, y, name, colors[*player]);
          if (g_gameMen[*player].m_bLobotomized) // good variable name
          {
            char *name = deadState[g_gameMen[*player].m_bLobotomized > 20];

            if (g_gameMen[*player].m_bLobotomized > 40)
              name = deadState[(g_gameMen[*player].m_bLobotomized > 62) + 2];
            DrawGameText(0.1f, y, name, colors[*player]);
          }

          y -= 0.050000001f;
        }
      }
    }
    else  if (g_levelLoadState[4] != 10)
    {
      char Buffer[6] = "xx:xx";
      Buffer[0] = g_gameScores[1] / 10 + '0';
      Buffer[1] = g_gameScores[1] % 10 + '0';
      Buffer[3] = g_gameScores[0] / 10 + '0';
      Buffer[4] = g_gameScores[0] % 10 + '0';
      DrawGameText(0.04, 0.5f, Buffer, 0xC0C0C0C0);
    }
  }

  if (g_levelLoadState[4] == 2) 
  {

    SumoS32 gameOver = 0;
    if ((g_gameScores[0] >= 5 || g_gameScores[1] >= 5) &&
        (g_gameScores[0] >= g_gameScores[1] + 2 ||
         g_gameScores[0] <= g_gameScores[1] - 2)) {
      gameOver = 1;
      SumoS32 winner = 0;
      if (g_gameScores[1] > g_gameScores[0])
        winner = gameOver;
      char arrows[2][16] = {" Game \n  ->  ", " Game \n  <-  "};
      DrawGameText(g_freeCameraAimScale, 0.41999999f, arrows[winner],
                   colors[winner]);
      DrawGameText(g_freeCameraAimScale, g_gameProjectileSpin,
                   "           \n Game Over \n           ",
                   (SumoS32)0xc0ffff00);
    } 
    if (g_sumoMode == 3) 
    {
      int winner = g_gameMen[1].eliminated == -1;
      char arrows[2][16] = {" Winner \n  ->  ", " Winner \n  <-  "};
      DrawGameText(-0.2f, 0.5f, arrows[winner],
                   colors[winner]);
    } 
    char spacetext[2][32] = {
        "Space to restart game","Space to main menu"
    };
    DrawGameText(-0.80000001f, g_gameProjectionMinimum, spacetext[gameOver],
                 (SumoS32)0xc0c0c0c0);
    if (g_gameKeyPressed[c_gameRoundRestartInput]) {
      if (gameOver) 
      {
        InitializeGameRuntimeState();
      }
      else
        StartGameRound();
    }
  }

  if (g_levelLoadState[4] == 0) {
    DrawGameText(0.2f, g_gameCameraInputOffsetScale,
                 "Controls:\n"
                 " DOWN      - start match\n"
                 " UP        - walk forward\n"
                 " BACKSPACE - Push\n"
                 " ENTER     - Push 1 hand",
                 (SumoS32)0xb0ffffff);
    if (g_gameAlternateCameraMode || g_gameHumanPlayerCount >= 2) {
      DrawGameText(-0.80000001f, g_gameCameraInputOffsetScale,
                   "Controls:\n"
                   " S         - start match\n"
                   " W         - walk forward\n"
                   " SHIFT     - Push\n"
                   " CTRL      - Push 1 hand",
                   (SumoS32)0xb0ffffff);
    }
  }
}

void UpdateFreeGameCameraFrame();
SumoS32 UpdateGameReplay();
void UpdateGameMenuScreen(SumoU8 drawOverlay);

extern SumoU32 g_screenTintColor;

void RunGameFrame(SumoU8 renderFrame) {
  SetGameFpuControlWord();
  ++g_screenTintLevel;
  SumoS32 screenshotRequested = 0;
  g_gameLineVertexCursor = &g_gameLineVertexScratch[0];

  if (1) {
    if (g_gameMode <= 2)
      UpdateGameCamera();
    else if (g_gameMode == 3)
      UpdateFreeGameCamera(4);
  }
  ResetRenderVertexScratch();

  if (!g_gameSimulationPaused)
    AdvanceGameSimulation();

  if (g_levelLoadState[4] == 10) {
    UpdateGameMenuScreen(renderFrame);
  } else {
    if (g_levelLoadState[4] == 11)
      UpdateHiddenGameScreen();
    GameAudioNoOpCallback();
    if (g_gamePrimaryInputPressed) {
      g_gamePrimaryInputPressed = 0;
      RestartGameMusic(3);
      InitializeGameRuntimeState();
    }
  }

  if (!renderFrame)
    return;

  if (g_gameKeyPressed[c_gameScreenshotInput]) {
    g_gameKeyPressed[c_gameScreenshotInput] = 0;
    screenshotRequested = 1;
    //g_gameRenderQualityCode = 12;
    //g_gameRenderQualityEnabled = 1;
  }

  if (g_gameMode <= 0) {
    DrawNormalGameOverlay();
  } else {
    if (g_gameKeyPressed[c_gameRoundRestartInput])
      StartGameRound();
    if (g_gameMode == 1 || g_gameMode == 3 || g_gameMode == 20) {
      if (g_gameReplayFrame != 0) {
        char timer[0x400];
        sprintf(timer, "%2d.%2d", g_gameReplayFrame / 100,
                g_gameReplayFrame % 100);
        DrawGameText(-0.80000001f, g_gameCameraInputOffsetScale, timer,
                     (SumoS32)0xc0c0c0c0);
      }
    }
  }
  g_gameKeyPressed[c_gameRoundRestartInput] = 0;

  if (g_gameRuntimeMode == 2) {
    DrawGameText(-0.44999999f, 0.2f, g_gameDemoTimeoutText,
                 (SumoS32)0xc0ffffff);
    g_screenTintColor = 0x505050;
    g_gameSimulationPaused = 1;
  }

  RenderGameScene();
  SetGameFpuControlWord();

  if (screenshotRequested) {
    char prefix[] = "sumotori";
    SaveGameScreenshot(prefix, 0);
  }
}
