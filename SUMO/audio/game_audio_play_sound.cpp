#include "game_sound_slot.h"

#include "decomp.h"

struct IDirect3DResource9;
extern "C" double log(double);

extern SumoS32 g_gameSoundInitialized;
extern IDirectSound8 *g_gameDirectSound;
extern SumoS32 g_deferredReleaseWriteIndex;
extern IDirect3DResource9 **g_deferredReleaseSlots[1024];
extern IDirectSoundBuffer **g_gameActiveSoundSlots[9];
extern const double g_gameSoundLogBase;
extern const SumoF32 g_gameSoundVolumeScale;

SumoU32 ReleaseNextQueuedRenderResource();

// FUNCTION: SUMO 0x004151f4
// FUNCTION: EDITOR 0x00415216
void *GameSoundSlot::PlaySound(SumoF32 p_frequencyScale, SumoF32 p_volumeScale, SumoS32 p_channel) {
  DWORD status;
  SumoF32 logBase;

  if (!g_gameSoundInitialized) {
    return NULL;
  }

  m_nextBuffer = 0;
  do {
    if (m_buffers[m_nextBuffer] == NULL) {
      break;
    }

    m_buffers[m_nextBuffer]->GetStatus(&status);
    if (!(status & DSBSTATUS_PLAYING)) {
      break;
    }

    ++m_nextBuffer;
  } while (m_nextBuffer < 120);

  if (m_nextBuffer == 120) {
    m_nextBuffer = 0;
  }

  while (m_buffers[m_nextBuffer] == NULL) {
    if (g_gameDirectSound->DuplicateSoundBuffer(
            m_buffers[0], &m_buffers[m_nextBuffer]) != DS_OK) {
      ReleaseNextQueuedRenderResource();
    } else {
      g_deferredReleaseSlots[g_deferredReleaseWriteIndex] =
          (IDirect3DResource9 **)&m_buffers[m_nextBuffer];
      g_deferredReleaseWriteIndex = (g_deferredReleaseWriteIndex + 1) & 0x3ff;
    }
  }

  if (m_buffers[m_nextBuffer] != NULL) {
    m_buffers[m_nextBuffer]->SetFrequency(
        (DWORD)(m_frequency * p_frequencyScale));
    logBase = (SumoF32)log(g_gameSoundLogBase);
    m_buffers[m_nextBuffer]->SetVolume(
        (LONG)(log(p_volumeScale) / logBase * g_gameSoundVolumeScale));
    m_buffers[m_nextBuffer]->SetCurrentPosition(0);
    m_buffers[m_nextBuffer]->Play(0, 0, 0);
  }

  IDirectSoundBuffer **result = &m_buffers[m_nextBuffer];
  ++m_nextBuffer;
  if (m_nextBuffer == 120) {
    m_nextBuffer = 0;
  }

  g_gameActiveSoundSlots[p_channel] = &m_buffers[m_nextBuffer];
  return result;
}

DECOMP_SIZE_ASSERT(GameSoundSlot, 0x1e8);
