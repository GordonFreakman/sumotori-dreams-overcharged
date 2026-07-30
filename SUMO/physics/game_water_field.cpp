#include "containers.h"

#include <math.h>

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
void InitializeWaterField()
{
  SumoS32 cellCount = g_waterGridWidth * g_waterGridHeight;
  g_waterBaseHeight = 23.0f;
  g_waterFieldActive = 1;
  g_waterHeights.Resize(cellCount);
  g_waterVelocities.Resize(g_waterGridWidth * g_waterGridHeight);

  for (SumoS32 index = 0;
       index < g_waterGridWidth * g_waterGridHeight;
       ++index) {
    SumoF32 wave = (SumoF32) sin(index * g_randomHalf);
    g_waterHeights[index] = wave * g_waterInitialWaveAmplitude +
                            g_waterBaseHeight;
    g_waterVelocities[index] = 0.0f;
  }
}
