#include "game_audio_tracker.h"
#include "types.h"

#include <math.h>

// GLOBAL: SUMO 0x0042cda0
// GLOBAL: EDITOR 0x0042cda0
extern const double g_trackerAutoVibratoAmplitude = 64.0;

// GLOBAL: SUMO 0x0042cda8
// GLOBAL: EDITOR 0x0042cda8
extern const float g_trackerAutoVibratoPhaseScale = 0.024543688f;


// FUNCTION: SUMO 0x00417a99
// FUNCTION: EDITOR 0x00417abb
void UpdateTrackerAutoVibrato(TrackerChannelState *channel, GameAudioInstrument *instrument) {

  SumoS32 waveform;
  switch (instrument->vibratoType) {
  case 0:
    waveform = (SumoS32)(sin(channel->instrumentVibratoPosition *
                             g_trackerAutoVibratoPhaseScale) *
                         g_trackerAutoVibratoAmplitude);
    break;
  case 1:
    waveform = channel->instrumentVibratoPosition < 128 ? 64 : -64;
    break;
  case 2:
    waveform = (128 - (channel->instrumentVibratoPosition + 128) % 256) >> 1;
    break;
  case 3:
    waveform = (128 - (384 - channel->instrumentVibratoPosition) % 256) >> 1;
    break;
  }

  SumoS32 modulation = waveform * instrument->vibratoDepth;
  if (instrument->vibratoSweep != 0) {
    modulation =
        modulation * channel->instrumentVibratoSweep / instrument->vibratoSweep;
  }
  channel->periodDelta += modulation >> 6;

  ++channel->instrumentVibratoSweep;
  if (channel->instrumentVibratoSweep > instrument->vibratoSweep)
    channel->instrumentVibratoSweep = instrument->vibratoSweep;

  channel->instrumentVibratoPosition += instrument->vibratoRate;
  if (channel->instrumentVibratoPosition > 255)
    channel->instrumentVibratoPosition -= 256;
  channel->dirtyFlags |= 1;
}

// GLOBAL: SUMO 0x0042cd98
// GLOBAL: EDITOR 0x0042cd98
extern const double g_trackerVibratoPhaseScale = 0.049087375;
