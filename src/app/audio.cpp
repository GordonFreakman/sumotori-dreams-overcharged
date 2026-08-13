#include "boundary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xm.h>

enum {
  c_audioVoiceCount = 64,
  c_audioStopChannelCount = 8,
  c_audioSourceCount = 7,
  c_audioDeviceRate = 44100
};

static const SumoU8 c_audioLogicalToSource[8] = {0, 1, 0, 2, 3, 4, 5, 6};

struct SumoAudioSource {
  SumoAssetBlob blob;
  const SumoS16 *samples;
  SumoU32 frameCount;
  SumoU32 sampleRate;
};

struct SumoAudioVoice {
  SumoS32 source;
  double position;
  double step;
  SumoF32 gain;
  bool playing;
};

extern SumoU8 g_gameAudioEnabled;
extern SumoU32 g_gameTimeScaleDenominator;

SumoS32 g_gameAudioPlaybackMode;

extern const SumoF64 g_gameSoundLogBase = 10.0;

static SumoAudioSource s_sources[c_audioSourceCount];
static SumoAudioVoice s_voices[c_audioVoiceCount];
static SumoS32 s_stopChannels[c_audioStopChannelCount] = {-1, -1, -1, -1,
                                                          -1, -1, -1, -1};
static xm_context_t *s_musicContext;
static void *s_musicContextBuffer;
static bool s_deviceOpen;
static SumoMutex *s_mixLock;

#if !defined(SUMO_AUDIO_DEFAULT_BACKEND)
#define SUMO_AUDIO_DEFAULT_BACKEND 0
#endif
static SumoAudioBackend s_backend =
    (SumoAudioBackend)SUMO_AUDIO_DEFAULT_BACKEND;

bool SumoParseAudioBackend(const char *text, SumoAudioBackend *backend) {
  if (text == NULL)
    return false;
  if (SDL_strcasecmp(text, "sdl") == 0) {
    *backend = c_sumoAudioBackendSdl;
    return true;
  }
  if (SDL_strcasecmp(text, "miniaudio") == 0) {
    *backend = c_sumoAudioBackendMiniaudio;
    return true;
  }
  return false;
}

const char *SumoAudioBackendName(SumoAudioBackend backend) {
  return backend == c_sumoAudioBackendMiniaudio ? "miniaudio" : "sdl";
}

void SumoAudioSetBackend(SumoAudioBackend backend) {
  if (s_deviceOpen && backend != s_backend) {
    fprintf(
        stderr,
        "sumotori: audio device already open on %s; ignoring switch to %s\n",
        SumoAudioBackendName(s_backend), SumoAudioBackendName(backend));
    return;
  }
  s_backend = backend;
}

SumoAudioBackend SumoAudioGetBackend() { return s_backend; }

bool SumoAudioDeviceOpen(SumoS32 sampleRate) {
  if (s_backend == c_sumoAudioBackendMiniaudio)
    return SumoAudioDeviceOpenMiniaudio(sampleRate);
  return SumoAudioDeviceOpenSdl(sampleRate);
}

void SumoAudioDeviceClose() {
  if (s_backend == c_sumoAudioBackendMiniaudio)
    SumoAudioDeviceCloseMiniaudio();
  else
    SumoAudioDeviceCloseSdl();
}

static bool LoadWavSource(SumoAudioSource *source, const char *relative) {
  SumoAssetBlob blob;
  if (!SumoAssetOpen(relative, &blob))
    return false;

  const SumoU8 *header = (const SumoU8 *)blob.data;
  if (blob.size < 44 || memcmp(header, "RIFF", 4) != 0 ||
      memcmp(header + 8, "WAVE", 4) != 0) {
    SumoAssetClose(&blob);
    return false;
  }
  SumoU32 sampleRate;
  SumoU32 dataBytes;
  memcpy(&sampleRate, header + 24, 4);
  memcpy(&dataBytes, header + 40, 4);
  if (dataBytes > blob.size - 44) {
    SumoAssetClose(&blob);
    return false;
  }

  source->blob = blob;
  source->samples = (const SumoS16 *)(header + 44);
  source->frameCount = dataBytes / 2;
  source->sampleRate = sampleRate;
  return true;
}

static void DestroyMusicContext() {
  if (s_musicContextBuffer != NULL) {
    free(s_musicContextBuffer);
    s_musicContextBuffer = NULL;
    s_musicContext = NULL;
  }
}

static bool LoadMusicContext() {
  DestroyMusicContext();

  SumoAssetBlob module;
  if (!SumoAssetOpen("audio/music/sumotori.xm", &module))
    return false;
  const char *moduleData = (const char *)module.data;
  SumoU32 length = module.size;

  char *prescan = (char *)malloc(XM_PRESCAN_DATA_SIZE);
  if (prescan == NULL ||
      !xm_prescan_module(moduleData, length, (xm_prescan_data_t *)prescan)) {
    SumoAssetClose(&module);
    free(prescan);
    return false;
  }
  s_musicContextBuffer =
      malloc(xm_size_for_context((xm_prescan_data_t *)prescan));
  if (s_musicContextBuffer == NULL) {
    SumoAssetClose(&module);
    free(prescan);
    return false;
  }
  s_musicContext =
      xm_create_context((char *)s_musicContextBuffer,
                        (xm_prescan_data_t *)prescan, moduleData, length);
  SumoAssetClose(&module);
  free(prescan);
  if (s_musicContext == NULL) {
    DestroyMusicContext();
    return false;
  }
  xm_set_sample_rate(s_musicContext, c_audioDeviceRate);
  xm_set_max_loop_count(s_musicContext, 0);
  return true;
}

