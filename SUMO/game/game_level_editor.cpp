#include "containers.h"
#include "expression_parser.h"
#include "game_replay.h"

#include <stdio.h>
#include <windows.h>

void SetGameCursorVisible(SumoU8 visible);
void RestartGameMusic(SumoS32 playbackMode);
void ResetAndSetSceneTransform(Vector3 &position, SumoF32 angle);
Vector3 *ResetGameRoundState();
typedef void(__cdecl *ResetSceneTransformLegacyCall)(Vector3 &, SumoF32,
                                                     SumoS32);

static __forceinline void ResetAndSetSceneTransformLegacy(Vector3 &position,
                                                          SumoF32 angle) {
  ((ResetSceneTransformLegacyCall)ResetAndSetSceneTransform)(position, angle,
                                                             0);
}
extern const char g_gameScreenshotReadMode[];
extern const char g_editClassName[];
extern char g_gameConsoleFont[];
extern const char g_gameLevelEditorTitle[];
extern const char g_gameLevelEditorClassName[];

// GLOBAL: SUMO 0x0042c5a8
// GLOBAL: EDITOR 0x0042c5a8
extern const char g_gameLevelEditedFilename[];

// GLOBAL: SUMO 0x00c06008
// GLOBAL: EDITOR 0x00c06828
SumoF32 g_gameArenaExtent;

// GLOBAL: SUMO 0x005115fc
// GLOBAL: EDITOR 0x00511e1c
SumoS32 g_gameEditorControlMode;

// GLOBAL: SUMO 0x00467348
// GLOBAL: EDITOR 0x00467b68
HWND g_gameLevelEditorEditControl;

// GLOBAL: SUMO 0x004e73d4
// GLOBAL: EDITOR 0x004e7bf4
HWND g_gameLevelEditorStatusWindow;

// GLOBAL: SUMO 0x004673b0
// GLOBAL: EDITOR 0x00467bd0
extern char g_gameLevelEditBuffer;

// GLOBAL: SUMO 0x00d0f1fc
// GLOBAL: EDITOR 0x00d0fa18
SumoS32 g_gameLevelEditorCloseRequested;

void LoadGameLevel(char *source);

static __forceinline Vector3 MakeGameLevelEditorVector3(SumoF32 x, SumoF32 y,
                                                        SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

// FUNCTION: SUMO 0x00406c37
// FUNCTION: EDITOR 0x00406c59
void StartGameLevelEditor(char *source) {
  ReplayWriteBoundary();
  g_gameArenaExtent = 150.0f;
  InitializeGameParser();
  SetGameCursorVisible(1);
  RestartGameMusic(6);

  Vector3 position = MakeGameLevelEditorVector3(60.0f, 35.0f, -97.0f);
  ResetAndSetSceneTransformLegacy(position, 0.0f);
  ResetGameRoundState();
  g_gameEditorControlMode = 4;
  LoadGameLevel(source);
}

// FUNCTION: SUMO 0x00406cb0
// FUNCTION: EDITOR 0x00406cd2
LRESULT CALLBACK GameLevelEditorWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_SIZE:
    MoveWindow(g_gameLevelEditorEditControl, 0, 0, LOWORD(lParam) - 30,
               HIWORD(lParam), TRUE);
    break;
  case WM_CLOSE:
    g_gameLevelEditorCloseRequested = 1;
    return 0;
  case WM_COMMAND:
    if (HIWORD(wParam) == EN_CHANGE) {
      LoadGameLevel(0);
    }
    break;
  }
  return DefWindowProcA(window, message, wParam, lParam);
}

// FUNCTION: SUMO 0x00406d23
// FUNCTION: EDITOR 0x00406d45
BOOL CreateGameLevelEditorWindow(HINSTANCE instance) {
  FILE *stream = fopen(g_gameLevelEditedFilename, g_gameScreenshotReadMode);
  if (stream != 0) {
    char *buffer = &g_gameLevelEditBuffer;
    SumoU32 size = fread(buffer, 1, 0x7ffff, stream);
    buffer[size] = 0;
    fclose(stream);
  }

  WNDCLASSEXA windowClass;
  windowClass.cbSize = sizeof(windowClass);
  windowClass.style = CS_CLASSDC;
  windowClass.lpfnWndProc = GameLevelEditorWindowProc;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = GetModuleHandleA(0);
  windowClass.hIcon = 0;
  windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
  windowClass.hbrBackground = CreateSolidBrush(0x00504030);
  windowClass.lpszMenuName = 0;
  windowClass.lpszClassName = g_gameLevelEditorClassName;
  windowClass.hIconSm = 0;
  RegisterClassExA(&windowClass);

  g_gameLevelEditorStatusWindow = CreateWindowExA(
      0, g_gameLevelEditorClassName, g_gameLevelEditorTitle, 0x00cf0000, 200,
      700, 800, 300, GetDesktopWindow(), 0, instance, 0);
  g_gameLevelEditorEditControl = CreateWindowExA(
      0, g_editClassName, &g_gameLevelEditBuffer, 0x50300004, 20, 20, 400, 150,
      g_gameLevelEditorStatusWindow, 0, instance, 0);
  HFONT font =
      CreateFontA(13, 0, 0, 0, 700, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                  VARIABLE_PITCH, g_gameConsoleFont);
  SendMessageA(g_gameLevelEditorEditControl, WM_SETFONT, (WPARAM)font, 1);
  return ShowWindow(g_gameLevelEditorStatusWindow, SW_SHOWNORMAL);
}
