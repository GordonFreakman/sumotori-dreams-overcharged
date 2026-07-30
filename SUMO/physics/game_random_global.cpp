#include "game_runtime.h"

#include <new>

static void __cdecl InitializeGlobalGameRandom() {
  new (&g_gameRandom) GameRandomGenerator;
}

#pragma section(".CRT$XCU", read, write)
__declspec(allocate(".CRT$XCU")) static void(
    __cdecl *g_initializeGlobalGameRandom)() = InitializeGlobalGameRandom;
