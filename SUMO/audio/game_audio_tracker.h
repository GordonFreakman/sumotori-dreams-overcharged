/******************************************************************************/
/* MiniFMOD-derived tracker layouts                                           */
/*                                                                            */
/* MiniFMOD public source code release.                                       */
/* This source is provided as-is. Firelight Multimedia will not support or    */
/* answer questions about the source provided.                                */
/* MiniFMOD Sourcecode is copyright (c) 2000, Firelight Multimedia.           */
/* MiniFMOD Sourcecode is in no way representative of FMOD 3 source.          */
/* Firelight Multimedia is a registered business name.                        */
/* This source must not be redistributed without this notice.                 */
/******************************************************************************/

#ifndef SUMOTORI_GAME_AUDIO_TRACKER_H
#define SUMOTORI_GAME_AUDIO_TRACKER_H

#include "types.h"

typedef struct TrackerPatternEvent TrackerPatternEvent;
typedef struct GameAudioPattern GameAudioPattern;
typedef struct GameAudioTimeInfo GameAudioTimeInfo;
typedef struct GameAudioParsedSample GameAudioParsedSample;
typedef struct GameAudioInstrument GameAudioInstrument;
typedef struct GameAudioMixerChannel GameAudioMixerChannel;
typedef struct TrackerChannelState TrackerChannelState;
typedef struct GameAudioParsedModule GameAudioParsedModule;

struct TrackerPatternEvent {
  SumoU8 note;
  SumoU8 number;
  SumoU8 volume;
  SumoU8 effect;
  SumoU8 eparam;
};

struct GameAudioPattern {
  SumoS32 rowCount;
  TrackerPatternEvent *events;
};


#pragma pack(push, 1)
struct GameAudioTimeInfo {
  SumoU8 order;
  SumoU8 row;
  SumoU32 milliseconds;
};
#pragma pack(pop)


struct GameAudioParsedSample {
  SumoS16 *data;
  SumoU32 length;
  SumoU32 loopStart;
  SumoU32 loopLength;
  SumoU8 defaultVolume;
  SumoS8 fineTune;
  SumoU8 alignment12[2];
  SumoS32 defaultFrequency;
  SumoS32 panning;
  SumoU8 bitDepth;
  SumoU8 loopMode;
  SumoU8 globalVolume;
  SumoS8 relativeNote;
  SumoS32 middleC;
  SumoU32 sustainLoopBegin;
  SumoU32 sustainLoopEnd;
  SumoU8 vibratoSpeed;
  SumoU8 vibratoDepth;
  SumoU8 vibratoType;
  SumoU8 vibratoRate;
};


struct GameAudioInstrument {
  SumoS32 sampleCount;
  GameAudioParsedSample *samples[16];
  SumoU8 sampleMap[96];
  SumoU16 volumeEnvelope[40];
  SumoU16 panningEnvelope[40];
  SumoU8 volumeEnvelopePointCount;
  SumoU8 panningEnvelopePointCount;
  SumoU8 volumeSustainPoint;
  SumoU8 volumeLoopStart;
  SumoU8 volumeLoopEnd;
  SumoU8 panningSustainPoint;
  SumoU8 panningLoopStart;
  SumoU8 panningLoopEnd;
  SumoU8 volumeEnvelopeType;
  SumoU8 panningEnvelopeType;
  SumoU8 vibratoType;
  SumoU8 vibratoSweep;
  SumoU8 vibratoDepth;
  SumoU8 vibratoRate;
  SumoU16 volumeFadeout;
};


struct GameAudioMixerChannel {
  SumoS32 index;
  SumoS32 volume;
  SumoS32 frequency;
  SumoS32 panning;
  SumoS32 actualVolume;
  SumoS32 actualPanning;
  SumoU32 sampleOffset;
  GameAudioParsedSample *sample;
  SumoU32 leftVolume;
  SumoU32 rightVolume;
  SumoU32 mixPosition;
  SumoU32 mixPositionFraction;
  SumoU32 speedFraction;
  SumoU32 speedInteger;
  SumoU32 speedDirection;
  SumoU32 rampLeftTarget;
  SumoU32 rampRightTarget;
  SumoU32 rampLeftVolume;
  SumoU32 rampRightVolume;
  SumoU32 rampLeftSpeed;
  SumoU32 rampRightSpeed;
  SumoU32 rampCount;
};


