#include "containers.h"
#include "decomp.h"
#include "types.h"


#include <windows.h>
#include <commdlg.h>

#include <d3d9.h>
#include <math.h>
#include <stdio.h>

extern Vector3 g_gameCameraWorldPosition;
void RenderWaterSurface();
#include <string.h>

extern IDirect3DDevice9 *g_gameD3DDevice;
extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gameMode;
extern const SumoF32 g_gameBoxDefaultValue;
extern char *g_gameScreenshotPrefix;
extern SumoS32 g_gameScreenshotIndex;

Vector3 *ResetGameCameraState();
SumoS32 WriteGameScreenshot();

// GLOBAL: SUMO 0x0042cb18
// GLOBAL: EDITOR 0x0042cb18
extern const char g_gameScreenshotFormat[] = "%s%d.bmp";

// GLOBAL: SUMO 0x0042c278
// GLOBAL: EDITOR 0x0042c278
extern const char g_gameScreenshotReadMode[] = "rb";

// GLOBAL: SUMO 0x0042c5b4
// GLOBAL: EDITOR 0x0042c5b4
extern const char g_gameScreenshotWriteMode[] = "wb";

// GLOBAL: SUMO 0x00c0eb38
// GLOBAL: EDITOR 0x00c0f358
extern SumoU32 g_gameTextureScratch[];

// GLOBAL: SUMO 0x00c4eb38
// GLOBAL: EDITOR 0x00c4f358
extern SumoU32 g_gameTextureScratchEnd;

// GLOBAL: SUMO 0x00d0eb38
// GLOBAL: EDITOR 0x00d0f358
SumoS32 g_gameRampTexture;

// GLOBAL: SUMO 0x00c0ea28
// GLOBAL: EDITOR 0x00c0f248
SumoS32 g_gameAttenuationTexture;

// GLOBAL: SUMO 0x0042cb28
// GLOBAL: EDITOR 0x0042cb28
extern const SumoF32 g_gameRampBias = 5.1f;

// GLOBAL: SUMO 0x0042c9f4
// GLOBAL: EDITOR 0x0042c9f4
extern const SumoF32 g_gameRampStep32 = 0.03125f;

// GLOBAL: SUMO 0x0042c9b0
// GLOBAL: EDITOR 0x0042c9b0
extern const SumoF32 g_gameFloorHalfExtent = 180.0f;

// GLOBAL: SUMO 0x0042c9f0
// GLOBAL: EDITOR 0x0042c9f0
extern const SumoF32 g_gameArenaVerticalHalfSize = -3.0f;

// GLOBAL: SUMO 0x0042cb40
// GLOBAL: EDITOR 0x0042cb40
extern const SumoF32 g_gameRampStep64 = 0.015625f;

// GLOBAL: SUMO 0x0042cb30
// GLOBAL: EDITOR 0x0042cb30
extern const double g_gameRampDecayTwoPercent = 0.02f;

// GLOBAL: SUMO 0x0042cb38
// GLOBAL: EDITOR 0x0042cb38
extern const double g_gameRampDecayFivePercent = 0.05f;

// GLOBAL: SUMO 0x0042cb48
// GLOBAL: EDITOR 0x0042cb48
extern const double g_gameRampDecayOnePercent = 0.01f;

// GLOBAL: SUMO 0x0042b318
// GLOBAL: EDITOR 0x0042b318
extern const double g_gameProjectionHalfFov = 0.6544984877109528;

// GLOBAL: SUMO 0x0042b314
// GLOBAL: EDITOR 0x0042b314
extern const SumoF32 g_gameProjectionMinimum = 0.55f;

// GLOBAL: SUMO 0x0042b310
// GLOBAL: EDITOR 0x0042b310
extern const SumoF32 g_gameNegativeHalf = -0.5f;

// GLOBAL: SUMO 0x0042b30c
// GLOBAL: EDITOR 0x0042b30c
extern const SumoF32 g_gameTwo = 2.0f;

// GLOBAL: SUMO 0x0042b2a0
// GLOBAL: EDITOR 0x0042b2a0
extern const SumoF32 g_gameCameraBackDistance = -100.0f;

// GLOBAL: SUMO 0x00c06338
// GLOBAL: EDITOR 0x00c06b58
SumoS32 g_gameAlternateCameraMode;

// GLOBAL: SUMO 0x004533e0
// GLOBAL: EDITOR 0x004533e0
SumoF32 g_gameCameraDistanceScale = 10.0f;

// GLOBAL: SUMO 0x004533d8
// GLOBAL: EDITOR 0x004533d8
SumoF32 g_gameCameraMoveScale = 1.5f;

// GLOBAL: SUMO 0x004533dc
// GLOBAL: EDITOR 0x004533dc
SumoF32 g_gameCameraTurnScale = 0.5f;

// GLOBAL: SUMO 0x00454fe0
// GLOBAL: EDITOR 0x00455000
Vector3 g_gameCameraPosition;

// GLOBAL: SUMO 0x0045503c
// GLOBAL: EDITOR 0x0045505c
Vector3 g_gameCameraAngles;

// GLOBAL: SUMO 0x00455068
// GLOBAL: EDITOR 0x00455088
Vector3 g_gameCameraAcceleration;

// GLOBAL: SUMO 0x00455028
// GLOBAL: EDITOR 0x00455048
Vector3 g_gameCameraVelocity;

// GLOBAL: SUMO 0x0045504c
// GLOBAL: EDITOR 0x0045506c
Vector3 g_gameCameraAngularVelocity;

// GLOBAL: SUMO 0x00455038
// GLOBAL: EDITOR 0x00455058
SumoF32 g_gameCameraInputA;

// GLOBAL: SUMO 0x00455048
// GLOBAL: EDITOR 0x00455068
SumoF32 g_gameCameraInputB;

// GLOBAL: SUMO 0x004533f0
// GLOBAL: EDITOR 0x004533f0
SumoF32 g_gameAspectRatio = 1.333f;

// GLOBAL: SUMO 0x004533e4
// GLOBAL: EDITOR 0x004533e4
SumoS32 g_gameRenderWidth = 1024;

// GLOBAL: SUMO 0x004533e8
// GLOBAL: EDITOR 0x004533e8
SumoS32 g_gameRenderHeight = 768;

// GLOBAL: SUMO 0x0045509c
// GLOBAL: EDITOR 0x004550bc
SumoF32 g_gameProjectionOffsetX;

// GLOBAL: SUMO 0x00455094
// GLOBAL: EDITOR 0x004550b4
SumoF32 g_gameProjectionOffsetY;

// GLOBAL: SUMO 0x004550a0
// GLOBAL: EDITOR 0x004550c0
SumoF32 g_gameProjectionScaleX;

// GLOBAL: SUMO 0x00455098
// GLOBAL: EDITOR 0x004550b8
SumoF32 g_gameProjectionScaleY;

// GLOBAL: SUMO 0x004550a4
// GLOBAL: EDITOR 0x004550c4
Vector3 g_gameViewOffset;

// GLOBAL: SUMO 0x004550b0
// GLOBAL: EDITOR 0x004550d0
Matrix3 g_gameViewMatrix;

