#include "decomp_keywords.h"
#include "types.h"
#include "containers.h"
#include "sumo_portable.h"
#include "runtime.h"
#include "input.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

SumoU32 g_gameTextureScratch[4194304];

enum { c_renderVertexScratchSize = 0x250120 };

// GLOBAL: SUMO 0x009b5ee0
// GLOBAL: EDITOR 0x009b6700
SumoU8 g_renderVertexScratch[c_renderVertexScratchSize];

SumoIntPtr g_gameTextures[256];

extern "C" SumoIntPtr g_gameTexturesEnd;
extern "C" SumoIntPtr g_gameTexturesOddEnd;
SumoIntPtr g_gameTexturesEnd;
SumoIntPtr g_gameTexturesOddEnd;

// GLOBAL: SUMO 0x0044eae0
// GLOBAL: EDITOR 0x0044eae0
SumoU8 g_textureProgram_LightWoodHeight[211] = {
    0x41, 0x54, 0x47, 0x17, 0x03, 0x00, 0x00, 0x2b, 0x57, 0x19, 0x15, 0xd2,
    0xc1, 0x03, 0x00, 0x00, 0x2b, 0xb0, 0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00,
    0x00, 0x2b, 0xce, 0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00, 0x00, 0x2b, 0xda,
    0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00, 0x00, 0x2b, 0xff, 0x19, 0x15, 0xd2,
    0xc1, 0x01, 0x01, 0x01, 0x00, 0x19, 0x15, 0xd2, 0xc1, 0x00, 0x01, 0x01,
    0x00, 0x00, 0x19, 0x15, 0xd2, 0xc1, 0x00, 0x01, 0x01, 0x00, 0x00, 0xfb,
    0x8b, 0x1c, 0x0e, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x25, 0x00,
    0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
};
// GLOBAL: SUMO 0x0044ebc0
// GLOBAL: EDITOR 0x0044ebc0
SumoU8 g_textureProgram_LightWood[229] = {
    0x41, 0x54, 0x47, 0x19, 0x03, 0x00, 0x00, 0x2b, 0x57, 0x19, 0x15, 0xd2,
    0xc1, 0x03, 0x00, 0x00, 0x2b, 0xb0, 0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00,
    0x00, 0x2b, 0xce, 0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00, 0x00, 0x2b, 0xda,
    0x19, 0x15, 0xd2, 0xc1, 0x03, 0x00, 0x00, 0x2b, 0xff, 0x19, 0x15, 0xd2,
    0xc1, 0x01, 0x01, 0x01, 0x00, 0x19, 0x15, 0xd2, 0xc1, 0x00, 0x01, 0x01,
    0x00, 0x00, 0x19, 0x15, 0xd2, 0xc1, 0x00, 0x01, 0x01, 0x00, 0x00, 0xfb,
    0x8b, 0x1c, 0x0e, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xfe, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xfe, 0x00, 0x25, 0x00,
    0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x0a, 0x00, 0x03, 0x03, 0x04,
    0x04, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0xff, 0xff, 0x7f, 0xde, 0x00,
    0x76,
};
// GLOBAL: SUMO 0x0044f4b0
// GLOBAL: EDITOR 0x0044f4b0
SumoU8 g_textureProgram_DarkWoodHeight[148] = {
    0x41, 0x54, 0x47, 0x10, 0x01, 0x01, 0x00, 0x00, 0x04, 0xc2, 0x2b, 0x01,
    0x00, 0x01, 0x01, 0x01, 0x00, 0x1c, 0x4d, 0x3c, 0xa3, 0x00, 0x03, 0x00,
    0x00, 0x0e, 0x4d, 0x00, 0x92, 0x1b, 0x70, 0x11, 0x00, 0x01, 0x00, 0xba,
    0x01, 0x01, 0xbc, 0x00, 0x11, 0x00, 0x01, 0x00, 0xba, 0x01, 0x01, 0xbc,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xba, 0x01, 0x01, 0xbc, 0x00, 0x11, 0x00,
    0x01, 0x00, 0x58, 0x01, 0x01, 0x4b, 0x00, 0x11, 0x00, 0x01, 0x00, 0x58,
    0x01, 0x01, 0x4b, 0x00, 0x01, 0x01, 0x00, 0x00, 0x04, 0x52, 0x42, 0xc4,
    0x00, 0x01, 0x01, 0x01, 0x00, 0x1b, 0xdd, 0x48, 0xe2, 0x00, 0x11, 0x00,
    0x01, 0x00, 0xc6, 0x01, 0x01, 0xc9, 0x00, 0x11, 0x00, 0x01, 0x00, 0xc6,
    0x01, 0x01, 0xc9, 0x00, 0x11, 0x00, 0x01, 0x00, 0xc6, 0x01, 0x01, 0xc9,
    0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x21, 0x00,
    0xac, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x4f, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
// GLOBAL: SUMO 0x0044e830
// GLOBAL: EDITOR 0x0044e830
SumoU8 g_textureProgram_DarkWood[211] = {
    0x41, 0x54, 0x47, 0x17, 0x01, 0x01, 0x00, 0x00, 0x04, 0xc2, 0x2b, 0x01,
    0x00, 0x01, 0x01, 0x01, 0x00, 0x1c, 0x4d, 0x3c, 0xa3, 0x00, 0x03, 0x00,
    0x00, 0x0e, 0x4d, 0x00, 0x92, 0x1b, 0x70, 0x11, 0x00, 0x01, 0x00, 0xba,
    0x01, 0x01, 0xbc, 0x00, 0x11, 0x00, 0x01, 0x00, 0xba, 0x01, 0x01, 0xbc,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xba, 0x01, 0x01, 0xbc, 0x00, 0x11, 0x00,
    0x01, 0x00, 0x58, 0x01, 0x01, 0x4b, 0x00, 0x11, 0x00, 0x01, 0x00, 0x58,
    0x01, 0x01, 0x4b, 0x00, 0x01, 0x01, 0x00, 0x00, 0x04, 0x52, 0x42, 0xc4,
    0x00, 0x01, 0x01, 0x01, 0x00, 0x1b, 0xdd, 0x48, 0xe2, 0x00, 0x05, 0x00,
    0x01, 0x20, 0x37, 0x26, 0xe5, 0x41, 0x00, 0x11, 0x00, 0x01, 0x00, 0xc6,
    0x01, 0x01, 0xc9, 0x00, 0x11, 0x00, 0x01, 0x00, 0xc6, 0x01, 0x01, 0xc9,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xc6, 0x01, 0x01, 0xc9, 0x00, 0x17, 0x02,
    0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x25, 0x02, 0x01, 0x4a, 0x4b,
    0x48, 0xa8, 0x41, 0x44, 0x17, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x24, 0x00, 0xed, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0xd2, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x01, 0x00, 0x8b, 0x00, 0x00, 0x00,
    0x00, 0x23, 0x00, 0x02, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00,
    0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// GLOBAL: SUMO 0x0044ecb0
// GLOBAL: EDITOR 0x0044ecb0
SumoU8 g_textureProgram_DiamondHeight[157] = {
    0x41, 0x54, 0x47, 0x11, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x21, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x25, 0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x19, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02,
    0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x6b, 0xff, 0xff,
    0x00, 0x25, 0x02, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x17, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x01, 0x02, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00,
    0x00,
};
// GLOBAL: SUMO 0x0044ed50
// GLOBAL: EDITOR 0x0044ed50
SumoU8 g_textureProgram_BlueDiamond[121] = {
    0x41, 0x54, 0x47, 0x0d, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x21, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x17, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25,
    0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0xb1, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0x81, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x25, 0x00, 0x00, 0x0f, 0x34, 0x62, 0xc4, 0xff, 0xbe,
};
// GLOBAL: SUMO 0x0044edd0
// GLOBAL: EDITOR 0x0044edd0
SumoU8 g_textureProgram_WhiteDiamond[112] = {
    0x41, 0x54, 0x47, 0x0c, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x21, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x25, 0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x19, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02,
    0xb1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0xc1, 0xff,
    0xc3, 0xff, 0xc1, 0xff,
};
// GLOBAL: SUMO 0x0044e7c0
// GLOBAL: EDITOR 0x0044e7c0
SumoU8 g_textureProgram_BlueWoodHeight[112] = {
    0x41, 0x54, 0x47, 0x0c, 0x01, 0x00, 0x00, 0x00, 0xa2, 0x07, 0x19, 0x8c,
    0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x05, 0x01,
    0x00, 0x10, 0xa2, 0x07, 0x19, 0x8c, 0x00, 0x05, 0x01, 0x01, 0x10, 0xcc,
    0xf8, 0x61, 0x87, 0x00, 0x11, 0x00, 0x01, 0x00, 0x50, 0x01, 0x01, 0x52,
    0x00, 0x01, 0x01, 0x00, 0x00, 0xd1, 0x0c, 0xa0, 0x53, 0x00, 0x01, 0x01,
    0x01, 0x00, 0x39, 0x8e, 0x03, 0xe7, 0x00, 0x11, 0x00, 0x01, 0x00, 0xbb,
    0x01, 0x01, 0xc0, 0x00, 0x11, 0x00, 0x01, 0x00, 0xbb, 0x01, 0x01, 0xc0,
    0x00, 0x0a, 0x00, 0x03, 0x01, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00,
    0x00, 0x00, 0x31, 0x00, 0x01, 0x2b, 0x00, 0x25, 0x00, 0x00, 0x85, 0xff,
    0x81, 0xff, 0x83, 0xff,
};
// GLOBAL: SUMO 0x0044e740
// GLOBAL: EDITOR 0x0044e740
SumoU8 g_textureProgram_BlueWood[121] = {
    0x41, 0x54, 0x47, 0x0d, 0x01, 0x00, 0x00, 0x00, 0xa2, 0x07, 0x19,
    0x8c, 0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
    0x05, 0x01, 0x00, 0x10, 0xa2, 0x07, 0x19, 0x8c, 0x00, 0x05, 0x01,
    0x01, 0x10, 0xcc, 0xf8, 0x61, 0x87, 0x00, 0x11, 0x00, 0x01, 0x00,
    0x50, 0x01, 0x01, 0x52, 0x00, 0x01, 0x01, 0x00, 0x00, 0xd1, 0x0c,
    0xa0, 0x53, 0x00, 0x01, 0x01, 0x01, 0x00, 0x39, 0x8e, 0x03, 0xe7,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xbb, 0x01, 0x01, 0xc0, 0x00, 0x11,
    0x00, 0x01, 0x00, 0xbb, 0x01, 0x01, 0xc0, 0x00, 0x0a, 0x00, 0x03,
    0x01, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x31,
    0x00, 0x01, 0x2b, 0x00, 0x11, 0x00, 0x00, 0x00, 0x31, 0x00, 0x01,
    0x2b, 0x00, 0x25, 0x00, 0x00, 0x86, 0x8f, 0x9b, 0xf4, 0xcf, 0xff,
};
// GLOBAL: SUMO 0x0044ee40
// GLOBAL: EDITOR 0x0044ee40
SumoU8 g_textureProgram_GreenDiamond[121] = {
    0x41, 0x54, 0x47, 0x0d, 0x02, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x21, 0x00, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x17, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25,
    0x02, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x02, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0xb1, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0x81, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x97, 0xc0, 0xff, 0x00, 0x00,
};
// GLOBAL: SUMO 0x0044e9f0
// GLOBAL: EDITOR 0x0044e9f0
SumoU8 g_textureProgram_PaintHeight[67] = {
    0x41, 0x54, 0x47, 0x07, 0x03, 0x00, 0x00, 0x0e, 0x64, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x00, 0x00, 0x00, 0xea, 0x21, 0xa6, 0x00, 0x01, 0x02, 0x01, 0x00, 0x04,
    0xaa, 0x4b, 0x30, 0x00, 0x11, 0x00, 0x02, 0x00, 0xba, 0x02, 0x00, 0xb7,
    0x00, 0x11, 0x00, 0x02, 0x00, 0xba, 0x02, 0x00, 0xb7, 0x00, 0x25, 0x00,
    0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
};
// GLOBAL: SUMO 0x0044f550
// GLOBAL: EDITOR 0x0044f550
SumoU8 g_textureProgram_Paint[103] = {
    0x41, 0x54, 0x47, 0x0b, 0x01, 0x00, 0x00, 0x00, 0xa2, 0x07, 0x19, 0x8c,
    0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x05, 0x01,
    0x00, 0x10, 0xa2, 0x07, 0x19, 0x8c, 0x00, 0x05, 0x01, 0x01, 0x10, 0xcc,
    0xf8, 0x61, 0x87, 0x00, 0x11, 0x00, 0x01, 0x00, 0x50, 0x01, 0x01, 0x52,
    0x00, 0x01, 0x01, 0x00, 0x00, 0xd1, 0x0c, 0xa0, 0x53, 0x00, 0x01, 0x01,
    0x01, 0x00, 0x39, 0x8e, 0x03, 0xe7, 0x00, 0x11, 0x00, 0x01, 0x00, 0xbb,
    0x01, 0x01, 0xc0, 0x00, 0x11, 0x00, 0x01, 0x00, 0xbb, 0x01, 0x01, 0xc0,
    0x00, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00,
    0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// GLOBAL: SUMO 0x0044e520
// GLOBAL: EDITOR 0x0044e520
SumoU8 g_textureProgram_Lava[139] = {
    0x41, 0x54, 0x47, 0x0f, 0x05, 0x00, 0x00, 0x08, 0xc1, 0xaf, 0xde, 0x2e,
    0x00, 0x05, 0x00, 0x01, 0x08, 0xa2, 0x07, 0x19, 0x8c, 0x00, 0x03, 0x02,
    0x00, 0x16, 0x62, 0xa2, 0x07, 0x19, 0x8c, 0x11, 0x02, 0x00, 0x00, 0x1f,
    0x00, 0x01, 0x1b, 0x00, 0x25, 0x02, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00,
    0xff, 0x17, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x01,
    0x00, 0xff, 0xff, 0xff, 0x22, 0x00, 0x10, 0x27, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x21, 0x02, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x27, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x02,
    0x01, 0x88, 0xff, 0x00, 0x00, 0x00, 0x00, 0x23, 0x02, 0x00, 0x88, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x19, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x17, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x00,
    0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
};

SumoU8 g_textureProgram_Silk[103] = {
    0x41, 0x54, 0x47, 0x0b, 0x02, 0x00, 0x03, 0x03, 0x18, 0x28, 0x00, 0x00,
    0x00, 0x0a, 0x00, 0x02, 0x01, 0x1e, 0x40, 0x2f, 0x00, 0x00, 0x17, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x02, 0x00, 0xa2, 0x67,
    0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0xd9, 0x36, 0xa6, 0x2e, 0xad,
    0x4e, 0x11, 0x02, 0x00, 0x00, 0x20, 0x02, 0x00, 0x2f, 0x00, 0x12, 0x00,
    0x02, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x24, 0x02, 0xa7, 0xfe, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x02, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
    0x02, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00};

SumoU8 g_textureProgram_SilkHeight[121] = {
    0x41, 0x54, 0x47, 0x0d, 0x02, 0x00, 0x03, 0x03, 0x18, 0x28, 0x00,
    0x00, 0x00, 0x0a, 0x00, 0x02, 0x01, 0x1e, 0x40, 0x2f, 0x00, 0x00,
    0x17, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x02,
    0x00, 0xa2, 0x67, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0xd9,
    0x36, 0xa6, 0x2e, 0xad, 0x4e, 0x11, 0x02, 0x00, 0x00, 0x20, 0x02,
    0x00, 0x2f, 0x00, 0x12, 0x00, 0x02, 0x00, 0x1b, 0x00, 0x00, 0x00,
    0x00, 0x1e, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
    0x02, 0xa7, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0x4d,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x14, 0x02, 0x01, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x14, 0x02, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00};

SumoU8 g_textureProgram_RedWoodHeight[] = {
    0x41, 0x54, 0x47, 0x09, 0x01, 0x00, 0x00, 0x00, 0x11, 0xdb, 0x7e,
    0xad, 0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
    0x05, 0x01, 0x00, 0x10, 0xd9, 0x1d, 0x5c, 0x6a, 0x00, 0x05, 0x01,
    0x01, 0x10, 0xfb, 0x12, 0x5f, 0x5b, 0x00, 0x11, 0x00, 0x01, 0x00,
    0x50, 0x01, 0x01, 0x4f, 0x00, 0x01, 0x01, 0x00, 0x00, 0x7f, 0xe2,
    0xfa, 0xba, 0x00, 0x01, 0x01, 0x01, 0x00, 0x53, 0x13, 0x92, 0x91,
    0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xff, 0x00, 0x11,
    0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xff, 0x00};

SumoU8 g_textureProgram_RedWood[] = {
    0x41, 0x54, 0x47, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x11, 0xdb, 0x7e, 0xad,
    0x00, 0x25, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x05, 0x01,
    0x00, 0x10, 0xd9, 0x1d, 0x5c, 0x6a, 0x00, 0x05, 0x01, 0x01, 0x10, 0xfb,
    0x12, 0x5f, 0x5b, 0x00, 0x11, 0x00, 0x01, 0x00, 0x50, 0x01, 0x01, 0x4f,
    0x00, 0x01, 0x01, 0x00, 0x00, 0x7f, 0xe2, 0xfa, 0xba, 0x00, 0x01, 0x01,
    0x01, 0x00, 0x53, 0x13, 0x92, 0x91, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff,
    0x01, 0x01, 0xff, 0x00, 0x11, 0x00, 0x01, 0x00, 0xff, 0x01, 0x01, 0xff,
    0x00, 0x25, 0x00, 0x00, 0xf7, 0xb9, 0x6b, 0x2c, 0x48, 0x09};

// GLOBAL: SUMO 0x00453890
// GLOBAL: EDITOR 0x00453890
SumoU8 *g_gameTexturePrograms[] = 
{
    // normal map,                          diffuse map
    g_textureProgram_LightWoodHeight,       g_textureProgram_LightWood, 
    g_textureProgram_DarkWoodHeight,        g_textureProgram_DarkWood, 
    g_textureProgram_DiamondHeight,         g_textureProgram_BlueDiamond,
    g_textureProgram_DiamondHeight,         g_textureProgram_WhiteDiamond, 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, 
    g_textureProgram_SilkHeight,            g_textureProgram_Silk, // TODO: replace with something unique?
    g_textureProgram_RedWoodHeight,         g_textureProgram_RedWood, //TODO: replace with something unique? 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, //TODO: replace with something unique?
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, //TODO: replace with something unique?
    g_textureProgram_DiamondHeight,         g_textureProgram_GreenDiamond, 
    g_textureProgram_PaintHeight,           g_textureProgram_Paint, 
    g_textureProgram_PaintHeight,           g_textureProgram_Lava,

    // game menu texture programs, if you change the amount of in-game textures change MENU_START_INDEX!!!!
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood,
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood,
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood,
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood, 
    g_textureProgram_BlueWoodHeight,        g_textureProgram_BlueWood,
    0
};

// GLOBAL: SUMO 0x004538f0
// GLOBAL: EDITOR 0x004538f0
char g_gameMenuLabels[7][7][24] = {
    {"2 players duel", "2 players & 1 comp.", "2 player & 2 comp.",
     "4 computers", "", "", ""},
    {"You vs. Computer", "You and 2 comp.", "You & 3 comp.", "2 Computers", "",
     "", ""},
    {"Arena selection", "AI mode: walk", "AI mode: stand", "Gamemodes", "Documentation", "Quit", ""},
    {"Default dojo", "Kitchen party", "Roof dancers", "play seesaw", "", "",
     ""},
    {"Up on the stage", "I go downstairs", "", "", "", "", ""},
    {"Default mode", "Water mode", "Breakable guys", "Classic mode", "The abyss...", "", ""},
    {"Hidden part.", "You and.. uhhhh", " ", " ", " ", "OK", ""},
};

// GLOBAL: SUMO 0x0042cb50
// GLOBAL: EDITOR 0x0042cb50
char g_gameTimesFont[] = "Times New Roman";

// GLOBAL: SUMO 0x0042c5bc
// GLOBAL: EDITOR 0x0042c5bc
char g_gameConsoleFont[] = "Lucida Console";

// GLOBAL: SUMO 0x00c0ea30
// GLOBAL: EDITOR 0x00c0f250
extern SumoIntPtr g_gameTextures[256];

extern "C" SumoIntPtr g_gameTexturesEnd;

extern "C" SumoIntPtr g_gameTexturesOddEnd;

// GLOBAL: SUMO 0x00c0ea2c
// GLOBAL: EDITOR 0x00c0f24c
SumoIntPtr g_gameFontAtlasTexture;

extern Matrix3 g_gameInverseViewMatrix;
extern SumoS32 g_screenTintLevel;

// GLOBAL: SUMO 0x00c06148
// GLOBAL: EDITOR 0x00c06968
Vector3 g_gameCameraWorldPosition;

// GLOBAL: SUMO 0x0042b2fc
// GLOBAL: EDITOR 0x0042b2fc
extern const SumoF32 g_wavyTextTimeScale = 0.02f;

// GLOBAL: SUMO 0x0042b2e4
// GLOBAL: EDITOR 0x0042b2e4
extern const SumoF32 g_wavyTextCosineRate = 1.37f;

// GLOBAL: SUMO 0x0042c77c
// GLOBAL: EDITOR 0x0042c77c
extern const SumoF32 g_wavyTextSineRate = 1.77f;

// GLOBAL: SUMO 0x0042b304
// GLOBAL: EDITOR 0x0042b304
extern const SumoF32 g_wavyTextPhaseScale = 1.1f;

// GLOBAL: SUMO 0x0042c778
// GLOBAL: EDITOR 0x0042c778
extern const SumoF32 g_wavyTextDisplacement = 0.004f;

extern SumoS32 g_screenTintLevel;
extern const SumoF32 g_wavyTextTimeScale;
extern const SumoF32 g_wavyTextCosineRate;
extern const SumoF32 g_wavyTextSineRate;
extern const SumoF32 g_wavyTextPhaseScale;
extern const SumoF32 g_wavyTextDisplacement;
extern Matrix3 g_gameInverseViewMatrix;
extern Vector3 g_gameCameraWorldPosition;

extern const SumoF32 g_parserMinimumBreakability;

Vector3 TransformWavyTextPoint(Vector3 &point) {
  double timeExtended = (double)g_screenTintLevel * g_wavyTextTimeScale;
  SumoF32 time = (SumoF32)timeExtended;
  SumoF32 phaseY = (SumoF32)(cos(timeExtended * g_wavyTextCosineRate) + time);
  SumoF32 phaseX = (SumoF32)(sin((double)time * g_wavyTextSineRate) + time);

  Vector3 wavy = point;
  wavy.Normalize();
  wavy.z = 1.0f;
  phaseY = phaseY * g_wavyTextPhaseScale;

  for (SumoS32 pass = 3; pass != 0; --pass) {
    wavy.x =
        (SumoF32)sin((double)wavy.y * g_parserMinimumBreakability + phaseX) *
            g_wavyTextDisplacement +
        wavy.x;
    wavy.y =
        (SumoF32)cos((double)wavy.x * g_parserMinimumBreakability + phaseY) *
            g_wavyTextDisplacement +
        wavy.y;
  }

  return (wavy + point).Transform(g_gameInverseViewMatrix) +
         g_gameCameraWorldPosition;
}

extern const SumoF64 g_textureZero = 0.0;
extern const SumoF64 g_textureHueCircle = 360.0;
extern const SumoF64 g_textureHueSectorScale = 0.016666666666666666;
extern const SumoF64 g_textureOne = 1.0;

SumoU32 ConvertTextureHsvToRgb(SumoF32 hue, SumoF32 saturation, SumoF32 value) {
  SumoF32 greenSlot = hue;
  SumoF32 blueSlot = value;
  SumoF32 redSource;
  if ((SumoF64)saturation == g_textureZero) {
    greenSlot = value;
    redSource = value;
  } else {
    SumoF64 adjusted = hue;
    while (!(adjusted < g_textureHueCircle))
      adjusted -= g_textureHueCircle;
    while (adjusted < g_textureZero)
      adjusted += g_textureHueCircle;
    adjusted = adjusted * g_textureHueSectorScale;
    SumoF32 scaledHue = (SumoF32)adjusted;
    greenSlot = scaledHue;
    SumoF64 sectorBase = floor(adjusted);
    SumoF64 fraction = scaledHue - sectorBase;
    SumoF32 mixLow = (SumoF32)((g_textureOne - saturation) * value);
    SumoF32 mixFalling =
        (SumoF32)((g_textureOne - fraction * saturation) * value);
    SumoF32 mixRising =
        (SumoF32)((g_textureOne - (g_textureOne - fraction) * saturation) *
                  value);
    SumoS32 sector = (SumoS32)sectorBase;
    if ((SumoU32)sector > 5) {
      redSource = blueSlot;
    } else {
      switch (sector) {
      case 0:
        redSource = blueSlot;
        greenSlot = mixRising;
        blueSlot = mixLow;
        break;
      case 1:
        redSource = mixFalling;
        greenSlot = blueSlot;
        blueSlot = mixLow;
        break;
      case 2:
        redSource = mixLow;
        greenSlot = blueSlot;
        blueSlot = mixRising;
        break;
      case 3:
        redSource = mixLow;
        greenSlot = mixFalling;
        blueSlot = value;
        break;
      case 4:
        redSource = mixRising;
        greenSlot = mixLow;
        blueSlot = value;
        break;
      default:
        redSource = blueSlot;
        greenSlot = mixLow;
        blueSlot = mixFalling;
        break;
      }
    }
  }

  SumoS32 red = (SumoS32)redSource;
  SumoS32 green = (SumoS32)greenSlot;
  SumoS32 blue = (SumoS32)blueSlot;
  if (red > 0xff)
    red = 0xff;
  if (green > 0xff)
    green = 0xff;
  if (blue > 0xff)
    blue = 0xff;
  return (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
}

extern const SumoF64 g_textureZero;
extern const SumoF64 g_textureHueCircle;

SumoU32 ConvertTextureHsvToRgb(SumoF32 hue, SumoF32 saturation, SumoF32 value);

extern SumoU8 *g_textureLayers[4];

extern const SumoF64 g_textureHueSectorTwo = 2.0;
extern const SumoF64 g_textureHueDegreesPerSector = 60.0;
extern const SumoF64 g_textureHueSectorFour = 4.0;
extern const SumoF64 g_textureInvByteMaximum = 0.0039215686274509803;
extern const SumoF64 g_textureHueByteToDegrees = 1.40625;

void ConvertTextureRgbToHsv(SumoF32 red, SumoF32 green, SumoF32 blue,
                            SumoF32 *hue, SumoF32 *saturation, SumoF32 *value) {
  SumoF32 maxValue = (red > green) ? red : green;
  if (blue > maxValue)
    maxValue = blue;
  SumoF32 minValue = (red < green) ? red : green;
  if (blue < minValue)
    minValue = blue;

  *value = maxValue;
  *saturation = 0.0f;
  if (!((SumoF64)maxValue == g_textureZero))
    *saturation = (SumoF32)(((SumoF64)maxValue - minValue) / maxValue);
  if ((SumoF64)*saturation == g_textureZero) {
    *hue = -1.0f;
    return;
  }

  SumoF32 delta = (SumoF32)((SumoF64)maxValue - minValue);
  SumoF32 redDelta = maxValue - red;
  SumoF32 greenDelta = maxValue - green;
  SumoF32 blueDelta = maxValue - blue;
  if (red == maxValue) {
    *hue = (SumoF32)(((SumoF64)blueDelta - greenDelta) / delta);
  } else if (green == maxValue) {
    *hue = (SumoF32)(((SumoF64)redDelta - blueDelta) / delta +
                     g_textureHueSectorTwo);
  } else if (blue == maxValue) {
    *hue = (SumoF32)(((SumoF64)greenDelta - redDelta) / delta +
                     g_textureHueSectorFour);
  }

  SumoF64 scaled = (SumoF64)*hue * g_textureHueDegreesPerSector;
  *hue = (SumoF32)scaled;
  if (scaled < g_textureZero) {
    SumoF64 lifted;
    do {
      lifted = (SumoF64)*hue + g_textureHueCircle;
      *hue = (SumoF32)lifted;
    } while (lifted < g_textureZero);
  }
  if (!((SumoF64)*hue < g_textureHueCircle)) {
    SumoF64 lowered;
    do {
      lowered = (SumoF64)*hue - g_textureHueCircle;
      *hue = (SumoF32)lowered;
    } while (!(lowered < g_textureHueCircle));
  }
}

void AdjustTextureHsv(SumoS32 layerIndex, SumoS32 hueOffset,
                      SumoS32 saturationReduction) {
  SumoU32 *cursor = (SumoU32 *)g_textureLayers[layerIndex];
  SumoF32 hueShift = (SumoF32)((SumoF64)hueOffset * g_textureHueByteToDegrees);
  SumoF32 saturationScale = (SumoF32)((SumoF64)(0xff - saturationReduction) *
                                      g_textureInvByteMaximum);
  for (SumoS32 count = 0x10000; count != 0; --count) {
    SumoU32 pixel = *cursor;
    SumoF32 hue;
    SumoF32 saturation;
    SumoF32 value;
    ConvertTextureRgbToHsv((SumoF32)(SumoS32)((pixel >> 16) & 0xff),
                           (SumoF32)(SumoS32)((pixel >> 8) & 0xff),
                           (SumoF32)(SumoS32)(pixel & 0xff), &hue, &saturation,
                           &value);
    *cursor = ConvertTextureHsvToRgb(hue + hueShift,
                                     saturation * saturationScale, value);
    ++cursor;
  }
}

extern SumoU8 *g_textureLayers[4];
extern SumoU32 *g_textureWorkBuffer;
extern const SumoF64 g_textureInvSize = 0.00390625;

SumoU32 SampleTexturePixel(SumoU32 *texture, SumoF32 x, SumoF32 y);

SumoS32 DistortTextureByLayers(SumoS32 targetLayer, SumoS32 firstMapLayer,
                               char firstChannel, SumoS32 firstStrength,
                               SumoS32 secondMapLayer, char secondChannel,
                               SumoS32 secondStrength) {
  SumoU32 *target = (SumoU32 *)g_textureLayers[targetLayer];
  SumoU32 *firstMap = (SumoU32 *)g_textureLayers[firstMapLayer];
  SumoU32 *secondMap = (SumoU32 *)g_textureLayers[secondMapLayer];
  SumoS32 firstShift = 16 - ((firstChannel << 3) & 0xff);
  SumoS32 secondShift = 16 - ((secondChannel << 3) & 0xff);
  SumoF32 firstScale = (SumoF32)((SumoF64)firstStrength * g_textureInvSize);
  SumoF32 secondScale = (SumoF32)((SumoF64)secondStrength * g_textureInvSize);

  SumoS32 pixel = 0;
  for (SumoS32 row = 0; row < 0x100; ++row) {
    SumoF32 rowBase = (SumoF32)row;
    for (SumoS32 column = 0; column < 0x100; ++column, ++pixel) {
      SumoS32 firstOffset = (SumoS32)((firstMap[pixel] >> firstShift) & 0xff);
      SumoS32 secondOffset =
          (SumoS32)((secondMap[pixel] >> secondShift) & 0xff);
      SumoF32 sampleX = (SumoF32)((SumoF64)firstOffset * firstScale + column);
      SumoF32 sampleY =
          (SumoF32)((SumoF64)secondOffset * secondScale + rowBase);
      g_textureWorkBuffer[pixel] = SampleTexturePixel(target, sampleX, sampleY);
    }
  }
  memcpy(target, g_textureWorkBuffer, 0x40000);
  return 0;
}

typedef void(__stdcall *TextureProgressCallback)(SumoF32 progress);

extern char g_textureExportFilename[];
extern SumoU8 g_textureLoadFromTga;
extern SumoU32 *g_textureWorkBuffer;
extern SumoU32 *g_textureChannelSwapBuffer;
extern SumoU8 *g_textureLayers[4];
extern SumoU8 *g_textureByteBuffer;
extern TextureProgressCallback g_textureProgressCallback;
extern SumoS32 g_textureProgramTotalWork;
extern SumoS32 g_textureProgramCompletedWork;

void *InitializeTextureGenerator();
SumoS8 ExportTextureTga(SumoU32 *texture);
SumoS32 ImportTextureTga(const char *filename, SumoU32 *texture);

SumoS32 ClearTextureWorkBuffer(void *buffer);
void GenerateTextureFractalPlasma(SumoS32, char, SumoS32, SumoS32, SumoS32,
                                  SumoS32);
void GenerateTexturePlasma(SumoS32, char, SumoS32, SumoS32, SumoS32, SumoS32);
void GenerateTextureCells(SumoS32, char, SumoS32, SumoS32, SumoS32, SumoS32,
                          SumoS32, SumoS32);
void GenerateTextureRadialGradient(SumoS32, SumoS32, char, SumoS32);
void GenerateTextureCubicNoise(SumoS32, char, SumoS32, SumoS32, SumoS32,
                               SumoS32, SumoS32);
SumoS32 DistortTextureSine(SumoS32, SumoS32, SumoS32, SumoS32, SumoS32, SumoS32,
                           SumoS32);
void TranslateTextureLayerWrapped(SumoS32, char, char);
SumoS32 DistortTextureTwirl(SumoS32, SumoS32);
void SubtractShiftedTextureLayer(SumoS32, SumoS16);
SumoS32 BlurTextureLayer(SumoS32, SumoS32);
SumoS32 DistortTextureByLayers(SumoS32, SumoS32, char, SumoS32, SumoS32, char,
                               SumoS32);
void DirectionalBlurTextureLayer(SumoS32, SumoS32, char, SumoS32);
void SwapTextureChannels(SumoS32, char, SumoS32, char);
SumoS32 ReplicateTextureChannel(SumoS32, char);
void CopyTextureChannel(SumoS32, char, SumoS32, char);
void MixTextureLayers(SumoS32, SumoS32, SumoS32);
void MultiplyTextureLayers(SumoS32, SumoS32);
void AddTextureLayersSaturated(SumoS32, SumoS32);
void MaxTextureLayers(SumoS32, SumoS32);
void AdjustTextureContrast(SumoS32, SumoS32);
void InvertTextureLayerLowBytes(SumoS32);
void ShadeTextureLayerByChannel(SumoS32, SumoS32, char);
void ApplyTextureColorMap(SumoS32, SumoS32);
void ApplyTextureCosineWave(SumoS32, char, SumoS32);
void RemapTextureChannelRange(SumoS32, char, SumoS32, SumoS32);
void AdjustTextureHsv(SumoS32, SumoS32, SumoS32);
void ApplyTextureGradient(SumoS32, SumoS8, SumoS32, SumoS32, SumoS32, SumoS32,
                          SumoS32, SumoS32);
void BlendTextureLayersByMask(SumoS32, SumoS32, SumoS32, SumoS8);
void EmbossTextureLayer(SumoS32);
SumoU32 *ExpandTextureBitmap(SumoS32, SumoU8 *, SumoU32, SumoU32);

SumoU8 *g_textureCommandCursor;

void ExecuteTextureProgram(void *program, SumoU32 *output) {
  if (program == NULL)
    return;
  if (output == NULL)
    return;
  if (g_textureWorkBuffer == NULL)
    InitializeTextureGenerator();

  if (g_textureLoadFromTga) {
    if (ImportTextureTga(g_textureExportFilename, output)) {
      g_textureProgramCompletedWork += ((SumoU8 *)program)[3];
      g_textureProgressCallback((SumoF32)g_textureProgramCompletedWork /
                                (SumoF32)g_textureProgramTotalWork);
      return;
    }
  }

  *(SumoU32 *)g_textureByteBuffer = *(SumoU32 *)program;
  ClearTextureWorkBuffer(g_textureWorkBuffer);
  ClearTextureWorkBuffer(g_textureChannelSwapBuffer);
  ClearTextureWorkBuffer(g_textureLayers[0]);
  ClearTextureWorkBuffer(g_textureLayers[1]);
  ClearTextureWorkBuffer(g_textureLayers[2]);
  ClearTextureWorkBuffer(g_textureLayers[3]);

  SumoU32 header = *(SumoU32 *)g_textureByteBuffer;
  if ((header & 0xffffff) != 0x475441)
    return;

  SumoS32 commandCount = (SumoS32)header >> 24;
  SumoS32 dataOffset = 4;
  if (commandCount > 0) {
    SumoS32 recordBase = 0;
    for (SumoS32 remaining = commandCount; remaining != 0; --remaining) {
      SumoU8 *record = (SumoU8 *)program + dataOffset + recordBase;
      g_textureCommandCursor = record;
      SumoS32 opcode = record[0];
      g_textureCommandCursor = record + 1;
      if (record[1] <= 3) {
        SumoS32 layer = record[1];
        switch (opcode) {
        case 0x01:
          GenerateTextureFractalPlasma(layer, (char)record[2], record[4],
                                       record[5], record[6], record[7]);
          break;
        case 0x02:
          GenerateTexturePlasma(layer, (char)record[8], record[2], record[3],
                                record[4], record[5]);
          break;
        case 0x03:
          GenerateTextureCells(layer, (char)record[2], record[3], record[4],
                               record[5], record[6], record[7], record[8]);
          break;
        case 0x04:
          GenerateTextureRadialGradient(layer, record[2], (char)record[3],
                                        record[4]);
          break;
        case 0x05:
          GenerateTextureCubicNoise(layer, (char)record[2], record[3],
                                    record[4], record[5], record[6], record[7]);
          break;
        case 0x06: ClearTextureWorkBuffer(g_textureLayers[layer]); break;
        case 0x0a:
          DistortTextureSine(layer, record[2], record[3], record[4], record[5],
                             record[6], record[7]);
          break;
        case 0x0b:
          TranslateTextureLayerWrapped(layer, (char)record[2], (char)record[3]);
          break;
        case 0x0c: DistortTextureTwirl(layer, record[2]); break;
        case 0x0e:
          SubtractShiftedTextureLayer(layer, (SumoS16)record[2]);
          break;
        case 0x0f: BlurTextureLayer(layer, record[2]); break;
        case 0x11:
          DistortTextureByLayers(layer, record[2], (char)record[3], record[4],
                                 record[5], (char)record[6], record[7]);
          break;
        case 0x12:
          DirectionalBlurTextureLayer(layer, record[2], (char)record[3],
                                      record[4]);
          break;
        case 0x14:
          SwapTextureChannels(layer, (char)record[2], record[3],
                              (char)record[4]);
          break;
        case 0x15: ReplicateTextureChannel(layer, (char)record[2]); break;
        case 0x17:
          CopyTextureChannel(layer, (char)record[2], record[3],
                             (char)record[4]);
          break;
        case 0x18: MixTextureLayers(layer, record[2], record[3]); break;
        case 0x19: MultiplyTextureLayers(layer, record[2]); break;
        case 0x1a: AddTextureLayersSaturated(layer, record[2]); break;
        case 0x1b: MaxTextureLayers(layer, record[2]); break;
        case 0x1e: AdjustTextureContrast(layer, record[2]); break;
        case 0x1f: InvertTextureLayerLowBytes(layer); break;
        case 0x20:
          ShadeTextureLayerByChannel(layer, record[2], (char)record[3]);
          break;
        case 0x21: ApplyTextureColorMap(layer, record[2]); break;
        case 0x22:
          ApplyTextureCosineWave(layer, (char)record[2], record[3]);
          break;
        case 0x23:
          RemapTextureChannelRange(layer, (char)record[2], record[3],
                                   record[4]);
          break;
        case 0x24: AdjustTextureHsv(layer, record[2], record[3]); break;
        case 0x25:
          ApplyTextureGradient(layer, (SumoS8)record[2], record[3], record[4],
                               record[5], record[6], record[7], record[8]);
          break;
        case 0x26:
          BlendTextureLayersByMask(layer, record[2], record[3],
                                   (SumoS8)record[4]);
          break;
        case 0x27: EmbossTextureLayer(layer); break;
        case 0x28: {
          SumoU32 zeroValue = ((SumoU32)record[2] << 16) |
                              ((SumoU32)record[3] << 8) | record[4];
          SumoU32 oneValue = ((SumoU32)record[5] << 16) |
                             ((SumoU32)record[6] << 8) | record[7];
          ExpandTextureBitmap(layer, record + 9, zeroValue, oneValue);
          dataOffset += 0x2000;
          break;
        }
        default: break;
        }
      }
      ++g_textureProgramCompletedWork;
      g_textureProgressCallback((SumoF32)g_textureProgramCompletedWork /
                                (SumoF32)g_textureProgramTotalWork);
      recordBase += 9;
    }
  }

  memcpy(output, g_textureLayers[0], 0x40000);
  if (g_textureLoadFromTga)
    ExportTextureTga((SumoU32 *)g_textureLayers[0]);
}

typedef void(__stdcall *TextureProgressCallback)(SumoF32 progress);

char g_textureExportFilename[] = "tex00000.tga";

SumoU8 g_textureTgaHeader[13] = {0, 0, 2};

SumoU8 g_textureLoadFromTga;

SumoU8 g_textureUseMmxSampler;

SumoU8 g_textureGeneratorInitialized;

SumoU8 *g_textureColorMap;

SumoU32 *g_textureWorkBuffer;

SumoU32 *g_textureChannelSwapBuffer;

SumoU8 *g_textureLayers[4];

SumoU8 *g_textureIoBuffer;

SumoU8 *g_textureByteBuffer;

TextureProgressCallback g_textureProgressCallback;

SumoS32 g_textureProgramTotalWork;

SumoS32 g_textureProgramCompletedWork;

SumoS32 g_textureNoiseSeed;

SumoS32 g_textureInterpolationWeights[256];

extern const SumoF64 g_textureByteMaximum = 255.0;
extern const SumoF64 g_textureColorMapRowScale = 0.007874015748031496;
extern const SumoF64 g_textureHalf = 0.5;
extern const SumoF64 g_texturePi = 3.1415927410125732421875;
extern const SumoF32 g_textureByteMaximumFloat = 255.0f;
extern const SumoF64 g_textureCenter = 128.0;
extern const SumoF64 g_textureCellRadiusScale = 0.0390625;
extern const SumoF64 g_textureWaveAmplitude = 127.0;
extern const SumoF64 g_texturePlasmaAmplitude = 63.0;
extern const SumoF64 g_textureRadiansPerPixel = 0.02454369328916073;
extern const SumoF64 g_textureRadialBaseScale = 0.8;
extern const SumoF32 g_textureTwirlFrequency = 0.012271847f;
extern const SumoF32 g_textureCenterFloat = 128.0f;
extern const SumoF64 g_textureAngleToByte = 40.74366429772945;
extern const SumoF64 g_textureContrastScale = 0.03125;
extern const SumoF64 g_textureHalfCenter = 127.5;
extern const SumoF64 g_textureTau = 6.283185482025146484375;
extern const SumoF32 g_textureBlendScale = 0.00390625f;

extern const SumoF32 g_textureWrapSizeFloat = 256.0f;
extern const SumoF64 g_textureSize = 256.0;

extern const SumoF64 g_textureOne;

extern const SumoF64 g_textureInvSize;

extern const SumoF32 g_gameOne;

void ExecuteTextureProgram(void *program, SumoU32 *output);

void *InitializeTextureGenerator() {
  g_textureColorMap = (SumoU8 *)malloc(0x10000);

  for (SumoS32 darkRow = 0; darkRow < 0x80; ++darkRow) {
    SumoU8 *destination = g_textureColorMap + (darkRow << 8);
    SumoU32 accumulator = 0;
    for (SumoS32 column = 0; column < 0x100; ++column) {
      destination[column] = (SumoU8)(accumulator / 127);
      accumulator += darkRow;
    }
  }

  for (SumoS32 lightRow = 0; lightRow < 0x80; ++lightRow) {
    SumoU8 *destination = g_textureColorMap + 0x8000 + (lightRow << 8);
    SumoF64 scale =
        g_textureOne - (SumoF64)lightRow * g_textureColorMapRowScale;
    for (SumoS32 column = 0; column < 0x100; ++column) {
      destination[column] =
          (SumoU8)(SumoS32)(g_textureByteMaximum -
                            (g_textureByteMaximum - (SumoF64)column) * scale);
    }
  }

  g_textureWorkBuffer = (SumoU32 *)malloc(0x40000);
  g_textureChannelSwapBuffer = (SumoU32 *)malloc(0x40000);
  g_textureLayers[0] = (SumoU8 *)malloc(0x40000);
  g_textureLayers[1] = (SumoU8 *)malloc(0x40000);
  g_textureLayers[2] = (SumoU8 *)malloc(0x40000);
  g_textureLayers[3] = (SumoU8 *)malloc(0x40000);
  g_textureIoBuffer = (SumoU8 *)malloc(0x40000);
  g_textureByteBuffer = (SumoU8 *)malloc(0x10000);
  return g_textureByteBuffer;
}

static void AdvanceTextureExportFilename() {
  char digit = (char)(g_textureExportFilename[7] + 1);
  g_textureExportFilename[7] = digit;
  if (digit == ':') {
    g_textureExportFilename[7] = '0';
    g_textureExportFilename[6] = (char)(g_textureExportFilename[6] + 1);
  }
}

SumoS8 ExportTextureTga(SumoU32 *texture) {
  SumoU8 header[18];
  memcpy(header, g_textureTgaHeader, 12);
  header[12] = 0x00;
  header[13] = 0x01;
  header[14] = 0x00;
  header[15] = 0x01;
  header[16] = 24;
  header[17] = g_textureTgaHeader[12];

  FILE *stream = fopen(g_textureExportFilename, "wb");
  if (stream != NULL) {
    fwrite(header, 1, 18, stream);
    SumoU8 *destination = g_textureIoBuffer;
    SumoU32 *row = texture + 0xff00;
    for (SumoS32 rowIndex = 0; rowIndex < 0x100; ++rowIndex) {
      SumoU32 *source = row;
      for (SumoS32 column = 0; column < 0x100; ++column) {
        SumoU32 pixel = *source++;
        destination[0] = (SumoU8)pixel;
        destination[1] = (SumoU8)((SumoS32)pixel >> 8);
        destination[2] = (SumoU8)((SumoS32)pixel >> 16);
        destination += 3;
      }
      row -= 0x100;
    }
    fwrite(g_textureIoBuffer, 1, 0x30000, stream);
    fclose(stream);
  }

  AdvanceTextureExportFilename();
  return 0;
}

static FILE *OpenTextureTga(const char *filename) {
  FILE *stream = fopen(filename, "rb");
  if (stream != NULL)
    return stream;

  char path[1024];
  const char *assetDirectory = getenv("SUMOTORI_ASSET_DIR");
  if (assetDirectory != NULL) {
    sprintf(path, "%s/textures/%s", assetDirectory, filename);
    stream = fopen(path, "rb");
    if (stream != NULL)
      return stream;
  }
  sprintf(path, "assets/textures/%s", filename);
  return fopen(path, "rb");
}

static SumoS32 CopyEmbeddedTextureTga(const char *filename) {
  char name[1024];
  sprintf(name, "textures/%s", filename);
  const void *data = 0;
  SumoU32 size = 0;
  if (!SumoLookupEmbeddedAsset(name, &data, &size) || size < 0x12)
    return 0;
  SumoU32 available = size - 0x12;
  if (available > 0x30000)
    available = 0x30000;
  memcpy(g_textureIoBuffer, (const SumoU8 *)data + 0x12, available);
  return 1;
}

SumoS32 ImportTextureTga(const char *filename, SumoU32 *texture) {
  FILE *stream = OpenTextureTga(filename);
  if (stream != NULL) {
    fseek(stream, 0x12, SEEK_SET);
    size_t readBytes = fread(g_textureIoBuffer, 1, 0x30000, stream);
    (void)readBytes;
    fclose(stream);
  } else if (!CopyEmbeddedTextureTga(filename)) {
    return 0;
  }

  SumoU8 *source = g_textureIoBuffer;
  SumoU32 *row = texture + 0xff00;
  for (SumoS32 rowIndex = 0; rowIndex < 0x100; ++rowIndex) {
    SumoU32 *destination = row;
    for (SumoS32 column = 0; column < 0x100; ++column) {
      SumoU32 blue = source[0];
      SumoU32 green = source[1];
      SumoU32 red = source[2];
      source += 3;
      *destination++ = ((red << 8 | green) << 8) | blue;
    }
    row -= 0x100;
  }

  AdvanceTextureExportFilename();
  return 1;
}

void ShutdownTextureGenerator() {
  if (g_textureChannelSwapBuffer != NULL) {
    free(g_textureChannelSwapBuffer);
  }
  if (g_textureWorkBuffer != NULL) {
    free(g_textureWorkBuffer);
  }
  if (g_textureLayers[0] != NULL) {
    free(g_textureLayers[0]);
  }
  if (g_textureLayers[1] != NULL) {
    free(g_textureLayers[1]);
  }
  if (g_textureLayers[2] != NULL) {
    free(g_textureLayers[2]);
  }
  if (g_textureLayers[3] != NULL) {
    free(g_textureLayers[3]);
  }
  if (g_textureIoBuffer != NULL) {
    free(g_textureIoBuffer);
  }
  if (g_textureByteBuffer != NULL) {
    free(g_textureByteBuffer);
  }
}

SumoU32 *BuildTextureFromProgram(void *program) {
  SumoU32 *buffer = (SumoU32 *)malloc(0x40000);
  ExecuteTextureProgram(program, buffer);
  return buffer;
}

void **BuildTextureSet(void **programs, void *progressCallback) {
  if (!g_textureGeneratorInitialized) {
    InitializeTextureGenerator();
    g_textureGeneratorInitialized = 1;
  }
  g_textureProgressCallback = (TextureProgressCallback)progressCallback;

  SumoS32 count = 0;
  void **cursor = programs;
  do {
    ++count;
    ++cursor;
  } while (*cursor != 0);

  g_textureProgramTotalWork = 0;
  g_textureProgramCompletedWork = 0;
  for (SumoS32 index = 0; index < count; ++index) {
    g_textureProgramTotalWork += ((SumoU8 *)programs[index])[3];
  }

  void **results = (void **)malloc(count * sizeof(void *));
  for (SumoS32 index = 0; index < count; ++index) {
    results[index] = BuildTextureFromProgram(programs[index]);
  }

  g_textureProgramTotalWork = 0;
  g_textureProgramCompletedWork = 0;
  ShutdownTextureGenerator();
  return results;
}

SumoS32 ClearTextureWorkBuffer(void *p_buffer) {
  SumoU32 *cursor = (SumoU32 *)p_buffer;
  SumoS32 count = 0x10000;
  while (count != 0) {
    *cursor++ = 0;
    --count;
  }

  return 0;
}

SumoS32 TextureNoiseHash(SumoS32 value) {
  SumoS32 mixed = (SumoS32)((SumoU32)value << 13) ^ value;
  SumoS32 accumulated = g_textureNoiseSeed + mixed;
  SumoU32 hashed = ((SumoU32)mixed * (SumoU32)mixed * 0x3d73u + 0xc0ae5u) *
                       (SumoU32)accumulated +
                   0x5208dd0du;
  SumoS32 scaled =
      (SumoS32)(((SumoS64)0x1535f585 * (SumoS64)(SumoS32)hashed) >> 32) >> 10;
  return scaled + (SumoS32)((SumoU32)scaled >> 31);
}

SumoF32 InterpolateTextureValue(SumoF32 first, SumoF32 second, SumoF32 third,
                                SumoF32 fourth, SumoF32 position,
                                SumoF32 span) {
  SumoF64 t = (SumoF64)position / span;
  SumoF64 firstDrop = (SumoF64)first - second;
  SumoF64 lastRise = ((SumoF64)fourth - third) - firstDrop;
  SumoF64 tSquared = t * t;
  SumoF64 sum = (firstDrop - lastRise) * tSquared + tSquared * t * lastRise;
  sum = sum + ((SumoF64)third - first) * t;
  return (SumoF32)(sum + second);
}

void FillTextureCubicNoise(SumoF32 *output, SumoS32 spacing,
                           SumoF32 amplitude) {
  SumoF32 scaledAmplitude = (SumoF32)(amplitude * g_textureInvSize);

  for (SumoS32 index = 0; index < 0x10000; ++index) {
    output[index] = 0.0f;
  }

  SumoS32 hashCounter = 0;
  SumoF32 *row = output;
  for (SumoS32 latticeY = 0; latticeY < 0x100; latticeY += spacing) {
    SumoF32 *cell = row;
    for (SumoS32 latticeX = 0; latticeX < 0x100; latticeX += spacing) {
      SumoS32 hashed = TextureNoiseHash(hashCounter) & 0xff;
      ++hashCounter;
      *cell = (SumoF32)((SumoF64)hashed * scaledAmplitude);
      cell += spacing;
    }
    row += spacing << 8;
  }

  for (SumoS32 rowBase = 0; rowBase < 0x10000; rowBase += spacing << 8) {
    for (SumoS32 x = 1; x < 0x100; ++x) {
      SumoS32 alignedX = x & (0x100 - spacing);
      SumoS32 nextColumn = (alignedX + spacing) & 0xff;
      SumoF32 previous = output[rowBase + ((alignedX - spacing) & 0xff)];
      SumoF32 current = output[rowBase + alignedX];
      SumoF32 next = output[rowBase + nextColumn];
      SumoF32 following = output[rowBase + ((nextColumn + spacing) & 0xff)];
      SumoS32 fraction = x & (spacing - 1);
      output[rowBase + x] =
          InterpolateTextureValue(previous, current, next, following,
                                  (SumoF32)fraction, (SumoF32)spacing);
    }
  }

  SumoF32 *destinationRow = output;
  for (SumoS32 y = 0; y < 0x100; ++y) {
    if (y != 0) {
      SumoS32 alignedY = y & (0x100 - spacing);
      SumoS32 nextRow = (alignedY + spacing) & 0xff;
      SumoF32 *previousCell = output + (((alignedY - spacing) & 0xff) << 8);
      SumoF32 *currentCell = output + (alignedY << 8);
      SumoF32 *nextCell = output + (nextRow << 8);
      SumoF32 *followingCell = output + (((nextRow + spacing) & 0xff) << 8);
      SumoF32 position = (SumoF32)(y & (spacing - 1));
      SumoF32 span = (SumoF32)spacing;
      SumoF32 *destination = destinationRow;
      for (SumoS32 column = 0x100; column != 0; --column) {
        *destination =
            InterpolateTextureValue(*previousCell, *currentCell, *nextCell,
                                    *followingCell, position, span);
        ++destination;
        ++previousCell;
        ++currentCell;
        ++nextCell;
        ++followingCell;
      }
    }
    destinationRow += 0x100;
  }
}

void GenerateTextureCubicNoise(SumoS32 layerIndex, char channel,
                               SumoS32 spacing, SumoS32 seed0, SumoS32 seed1,
                               SumoS32 seed2, SumoS32 seed3) {
  if (spacing == 0) {
    return;
  }
  g_textureNoiseSeed = ((((seed0 << 8 | seed1) << 8) | seed2) << 8) | seed3;
  SumoF32 *buffer = (SumoF32 *)malloc(0x40000);
  FillTextureCubicNoise(buffer, spacing, 255.0f);

  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 shift = (2 - channel) << 3;
  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  SumoF32 *source = buffer;
  for (SumoS32 count = 0x10000; count != 0; --count) {
    SumoU32 preserved = *layer & keepMask;
    SumoS32 value = (SumoS32)*source;
    if (value > 0xff) {
      value = 0xff;
    } else if (value < 0) {
      value = 0;
    }
    *layer = ((SumoU32)value << shift) | preserved;
    ++layer;
    ++source;
  }
  free(buffer);
}

SumoU32 *AddTextureLayers(SumoU32 *destination, SumoU32 *source) {
  for (SumoS32 count = 0x10000; count != 0; --count) {
    *destination = *destination + *source;
    ++destination;
    ++source;
  }
  return destination;
}

void FillTextureFractalMap(SumoU32 *output, SumoS32 spacing,
                           SumoF32 amplitude) {
  SumoF32 scaledAmplitude = (SumoF32)(amplitude * g_textureInvSize);

  for (SumoS32 index = 0; index < 0x10000; ++index) {
    output[index] = 0;
  }

  SumoS32 hashCounter = 0;
  SumoU32 *row = output;
  for (SumoS32 latticeY = 0; latticeY < 0x100; latticeY += spacing) {
    SumoU32 *cell = row;
    for (SumoS32 latticeX = 0; latticeX < 0x100; latticeX += spacing) {
      SumoS32 hashed = TextureNoiseHash(hashCounter) & 0xff;
      ++hashCounter;
      *cell = (SumoU32)((SumoS32)((SumoF64)hashed * scaledAmplitude) << 16);
      cell += spacing;
    }
    row += spacing << 8;
  }

  for (SumoS32 step = 0; step < spacing; ++step) {
    g_textureInterpolationWeights[step] =
        (SumoS32)((g_textureOne -
                   cos((SumoF64)step * g_texturePi / (SumoF64)spacing)) *
                  g_textureHalf * g_textureSize);
  }

  for (SumoS32 rowBase = 0; rowBase < 0x10000; rowBase += spacing << 8) {
    for (SumoS32 x = 0; x < 0x100; ++x) {
      SumoS32 alignedX = x & (0x100 - spacing);
      SumoS32 current = (SumoS32)output[rowBase + alignedX];
      SumoS32 next = (SumoS32)output[rowBase + ((alignedX + spacing) & 0xff)];
      SumoS32 value = (((next - current) *
                        g_textureInterpolationWeights[x & (spacing - 1)]) >>
                       8) +
                      current;
      output[rowBase + x] = (SumoU32)value;
    }
  }

  SumoU32 *destinationRow = output;
  for (SumoS32 y = 0; y < 0x100; ++y) {
    if (y != 0) {
      SumoS32 alignedY = y & (0x100 - spacing);
      SumoU32 *currentCell = output + (alignedY << 8);
      SumoU32 *nextCell = output + (((alignedY + spacing) & 0xff) << 8);
      SumoS32 weight = g_textureInterpolationWeights[y & (spacing - 1)];
      SumoU32 *destination = destinationRow;
      for (SumoS32 column = 0x100; column != 0; --column) {
        SumoS32 current = (SumoS32)*currentCell;
        SumoS32 value =
            ((((SumoS32)*nextCell - current) * weight) >> 8) + current;
        *destination = (SumoU32)value;
        ++destination;
        ++currentCell;
        ++nextCell;
      }
    }
    destinationRow += 0x100;
  }
}

void GenerateTextureFractalPlasma(SumoS32 layerIndex, char channel,
                                  SumoS32 seed0, SumoS32 seed1, SumoS32 seed2,
                                  SumoS32 seed3) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 shift = (2 - channel) << 3;
  g_textureNoiseSeed = ((((seed0 << 8 | seed1) << 8) | seed2) << 8) | seed3;
  FillTextureFractalMap(g_textureWorkBuffer, 0x80, 128.0f);

  SumoS32 spacing = 0x40;
  SumoF32 amplitude = 64.0f;
  do {
    FillTextureFractalMap(g_textureChannelSwapBuffer, spacing, amplitude);
    AddTextureLayers(g_textureWorkBuffer, g_textureChannelSwapBuffer);
    amplitude = (SumoF32)(amplitude * g_textureHalf);
    spacing = spacing / 2;
  } while (spacing > 0);

  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  for (SumoS32 index = 0; index < 0x10000; ++index) {
    layer[index] = (layer[index] & keepMask) |
                   ((g_textureWorkBuffer[index] >> 16) << shift);
  }
}

void GenerateTextureCells(SumoS32 layerIndex, char channel, SumoS32 cellCount,
                          SumoS32 radiusScale, SumoS32 seed0, SumoS32 seed1,
                          SumoS32 seed2, SumoS32 seed3) {
  SumoF32 scaledRadius =
      (SumoF32)((SumoF64)radiusScale * g_textureCellRadiusScale);
  SumoS32 *kernel = (SumoS32 *)malloc(0x40000);
  SumoS32 *cell = kernel;
  for (SumoS32 y = 0; y < 0x100; ++y) {
    SumoF64 deltaY = (SumoF64)y - g_textureCenter;
    SumoF64 deltaYSquared = deltaY * deltaY;
    for (SumoS32 x = 0; x < 0x100; ++x) {
      SumoF64 deltaX = (SumoF64)x - g_textureCenter;
      SumoF64 distance = sqrt(deltaX * deltaX + deltaYSquared) * scaledRadius;
      if (distance > g_textureByteMaximumFloat) {
        distance = g_textureByteMaximumFloat;
      }
      *cell = (SumoS32)distance;
      ++cell;
    }
  }

  g_textureNoiseSeed = ((((seed0 << 8 | seed1) << 8) | seed2) << 8) | seed3;
  for (SumoS32 index = 0; index < 0x10000; ++index) {
    g_textureWorkBuffer[index] = 0xff;
  }

  SumoS32 hashCounter = 0;
  for (SumoS32 remaining = cellCount; remaining > 0; --remaining) {
    SumoS32 cellX = TextureNoiseHash(hashCounter) & 0xff;
    ++hashCounter;
    SumoS32 cellY = TextureNoiseHash(hashCounter) & 0xff;
    ++hashCounter;
    SumoS32 *stamp = kernel;
    for (SumoS32 y = cellY - 0x80; y < cellY + 0x80; ++y) {
      SumoS32 rowOffset = (y & 0xff) << 8;
      for (SumoS32 x = cellX - 0x80; x < cellX + 0x80; ++x) {
        SumoU32 *pixel = g_textureWorkBuffer + rowOffset + (x & 0xff);
        SumoU32 value = (SumoU32)*stamp;
        ++stamp;
        if (*pixel > value) {
          *pixel = value;
        }
      }
    }
  }

  SumoS32 shift = (2 - channel) << 3;
  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  for (SumoS32 index = 0; index < 0x10000; ++index) {
    layer[index] =
        (layer[index] & keepMask) | (g_textureWorkBuffer[index] << shift);
  }
  free(kernel);
}

void GenerateTexturePlasma(SumoS32 layerIndex, char channel, SumoS32 frequencyX,
                           SumoS32 frequencyY, SumoS32 shiftX, SumoS32 shiftY) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 shift = (SumoU8)(0x10 - (SumoU8)(channel << 3));
  SumoS32 index = 0;
  for (SumoS32 y = 0; y < 0x100; ++y) {
    SumoF64 rowWave =
        sin((SumoF64)(SumoF32)((SumoF64)((y + shiftY) * frequencyY) *
                               g_textureRadiansPerPixel));
    for (SumoS32 x = 0; x < 0x100; ++x) {
      SumoF32 wave =
          (SumoF32)(sin((
                        SumoF64)(SumoF32)((SumoF64)((x + shiftX) * frequencyX) *
                                          g_textureRadiansPerPixel)) +
                    rowWave);
      SumoS32 value =
          (SumoS32)(SumoF32)((SumoF64)(SumoF32)((SumoF64)wave *
                                                g_texturePlasmaAmplitude) +
                             g_textureWaveAmplitude);
      g_textureWorkBuffer[index] = (SumoU32)value << shift;
      ++index;
    }
  }

  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  for (SumoS32 pixel = 0; pixel < 0x10000; ++pixel) {
    layer[pixel] = (layer[pixel] & keepMask) | g_textureWorkBuffer[pixel];
  }
}

void GenerateTextureRadialGradient(SumoS32 layerIndex, SumoS32 mode,
                                   char channel, SumoS32 scale) {
  SumoU32 *cursor = (SumoU32 *)g_textureLayers[layerIndex];
  SumoF64 scaleFactor;
  if (mode == 0) {
    scaleFactor = g_gameOne;
  } else if (mode == 1) {
    scaleFactor = (SumoF64)scale * g_textureInvSize + g_textureRadialBaseScale;
  } else {
    scaleFactor = *(SumoF32 *)&mode;
  }

  SumoS32 shift = (2 - channel) << 3;
  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  for (SumoS32 y = 0; y < 0x100; ++y) {
    SumoF64 deltaY = (SumoF64)(y - 0x80);
    SumoF64 deltaYSquared = deltaY * deltaY;
    for (SumoS32 x = 0; x < 0x100; ++x) {
      SumoF64 deltaX = (SumoF64)(x - 0x80);
      SumoF64 shaded = sqrt(deltaX * deltaX + deltaYSquared) * scaleFactor;
      SumoS32 value = (SumoS32)(g_textureByteMaximum - (shaded + shaded));
      if (value < 0) {
        value = 0;
      } else if (value > 0xff) {
        value = 0xff;
      }
      if (mode == 0) {
        *cursor = (SumoU32)(((value << 8) | value) << 8) | (SumoU32)value;
      } else if (mode == 1) {
        *cursor = (*cursor & keepMask) | ((SumoU32)value << shift);
      }
      ++cursor;
    }
  }
}

static SumoS32 RoundTextureCoordinate(SumoF64 value) {
  SumoF64 floored = floor(value);
  SumoS32 result = (SumoS32)floored;
  SumoF64 fraction = value - floored;
  if (fraction > g_textureHalf) {
    ++result;
  } else if (fraction == g_textureHalf) {
    result += result & 1;
  }
  return result;
}

SumoU32 SampleTexturePixel(SumoU32 *texture, SumoF32 x, SumoF32 y) {
  SumoS32 xFixed = RoundTextureCoordinate((SumoF64)x * g_textureSize);
  SumoS32 yFixed = RoundTextureCoordinate((SumoF64)y * g_textureSize);
  SumoS32 xWeight = xFixed & 0xff;
  SumoS32 yWeight = yFixed & 0xff;
  SumoS32 topRow = yFixed & 0xff00;
  SumoS32 bottomRow = (topRow + 0x100) & 0xff00;
  SumoS32 cellX = (xFixed & 0xff00) >> 8;
  SumoS32 nextX = (cellX + 1) & 0xff;
  SumoU32 topLeft = texture[topRow + cellX];
  SumoU32 topRight = texture[topRow + nextX];
  SumoU32 bottomRight = texture[bottomRow + nextX];
  SumoU32 bottomLeft = texture[bottomRow + cellX];

  SumoU32 result = 0;
  for (SumoS32 shift = 0; shift < 24; shift += 8) {
    SumoU32 blended =
        ((((bottomRight >> shift) & 0xff) * (SumoU32)xWeight) >> 8) *
        (SumoU32)yWeight;
    blended += ((((bottomLeft >> shift) & 0xff) * (SumoU32)yWeight) >> 8) *
               (SumoU32)(0xff - xWeight);
    blended += ((((topRight >> shift) & 0xff) * (SumoU32)xWeight) >> 8) *
               (SumoU32)(0xff - yWeight);
    blended +=
        ((((topLeft >> shift) & 0xff) * (SumoU32)(0xff - xWeight)) >> 8) *
        (SumoU32)(0xff - yWeight);
    result |= (blended >> 8) << shift;
  }
  return result;
}

SumoS32 DistortTextureSine(SumoS32 layerIndex, SumoS32 xFrequency,
                           SumoS32 yFrequency, SumoS32 xAmplitude,
                           SumoS32 yAmplitude, SumoS32 xPhase, SumoS32 yPhase) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoF32 xAmplitudeFloat = (SumoF32)xAmplitude;
  SumoF64 yAmplitudeWide = (SumoF64)yAmplitude;

  SumoF32 columnWave[0x100];
  for (SumoS32 index = 0; index < 0x100; ++index) {
    columnWave[index] =
        (SumoF32)(cos((SumoF64)(SumoF32)((SumoF64)((index + yPhase) *
                                                   yFrequency) *
                                         g_textureRadiansPerPixel)) *
                  yAmplitudeWide);
  }

  SumoS32 pixel = 0;
  SumoF32 rowPosition = 0.0f;
  for (SumoS32 row = 0; row < 0x100; ++row) {
    SumoF32 rowWave =
        (SumoF32)(sin((
                      SumoF64)(SumoF32)((SumoF64)((row + xPhase) * xFrequency) *
                                        g_textureRadiansPerPixel)) *
                  xAmplitudeFloat);
    SumoF32 columnPosition = 0.0f;
    for (SumoS32 column = 0; column < 0x100; ++column, ++pixel) {
      SumoF32 sampleY = (SumoF32)(rowPosition + columnWave[column]);
      SumoF32 sampleX = (SumoF32)(columnPosition + rowWave);
      g_textureWorkBuffer[pixel] = SampleTexturePixel(layer, sampleX, sampleY);
      columnPosition = (SumoF32)(columnPosition + g_gameOne);
    }
    rowPosition = (SumoF32)(rowPosition + g_gameOne);
  }
  memcpy(layer, g_textureWorkBuffer, 0x40000);
  return 0;
}

SumoS32 DistortTextureTwirl(SumoS32 layerIndex, SumoS32 strength) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoF32 scaledStrength = (SumoF32)(((SumoF64)strength - g_textureHalfCenter) *
                                     g_textureContrastScale);
  SumoF32 direction = -1.0f;
  if (!(scaledStrength > g_vectorZero)) {
    direction = 1.0f;
  }

  SumoS32 pixel = 0;
  for (SumoS32 row = 0; row < 0x100; ++row) {
    SumoF64 deltaY = (SumoF64)row - g_textureHalfCenter;
    SumoF32 deltaYFloat = (SumoF32)deltaY;
    SumoF32 deltaYSquared = (SumoF32)(deltaY * deltaYFloat);
    for (SumoS32 column = 0; column < 0x100; ++column, ++pixel) {
      SumoF64 deltaX = (SumoF64)column - g_textureHalfCenter;
      SumoF32 radius = (SumoF32)sqrt(deltaX * deltaX + deltaYSquared);
      SumoF64 angleByte =
          atan2(deltaX, (SumoF64)deltaYFloat) * g_textureAngleToByte;
      SumoF64 falloff = (SumoF64)g_textureCenterFloat - radius;
      SumoF64 twirl;
      if (falloff < g_vectorZero) {
        twirl = g_vectorZero;
      } else {
        twirl = cos(falloff * scaledStrength * g_textureTwirlFrequency) *
                    g_textureCenter +
                g_textureCenter;
      }
      SumoF64 theta =
          (angleByte + twirl * direction) * g_textureRadiansPerPixel;
      SumoF32 sampleY = (SumoF32)(cos(theta) * radius + g_textureCenter);
      SumoF32 sampleX = (SumoF32)(sin(theta) * radius + g_textureCenter);
      g_textureWorkBuffer[pixel] = SampleTexturePixel(layer, sampleX, sampleY);
    }
  }
  memcpy(layer, g_textureWorkBuffer, 0x40000);
  return 0;
}