struct TrackerChannelState {
  SumoU8 note;
  SumoU8 sampleNumber;
  SumoU8 dirtyFlags;
  SumoU8 alignment03;
  GameAudioMixerChannel *mixer;
  GameAudioParsedSample *sample;
  SumoS32 period;
  SumoS32 volume;
  SumoS32 panning;
  SumoS32 volumeDelta;
  SumoS32 periodDelta;
  SumoS32 panningDelta;
  SumoS32 sampleGlobalVolume;
  SumoS32 volumeEnvelopeTick;
  SumoS32 volumeEnvelopePoint;
  SumoS32 volumeEnvelopeAccumulator;
  SumoS32 volumeEnvelopeValue;
  SumoS32 volumeEnvelopeDelta;
  SumoS8 volumeEnvelopeStopped;
  SumoU8 alignment3D[3];
  SumoS32 panningEnvelopeTick;
  SumoS32 panningEnvelopePoint;
  SumoS32 panningEnvelopeAccumulator;
  SumoS32 panningEnvelopeValue;
  SumoS32 panningEnvelopeDelta;
  SumoS8 panningEnvelopeStopped;
  SumoU8 alignment55[3];
  SumoS32 fadeoutVolume;
  SumoS32 instrumentVibratoPosition;
  SumoS32 instrumentVibratoSweep;
  SumoS8 fade;
  SumoS8 keyOff;
  SumoU8 instrumentNumber;
  SumoU8 realNote;
  SumoU32 targetPeriod;
  SumoU8 recentEffect;
  SumoU8 alignment6D[3];
  SumoU32 sampleOffset;
  SumoS32 globalVolume;
  SumoU8 portamentoDown;
  SumoU8 portamentoUp;
  SumoU8 extraPortamentoDown;
  SumoU8 extraPortamentoUp;
  SumoU8 volumeSlide;
  SumoU8 panningSlide;
  SumoU8 retriggerVolumeMode;
  SumoU8 retriggerTickCount;
  SumoS32 portamentoTarget;
  SumoU8 portamentoSpeed;
  SumoS8 vibratoPosition;
  SumoU8 vibratoSpeed;
  SumoU8 vibratoDepth;
  SumoU8 vibratoType;
  SumoS8 tremoloPosition;
  SumoU8 tremoloSpeed;
  SumoU8 tremoloDepth;
  SumoS32 panningVibratoPosition;
  SumoU8 panningVibratoSpeed;
  SumoU8 panningVibratoDepth;
  SumoU8 tremorPosition;
  SumoU8 tremorOn;
  SumoU8 tremorOff;
  SumoU8 arpeggio;
  SumoU8 alignment96[2];
  SumoS32 patternLoopRow;
  SumoS32 patternLoopCount;
  SumoU8 channelVolumeSlide;
  SumoU8 specialParameter;
  SumoU8 waveformControl;
  SumoU8 vibratoWaveformControl;
  SumoU8 tremoloWaveformControl;
  SumoU8 panningWaveformControl;
  SumoU8 fineVolumeSlideDown;
  SumoU8 fineVolumeSlideUp;
  SumoU8 finePortamentoUp;
  SumoU8 finePortamentoDown;
  SumoU8 highSampleOffset;
  SumoU8 volumeColumnSlide;
};

typedef void(__cdecl *GameAudioSampleDecodeCallback)(void *output,
                                                     SumoU32 byteCount,
                                                     SumoU32 bitDepth,
                                                     SumoS32 instrumentIndex,
                                                     SumoU32 sampleIndex);


struct GameAudioParsedModule {
  GameAudioPattern *patterns;
  GameAudioInstrument *instruments;
  SumoS32 mixerSamplesLeft;
  SumoS32 mixerSamplesPerTick;
  SumoS16 songLength;
  SumoS16 restartPosition;
  SumoS16 channelCount;
  SumoU8 alignment016[2];
  SumoS32 usedPatternCount;
  SumoS32 allocatedPatternCount;
  SumoS16 instrumentCount;
  SumoU16 frequencyMode;
  SumoS16 initialTempo;
  SumoS16 initialBpm;
  SumoU8 patternOrder[256];
  SumoU8 defaultVolume;
  SumoU8 alignment129[3];
  SumoS32 globalVolume;
  SumoU8 globalVolumeSlide;
  SumoU8 alignment131[3];
  SumoS32 currentTick;
  SumoS32 tempo;
  SumoS32 bpm;
  SumoS32 currentRow;
  SumoS32 orderIndex;
  SumoS32 rowDelay;
  SumoS32 pendingRow;
  SumoS32 pendingOrder;
  SumoS32 elapsedMilliseconds;
  void(__cdecl *startupCallback)(void *);
  void(__cdecl *tickCallback)(GameAudioParsedModule *);
  GameAudioSampleDecodeCallback decodeCallback;
};

struct TrackerEnvelopePoint {
  SumoU16 tick;
  SumoU16 value;
};

typedef char
    GameAudioSampleSizeCheck[sizeof(GameAudioParsedSample) == 0x30 ? 1 : -1];
typedef char
    GameAudioTimeInfoSizeCheck[sizeof(GameAudioTimeInfo) == 0x6 ? 1 : -1];
typedef char
    GameAudioInstrumentSizeCheck[sizeof(GameAudioInstrument) == 0x154 ? 1 : -1];
typedef char
    GameAudioMixerChannelSizeCheck[sizeof(GameAudioMixerChannel) == 0x58 ? 1
                                                                         : -1];
typedef char
    TrackerChannelStateSizeCheck[sizeof(TrackerChannelState) == 0xac ? 1 : -1];
typedef char
    GameAudioModuleSizeCheck[sizeof(GameAudioParsedModule) == 0x164 ? 1 : -1];

#endif