// FUNCTION: SUMO 0x00402d01
// FUNCTION: EDITOR 0x00402d01
Vector3 *ResetGameCameraState() {
  g_gameCameraInputB = 0.0f;
  g_gameCameraInputA = 0.0f;

  Vector3 cameraPosition;
  cameraPosition.x = 0.0f;
  cameraPosition.y = 15.0f;
  cameraPosition.z = g_gameCameraBackDistance;

  g_gameCameraDistanceScale = 10.0f;
  g_gameCameraMoveScale = 1.5f;
  g_gameCameraTurnScale = 0.5f;
  g_gameCameraPosition = cameraPosition;

  if (g_gameAlternateCameraMode != 0) {
    cameraPosition.x = g_gameCameraBackDistance;
    cameraPosition.y = 7.0f;
    cameraPosition.z = 0.0f;
    g_gameCameraPosition = cameraPosition;
  }

  g_gameCameraAngles.z = 0.0f;
  g_gameCameraAngles.y = 0.0f;
  g_gameCameraAngles.x = 0.0f;
  if (g_gameMode != 0) {
    cameraPosition.x = g_gameCameraBackDistance;
    cameraPosition.y = 7.0f;
    cameraPosition.z = 0.0f;
    g_gameCameraPosition = cameraPosition;

    Vector3 cameraAngles;
    cameraAngles.x = 0.0f;
    cameraAngles.y = -1.5707964f;
    cameraAngles.z = 0.0f;
    g_gameCameraAngles = cameraAngles;
  }

  g_gameCameraAcceleration.z = 0.0f;
  g_gameCameraAcceleration.y = 0.0f;
  g_gameCameraAcceleration.x = 0.0f;
  g_gameCameraVelocity.z = 0.0f;
  g_gameCameraVelocity.y = 0.0f;
  g_gameCameraVelocity.x = 0.0f;
  g_gameCameraAngularVelocity.z = 0.0f;
  g_gameCameraAngularVelocity.y = 0.0f;
  g_gameCameraAngularVelocity.x = 0.0f;
  return &g_gameCameraPosition;
}

SumoS32 RefreshGameProjection();

// GLOBAL: SUMO 0x004536d8
// GLOBAL: EDITOR 0x004536d8
SumoS32 g_gameSelectedPlayer = -1;

// GLOBAL: SUMO 0x005115f0
// GLOBAL: EDITOR 0x00511e10
SumoS32 g_gameRoundTimer;

// GLOBAL: SUMO 0x004536dc
// GLOBAL: EDITOR 0x004536dc
SumoS32 g_gameRoundEnabled = 1;

// FUNCTION: SUMO 0x0040397a
// FUNCTION: EDITOR 0x0040397a
__declspec(naked) HRESULT SetGameViewTransform() {
  __asm {
    push ebp
    mov ebp, esp
    sub esp, 40h
    mov edx, dword ptr [eax]
    fldz
    fstp dword ptr [ebp - 34h]
    mov dword ptr [ebp - 40h], edx
    mov edx, dword ptr [eax + 0ch]
    fldz
    fstp dword ptr [ebp - 24h]
    mov dword ptr [ebp - 3ch], edx
    mov edx, dword ptr [eax + 18h]
    fldz
    mov dword ptr [ebp - 38h], edx
    mov edx, dword ptr [eax + 4]
    fstp dword ptr [ebp - 14h]
    fld dword ptr [ecx]
    mov dword ptr [ebp - 30h], edx
    mov edx, dword ptr [eax + 10h]
    fchs
    fstp dword ptr [ebp - 10h]
    mov dword ptr [ebp - 2ch], edx
    mov edx, dword ptr [eax + 1ch]
    fld dword ptr [ecx + 4]
    mov dword ptr [ebp - 28h], edx
    fchs
    mov edx, dword ptr [eax + 8]
    fstp dword ptr [ebp - 0ch]
    fld dword ptr [ecx + 8]
    mov dword ptr [ebp - 20h], edx
    mov edx, dword ptr [eax + 14h]
    fchs
    mov eax, dword ptr [eax + 20h]
    fstp dword ptr [ebp - 8]
    mov dword ptr [ebp - 1ch], edx
    fld1
    lea edx, dword ptr [ebp - 40h]
    push edx
    fstp dword ptr [ebp - 4]
    mov dword ptr [ebp - 18h], eax
    mov eax, dword ptr [g_gameD3DDevice]
    mov ecx, dword ptr [eax]
    push 2
    push eax
    call dword ptr [ecx + 0b0h]
    leave
    ret
  }
}

// FUNCTION: SUMO 0x004039f6
// FUNCTION: EDITOR 0x004039f6
HRESULT ApplyGameViewTransform() {
  Vector3 transformed = g_gameViewMatrix.Transform(g_gameViewOffset);
  __asm {
    lea ecx, transformed
    mov eax, offset g_gameViewMatrix
    call SetGameViewTransform
  }
}

// GLOBAL: SUMO 0x0045715c
// GLOBAL: EDITOR 0x0045717c
SumoS32 g_gameAdapterCount;

// FUNCTION: SUMO 0x00403a1e
// FUNCTION: EDITOR 0x00403a1e
SumoS32 FindGameAdapter(const GUID *identifier, IDirect3D9 *direct3D) {
  g_gameAdapterCount = direct3D->GetAdapterCount();
  for (SumoS32 index = 0; index < g_gameAdapterCount; ++index) {
    D3DADAPTER_IDENTIFIER9 adapter;
    direct3D->GetAdapterIdentifier(index, 0, &adapter);
    if (memcmp(&adapter.DeviceIdentifier, identifier, sizeof(GUID)) == 0) {
      return index;
    }
  }
  return -1;
}

struct GameDisplayMode {
  SumoS32 width;
  SumoS32 height;
  SumoS32 colorDepth;
  SumoS32 refreshRate;
};

// GLOBAL: SUMO 0x00457158
// GLOBAL: EDITOR 0x00457178
GameDisplayMode *g_gameDisplayModes;

// GLOBAL: SUMO 0x004571e4
// GLOBAL: EDITOR 0x00457204
IDirect3D9 *g_gameD3D;

// GLOBAL: SUMO 0x004571e0
// GLOBAL: EDITOR 0x00457200
void *g_gameDeviceResource;

// GLOBAL: SUMO 0x00457200
// GLOBAL: EDITOR 0x00457220
D3DCAPS9 g_gameDeviceCaps;

// FUNCTION: SUMO 0x00407d92
// FUNCTION: EDITOR 0x00407db4
Vector3 *ResetGameRoundState() {
  g_screenTintLevel = 0;
  g_gameSelectedPlayer = -1;
  g_gameRoundTimer = 0;
  g_gameRoundEnabled = 1;
  return ResetGameCameraState();
}

extern SumoU8 g_renderVertexScratch[];

// GLOBAL: SUMO 0x00a45ef0
// GLOBAL: EDITOR 0x00a46710
SumoU8 g_gameLineVertexScratch;

