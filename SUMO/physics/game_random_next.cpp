#include "game_runtime.h"

extern const SumoF32 g_gameOne;

// FUNCTION: SUMO 0x0040b776
// FUNCTION: EDITOR 0x0040b798
SumoF32 GameRandomGenerator::Next() {
  SumoF32 value = values[firstIndex] - values[secondIndex];
  if (value < g_vectorZero) {
    value += g_gameOne;
  }
  values[firstIndex] = value;

  if (--firstIndex == 0) {
    firstIndex = 97;
  }
  if (--secondIndex == 0) {
    secondIndex = 97;
  }

  carry = carry - decrement;
  if (carry < g_vectorZero) {
    carry += modulus;
  }

  value = value - carry;
  if (value < g_vectorZero) {
    value += g_gameOne;
  }
  return value;
}
