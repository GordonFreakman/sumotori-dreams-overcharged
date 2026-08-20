#include "boundary.h"

#include <stdio.h>
#include <stdlib.h>

#if defined(__SSE2__) || defined(_M_X64) ||                                    \
    (defined(_M_IX86) && defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#define SUMO_FPU_MXCSR 1
#include <xmmintrin.h>
#elif defined(_MSC_VER)
#define SUMO_FPU_CONTROLFP 1
#include <float.h>
#else
#define SUMO_FPU_FENV 1
#include <fenv.h>
#endif

SumoU32 g_gameTimeScaleNumerator = 120;

SumoU32 g_gameTimeScaleDenominator = 1;

SumoU8 g_gameCursorVisible = 1;

SumoU8 g_gameDebugInitialized;

FILE *g_gameDebugStream;

SumoU8 g_gameKeyDown[256];

SumoU8 g_gameKeyPressed[256];

SumoS32 g_gameMouseX = -1;

SumoS32 g_gameMouseY;

SumoS32 g_cameraMouseX, g_cameraMouseY;

SumoS32 g_gamePrimaryInputPressed;

#if defined(_WIN32)
extern "C" int __stdcall AttachConsole(unsigned long processId);
#endif

void SumoAttachParentConsole() {
#if defined(_WIN32)
  if (AttachConsole((unsigned long)-1) == 0)
    return;
#if defined(_MSC_VER)
  FILE *stream = NULL;
  freopen_s(&stream, "CONOUT$", "w", stdout);
  freopen_s(&stream, "CONOUT$", "w", stderr);
#else
  (void)!freopen("CONOUT$", "w", stdout);
  (void)!freopen("CONOUT$", "w", stderr);
#endif
#endif
}

void SetGameFpuControlWord() {
#if defined(SUMO_FPU_MXCSR)
  unsigned int csr = _mm_getcsr();
  csr &= ~0x8040u;
  csr = (csr & ~0x6000u) | 0x2000u;
  _mm_setcsr(csr);
#elif defined(SUMO_FPU_CONTROLFP)
  unsigned int previous = 0;
  _controlfp_s(&previous, _RC_DOWN, _MCW_RC);
#else
  fesetround(FE_DOWNWARD);
#endif
}

SumoS32 MessageBox(void *owner, const char *text, const char *caption,
                   SumoU32 type) {
  (void)owner;
  (void)type;
  fprintf(stderr, "sumotori: %s: %s\n", caption, text);
  return 1;
}

SumoU32 timeGetTime() { return (SumoU32)SDL_GetTicks(); }

SumoU32 GetScaledGameTime() {
  return timeGetTime() * g_gameTimeScaleNumerator / 1000 /
         g_gameTimeScaleDenominator;
}

SumoU32 GameAudioShutdown();

void ExitGameProcess() {
  SumoPlatformDestroyWindow();
  GameAudioShutdown();
  exit(0);
}

static char s_emptyCommandLineFile[1];
char *g_gameCommandLineFile = s_emptyCommandLineFile;

SumoS32 LogGameDebugValue(const char *text, SumoS32 value) {
  if (!g_gameDebugInitialized) {
    g_gameDebugInitialized = 1;
    g_gameDebugStream = fopen("debug.!", "w");
    fclose(g_gameDebugStream);
  }

  g_gameDebugStream = fopen("debug.!", "a");
  fprintf(g_gameDebugStream, "%s %d\n", text, value);
  return fclose(g_gameDebugStream);
}

void SumoResolveWindowSize(SumoS32 requestedWidth, SumoS32 requestedHeight,
                           SumoS32 desktopWidth, SumoS32 desktopHeight,
                           SumoS32 *outWidth, SumoS32 *outHeight) {
  SumoS32 width = requestedWidth;
  SumoS32 height = requestedHeight;
  if (width <= 0 || height <= 0) {
    width = desktopWidth;
    height = desktopHeight;
  }
  if (width <= 0 || height <= 0) {
    width = 1024;
    height = 768;
  }
  *outWidth = width;
  *outHeight = height;
}

void SetGameCursorVisible(SumoU8 visible) {
  if (g_gameCursorVisible != visible) {
    g_gameCursorVisible = visible;
#if SUMO_SDL_VERSION == 3
    if (visible) {
      SDL_ShowCursor();
    } else {
      SDL_HideCursor();
    }
#else
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
#endif
  }
}