// GLOBAL: SUMO 0x00be5ff8
// GLOBAL: EDITOR 0x00be6818
SumoU8 *g_gameLineVertexCursor;

// GLOBAL: SUMO 0x00c06004
// GLOBAL: EDITOR 0x00c06824
SumoU8 *g_renderVertexCursor;

extern SumoS32 g_gameFontAtlasTexture;

HRESULT SetGameTexture(DWORD stage, IDirect3DBaseTexture9 *texture);
Vector3 TransformWavyTextPoint(Vector3 &point);
extern Matrix3 g_gameInverseViewMatrix;
extern const SumoF32 g_wavyTextDisplacement;

struct GameTextVertex {
  Vector3 position;
  SumoU32 color;
  SumoF32 u;
  SumoF32 v;
};

DECOMP_SIZE_ASSERT(GameTextVertex, 0x18);

#define EMIT_GAME_TEXT_VERTEX(positionExpression, vertexColor, textureU,       \
                              textureV)                                        \
  do {                                                                         \
    ((GameTextVertex *)g_renderVertexCursor)->position = (positionExpression); \
    ((GameTextVertex *)g_renderVertexCursor)->color = (vertexColor);           \
    ((GameTextVertex *)g_renderVertexCursor)->u = (textureU);                  \
    ((GameTextVertex *)g_renderVertexCursor)->v = (textureV);                  \
    g_renderVertexCursor += sizeof(GameTextVertex);                            \
  } while (0)

// GLOBAL: SUMO 0x004536ec
// GLOBAL: EDITOR 0x004536ec
SumoU32 g_gameMainVertexFvf = 322;

// GLOBAL: SUMO 0x004536f0
// GLOBAL: EDITOR 0x004536f0
SumoU32 g_gameLineVertexFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

// GLOBAL: SUMO 0x004536f4
// GLOBAL: EDITOR 0x004536f4
SumoU32 g_gamePositionVertexFvf = 2;

// GLOBAL: SUMO 0x00c06000
// GLOBAL: EDITOR 0x00c06820
IDirect3DVertexBuffer9 *g_gameMainVertexBuffer;

// GLOBAL: SUMO 0x00a45ee0
// GLOBAL: EDITOR 0x00a46700
IDirect3DVertexBuffer9 *g_gamePositionVertexBuffer;

// FUNCTION: SUMO 0x0040b81d
// FUNCTION: EDITOR 0x0040b83f
SumoS32 InitializeGameVertexBuffers() {
  RefreshGameProjection();

  g_gameD3DDevice->CreateVertexBuffer(
      0x240000, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, g_gameMainVertexFvf,
      D3DPOOL_DEFAULT, &g_gameMainVertexBuffer, NULL);
  return g_gameD3DDevice->CreateVertexBuffer(
      0x120000, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, g_gamePositionVertexFvf,
      D3DPOOL_DEFAULT, &g_gamePositionVertexBuffer, NULL);
}

// FUNCTION: SUMO 0x0040b958
// FUNCTION: EDITOR 0x0040b97a
void ResetRenderVertexScratch() {
  g_renderVertexCursor = g_renderVertexScratch;
}

// FUNCTION: SUMO 0x0040b963
// FUNCTION: EDITOR 0x0040b985
char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color) {
  Vector3 initialOffset;
  initialOffset.x = g_wavyTextDisplacement;
  initialOffset.y = g_wavyTextDisplacement;
  initialOffset.z = 0.0f;
  Vector3 point = initialOffset;
  Vector3 offset = point.Transform(g_gameInverseViewMatrix);

  const SumoF32 initialX = x;
  const SumoU32 shadowColor = (SumoU32)color & 0xff000000;

  while (*text != 0) {
    SumoF32 nextY;
    Vector3 corners[4];

    point = MakeVector3(x, y, 1.0f);
    corners[0] = TransformWavyTextPoint(point);
    SumoF32 nextX = x + 0.025f;
    Vector3 topRightPoint = MakeVector3(nextX, y, 1.0f);
    corners[1] = TransformWavyTextPoint(topRightPoint);
    nextY = y - 0.038f;
    Vector3 bottomLeftPoint;
    Vector3 bottomRightPoint = MakeVector3(nextX, nextY, 1.0f);
    corners[2] = TransformWavyTextPoint(bottomRightPoint);
    bottomLeftPoint = MakeVector3(x, nextY, 1.0f);
    corners[3] = TransformWavyTextPoint(bottomLeftPoint);

    signed char glyph = (signed char)*text;
    SumoF32 u0 = (SumoF32)(glyph & 15) * g_gameBoxDefaultValue;
    SumoF32 v0 = (SumoF32)(glyph / 16) * g_gameBoxDefaultValue;

    EMIT_GAME_TEXT_VERTEX(corners[0] - offset, shadowColor, u0, v0);
    SumoF32 u1;
    EMIT_GAME_TEXT_VERTEX(corners[1] - offset, shadowColor,
                          u1 = u0 + g_gameBoxDefaultValue, v0);
    SumoF32 v1;
    EMIT_GAME_TEXT_VERTEX(corners[3] - offset, shadowColor, u0,
                          v1 = v0 + g_gameBoxDefaultValue);
    EMIT_GAME_TEXT_VERTEX(corners[1] - offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2] - offset, shadowColor, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3] - offset, shadowColor, u0, v1);

    EMIT_GAME_TEXT_VERTEX(corners[0] + offset, shadowColor, u0, v0);
    EMIT_GAME_TEXT_VERTEX(corners[1] + offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[3] + offset, shadowColor, u0, v1);
    EMIT_GAME_TEXT_VERTEX(corners[1] + offset, shadowColor, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2] + offset, shadowColor, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3] + offset, shadowColor, u0, v1);

    EMIT_GAME_TEXT_VERTEX(corners[0], color, u0, v0);
    EMIT_GAME_TEXT_VERTEX(corners[1], color, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[3], color, u0, v1);
    EMIT_GAME_TEXT_VERTEX(corners[1], color, u1, v0);
    EMIT_GAME_TEXT_VERTEX(corners[2], color, u1, v1);
    EMIT_GAME_TEXT_VERTEX(corners[3], color, u0, v1);

    ++text;
    x = nextX;
    if (*text == '\n') {
      ++text;
      x = initialX;
      y = nextY;
    }
  }
  return text;
}

#undef EMIT_GAME_TEXT_VERTEX

// FUNCTION: SUMO 0x0040bf8e
// FUNCTION: EDITOR 0x0040bfb0
void FlushGameTextVertices() {
  g_gameD3DDevice->SetFVF(g_gameMainVertexFvf);
  if ((SumoS32)(g_renderVertexCursor - g_renderVertexScratch) / 24 != 0) {
    g_gameD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_gameD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_gameD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_gameD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_gameD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    g_gameD3DDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

    SetGameTexture(0, (IDirect3DBaseTexture9 *)g_gameFontAtlasTexture);
    g_gameD3DDevice->DrawPrimitiveUP(
        D3DPT_TRIANGLELIST,
        ((SumoS32)(g_renderVertexCursor - g_renderVertexScratch) / 24) / 3,
        g_renderVertexScratch, 24);
  }
}

