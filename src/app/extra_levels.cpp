#include "boundary.h"

#include "types.h"

extern char g_gameMenuLabels[5][7][24];

extern char *g_builtinLevelScripts[];

extern SumoS32 g_gameArenaPageRowCount;
extern SumoS32 g_gameArenaPageChainLinks;
extern void (*g_gameModFilePickerRequest)();


extern "C" int SumoTraceFracture(int id, float x, float y, float z, float b) {
  SDL_Log("[TRACE] fracture id=%d pos=(%.2f,%.2f,%.2f) breakability=%.2f", id,
          x, y, z, b);
  return 0;
}

void SumoInstallExtraLevels() {
  g_gameMenuLabels[4][5][0] = '\0';

  g_gameModFilePickerRequest = SumoRequestModFilePicker;

  g_gameArenaPageRowCount = 5;
  g_gameArenaPageChainLinks = 2;
}
