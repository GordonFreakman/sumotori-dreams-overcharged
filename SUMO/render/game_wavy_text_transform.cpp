#include "containers.h"

#include <math.h>

extern Matrix3 g_gameInverseViewMatrix;
extern SumoS32 g_screenTintLevel;

static const SumoF32 g_parserMinimumBreakability = 10.0f;

// GLOBAL: SUMO 0x00c06148
// GLOBAL: EDITOR 0x00c06968
Vector3 g_gameCameraWorldPosition;

// GLOBAL: SUMO 0x0042b2fc
// GLOBAL: EDITOR 0x0042b2fc
extern const SumoF32 g_wavyTextTimeScale = 0.02f;

// GLOBAL: SUMO 0x0042b2e4
// GLOBAL: EDITOR 0x0042b2e4
extern const SumoF32 g_wavyTextCosineRate = 1.37f;

// GLOBAL: SUMO 0x0042c77c
// GLOBAL: EDITOR 0x0042c77c
extern const SumoF32 g_wavyTextSineRate = 1.77f;

// GLOBAL: SUMO 0x0042b304
// GLOBAL: EDITOR 0x0042b304
extern const SumoF32 g_wavyTextPhaseScale = 1.1f;

// GLOBAL: SUMO 0x0042c778
// GLOBAL: EDITOR 0x0042c778
extern const SumoF32 g_wavyTextDisplacement = 0.004f;
