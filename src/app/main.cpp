#include "boundary.h"

#include "decomp_keywords.h"

#include "containers.h"
#include "input.h"
#include "runtime.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LoadLevelScriptFile(char *fileName);
SumoS32 StartGameRuntime();
void RunGameFrame(SumoU8 renderFrame);
void StopReplayRecording();
SumoU8 InitializeGameAudio();
void InitializeGameMusic();

extern SumoU8 g_gameAudioEnabled;
extern SumoS32 g_gameLevelEditorCloseRequested;
extern SumoS32 g_gameSimulationPaused;

SumoS32 g_gameFrameClock;

SumoU32 GameAudioShutdown();

int main(int argc, char **argv) {
  SumoAttachParentConsole();
  SumoStartupConfig config;

  SumoLoadStartupConfig(&config);
  bool skipLauncher = false;
  bool editorRequested = false;
  char *modFile = NULL;

  SumoAudioBackend audioBackend = (SumoAudioBackend)config.audioBackend;
  //SumoParseAudioBackend(SDL_getenv("SUMOTORI_AUDIO_BACKEND"), &audioBackend);

  for (int index = 1; index < argc; ++index) {
    if (strcmp(argv[index], "--fullscreen") == 0) {
      config.fullscreen = true;
    } else if (strcmp(argv[index], "--windowed") == 0) {
      config.fullscreen = false;
    } else if (strcmp(argv[index], "--width") == 0 && index + 1 < argc) {
      config.width = atoi(argv[++index]);
    } else if (strcmp(argv[index], "--height") == 0 && index + 1 < argc) {
      config.height = atoi(argv[++index]);
    } else if (strcmp(argv[index], "--skip-launcher") == 0) {
      skipLauncher = true;
    } else if (strcmp(argv[index], "--editor") == 0) {
      editorRequested = true;
    } else if (strcmp(argv[index], "--mod") == 0 && index + 1 < argc) {
      modFile = argv[++index];
    }
  }

  if (modFile != NULL && *modFile != 0) {
    LoadLevelScriptFile(modFile);
  }

  config.audioBackend = audioBackend;
  SumoAudioSetBackend(audioBackend);
  g_gameAudioEnabled = config.soundEnabled ? 1 : 0;
  ApplyGameQuality(config.quality);
  SumoU8 oldgameAudioEnabled = g_gameAudioEnabled;
  if (g_gameAudioEnabled) 
  {
    InitializeGameAudio();
    InitializeGameMusic();
  }

  SetGameFpuControlWord();

  if (!SumoPlatformCreateWindow(config.width, config.height,
                                config.fullscreen)) {
    fprintf(stderr, "sumotori: SDL initialization failed: %s\n",
            SDL_GetError());
    return 1;
  }
  if (!SumoRenderCreateContext()) {
    return 1;
  }
  SumoRenderUpdateTargetSize();

  if (!skipLauncher) {
    if (!SumoRunStartupUI(&config)) {
      SumoPlatformDestroyWindow();
      SDL_Quit();
      return 0;
    }
    SumoRenderUpdateTargetSize();
    if (config.modPath[0] != '\0')
      LoadLevelScriptFile(config.modPath);
    if (config.editorRequested)
      editorRequested = true;
  }

  if (oldgameAudioEnabled != g_gameAudioEnabled)
  {
    if (!g_gameAudioEnabled) 
    {
      GameAudioShutdown();
    } 
    else 
    {
      InitializeGameAudio();
      InitializeGameMusic();
    }
  }
  if (editorRequested) {
    g_gameIsRunning = 1;
    SumoEditorEnter();
  }

  SumoInstallExtraLevels();

  PumpGameMessages();
  //InitializeGameAudio();
  //InitializeGameMusic();
  StartGameRuntime();
  
  while (!g_gameLevelEditorCloseRequested && !SumoPlatformQuitRequested()) {
    SumoS32 scaledTime = (SumoS32)GetScaledGameTime();
    if (scaledTime <= g_gameFrameClock) {
      SDL_Delay(0);
    } else {
      ++g_gameFrameClock;
      if (g_gameKeyDown[c_gameTripleStepInput]) {
        RunGameFrame(0);
        RunGameFrame(0);
        RunGameFrame(0);
      }

      SumoS32 frameDifference = scaledTime - g_gameFrameClock;
      if (frameDifference > 20)
        g_gameFrameClock = scaledTime;
      RunGameFrame((SumoU8)(g_gameFrameClock == scaledTime));

      if (g_gameKeyDown[c_gameFastForwardInput])
        g_gameFrameClock += 3;
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