// GLOBAL: SUMO 0x00775de0
// GLOBAL: EDITOR 0x00776600
extern SumoU8 g_gameBoxLitVertexStorage;

// GLOBAL: SUMO 0x00775df8
// GLOBAL: EDITOR 0x00776618
extern SumoU8 g_gameBoxLitVertexStorageSecond;

// GLOBAL: SUMO 0x00775e10
// GLOBAL: EDITOR 0x00776630
extern SumoU8 g_gameBoxLitVertexStorageThird;

// GLOBAL: SUMO 0x00ac5ef8
// GLOBAL: EDITOR 0x00ac6718
extern SumoU8 g_gameBoxShadowPositionStorage;

// GLOBAL: SUMO 0x00be6000
// GLOBAL: EDITOR 0x00be6820
extern SumoU8 g_gameBoxIndexPairStorage;

// GLOBAL: SUMO 0x00be5ef8
// GLOBAL: EDITOR 0x00be6718
extern SumoU8 g_gameBoxTextureTriangleCounts;
extern SumoU8 *g_gameBoxLitVertexCursor;
extern SumoU8 *g_gameBoxShadowPositionCursor;
extern SumoU8 *g_gameBoxIndexPairCursor;
extern Vector3 g_gameBoxLightDirection;
extern SumoS32 g_gameTextures[256];
extern SumoS32 g_gameRenderQualityCode;
extern SumoS32 g_gameRenderQualityEnabled;
extern SumoU8 g_waterFieldActive;
extern SumoU32 g_screenTintColor;
void RenderGameBoxes(SumoS32);

// GLOBAL: SUMO 0x0042c794
// GLOBAL: EDITOR 0x0042c794
extern const SumoF32 g_gameLightPassRotationStep = 5.1999998f;

struct GameSceneIndexPair {
  SumoS16 triangleIndex;
  SumoS16 textureIndex;
};

struct GameLineVertex {
  Vector3 position;
  SumoU32 color;
};

DECOMP_SIZE_ASSERT(GameLineVertex, 0x10);

enum {
  c_gameLinePrimitiveBytes = sizeof(GameLineVertex) * 2,
  c_gameLinePrimitiveShift = 5
};

static __forceinline Vector3 MakeGameRenderVector3(SumoF32 p_x, SumoF32 p_y,
                                                   SumoF32 p_z) {
  Vector3 result;
  result.x = p_x;
  result.y = p_y;
  result.z = p_z;
  return result;
}

// GLOBAL: SUMO 0x009b5de0
// GLOBAL: EDITOR 0x009b6600
SumoS16 g_gameBoxTextureTriangleOffsets[128];

// GLOBAL: SUMO 0x00765dd8
// GLOBAL: EDITOR 0x007665f8
extern SumoS16 g_gameBoxTriangleOrder[];

