#include "game_runtime.h"

extern SumoU8 g_gameBoxLitVertexStorage;
extern SumoU8 g_gameBoxShadowPositionStorage;
extern SumoU8 g_gameBoxIndexPairStorage;
extern SumoU8 g_gameBoxTextureTriangleCounts;

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
