#include "game_runtime.h"
#include "game_replay.h"

#include "decomp.h"

#include <math.h>
#include <string.h>

#include <windows.h>
#include <mmsystem.h>


void *PlayGameSound(SumoS32 soundIndex, SumoF32 frequencyScale,
                    SumoF32 volumeScale, SumoS32 channel);
SumoS32 CheckStoredGameSettings();
void SetGameCursorVisible(SumoU8 visible);
void StartGameLevelEditor(char *source);
void RestartGameMusic(SumoS32 playbackMode);
void ResetAndSetSceneTransform(Vector3 &position, SumoF32 angle);
typedef void(__cdecl *ResetSceneTransformLegacyCall)(Vector3 &, SumoF32,
                                                     SumoS32);

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

// GLOBAL: EDITOR 0x0042b28c
extern const SumoF32 g_parserMinimumBreakability = 10.0f;

// GLOBAL: EDITOR 0x0042b2b0
extern const SumoF32 g_gameOne = 1.0f;

// GLOBAL: EDITOR 0x0042c2d0
extern const SumoF32 g_gameBoxDefaultValue = 0.0625f;

// GLOBAL: EDITOR 0x0042c724
extern const SumoF32 g_cutPlaneFloor = -1000.0f;

// GLOBAL: EDITOR 0x0042c630
static const SumoF32 g_randomHalf = 0.5f;

SumoS32 InitializeGameRuntimeState();

// GLOBAL: EDITOR 0x0042c9b8
extern const SumoF32 g_gameManEventVolume = 0.75f;

// GLOBAL: EDITOR 0x0042c9bc
extern const SumoF32 g_gameAiPushDistanceThreshold = 7.5f;

// GLOBAL: EDITOR 0x0042c9c0
extern const SumoF32 g_gameAiForwardDistanceSquaredLimit = 64.0f;

// GLOBAL: EDITOR 0x0042c9c4
extern const SumoF32 g_gameAiVelocityProjectionScale = 50.0f;

// GLOBAL: EDITOR 0x0042c9c8
extern const SumoF32 g_gameAiStateScale = 0.0015384615f;

// GLOBAL: EDITOR 0x0042c9cc
extern const SumoF32 g_gameAiLateralRecoveryThreshold = -2.0f;

// GLOBAL: EDITOR 0x0042c9d0
extern const SumoF32 g_gameAiMotionSquaredLimit = 16.0f;

// GLOBAL: EDITOR 0x0042c9d4
extern const SumoF32 g_gameAiStabilitySquaredLimit = 0.040000001f;

// GLOBAL: EDITOR 0x0042c9d8
extern const SumoF32 g_gameAiOpponentMotionSquaredLimit = 25.0f;

extern const SumoF32 g_gameProjectileDefaultValue;
extern const SumoF32 g_gameRampStep32;
extern const SumoF32 g_boxWaterDiagonalScale;
extern const SumoF32 g_gameTwo;

// GLOBAL: EDITOR 0x0042c770
extern const SumoF32 g_waterMotionThreshold = 0.00001f;

// GLOBAL: EDITOR 0x0042c788
extern const SumoF32 g_gameArenaHalfExtent = 31.0f;

// GLOBAL: EDITOR 0x0042c960
extern const SumoF32 g_gameWallSegmentSpacing = 18.0f;

extern const SumoF32 g_gameFloorHalfExtent;

// GLOBAL: EDITOR 0x0042c9dc
extern const SumoF32 g_gameRimTiltAngle = -0.78539819f;

// GLOBAL: EDITOR 0x0042c9e0
extern const SumoF32 g_gameRimAngleStep = 0.2026834f;

// GLOBAL: EDITOR 0x0042c9e4
extern const SumoF32 g_gameWallCenterSegment = 2.5f;

// GLOBAL: EDITOR 0x0042c9e8
extern const SumoF32 g_gameWallQuarterTurn = 1.5707964f;

// GLOBAL: EDITOR 0x0042c9ec
extern const SumoF32 g_gameArenaLowerPointScale = 1.1548387f;

extern const SumoF32 g_gameArenaVerticalHalfSize;

// GLOBAL: EDITOR 0x00453cd0
SumoF32 g_gameSimulationStep = 1.0f;

// GLOBAL: EDITOR 0x005aec40
SumoF32 g_gameInverseSimulationStep;

// GLOBAL: EDITOR 0x00467b6c
GameBox *g_currentBox = 0;

// GLOBAL: EDITOR 0x00531220
extern GameBox g_cutPlaneBox;

// GLOBAL: EDITOR 0x00531320
extern GameBox g_clipScratchBox;

// GLOBAL: EDITOR 0x00746c50
extern GameBox g_gameBoxes[512];

// GLOBAL: EDITOR 0x004536e4
GameBox *g_gameBoxesLimit = g_gameBoxes + 512;

// GLOBAL: EDITOR 0x00561428
extern GameBox *g_gameBoxesEnd;

