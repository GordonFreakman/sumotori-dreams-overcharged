#include "game_audio_tracker.h"

// FUNCTION: SUMO 0x00417c7d
// FUNCTION: EDITOR 0x00417c9f
extern "C" void ApplyTrackerVolumeColumn(TrackerChannelState *channel, SumoU8 command) {
  if (command >= 0x10 && command <= 0x50) {
    channel->dirtyFlags |= 2;
    channel->volume = command - 0x10;
    return;
  }

  switch (command >> 4) {
  case 6:
  case 8:
    channel->volume -= command & 0x0f;
    if (channel->volume < 0) {
      channel->volume = 0;
    }
    channel->dirtyFlags |= 2;
    break;

  case 7:
  case 9:
    channel->volume += command & 0x0f;
    if (channel->volume > 64) {
      channel->volume = 64;
    }
    channel->dirtyFlags |= 2;
    break;

  case 0xa:
    channel->vibratoSpeed = command & 0x0f;
    break;

  case 0xb:
    channel->vibratoDepth = command & 0x0f;
    break;

  case 0xc:
    channel->panning = (command & 0x0f) << 4;
    channel->dirtyFlags |= 4;
    break;

  case 0xd:
    channel->panning -= command & 0x0f;
    channel->dirtyFlags |= 4;
    break;

  case 0xe:
    channel->panning += command & 0x0f;
    channel->dirtyFlags |= 4;
    break;

  case 0xf:
    if ((command & 0x0f) != 0) {
      channel->portamentoSpeed = command << 4;
    }
    channel->portamentoTarget = channel->targetPeriod;
    channel->dirtyFlags &= 0xf7;
    break;
  }
}
