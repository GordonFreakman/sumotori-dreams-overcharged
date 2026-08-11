#include "boundary.h"

static SDL_AudioDeviceID s_device;

static void SDLCALL DeviceCallback(void *userdata, Uint8 *stream, int length) {
  (void)userdata;
  SumoAudioMix((float *)stream, length / (int)(2 * sizeof(float)));
}

bool SumoAudioDeviceOpenSdl(SumoS32 sampleRate) {
  if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
    return false;
  SDL_AudioSpec want;
  SDL_zero(want);
  want.freq = sampleRate;
  want.format = AUDIO_F32SYS;
  want.channels = 2;
  want.samples = 1024;
  want.callback = DeviceCallback;
  s_device = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);
  if (s_device == 0)
    return false;
  SDL_PauseAudioDevice(s_device, 0);
  return true;
}

void SumoAudioDeviceCloseSdl() {
  if (s_device != 0) {
    SDL_CloseAudioDevice(s_device);
    s_device = 0;
  }
}
