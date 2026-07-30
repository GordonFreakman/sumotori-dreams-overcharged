#include "game_runtime.h"

#include <new>

// FUNCTION: SUMO 0x00408389
// FUNCTION: EDITOR 0x004083ab
void GameBox::DestroyGeometry() {
  operator delete(pointsBegin);
  operator delete(pointReferencesBegin);
  operator delete(facesBegin);
  operator delete(edgesBegin);
}

// FUNCTION: SUMO 0x004083b0
// FUNCTION: EDITOR 0x004083d2
void ResetGameBoxes() {
  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    box->DestroyGeometry();
    ++box;
  }
  g_gameBoxesEnd = g_gameBoxes;
}

// FUNCTION: SUMO 0x00408e08
// FUNCTION: EDITOR 0x00408e2a
void RenderGameBoxes(SumoS32) {
  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    box->Render();
    ++box;
  }
}

// FUNCTION: SUMO 0x00408ec7
// FUNCTION: EDITOR 0x00408ee9
void LimitDynamicBoxes() {
  SumoF32 smallestMass = g_immovableMass;
  GameBox *smallestBox = 0;
  SumoS32 dynamicCount = 0;

  GameBox *box = g_gameBoxes;
  while (box < g_gameBoxesEnd) {
    if (box->contactLinks == 0 && !box->flagD0 && !box->flag58) {
      if (smallestMass > box->mass) {
        smallestBox = box;
        smallestMass = box->mass;
      }
      ++dynamicCount;
    }
    ++box;
  }

  if (dynamicCount > 90 && smallestBox != 0) {
    smallestBox->flag58 = true;
  }
}
