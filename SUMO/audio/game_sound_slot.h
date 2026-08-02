#ifndef SUMOTORI_GAME_SOUND_SLOT_H
#define SUMOTORI_GAME_SOUND_SLOT_H

#include "types.h"

#include <dsound.h>

#undef PlaySound

// SIZE 0x1e8
class GameSoundSlot {
public:
  void *PlaySound(SumoF32 p_frequencyScale, SumoF32 p_volumeScale,
                  SumoS32 p_channel);

private:
  SumoS32 m_frequency;                // 0x000
  IDirectSoundBuffer *m_buffers[120]; // 0x004
  SumoS32 m_nextBuffer;               // 0x1e4
};

#endif
