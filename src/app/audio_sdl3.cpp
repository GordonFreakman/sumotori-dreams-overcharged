#include "boundary.h"

static SDL_AudioStream *s_stream;

static void SDLCALL StreamCallback(void *userdata, SDL_AudioStream *stream,
                                   int additionalAmount, int totalAmount) {
  (void)userdata;
  (void)totalAmount;
  static float buffer[4096];
  int remaining = additionalAmount / (int)(2 * sizeof(float));
  while (remaining > 0) {
    int chunk = remaining > 2048 ? 2048 : remaining;
    SumoAudioMix(buffer, chunk);
    SDL_PutAudioStreamData(stream, buffer, chunk * (int)(2 * sizeof(float)));
    remaining -= chunk;
  }
}

bool SumoAudioDeviceOpenSdl(SumoS32 sampleRate) {
  if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
    return false;
  SDL_AudioSpec spec;
  spec.format = SDL_AUDIO_F32;
  spec.channels = 2;
  spec.freq = sampleRate;
  s_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec,
                                       StreamCallback, NULL);
  if (s_stream == NULL)
    return false;
  SDL_ResumeAudioStreamDevice(s_stream);
  return true;
}

void SumoAudioDeviceCloseSdl() {
  if (s_stream != NULL) {
    SDL_DestroyAudioStream(s_stream);
    s_stream = NULL;
  }
}
