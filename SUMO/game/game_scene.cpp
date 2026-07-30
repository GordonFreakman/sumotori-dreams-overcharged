#include "containers.h"
#include "game_input.h"
#include "game_runtime.h"

#include <math.h>
#include <stdio.h>

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
