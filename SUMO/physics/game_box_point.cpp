#include "game_runtime.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(GameBoxPoint, 0x10);

// FUNCTION: SUMO 0x00407dfa
// FUNCTION: EDITOR 0x00407e1c
void GameBoxPoint::SubtractOffset(Vector3& offset)
{
  position.x -= offset.x;
  position.y -= offset.y;
  position.z -= offset.z;
}