// FUNCTION: SUMO 0x0040caa2
// FUNCTION: EDITOR 0x0040cac4
HRESULT RenderGameScene() {
  g_gameD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
  g_gameD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
  g_gameD3DDevice->SetRenderState(D3DRS_CLIPPING, TRUE);
  g_gameD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
  g_gameD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
  g_gameD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
  for (SumoS32 stage = 0; stage < 6; ++stage) {
    g_gameD3DDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    g_gameD3DDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    g_gameD3DDevice->SetSamplerState(stage, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
  }

  g_gameViewMatrix = g_gameInverseViewMatrix;
  g_gameViewOffset = g_gameCameraWorldPosition;
  ApplyGameViewTransform();
  SumoU32 clearColor =
      (0x80c1u * (((SumoS32)g_screenTintColor >> 2) & 0x3f)) & 0x003f3f3f;
  g_gameD3DDevice->Clear(0, 0,
                         D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                         clearColor, 1.0f, 0);
  g_gameD3DDevice->BeginScene();

  bool firstLightPass = true;
  SumoS32 passCount = g_gameRenderQualityCode;
  SumoS32 pass = 0;
  if (passCount > 0) {
    do {
      g_gameBoxLightDirection = MakeGameRenderVector3(0.30000001f, 1.0f, 0.5f);
      Vector3 lightRotation = MakeGameRenderVector3(
          0.0f,
          (SumoF32)pass * g_gameLightPassRotationStep / (SumoF32)passCount,
          0.0f);
      SumoU32 textureFactor = 526086u * ((288 / (passCount + 1) + 8) / 16);
      g_gameBoxLightDirection.Rotate(lightRotation);
      g_gameBoxLightDirection.Normalize();

      SumoS16 *triangleCounts = (SumoS16 *)&g_gameBoxTextureTriangleCounts;
      SumoU32 *triangleCountWords = (SumoU32 *)triangleCounts;
      for (SumoS32 word = 0; word < 64; ++word)
        triangleCountWords[word] = 0;
      void *lockedPositions;
      g_gameBoxIndexPairCursor = &g_gameBoxIndexPairStorage;
      g_gameBoxLitVertexCursor = &g_gameBoxLitVertexStorage;
      g_gameBoxShadowPositionCursor = &g_gameBoxShadowPositionStorage;
      RenderGameBoxes(0);

      SumoS32 shadowTriangleCount =
          ((Vector3 *)g_gameBoxShadowPositionCursor -
           (Vector3 *)&g_gameBoxShadowPositionStorage) /
          3;
      g_gamePositionVertexBuffer->Lock(
          0, shadowTriangleCount * 3 * sizeof(Vector3), &lockedPositions,
          D3DLOCK_DISCARD);
      memcpy(lockedPositions, &g_gameBoxShadowPositionStorage,
             shadowTriangleCount * 3 * sizeof(Vector3));
      g_gamePositionVertexBuffer->Unlock();

      SumoS32 triangleCount = 0;
      for (SumoS32 texture = 0; texture < 128; ++texture) {
        g_gameBoxTextureTriangleOffsets[texture] = (SumoS16)triangleCount;
        triangleCount += triangleCounts[texture];
      }

      GameSceneIndexPair *pair =
          (GameSceneIndexPair *)&g_gameBoxIndexPairStorage;
      SumoS32 emittedTriangleCount = 0;
      if ((SumoU8 *)pair < g_gameBoxIndexPairCursor) {
        do {
          g_gameBoxTriangleOrder
              [g_gameBoxTextureTriangleOffsets[pair->textureIndex] +
               pair->triangleIndex] = (SumoS16)emittedTriangleCount;
          ++emittedTriangleCount;
          ++pair;
        } while ((SumoU8 *)pair < g_gameBoxIndexPairCursor);
      }

      GameTextVertex *lockedVertices;
      g_gameMainVertexBuffer->Lock(
          0, emittedTriangleCount * 3 * sizeof(GameTextVertex),
          (void **)&lockedVertices, D3DLOCK_DISCARD);
      GameTextVertex *sourceVertices =
          (GameTextVertex *)&g_gameBoxLitVertexStorage;
      GameTextVertex *secondSourceVertices =
          (GameTextVertex *)&g_gameBoxLitVertexStorageSecond;
      GameTextVertex *thirdSourceVertices =
          (GameTextVertex *)&g_gameBoxLitVertexStorageThird;
      for (SumoS32 triangle = 0; triangle < emittedTriangleCount; ++triangle) {
        *lockedVertices++ =
            sourceVertices[g_gameBoxTriangleOrder[triangle] * 3];
        *lockedVertices++ =
            secondSourceVertices[g_gameBoxTriangleOrder[triangle] * 3];
        *lockedVertices++ =
            thirdSourceVertices[g_gameBoxTriangleOrder[triangle] * 3];
      }
      g_gameMainVertexBuffer->Unlock();
      g_gameD3DDevice->SetFVF(g_gameMainVertexFvf);
      g_gameD3DDevice->SetStreamSource(0, g_gameMainVertexBuffer, 0,
                                       sizeof(GameTextVertex));

      if (g_gameRenderQualityEnabled) {
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILREF, 8);
        g_gameD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILZFAIL,
                                        D3DSTENCILOP_REPLACE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILFAIL,
                                        D3DSTENCILOP_REPLACE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILPASS,
                                        D3DSTENCILOP_REPLACE);
      }
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP,
                                            D3DTOP_SELECTARG2);
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
      g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
      if (firstLightPass)
        g_gameD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0x00203040);
      else {
        g_gameD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0);
        g_gameD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
      }
      if (g_gameRenderQualityEnabled || firstLightPass) {
        g_gameD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangleCount);
      }

      g_gameD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
      g_gameD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
      g_gameD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILREF, 8);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCR);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
      if (g_gameRenderQualityEnabled) {
        g_gameD3DDevice->SetFVF(g_gamePositionVertexFvf);
        g_gameD3DDevice->SetStreamSource(0, g_gamePositionVertexBuffer, 0, 12);
        g_gameD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
        g_gameD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,
                                       shadowTriangleCount);
        g_gameD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_DECR);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
        g_gameD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,
                                       shadowTriangleCount);
      }
      g_gameD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 15);

      if (firstLightPass) {
        g_gameD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        g_gameD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
        g_gameD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
        firstLightPass = false;
      }
      g_gameD3DDevice->SetFVF(g_gameMainVertexFvf);
      g_gameD3DDevice->SetStreamSource(0, g_gameMainVertexBuffer, 0,
                                       sizeof(GameTextVertex));
      if (g_gameRenderQualityEnabled) {
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILREF, 8);
        g_gameD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        g_gameD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
      }
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP,
                                            D3DTOP_DOTPRODUCT3);
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
      g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
      g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
      g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
      g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TFACTOR);
      g_gameD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
      g_gameD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, textureFactor);
      for (SumoS32 texture = 0; texture < 128; ++texture) {
        if (triangleCounts[texture] != 0) {
          SetGameTexture(0,
                         (IDirect3DBaseTexture9 *)g_gameTextures[texture * 2]);
          g_gameD3DDevice->DrawPrimitive(
              D3DPT_TRIANGLELIST, 3 * g_gameBoxTextureTriangleOffsets[texture],
              triangleCounts[texture]);
        }
      }
      g_gameD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
      g_gameD3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
    } while (++pass < passCount);
  }

  g_gameD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  g_gameD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
  g_gameD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
  g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
  g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
  g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
  g_gameD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
  g_gameD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_screenTintColor);
  SumoS16 *finalCounts = (SumoS16 *)&g_gameBoxTextureTriangleCounts;
  for (SumoS32 texture = 0; texture < 128; ++texture) {
    if (finalCounts[texture] != 0) {
      SetGameTexture(0,
                     (IDirect3DBaseTexture9 *)g_gameTextures[texture * 2 + 1]);
      g_gameD3DDevice->DrawPrimitive(
          D3DPT_TRIANGLELIST, 3 * g_gameBoxTextureTriangleOffsets[texture],
          finalCounts[texture]);
    }
  }

  if (g_waterFieldActive)
    RenderWaterSurface();
  g_gameD3DDevice->SetTexture(0, 0);
  g_gameD3DDevice->SetTexture(1, 0);
  FlushGameTextVertices();
  if ((SumoS32)(g_gameLineVertexCursor - &g_gameLineVertexScratch) &
      -c_gameLinePrimitiveBytes) {
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
    g_gameD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_gameD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    g_gameD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    g_gameD3DDevice->SetFVF(g_gameLineVertexFvf);
    g_gameD3DDevice->DrawPrimitiveUP(
        D3DPT_LINELIST,
        (SumoS32)(g_gameLineVertexCursor - &g_gameLineVertexScratch) >>
            c_gameLinePrimitiveShift,
        &g_gameLineVertexScratch, sizeof(GameLineVertex));
  }
  g_gameD3DDevice->EndScene();
  return g_gameD3DDevice->Present(0, 0, 0, 0);
}

// GLOBAL: SUMO 0x00c0d9f0
// GLOBAL: EDITOR 0x00c0e210
extern SumoU32 g_deferredReleaseIndex;

// GLOBAL: SUMO 0x00c0d9f8
// GLOBAL: EDITOR 0x00c0e218
extern IDirect3DResource9 **g_deferredReleaseSlots[1024];

// GLOBAL: SUMO 0x00c0e9f8
// GLOBAL: EDITOR 0x00c0f218
extern SumoS32 g_deferredReleaseWriteIndex;


// FUNCTION: SUMO 0x004151a0
// FUNCTION: EDITOR 0x004151c2
SumoS32 SaveGameScreenshot(char *p_prefix, SumoS32 p_index) {
  g_gameScreenshotIndex = p_index;
  g_gameScreenshotPrefix = p_prefix;
  return WriteGameScreenshot();
}

// FUNCTION: SUMO 0x004151b7
// FUNCTION: EDITOR 0x004151d9
SumoU32 ReleaseNextQueuedRenderResource() {
  if (*g_deferredReleaseSlots[g_deferredReleaseIndex] != NULL) {
    (*g_deferredReleaseSlots[g_deferredReleaseIndex])->Release();
  }

  *g_deferredReleaseSlots[g_deferredReleaseIndex] = NULL;
  return g_deferredReleaseIndex = (g_deferredReleaseIndex + 1) & 0x3ff;
}

// GLOBAL: SUMO 0x004571ec
// GLOBAL: EDITOR 0x0045720c
IDirect3DDevice9 *g_gameD3DDevice;

// GLOBAL: SUMO 0x00d0eb3c
// GLOBAL: EDITOR 0x00d0f35c
HWND g_gameConfigParentWindow;

// GLOBAL: SUMO 0x00d0eb4c
// GLOBAL: EDITOR 0x00d0f36c
HWND g_gameConfigWindow;

// GLOBAL: SUMO 0x00d0eb7c
// GLOBAL: EDITOR 0x00d0f39c
HWND g_gameHomepageWindow;

// GLOBAL: SUMO 0x00d0eb80
// GLOBAL: EDITOR 0x00d0f3a0
HWND g_gamePurchaseWindow;

// GLOBAL: SUMO 0x00d0eb74
// GLOBAL: EDITOR 0x00d0f394
HWND g_gameConfigQuitButton;

