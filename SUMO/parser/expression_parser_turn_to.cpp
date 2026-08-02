#include "expression_parser.h"
#include "game_runtime.h"

#include <math.h>

// FUNCTION: SUMO 0x00404d6d
// FUNCTION: EDITOR 0x00404d8f
void ParserBuiltinTurnTo(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_currentBox == NULL) {
    return;
  }

  g_currentBox->orientation.RotateRows02(
      ParserAtan2Value(call->arguments[0]->x, call->arguments[0]->z));

  Vector3 horizontal =
      MakeVector3(call->arguments[0]->x, call->arguments[0]->z, 0.0f);
  g_currentBox->orientation.RotateRows12(ParserAtan2Value(
      call->arguments[0]->y,
      (SumoF32)sqrt(horizontal.x * horizontal.x + horizontal.y * horizontal.y +
                    horizontal.z * horizontal.z)));
}