void TranslateTextureLayerWrapped(SumoS32 layerIndex, char offsetX,
                                  char offsetY) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  for (SumoS32 row = 0; row < 0x100; ++row) {
    SumoS32 sourceRowBase = ((offsetY + row) & 0xff) << 8;
    for (SumoS32 column = 0; column < 0x100; ++column) {
      g_textureWorkBuffer[(row << 8) + column] =
          layer[sourceRowBase + ((column + offsetX) & 0xff)];
    }
  }
  memcpy(layer, g_textureWorkBuffer, 0x40000);
}

void SubtractShiftedTextureLayer(SumoS32 layerIndex, SumoS16 diagonalOffset) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 delta = ((SumoS32)diagonalOffset << 8) + diagonalOffset;
  for (SumoS32 pixel = 0; pixel < 0x10000; ++pixel) {
    SumoU32 shifted = layer[(delta + pixel) & 0xffff];
    SumoU32 base = layer[pixel];
    SumoS32 red =
        (SumoS32)((shifted >> 16) & 0xff) - (SumoS32)((base >> 16) & 0xff);
    SumoS32 green =
        (SumoS32)((shifted >> 8) & 0xff) - (SumoS32)((base >> 8) & 0xff);
    SumoS32 blue = (SumoS32)(shifted & 0xff) - (SumoS32)(base & 0xff);
    if (red < 0) {
      red = 0;
    }
    if (green < 0) {
      green = 0;
    }
    if (blue < 0) {
      blue = 0;
    }
    g_textureWorkBuffer[pixel] =
        (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
  }
  memcpy(layer, g_textureWorkBuffer, 0x40000);
}

