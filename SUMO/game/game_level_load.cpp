#include "expression_parser.h"
#include "game_runtime.h"

#include <stdio.h>
#include <string.h>

#include <windows.h>


extern HWND g_gameLevelEditorEditControl;
extern HWND g_gameLevelEditorStatusWindow;
extern const char g_gameScreenshotWriteMode[];
extern SumoS32 g_levelLoadState[8];

extern const char g_gameLevelEditedFilename[] = "edited.txt";

extern char g_gameLevelEditBuffer;

// GLOBAL: SUMO 0x0042c5b8
// GLOBAL: EDITOR 0x0042c5b8
extern const SumoF32 g_gameLevelArenaExtent = 100.0f;

// FUNCTION: SUMO 0x00406985
// FUNCTION: EDITOR 0x004069a7
void LoadGameLevel(char *source) {
  g_pendingManCount = 0;
  g_levelLoadState[4] = 0;
  g_levelLoadState[6] = 0;
  g_screenTintLevel = 0;
  g_levelLoadState[7] = 0;
  g_levelLoadState[0] = -1;
  g_levelLoadState[1] = -1;
  g_levelLoadState[2] = -1;
  g_levelLoadState[3] = -1;

  ResetGameBoxes();
  memset(g_gameContactObjects, 0, sizeof(g_gameContactObjects));
  g_gameContactObjectsEnd = g_gameContactObjects;

  Vector3 position;
  position.x = 0.0f;
  position.z = 0.0f;
  position.y = -20.0f;

  Vector3 halfSize;
  halfSize.x = g_gameLevelArenaExtent;
  halfSize.y = -10.0f;
  halfSize.z = g_gameLevelArenaExtent;
  g_nextGameMan = g_gameMen;
  g_currentBox = CreateGameBox(halfSize, position, 1, g_gameBoxDefaultValue);
  g_currentBox->MakeImmovable();
  g_currentBox = NULL;

  if (g_gameIsRunning) {
    char *editBuffer = &g_gameLevelEditBuffer;
    GetWindowText(g_gameLevelEditorEditControl, editBuffer, 0x80000);
    FILE *stream = fopen(g_gameLevelEditedFilename, g_gameScreenshotWriteMode);
    fwrite(editBuffer, 1, strlen(editBuffer), stream);
    fclose(stream);
    source = editBuffer;
  }

  g_gameParser.Reset();
  g_gameParser.AddStandardConstants();
  g_gameParser.m_globalVariables = NULL;
  g_gameParser.CompileStatements(source);

  if (g_gameIsRunning) {
    if (g_gameParser.m_hasError) {
      SetWindowText(g_gameLevelEditorStatusWindow, g_gameParser.m_errorMessage);
    } else {
      SetWindowText(g_gameLevelEditorStatusWindow,
                    "Sumotori Dreams level editor");
      g_gameParser.PrepareEvaluation();
      g_gameParser.Evaluate();
    }
  } else if (g_gameParser.m_hasError) {
    MessageBox(NULL, g_gameParser.m_errorMessage, "Error in MOD file",
               MB_ICONEXCLAMATION);
  }

  if (g_currentBox != NULL) {
    Matrix3 savedOrientation = g_currentBox->orientation;
    SumoF32 savedBreakability = g_currentBox->breakability;
    bool wasImmovable = g_currentBox->flagD0;

    g_currentBox->FinishContacts(1);
    g_currentBox->RecalculateMass();
    g_currentBox->ClearForces();
    g_currentBox->InitializePhysics();
    if (wasImmovable) {
      g_currentBox->MakeImmovable();
    }

    g_currentBox->orientation = savedOrientation;
    g_currentBox->breakability = savedBreakability;
  }

  GameMan *man = g_gameMen;
  if (man < g_nextGameMan) {
    Vector3 lateralAxis;
    lateralAxis.x = 0.0f;
    lateralAxis.y = 0.0f;
    lateralAxis.z = 0.0f;
    Vector3 facingAxis;
    facingAxis.x = 0.0f;
    facingAxis.y = 0.0f;
    facingAxis.z = 0.0f;

    do {
      Vector3 lateral = lateralAxis;
      Vector3 facing = facingAxis;
      man->state700 = (SumoS32)man->FindNearestOpponent(facing, lateral);
      ++man;
    } while (man < g_nextGameMan);
  }

  if (g_gameParser.m_hasError) {
    g_gameContactObjectsEnd = g_gameContactObjects;
    g_nextGameMan = g_gameMen;
    g_gameBoxesEnd = g_gameBoxes;
  }

  RefreshGameContactLists();
}
