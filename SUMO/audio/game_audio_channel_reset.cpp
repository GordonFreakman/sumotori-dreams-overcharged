#include "game_audio_tracker.h"
#include "types.h"

#include <math.h>

// GLOBAL: SUMO 0x0042cda0
// GLOBAL: EDITOR 0x0042cda0
extern const double g_trackerAutoVibratoAmplitude = 64.0;

// GLOBAL: SUMO 0x0042cda8
// GLOBAL: EDITOR 0x0042cda8
extern const float g_trackerAutoVibratoPhaseScale = 0.024543688f;

extern const double g_trackerVibratoPhaseScale;
extern const double g_textureSize;

// FUNCTION: SUMO 0x004179f9
// FUNCTION: EDITOR 0x00417a1b
void UpdateTrackerVibrato(TrackerChannelState *channel) {

  SumoS32 waveform;
  switch (channel->waveformControl & 3) {
  case 0: {
    SumoF64 phase = channel->vibratoPosition;
    waveform = (SumoS32)fabs(sin((phase + phase) * g_trackerVibratoPhaseScale) *
                             g_textureSize);
    break;
  }
  case 1: {
    SumoU8 ramp = channel->vibratoPosition << 3;
    if (channel->vibratoPosition < 0) {
      ramp = 255 - ramp;
    }
    waveform = ramp;
    break;
  }
  case 2:
  case 3:
    waveform = 255;
    break;
  }

  SumoS32 delta = ((channel->vibratoDepth * waveform) >> 5) & ~3;
  if (channel->vibratoPosition >= 0) {
    delta = -delta;
  }

  channel->dirtyFlags |= 1;
  channel->periodDelta = delta;
}

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

// FUNCTION: SUMO 0x00417f89
// FUNCTION: EDITOR 0x00417fab
void ResetTrackerChannelState(TrackerChannelState *channel, GameAudioParsedSample *sample) {
  channel->volume = sample->defaultVolume;
  channel->panning = sample->panning;

  channel->volumeEnvelopeValue = 64;
  channel->volumeEnvelopePoint = 0;
  channel->volumeEnvelopeTick = 0;
  channel->volumeEnvelopeDelta = 0;

  channel->panningEnvelopeValue = 32;
  channel->panningEnvelopePoint = 0;
  channel->panningEnvelopeTick = 0;
  channel->panningEnvelopeDelta = 0;

  channel->keyOff = 0;
  channel->fadeoutVolume = 0x10000;
  channel->volumeEnvelopeStopped = 0;
  channel->panningEnvelopeStopped = 0;
  channel->instrumentVibratoSweep = 0;
  channel->instrumentVibratoPosition = 0;

  if ((channel->waveformControl & 0x0f) < 4) {
    channel->vibratoPosition = 0;
  }
  if ((channel->waveformControl & 0xf0) < 0x40) {
    channel->tremoloPosition = 0;
  }

  channel->dirtyFlags |= 6;
  channel->tremorPosition = 0;
}

// GLOBAL: SUMO 0x0042cd98
// GLOBAL: EDITOR 0x0042cd98
extern const double g_trackerVibratoPhaseScale = 0.049087375;