void SwapTextureChannels(SumoS32 firstIndex, char firstChannel,
                         SumoS32 secondIndex, char secondChannel) {
  SumoU32 *firstLayer = (SumoU32 *)g_textureLayers[firstIndex];
  SumoU32 *secondLayer = (SumoU32 *)g_textureLayers[secondIndex];
  SumoS32 firstShift = 16 - ((firstChannel << 3) & 0xff);
  SumoS32 secondShift = 16 - ((secondChannel << 3) & 0xff);

  for (SumoS32 word = 0; word < 0x10000; ++word) {
    g_textureWorkBuffer[word] = ((secondLayer[word] >> secondShift) & 0xff)
                                << firstShift;
  }
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    g_textureChannelSwapBuffer[word] = ((firstLayer[word] >> firstShift) & 0xff)
                                       << secondShift;
  }

  SumoU32 firstKeepMask = 0xffffff - (0xffu << firstShift);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    firstLayer[word] =
        (firstLayer[word] & firstKeepMask) | g_textureWorkBuffer[word];
  }
  SumoU32 secondKeepMask = 0xffffff - (0xffu << secondShift);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    secondLayer[word] =
        (secondLayer[word] & secondKeepMask) | g_textureChannelSwapBuffer[word];
  }
}

SumoS32 ReplicateTextureChannel(SumoS32 planeIndex, char channel) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[planeIndex];
  SumoS32 shift = 16 - ((channel << 3) & 0xff);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 value = (layer[word] >> shift) & 0xff;
    layer[word] = ((value << 8 | value) << 8) | value;
  }
  return 0;
}