// GLOBAL: SUMO 0x00d0eb78
// GLOBAL: EDITOR 0x00d0f398
HWND g_gameConfigPlayButton;

// GLOBAL: SUMO 0x00d0eb84
// GLOBAL: EDITOR 0x00d0f3a4
HWND g_gameConfigModButton;

// GLOBAL: SUMO 0x00d0eb8c
// GLOBAL: EDITOR 0x00d0f3ac
HWND g_gameConfigTitleWindow;

// GLOBAL: SUMO 0x00d0eba8
// GLOBAL: EDITOR 0x00d0f3c8
SumoS32 g_gameConfigDisplayModeCount;

// GLOBAL: SUMO 0x00d0ebac
// GLOBAL: EDITOR 0x00d0f3cc
SumoS32 g_gameConfigResult;

// GLOBAL: SUMO 0x00d0ebb0
// GLOBAL: EDITOR 0x00d0f3d0
SumoS32 g_gameConfigClassRegistered;

// GLOBAL: SUMO 0x00d0ece8
// GLOBAL: EDITOR 0x00d0f508
HINSTANCE g_gameInstance;

// FUNCTION: SUMO 0x004158a5
// FUNCTION: EDITOR 0x004158c7
void __stdcall IgnoreGameTextureProgress(SumoF32) {}


// FUNCTION: SUMO 0x00415a3a
// FUNCTION: EDITOR 0x00415a5c
SumoS32 CreateGameTextureFromPixels(void *p_pixels, SumoS32 p_width, SumoS32 p_height, SumoS32 p_singleLevel) {
  struct TextureUploadState {
    D3DLOCKED_RECT locked;
    SumoS32 remaining;
    SumoS32 rowBytes;
  } upload;

  IDirect3DTexture9 *texture;
  g_gameD3DDevice->CreateTexture(p_width, p_height, p_singleLevel,
                                 (p_singleLevel ^ 1) * D3DUSAGE_AUTOGENMIPMAP,
                                 D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture,
                                 NULL);

  texture->LockRect(0, &upload.locked, NULL, 0);

  SumoU8 *destination = (SumoU8 *)upload.locked.pBits;
  SumoU8 *source = (SumoU8 *)p_pixels;
  if (p_height > 0) {
    upload.rowBytes = p_width << 2;
    upload.remaining = p_height;
    do {
      memcpy(destination, source, upload.rowBytes);
      destination += upload.locked.Pitch;
      source += upload.rowBytes;
    } while (--upload.remaining != 0);
  }

  texture->UnlockRect(0);
  return (SumoS32)texture;
}

// FUNCTION: SUMO 0x00415bf5
// FUNCTION: EDITOR 0x00415c17
HRESULT SetGameTexture(DWORD stage, IDirect3DBaseTexture9 *texture)
{

  return g_gameD3DDevice->SetTexture(stage, texture);
}


struct GameDisplaySettings {
  SumoS32 width;
  SumoS32 height;
  SumoS32 colorDepth;
  SumoS32 displayMode;
  SumoS32 quality;
  SumoS32 enabled;
};

// GLOBAL: SUMO 0x00d0eb50
// GLOBAL: EDITOR 0x00d0f370
GameDisplaySettings g_gameDisplaySettings;

// GLOBAL: SUMO 0x00d0eb90
// GLOBAL: EDITOR 0x00d0f3b0
GameDisplaySettings g_activeDisplaySettings;

// GLOBAL: SUMO 0x00c0ea20
// GLOBAL: EDITOR 0x00c0f240
SumoU8 g_gameAudioEnabled;

// GLOBAL: SUMO 0x00453700
// GLOBAL: EDITOR 0x00453700
SumoS32 g_gameRenderQualityCode = 12;

// GLOBAL: SUMO 0x004536fc
// GLOBAL: EDITOR 0x004536fc
SumoS32 g_gameRenderQualityEnabled = 1;

// GLOBAL: SUMO 0x00457334
// GLOBAL: EDITOR 0x00457354
SumoS32 g_gameConfiguredWidth;

// GLOBAL: SUMO 0x00457338
// GLOBAL: EDITOR 0x00457358
SumoS32 g_gameConfiguredHeight;

// GLOBAL: SUMO 0x004571f4
// GLOBAL: EDITOR 0x00457214
SumoS32 g_gameConfiguredColorDepth;

// GLOBAL: SUMO 0x004571f0
// GLOBAL: EDITOR 0x00457210
SumoS32 g_gameConfiguredDisplayMode;

// GLOBAL: SUMO 0x0045733c
// GLOBAL: EDITOR 0x0045735c
SumoU8 g_gameUseDesktopSize;

struct GameDisplayMode;

// GLOBAL: SUMO 0x00d0eb68
// GLOBAL: EDITOR 0x00d0f388
GameDisplayMode *g_gameConfigDisplayModes;

// GLOBAL: SUMO 0x00d0eb88
// GLOBAL: EDITOR 0x00d0f3a8
HWND g_gameDisplayModeCombo;

// GLOBAL: SUMO 0x00d0eb44
// GLOBAL: EDITOR 0x00d0f364
HWND g_gameQualityCombo;

// GLOBAL: SUMO 0x00d0eb6c
// GLOBAL: EDITOR 0x00d0f38c
HWND g_gameAudioCombo;

// GLOBAL: SUMO 0x0042cbd0
// GLOBAL: EDITOR 0x0042cbd0
static const char g_displayConfigValueName[] = "configf";

// GLOBAL: SUMO 0x0042c5cc
// GLOBAL: EDITOR 0x0042c5cc
extern const char g_editClassName[] = "edit";

// GLOBAL: SUMO 0x0042c5d4
// GLOBAL: EDITOR 0x0042c5d4
extern const char g_gameLevelEditorTitle[] = "Sumotori Editor";

// GLOBAL: SUMO 0x0042c5e4
// GLOBAL: EDITOR 0x0042c5e4
extern const char g_gameLevelEditorClassName[] = "gameeditor";

// GLOBAL: SUMO 0x0042cb6c
// GLOBAL: EDITOR 0x0042cb6c
static const char g_purchaseNoticeText[] =
    "Thanks for purchasing Sumotori Dreams!   ENJOY!";

// GLOBAL: SUMO 0x0042cb9c
// GLOBAL: EDITOR 0x0042cb9c
static const char g_homepageNoticeText[] =
    "Homepage: http://www.gravitysensation.com/sumotori/";


// FUNCTION: SUMO 0x00415c0c
// FUNCTION: EDITOR 0x00415c2e
void InitializeDefaultDisplaySettings()
{

  g_gameDisplaySettings.displayMode = 0;
  g_gameDisplaySettings.width = 640;
  g_gameDisplaySettings.height = 480;
  g_gameDisplaySettings.colorDepth = 32;
  g_gameDisplaySettings.quality = 2;
  g_gameDisplaySettings.enabled = 1;
}

