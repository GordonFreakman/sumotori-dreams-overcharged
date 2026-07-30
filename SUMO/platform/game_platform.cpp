#include "game_input.h"

#include <process.h>
#include <stdio.h>

#include <windows.h>
#include <mmsystem.h>


MMRESULT GameAudioShutdown();
extern SumoU8 g_gameUseDesktopSize;
extern SumoS32 g_gameRenderWidth;
extern SumoS32 g_gameRenderHeight;
extern SumoS32 g_gameConfiguredWidth;
extern SumoS32 g_gameConfiguredHeight;

// GLOBAL: SUMO 0x00453cd8
// GLOBAL: EDITOR 0x00453cdc
SumoU32 g_gameTimeScaleNumerator = 120;

// GLOBAL: SUMO 0x00453cdc
// GLOBAL: EDITOR 0x00453ce0
SumoU32 g_gameTimeScaleDenominator = 1;

// GLOBAL: SUMO 0x00453ce4
// GLOBAL: EDITOR 0x00453ce8
SumoU8 g_gameCursorVisible = 1;

// GLOBAL: SUMO 0x00d0ecf0
// GLOBAL: EDITOR 0x00d0f510
HWND g_gameWindow;

// GLOBAL: SUMO 0x00d0f200
// GLOBAL: EDITOR 0x00d0fa1c
SumoU8 g_gameDebugInitialized;

// GLOBAL: SUMO 0x00d0ebdc
// GLOBAL: EDITOR 0x00d0f3fc
FILE *g_gameDebugStream;

// GLOBAL: SUMO 0x00d0ebe0
// GLOBAL: EDITOR 0x00d0f400
SumoU8 g_gameKeyDown[256];

// GLOBAL: SUMO 0x00d0ecf8
// GLOBAL: EDITOR 0x00d0f518
SumoU8 g_gameKeyPressed[256];

// GLOBAL: SUMO 0x00453ce0
// GLOBAL: EDITOR 0x00453ce4
SumoS32 g_gameMouseX = -1;

// GLOBAL: SUMO 0x00d0f204
// GLOBAL: EDITOR 0x00d0fa20
SumoS32 g_gameMouseY;

// GLOBAL: SUMO 0x00d0f208
// GLOBAL: EDITOR 0x00d0fa24
SumoS32 g_gamePrimaryInputPressed;

// FUNCTION: SUMO 0x00403bb8
// FUNCTION: EDITOR 0x00403bb8
HWND CreateGameWindow(HINSTANCE instance) {
  if (g_gameUseDesktopSize) {
    return CreateWindowExA(0,
                           // STRING: SUMO 0x0042b320
                           // STRING: EDITOR 0x0042b320
                           "archee",
                           // STRING: SUMO 0x0042b328
                           // STRING: EDITOR 0x0042b328
                           "Sumotori", WS_OVERLAPPEDWINDOW, 0, 0,
                           g_gameRenderWidth, g_gameRenderHeight,
                           GetDesktopWindow(), 0, instance, 0);
  }

  HWND window =
      CreateWindowExA(0, "archee", "Sumotori", (DWORD)0x87000000, 0, 0, 2000,
                      2000, GetDesktopWindow(), 0, instance, 0);
  g_gameRenderWidth = g_gameConfiguredWidth;
  g_gameRenderHeight = g_gameConfiguredHeight;
  return window;
}

// FUNCTION: SUMO 0x004168a5
// FUNCTION: EDITOR 0x004168c7
void PumpGameMessages() {
  MSG message;
  while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessageA(&message);
  }
}

// FUNCTION: SUMO 0x004168de
// FUNCTION: EDITOR 0x00416900
void SetGameFpuControlWord() {
  SumoU16 controlWord = 0x077f;
  __asm fldcw controlWord
}

// FUNCTION: SUMO 0x004168eb
// FUNCTION: EDITOR 0x0041690d
SumoU32 GetScaledGameTime() {
  return timeGetTime() * g_gameTimeScaleNumerator / 1000 /
         g_gameTimeScaleDenominator;
}

// FUNCTION: SUMO 0x0041690a
// FUNCTION: EDITOR 0x0041692c
void ExitGameProcess() {
  DestroyWindow(g_gameWindow);
  GameAudioShutdown();
  _exit(0);
}

// FUNCTION: SUMO 0x00416923
// FUNCTION: EDITOR 0x00416945
SumoS32 LogGameDebugValue(const char *text, SumoS32 value) {
  if (!g_gameDebugInitialized) {
    g_gameDebugInitialized = 1;
    // STRING: SUMO 0x0042cd40
    // STRING: EDITOR 0x0042cd40
    g_gameDebugStream = fopen("debug.!", "w");
    fclose(g_gameDebugStream);
  }

  g_gameDebugStream = fopen("debug.!",
                            // STRING: SUMO 0x0042b280
                            // STRING: EDITOR 0x0042b280
                            "a");
  // STRING: SUMO 0x0042cd38
  // STRING: EDITOR 0x0042cd38
  fprintf(g_gameDebugStream, "%s %d\n", text, value);
  return fclose(g_gameDebugStream);
}

// FUNCTION: SUMO 0x00416985
// FUNCTION: EDITOR 0x004169a7
void SetGameCursorVisible(SumoU8 visible) {
  if (g_gameCursorVisible != visible) {
    g_gameCursorVisible = visible;
    ShowCursor(visible);
  }
}
