#include <windows.h>

#include "decomp.h"
#include "game_input.h"
#include "game_replay.h"
#include "types.h"

DECOMP_STATIC_ASSERT(sizeof(void *) == 4);

extern HINSTANCE g_gameInstance;
extern HWND g_gameWindow;
extern SumoU8 g_gameUseDesktopSize;
extern SumoS32 g_gameRenderQualityCode;
extern SumoS32 g_gameRenderQualityEnabled;
extern SumoS32 g_gameIsRunning;
extern SumoS32 g_gameLevelEditorCloseRequested;
extern SumoS32 g_gameSimulationPaused;

void LoadLevelScriptFile(char *fileName);
SumoS32 LoadDisplaySettings();
SumoS32 RunGameConfiguration(const char *windowName);
LRESULT CALLBACK GameWindowProc(HWND window, UINT message, WPARAM wParam,
                                LPARAM lParam);
HWND CreateGameWindow(HINSTANCE instance);
void PumpGameMessages();
SumoS32 InitializeGameD3DDevice();
SumoU8 InitializeGameAudio();
BOOL CreateGameLevelEditorWindow(HINSTANCE instance);
void InitializeGameMusic();
SumoS32 StartGameRuntime();
SumoU32 GetScaledGameTime();
void RunGameFrame(SumoU8 renderFrame);
__declspec(noreturn) void ExitGameProcess();

// GLOBAL: SUMO 0x00d0ebd8
// GLOBAL: EDITOR 0x00d0f3f8
char *g_gameCommandLineFile;

// GLOBAL: SUMO 0x00d0ecec
// GLOBAL: EDITOR 0x00d0f50c
SumoS32 g_gameFrameClock;


// FUNCTION: SUMO 0x00416a1c
// FUNCTION: EDITOR 0x00416a3e
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance,
                   LPSTR commandLine, int showCommand)
{

  (void)previousInstance;
  (void)showCommand;

  g_gameInstance = instance;
  if (g_gameCommandLineFile != 0 && *g_gameCommandLineFile != 0) {
    LoadLevelScriptFile(g_gameCommandLineFile);
  }

  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

  if (!g_gameIsRunning) {
    LoadDisplaySettings();
    if (RunGameConfiguration("Sumotori Dreams Full Version") == 2) {
      return 0;
    }
  }
  if (g_gameIsRunning)
    g_gameUseDesktopSize = 1;

  if (*commandLine == '_') {
    g_gameRenderQualityCode = 2;
    g_gameRenderQualityEnabled = 0;
  }

  WNDCLASSEX windowClass;
  windowClass.cbSize = sizeof(windowClass);
  windowClass.style = 64;
  windowClass.lpfnWndProc = GameWindowProc;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = GetModuleHandle(0);
  windowClass.hIcon = 0;
  windowClass.hCursor = LoadCursor(0, IDC_ARROW);
  windowClass.hbrBackground = 0;
  windowClass.lpszMenuName = 0;
  windowClass.lpszClassName = "archee";
  windowClass.hIconSm = 0;
  RegisterClassEx(&windowClass);

  HWND gameWindow = CreateGameWindow(instance);
  g_gameWindow = gameWindow;
  ShowWindow(gameWindow, SW_SHOWNORMAL);
  UpdateWindow(gameWindow);
  PumpGameMessages();
  InitializeGameD3DDevice();
  InitializeGameAudio();
  if (g_gameIsRunning)
    CreateGameLevelEditorWindow(instance);
  InitializeGameMusic();
  StartGameRuntime();

  SumoS32 frameClock = g_gameFrameClock;
  while (!g_gameLevelEditorCloseRequested) {
    SumoS32 scaledTime = (SumoS32)GetScaledGameTime();
    if (scaledTime <= frameClock) {
      Sleep(0);
    } else {
      ++frameClock;
      if (g_gameKeyDown[c_gameTripleStepInput]) {
        RunGameFrame(0);
        RunGameFrame(0);
        RunGameFrame(0);
      }

      SumoS32 frameDifference = scaledTime - frameClock;
      if (frameDifference > 20)
        frameClock = scaledTime;
      RunGameFrame((SumoU8)(frameClock == scaledTime));

      if (g_gameKeyDown[c_gameFastForwardInput])
        frameClock += 3;
      if (g_gameKeyPressed[c_gamePauseInput]) {
        g_gameSimulationPaused ^= 1;
        g_gameKeyPressed[c_gamePauseInput] = 0;
      }
    }
    PumpGameMessages();
  }

  StopReplayRecording();
  ExitGameProcess();
  return 0;
}