void ShadeTextureLayerByChannel(SumoS32 destinationIndex, SumoS32 sourceIndex,
                                char sourceChannel) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex];
  SumoS32 shift = 16 - ((sourceChannel << 3) & 0xff);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 bank = ((source[word] >> shift) & 0xff) << 8;
    SumoU32 pixel = destination[word];
    SumoU32 red = g_textureColorMap[bank + ((pixel >> 16) & 0xff)];
    SumoU32 green = g_textureColorMap[bank + ((pixel >> 8) & 0xff)];
    SumoU32 blue = g_textureColorMap[bank + (pixel & 0xff)];
    destination[word] = ((red << 8 | green) << 8) | blue;
  }
}

void CopyTextureChannel(SumoS32 destinationIndex, char destinationChannel,
                        SumoS32 sourceIndex, char sourceChannel) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex & 0xff];
  SumoS32 destinationShift = 16 - ((destinationChannel << 3) & 0xff);
  SumoS32 sourceShift = 16 - ((sourceChannel << 3) & 0xff);

  for (SumoS32 word = 0; word < 0x10000; ++word) {
    g_textureWorkBuffer[word] = ((source[word] >> sourceShift) & 0xff)
                                << destinationShift;
  }
  SumoU32 keepMask = 0xffffff - (0xffu << destinationShift);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    destination[word] =
        (destination[word] & keepMask) | g_textureWorkBuffer[word];
  }
}

void MixTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex,
                      SumoS32 amount) {
  SumoU8 *destination = g_textureLayers[destinationIndex];
  SumoU8 *source = g_textureLayers[sourceIndex];
  SumoS32 scaled = (amount & ~1) << 7;
  SumoU8 *sourceMap = g_textureColorMap + 0x7f00 - scaled;
  SumoU8 *destinationMap = g_textureColorMap + scaled;
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    destination[0] =
        (SumoU8)(sourceMap[source[0]] + destinationMap[destination[0]]);
    destination[1] =
        (SumoU8)(sourceMap[source[1]] + destinationMap[destination[1]]);
    destination[2] =
        (SumoU8)(sourceMap[source[2]] + destinationMap[destination[2]]);
    destination += 4;
    source += 4;
  }
}

void MultiplyTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex];
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 destPixel = destination[word];
    SumoU32 srcPixel = source[word];
    SumoS32 red = ((SumoS32)srcPixel >> 16) * ((SumoS32)destPixel >> 16);
    SumoS32 green =
        (SumoS32)((srcPixel >> 8) & 0xff) * (SumoS32)((destPixel >> 8) & 0xff);
    SumoS32 blue = (SumoS32)(srcPixel & 0xff) * (SumoS32)(destPixel & 0xff);
    destination[word] =
        (SumoU32)((((red >> 8) << 8 | (green >> 8)) << 8) | (blue >> 8));
  }
}