// GLOBAL: EDITOR 0x00521e20
extern SumoU8 g_gameContactObjects[0xf400];

// GLOBAL: EDITOR 0x00561424
extern SumoU8 *g_gameContactObjectsEnd;

// GLOBAL: EDITOR 0x00561430
extern SumoU8 g_gameContactLinks[0x1800];

// GLOBAL: EDITOR 0x0056142c
extern SumoU8 *g_gameContactLinksEnd;

// GLOBAL: EDITOR 0x00766458
extern GameRandomGenerator g_gameRandom;

// GLOBAL: EDITOR 0x00c069a8
GameRandomGenerator g_simulationRandom;

// GLOBAL: EDITOR 0x00c06b80
extern GameMan g_gameMen[4];

// GLOBAL: EDITOR 0x00c08840
extern SumoU8 g_gameMenEnd;

// GLOBAL: EDITOR 0x00453858
GameMan *g_nextGameMan = g_gameMen;

// GLOBAL: EDITOR 0x00453cd8
SumoS32 g_gameIsRunning = 1;

// GLOBAL: EDITOR 0x00ac6714
SumoU32 g_screenTintColor;

// GLOBAL: EDITOR 0x00c06998
SumoS32 g_screenTintLevel;

// GLOBAL: EDITOR 0x004e7bd0
SumoU32 g_pendingManCount = 0;

// GLOBAL: EDITOR 0x00c06b60
SumoS32 g_levelLoadState[8];

// GLOBAL: EDITOR 0x00467b70
Vector3 g_pendingManPositions[9];

// GLOBAL: EDITOR 0x004e7bd4
SumoF32 g_pendingManAngles[9];

// GLOBAL: EDITOR 0x00c0a504
SumoS32 g_gameManUpdateCounter;

// GLOBAL: EDITOR 0x00c0a500
SumoF32 g_unk0x00c09ce0;

// GLOBAL: EDITOR 0x00c069a4
SumoS32 g_gameRuntimeMode;

// GLOBAL: EDITOR 0x004535f8
SumoS32 g_gamePlayerCount = 3;

// GLOBAL: EDITOR 0x00453600
char g_gameMenuWarningText[] =
    "WARNING: The characters in the game were performed by\n"
    "trained professionals!!! Do not try this at home!!!\n \n"
    "Rules: When you hit the ground, you loose\n"
    "winner is the one, who stays on feet for the longest\n";

// GLOBAL: EDITOR 0x004eaca0
SumoS32 g_gameHumanPlayerCount;

// GLOBAL: EDITOR 0x00c069a0
SumoS32 g_gameResetScores;

// GLOBAL: EDITOR 0x00c06b48
SumoS32 g_gameScores[2];

// GLOBAL: EDITOR 0x00c06b5c
SumoS32 g_gameRoundPlayerCount;

// GLOBAL: EDITOR 0x0045385c
SumoF32 g_gameDecorationHeight = 27.0f;

// GLOBAL: EDITOR 0x004eac9c
SumoS32 __declspec(align(16)) g_gameMenuPage;

// GLOBAL: EDITOR 0x004eac98
SumoS32 g_gameMenuTransitionTicks;

// GLOBAL: EDITOR 0x004eaca4
SumoS32 g_gameMenuAlternateLayout;

// GLOBAL: EDITOR 0x00453860
SumoU8 g_gameUsesScriptedArena = 1;

// GLOBAL: EDITOR 0x004eaca8
SumoU8 g_gameLevelEditorActive;

// GLOBAL: EDITOR 0x004eac94
SumoS32 g_gameProjectileCooldown;

// GLOBAL: EDITOR 0x00766454
SumoS32 g_gameSkipPhysicsStep;

// GLOBAL: EDITOR 0x004536e8
SumoU8 g_gameCollisionPassActive = 1;

// GLOBAL: EDITOR 0x00746c48
SumoU8 g_gameBoxesInitialized;

// GLOBAL: EDITOR 0x00511e0c
SumoS32 g_gameSimulationTick;

// GLOBAL: EDITOR 0x00562c30
extern SumoS32 g_gameMenuSelection;

DECOMP_SIZE_ASSERT(GameBoxJoint, 0xf4);

static __forceinline void AddGameMenuConstraint(
    GameBox *first, GameBox *second, const Vector3 &firstAnchor,
    const Vector3 &secondAnchor, const Vector3 &firstDirection,
    const Vector3 &secondAnchorDirection, const Vector3 &secondDirection,
    const Vector3 &secondAxis, const Vector3 *firstDirectionOverride,
    SumoF32 minimumAngle) {
  ((GameBoxJoint *)g_gameContactObjectsEnd)->boxes[0] = first;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->localAnchors[0] = firstAnchor;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->firstPoseDirection =
      firstDirection;
  if (firstDirectionOverride != 0) {
    ((GameBoxJoint *)g_gameContactObjectsEnd)->firstPoseDirection =
        *firstDirectionOverride;
  }
  ((GameBoxJoint *)g_gameContactObjectsEnd)->secondPoseDirection =
      secondDirection;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->boxes[1] = g_gameBoxesEnd - 1;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->localAnchors[1] = secondAnchor;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->secondAnchorDirection =
      secondAnchorDirection;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->secondAxis = secondAxis;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->minimumAngle = minimumAngle;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->maximumAngle = 1.21f;
  ((GameBoxJoint *)g_gameContactObjectsEnd)->state = 0.0f;
  g_gameContactObjectsEnd += sizeof(GameBoxJoint);
}

