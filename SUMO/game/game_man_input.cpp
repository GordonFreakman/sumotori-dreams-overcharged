#include "types.h"

extern SumoU8 g_gameKeyDown[256];

// FUNCTION: SUMO 0x0040fe79
// FUNCTION: EDITOR 0x0040fe9b
SumoS32 __fastcall ReadGameManInputMask(SumoS32 p_playerIndex) {
  SumoS8 scanCodes[2][8] = {
      {0x4b, 0x4d, 0x48, 0x50, 0x0e, 0x1c},
      {0x1e, 0x20, 0x11, 0x1f, 0x2a, 0x1d},
  };
  SumoS32 flag = 1;
  SumoS32 index = 0;
  SumoS8 *playerScanCodes = scanCodes[p_playerIndex];
  p_playerIndex = 0;
  do {
    if (g_gameKeyDown[playerScanCodes[index]]) {
      p_playerIndex |= flag;
    }
    flag += flag;
    ++index;
  } while (index < 6);
  return p_playerIndex;
}