void InvertTextureLayerLowBytes(SumoS32 index) {
  SumoU8 *layer = g_textureLayers[index];
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    *layer = (SumoU8)(*layer ^ 0xff);
    layer += 4;
  }
}

void AdjustTextureContrast(SumoS32 layerIndex, SumoS32 amount) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoF64 scale = (SumoF64)amount * g_textureContrastScale;
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 pixel = layer[word];
    SumoS32 red =
        (SumoS32)((SumoF64)((SumoS32)((pixel >> 16) & 0xff) - 0x80) * scale);
    SumoS32 green =
        (SumoS32)((SumoF64)((SumoS32)((pixel >> 8) & 0xff) - 0x80) * scale);
    SumoS32 blue = (SumoS32)((SumoF64)((SumoS32)(pixel & 0xff) - 0x80) * scale);
    if (red > 0x7f) {
      red = 0x7f;
    }
    if (green > 0x7f) {
      green = 0x7f;
    }
    if (blue > 0x7f) {
      blue = 0x7f;
    }
    if (red < -0x7f) {
      red = -0x7f;
    }
    if (green < -0x7f) {
      green = -0x7f;
    }
    if (blue < -0x7f) {
      blue = -0x7f;
    }
    layer[word] =
        (SumoU32)(((red + 0x80) << 16) | ((green + 0x80) << 8) | (blue + 0x80));
  }
}

void ApplyTextureColorMap(SumoS32 layerIndex, SumoS32 mapBank) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoU32 bank = (SumoU32)(mapBank << 8);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 pixel = layer[word];
    SumoU32 red = g_textureColorMap[((pixel >> 16) & 0xff) + bank];
    SumoU32 green = g_textureColorMap[((pixel >> 8) & 0xff) + bank];
    SumoU32 blue = g_textureColorMap[(pixel & 0xff) + bank];
    layer[word] = ((red << 8 | green) << 8) | blue;
  }
}

void ApplyTextureCosineWave(SumoS32 layerIndex, char channel,
                            SumoS32 frequency) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 shift = 16 - ((channel << 3) & 0xff);
  SumoF64 omega = (SumoF64)frequency * g_textureTau * g_textureInvSize;
  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 pixel = layer[word];
    SumoS32 value = (SumoS32)((pixel >> shift) & 0xff);
    SumoS32 wave =
        (SumoS32)(g_textureWaveAmplitude -
                  cos((SumoF64)value * omega) * g_textureWaveAmplitude);
    layer[word] = (pixel & keepMask) | ((SumoU32)wave << shift);
  }
}

void RemapTextureChannelRange(SumoS32 layerIndex, char channel,
                              SumoS32 rangeStart, SumoS32 rangeEnd) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  SumoS32 shift = 16 - ((channel << 3) & 0xff);
  SumoS32 range = rangeEnd - rangeStart;
  if (range == 0) {
    range = 1;
  }
  SumoF64 scale = (SumoF64)range * g_textureInvSize;
  SumoF64 base = (SumoF64)rangeStart;
  SumoU32 keepMask = 0xffffff - (0xffu << shift);
  for (SumoS32 word = 0; word < 0x10000; ++word) {
    SumoU32 pixel = layer[word];
    SumoS32 value = (SumoS32)((pixel >> shift) & 0xff);
    SumoS32 remapped = (SumoS32)(base + (SumoF64)value * scale);
    layer[word] = (pixel & keepMask) | ((SumoU32)remapped << shift);
  }
}

SumoU32 *ExpandTextureBitmap(SumoS32 planeIndex, SumoU8 *bits,
                             SumoU32 zeroValue, SumoU32 oneValue) {
  SumoU32 *plane = (SumoU32 *)g_textureLayers[planeIndex];
  SumoU32 *destination = plane;
  for (SumoS32 byteIndex = 0; byteIndex < 0x2000; ++byteIndex) {
    SumoU8 packed = bits[byteIndex];
    for (SumoS32 bit = 0; bit < 8; ++bit) {
      *destination++ = (packed & 1) ? oneValue : zeroValue;
      packed = (SumoU8)(packed >> 1);
    }
  }
  return plane + 0x10000;
}

SumoS32 BlurTextureLayer(SumoS32 layerIndex, SumoS32 passCount) {
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  if (passCount <= 0)
    return passCount;
  for (SumoS32 pass = passCount; pass != 0; --pass) {
    SumoS32 writeIndex = 0;
    for (SumoS32 row = 0; row < 0x100; ++row) {
      SumoU32 *rowAbove = layer + (((row - 1) & 0xff) << 8);
      SumoU32 *rowBelow = layer + (((row + 1) & 0xff) << 8);
      SumoU32 *rowCenter = layer + (row << 8);
      for (SumoS32 column = 0; column < 0x100; ++column) {
        SumoU32 above = rowAbove[column];
        SumoU32 below = rowBelow[column];
        SumoU32 center = rowCenter[column];
        SumoU32 left = rowCenter[(column - 1) & 0xff];
        SumoU32 right = rowCenter[(column + 1) & 0xff];
        SumoS32 red =
            (SumoS32)(((right >> 16) & 0xff) + ((center >> 16) & 0xff) * 4 +
                      ((above >> 16) & 0xff) + ((left >> 16) & 0xff) +
                      ((below >> 16) & 0xff)) >>
            3;
        SumoS32 green =
            (SumoS32)(((right >> 8) & 0xff) + ((center >> 8) & 0xff) * 4 +
                      ((above >> 8) & 0xff) + ((left >> 8) & 0xff) +
                      ((below >> 8) & 0xff)) >>
            3;
        SumoS32 blue =
            (SumoS32)((right & 0xff) + (center & 0xff) * 4 + (above & 0xff) +
                      (left & 0xff) + (below & 0xff)) >>
            3;
        g_textureWorkBuffer[writeIndex] =
            (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
        ++writeIndex;
      }
    }
    memcpy(layer, g_textureWorkBuffer, 0x40000);
  }
  return 0;
}

void DirectionalBlurTextureLayer(SumoS32 destinationIndex,
                                 SumoS32 directionIndex, char directionChannel,
                                 SumoS32 sampleCount) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *direction = (SumoU32 *)g_textureLayers[directionIndex];
  SumoS32 shift = (2 - directionChannel) << 3;

  SumoS32 writeIndex = 0;
  for (SumoS32 row = 0; row < 0x100; ++row) {
    for (SumoS32 column = 0; column < 0x100; ++column) {
      SumoF64 redAccum = g_vectorZero;
      SumoF64 greenAccum = g_vectorZero;
      SumoF64 blueAccum = g_vectorZero;
      SumoS32 angleByte = (SumoS32)((direction[writeIndex] >> shift) & 0xff);
      SumoF64 angle = (SumoF64)angleByte * g_textureRadiansPerPixel;
      SumoF32 sine = (SumoF32)sin(angle);
      SumoF32 cosine = (SumoF32)cos(angle);
      if (sampleCount > 0) {
        SumoS32 step = 0;
        for (SumoS32 sample = sampleCount; sample != 0; --sample) {
          SumoS32 sampleRow = (SumoS32)((SumoF64)step * cosine + row);
          SumoS32 sampleColumn = (SumoS32)((SumoF64)step * sine + column);
          SumoU32 pixel =
              destination[((sampleRow & 0xff) << 8) + (sampleColumn & 0xff)];
          redAccum += (SumoS32)pixel >> 16;
          greenAccum += (SumoS32)((pixel >> 8) & 0xff);
          blueAccum += (SumoS32)(pixel & 0xff);
          step += 2;
        }
      }
      SumoF32 sampleCountFloat = (SumoF32)sampleCount;
      SumoS32 red = (SumoS32)(redAccum / sampleCountFloat);
      SumoS32 green = (SumoS32)(greenAccum / sampleCountFloat);
      SumoS32 blue = (SumoS32)(blueAccum / sampleCountFloat);
      g_textureWorkBuffer[writeIndex] =
          (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
      ++writeIndex;
    }
  }
  memcpy(destination, g_textureWorkBuffer, 0x40000);
  BlurTextureLayer(destinationIndex, 2);
}

void AddTextureLayersSaturated(SumoS32 destinationIndex, SumoS32 sourceIndex) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex];
  for (SumoS32 count = 0x10000; count != 0; --count) {
    SumoU32 destinationPixel = *destination;
    SumoU32 sourcePixel = *source;
    SumoS32 red =
        ((SumoS32)sourcePixel >> 16) + ((SumoS32)destinationPixel >> 16);
    SumoS32 green = (SumoS32)(((sourcePixel >> 8) & 0xff) +
                              ((destinationPixel >> 8) & 0xff));
    SumoS32 blue = (SumoS32)((sourcePixel & 0xff) + (destinationPixel & 0xff));
    if (red > 0xff)
      red = 0xff;
    if (green > 0xff)
      green = 0xff;
    if (blue > 0xff)
      blue = 0xff;
    *destination = (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
    ++destination;
    ++source;
  }
}

void MaxTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex];
  for (SumoS32 count = 0x10000; count != 0; --count) {
    SumoU32 destinationPixel = *destination;
    SumoU32 sourcePixel = *source;
    SumoS32 red = (SumoS32)((sourcePixel >> 16) & 0xff);
    SumoS32 green = (SumoS32)((sourcePixel >> 8) & 0xff);
    SumoS32 blue = (SumoS32)(sourcePixel & 0xff);
    SumoS32 destinationRed = (SumoS32)((destinationPixel >> 16) & 0xff);
    SumoS32 destinationGreen = (SumoS32)((destinationPixel >> 8) & 0xff);
    SumoS32 destinationBlue = (SumoS32)(destinationPixel & 0xff);
    if (destinationRed > red)
      red = destinationRed;
    if (destinationGreen > green)
      green = destinationGreen;
    if (destinationBlue > blue)
      blue = destinationBlue;
    *destination = (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
    ++destination;
    ++source;
  }
}