static __forceinline Vector3 MakeGameRuntimeVector3(SumoF32 x, SumoF32 y,
                                                    SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

// FUNCTION: EDITOR 0x0040778f
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

// FUNCTION: EDITOR 0x0040795f
void UpdateGameMenuScreen(SumoU8 drawOverlay) {
  if (g_gameBoxesEnd > g_gameBoxes + 200) {
    InitializeGameRuntimeState();
  }

  if (g_gameMenuSelection != 0) {
    g_gameMenuTransitionTicks -= 2;
    if (g_gameMenuTransitionTicks <= 0) {
      switch (g_gameMenuPage) {
      case 1:
        g_externalLevelScriptOverride = 0;
        g_gameMenuPage = 0;
        g_selectedLevelScript =
            g_gameMenuSelection % 16 + 4 * (g_gameMenuSelection / 16) - 1;
        InitializeGameRuntimeState();
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
        case 35:
          g_gameLevelEditorCloseRequested = 1;
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
    g_gameLevelEditorCloseRequested = 1;
  }

  if (drawOverlay) {
    if (g_gameMenuPage == 3) {
      DrawGameText(-0.85000002f, g_inertiaRadiusScale, g_gameMenuWarningText,
                   0xc0ffffff);
      g_screenTintColor =
          (0x007f007f & ((SumoS32)g_screenTintColor / 2)) +
          ((3 * ((SumoS32)g_screenTintColor & 0xff00) / 4) & 0xff00);
    }
    DrawGameText(-0.2f, 0.56f, "Sumotori Dreams Full", 0xc08080ff);
    DrawGameText(0.27000001f, g_gameNegativeHalf, "\"Tested on party animals\"",
                 0xc0ffffff);
    DrawGameText(-0.85000002f, g_gameNegativeHalf,
                 "www.gravitysensation.com/sumotori", 0xc0ffffff);
  }
}

// FUNCTION: EDITOR 0x00407dd8
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

// FUNCTION: EDITOR 0x00407e0c
void RefreshScreenTint() { UpdateScreenTint(g_screenTintLevel * 8); }

// FUNCTION: EDITOR 0x00409679
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

// FUNCTION: EDITOR 0x0040b5f7
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
  if (g_gameMode >= 2) {
    ApplyWaterInteractionToMovingBoxes();
  }
  UpdateGameReplay();
  UpdateWaterField();
  ++g_gameSimulationTick;
}

// FUNCTION: EDITOR 0x0040b685
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

// FUNCTION: EDITOR 0x0040b829
GameRandomGenerator::GameRandomGenerator() { Initialize(0x4641, 0x535a); }

// FUNCTION: EDITOR 0x0040e188
void InitializeRandomFromClock() {
  SumoS32 milliseconds = timeGetTime();
  g_simulationRandom.Initialize(milliseconds & 0x3fff,
                                ((milliseconds >> 8) + 1000) & 0x3fff);
}

// FUNCTION: EDITOR 0x0040e1af
SumoS32 StartGameRuntime() {
  InitializeRandomFromClock();
  ResetSceneTransform();
  InitializeGameTextures();
  InitializeGameVertexBuffers();
  InitializeClipBoxes();
  ResetGameRoundState();
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

// FUNCTION: EDITOR 0x0040fd42
void ApplyGameManPoseConstraints() {
  GameMan *man = g_gameMen;
  while (man < g_nextGameMan) {
    man->Render((SumoU8 *)man + 0x14c);
    ++man;
  }
}

// FUNCTION: EDITOR 0x0040ff13
void SetGameManAudioState(GameMan *man, SumoS32 channel) {
  man->state144 &= 0;
  man->active = 8;
  PlayGameSound(5, 1.0f, g_gameManEventVolume, channel ^ 3);
}

// FUNCTION: EDITOR 0x00410885
GameMan *CreateGameMen() {
  SumoS32 playerCount = g_gamePlayerCount;
  SumoS32 humanCount = g_gameHumanPlayerCount;
  if (g_gameResetScores) {
    g_gameScores[0] = 0;
    g_gameScores[1] = 0;
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
                            (SumoS32)(g_gameMen + opponentIndex));
      next->active = 4;
      if (g_levelLoadState[4] == 11)
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

// FUNCTION: EDITOR 0x00410a7e
void StartGameRound() {
  SetGameCursorVisible(0);
  g_gameEditorControlMode = 4;
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

  CreateGameMen();
  RefreshGameContactLists();
}

// FUNCTION: EDITOR 0x00414edb
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
