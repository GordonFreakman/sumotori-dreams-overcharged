#include "game_runtime.h"

#include <new>

// FUNCTION: SUMO 0x004089bc
// FUNCTION: EDITOR 0x004089de
void GameBox::BuildEdges() {
  edgesBegin = (GameBoxEdge *)operator new(
      (pointReferencesEnd - pointReferencesBegin) * sizeof(GameBoxEdge));
  edgesEnd = edgesBegin;

  GameBoxFace *face = facesBegin;
  while (face < facesEnd) {
    SumoS32 previousIndex = face->pointCount - 1;
    SumoS32 index = 0;
    while (index < face->pointCount) {
      if (face->pointReferences[index].index >
          face->pointReferences[previousIndex].index) {
        edgesEnd->firstIndex = face->pointReferences[index].index;
        edgesEnd->secondIndex = face->pointReferences[previousIndex].index;
        edgesEnd->firstFace = face;
        edgesEnd->secondFace = NULL;
        ++edgesEnd;
      }

      previousIndex = index;
      ++index;
    }

    ++face;
  }

  face = facesBegin;
  while (face < facesEnd) {
    SumoS32 previousIndex = face->pointCount - 1;
    SumoS32 index = 0;
    while (index < face->pointCount) {
      if (face->pointReferences[index].index <
          face->pointReferences[previousIndex].index) {
        GameBoxEdge *edge = edgesBegin;
        while (edge->firstIndex != face->pointReferences[previousIndex].index ||
               edge->secondIndex != face->pointReferences[index].index) {
          ++edge;
        }
        edge->secondFace = face;
      }

      previousIndex = index;
      ++index;
    }

    ++face;
  }
}