// FUNCTION: SUMO 0x00415c46
// FUNCTION: EDITOR 0x00415c68
SumoS32 ApplyGameDisplaySettings(GameDisplaySettings *settings) {
  SumoS32 qualityCodes[4];

  g_activeDisplaySettings = *settings;
  qualityCodes[0] = 1;
  g_gameAudioEnabled = settings->enabled != 0;
  SumoS32 quality = settings->quality;
  qualityCodes[1] = 2;
  qualityCodes[2] = 4;
  qualityCodes[3] = 12;
  g_gameRenderQualityCode = qualityCodes[quality];
  g_gameRenderQualityEnabled = settings->quality != 0;
  g_gameConfiguredWidth = settings->width;
  g_gameConfiguredHeight = settings->height;
  g_gameConfiguredColorDepth = settings->colorDepth;

  SumoS32 result = settings->displayMode;
  g_gameConfiguredDisplayMode = result;
  g_gameUseDesktopSize = g_gameConfiguredWidth * g_gameConfiguredHeight == 0;
  return result;
}

// FUNCTION: SUMO 0x00415cd6
// FUNCTION: EDITOR 0x00415cf8
SumoS32 ReadDisplaySettingsControls() {
  g_gameUseDesktopSize = FALSE;
  SumoS32 selection =
      (SumoS32)SendMessage(g_gameDisplayModeCombo, LB_GETCURSEL, 0, 0) - 1;
  if (selection == -1) {
    g_gameDisplaySettings.width = 0;
    g_gameDisplaySettings.height = 0;
    g_gameDisplaySettings.colorDepth = 0;
    g_gameDisplaySettings.displayMode = 0;
  } else {
    *(GameDisplayMode *)&g_gameDisplaySettings =
        g_gameConfigDisplayModes[selection];
  }

  g_gameDisplaySettings.quality =
      (SumoS32)SendMessage(g_gameQualityCombo, LB_GETCURSEL, 0, 0);
  g_gameDisplaySettings.enabled =
      (SumoS32)SendMessage(g_gameAudioCombo, LB_GETCURSEL, 0, 0);
  return ApplyGameDisplaySettings(&g_gameDisplaySettings);
}

// FUNCTION: SUMO 0x00415d5f
// FUNCTION: EDITOR 0x00415d81
HWND CreatePurchaseNoticeWindows() {
  g_gameHomepageWindow =
      CreateWindowExA(0, g_editClassName, g_homepageNoticeText,
                      WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 325, 500, 25,
                      g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gamePurchaseWindow =
      CreateWindowExA(0, g_editClassName, g_purchaseNoticeText,
                      WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 300, 500, 25,
                      g_gameConfigParentWindow, 0, g_gameInstance, 0);
  return g_gamePurchaseWindow;
}

// FUNCTION: SUMO 0x00415dcf
// FUNCTION: EDITOR 0x00415df1
void RecreatePurchaseNoticeWindows() {
  if (g_gameConfigWindow != 0) {
    DestroyWindow(g_gameHomepageWindow);
    g_gameHomepageWindow = 0;
    DestroyWindow(g_gamePurchaseWindow);
    g_gamePurchaseWindow = 0;
    DestroyWindow(g_gameConfigWindow);
    g_gameConfigWindow = 0;
    CreatePurchaseNoticeWindows();
  }
}

// FUNCTION: SUMO 0x00415e13
// FUNCTION: EDITOR 0x00415e35
LONG SaveDisplaySettings() {
  HKEY key;
  LONG result =
      RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Archee\\Sumotori", &key);
  if (result == ERROR_SUCCESS) {
    RegSetValueExA(key, g_displayConfigValueName, 0, REG_BINARY,
                   (const BYTE *)&g_gameDisplaySettings,
                   sizeof(g_gameDisplaySettings));
    result = RegCloseKey(key);
  }
  return result;
}


// FUNCTION: SUMO 0x00415e52
// FUNCTION: EDITOR 0x00415e74
SumoS32 LoadDisplaySettings()
{

  InitializeDefaultDisplaySettings();

  HKEY key;
  if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Archee\\Sumotori", 0,
                    KEY_READ, &key) == ERROR_SUCCESS) {
    DWORD size = sizeof(g_gameDisplaySettings);
    RegQueryValueExA(key, g_displayConfigValueName, 0, 0,
                     (BYTE *)&g_gameDisplaySettings, &size);
    RegCloseKey(key);
  }

  return ApplyGameDisplaySettings(&g_gameDisplaySettings);
}

extern "C" void EnumerateGameDisplayModes(const GUID *identifier,
                                          GameDisplayMode **modes,
                                          SumoS32 *count);
SumoS32 ValidateAndSaveGameSettingsCode(char *text, char save);
SumoS32 CheckStoredGameSettings();
SumoS32 ReadDisplaySettingsControls();
void LoadLevelScriptFile(char *fileName);
extern SumoS32 g_selectedLevelScript;

// GLOBAL: SUMO 0x00453bc8
// GLOBAL: EDITOR 0x00453bc8
static char g_gameQualityLabels[4][64] = {"No Shadow", "2  Lights", "4  Lights",
                                          "12 Lights"};

// GLOBAL: SUMO 0x00453cc8
// GLOBAL: EDITOR 0x00453cc8
SumoS32 g_waterGridWidth = 128;

// GLOBAL: SUMO 0x00453ccc
// GLOBAL: EDITOR 0x00453ccc
SumoS32 g_waterGridHeight = 64;


// FUNCTION: SUMO 0x00415eb2
// FUNCTION: EDITOR 0x00415ed4
LRESULT CALLBACK GameConfigWindowProc(HWND window, UINT message, WPARAM wParam,
                                      volatile LPARAM lParam)
{

  OPENFILENAMEA openFile;
  PAINTSTRUCT paint;
  char text[200];

  switch (message) {
  case WM_DESTROY:
    g_gameConfigParentWindow = 0;
    g_gameConfigResult = 2;
    break;

  case WM_CLOSE:
    g_gameConfigResult = 2;
    return 0;

  case WM_PAINT:
    BeginPaint(window, &paint);
    EndPaint(window, &paint);
    return 0;

  case WM_COMMAND:
    SumoU32 notification = (SumoU32)wParam >> 16;
    if (notification != 0) {
      if (notification == EN_UPDATE) {
        GetWindowTextA(g_gameConfigWindow, text, 199);
        if (!ValidateAndSaveGameSettingsCode(text, 1)) {
          if (g_gameConfigWindow != 0) {
            RecreatePurchaseNoticeWindows();
          }
        }
      }
      break;
    }

    if ((HWND)lParam == g_gameConfigModButton) {
      char fileName[MAX_PATH];
      GetCurrentDirectoryA(252, fileName);
      strcat(fileName, "\\*.smo");
      memset(&openFile, 0, sizeof(openFile));
      openFile.lStructSize = sizeof(openFile);
      openFile.hwndOwner = 0;
      openFile.lpstrFilter = "Sumotori Mods (*.smo)";
      openFile.lpstrFile = fileName;
      openFile.nMaxFile = MAX_PATH;
      openFile.Flags = 0x81000;
      openFile.lpstrDefExt = "smo";
      if (GetOpenFileNameA(&openFile)) {
        LoadLevelScriptFile(openFile.lpstrFile);
      }
      if (g_selectedLevelScript == -1) {
        lParam = (LPARAM)g_gameConfigPlayButton;
      }
    }

    if ((HWND)lParam == g_gameConfigPlayButton) {
      if (!CheckStoredGameSettings()) {
        GetWindowTextA(g_gameConfigWindow, text, 199);
        if (text[0] != 0 && text[1] != 0 && text[2] != 0 &&
            ValidateAndSaveGameSettingsCode(text, 1)) {
          MessageBoxA(g_gameConfigParentWindow, "Invalid license key", "Error",
                      MB_OK);
        }
      }
      ReadDisplaySettingsControls();
      SaveDisplaySettings();
      g_gameConfigResult = 1;
    }

    if ((HWND)lParam == g_gameConfigQuitButton) {
      ReadDisplaySettingsControls();
      g_gameConfigResult = 2;
    }
    break;
  }

  return DefWindowProcA(window, message, wParam, lParam);
}


