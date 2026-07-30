#include "game_runtime.h"

#include "decomp.h"

extern SumoF32 g_gameGravityStep;

DECOMP_SIZE_ASSERT(GameBoxContactLink, 0x0c);
DECOMP_SIZE_ASSERT(GameCollisionFeatureLink, 0xcc);
DECOMP_SIZE_ASSERT(GameCollisionPointRecord, 0x60);
DECOMP_SIZE_ASSERT(GameCollisionCorrectionRecord, 0x20);

// GLOBAL: SUMO 0x00511600
// GLOBAL: EDITOR 0x00511e20
extern GameCollisionCorrectionRecord g_gameCollisionCorrections[2048];

// GLOBAL: SUMO 0x00530c00
// GLOBAL: EDITOR 0x00531420
extern GameCollisionPointRecord g_gameCollisionPoints[2048];

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
  return (SumoU32)g_gameCollisionCorrections +
         (SumoU32)g_gameCollisionPoints +
         (SumoU32)g_gameCollisionCorrectionsEnd +
         (SumoU32)g_gameCollisionPointsEnd +
         (SumoU32)g_gameCollisionFeatureLinks +
         (SumoU32)g_gameCollisionFeatureLinksEnd +
         (SumoU32)&g_gameCollisionGroupSentinel;
}
