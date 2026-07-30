#include "game_runtime.h"

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
void GameBox::IntegratePhysics()
{
  if (!flag58 && !flagD0) {
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
          if (++sleepCounter > 30) sleeping = true;
        } else {
          sleepCounter = 0;
        }
      }

      if (!sleeping) linearVelocity.y += g_gameGravityStep;
    }
    activityValue *= g_gameActivityDecay;
  }
}