void ApplyTextureGradient(SumoS32 layerIndex, SumoS8 channel, SumoS32 redLow,
                          SumoS32 redHigh, SumoS32 greenLow, SumoS32 greenHigh,
                          SumoS32 blueLow, SumoS32 blueHigh) {
  SumoU32 table[0x100];
  SumoS32 shift = (2 - channel) << 3;
  SumoS32 redRange = redHigh - redLow;
  SumoS32 greenRange = greenHigh - greenLow;
  SumoS32 blueRange = blueHigh - blueLow;
  for (SumoS32 index = 0; index < 0x100; ++index) {
    SumoS32 red =
        (SumoS32)((SumoF64)index * redRange * g_textureBlendScale + redLow);
    SumoS32 green =
        (SumoS32)((SumoF64)index * greenRange * g_textureBlendScale + greenLow);
    SumoS32 blue =
        (SumoS32)((SumoF64)index * blueRange * g_textureBlendScale + blueLow);
    table[index] = (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
  }

  SumoU32 *cursor = (SumoU32 *)g_textureLayers[layerIndex];
  for (SumoS32 pixel = 0; pixel < 0x10000; ++pixel) {
    cursor[pixel] = table[(cursor[pixel] >> shift) & 0xff];
  }
}

void BlendTextureLayersByMask(SumoS32 destinationIndex, SumoS32 sourceIndex,
                              SumoS32 maskIndex, SumoS8 maskChannel) {
  SumoU32 *destination = (SumoU32 *)g_textureLayers[destinationIndex];
  SumoU32 *source = (SumoU32 *)g_textureLayers[sourceIndex];
  SumoU32 *mask = (SumoU32 *)g_textureLayers[maskIndex];
  SumoS32 shift = (2 - maskChannel) << 3;
  for (SumoS32 count = 0x10000; count != 0; --count) {
    SumoS32 weight = 0xff - (SumoS32)((*mask >> shift) & 0xff);
    SumoU32 sourcePixel = *source;
    SumoU32 destinationPixel = *destination;
    SumoS32 destinationRed = (SumoS32)((destinationPixel >> 16) & 0xff);
    SumoS32 destinationGreen = (SumoS32)((destinationPixel >> 8) & 0xff);
    SumoS32 destinationBlue = (SumoS32)(destinationPixel & 0xff);
    SumoS32 sourceRed = (SumoS32)((sourcePixel >> 16) & 0xff);
    SumoS32 sourceGreen = (SumoS32)((sourcePixel >> 8) & 0xff);
    SumoS32 sourceBlue = (SumoS32)(sourcePixel & 0xff);
    SumoS32 red = (SumoS32)((SumoF64)(sourceRed - destinationRed) * weight *
                                g_textureBlendScale +
                            destinationRed);
    SumoS32 green = (SumoS32)((SumoF64)(sourceGreen - destinationGreen) *
                                  weight * g_textureBlendScale +
                              destinationGreen);
    SumoS32 blue = (SumoS32)((SumoF64)(sourceBlue - destinationBlue) * weight *
                                 g_textureBlendScale +
                             destinationBlue);
    *destination = (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
    ++destination;
    ++source;
    ++mask;
  }
}

void EmbossTextureLayer(SumoS32 layerIndex) {
  SumoS8 kernel[3];
  kernel[0] = -1;
  kernel[1] = 0;
  kernel[2] = 1;
  SumoU32 *layer = (SumoU32 *)g_textureLayers[layerIndex];
  for (SumoS32 row = 0; row < 0x100; ++row) {
    for (SumoS32 column = 0; column < 0x100; ++column) {
      SumoS32 red = 0;
      SumoS32 green = 0;
      SumoS32 blue = 0;
      for (SumoS32 kernelRow = 0; kernelRow < 3; ++kernelRow) {
        SumoS32 rowBase = ((row + kernelRow - 1) & 0xff) << 8;
        for (SumoS32 kernelColumn = 0; kernelColumn < 3; ++kernelColumn) {
          SumoS32 weight = kernel[kernelColumn];
          SumoU32 pixel = layer[rowBase + ((column + kernelColumn - 1) & 0xff)];
          red += (SumoS32)(pixel >> 16) * weight;
          green += (SumoS32)((pixel >> 8) & 0xff) * weight;
          blue += (SumoS32)(pixel & 0xff) * weight;
        }
      }
      red += 0x80;
      green += 0x80;
      blue += 0x80;
      if (red > 0xff)
        red = 0xff;
      if (green > 0xff)
        green = 0xff;
      if (blue > 0xff)
        blue = 0xff;
      if (red < 0)
        red = 0;
      if (green < 0)
        green = 0;
      if (blue < 0)
        blue = 0;
      g_textureWorkBuffer[(row << 8) + column] =
          (SumoU32)(((red << 8) | green) << 8) | (SumoU32)blue;
    }
  }
  memcpy(layer, g_textureWorkBuffer, 0x40000);
}

SumoS32 CreateGameAttenuationTexture();
SumoS32 CreateGameRampTexture();
void IgnoreGameTextureProgress(SumoF32);
void **BuildTextureSet(void **programs, void *progressCallback);
SumoS32 BlendTextIntoTexture(SumoU8 *pixels, const char *text, SumoS32 x,
                             SumoS32 y, SumoS32 textureWidth, SumoS32 width,
                             SumoS32 height, SumoS32 fontHeight,
                             SumoS32 textColor, SumoS32 backgroundColor,
                             const char *fontName);
SumoIntPtr CreateGameNormalMapTexture(SumoU8 *heightMap, SumoS32 width,
                                      SumoS32 height, SumoS32 depth);
SumoIntPtr CreateGameTextureFromPixels(void *pixels, SumoS32 width,
                                       SumoS32 height, SumoS32 singleLevel);

extern SumoU8 g_textureLoadFromTga;
extern SumoU8 g_textureUseMmxSampler;
extern SumoIntPtr g_gameTextures[256];
extern char g_gameTimesFont[];
extern char g_gameConsoleFont[];
extern SumoU32 g_gameTextureScratch[];
extern SumoIntPtr g_gameFontAtlasTexture;

SumoS32 InitializeGameTextures() {
  CreateGameAttenuationTexture();
  CreateGameRampTexture();
  g_textureLoadFromTga = 0;
  g_textureUseMmxSampler = 1;
  void **pixelSets = BuildTextureSet((void **)g_gameTexturePrograms,
                                     (void *)IgnoreGameTextureProgress);

  for (SumoS32 index = 0; g_gameTexturePrograms[index] != 0; ++index) {
    SumoU8 *pixels = (SumoU8 *)pixelSets[index];
    SumoS32 labelIndex = (index / 2 - MENU_START_INDEX);

    if (index >= (MENU_START_INDEX * 2)) {
      char (*line)[24] = &g_gameMenuLabels[labelIndex][0];
      if ((*line)[0] != 0) {
        SumoS32 textColor = (index & 1) * 0x7f7f7f;
        SumoS32 labelY = 6;
        do {
          BlendTextIntoTexture(pixels, *line, 0xa, labelY, 0x100, 0xf6, 0x20,
                               0x18, textColor, 0xffffff, g_gameTimesFont);
          labelY += 0x2a;
          ++line;
        } while ((*line)[0] != 0);
      }
    }

    if ((index & 1) == 0)
      g_gameTextures[index] =
          CreateGameNormalMapTexture(pixels, 0x100, 0x100, -0x64);
    else
      g_gameTextures[index] =
          CreateGameTextureFromPixels(pixels, 0x100, 0x100, 0);
  }

  for (SumoS32 word = 0; word < 4194304; ++word)
    g_gameTextureScratch[word] = 0xffffffffu;

  for (SumoS32 glyph = 0; glyph < 0x400; ++glyph) {
    char glyphText[2];
    glyphText[0] = (char)glyph;
    glyphText[1] = 0;
    BlendTextIntoTexture((SumoU8 *)g_gameTextureScratch, glyphText,
                         ((glyph & 0xf) << 4) * 4, ((glyph / 0x10) << 4) * 4, 1024, 0x40,
                         0x40, (0xc * 4), 0, 0xffffff, g_gameConsoleFont);
  }

  for (SumoU32 *cursor = g_gameTextureScratch;
       cursor < g_gameTextureScratch + 4194304; ++cursor)
    *cursor = ~*cursor;

  g_gameFontAtlasTexture =
      CreateGameTextureFromPixels(g_gameTextureScratch, 1024, 1024, 1);
  return (SumoS32)g_gameFontAtlasTexture;
}

extern const SumoF32 g_textureByteMaximumFloat;
extern const SumoF32 g_gameRampBias;
extern const SumoF32 g_gameRampStep32;
extern const SumoF32 g_gameRampStep64;
extern const SumoF64 g_gameRampDecayTwoPercent;
extern const SumoF64 g_gameRampDecayFivePercent;
extern const SumoF64 g_gameRampDecayOnePercent;
extern SumoU32 g_gameTextureScratch[];
extern SumoIntPtr g_gameRampTexture;
extern SumoIntPtr g_gameAttenuationTexture;

SumoIntPtr CreateGameTextureFromPixels(void *, SumoS32, SumoS32, SumoS32);

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

SumoIntPtr CreateGameTextureFromPixels(void *pixels, SumoS32 width,
                                       SumoS32 height, SumoS32 singleLevel);

SumoIntPtr CreateGameNormalMapTexture(SumoU8 *heightMap, SumoS32 width,
                                      SumoS32 height, SumoS32 depth) {
  SumoU8 *pixels = new SumoU8[width * height * 4];
  SumoU8 *cursor = pixels;
  SumoU8 *row = heightMap;
  SumoU8 *rowAbove = heightMap + (height - 1) * width * 4;

  SumoS32 lengthSign = 2;
  if (depth < 0)
    lengthSign = -2;
  SumoS32 depthSquared = depth * depth;
  SumoS32 depthScaled = depth << 8;
  SumoF32 lengthSignFloat = (SumoF32)lengthSign;

  for (SumoS32 rowIndex = 0; rowIndex < height; ++rowIndex) {
    SumoU8 *current = row;
    SumoU8 *left = row + width * 4 - 4;
    SumoS32 aboveOffset = (SumoS32)(rowAbove - row);

    for (SumoS32 column = 0; column < width; ++column) {
      SumoS32 deltaX = (SumoS32)*current - (SumoS32)*left;
      SumoS32 deltaY = (SumoS32)*current - (SumoS32)(current[aboveOffset]);
      SumoS32 lengthSquared = deltaY * deltaY + depthSquared + deltaX * deltaX;
      SumoS32 length = (SumoS32)(sqrt((double)lengthSquared) * lengthSignFloat);

      cursor[0] = (SumoU8)((SumoU8)((deltaX << 8) / length) + 0x7f);
      cursor[1] = (SumoU8)((SumoU8)((deltaY << 8) / length) + 0x7f);
      cursor[2] = (SumoU8)((SumoU8)(depthScaled / length) + 0x7f);
      cursor[3] = 0;
      cursor += 4;

      left = current;
      current += 4;
    }

    rowAbove = row;
    row += width * 4;
  }

  SumoIntPtr texture = CreateGameTextureFromPixels(pixels, width, height, 0);
  delete[] pixels;
  return texture;
}

extern const double g_gameProjectionHalfFov;
extern const SumoF32 g_gameProjectionMinimum;
extern const SumoF32 g_gameNegativeHalf;
extern const SumoF32 g_gameTwo;
extern SumoF32 g_gameAspectRatio;
extern SumoS32 g_gameRenderWidth;
extern SumoS32 g_gameRenderHeight;
extern SumoF32 g_gameProjectionOffsetX;
extern SumoF32 g_gameProjectionOffsetY;
extern SumoF32 g_gameProjectionScaleX;
extern SumoF32 g_gameProjectionScaleY;

HRESULT SetGameTransform(SumoU32 state, const SumoF32 *matrix);

SumoS32 ApplyGameProjection() {
  SumoF32 vertical = g_gameAspectRatio;
  double tangent = tan(g_gameProjectionHalfFov);
  vertical = (SumoF32)(tangent / vertical);
  if (vertical < g_gameProjectionMinimum) {
    tangent = tangent / vertical * g_gameProjectionMinimum;
    vertical = g_gameProjectionMinimum;
  }
  double inverseTangent = 1.0 / tangent;

  SumoF32 matrix[16];
  matrix[10] = 1.0000250339508057f;
  matrix[14] = -0.10000250488519669f;

  double inverseVertical = 1.0 / vertical;
  SumoF32 renderWidth = (SumoF32)g_gameRenderWidth;
  g_gameProjectionOffsetX = g_gameNegativeHalf * renderWidth;
  SumoF32 renderHeight = (SumoF32)g_gameRenderHeight;
  g_gameProjectionOffsetY = g_gameNegativeHalf * renderHeight;
  g_gameProjectionScaleX = (SumoF32)(g_gameTwo / inverseTangent / renderWidth);
  g_gameProjectionScaleY =
      (SumoF32)(g_gameTwo / inverseVertical / renderHeight);

  matrix[0] = (SumoF32)inverseTangent;
  matrix[4] = 0.0f;
  matrix[8] = 0.0f;
  matrix[12] = 0.0f;
  matrix[1] = 0.0f;
  matrix[5] = (SumoF32)inverseVertical;
  matrix[9] = 0.0f;
  matrix[13] = 0.0f;
  matrix[2] = 0.0f;
  matrix[6] = 0.0f;
  matrix[3] = 0.0f;
  matrix[7] = 0.0f;
  matrix[11] = 1.0f;
  matrix[15] = 0.0f;
  return SetGameTransform(3, matrix);
}

SumoS32 ApplyGameProjection();

// FUNCTION: SUMO 0x00403975
// FUNCTION: EDITOR 0x00403975
SumoS32 RefreshGameProjection() { return ApplyGameProjection(); }

extern SumoS32 g_gameMouseX;
extern SumoS32 g_gameMouseY;
extern SumoF32 g_gameProjectionOffsetX;
extern SumoF32 g_gameProjectionOffsetY;
extern SumoF32 g_gameProjectionScaleX;
extern SumoF32 g_gameProjectionScaleY;

// GLOBAL: SUMO 0x00c06154
// GLOBAL: EDITOR 0x00c06974
Matrix3 g_gameInverseViewMatrix;

// FUNCTION: SUMO 0x00407772
// FUNCTION: EDITOR 0x00407794
Vector3 GetGameMouseRayDirection() {
  Vector3 direction = MakeVector3(
      (g_gameMouseX + g_gameProjectionOffsetX) * g_gameProjectionScaleX,
      -(g_gameMouseY + g_gameProjectionOffsetY) * g_gameProjectionScaleY, 1.0f);
  direction = direction.Transform(g_gameInverseViewMatrix);
  direction.Normalize();
  return direction;
}

extern const char g_gameScreenshotFormat[];
extern const char g_gameScreenshotReadMode[];
extern const char g_gameScreenshotWriteMode[];
extern char *g_gameScreenshotPrefix;
extern SumoS32 g_gameScreenshotIndex;
extern SumoS32 g_gameConfiguredWidth;
extern SumoS32 g_gameConfiguredHeight;

SumoS32 WriteGameScreenshot() {
  char filename[0x104];
  FILE *probe;
  do {
    sprintf(filename, g_gameScreenshotFormat, g_gameScreenshotPrefix,
            g_gameScreenshotIndex);
    probe = fopen(filename, g_gameScreenshotReadMode);
    if (probe != 0)
      fclose(probe);
    ++g_gameScreenshotIndex;
  } while (probe != 0);

  SumoS32 pitch = 0;
  SumoU8 *locked = AcquireGameBackBufferPixels(&pitch);
  if (locked == 0)
    return 0;

  SumoS32 width = g_gameConfiguredWidth;
  SumoS32 height = g_gameConfiguredHeight;
  SumoU8 *pixels = new SumoU8[(size_t)height * width * 4];
  SumoU8 *lockedCopy = new SumoU8[(size_t)(height * (pitch / 4)) * 4];
  memcpy(lockedCopy, locked, (size_t)height * pitch);
  ReleaseGameBackBufferPixels(locked);

  SumoS32 sourceRow = height - 1;
  for (SumoS32 destinationRow = 0; destinationRow < height;
       ++destinationRow, --sourceRow) {
    memcpy(pixels + (size_t)destinationRow * width * 4,
           lockedCopy + (size_t)(sourceRow * (pitch / 4)) * 4,
           (size_t)width * 4);
  }

  SumoU8 header[0x36];
  memset(header, 0, sizeof(header));
  header[0] = 'B';
  header[1] = 'M';
  header[2] = 0x36;
  header[3] = 0x30;
  header[10] = 0x36;
  header[14] = 0x28;
  header[18] = (SumoU8)(width & 0xff);
  header[19] = (SumoU8)((width >> 8) & 0xff);
  header[22] = (SumoU8)(height & 0xff);
  header[23] = (SumoU8)((height >> 8) & 0xff);
  header[26] = 1;
  header[28] = 0x20;
  header[35] = 0x1e;
  header[38] = 0xc6;
  header[39] = 0x11;
  header[42] = 0xc6;
  header[43] = 0x11;

  FILE *stream = fopen(filename, g_gameScreenshotWriteMode);
  fwrite(header, 1, 0x36, stream);
  fwrite(pixels, 1, (size_t)(height * width) * 4, stream);
  fclose(stream);
  delete[] lockedCopy;
  delete[] pixels;
  return 0;
}

extern FloatVector g_waterHeights;
extern SumoS32 g_waterGridWidth;
extern SumoS32 g_waterGridHeight;
extern SumoF32 g_gameSimulationStep;
extern Vector3 g_gameCameraWorldPosition;
extern const SumoF32 g_gameArenaHalfExtent;
extern const SumoF32 g_freeCameraPositionRecordScale;

void RenderWaterSurface() {
 // if (!g_waterHeights.HasElements())
    return;

  SumoS32 width = g_waterGridWidth;
  SumoS32 height = g_waterGridHeight;
  SumoU8 *vertices = BeginGameWaterVertices(width * height * 9 * 16);
  if (vertices == 0)
    return;

  static const SumoS32 c_heightOffsets[6] = {0, 1, 0, 1, 0, 0};
  SumoS32 heightSteps[6];
  heightSteps[0] = 0;
  heightSteps[1] = 1;
  heightSteps[2] = width;
  heightSteps[3] = 1;
  heightSteps[4] = width + 1;
  heightSteps[5] = width;
  static const SumoS32 c_columnOffsets[6] = {0, 1, 0, 1, 1, 0};
  static const SumoS32 c_rowOffsets[6] = {0, 0, 1, 0, 1, 1};
  (void)c_heightOffsets;

  SumoU8 *cursor = vertices;
  SumoS32 cellIndex = 0;
  for (SumoS32 row = 0; row < height - 1; ++row) {
    SumoF32 rowBase = (SumoF32)row;
    for (SumoS32 column = 0; column < width - 1; ++column) {
      Vector3 normal = MakeVector3(
          g_waterHeights[cellIndex] - g_waterHeights[cellIndex + 1],
          g_gameSimulationStep,
          g_waterHeights[cellIndex] - g_waterHeights[cellIndex + width]);
      normal.Normalize();
      Vector3 position =
          MakeVector3((SumoF32)((SumoF64)column * g_gameSimulationStep),
                      g_waterHeights[cellIndex],
                      (SumoF32)((SumoF64)rowBase * g_gameSimulationStep));
      Vector3 view = position - g_gameCameraWorldPosition;
      SumoF32 reflectionScale =
          (SumoF32)(((SumoF64)view.z * normal.z + (SumoF64)view.y * normal.y +
                     (SumoF64)view.x * normal.x) *
                    2.0);
      Vector3 reflection = view - normal.Scale(reflectionScale);
      reflection.Normalize();
      SumoS32 shade = (SumoS32)((SumoF64)reflection.y * g_gameArenaHalfExtent +
                                g_freeCameraPositionRecordScale);
      SumoU32 color = (SumoU32)(shade * 0x1030401) + 0xc0;

      for (SumoS32 corner = 0; corner < 6; ++corner) {
        *(SumoU32 *)(cursor + 0xc) = color;
        Vector3 cornerPosition =
            MakeVector3((SumoF32)((SumoF64)(column + c_columnOffsets[corner]) *
                                  g_gameSimulationStep),
                        g_waterHeights[cellIndex + heightSteps[corner]],
                        (SumoF32)((SumoF64)(row + c_rowOffsets[corner]) *
                                  g_gameSimulationStep));
        memcpy(cursor, &cornerPosition, sizeof(Vector3));
        *(SumoF32 *)(cursor + 0x10) = 0.0f;
        *(SumoF32 *)(cursor + 0x14) = 0.0f;
        cursor += 0x18;
      }
      ++cellIndex;
    }
    ++cellIndex;
  }

  FinishGameWaterVertices((height - 1) * (width - 1) * 2);
}

extern GameMan g_gameMen[];
extern GameMan *g_nextGameMan;
extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_gameMode;
extern SumoS32 g_sumoMode;
extern SumoS32 g_gameAlternateCameraMode;
extern Matrix3 g_gameInverseViewMatrix;
extern Vector3 g_gameCameraWorldPosition;
extern Vector3 g_gameCameraFocus;
extern Vector3 g_gameCameraPosition;
extern Vector3 g_gameCameraAngles;
extern Vector3 g_gameCameraAcceleration;
extern Vector3 g_gameCameraVelocity;
extern Vector3 g_gameCameraAngularVelocity;
extern SumoF32 g_gameCameraInputB;
extern SumoF32 g_gameCameraZoomVelocity;
extern SumoF32 g_gameCameraDistanceScale;
extern SumoF32 g_gameCameraMoveScale;
extern SumoF32 g_gameCameraTurnScale;
extern const SumoF32 g_gameCameraNormalTurnStep;
extern const SumoF32 g_gameCameraZoomStep;
extern const SumoF32 g_gameCameraInputDamping;
extern const SumoF32 g_gameCameraMinimumDistance;
extern const SumoF32 g_gameCameraMinimumDistanceScale;
extern const SumoF32 g_gameCameraDistanceBias;
extern const SumoF32 g_gameCameraGroupRadiusScale;
extern const SumoF32 g_gameCameraFacingEpsilon;
extern const SumoF32 g_gameCameraHeightBaseline;
extern const SumoF32 g_gameCameraHeightScale;
extern const SumoF32 g_gameCameraHeightOffset;
extern const SumoF64 g_gameCameraFastSpringDistanceSquared;
extern const SumoF32 g_gameCameraInputOffsetScale;
extern const SumoF32 g_gameCameraVelocityDamping;
extern const SumoF32 g_gameCameraYawResponse;
extern const SumoF32 g_gameCameraPitchResponse;
extern const SumoF32 g_gameCameraAimDamping;
extern const SumoF32 g_gameManPoseImpulseGain;
extern const SumoF32 g_gameProjectileSpin;
extern const SumoF32 g_gameOne;

static __forceinline Vector3 MakeGameCameraVector3(SumoF32 p_x, SumoF32 p_y,
                                                   SumoF32 p_z) {
  Vector3 result;
  result.x = p_x;
  result.y = p_y;
  result.z = p_z;
  return result;
}
GameMan *lastManFocused;

void UpdateGameCamera() {
  Vector3 direction = MakeGameCameraVector3(0.0f, 0.0f, 0.0f);
  Vector3 focus = direction;
  SumoF32 searchRadius = 50.0f;

  if (g_nextGameMan - g_gameMen > 0) {
    focus = g_gameCameraFocus;
    Vector3 zeroStep = MakeGameCameraVector3(0.0f, 0.0f, 0.0f);
    Vector3 acceptedFocus = focus;
    Vector3 acceptedDirection = direction;
    SumoF32 stepScale = 0.1f;
    SumoF32 bestDistanceSquared = 1e35f;
    SumoF32 farthestDistanceSquared = 0.0f;

    for (SumoS32 iteration = 64; iteration != 0; --iteration) {
      farthestDistanceSquared = 0.0f;
      direction = zeroStep;
      bool m_bOneManFound = false;
      for (GameMan *man = g_gameMen; man < g_nextGameMan; ++man) {

        if (man->m_bLobotomized)
          continue;
        m_bOneManFound = true;
        if ((man->centerOfMass - focus).LengthSquared() >
            farthestDistanceSquared) {
          farthestDistanceSquared = (man->centerOfMass - focus).LengthSquared();
          direction = (man->centerOfMass - focus).Normalized();
        }

        lastManFocused = man;
      }
      if (!m_bOneManFound) {
        GameMan *man = lastManFocused;
        if ((man->centerOfMass - focus).LengthSquared() >
            farthestDistanceSquared) {
          farthestDistanceSquared = (man->centerOfMass - focus).LengthSquared();
          direction = (man->centerOfMass - focus).Normalized();
        }
      }

      if (bestDistanceSquared < farthestDistanceSquared) {
        stepScale = stepScale * g_gameManPoseImpulseGain;
        focus = acceptedFocus;
        direction = acceptedDirection;
      } else {
        bestDistanceSquared = farthestDistanceSquared;
        stepScale = stepScale * 1.1f;
      }
      acceptedFocus = focus;
      acceptedDirection = direction;
      Vector3 step = direction.Scale(stepScale);
      focus.AddInline(step);
    }

    focus = acceptedFocus;
    searchRadius = (SumoF32)sqrt((double)farthestDistanceSquared);
  }

  SumoF32 turnInput = 0.0f;
  g_gameCameraFocus = focus;
  SumoS32 state = g_levelLoadState[4];

  if ((state == 2 || state == 11 || g_gameMode == 3) && g_gameMode != 1) {
    g_gameCameraTurnScale = 0.0f;
    SumoF32 turnStep = g_gameCameraNormalTurnStep;
    if (state == 11)
      turnStep = 0.02f;
    if (g_gameKeyDown[c_gameCameraTurnRightInput])
      turnInput = turnStep;
    if (g_gameKeyDown[c_gameCameraTurnLeftInput])
      turnInput = turnInput - turnStep;
  } else {
    g_gameCameraTurnScale = 0.0f;
    if (state == 1 && g_gameAlternateCameraMode == 0)
      g_gameCameraTurnScale = 0.5f;
  }

  SumoF32 zoomVelocity = g_gameCameraZoomVelocity;
  if (g_gameKeyDown[c_gameCameraZoomInInput])
    zoomVelocity = zoomVelocity - g_gameCameraZoomStep;
  if (g_gameKeyDown[c_gameCameraZoomOutInput])
    zoomVelocity = zoomVelocity + g_gameCameraZoomStep;
  g_gameCameraDistanceScale =
      g_gameCameraDistanceScale +
      (g_gameCameraZoomVelocity = zoomVelocity * g_gameCameraInputDamping);
  if (g_gameCameraDistanceScale < g_gameCameraMinimumDistance)
    g_gameCameraDistanceScale = g_gameCameraMinimumDistance;

  g_gameCameraInputB = g_gameCameraInputB + turnInput;

  Vector3 offset = MakeGameCameraVector3(0.0f, 40.0f, -100.0f);
  Vector3 aimTarget = MakeGameCameraVector3(0.0f, 0.0f, 0.0f);
  Vector3 desired = offset;

  if (g_nextGameMan - g_gameMen > 0) {
    SumoS32 count = (SumoS32)(g_nextGameMan - g_gameMen);
    Vector3 anchor = g_gameMen[0].centerOfMass;
    Vector3 target = anchor;
    SumoF32 cameraDistance = 50.0f;
    if (g_sumoMode == 2) 
    {
      count = 4;
    }
    if (count == 2) {
      target = g_gameMen[1].CalculateCenterOfMassPosition();
      cameraDistance =
          (SumoF32)sqrt((double)(anchor - target).LengthSquared()) * 1.37f +
          g_gameCameraDistanceScale * 3.0f - g_gameCameraDistanceBias;
    } else if (count > 2 && count <= 4) {
      anchor = focus;
      target = focus;
      cameraDistance = g_gameCameraDistanceScale * g_gameProjectileSpin *
                       searchRadius * g_gameCameraGroupRadiusScale;
    }

    SumoF32 minimumDistance =
        g_gameCameraDistanceScale * g_gameCameraMinimumDistanceScale;
    if (cameraDistance < minimumDistance)
      cameraDistance = minimumDistance;

    offset = target - anchor;
    offset.y = 0.0f;
    if (offset.z * offset.z + offset.x * offset.x < g_gameCameraFacingEpsilon) {
      offset = MakeGameCameraVector3(-1.0f, 0.0f, 1.0f);
    }
    offset.Normalize();
    if (g_gameMode == 3)
      offset = MakeGameCameraVector3(0.0f, 0.0f, 1.0f);

    SumoF32 angle = g_gameCameraMoveScale - g_gameCameraTurnScale;
    SumoF32 cosine = (SumoF32)cos((double)angle);
    Vector3 spin = MakeVector3(cosine, 0.0f, (SumoF32)sin((double)angle));
    Vector3 upScaled = MakeGameCameraVector3(0.0f, 0.75f, 0.0f);
    spin = spin.Cross(upScaled);

    g_gameCameraMoveScale =
        (spin.z * offset.z + spin.x * offset.x + spin.y * offset.y) /
            cameraDistance * g_gameCameraInputDamping +
        g_gameCameraMoveScale;

    Vector3 yaw = MakeGameCameraVector3(
        0.0f, g_gameCameraInputB + g_gameCameraTurnScale, 0.0f);
    spin.Rotate(yaw);
    spin.x = spin.x * cameraDistance;
    spin.y = spin.y * cameraDistance;
    spin.z = spin.z * cameraDistance;

    SumoF32 half = 0.5f;
    aimTarget = (anchor + target).Scale(half);
    desired = aimTarget + spin;
    state = g_levelLoadState[4];
    desired.y = (cameraDistance - g_gameCameraHeightBaseline) *
                    g_gameCameraHeightScale +
                focus.y + g_gameCameraHeightOffset;
  }

  SumoF32 springConstant = 0.0003f;
  if (state == 2) {
    if ((desired - g_gameCameraPosition).LengthSquared() >
        g_gameCameraFastSpringDistanceSquared)
      springConstant = 0.002f;
  }

  SumoF32 springGain = 30.0f;
  Vector3 impulse =
      ((desired - g_gameCameraAngularVelocity) - g_gameCameraVelocity)
          .Scale(springConstant)
          .Scale(springGain);
  volatile SumoF32 velocityX = g_gameCameraVelocity.x + impulse.x;
  volatile SumoF32 velocityY = g_gameCameraVelocity.y + impulse.y;
  volatile SumoF32 velocityZ = g_gameCameraVelocity.z + impulse.z;

  Vector3 inputOffset = MakeGameCameraVector3(
      turnInput * g_gameCameraInputOffsetScale, 0.0f, 0.0f);
  Vector3 correction = ((desired - g_gameCameraPosition) +
                        inputOffset.Transform(g_gameInverseViewMatrix))
                           .Scale(springConstant);
  volatile SumoF32 dampedX = velocityX + correction.x;
  volatile SumoF32 dampedY = velocityY + correction.y;
  g_gameCameraVelocity.x = dampedX * g_gameCameraVelocityDamping;
  g_gameCameraVelocity.y = dampedY * g_gameCameraVelocityDamping;
  g_gameCameraVelocity.z =
      (velocityZ + correction.z) * g_gameCameraVelocityDamping;
  g_gameCameraAngularVelocity = desired;

  SumoF32 positionGain = 0.01f;
  Vector3 approach = (desired - g_gameCameraPosition).Scale(positionGain);
  volatile SumoF32 positionX = g_gameCameraPosition.x + approach.x;
  volatile SumoF32 positionY = g_gameCameraPosition.y + approach.y;
  g_gameCameraPosition.x = positionX + g_gameCameraVelocity.x;
  g_gameCameraPosition.y = positionY + g_gameCameraVelocity.y;
  g_gameCameraPosition.z =
      g_gameCameraPosition.z + approach.z + g_gameCameraVelocity.z;

  if (state == 10) {
    g_gameCameraPosition = MakeGameCameraVector3(-129.0f, 17.0f, 6.0f);
    g_gameCameraAngles = MakeGameCameraVector3(0.05f, -1.6650441f, 0.0f);
  }

  g_gameCameraWorldPosition = g_gameCameraPosition;
  g_gameInverseViewMatrix.SetIdentity();
  g_gameInverseViewMatrix.RotateColumns12(g_gameCameraAngles.x);
  g_gameInverseViewMatrix.RotateColumns02(g_gameCameraAngles.y);
  g_gameInverseViewMatrix.RotateColumns01(g_gameCameraAngles.z);

  Vector3 aim =
      g_gameInverseViewMatrix.Transform(aimTarget - g_gameCameraPosition);
  double inverseLength =
      g_gameOne / sqrt((double)(aim.z * aim.z + aim.y * aim.y + aim.x * aim.x));
  double accelerationY = g_gameCameraAcceleration.y -
                         aim.x * inverseLength * g_gameCameraYawResponse;
  g_gameCameraAcceleration.x =
      (SumoF32)((g_gameCameraAcceleration.x -
                 aim.y * inverseLength * g_gameCameraPitchResponse) *
                g_gameCameraAimDamping);
  g_gameCameraAcceleration.y =
      (SumoF32)(accelerationY * g_gameCameraAimDamping);
  g_gameCameraAcceleration.z =
      g_gameCameraAcceleration.z * g_gameCameraAimDamping;

  g_gameCameraAngles.x = g_gameCameraAcceleration.x + g_gameCameraAngles.x;
  g_gameCameraAngles.y = g_gameCameraAcceleration.y + g_gameCameraAngles.y;
  g_gameCameraAngles.z = g_gameCameraAcceleration.z + g_gameCameraAngles.z;

    GameAudioUpdateOrigin(
      g_gameCameraPosition,
      MakeVector3(0.0f, 0.0f, 1.0f).Transform(
                                                  g_gameInverseViewMatrix));
}
