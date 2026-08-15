#ifndef SUMOAPP_SUMOAPP_H
#define SUMOAPP_SUMOAPP_H

#include "types.h"

#define SUMOSPACIAL
#if SUMO_SDL_VERSION == 3
#include <SDL3/SDL.h>
#else
#include <SDL.h>
#endif

enum {
  c_audioVoiceCount = 64,
  c_audioStopChannelCount = 8,
  c_audioSourceCount = 5 * 4,
  c_audioDeviceRate = 44100
};

struct SumoAssetBlob {
  const void *data;
  SumoU32 size;
  bool owned;
};

struct SumoWavHeader {
  // RIFF Header
  char riff_header[4]; // Contains "RIFF"
  int wav_size;        // Size of the wav portion of the file, which follows the
                       // first 8 bytes. File size - 8
  char wave_header[4]; // Contains "WAVE"

  // Format Header
  char fmt_header[4]; // Contains "fmt " (includes trailing space)
  int fmt_chunk_size; // Should be 16 for PCM
  short audio_format; // Should be 1 for PCM. 3 for IEEE Float
  short num_channels;
  int sample_rate;
  int byte_rate; // Number of bytes per second. sample_rate * num_channels *
                 // Bytes Per Sample
  short sample_alignment; // num_channels * Bytes Per Sample
  short bit_depth;        // Number of bits per sample

  // Data
  char data_header[4]; // Contains "data"
  int data_bytes; // Number of bytes in data. Number of samples * num_channels
                  // * sample byte size
                  // uint8_t bytes[]; // Remainder of wave file is bytes
};

struct SumoAudioSource {
  SumoAssetBlob blob;
  const SumoS16 *samples;
  SumoU32 frameCount;
  SumoU32 sampleRate;
  SumoWavHeader header;
  const char *path;
};

bool SumoPlatformCreateWindow(SumoS32 width, SumoS32 height, bool fullscreen);
void SumoPlatformDestroyWindow();
SDL_Window *SumoPlatformWindow();

void PumpGameMessages();
void SumoResolveWindowSize(SumoS32 requestedWidth, SumoS32 requestedHeight,
                           SumoS32 desktopWidth, SumoS32 desktopHeight,
                           SumoS32 *outWidth, SumoS32 *outHeight);
void SetGameFpuControlWord();
void SumoAttachParentConsole();
SumoU32 GetScaledGameTime();
void ExitGameProcess();
void SetGameCursorVisible(SumoU8 visible);
bool SumoPlatformQuitRequested();

SumoU8 SumoTranslateScancode(SumoS32 sdlScancode);
void SumoHandleKeyDown(SumoS32 sdlScancode);
void SumoHandleKeyUp(SumoS32 sdlScancode);
void SumoHandleLeftMouseDown(SumoS32 x, SumoS32 y);

void SumoRenderRequestGLAttributes();
bool SumoRenderCreateContext();
void SumoRenderPresent();
void SumoRenderUpdateTargetSize();
void SumoRenderAdoptTargetSize(SumoS32 width, SumoS32 height);
void SumoRenderMarkProjectionLive();
bool SumoRenderContextReady();

struct SumoStartupConfig {
  SumoS32 width;
  SumoS32 height;
  bool fullscreen;
  int quality;
  bool soundEnabled;
  bool soundRandomized;
  SumoS32 audioBackend;
  bool editorRequested;
  char modPath[1024];
};
void SumoLoadStartupConfig(SumoStartupConfig *config);
void ApplyGameQuality(int qualityCode);
void SumoSaveStartupConfig(const SumoStartupConfig *config);
bool SumoRunStartupUI(SumoStartupConfig *config);

void SumoInstallExtraLevels();

bool SumoAssetOpen(const char *relative, SumoAssetBlob *blob);
bool SumoAssetOpenFile(const char *path, SumoAssetBlob *blob);
void SumoAssetClose(SumoAssetBlob *blob);

struct SumoIconImage {
  SumoU8 *pixels;
  SumoS32 width;
  SumoS32 height;
};
bool SumoDecodeIcon(const void *iconData, SumoU32 iconSize,
                    SumoIconImage *image);
bool SumoLoadWindowIcon(SumoIconImage *image);
void SumoFreeIcon(SumoIconImage *image);
void SumoApplyWindowIcon(SDL_Window *window);

void SumoOverlayProcessEvent(void *sdlEvent);
bool SumoOverlayWantCaptureKeyboard();
bool SumoOverlayWantCaptureMouse();
void SumoOverlayDraw();

void SumoEditorEnter();
bool SumoEditorActive();
void SumoEditorDrawPanel();
void SumoEditorSetDocument(const char *text);
const char *SumoEditorStatus();

void SumoRequestModFilePicker();
bool SumoModPickerActive();
void SumoModPickerDrawPanel();
void SumoModPickerCancel();
bool SumoModPickerSetDirectory(const char *path);
const char *SumoModPickerDirectory();
SumoS32 SumoModPickerEntryCount();
const char *SumoModPickerEntryName(SumoS32 index);
bool SumoModPickerEntryIsDirectory(SumoS32 index);
bool SumoModPickerChoose(SumoS32 index);
bool SumoModPickerLoadFile(const char *path);

#if SUMO_SDL_VERSION == 3
typedef SDL_Mutex SumoMutex;
#else
typedef SDL_mutex SumoMutex;
#endif

enum SumoAudioBackend {
  c_sumoAudioBackendSdl = 0,
  c_sumoAudioBackendMiniaudio = 1
};
bool SumoAudioDeviceOpenSdl(SumoS32 sampleRate);
void SumoAudioDeviceCloseSdl();
bool SumoAudioDeviceOpenMiniaudio(SumoS32 sampleRate);
void SumoAudioDeviceCloseMiniaudio();

void SumoAudioSetBackend(SumoAudioBackend backend);
SumoAudioBackend SumoAudioGetBackend();
const char *SumoAudioBackendName(SumoAudioBackend backend);
bool SumoParseAudioBackend(const char *text, SumoAudioBackend *backend);

bool SumoAudioDeviceOpen(SumoS32 sampleRate);
void SumoAudioDeviceClose();
void SumoAudioMix(float *output, SumoS32 frameCount);
void SumoAudioCreateEngine();
void SumoAudioPrecacheWAV(const char *path, SumoAssetBlob *blob);
void SumoAudioCreateAudio(SumoAudioSource sound, SumoF32 frequencyScale, SumoF32 volumeScale, SumoS32 channel, Vector3 origin);
void SumoAudioUpdateOrigin(Vector3 origin, Vector3 angle);
#endif
