#include "boundary.h"

#define MA_ASSERT(condition) SDL_assert(condition)
//#define MA_NO_DECODING
//#define MA_NO_ENCODING
///#define MA_NO_RESOURCE_MANAGER
//#define MA_NO_NODE_GRAPH
//#define MA_NO_ENGINE
//#define MA_NO_GENERATION
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#ifdef SUMOSPACIAL
ma_engine g_MAEngine;
static ma_sound g_audio[2048];
#endif

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

#ifdef SUMOSPACIAL

void SumoAudioCreateEngine()
{
  ma_engine_config engineConfig = ma_engine_config_init();
  //engineConfig.noDevice = MA_TRUE;
  engineConfig.channels = 2;
  //engineConfig.sampleRate = 44100;
  ma_result result = ma_engine_init(&engineConfig, &g_MAEngine);

  if (result != MA_SUCCESS) {
    printf("Failed to initialize engine.\n");
  }
}
void SumoAudioPrecacheWAV(const char *path, SumoAssetBlob *blob)
{
  ma_resource_manager_register_encoded_data(
      ma_engine_get_resource_manager(&g_MAEngine), path, blob->data, blob->size);
}

void SumoAudioUpdateOrigin(Vector3 origin, Vector3 angle) 
{
  
  ma_engine_listener_set_position(&g_MAEngine, 0, origin.x, origin.y, -origin.z);
  ma_engine_listener_set_direction(&g_MAEngine, 0, angle.x, angle.y, -angle.z);
  ///ma_engine_listener_set_world_up(&g_MAEngine, 0, 0, 0, -1);
}

void SumoAudioCreateAudio(SumoAudioSource sound, SumoF32 frequencyScale,
                          SumoF32 volumeScale, SumoS32 channel, Vector3 origin) {


  for (size_t i = 0; i < 2048; i++) 
  {
      if (!ma_sound_is_playing(&g_audio[i])) 
      {
        ma_sound_uninit(&g_audio[i]);
        if (ma_sound_init_from_file(&g_MAEngine, sound.path, 0, NULL, NULL, &g_audio[i]) == MA_SUCCESS)
        {
          ma_sound_set_attenuation_model(&g_audio[i],
                                         ma_attenuation_model_linear);
          ma_sound_set_position(&g_audio[i], origin.x, origin.y, -origin.z);
          ma_sound_set_min_distance(&g_audio[i], 0.f);
          ma_sound_set_max_distance(&g_audio[i], 256.f);

          //ma_sound_set_max_gain(&g_audio[i], volumeScale);
          //ma_sound_set_rolloff(&g_audio[i], 10.f);
          ma_sound_set_pitch(&g_audio[i], frequencyScale);

              if (volumeScale > 1.0f) 
              {
                    ma_sound_set_max_distance(&g_audio[i], 256.f * volumeScale);
                    volumeScale = 1.0f;
                }

          ma_sound_set_volume(&g_audio[i], volumeScale);
          ma_sound_start(&g_audio[i]);
        }
        break;
      }
    }
}
#endif