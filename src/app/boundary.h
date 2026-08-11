#ifndef SUMOAPP_SUMOAPP_H
#define SUMOAPP_SUMOAPP_H

#include "types.h"

#if SUMO_SDL_VERSION == 3
#include <SDL3/SDL.h>
#else
#include <SDL.h>
#endif

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
  SumoS32 quality;
  bool soundEnabled;
  SumoS32 audioBackend;
  bool editorRequested;
  char modPath[1024];
};
void SumoLoadStartupConfig(SumoStartupConfig *config);
void ApplyGameQuality(SumoS32 qualityCode);
void SumoSaveStartupConfig(const SumoStartupConfig *config);
bool SumoRunStartupUI(SumoStartupConfig *config);

void SumoInstallExtraLevels();

struct SumoAssetBlob {
  const void *data;
  SumoU32 size;
  bool owned;
};
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

#endif
