#ifndef SUMOTORI_GAME_INPUT_H
#define SUMOTORI_GAME_INPUT_H

#include "types.h"

enum GameInputCode {
  c_gameReplayRestartInput = 4,
  c_gameReplayToggleRecordingInput = 5,
  c_gameReplayStartFreshInput = 6,
  c_gameScreenshotInput = 7,
  c_gamePauseInput = 8,
  c_gameFastForwardInput = 9,
  c_gameTripleStepInput = 10,
  c_gameRoundRestartInput = 57,
  c_gameFreeCameraRecordInput = 57,
  c_gameReplayReloadInput = 60,
  c_gameReplayHalfRateInput = 61,
  c_gameReplayDoubleStepInput = 62,
  c_gameCameraTurnLeftInput = 71,
  c_gameCameraTurnRightInput = 73,
  c_gameCameraZoomOutInput = 74,
  c_gameCameraZoomInInput = 78
};

extern SumoU8 g_gameKeyDown[256];
extern SumoU8 g_gameKeyPressed[256];

#endif
