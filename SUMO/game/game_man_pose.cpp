#include "game_runtime.h"

// FUNCTION: SUMO 0x0040e718
// FUNCTION: EDITOR 0x0040e73a
void GameManPose::InitializeJointTransforms(GameMan *p_man) {
  for (SumoS32 index = 0; index < sizeof(joints) / sizeof(joints[0]); ++index) {
    joints[index].firstDirection =
        p_man->joints[index]->boxes[1]->orientation.Transform(
            p_man->joints[index]->firstPoseDirection.Transform(
                p_man->joints[index]->boxes[0]->orientation));
    joints[index].secondDirection =
        p_man->joints[index]->boxes[1]->orientation.Transform(
            p_man->joints[index]->secondPoseDirection.Transform(
                p_man->joints[index]->boxes[0]->orientation));
  }
}
