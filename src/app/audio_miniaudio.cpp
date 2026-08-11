#include "boundary.h"

#define MA_ASSERT(condition) SDL_assert(condition)
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_GENERATION
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

static ma_context s_context;
static ma_device s_device;
static bool s_contextReady;
static bool s_deviceReady;

static void DeviceCallback(ma_device *device, void *output, const void *input,
                           ma_uint32 frameCount) {
  (void)device;
  (void)input;
  SumoAudioMix((float *)output, (SumoS32)frameCount);
}

static bool OpenWithContext(SumoS32 sampleRate) {
  ma_device_config config = ma_device_config_init(ma_device_type_playback);
  config.playback.format = ma_format_f32;
  config.playback.channels = 2;
  config.sampleRate = (ma_uint32)sampleRate;
  config.dataCallback = DeviceCallback;
  if (ma_device_init(s_contextReady ? &s_context : NULL, &config, &s_device) !=
      MA_SUCCESS)
    return false;
  if (ma_device_start(&s_device) != MA_SUCCESS) {
    ma_device_uninit(&s_device);
    return false;
  }
  s_deviceReady = true;
  return true;
}

bool SumoAudioDeviceOpenMiniaudio(SumoS32 sampleRate) {
  if (s_deviceReady)
    return true;
  if (OpenWithContext(sampleRate))
    return true;
  ma_backend nullBackend = ma_backend_null;
  if (ma_context_init(&nullBackend, 1, NULL, &s_context) != MA_SUCCESS)
    return false;
  s_contextReady = true;
  if (OpenWithContext(sampleRate))
    return true;
  ma_context_uninit(&s_context);
  s_contextReady = false;
  return false;
}

void SumoAudioDeviceCloseMiniaudio() {
  if (s_deviceReady) {
    ma_device_uninit(&s_device);
    s_deviceReady = false;
  }
  if (s_contextReady) {
    ma_context_uninit(&s_context);
    s_contextReady = false;
  }
}
