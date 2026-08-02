#include "game_runtime.h"

// FUNCTION: SUMO 0x00408684
// FUNCTION: EDITOR 0x004086a6
void ApplyPairedAngularImpulse(GameBox **boxes, Vector3 &impulse) {
  Vector3 opposed = -impulse;
  boxes[0]->ApplyAngularImpulse(opposed, opposed);
  boxes[1]->ApplyAngularImpulse(opposed, impulse);
}