void SumoAudioMix(float *output, SumoS32 frameCount) {
  memset(output, 0, (size_t)frameCount * 2 * sizeof(float));
  SDL_LockMutex(s_mixLock);

  if (s_musicContext != NULL) {
    static float musicBuffer[4096];
    SumoS32 remaining = frameCount;
    float *cursor = output;
    while (remaining > 0) {
      SumoS32 chunk = remaining > 2048 ? 2048 : remaining;
      xm_generate_samples(s_musicContext, musicBuffer, (SumoU16)chunk);
      for (SumoS32 index = 0; index < chunk * 2; ++index)
        cursor[index] += musicBuffer[index];
      cursor += chunk * 2;
      remaining -= chunk;
    }
  }

  for (SumoS32 index = 0; index < c_audioVoiceCount; ++index) {
    SumoAudioVoice *voice = &s_voices[index];
    if (!voice->playing)
      continue;
    const SumoAudioSource *source = &s_sources[voice->source];
    for (SumoS32 frame = 0; frame < frameCount; ++frame) {
      SumoU32 base = (SumoU32)voice->position;
      if (base + 1 >= source->frameCount) {
        voice->playing = false;
        break;
      }
      float fraction = (float)(voice->position - base);
      float sample = ((float)source->samples[base] * (1.0f - fraction) +
                      (float)source->samples[base + 1] * fraction) /
                     32768.0f * voice->gain;
      output[frame * 2] += sample;
      output[frame * 2 + 1] += sample;
      voice->position += voice->step;
    }
  }

  SDL_UnlockMutex(s_mixLock);
}

SumoU8 InitializeGameAudio() {
  if (!g_gameAudioEnabled)
    return 0;

  if (s_mixLock == NULL)
    s_mixLock = SDL_CreateMutex();

  static const char *c_sourceNames[c_audioSourceCount] = {
      "audio/sfx/source0.wav", "audio/sfx/source1.wav",
      "audio/sfx/source2.wav", "audio/sfx/source3.wav", 
      "audio/sfx/source4.wav", "audio/sfx/source5.wav",
      "audio/sfx/source6.wav"};
  bool complete = true;
  for (SumoS32 index = 0; index < c_audioSourceCount; ++index) {
    if (s_sources[index].samples == NULL &&
        !LoadWavSource(&s_sources[index], c_sourceNames[index])) {
      complete = false;
    }
  }
  if (!complete)
    fprintf(stderr, "sumotori: some sound effects failed to load\n");

  if (!s_deviceOpen) {
    s_deviceOpen = SumoAudioDeviceOpen(c_audioDeviceRate);
    if (!s_deviceOpen)
      fprintf(stderr, "sumotori: %s audio backend could not open a device\n",
              SumoAudioBackendName(s_backend));
  }
  return s_deviceOpen ? 1 : 0;
}

static void InitializeGameMusicCommon() {
  if (!g_gameAudioEnabled)
    return;
  SDL_LockMutex(s_mixLock);
  if (LoadMusicContext()) {
    xm_seek(s_musicContext, (SumoU8)g_gameAudioPlaybackMode, 0, 0);
  } else {
    fprintf(stderr, "sumotori: music module failed to load\n");
  }
  SDL_UnlockMutex(s_mixLock);
}

void InitializeGameMusic() {
  g_gameAudioPlaybackMode = 3;
  InitializeGameMusicCommon();
}

void RestartGameMusic(SumoS32 playbackMode) {
  if (!g_gameAudioEnabled)
    return;
  g_gameAudioPlaybackMode = playbackMode;
  InitializeGameMusicCommon();
}

SumoU32 GameAudioShutdown() {
  if (s_deviceOpen) {
    SumoAudioDeviceClose();
    s_deviceOpen = false;
  }
  SDL_LockMutex(s_mixLock);
  DestroyMusicContext();
  SDL_UnlockMutex(s_mixLock);
  return 0;
}

void ReplayRecordCommand(SumoS32 first, SumoS32 second, SumoS32 third,
                         SumoS32 fourth);

void GameAudioNoOpCallback() {}

void *PlayGameSound(SumoS32 soundIndex, SumoF32 frequencyScale,
                    SumoF32 volumeScale, SumoS32 channel) {
  SumoS32 frequencyBits;
  SumoS32 volumeBits;
  memcpy(&frequencyBits, &frequencyScale, sizeof(frequencyBits));
  memcpy(&volumeBits, &volumeScale, sizeof(volumeBits));
  ReplayRecordCommand(soundIndex, frequencyBits, volumeBits, channel);

  if (!s_deviceOpen || soundIndex < 0 || soundIndex >= 8 || channel < 0 ||
      channel >= c_audioStopChannelCount) {
    return NULL;
  }
  SumoS32 source = c_audioLogicalToSource[soundIndex];
  if (s_sources[source].samples == NULL)
    return NULL;

  SumoF32 gain = volumeScale > 1.0f ? 1.0f : volumeScale;
  if (gain <= 0.0f)
    return NULL;

  SDL_LockMutex(s_mixLock);
  if (channel != 0) {
    SumoS32 previous = s_stopChannels[channel];
    if (previous >= 0)
      s_voices[previous].playing = false;
  }

  SumoS32 slot = 0;
  while (slot < c_audioVoiceCount && s_voices[slot].playing)
    ++slot;
  if (slot == c_audioVoiceCount)
    slot = 0;
  s_stopChannels[channel] = slot;

  SumoAudioVoice *voice = &s_voices[slot];
  voice->source = source;
  voice->position = 0.0;
  voice->step = (double)s_sources[source].sampleRate * frequencyScale /
                (double)g_gameTimeScaleDenominator / (double)c_audioDeviceRate;
  voice->gain = gain;
  voice->playing = true;
  SDL_UnlockMutex(s_mixLock);
  return voice;
}
