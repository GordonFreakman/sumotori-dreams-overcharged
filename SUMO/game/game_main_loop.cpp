#include "game_input.h"
#include "game_replay.h"
#include "game_runtime.h"

#include <stdio.h>
#include <windows.h>

void SetGameFpuControlWord();
void UpdateGameCamera();
void UpdateFreeGameCamera(SumoS32 controlMode);
void ResetRenderVertexScratch();
void AdvanceGameSimulation();
SumoS32 UpdateHiddenGameScreen();
void GameAudioNoOpCallback();
void RestartGameMusic(SumoS32 playbackMode);
SumoS32 InitializeGameRuntimeState();
void StartGameRound();
char *DrawGameText(SumoF32 x, SumoF32 y, char *text, SumoS32 color);
HRESULT RenderGameScene();
SumoS32 SaveGameScreenshot(char *prefix, SumoS32 index);

extern SumoS32 g_screenTintLevel;
extern SumoS32 g_gamePrimaryInputPressed;
extern SumoS32 g_levelLoadState[8];
extern SumoS32 g_gameScores[2];
extern SumoS32 g_gameHumanPlayerCount;
extern SumoS32 g_gameAlternateCameraMode;
extern SumoS32 g_gameRenderQualityCode;
extern SumoS32 g_gameRenderQualityEnabled;
extern SumoS32 g_gameReplayFrame;
extern SumoS32 g_gameRuntimeMode;
extern SumoU8 g_gameLineVertexScratch;
extern SumoU8 *g_gameLineVertexCursor;
extern const SumoF32 g_freeCameraAimScale;
extern const SumoF32 g_gameProjectileSpin;
extern const SumoF32 g_gameProjectionMinimum;
extern const SumoF32 g_gameCameraInputOffsetScale;

// GLOBAL: SUMO 0x00d0f210
// GLOBAL: EDITOR 0x00d0fa2c
SumoS32 g_gameSimulationPaused;

// GLOBAL: SUMO 0x00453780
// GLOBAL: EDITOR 0x00453780
char g_gameDemoTimeoutText[] = "              demo time out\n"
                               "      please purchase a licence at\n"
                               "http://www.gravitysensation.com/sumotori/\n"
                               " \n"
                               " \n"
                               " \n"
                               "Copy the licence-key from the e-mail into the\n"
                               "box in the settings dialog at startup.\n"
                               "press ESC to quit\n";

static __forceinline void DrawNormalGameOverlay() {
  char computerNames[4][25] = {"Blue guy", "Grey guy", "Brown guy",
                               "Green guy"};
  SumoS32 colors[4] = {(SumoS32)0xe08080ff, (SumoS32)0xc0ffffff,
                       (SumoS32)0xe0c08000, (SumoS32)0xc020e020};
  char playerNames[2][25] = {"Blue guy (player)", "Grey guy (player2)"};

  SumoF32 y = 0.5f;
  if (g_levelLoadState[4] != 11) {
    for (SumoS32 slot = 0; slot < g_nextGameMan - g_gameMen; ++slot) {
      SumoS32 *player = &g_levelLoadState[slot];
      if (*player != -1) {
        char number[2];
        number[1] = 0;
        number[0] = (char)('1' + slot);
        DrawGameText(-0.2f, y, number, colors[*player]);
        char *name = g_gameMen[*player].mode == 1 ? playerNames[*player]
                                                  : computerNames[*player];
        DrawGameText(-0.15000001f, y, name, colors[*player]);
        y -= 0.050000001f;
      }
    }
  }

  if (g_levelLoadState[4] == 2) {
    SumoS32 gameOver = 0;
    if ((g_gameScores[0] >= 5 || g_gameScores[1] >= 5) &&
        (g_gameScores[0] >= g_gameScores[1] + 2 ||
         g_gameScores[0] <= g_gameScores[1] - 2)) {
      gameOver = 1;
      SumoS32 winner = 0;
      if (g_gameScores[1] > g_gameScores[0])
        winner = gameOver;
      char arrows[2][16] = {" Game \n  ->  ", " Game \n  <-  "};
      DrawGameText(g_freeCameraAimScale, 0.41999999f, arrows[winner],
                   colors[winner]);
      DrawGameText(g_freeCameraAimScale, g_gameProjectileSpin,
                   "           \n Game Over \n           ",
                   (SumoS32)0xc0ffff00);
    }

    DrawGameText(-0.80000001f, g_gameProjectionMinimum, "Space to restart game",
                 (SumoS32)0xc0c0c0c0);
    if (g_gameKeyPressed[c_gameRoundRestartInput]) {
      if (gameOver)
        InitializeGameRuntimeState();
      else
        StartGameRound();
    }
  }

  if (g_levelLoadState[4] == 0) {
    DrawGameText(0.2f, g_gameCameraInputOffsetScale,
                 "Controls:\n"
                 " DOWN      - start match\n"
                 " UP        - walk forward\n"
                 " BACKSPACE - Push\n"
                 " ENTER     - Push 1 hand",
                 (SumoS32)0xb0ffffff);
    if (g_gameAlternateCameraMode || g_gameHumanPlayerCount >= 2) {
      DrawGameText(-0.80000001f, g_gameCameraInputOffsetScale,
                   "Controls:\n"
                   " S         - start match\n"
                   " W         - walk forward\n"
                   " SHIFT     - Push\n"
                   " CTRL      - Push 1 hand",
                   (SumoS32)0xb0ffffff);
    }
  }
}
