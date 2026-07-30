#include "game_runtime.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(MassAccumulator, 0x10);

// FUNCTION: SUMO 0x004080ea
// FUNCTION: EDITOR 0x0040810c
MassAccumulator::MassAccumulator()
{
  volume = 0.0f;

  Vector3 zero;
  zero.x = 0.0f;
  zero.y = 0.0f;
  zero.z = 0.0f;
  weightedCenter = zero;
}