// FUNCTION: SUMO 0x004160dc
// FUNCTION: EDITOR 0x004160fe
HWND CreateGameConfigControls()
{

  g_gameConfigTitleWindow =
      CreateWindowExA(0, g_editClassName, "System Settings",
                      WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 0, 380, 20,
                      g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gameDisplayModeCombo = CreateWindowExA(
      0, "listbox", "drivers", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
      400, 10, 180, 280, g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gameQualityCombo = CreateWindowExA(
      0, "listbox", "drivers", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
      10, 30, 380, 120, g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gameAudioCombo = CreateWindowExA(
      0, "listbox", "sound", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
      10, 190, 180, 60, g_gameConfigParentWindow, 0, g_gameInstance, 0);

  SendMessageA(g_gameAudioCombo, LB_ADDSTRING, 0, (LPARAM) "SOUND OFF");
  SendMessageA(g_gameAudioCombo, LB_ADDSTRING, 0, (LPARAM) "SOUND ON");
  EnumerateGameDisplayModes(0, &g_gameConfigDisplayModes,
                            &g_gameConfigDisplayModeCount);
  SendMessageA(g_gameDisplayModeCombo, LB_ADDSTRING, 0,
               (LPARAM) "WINDOWED MODE ***");

  WPARAM selection = 0;
  GameDisplayMode *mode = g_gameConfigDisplayModes;
  for (SumoS32 index = 0; index < g_gameConfigDisplayModeCount;
       ++mode, ++index) {
    char label[256];
    sprintf(label, "%dx%d %dbpp", mode->width, mode->height, mode->colorDepth,
            mode->refreshRate);
    SendMessageA(g_gameDisplayModeCombo, LB_ADDSTRING, 0, (LPARAM)label);
    if (mode->width == g_gameConfiguredWidth &&
        mode->height == g_gameConfiguredHeight &&
        mode->colorDepth == g_gameConfiguredColorDepth &&
        mode->refreshRate == g_gameConfiguredDisplayMode) {
      selection = index + 1;
    }
  }
  SendMessageA(g_gameDisplayModeCombo, LB_SETCURSEL, selection, selection);

  LONG_PTR qualityLabel = (LONG_PTR)g_gameQualityLabels[0];
  do {
    SendMessageA(g_gameQualityCombo, LB_ADDSTRING, 0, (LPARAM)qualityLabel);
    qualityLabel += sizeof(g_gameQualityLabels[0]);
  } while (qualityLabel < (LONG_PTR)&g_waterGridWidth);
  SendMessageA(g_gameQualityCombo, LB_SETCURSEL, g_gameDisplaySettings.quality,
               g_gameDisplaySettings.quality);
  SendMessageA(g_gameAudioCombo, LB_SETCURSEL, g_gameDisplaySettings.enabled,
               g_gameDisplaySettings.enabled);

  g_gameConfigModButton =
      CreateWindowExA(0, "button", "PLAY MOD", WS_CHILD | WS_VISIBLE, 460, 370,
                      120, 20, g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gameConfigPlayButton =
      CreateWindowExA(0, "button", "PLAY GAME", WS_CHILD | WS_VISIBLE, 300, 410,
                      180, 20, g_gameConfigParentWindow, 0, g_gameInstance, 0);
  g_gameConfigQuitButton =
      CreateWindowExA(0, "button", "QUIT", WS_CHILD | WS_VISIBLE, 500, 410, 80,
                      20, g_gameConfigParentWindow, 0, g_gameInstance, 0);

  if (!CheckStoredGameSettings()) {
    g_gamePurchaseWindow = CreateWindowExA(
        0, g_editClassName,
        "Visit http://www.gravitysensation.com/sumotori/ to get a license.",
        WS_CHILD | WS_VISIBLE | ES_READONLY, 10, 300, 500, 25,
        g_gameConfigParentWindow, 0, g_gameInstance, 0);
    g_gameHomepageWindow = CreateWindowExA(
        0, g_editClassName,
        "Type the license key below:", WS_CHILD | WS_VISIBLE | ES_READONLY, 10,
        325, 500, 25, g_gameConfigParentWindow, 0, g_gameInstance, 0);
    g_gameConfigWindow =
        CreateWindowExA(0, g_editClassName, "", 0x50000008, 10, 360, 400, 25,
                        g_gameConfigParentWindow, 0, g_gameInstance, 0);
    return g_gameConfigWindow;
  }
  return CreatePurchaseNoticeWindows();
}


// FUNCTION: SUMO 0x0041643f
// FUNCTION: EDITOR 0x00416461
SumoS32 RunGameConfiguration(const char *windowName)
{

  if (!g_gameConfigClassRegistered) {
    g_gameConfigClassRegistered = 1;
    WNDCLASSA windowClass;
    windowClass.style = CS_DBLCLKS;
    windowClass.lpfnWndProc = GameConfigWindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = g_gameInstance;
    windowClass.hIcon = 0;
    windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
    windowClass.hbrBackground = CreateSolidBrush(0x00d0c0c0);
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = "archeecfg";
    if (!RegisterClassA(&windowClass)) {
      return 0;
    }
  }

  RECT rectangle;
  rectangle.left = 0;
  rectangle.right = 600;
  rectangle.bottom = 460;
  rectangle.top = 0;
  AdjustWindowRect(&rectangle, 0x00ca0000, FALSE);
  g_gameConfigParentWindow = CreateWindowExA(
      WS_EX_APPWINDOW, "archeecfg", windowName, 0x00ca0000, CW_USEDEFAULT,
      CW_USEDEFAULT, rectangle.right - rectangle.left,
      rectangle.bottom - rectangle.top, 0, 0, g_gameInstance, 0);
  ShowWindow(g_gameConfigParentWindow, SW_SHOWNORMAL);
  SetCursor(0);
  CreateGameConfigControls();

  g_gameConfigResult = 0;
  MSG message;
  for (;;) {
    GetMessageA(&message, 0, 0, 0);
    if (g_gameConfigResult != 0) {
      break;
    }
    TranslateMessage(&message);
    DispatchMessageA(&message);
  }
  SumoS32 result = g_gameConfigResult;
  DestroyWindow(g_gameConfigParentWindow);
  return result;
}
