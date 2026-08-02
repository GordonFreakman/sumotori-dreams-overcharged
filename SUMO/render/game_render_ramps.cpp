#include "types.h"

#include <math.h>

extern const SumoF32 g_textureByteMaximumFloat;
extern const SumoF32 g_gameRampBias;
extern const SumoF32 g_gameRampStep32;
extern const SumoF32 g_gameRampStep64;
extern const SumoF64 g_gameRampDecayTwoPercent;
extern const SumoF64 g_gameRampDecayFivePercent;
extern const SumoF64 g_gameRampDecayOnePercent;
extern SumoU32 g_gameTextureScratch[];
extern SumoS32 g_gameRampTexture;
extern SumoS32 g_gameAttenuationTexture;

SumoS32 CreateGameTextureFromPixels(void *, SumoS32, SumoS32, SumoS32);

// FUNCTION: SUMO 0x004156a6
// FUNCTION: EDITOR 0x004156c8
SumoS32 CreateGameRampTexture() {
  SumoS32 remaining = 32;
  SumoF32 red = g_textureByteMaximumFloat;
  SumoF32 green = red;
  SumoF32 blue = green;
  SumoU32 *pixels = g_gameTextureScratch;
  SumoU32 *pixel = pixels;
  SumoF32 redDecay =
      (SumoF32)exp(log(g_gameRampDecayTwoPercent) * g_gameRampStep32);
  SumoF32 greenDecay =
      (SumoF32)exp(log(g_gameRampDecayTwoPercent) * g_gameRampStep32);
  SumoF32 blueDecay =
      (SumoF32)exp(log(g_gameRampDecayTwoPercent) * g_gameRampStep32);

  do {
    SumoS32 packed = (SumoS32)(red - g_gameRampBias);
    packed = (packed << 8) + (SumoS32)(green - g_gameRampBias);
    packed = (packed << 8) + (SumoS32)(blue - g_gameRampBias);
    *pixel++ = packed;

    red *= redDecay;
    green *= greenDecay;
    blue *= blueDecay;
  } while (--remaining != 0);

  return g_gameRampTexture = CreateGameTextureFromPixels(pixels, 32, 1, 1);
}

// FUNCTION: SUMO 0x0041579b
// FUNCTION: EDITOR 0x004157bd
SumoS32 CreateGameAttenuationTexture() {
  SumoS32 row = 0;
  SumoU32 *pixels = g_gameTextureScratch;
  SumoU32 *pixel = pixels;

  do {
    SumoF32 red = g_textureByteMaximumFloat;
    SumoF32 green = red;
    SumoF32 blue = green;
    SumoF32 redDecay =
        (SumoF32)exp(log(g_gameRampDecayOnePercent) * g_gameRampStep64);
    SumoF32 greenDecay =
        (SumoF32)exp(log(g_gameRampDecayTwoPercent) * g_gameRampStep64);
    SumoF32 blueDecay =
        (SumoF32)exp(log(g_gameRampDecayFivePercent) * g_gameRampStep64);

    if (row > 8) {
      SumoF32 previousBlueDecay = blueDecay;
      blueDecay = redDecay;
      greenDecay = previousBlueDecay;
    }

    SumoS32 remaining = 64;
    do {
      SumoS32 packed = (SumoS32)red;
      packed = (packed << 8) + (SumoS32)green;
      packed = (packed << 8) + (SumoS32)blue;
      *pixel++ = packed;

      red *= redDecay;
      green *= greenDecay;
      blue *= blueDecay;
    } while (--remaining != 0);
  } while (++row < 16);

  return g_gameAttenuationTexture =
             CreateGameTextureFromPixels(pixels, 64, 16, 0);
}
