#include "game_audio_tracker.h"
#include "game_audio_xm_adapter.h"
#include "game_sound_slot.h"
#include "types.h"

#include <dsound.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern "C" SumoS32 _ftol2();
extern "C" SumoS32 _ftol();
extern "C" double floor(double);
extern "C" double pow(double, double);
extern const SumoF32 g_gameOne;
extern const SumoF32 g_vectorZero;
extern SumoU8 *g_textureColorMap;
extern SumoU32 *g_textureWorkBuffer;
extern SumoU32 *g_textureChannelSwapBuffer;
extern SumoU8 *g_textureLayers[4];
extern SumoU8 *g_textureByteBuffer;
extern SumoU8 *g_textureIoBuffer;
extern const double g_textureColorMapRowScale;
extern const double g_textureOne;
extern const double g_textureByteMaximum;
extern SumoU8 g_textureGeneratorInitialized;
typedef void(__stdcall *TextureProgressCallback)(SumoF32 progress);
extern TextureProgressCallback g_textureProgressCallback;
extern SumoS32 g_textureProgramTotalWork;
extern SumoS32 g_textureProgramCompletedWork;
extern SumoU8 g_textureLoadFromTga;
extern SumoU8 *g_textureCommandCursor;
extern SumoU8 *g_gameSoundSources[8];
extern SumoU8 g_gameAudioEnabled;
extern HWND g_gameWindow;
extern SumoU32 g_gameTimeScaleDenominator;

typedef SumoS32(__cdecl *GameAudioOpenCallback)(SumoS32 source);
typedef void(__cdecl *GameAudioCloseCallback)(SumoS32 value);
typedef SumoS32(__cdecl *GameAudioIoCallback)(SumoS32 first, SumoS32 second,
                                              SumoS32 value);
typedef SumoS32(__cdecl *GameAudioTellCallback)(SumoS32 value);

extern GameAudioOpenCallback g_gameAudioCreateValue;
extern GameAudioCloseCallback g_gameAudioDestroyValue;
extern GameAudioIoCallback g_gameAudioInvokeTail;
extern GameAudioIoCallback g_gameAudioInvokeHead;
extern GameAudioTellCallback g_gameAudioReleaseCallback;

extern "C" void ConfigureGameAudioStreamCallbacks(
    GameAudioOpenCallback openCallback, GameAudioCloseCallback closeCallback,
    GameAudioIoCallback readCallback, GameAudioIoCallback seekCallback,
    GameAudioTellCallback tellCallback);

SumoU8 InitializeGameDirectSound();
SumoU8 DecodeGameSoundAssets();
SumoU8 InitializeGameAudioOutput(SumoS32 sampleRate, SumoS32 flags);
void *LoadGameAudioModule(SumoS32 source, SumoS32 flags);
SumoU8 StartGameAudioModule(SumoU8 *module);
SumoU8 DestroyGameAudioModule(void *module);
GameAudioOwnedBlock *CreateGameAudioOwnedBlock(SumoS32 source, char flag,
                                               SumoS32 userValue);
void DestroyGameAudioOwnedBlock(GameAudioOwnedBlock *block);
extern "C" SumoS8 ParseGameAudioModule(GameAudioParsedModule *module,
                                       GameAudioOwnedBlock *block);
void FillGameAudioBuffer();
void ConvertGameAudioPcm(void *destination, void *source, SumoS32 length);
void MixGameAudioChannels(void *buffer, SumoS32 frameCount, SumoS32 flags);
DWORD GameAudioThreadMain(void *parameter);
void ReplayRecordCommand(SumoS32 p_first, SumoS32 p_second, SumoS32 p_third,
                         SumoS32 p_fourth);

// GLOBAL: SUMO 0x0042cdb0
// GLOBAL: EDITOR 0x0042cdb0
extern const double g_trackerLinearBaseFrequency = 8363.0;
// GLOBAL: SUMO 0x0042cdb8
// GLOBAL: EDITOR 0x0042cdb8
extern const SumoF32 g_trackerLinearPeriodScale = 1.0f / 768.0f;
// GLOBAL: SUMO 0x0042cdbc
// GLOBAL: EDITOR 0x0042cdbc
extern const SumoF32 g_trackerLinearPeriodBase = 4608.0f;

extern const double g_textureHueSectorTwo;
// GLOBAL: SUMO 0x0042cdc0
// GLOBAL: EDITOR 0x0042cdc0
extern const SumoF32 g_trackerVolumeScale =
    (255.0f / (64.0f * 64.0f * 65536.0f * 64.0f)) * 0.5f;

// GLOBAL: SUMO 0x0042c718
// GLOBAL: EDITOR 0x0042c718
extern const char g_gameMusicFilename[] = "f.xm";

// STRING: SUMO 0x0042cb10
// STRING: EDITOR 0x0042cb10
// GLOBAL: SUMO 0x00453864
// GLOBAL: EDITOR 0x00453864
char *g_gameScreenshotPrefix = "shot";

// GLOBAL: SUMO 0x00c0e9fc
// GLOBAL: EDITOR 0x00c0f21c
extern IDirectSound8 *g_gameDirectSound;

// GLOBAL: SUMO 0x00453868
// GLOBAL: EDITOR 0x00453868
SumoS32 g_gameUsePrimaryBuffer = 1;

// GLOBAL: SUMO 0x00c0ea24
// GLOBAL: EDITOR 0x00c0f244
extern SumoS32 g_gameSoundInitialized;

// GLOBAL: SUMO 0x00c0ea00
// GLOBAL: EDITOR 0x00c0f220
extern IDirectSoundBuffer **g_gameActiveSoundSlots[9];

// GLOBAL: SUMO 0x0042c4f8
// GLOBAL: EDITOR 0x0042c4f8
extern const double g_gameSoundLogBase = 10.0;

// GLOBAL: SUMO 0x0042cb24
// GLOBAL: EDITOR 0x0042cb24
extern const SumoF32 g_gameSoundVolumeScale = 2000.0f;

// GLOBAL: SUMO 0x00c09ce8
// GLOBAL: EDITOR 0x00c0a508
SumoS32 g_gameScreenshotIndex;

// GLOBAL: SUMO 0x00c09cf4
// GLOBAL: EDITOR 0x00c0a514
extern SumoU8 g_gameSoundSlots[0x3cfc];

// GLOBAL: SUMO 0x00c09cf0
// GLOBAL: EDITOR 0x00c0a510
extern SumoS32 g_gameSoundSlotFrequency0;

// GLOBAL: SUMO 0x00c0d9f4
// GLOBAL: EDITOR 0x00c0e214
extern IDirectSoundBuffer *g_gamePrimarySoundBuffer;

// GLOBAL: SUMO 0x0042cdd8
// GLOBAL: EDITOR 0x0042cdd8
extern const GUID g_gameNullGuid = {0};

// GLOBAL: SUMO 0x00453cf0
// GLOBAL: EDITOR 0x00453cf4
char g_textureExportFilename[] = "tex00000.tga";

// GLOBAL: SUMO 0x00453d00
// GLOBAL: EDITOR 0x00453d04
SumoU8 g_textureTgaHeader[13] = {0, 0, 2};

extern "C" SumoS32 __ftol() { return _ftol(); }

extern "C" __declspec(naked) double _floor(double) {
  __asm {
    jmp floor
  }
}

struct GameAudioStreamContext {
  SumoS32 size;
  SumoU32 position;
  SumoU8 *data;
};


// GLOBAL: SUMO 0x00436070
// GLOBAL: EDITOR 0x00436070
extern SumoU8 g_gameAudioData[];

// GLOBAL: SUMO 0x004ea4c0
// GLOBAL: EDITOR 0x004eace0
GameAudioStreamContext g_gameAudioStream;

// FUNCTION: SUMO 0x00407c63
// FUNCTION: EDITOR 0x00407c85
GameAudioStreamContext *GameAudioOpenStream() {
  g_gameAudioStream.position = 0;
  g_gameAudioStream.data = g_gameAudioData;
  g_gameAudioStream.size = 0x20000;
  return &g_gameAudioStream;
}

// FUNCTION: SUMO 0x00407c84
// FUNCTION: EDITOR 0x00407ca6
void GameAudioNoOpCallback() {}


// FUNCTION: SUMO 0x00407c85
// FUNCTION: EDITOR 0x00407ca7
SumoS32 GameAudioRead(void *destination, SumoS32 size, GameAudioStreamContext *context) {

  SumoS32 readSize = size;
  if ((SumoS32)(context->position + size) >= context->size) {
    readSize = context->size - context->position;
  }

  memcpy(destination, context->data + context->position, readSize);
  context->position += readSize;
  return readSize;
}


// FUNCTION: SUMO 0x00407cba
// FUNCTION: EDITOR 0x00407cdc
GameAudioStreamContext *GameAudioSeek(GameAudioStreamContext *context, SumoS32 offset, SumoS8 origin) {

  if (origin == 0) {
    context->position = offset;
  } else if (origin == 1) {
    context->position += offset;
  } else if (origin == 2) {
    context->position = context->size + offset;
  }

  if ((SumoS32)context->position > context->size) {
    context->position = context->size;
  }
  return context;
}

// FUNCTION: SUMO 0x00407cf3
// FUNCTION: EDITOR 0x00407d15
SumoU32 GameAudioGetStreamPosition(GameAudioStreamContext *context) {
  return context->position;
}

SumoU8 GameAudioShutdownBackend(SumoS32 active);
MMRESULT GameAudioCloseOutput();

// GLOBAL: SUMO 0x004ea4d0
// GLOBAL: EDITOR 0x004eacf0
SumoS32 g_gameAudioModule;

// GLOBAL: SUMO 0x00d0f218
// GLOBAL: EDITOR 0x00d0fa34
SumoS32 g_gameAudioPlaybackMode;

// FUNCTION: SUMO 0x00407cfb
// FUNCTION: EDITOR 0x00407d1d
static void InitializeGameMusicCommon() {
  if (!g_gameAudioEnabled) {
    return;
  }

  ConfigureGameAudioStreamCallbacks(
      (GameAudioOpenCallback)GameAudioOpenStream,
      (GameAudioCloseCallback)GameAudioNoOpCallback,
      (GameAudioIoCallback)GameAudioRead, (GameAudioIoCallback)GameAudioSeek,
      (GameAudioTellCallback)GameAudioGetStreamPosition);
  InitializeGameAudioOutput(44100, 0);
  g_gameAudioModule =
      (SumoS32)LoadGameAudioModule((SumoS32)g_gameMusicFilename, 0);
  StartGameAudioModule((SumoU8 *)g_gameAudioModule);
}

// FUNCTION: SUMO 0x00407d49
// FUNCTION: EDITOR 0x00407d6b
void InitializeGameMusic() {
  g_gameAudioPlaybackMode = 3;
  InitializeGameMusicCommon();
}

// FUNCTION: SUMO 0x00407d58
// FUNCTION: EDITOR 0x00407d7a
void RestartGameMusic(SumoS32 playbackMode) {
  if (!g_gameAudioEnabled) {
    return;
  }

  DestroyGameAudioModule((void *)g_gameAudioModule);
  GameAudioCloseOutput();
  g_gameAudioPlaybackMode = playbackMode;
  InitializeGameMusicCommon();
}

// FUNCTION: SUMO 0x00407d81
// FUNCTION: EDITOR 0x00407da3
MMRESULT GameAudioShutdown() {
  GameAudioShutdownBackend(g_gameAudioModule);
  return GameAudioCloseOutput();
}

typedef void(__cdecl *ReplayRecordSoundCall)(SumoS32, SumoF32, SumoF32,
                                             SumoS32);

// FUNCTION: SUMO 0x00415369
// FUNCTION: EDITOR 0x0041538b
void *PlayGameSound(SumoS32 p_soundIndex, SumoF32 p_frequencyScale, SumoF32 p_volumeScale, SumoS32 p_channel) {
  ((ReplayRecordSoundCall)ReplayRecordCommand)(p_soundIndex, p_frequencyScale,
                                               p_volumeScale, p_channel);

  if (p_channel && g_gameActiveSoundSlots[p_channel] != NULL &&
      *g_gameActiveSoundSlots[p_channel] != NULL) {
    (*g_gameActiveSoundSlots[p_channel])->Stop();
  }

  GameSoundSlot *slots = (GameSoundSlot *)&g_gameSoundSlotFrequency0;
  return slots[p_soundIndex].PlaySound(p_frequencyScale, p_volumeScale,
                                       p_channel);
}

// FUNCTION: SUMO 0x004155bc
// FUNCTION: EDITOR 0x004155de
SumoU8 InitializeGameDirectSound() {
  if (DirectSoundCreate8(NULL, &g_gameDirectSound, NULL) != DS_OK) {
    return 0;
  }

  g_gameDirectSound->SetCooperativeLevel(g_gameWindow, DSSCL_PRIORITY);

  DSBUFFERDESC descriptor;
  descriptor.dwSize = sizeof(descriptor);
  descriptor.dwFlags = g_gameUsePrimaryBuffer ? 0x15 : 0x19;
  descriptor.dwBufferBytes = 0;
  descriptor.dwReserved = 0;
  descriptor.lpwfxFormat = NULL;
  descriptor.guid3DAlgorithm = g_gameNullGuid;
  if (g_gameDirectSound->CreateSoundBuffer(
          &descriptor, &g_gamePrimarySoundBuffer, NULL) != DS_OK) {
    return 0;
  }

  if (!DecodeGameSoundAssets()) {
    g_gamePrimarySoundBuffer->Release();
    g_gameDirectSound->Release();
    return 0;
  }

  g_gameSoundInitialized = 1;
  return 1;
}

// FUNCTION: SUMO 0x00415678
// FUNCTION: EDITOR 0x0041569a
SumoU8 InitializeGameAudio() {
  if (!g_gameAudioEnabled) {
    return 0;
  }

  g_gameUsePrimaryBuffer = 1;
  if (InitializeGameDirectSound()) {
    return 1;
  }

  g_gameUsePrimaryBuffer = 0;
  return InitializeGameDirectSound();
}



// GLOBAL: SUMO 0x00d0f620
// GLOBAL: EDITOR 0x00d0fe38
volatile SumoU8 g_gameAudioStopRequested;

// GLOBAL: SUMO 0x00d0f621
// GLOBAL: EDITOR 0x00d0fe39
volatile SumoU8 g_gameAudioWorkerBusy;

// GLOBAL: SUMO 0x00d0f624
// GLOBAL: EDITOR 0x00d0fe3c
volatile HANDLE g_gameAudioThread;

// GLOBAL: SUMO 0x00453cec
// GLOBAL: EDITOR 0x00453cf0
volatile SumoU8 g_gameAudioThreadFinished = 1;

// GLOBAL: SUMO 0x00d157c8
// GLOBAL: EDITOR 0x00d15fc8
void *g_gameAudioBlock;

// GLOBAL: SUMO 0x00d16f20
// GLOBAL: EDITOR 0x00d17720
WAVEHDR g_gameWaveHeader;

// GLOBAL: SUMO 0x00d0f214
// GLOBAL: EDITOR 0x00d0fa30
SumoS32 g_gameAudioActive;

// GLOBAL: SUMO 0x00d16db0
// GLOBAL: EDITOR 0x00d175b0
GameAudioTimeInfo *g_gameAudioSecondaryBlock;

// GLOBAL: SUMO 0x00d16f44
// GLOBAL: EDITOR 0x00d17744
HWAVEOUT g_gameWaveOut;

// GLOBAL: SUMO 0x00d16db4
// GLOBAL: EDITOR 0x00d175b4
SumoS32 g_gameAudioMixRate;

// GLOBAL: SUMO 0x00d16d60
// GLOBAL: EDITOR 0x00d17560
SumoS32 g_gameAudioOutputSampleCount;

// GLOBAL: SUMO 0x00d157c4
// GLOBAL: EDITOR 0x00d15fc4
SumoS32 g_gameAudioFramesPerBuffer;

// GLOBAL: SUMO 0x00d157e0
// GLOBAL: EDITOR 0x00d15fe0
extern SumoU8 g_gameAudioChannelStates[0x1600];

// GLOBAL: SUMO 0x00d0ffc0
// GLOBAL: EDITOR 0x00d107c0
extern GameAudioMixerChannel g_gameAudioChannelScratch[256];

// GLOBAL: SUMO 0x00d115c0
// GLOBAL: EDITOR 0x00d11dc0
extern SumoU8 g_gameAudioChannelScratchEnd;

// GLOBAL: SUMO 0x00d157c0
// GLOBAL: EDITOR 0x00d15fc0
void *g_gameAudioAlignedMixBlock;

// GLOBAL: SUMO 0x00d0f628
// GLOBAL: EDITOR 0x00d0fe40
volatile SumoS32 g_gameAudioBufferIndex;

// GLOBAL: SUMO 0x00d16f40
// GLOBAL: EDITOR 0x00d17740
void *g_gameAudioPcmBlock;

// GLOBAL: SUMO 0x00d157cc
// GLOBAL: EDITOR 0x00d15fcc
SumoF32 g_gameAudioTimeIncrement;

// GLOBAL: SUMO 0x00453ce8
// GLOBAL: EDITOR 0x00453cec
SumoS32 g_gameAudioBufferDuration = 1000;

// GLOBAL: SUMO 0x00d0f684
// GLOBAL: EDITOR 0x00d0fe9c
SumoU32 g_gameAudioMixStep;

// GLOBAL: SUMO 0x00d0f688
// GLOBAL: EDITOR 0x00d0fea0
SumoF32 g_gameAudioInverseMixStep;

// GLOBAL: SUMO 0x0042cd7c
// GLOBAL: EDITOR 0x0042cd7c
extern const SumoF32 g_gameAudioPcmScale255 = 255.0f;

// GLOBAL: SUMO 0x0042cd80
// GLOBAL: EDITOR 0x0042cd80
extern const SumoF32 g_gameAudioPcmScale256 = 256.0f;

// GLOBAL: SUMO 0x0042cd84
// GLOBAL: EDITOR 0x0042cd84
extern const SumoF32 g_gameAudioUnitOver255 = 1.0f / 255.0f;

// GLOBAL: SUMO 0x0042cd88
// GLOBAL: EDITOR 0x0042cd88
extern const SumoF32 g_gameAudioUnitOver256 = 1.0f / 256.0f;

// GLOBAL: SUMO 0x0042cd8c
// GLOBAL: EDITOR 0x0042cd8c
extern const SumoF32 g_gameAudioFixedPointScale = 1.0f / 2147483648.0f;

// GLOBAL: SUMO 0x00d0f62c
// GLOBAL: EDITOR 0x00d0fe44
volatile SumoS32 g_gameAudioWorkerBufferIndex;

// GLOBAL: SUMO 0x00d0f634
// GLOBAL: EDITOR 0x00d0fe4c
SumoU8 g_gameAudioMixerWorkspace[0x50];

extern const SumoF32 g_inertiaRadiusScale;

// GLOBAL: SUMO 0x0042cd68
// GLOBAL: EDITOR 0x0042cd68
extern const SumoF32 g_gameAudioMilliseconds = 1000.0f;

// GLOBAL: SUMO 0x0042c714
// GLOBAL: EDITOR 0x0042c714
extern const SumoF32 g_gameAudioSeconds = 0.001f;

struct GameAudioTiming {
  SumoU8 unknown000[0x0c];
  SumoS32 interval;
  SumoU8 unknown010[0x12c];
  SumoS32 rate;
};

// FUNCTION: SUMO 0x00416bc2
// FUNCTION: EDITOR 0x00416be4
__declspec(naked) void ConfigureGameAudioTiming(GameAudioTiming *timing, SumoS32 rate) {

  __asm {
    fild dword ptr [esp + 8]
    mov eax, dword ptr [esp + 8]
    push esi
    mov esi, dword ptr [esp + 8]
    fmul dword ptr [g_inertiaRadiusScale]
    mov dword ptr [esi + 13ch], eax
    fdivr dword ptr [g_gameAudioMilliseconds]
    fimul dword ptr [g_gameAudioMixRate]
    fmul dword ptr [g_gameAudioSeconds]
    call _ftol2
    mov dword ptr [esi + 0ch], eax
    pop esi
    ret
  }
}

// FUNCTION: SUMO 0x00416bf7
// FUNCTION: EDITOR 0x00416c19
SumoU8 GameAudioShutdownBackend(SumoS32 active) {
  if (!active) {
    return 0;
  }

  g_gameAudioStopRequested = 1;
  while (g_gameAudioWorkerBusy) {
  }

  if (g_gameAudioThread != 0) {
    while (!g_gameAudioThreadFinished) {
      Sleep(50);
    }
    g_gameAudioThread = 0;
  }

  if (g_gameAudioBlock != 0) {
    free(g_gameAudioBlock);
    g_gameAudioBlock = 0;
  }

  if (g_gameWaveHeader.lpData != 0) {
    waveOutUnprepareHeader(g_gameWaveOut, &g_gameWaveHeader,
                           sizeof(g_gameWaveHeader));
    g_gameWaveHeader.dwFlags &= ~WHDR_PREPARED;
  }

  g_gameAudioActive = 0;
  if (g_gameAudioSecondaryBlock != 0) {
    free(g_gameAudioSecondaryBlock);
    g_gameAudioSecondaryBlock = 0;
  }
  return 1;
}

// FUNCTION: SUMO 0x00416c8b
// FUNCTION: EDITOR 0x00416cad
SumoU8 DestroyGameAudioModule(void *modulePointer) {
  GameAudioParsedModule *module = (GameAudioParsedModule *)modulePointer;
  SumoS32 count;
  if (module == NULL) {
    return 0;
  }

  while (g_gameAudioWorkerBusy) {
  }

  GameAudioShutdownBackend((SumoS32)module);
  if (module->instruments != NULL) {
    for (count = 0; count < module->instrumentCount; ++count) {
      SumoS32 sampleIndex;
      GameAudioInstrument *instrument = &module->instruments[count];
      for (sampleIndex = 0; sampleIndex < instrument->sampleCount;
           ++sampleIndex) {
        if (instrument->samples[sampleIndex] != NULL) {
          GameAudioParsedSample *sample = instrument->samples[sampleIndex];
          free(sample->data);
          free(sample);
        }
      }
    }
  }

  if (module->instruments != NULL) {
    free(module->instruments);
  }

  if (module->patterns != NULL) {
    for (count = 0; count < module->allocatedPatternCount; ++count) {
      if (module->patterns[count].events != NULL) {
        free(module->patterns[count].events);
      }
    }

    if (module->patterns != NULL) {
      free(module->patterns);
    }
  }

  free(module);
  return 1;
}

// FUNCTION: SUMO 0x00416d5c
// FUNCTION: EDITOR 0x00416d7e
SumoU8 StartGameAudioModule(SumoU8 *modulePointer) {
  SumoS32 count;
  TrackerChannelState *channel;
  SumoS32 totalBlocks =
      g_gameAudioOutputSampleCount / g_gameAudioFramesPerBuffer;
  GameAudioParsedModule *module = (GameAudioParsedModule *)modulePointer;
  if (module == NULL) {
    return 0;
  }

  GameAudioShutdownBackend((SumoS32)module);

  module->globalVolume = module->defaultVolume;
  module->tempo = module->initialTempo;
  module->currentRow = 0;
  module->orderIndex = g_gameAudioPlaybackMode;
  module->pendingOrder = -1;
  module->pendingRow = -1;
  module->mixerSamplesLeft = 0;
  module->currentTick = 0;
  module->rowDelay = 0;
  module->elapsedMilliseconds = 0;

  if (module->startupCallback != NULL) {
    module->startupCallback(module);
  }

  ConfigureGameAudioTiming((GameAudioTiming *)module, module->initialBpm);
  memset(g_gameAudioChannelStates, 0,
         module->channelCount * sizeof(TrackerChannelState));
  for (count = 0; count < module->channelCount; ++count) {
    channel = &((TrackerChannelState *)g_gameAudioChannelStates)[count];
    channel->mixer = &g_gameAudioChannelScratch[count];
  }

  g_gameAudioActive = (SumoS32)module;
  g_gameAudioSecondaryBlock =
      (GameAudioTimeInfo *)calloc(totalBlocks * sizeof(GameAudioTimeInfo), 1);

  WAVEHDR *waveHeader = &g_gameWaveHeader;
  SumoS32 length = g_gameAudioOutputSampleCount;
  length <<= 2;
  g_gameAudioPcmBlock = calloc(length, 1);
  waveHeader->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
  waveHeader->lpData = (char *)g_gameAudioPcmBlock;
  waveHeader->dwBufferLength = length;
  waveHeader->dwBytesRecorded = 0;
  waveHeader->dwUser = 0;
  waveHeader->dwLoops = -1;
  waveOutPrepareHeader(g_gameWaveOut, waveHeader, sizeof(WAVEHDR));

  g_gameAudioBlock = calloc((g_gameAudioOutputSampleCount << 3) + 256, 1);
  g_gameAudioAlignedMixBlock =
      (void *)(((SumoU32)g_gameAudioBlock + 15) & 0xfffffff0);

  g_gameAudioBufferIndex = 0;
  do {
    FillGameAudioBuffer();
  } while (g_gameAudioBufferIndex);

  waveOutWrite(g_gameWaveOut, waveHeader, sizeof(WAVEHDR));

  {
    DWORD threadId;

    g_gameAudioStopRequested = FALSE;
    g_gameAudioThread = CreateThread(
        NULL, 0, (LPTHREAD_START_ROUTINE)GameAudioThreadMain, 0, 0, &threadId);
    SetThreadPriority(g_gameAudioThread, THREAD_PRIORITY_TIME_CRITICAL);
  }
  return 1;
}

// FUNCTION: SUMO 0x00416f16
// FUNCTION: EDITOR 0x00416f38
void *LoadGameAudioModule(SumoS32 source, SumoS32 decodeCallback) {
  GameAudioParsedModule *module =
      (GameAudioParsedModule *)calloc(sizeof(GameAudioParsedModule), 1);
  GameAudioOwnedBlock *block = CreateGameAudioOwnedBlock(source, 0, 0);
  if (block == NULL) {
    return NULL;
  }

  module->decodeCallback = (GameAudioSampleDecodeCallback)decodeCallback;
  SumoS8 loaded = ParseGameAudioModule(module, block);
  DestroyGameAudioOwnedBlock(block);
  if (!loaded) {
    DestroyGameAudioModule(module);
    return NULL;
  }

  return module;
}

// FUNCTION: SUMO 0x00416f6e
// FUNCTION: EDITOR 0x00416f90
MMRESULT GameAudioCloseOutput() {
  waveOutReset(g_gameWaveOut);
  return waveOutClose(g_gameWaveOut);
}

// FUNCTION: SUMO 0x00416f87
// FUNCTION: EDITOR 0x00416fa9
void FillGameAudioBuffer() {
  void *mixBuffer;
  SumoS32 mixPosition = g_gameAudioBufferIndex * g_gameAudioFramesPerBuffer;
  SumoS32 totalBlocks =
      g_gameAudioOutputSampleCount / g_gameAudioFramesPerBuffer;

  mixBuffer = (SumoU8 *)g_gameAudioAlignedMixBlock + (mixPosition << 3);
  memset(mixBuffer, 0, g_gameAudioFramesPerBuffer << 3);

  {
    SumoS32 mixedSoFar = 0;
    SumoS32 mixedLeft =
        ((GameAudioParsedModule *)g_gameAudioActive)->mixerSamplesLeft;
    SumoS32 samplesToMix;
    SumoS8 *mixPointer = (SumoS8 *)mixBuffer;

    while (mixedSoFar < g_gameAudioFramesPerBuffer) {
      if (!mixedLeft) {
        GameAudioParsedModule *module =
            (GameAudioParsedModule *)g_gameAudioActive;
        module->tickCallback(module);
        samplesToMix =
            ((GameAudioParsedModule *)g_gameAudioActive)->mixerSamplesPerTick;
        mixedLeft = samplesToMix;
      } else {
        samplesToMix = mixedLeft;
      }

      if (mixedSoFar + samplesToMix > g_gameAudioFramesPerBuffer) {
        samplesToMix = g_gameAudioFramesPerBuffer - mixedSoFar;
      }

      MixGameAudioChannels(mixPointer, samplesToMix, FALSE);
      mixedSoFar += samplesToMix;
      mixPointer += samplesToMix << 3;
      mixedLeft -= samplesToMix;
      ((GameAudioParsedModule *)g_gameAudioActive)->elapsedMilliseconds +=
          (SumoS32)(((SumoF32)samplesToMix * g_gameAudioTimeIncrement) *
                    g_gameAudioMilliseconds);
    }

    g_gameAudioSecondaryBlock[g_gameAudioBufferIndex].milliseconds =
        ((GameAudioParsedModule *)g_gameAudioActive)->elapsedMilliseconds;
    g_gameAudioSecondaryBlock[g_gameAudioBufferIndex].row =
        (SumoU8)((GameAudioParsedModule *)g_gameAudioActive)->currentRow;
    g_gameAudioSecondaryBlock[g_gameAudioBufferIndex].order =
        (SumoU8)((GameAudioParsedModule *)g_gameAudioActive)->orderIndex;
    ((GameAudioParsedModule *)g_gameAudioActive)->mixerSamplesLeft = mixedLeft;
  }

  {
    void *destination = (SumoU8 *)g_gameAudioPcmBlock + (mixPosition << 2);
    SumoU32 length = g_gameAudioFramesPerBuffer << 2;
    ConvertGameAudioPcm(destination, mixBuffer, length >> 2);
  }

  ++g_gameAudioBufferIndex;
  if (g_gameAudioBufferIndex >= totalBlocks) {
    g_gameAudioBufferIndex = 0;
  }
}

// FUNCTION: SUMO 0x004170ff
// FUNCTION: EDITOR 0x00417121
DWORD GameAudioThreadMain(void *) {
  SumoS32 totalBlocks;

  g_gameAudioThreadFinished = FALSE;
  totalBlocks = g_gameAudioOutputSampleCount / g_gameAudioFramesPerBuffer;

  while (!g_gameAudioStopRequested) {
    SumoS32 cursorPosition;
    SumoS32 cursorBlock;
    MMTIME time;

    time.wType = TIME_BYTES;
    waveOutGetPosition(g_gameWaveOut, &time, sizeof(MMTIME));
    time.u.cb >>= 2;
    cursorPosition = time.u.cb;
    cursorPosition %= g_gameAudioOutputSampleCount;
    cursorBlock = cursorPosition / g_gameAudioFramesPerBuffer;

    while (g_gameAudioBufferIndex != cursorBlock) {
      g_gameAudioWorkerBusy = TRUE;
      FillGameAudioBuffer();

      ++g_gameAudioWorkerBufferIndex;
      if (g_gameAudioWorkerBufferIndex >= totalBlocks) {
        g_gameAudioWorkerBufferIndex = 0;
      }

      g_gameAudioWorkerBusy = FALSE;
    }

    Sleep(5);
  }

  g_gameAudioThreadFinished = TRUE;
  return 0;
}

// FUNCTION: SUMO 0x004171b7
// FUNCTION: EDITOR 0x004171d9
SumoU8 InitializeGameAudioOutput(SumoS32 sampleRate, SumoS32) {
  SumoS32 count;
  WAVEFORMATEX format;

  if (g_gameAudioCreateValue == NULL || g_gameAudioDestroyValue == NULL ||
      g_gameAudioInvokeTail == NULL || g_gameAudioInvokeHead == NULL ||
      g_gameAudioReleaseCallback == NULL) {
    return 0;
  }

  GameAudioCloseOutput();
  g_gameAudioMixRate = sampleRate;

  format.wFormatTag = WAVE_FORMAT_PCM;
  format.nChannels = 2;
  format.wBitsPerSample = 16;
  format.nBlockAlign = format.nChannels * format.wBitsPerSample / 8;
  format.nSamplesPerSec = sampleRate / (SumoS32)g_gameTimeScaleDenominator;
  format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
  format.cbSize = 0;

  if (waveOutOpen(&g_gameWaveOut, WAVE_MAPPER, &format, 0, 0, 0) !=
      MMSYSERR_NOERROR) {
    return 0;
  }

  g_gameAudioTimeIncrement = g_gameOne / (SumoF32)sampleRate;
  g_gameAudioFramesPerBuffer =
      ((g_gameAudioMixRate * 20 / 1000) + 3) & 0xfffffffc;
  g_gameAudioOutputSampleCount =
      g_gameAudioFramesPerBuffer * (g_gameAudioBufferDuration / 20);
  g_gameAudioOutputSampleCount <<= 1;

  g_gameAudioMixStep = g_gameAudioMixRate * 128 / 44100;
  g_gameAudioInverseMixStep = g_gameOne / (SumoF32)g_gameAudioMixStep;

  memset(g_gameAudioChannelScratch, 0, sizeof(GameAudioMixerChannel) * 256);
  GameAudioMixerChannel *channel = g_gameAudioChannelScratch;
  count = 0;
  do {
    channel->index = count;
    channel->speedInteger = 1;
    ++channel;
    ++count;
  } while ((SumoS32)&channel->speedInteger < (SumoS32) &
           ((TrackerChannelState *)g_gameAudioChannelStates)->panning);

  return 1;
}

// FUNCTION: SUMO 0x004172fe
// FUNCTION: EDITOR 0x00417320
void ConvertGameAudioPcm(void *destination, void *source, SumoS32 length) {
  SumoS32 count;
  SumoS16 *destinationPointer = (SumoS16 *)destination;
  SumoF32 *sourcePointer = (SumoF32 *)source;

  if (length <= 0 || destination == NULL || source == NULL) {
    return;
  }

  for (count = 0; count < length << 1; ++count) {
    SumoS32 value;
    __asm {
      mov eax, sourcePointer
      fld dword ptr [eax]
      add sourcePointer, 4
      fistp value
    }
    *destinationPointer++ = (value < -32768  ? -32768
                             : value > 32767 ? 32767
                                             : value);
  }
}


struct GameAudioRamp {
  SumoU8 unknown00[2];
  SumoU8 flags;
  SumoU8 unknown03[9];
  SumoS32 current;
  SumoU8 unknown10[0x70];
  SumoS32 target;
  SumoU8 step;
};

// FUNCTION: SUMO 0x004179b6
// FUNCTION: EDITOR 0x004179d8
GameAudioRamp *UpdateGameAudioRamp(GameAudioRamp *ramp) {
  if (ramp->current < ramp->target) {
    ramp->current += ramp->step * 4;
    if (ramp->current > ramp->target) {
      ramp->current = ramp->target;
    }
  } else if (ramp->current > ramp->target) {
    ramp->current -= ramp->step * 4;
    if (ramp->current < ramp->target) {
      ramp->current = ramp->target;
    }
  }
  ramp->flags |= 1;
  return ramp;
}


// GLOBAL: SUMO 0x00d0f69c
// GLOBAL: EDITOR 0x00d0feb4
SumoS32 (__cdecl *g_gameAudioReleaseCallback)(SumoS32 value);

// GLOBAL: SUMO 0x00d0f68c
// GLOBAL: EDITOR 0x00d0fea4
SumoS32 (__cdecl *g_gameAudioCreateValue)(SumoS32 source);

// GLOBAL: SUMO 0x00d0f690
// GLOBAL: EDITOR 0x00d0fea8
void (__cdecl *g_gameAudioDestroyValue)(SumoS32 value);

// GLOBAL: SUMO 0x00d0f694
// GLOBAL: EDITOR 0x00d0feac
SumoS32 (__cdecl *g_gameAudioInvokeTail)(SumoS32 first, SumoS32 second, SumoS32 value);

// GLOBAL: SUMO 0x00d0f698
// GLOBAL: EDITOR 0x00d0feb0
SumoS32 (__cdecl *g_gameAudioInvokeHead)(SumoS32 value, SumoS32 second, SumoS32 third);


// GLOBAL: SUMO 0x00d16d80
// GLOBAL: EDITOR 0x00d17580
GameAudioParsedSample g_gameAudioEmptySample;

// GLOBAL: SUMO 0x00d16dc0
// GLOBAL: EDITOR 0x00d175c0
GameAudioInstrument g_gameAudioEmptyInstrument;

// GLOBAL: SUMO 0x0042cdc4
// GLOBAL: EDITOR 0x0042cdc4
extern const char g_gameAudioXmSignature[] = "Extended Module: ";

static __forceinline void GameAudioReadBlock(GameAudioOwnedBlock *block,
                                             void *output, SumoS32 byteCount) {
  InvokeGameAudioBlockTail((SumoS32)output, byteCount, block);
}

static __forceinline void GameAudioSeekBlock(GameAudioOwnedBlock *block,
                                             SumoS32 offset, SumoS32 origin) {
  InvokeGameAudioBlockHead(block, offset, origin);
}

static __forceinline SumoS32 GameAudioTellBlock(GameAudioOwnedBlock *block) {
  return ReleaseGameAudioOwnedBlock(block);
}

void UpdateTrackerVibrato(TrackerChannelState *channel);
void UpdateTrackerAutoVibrato(TrackerChannelState *channel,
                              GameAudioInstrument *instrument);
void UpdateTrackerEnvelope(TrackerChannelState *p_channel,
                           SumoS32 *p_pointIndex, SumoS32 *p_tick,
                           SumoU8 p_flags, SumoS32 p_pointCount,
                           TrackerEnvelopePoint *p_points, SumoU8 p_loopEnd,
                           SumoU8 p_loopStart, SumoU8 p_sustainPoint,
                           SumoS32 *p_output, SumoS32 *p_accumulator,
                           SumoU8 *p_finished, SumoS32 *p_slope,
                           SumoU8 p_dirtyMask);
void ResetTrackerChannelState(TrackerChannelState *channel,
                              GameAudioParsedSample *sample);
extern "C" void ApplyTrackerVolumeColumn(TrackerChannelState *channel,
                                         SumoU8 command);

static SumoS32 &TrackerS32(SumoU8 *state, SumoS32 offset) {
  return *(SumoS32 *)(state + offset);
}

static SumoU32 &TrackerU32(SumoU8 *state, SumoS32 offset) {
  return *(SumoU32 *)(state + offset);
}

static SumoU8 &TrackerU8(SumoU8 *state, SumoS32 offset) {
  return *(SumoU8 *)(state + offset);
}


// FUNCTION: SUMO 0x00417d73
// FUNCTION: EDITOR 0x00417d95
void UpdateTrackerMixerChannel(TrackerChannelState *channel, GameAudioParsedSample *sample, GameAudioParsedModule *module) {

  GameAudioMixerChannel *mixer = channel->mixer;
  SumoS32 mixerIndex;
  if (mixer != 0)
    mixerIndex = mixer->index;

  if (!(channel->period + channel->periodDelta))
    channel->dirtyFlags &= (SumoU8)~1;

  if (channel->dirtyFlags & 8) {
    mixer = &g_gameAudioChannelScratch[mixerIndex];
    if (mixer->sample != 0) {
      if (mixerIndex < 32)
        mixerIndex += 32;
      else
        mixerIndex -= 32;
      memcpy(&g_gameAudioChannelScratch[mixerIndex], mixer,
             sizeof(GameAudioMixerChannel));
      g_gameAudioChannelScratch[mixerIndex].index = mixerIndex;
      mixer->volume = mixer->actualVolume = 0;
      mixer->leftVolume = 0;
      mixer->rightVolume = 0;
      mixer = &g_gameAudioChannelScratch[mixerIndex];
      channel->mixer = mixer;
    }
    mixer->sample = sample;
    if (mixer->sampleOffset >= sample->loopStart + sample->loopLength)
      mixer->sampleOffset = 0;
    mixer->mixPosition = mixer->sampleOffset;
    mixer->mixPositionFraction = 0;
    mixer->speedDirection = 1;
    mixer->sampleOffset = 0;
    mixer->rampLeftVolume = 0;
    mixer->rampRightVolume = 0;
    mixer->rampCount = 0;
  }

  if (channel->dirtyFlags & 2) {
    SumoF32 finalVolume = (SumoF32)channel->volumeEnvelopeValue;
    finalVolume *= channel->volume + channel->volumeDelta;
    finalVolume *= channel->fadeoutVolume;
    finalVolume *= module->globalVolume;
    finalVolume *= g_trackerVolumeScale;
    SumoS32 volume = (SumoS32)finalVolume;
    if (mixer != 0) {
      mixer->volume = mixer->actualVolume = volume;
      mixer->leftVolume = volume * mixer->actualPanning / 255;
      mixer->rightVolume = volume * (255 - mixer->actualPanning) / 255;
    }
  }

  if (channel->dirtyFlags & 4) {
    SumoS32 pan =
        channel->panning + (channel->panningEnvelopeValue - 32) *
                               ((128 - abs(channel->panning - 128)) / 32);
    if (pan < 0)
      pan = 0;
    if (pan > 255)
      pan = 255;
    if (mixer != 0) {
      mixer->panning = mixer->actualPanning = pan;
      mixer->leftVolume = mixer->actualVolume * pan / 255;
      mixer->rightVolume = mixer->actualVolume * (255 - pan) / 255;
    }
  }

  if (channel->dirtyFlags & 1) {
    SumoS32 frequency;
    if ((module->frequencyMode & 1) != 0) {
      frequency = (SumoS32)(pow(g_textureHueSectorTwo,
                                (g_trackerLinearPeriodBase - channel->period +
                                 channel->periodDelta) *
                                    g_trackerLinearPeriodScale) *
                            g_trackerLinearBaseFrequency);
    } else {
      frequency = 14317056 / (channel->period + channel->periodDelta);
    }
    mixer->frequency = frequency;
    if (frequency < 100)
      frequency = 100;

    __asm {
      push eax
      push ebx
      push ecx
      push edx
      mov ecx, mixer
      mov ebx, g_gameAudioMixRate
      mov eax, frequency
      xor edx, edx
      div ebx
      mov [ecx]GameAudioMixerChannel.speedInteger, eax
      div ebx
      mov [ecx]GameAudioMixerChannel.speedFraction, eax
      pop edx
      pop ecx
      pop ebx
      pop eax
    }
  }

  if (channel->dirtyFlags & 0x20) {
    mixer->mixPositionFraction = 0;
    mixer->mixPosition = 0;
    mixer->sampleOffset = 0;
  }
}

// FUNCTION: SUMO 0x00418007
// FUNCTION: EDITOR 0x00418029
void ProcessGameAudioPatternRow(GameAudioParsedModule *module) {
  module->pendingOrder = -1;
  module->pendingRow = -1;
  SumoU8 *event =
      (SumoU8 *)module->patterns[module->patternOrder[module->orderIndex]]
          .events +
      module->currentRow * module->channelCount * 5;
  if (event == 0)
    return;

  for (SumoS32 index = 0; index < module->channelCount; ++index, event += 5) {
    TrackerChannelState *channel =
        ((TrackerChannelState *)g_gameAudioChannelStates) + index;
    SumoU8 high = event[4] >> 4;
    SumoU8 low = event[4] & 15;
    bool tonePortamento = event[3] == 3 || event[3] == 5;
    if (event[1] != 0 && !tonePortamento)
      channel->instrumentNumber = event[1] - 1;
    if (event[0] != 0 && event[0] != 0xff && !tonePortamento)
      channel->note = event[0] - 1;

    GameAudioInstrument *instrument;
    GameAudioParsedSample *sample;
    if (channel->instrumentNumber >= module->instrumentCount) {
      instrument = &g_gameAudioEmptyInstrument;
      sample = &g_gameAudioEmptySample;
      g_gameAudioEmptySample.data = 0;
    } else {
      instrument = module->instruments + channel->instrumentNumber;
      SumoU8 sampleIndex = instrument->sampleMap[channel->note];
      if (sampleIndex >= 16)
        sample = &g_gameAudioEmptySample;
      else
        sample = instrument->samples[sampleIndex];
      if (!tonePortamento)
        channel->sample = sample;
    }

    SumoS32 previousVolume = channel->volume;
    SumoS32 previousPeriod = channel->period;
    SumoS32 previousPan = channel->panning;
    if (channel->recentEffect == 7 && event[3] != 7)
      channel->volume += channel->volumeDelta;
    channel->recentEffect = event[3];
    channel->volumeDelta = 0;
    channel->dirtyFlags = 0;

    if (event[0] != 0 && event[0] != 0xff) {
      SumoU8 adjustedNote = event[0] + sample->relativeNote - 1;
      channel->realNote = adjustedNote;
      if ((module->frequencyMode & 1) != 0)
        channel->targetPeriod = 7680 - 64 * adjustedNote - sample->fineTune / 2;
      if (!tonePortamento)
        channel->period = channel->targetPeriod;
      channel->dirtyFlags = 8;
    }
    channel->periodDelta = 0;
    channel->dirtyFlags |= 3;

    if (event[1] != 0)
      ResetTrackerChannelState(channel, sample);
    if (event[2] != 0)
      ApplyTrackerVolumeColumn(channel, event[2]);
    if (event[0] == 0xff || event[3] == 20)
      channel->keyOff = 1;

    if ((instrument->volumeEnvelopeType & 1) != 0) {
      if (channel->volumeEnvelopeStopped == 0) {
        UpdateTrackerEnvelope(
            channel, &channel->volumeEnvelopePoint,
            &channel->volumeEnvelopeTick, instrument->volumeEnvelopeType,
            instrument->volumeEnvelopePointCount,
            (TrackerEnvelopePoint *)instrument->volumeEnvelope,
            instrument->volumeLoopEnd, instrument->volumeLoopStart,
            instrument->volumeSustainPoint, &channel->volumeEnvelopeValue,
            &channel->volumeEnvelopeAccumulator,
            (SumoU8 *)&channel->volumeEnvelopeStopped,
            &channel->volumeEnvelopeDelta, 2);
      }
    } else if (channel->keyOff != 0) {
      channel->volumeEnvelopeValue = 0;
    }

    if ((instrument->panningEnvelopeType & 1) != 0 &&
        channel->panningEnvelopeStopped == 0) {
      UpdateTrackerEnvelope(
          channel, &channel->panningEnvelopePoint,
          &channel->panningEnvelopeTick, instrument->panningEnvelopeType,
          instrument->panningEnvelopePointCount,
          (TrackerEnvelopePoint *)instrument->panningEnvelope,
          instrument->panningLoopEnd, instrument->panningLoopStart,
          instrument->panningSustainPoint, &channel->panningEnvelopeValue,
          &channel->panningEnvelopeAccumulator,
          (SumoU8 *)&channel->panningEnvelopeStopped,
          &channel->panningEnvelopeDelta, 4);
    }

    if (channel->keyOff != 0) {
      channel->fadeoutVolume -= instrument->volumeFadeout;
      if (channel->fadeoutVolume < 0)
        channel->fadeoutVolume = 0;
      channel->dirtyFlags |= 2;
    }

    switch (event[3]) {
    case 0:
      break;
    case 1:
      if (event[4] != 0)
        channel->portamentoUp = event[4];
      break;
    case 2:
      if (event[4] != 0)
        channel->portamentoDown = event[4];
      break;
    case 3:
      if (event[4] != 0)
        channel->portamentoSpeed = event[4];
      channel->dirtyFlags &= 0xf6;
      channel->portamentoTarget = channel->targetPeriod;
      break;
    case 4:
      if (high != 0)
        channel->vibratoSpeed = high;
      if (low != 0)
        channel->vibratoDepth = low;
      UpdateTrackerVibrato(channel);
      break;
    case 9:
      if (event[4] != 0)
        channel->sampleOffset = event[4];
      if (channel->mixer == 0)
        break;
      {
        SumoU32 offset = channel->sampleOffset << 8;
        if (offset >= sample->loopStart + sample->loopLength) {
          channel->dirtyFlags &= (SumoU8)~8;
          channel->dirtyFlags |= 0x20;
        } else {
          channel->mixer->sampleOffset = offset;
        }
      }
      break;
    case 14: {
      switch (high) {
      case 9:
      case 12:
      case 0:
      case 15:
      case 3:
        break;
      case 2:
        if (low != 0)
          channel->finePortamentoDown = low;
        channel->period += channel->finePortamentoDown << 2;
        break;
      case 13:
        channel->volume = previousVolume;
        channel->period = previousPeriod;
        channel->panning = previousPan;
        channel->dirtyFlags &= (SumoU8)~1;
        channel->dirtyFlags &= (SumoU8)~2;
        channel->dirtyFlags &= (SumoU8)~4;
        channel->dirtyFlags &= (SumoU8)~8;
        break;
      }
      break;
    }
    case 15:
      if (event[4] < 0x20)
        module->tempo = event[4];
      else
        ConfigureGameAudioTiming((GameAudioTiming *)module, event[4]);
      break;
    case 27:
      if (event[4] != 0) {
        channel->retriggerVolumeMode = high;
        channel->retriggerTickCount = low;
      }
      break;
    }

    UpdateTrackerAutoVibrato(channel, instrument);
    UpdateTrackerMixerChannel(channel, sample, module);
  }
}

// FUNCTION: SUMO 0x00418424
// FUNCTION: EDITOR 0x00418446
void ProcessGameAudioPatternTick(GameAudioParsedModule *module) {
  TrackerPatternEvent *current =
      (TrackerPatternEvent *)module
          ->patterns[module->patternOrder[module->orderIndex]]
          .events +
      module->currentRow * module->channelCount;
  if (current == 0)
    return;

  for (SumoS32 index = 0; index < module->channelCount; ++index, ++current) {
    TrackerChannelState *channel =
        ((TrackerChannelState *)g_gameAudioChannelStates) + index;
    GameAudioInstrument *instrument;
    GameAudioParsedSample *sample;
    SumoU8 effect;
    SumoU8 high;
    SumoU8 low;

    if (channel->instrumentNumber >= module->instrumentCount) {
      instrument = &g_gameAudioEmptyInstrument;
      sample = &g_gameAudioEmptySample;
      g_gameAudioEmptySample.data = 0;
    } else {
      instrument = module->instruments + channel->instrumentNumber;
      if (instrument->sampleMap[channel->note] >= 16)
        sample = &g_gameAudioEmptySample;
      else
        sample = instrument->samples[instrument->sampleMap[channel->note]];
      if (sample == 0)
        sample = &g_gameAudioEmptySample;
    }

    effect = current->effect;
    high = current->eparam >> 4;
    low = current->eparam & 15;

    channel->volumeDelta = 0;
    channel->periodDelta = 0;
    channel->dirtyFlags = 0;
    if ((instrument->volumeEnvelopeType & 1) != 0 &&
        channel->volumeEnvelopeStopped == 0) {
      UpdateTrackerEnvelope(
          channel, &channel->volumeEnvelopePoint, &channel->volumeEnvelopeTick,
          instrument->volumeEnvelopeType, instrument->volumeEnvelopePointCount,
          (TrackerEnvelopePoint *)instrument->volumeEnvelope,
          instrument->volumeLoopEnd, instrument->volumeLoopStart,
          instrument->volumeSustainPoint, &channel->volumeEnvelopeValue,
          &channel->volumeEnvelopeAccumulator,
          (SumoU8 *)&channel->volumeEnvelopeStopped,
          &channel->volumeEnvelopeDelta, 2);
    }
    if ((instrument->panningEnvelopeType & 1) != 0 &&
        channel->panningEnvelopeStopped == 0) {
      UpdateTrackerEnvelope(
          channel, &channel->panningEnvelopePoint,
          &channel->panningEnvelopeTick, instrument->panningEnvelopeType,
          instrument->panningEnvelopePointCount,
          (TrackerEnvelopePoint *)instrument->panningEnvelope,
          instrument->panningLoopEnd, instrument->panningLoopStart,
          instrument->panningSustainPoint, &channel->panningEnvelopeValue,
          &channel->panningEnvelopeAccumulator,
          (SumoU8 *)&channel->panningEnvelopeStopped,
          &channel->panningEnvelopeDelta, 4);
    }
    if (channel->keyOff != 0) {
      channel->fadeoutVolume -= instrument->volumeFadeout;
      if (channel->fadeoutVolume < 0)
        channel->fadeoutVolume = 0;
      channel->dirtyFlags |= 2;
    }

    switch (current->volume >> 4) {
    case 6:
      channel->volume -= current->volume & 15;
      if (channel->volume < 0)
        channel->volume = 0;
      channel->dirtyFlags |= 2;
      break;
    case 7:
      channel->volume += current->volume & 15;
      if (channel->volume > 64)
        channel->volume = 64;
      channel->dirtyFlags |= 2;
      break;
    case 11:
      channel->vibratoDepth = current->volume & 15;
      UpdateTrackerVibrato(channel);
      channel->vibratoPosition += channel->vibratoSpeed;
      if (channel->vibratoPosition > 31)
        channel->vibratoPosition -= 64;
      break;
    case 13:
      channel->panning -= current->volume & 15;
      channel->dirtyFlags |= 4;
      break;
    case 14:
      channel->panning += current->volume & 15;
      channel->dirtyFlags |= 4;
      break;
    case 15:
      UpdateGameAudioRamp((GameAudioRamp *)channel);
      break;
    }

    switch (effect) {
    case 0:
      if (current->eparam > 0) {
        switch (module->currentTick % 3) {
        case 1:
          if ((module->frequencyMode & 1) != 0)
            channel->periodDelta = high << 6;
          break;
        case 2:
          if ((module->frequencyMode & 1) != 0)
            channel->periodDelta = low << 6;
          break;
        }
        channel->dirtyFlags |= 1;
      }
      break;
    case 1:
      channel->periodDelta = 0;
      channel->period -= channel->portamentoUp << 2;
      if (channel->period < 56)
        channel->period = 56;
      channel->dirtyFlags |= 1;
      break;
    case 2:
      channel->periodDelta = 0;
      channel->period += channel->portamentoDown << 2;
      channel->dirtyFlags |= 1;
      break;
    case 3:
      channel->periodDelta = 0;
      UpdateGameAudioRamp((GameAudioRamp *)channel);
      break;
    case 4:
      UpdateTrackerVibrato(channel);
      channel->vibratoPosition += channel->vibratoSpeed;
      if (channel->vibratoPosition > 31)
        channel->vibratoPosition -= 64;
      break;
    case 14: {
      switch (high) {
      case 12:
        if (module->currentTick == low) {
          channel->volume = 0;
          channel->dirtyFlags |= 2;
        }
        break;
      case 13:
        if (module->currentTick == low) {
          ResetTrackerChannelState(channel, sample);
          channel->period = channel->targetPeriod;
          channel->dirtyFlags |= 1;
          if (current->volume != 0)
            ApplyTrackerVolumeColumn(channel, current->volume);
          channel->dirtyFlags |= 8;
        } else {
          channel->dirtyFlags &= (SumoU8)~2;
          channel->dirtyFlags &= (SumoU8)~1;
          channel->dirtyFlags &= (SumoU8)~4;
          channel->dirtyFlags &= (SumoU8)~8;
        }
        break;
      }
      break;
    }
    case 27:
      if (channel->retriggerTickCount == 0)
        break;
      if (module->currentTick % channel->retriggerTickCount == 0) {
        if (channel->retriggerVolumeMode != 0) {
          switch (channel->retriggerVolumeMode) {
          case 1:
            --channel->volume;
            break;
          case 2:
            channel->volume -= 2;
            break;
          case 3:
            channel->volume -= 4;
            break;
          case 4:
            channel->volume -= 8;
            break;
          case 5:
            channel->volume -= 16;
            break;
          case 6:
            channel->volume = channel->volume * 2 / 3;
            break;
          case 7:
            channel->volume >>= 1;
            break;
          case 8:
            break;
          case 9:
            ++channel->volume;
            break;
          case 10:
            channel->volume += 2;
            break;
          case 11:
            channel->volume += 4;
            break;
          case 12:
            channel->volume += 8;
            break;
          case 13:
            channel->volume += 16;
            break;
          case 14:
            channel->volume = channel->volume * 3 / 2;
            break;
          case 15:
            channel->volume <<= 1;
            break;
          }
          if (channel->volume > 64)
            channel->volume = 64;
          if (channel->volume < 0)
            channel->volume = 0;
          channel->dirtyFlags |= 2;
        }
        channel->dirtyFlags |= 8;
      }
      break;
    }

    UpdateTrackerAutoVibrato(channel, instrument);
    UpdateTrackerMixerChannel(channel, sample, module);
  }
}

// FUNCTION: SUMO 0x004188a5
// FUNCTION: EDITOR 0x004188c7
void GameAudioParsedTick(GameAudioParsedModule *module) {
  if (module->currentTick == 0) {
    if (module->pendingOrder >= 0)
      module->orderIndex = module->pendingOrder;
    if (module->pendingRow >= 0)
      module->currentRow = module->pendingRow;
    ProcessGameAudioPatternRow(module);
    if (module->pendingRow == -1) {
      module->pendingRow = module->currentRow + 1;
      if (module->pendingRow >=
          (SumoS32)module->patterns[module->patternOrder[module->orderIndex]]
              .rowCount) {
        module->pendingOrder = module->orderIndex + 1;
        if (module->pendingOrder >= module->songLength)
          module->pendingOrder = module->restartPosition;
        module->pendingRow = 0;
      }
    }
  } else {
    ProcessGameAudioPatternTick(module);
  }

  ++module->currentTick;
  if (module->currentTick >= module->tempo + module->rowDelay) {
    module->rowDelay = 0;
    module->currentTick -= module->tempo;
  }
}


// FUNCTION: SUMO 0x00419001
// FUNCTION: EDITOR 0x00419023
extern "C" void ConfigureGameAudioStreamCallbacks( GameAudioOpenCallback openCallback, GameAudioCloseCallback closeCallback, GameAudioIoCallback readCallback, GameAudioIoCallback seekCallback, GameAudioTellCallback tellCallback) {

  if (openCallback != 0 && closeCallback != 0 && readCallback != 0 &&
      seekCallback != 0 && tellCallback != 0) {
    g_gameAudioCreateValue = openCallback;
    g_gameAudioDestroyValue = closeCallback;
    g_gameAudioInvokeTail = readCallback;
    g_gameAudioInvokeHead = seekCallback;
    g_gameAudioReleaseCallback = tellCallback;
  } else {
    g_gameAudioCreateValue = 0;
    g_gameAudioDestroyValue = 0;
    g_gameAudioInvokeTail = 0;
    g_gameAudioInvokeHead = 0;
    g_gameAudioReleaseCallback = 0;
  }
}


// FUNCTION: SUMO 0x0041906e
// FUNCTION: EDITOR 0x00419090
GameAudioOwnedBlock *CreateGameAudioOwnedBlock(SumoS32 source, char flag, SumoS32 userValue) {

  GameAudioOwnedBlock *block =
      (GameAudioOwnedBlock *)calloc(sizeof(GameAudioOwnedBlock), 1);
  block->flag = flag;
  block->userValue = userValue;
  block->releaseValue = g_gameAudioCreateValue(source);
  if (block->releaseValue == 0) {
    free(block);
    return 0;
  }
  return block;
}

// FUNCTION: SUMO 0x004190aa
// FUNCTION: EDITOR 0x004190cc
void DestroyGameAudioOwnedBlock(GameAudioOwnedBlock *block) {
  if (block != 0) {
    g_gameAudioDestroyValue(block->releaseValue);
    free(block);
  }
}


// FUNCTION: SUMO 0x004190c6
// FUNCTION: EDITOR 0x004190e8
SumoS32 InvokeGameAudioBlockTail(SumoS32 first, SumoS32 second, GameAudioOwnedBlock *block) {

  if (block == 0) {
    return 0;
  }
  return g_gameAudioInvokeTail(first, second, block->releaseValue);
}


// FUNCTION: SUMO 0x004190e4
// FUNCTION: EDITOR 0x00419106
SumoS32 InvokeGameAudioBlockHead(GameAudioOwnedBlock *block, SumoS32 second, SumoS32 third) {

  SumoS32 result = (SumoS32)block;
  if (block != 0) {
    result = g_gameAudioInvokeHead(block->releaseValue, second, third);
  }
  return result;
}

// FUNCTION: SUMO 0x00419101
// FUNCTION: EDITOR 0x00419123
SumoS32 ReleaseGameAudioOwnedBlock(GameAudioOwnedBlock *block) {
  if (block == 0) {
    return 0;
  }
  return g_gameAudioReleaseCallback(block->releaseValue);
}

// FUNCTION: SUMO 0x00419140
// FUNCTION: EDITOR 0x00419160
__declspec(naked) void *InitializeTextureGenerator() {
  __asm {
    sub esp, 0ch
    push ebp
    push esi
    push edi
    push 10000h
    call malloc
    add esp, 4
    mov dword ptr [g_textureColorMap], eax
    xor ebp, ebp
initializeColorMapDarkRow:
    mov edi, ebp
    xor ecx, ecx
    shl edi, 8
    xor esi, esi
initializeColorMapDarkPixel:
    mov eax, 2040811h
    mul esi
    mov eax, esi
    add esi, ebp
    sub eax, edx
    shr eax, 1
    add eax, edx
    mov edx, dword ptr [g_textureColorMap]
    add edx, edi
    shr eax, 6
    mov byte ptr [edx + ecx], al
    inc ecx
    cmp ecx, 100h
    jl initializeColorMapDarkPixel
    inc ebp
    cmp ebp, 80h
    jl initializeColorMapDarkRow
    xor ebp, ebp
    mov edi, 8000h
initializeColorMapLightRow:
    xor esi, esi
    mov dword ptr [esp + 10h], ebp
    mov dword ptr [esp + 14h], esi
    mov dword ptr [esp + 0ch], esi
    fild qword ptr [esp + 10h]
    fmul qword ptr [g_textureColorMapRowScale]
    fsubr qword ptr [g_textureOne]
initializeColorMapLightPixel:
    fild dword ptr [esp + 0ch]
    fsubr qword ptr [g_textureByteMaximum]
    fmul st, st(1)
    fsubr qword ptr [g_textureByteMaximum]
    call __ftol
    mov ecx, dword ptr [g_textureColorMap]
    inc esi
    cmp esi, 100h
    mov dword ptr [esp + 0ch], esi
    lea edx, dword ptr [edi + ecx]
    mov byte ptr [edx + esi - 1], al
    jl initializeColorMapLightPixel
    add edi, 100h
    inc ebp
    cmp edi, 10000h
    fstp st
    jl initializeColorMapLightRow
    push 40000h
    call malloc
    push 40000h
    mov dword ptr [g_textureWorkBuffer], eax
    call malloc
    push 40000h
    mov dword ptr [g_textureChannelSwapBuffer], eax
    call malloc
    push 40000h
    mov dword ptr [g_textureLayers], eax
    call malloc
    push 40000h
    mov dword ptr [g_textureLayers + 4], eax
    call malloc
    push 40000h
    mov dword ptr [g_textureLayers + 8], eax
    call malloc
    push 40000h
    mov dword ptr [g_textureLayers + 0ch], eax
    call malloc
    push 10000h
    mov dword ptr [g_textureIoBuffer], eax
    call malloc
    add esp, 20h
    mov dword ptr [g_textureByteBuffer], eax
    pop edi
    pop esi
    pop ebp
    add esp, 0ch
    ret
  }
}

// FUNCTION: SUMO 0x00419280
// FUNCTION: EDITOR 0x004192a0
__declspec(naked) SumoS8 ExportTextureTga(SumoU32 *texture) {
  __asm {
    sub esp, 20h
    mov eax, dword ptr [g_textureTgaHeader]
    push ebx
    push ebp
    mov ecx, dword ptr [g_textureTgaHeader + 4]
    mov edx, dword ptr [g_textureTgaHeader + 8]
    push esi
    push edi
    push 0
    push 80h
    push 2
    push 0
    mov dword ptr [esp + 30h], eax
    mov al, byte ptr [g_textureTgaHeader + 0ch]
    push 0
    mov ebx, 100h
    push 40000000h
    push offset g_textureExportFilename
    mov dword ptr [esp + 30h], ebx
    mov dword ptr [esp + 38h], 18h
    mov dword ptr [esp + 40h], ecx
    mov dword ptr [esp + 44h], edx
    mov byte ptr [esp + 48h], al
    call dword ptr [CreateFileA]
    mov esi, dword ptr [WriteFile]
    lea ecx, dword ptr [esp + 10h]
    push 0
    push ecx
    lea edx, dword ptr [esp + 28h]
    mov edi, eax
    push 0ch
    push edx
    push edi
    call esi
    lea eax, dword ptr [esp + 10h]
    push 0
    push eax
    lea ecx, dword ptr [esp + 1ch]
    push 2
    push ecx
    push edi
    call esi
    lea edx, dword ptr [esp + 10h]
    push 0
    push edx
    lea eax, dword ptr [esp + 1ch]
    push 2
    push eax
    push edi
    call esi
    lea ecx, dword ptr [esp + 10h]
    push 0
    push ecx
    lea edx, dword ptr [esp + 24h]
    push 2
    push edx
    push edi
    call esi
    mov ecx, dword ptr [esp + 34h]
    xor eax, eax
    mov dword ptr [esp + 18h], ebx
    lea esi, dword ptr [ecx + 3fc00h]
    mov dword ptr [esp + 34h], esi
exportTgaNextRow:
    mov ebp, 100h
exportTgaNextPixel:
    mov edx, dword ptr [g_textureIoBuffer]
    mov ecx, dword ptr [esi]
    add esi, 4
    mov byte ptr [edx + eax], cl
    mov ebx, dword ptr [g_textureIoBuffer]
    mov edx, ecx
    inc eax
    sar edx, 8
    mov byte ptr [ebx + eax], dl
    mov edx, dword ptr [g_textureIoBuffer]
    inc eax
    sar ecx, 10h
    mov byte ptr [edx + eax], cl
    inc eax
    dec ebp
    jne exportTgaNextPixel
    mov esi, dword ptr [esp + 34h]
    mov ecx, dword ptr [esp + 18h]
    sub esi, 400h
    dec ecx
    mov dword ptr [esp + 34h], esi
    mov dword ptr [esp + 18h], ecx
    jne exportTgaNextRow
    mov ecx, dword ptr [g_textureIoBuffer]
    lea eax, dword ptr [esp + 10h]
    push 0
    push eax
    push 30000h
    push ecx
    push edi
    call dword ptr [WriteFile]
    push edi
    call dword ptr [CloseHandle]
    mov al, byte ptr [g_textureExportFilename + 7]
    pop edi
    inc al
    pop esi
    pop ebp
    cmp al, 3ah
    mov byte ptr [g_textureExportFilename + 7], al
    pop ebx
    jne exportTgaDone
    mov al, byte ptr [g_textureExportFilename + 6]
    mov byte ptr [g_textureExportFilename + 7], 30h
    inc al
    mov byte ptr [g_textureExportFilename + 6], al
exportTgaDone:
    add esp, 20h
    ret
  }
}


// FUNCTION: SUMO 0x004193e0
// FUNCTION: EDITOR 0x00419400
__declspec(naked) SumoS32 ImportTextureTga(const char *filename, SumoU32 *texture) {

  __asm {
    push ecx
    mov eax, dword ptr [esp + 8]
    push esi
    push 0
    push 80h
    push 3
    push 0
    push 0
    push 80000000h
    push eax
    call dword ptr [CreateFileA]
    mov esi, eax
    cmp esi, -1
    jne importTgaOpened
    xor eax, eax
    pop esi
    pop ecx
    ret
importTgaOpened:
    push ebx
    push ebp
    push edi
    push 0
    push 0
    push 12h
    push esi
    call dword ptr [SetFilePointer]
    mov edx, dword ptr [g_textureIoBuffer]
    lea ecx, dword ptr [esp + 10h]
    push 0
    push ecx
    push 30000h
    push edx
    push esi
    call dword ptr [ReadFile]
    push esi
    call dword ptr [CloseHandle]
    mov ecx, dword ptr [esp + 1ch]
    xor eax, eax
    mov dword ptr [esp + 18h], 100h
    lea ebp, dword ptr [ecx + 3fc00h]
importTgaNextRow:
    mov esi, ebp
    mov edi, 100h
importTgaNextPixel:
    mov ecx, dword ptr [g_textureIoBuffer]
    inc eax
    xor ebx, ebx
    add esi, 4
    mov dl, byte ptr [ecx + eax - 1]
    inc eax
    mov byte ptr [esp + 1ch], dl
    mov dl, byte ptr [ecx + eax - 1]
    mov cl, byte ptr [ecx + eax]
    inc eax
    mov bh, cl
    mov ecx, dword ptr [esp + 1ch]
    mov bl, dl
    and ecx, 0ffh
    shl ebx, 8
    or ebx, ecx
    dec edi
    mov dword ptr [esi - 4], ebx
    jne importTgaNextPixel
    mov ecx, dword ptr [esp + 18h]
    sub ebp, 400h
    dec ecx
    mov dword ptr [esp + 18h], ecx
    jne importTgaNextRow
    mov al, byte ptr [g_textureExportFilename + 7]
    pop edi
    inc al
    pop ebp
    cmp al, 3ah
    mov byte ptr [g_textureExportFilename + 7], al
    pop ebx
    jne importTgaDone
    mov al, byte ptr [g_textureExportFilename + 6]
    mov byte ptr [g_textureExportFilename + 7], 30h
    inc al
    mov byte ptr [g_textureExportFilename + 6], al
importTgaDone:
    mov eax, 1
    pop esi
    pop ecx
    ret
  }
}

#pragma optimize("s", off)
#pragma optimize("t", on)
// FUNCTION: SUMO 0x004194d0
// FUNCTION: EDITOR 0x004194f0
void ShutdownTextureGenerator() {
  if (g_textureChannelSwapBuffer != NULL) {
    free(g_textureChannelSwapBuffer);
  }
  if (g_textureWorkBuffer != NULL) {
    free(g_textureWorkBuffer);
  }
  if (g_textureLayers[0] != NULL) {
    free(g_textureLayers[0]);
  }
  if (g_textureLayers[1] != NULL) {
    free(g_textureLayers[1]);
  }
  if (g_textureLayers[2] != NULL) {
    free(g_textureLayers[2]);
  }
  if (g_textureLayers[3] != NULL) {
    free(g_textureLayers[3]);
  }
  if (g_textureIoBuffer != NULL) {
    free(g_textureIoBuffer);
  }
  if (g_textureByteBuffer != NULL) {
    free(g_textureByteBuffer);
  }
}
#pragma optimize("t", off)
#pragma optimize("s", on)

extern const double g_textureSize;

// GLOBAL: SUMO 0x0042ce00
// GLOBAL: EDITOR 0x0042ce00
const SumoF32 g_textureWrapSizeFloat = 256.0f;

// GLOBAL: SUMO 0x00d0fad0
// GLOBAL: EDITOR 0x00d102e8
SumoU8 g_textureUseMmxSampler;


// FUNCTION: SUMO 0x00419560
// FUNCTION: EDITOR 0x00419580
__declspec(naked) SumoU32 SampleTexturePixelX87(SumoU32 *texture, SumoF32 x, SumoF32 y) {

  __asm {
    sub esp, 0ch
    fld dword ptr [esp + 14h]
    _emit 0d9h
    _emit 054h
    _emit 024h
    _emit 000h
    fld dword ptr [esp + 14h]
    fcomp dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 1
    jz textureX87XNonnegative
textureX87WrapXUp:
    fadd dword ptr [g_textureWrapSizeFloat]
    fcom dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 1
    jnz textureX87WrapXUp
    _emit 0d9h
    _emit 054h
    _emit 024h
    _emit 000h
textureX87XNonnegative:
    fcom qword ptr [g_textureSize]
    fnstsw ax
    test ah, 1
    jnz textureX87YBegin
textureX87WrapXDown:
    fsub dword ptr [g_textureWrapSizeFloat]
    fcom qword ptr [g_textureSize]
    fnstsw ax
    test ah, 1
    jz textureX87WrapXDown
    _emit 0d9h
    _emit 054h
    _emit 024h
    _emit 000h
textureX87YBegin:
    fld dword ptr [esp + 18h]
    fst dword ptr [esp + 14h]
    fld dword ptr [esp + 18h]
    fcomp dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 1
    jz textureX87YNonnegative
textureX87WrapYUp:
    fadd dword ptr [g_textureWrapSizeFloat]
    fcom dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 1
    jnz textureX87WrapYUp
    fst dword ptr [esp + 14h]
textureX87YNonnegative:
    fcom qword ptr [g_textureSize]
    fnstsw ax
    test ah, 1
    jnz textureX87DiscardWrappedY
textureX87WrapYDown:
    fsub dword ptr [g_textureWrapSizeFloat]
    fcom qword ptr [g_textureSize]
    fnstsw ax
    test ah, 1
    jz textureX87WrapYDown
    fstp dword ptr [esp + 14h]
textureX87Wrapped:
    push ebx
    push esi
    push edi
    sub esp, 8
    fstp qword ptr [esp]
    call _floor
    call __ftol
    fld dword ptr [esp + 28h]
    mov ebx, eax
    fstp qword ptr [esp]
    mov dword ptr [esp + 2ch], ebx
    call _floor
    add esp, 8
    call __ftol
    lea esi, dword ptr [eax + 1]
    mov edi, dword ptr [esp + 1ch]
    shl esi, 8
    mov edx, ebx
    xor ecx, ecx
    and esi, 0ff00h
    and edx, 0ffh
    fild dword ptr [esp + 24h]
    mov ch, al
    inc ebx
    mov dword ptr [esp + 10h], eax
    and ebx, 0ffh
    lea eax, dword ptr [edx + ecx]
    add ecx, ebx
    fsubr dword ptr [esp + 0ch]
    mov eax, dword ptr [edi + eax * 4]
    mov ecx, dword ptr [edi + ecx * 4]
    add edx, esi
    add ebx, esi
    fild dword ptr [esp + 10h]
    mov edx, dword ptr [edi + edx * 4]
    mov esi, dword ptr [edi + ebx * 4]
    mov edi, eax
    mov ebx, ecx
    fsubr dword ptr [esp + 20h]
    shr edi, 10h
    and edi, 0ffh
    mov dword ptr [esp + 10h], edi
    xor edi, edi
    shr ebx, 10h
    mov dword ptr [esp + 14h], edi
    and ebx, 0ffh
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], ebx
    mov dword ptr [esp + 14h], edi
    fild qword ptr [esp + 10h]
    mov ebx, eax
    mov dword ptr [esp + 14h], edi
    shr ebx, 8
    fsub st, st(1)
    and ebx, 0ffh
    and eax, 0ffh
    mov dword ptr [esp + 10h], ebx
    mov ebx, ecx
    fmul st, st(3)
    shr ebx, 8
    and ebx, 0ffh
    and ecx, 0ffh
    faddp st(1), st
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], ebx
    mov dword ptr [esp + 14h], edi
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 14h], edi
    fsub st, st(1)
    fmul st, st(4)
    fadd st, st(1)
    fstp dword ptr [esp + 24h]
    fstp st
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], ecx
    mov dword ptr [esp + 14h], edi
    fild qword ptr [esp + 10h]
    mov eax, edx
    mov ecx, edx
    shr eax, 10h
    fsub st, st(1)
    and eax, 0ffh
    mov dword ptr [esp + 14h], edi
    shr ecx, 8
    fmul st, st(4)
    mov dword ptr [esp + 10h], eax
    and ecx, 0ffh
    and edx, 0ffh
    fadd st, st(1)
    fstp dword ptr [esp + 0ch]
    fstp st
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], ecx
    mov dword ptr [esp + 14h], edi
    fild qword ptr [esp + 10h]
    mov dword ptr [esp + 10h], edx
    mov dword ptr [esp + 14h], edi
    mov edx, esi
    fstp dword ptr [esp + 20h]
    fild qword ptr [esp + 10h]
    shr edx, 10h
    and edx, 0ffh
    mov dword ptr [esp + 14h], edi
    fstp dword ptr [esp + 1ch]
    mov dword ptr [esp + 10h], edx
    fild qword ptr [esp + 10h]
    fsub st, st(1)
    fmul st, st(4)
    fadd st, st(1)
    fsub st, st(2)
    fmul st, st(3)
    fadd st, st(2)
    call __ftol
    mov ebx, eax
    mov eax, esi
    shr eax, 8
    fstp st
    and eax, 0ffh
    mov dword ptr [esp + 14h], edi
    fstp st
    mov dword ptr [esp + 10h], eax
    fild qword ptr [esp + 10h]
    shl ebx, 8
    fsub dword ptr [esp + 20h]
    fmul st, st(2)
    fadd dword ptr [esp + 20h]
    fsub dword ptr [esp + 24h]
    fmul st, st(1)
    fadd dword ptr [esp + 24h]
    call __ftol
    and esi, 0ffh
    mov dword ptr [esp + 14h], edi
    mov dword ptr [esp + 10h], esi
    or ebx, eax
    fild qword ptr [esp + 10h]
    shl ebx, 8
    fsub dword ptr [esp + 1ch]
    fmul st, st(2)
    fadd dword ptr [esp + 1ch]
    fsub dword ptr [esp + 0ch]
    fmul st, st(1)
    fadd dword ptr [esp + 0ch]
    call __ftol
    fstp st
    pop edi
    or eax, ebx
    pop esi
    pop ebx
    fstp st
    add esp, 0ch
    ret
textureX87DiscardWrappedY:
    fstp st
    jmp textureX87Wrapped
  }
}


// FUNCTION: SUMO 0x00419820
// FUNCTION: EDITOR 0x00419840
__declspec(naked) SumoU32 SampleTexturePixelMmx(SumoU32 *texture, SumoF32 x, SumoF32 y) {

  __asm {
    push ebp
    mov ebp, esp
    sub esp, 1ch
    push ebx
    push esi
    mov dword ptr [ebp - 4], 43800000h
    mov esi, dword ptr [ebp + 8]
    fld dword ptr [ebp + 10h]
    fld dword ptr [ebp + 0ch]
    fmul dword ptr [ebp - 4]
    fistp dword ptr [ebp - 1ch]
    fmul dword ptr [ebp - 4]
    mov eax, dword ptr [ebp - 1ch]
    fistp dword ptr [ebp - 14h]
    mov ecx, dword ptr [ebp - 14h]
    push eax
    push ecx
    and eax, 0ffh
    and ecx, 0ffh
    mov ebx, eax
    mov edx, ecx
    shl eax, 8
    shl ecx, 8
    add eax, ebx
    add ecx, edx
    shl eax, 8
    shl ecx, 8
    add eax, ebx
    add ecx, edx
    mov edx, 0ff00h
    mov dword ptr [ebp - 1ch], eax
    mov dword ptr [ebp - 14h], ecx
    pop ebx
    pop eax
    and ebx, edx
    pxor mm0, mm0
    and eax, edx
    shr eax, 8
    mov ecx, eax
    add eax, ebx
    movd mm4, dword ptr [esi + eax * 4]
    mov eax, ecx
    inc eax
    punpcklbw mm4, mm0
    and eax, 0ffh
    push eax
    add eax, ebx
    movd mm5, dword ptr [esi + eax * 4]
    pop eax
    punpcklbw mm5, mm0
    add ebx, 100h
    and ebx, edx
    add eax, ebx
    movd mm7, dword ptr [esi + eax * 4]
    mov eax, ecx
    punpcklbw mm7, mm0
    add eax, ebx
    movd mm6, dword ptr [esi + eax * 4]
    punpcklbw mm6, mm0
    pxor mm3, mm3
    movd mm0, dword ptr [ebp - 1ch]
    movd mm1, dword ptr [ebp - 14h]
    pcmpeqw mm2, mm2
    punpcklbw mm0, mm3
    punpcklbw mm2, mm3
    punpcklbw mm1, mm3
    movq mm3, mm2
    psubw mm2, mm0
    psubw mm3, mm1
    pmullw mm7, mm0
    psrlw mm7, 8
    pmullw mm7, mm1
    pmullw mm6, mm1
    psrlw mm6, 8
    pmullw mm6, mm2
    paddw mm7, mm6
    pmullw mm5, mm0
    psrlw mm5, 8
    pmullw mm5, mm3
    paddw mm7, mm5
    pxor mm0, mm0
    pmullw mm4, mm2
    psrlw mm4, 8
    pmullw mm4, mm3
    paddw mm7, mm4
    psrlw mm7, 8
    packuswb mm7, mm0
    movd dword ptr [ebp - 0ch], mm7
    emms
    mov eax, dword ptr [ebp - 0ch]
    pop esi
    pop ebx
    mov esp, ebp
    pop ebp
    ret
  }
}


// FUNCTION: SUMO 0x00419930
// FUNCTION: EDITOR 0x00419950
__declspec(naked) SumoU32 SampleTexturePixel(SumoU32 *texture, SumoF32 x, SumoF32 y) {

  __asm {
    mov al, byte ptr [g_textureUseMmxSampler]
    mov ecx, dword ptr [esp + 8]
    mov edx, dword ptr [esp + 4]
    test al, al
    mov eax, dword ptr [esp + 0ch]
    push eax
    push ecx
    push edx
    jz sampleTextureUseX87
    call SampleTexturePixelMmx
    add esp, 0ch
    ret
  sampleTextureUseX87:
    call SampleTexturePixelX87
    add esp, 0ch
    ret
  }
}

SumoU32 *BuildTextureFromProgram(void *program);


// FUNCTION: SUMO 0x00419960
// FUNCTION: EDITOR 0x00419980
__declspec(naked) void **BuildTextureSet(void **programs, void *progressCallback) {

  __asm {
    mov al, byte ptr [g_textureGeneratorInitialized]
    test al, al
    jne textureSetInitialized
    call InitializeTextureGenerator
    mov byte ptr [g_textureGeneratorInitialized], 1
  textureSetInitialized:
    mov eax, dword ptr [esp + 8]
    push ebx
    push ebp
    mov ebp, dword ptr [esp + 0ch]
    push esi
    push edi
    mov dword ptr [g_textureProgressCallback], eax
    xor esi, esi
    xor edi, edi
    mov eax, ebp
  textureSetCountPrograms:
    mov ecx, dword ptr [eax + 4]
    add eax, 4
    inc edi
    cmp ecx, esi
    jne textureSetCountPrograms
    cmp edi, esi
    mov dword ptr [g_textureProgramTotalWork], esi
    mov dword ptr [g_textureProgramCompletedWork], esi
    jle textureSetAllocateResults
    mov eax, ebp
    mov ecx, edi
  textureSetSumWork:
    mov edx, dword ptr [eax]
    xor ebx, ebx
    add eax, 4
    mov bl, byte ptr [edx + 3]
    mov edx, dword ptr [g_textureProgramTotalWork]
    add edx, ebx
    dec ecx
    mov dword ptr [g_textureProgramTotalWork], edx
    jne textureSetSumWork
  textureSetAllocateResults:
    lea eax, dword ptr [edi * 4]
    push eax
    call malloc
    add esp, 4
    cmp edi, esi
    mov ebx, eax
    jle textureSetProgramsDone
    mov esi, ebx
    sub ebp, ebx
  textureSetBuildNext:
    mov ecx, dword ptr [esi + ebp]
    push ecx
    call BuildTextureFromProgram
    mov dword ptr [esi], eax
    add esp, 4
    add esi, 4
    dec edi
    jne textureSetBuildNext
    xor esi, esi
  textureSetProgramsDone:
    mov dword ptr [g_textureProgramTotalWork], esi
    mov dword ptr [g_textureProgramCompletedWork], esi
    call ShutdownTextureGenerator
    pop edi
    pop esi
    mov eax, ebx
    pop ebp
    pop ebx
    ret
  }
}

SumoS32 ClearTextureWorkBuffer(void *buffer);
void GenerateTextureFractalPlasma(SumoS32, char, SumoS32, SumoS32, SumoS32,
                                  SumoS32);
void GenerateTexturePlasma(SumoS32, char, SumoS32, SumoS32, SumoS32, SumoS32);
void GenerateTextureCells(SumoS32, char, SumoS32, SumoS32, SumoS32, SumoS32,
                          SumoS32, SumoS32);
void GenerateTextureRadialGradient(SumoS32, SumoS32, char, SumoS32);
void GenerateTextureCubicNoise(SumoS32, char, SumoS32, SumoS32, SumoS32,
                               SumoS32, SumoS32);
SumoS32 DistortTextureSine(SumoS32, SumoS32, SumoS32, SumoS32, SumoS32, SumoS32,
                           SumoS32);
void TranslateTextureLayerWrapped(SumoS32, char, char);
SumoS32 DistortTextureTwirl(SumoS32, SumoS32);
void SubtractShiftedTextureLayer(SumoS32, SumoS16);
SumoS32 BlurTextureLayer(SumoS32, SumoS32);
SumoS32 DistortTextureByLayers(SumoS32, SumoS32, char, SumoS32, SumoS32, char,
                               SumoS32);
void DirectionalBlurTextureLayer(SumoS32, SumoS32, char, SumoS32);
void SwapTextureChannels(SumoS32, char, SumoS32, char);
SumoS32 ReplicateTextureChannel(SumoS32, char);
void CopyTextureChannel(SumoS32, char, SumoS32, char);
void MixTextureLayers(SumoS32, SumoS32, SumoS32);
void MultiplyTextureLayers(SumoS32, SumoS32);
void AddTextureLayersSaturated(SumoS32, SumoS32);
void MaxTextureLayers(SumoS32, SumoS32);
void AdjustTextureContrast(SumoS32, SumoS32);
void InvertTextureLayerLowBytes(SumoS32);
void ShadeTextureLayerByChannel(SumoS32, SumoS32, char);
void ApplyTextureColorMap(SumoS32, SumoS32);
void ApplyTextureCosineWave(SumoS32, char, SumoS32);
void RemapTextureChannelRange(SumoS32, char, SumoS32, SumoS32);
void AdjustTextureHsv(SumoS32, SumoS32, SumoS32);
void ApplyTextureGradient(SumoS32, SumoS8, SumoS32, SumoS32, SumoS32, SumoS32,
                          SumoS32, SumoS32);
void BlendTextureLayersByMask(SumoS32, SumoS32, SumoS32, SumoS8);
void EmbossTextureLayer(SumoS32);
SumoU32 *ExpandTextureBitmap(SumoS32, SumoU8 *, SumoU32, SumoU32);
void ExecuteTextureProgram(void *program, SumoU32 *output);

// FUNCTION: SUMO 0x00419a10
// FUNCTION: EDITOR 0x00419a30
__declspec(naked) SumoU32 *BuildTextureFromProgram(void *program) {
  __asm {
    push esi
    push 40000h
    call malloc
    mov esi, eax
    mov eax, dword ptr [esp + 0ch]
    push esi
    push eax
    call ExecuteTextureProgram
    add esp, 0ch
    mov eax, esi
    pop esi
    ret
  }
}

// FUNCTION: SUMO 0x0041a0d0
// FUNCTION: EDITOR 0x0041a0f0
SumoS32 ClearTextureWorkBuffer(void *p_buffer) {
  SumoU32 *cursor = (SumoU32 *)p_buffer;
  SumoS32 count = 0x10000;
  while (count != 0) {
    *cursor++ = 0;
    --count;
  }

  return 0;
}

// GLOBAL: SUMO 0x00d0fac0
// GLOBAL: EDITOR 0x00d102d8
SumoS32 g_textureNoiseSeed;

// FUNCTION: SUMO 0x0041a0e0
// FUNCTION: EDITOR 0x0041a100
__declspec(naked) SumoS32 TextureNoiseHash(SumoS32 value) {
  __asm {
    mov ecx, dword ptr [esp + 4]
    mov edx, dword ptr [g_textureNoiseSeed]
    mov eax, ecx
    shl eax, 0dh
    xor eax, ecx
    mov ecx, eax
    add edx, eax
    imul ecx, eax
    imul ecx, ecx, 03d73h
    add ecx, 0c0ae5h
    mov eax, 1535f585h
    imul ecx, edx
    add ecx, 5208dd0dh
    imul ecx
    mov eax, edx
    sar eax, 0ah
    mov ecx, eax
    shr ecx, 1fh
    add eax, ecx
    ret
  }
}


// FUNCTION: SUMO 0x0041a130
// FUNCTION: EDITOR 0x0041a150
__declspec(naked) SumoF32 InterpolateTextureValue(SumoF32 first, SumoF32 second, SumoF32 third, SumoF32 fourth, SumoF32 position, SumoF32 span) {

  __asm {
    fld dword ptr [esp + 14h]
    fdiv dword ptr [esp + 18h]
    fld dword ptr [esp + 4]
    fsub dword ptr [esp + 8]
    fld dword ptr [esp + 10h]
    fsub dword ptr [esp + 0ch]
    fsub st, st(1)
    fld st(2)
    fmul st, st(3)
    fxch st(2)
    fsub st, st(1)
    fmul st, st(2)
    fxch st(2)
    fmul st, st(3)
    fmul st, st(1)
    faddp st(2), st
    fld dword ptr [esp + 0ch]
    fsub dword ptr [esp + 4]
    fmul st, st(3)
    faddp st(2), st
    fxch st(1)
    fadd dword ptr [esp + 8]
    fstp st(2)
    fstp st
    ret
  }
}

extern const double g_textureInvSize;
extern SumoU8 *g_textureLayers[4];


// FUNCTION: SUMO 0x0041a180
// FUNCTION: EDITOR 0x0041a1a0
__declspec(naked) void FillTextureCubicNoise(SumoF32 *output, SumoS32 spacing, SumoF32 amplitude) {

  __asm {
    sub esp, 28h
    fld dword ptr [esp + 34h]
    fmul qword ptr [g_textureInvSize]
    push ebx
    mov ebx, dword ptr [esp + 30h]
    push ebp
    push esi
    mov esi, dword ptr [esp + 3ch]
    push edi
    fstp dword ptr [esp + 28h]
    mov ecx, 10000h
    xor eax, eax
    mov edi, ebx
    mov dword ptr [esp + 24h], eax
    rep stosd
    mov dword ptr [esp + 3ch], eax
    mov eax, esi
    shl eax, 0ah
    mov dword ptr [esp + 20h], eax
    mov dword ptr [esp + 44h], ebx
cubicNoiseLatticeRow:
    mov ebp, dword ptr [esp + 44h]
    xor edi, edi
cubicNoiseLatticeColumn:
    mov ecx, dword ptr [esp + 24h]
    mov eax, ecx
    inc ecx
    push eax
    mov dword ptr [esp + 28h], ecx
    call TextureNoiseHash
    and eax, 0ffh
    add edi, esi
    mov dword ptr [esp + 30h], eax
    lea eax, dword ptr [esi * 4]
    fild dword ptr [esp + 30h]
    add esp, 4
    fmul dword ptr [esp + 28h]
    fstp dword ptr [ebp]
    add ebp, eax
    cmp edi, 100h
    jl cubicNoiseLatticeColumn
    mov eax, dword ptr [esp + 3ch]
    mov ecx, dword ptr [esp + 20h]
    mov edx, dword ptr [esp + 44h]
    add eax, esi
    add edx, ecx
    cmp eax, 100h
    mov dword ptr [esp + 3ch], eax
    mov dword ptr [esp + 44h], edx
    jl cubicNoiseLatticeRow
    mov eax, esi
    xor edi, edi
    shl eax, 8
    mov dword ptr [esp + 2ch], eax
cubicNoiseHorizontalRow:
    xor ebp, ebp
cubicNoiseHorizontalColumn:
    test ebp, ebp
    jz cubicNoiseHorizontalAdvance
    mov eax, 100h
    sub eax, esi
    and eax, ebp
    mov edx, eax
    sub edx, esi
    lea ecx, dword ptr [eax + esi]
    and edx, 0ffh
    add eax, edi
    add edx, edi
    and ecx, 0ffh
    fld dword ptr [ebx + edx * 4]
    lea edx, dword ptr [edi + ecx]
    add ecx, esi
    fstp dword ptr [esp + 18h]
    fld dword ptr [ebx + eax * 4]
    and ecx, 0ffh
    lea eax, dword ptr [esi - 1]
    fstp dword ptr [esp + 14h]
    fld dword ptr [ebx + edx * 4]
    add ecx, edi
    and eax, ebp
    fstp dword ptr [esp + 10h]
    fld dword ptr [ebx + ecx * 4]
    push ecx
    mov edx, dword ptr [esp + 14h]
    fstp dword ptr [esp + 48h]
    fild dword ptr [esp + 44h]
    mov dword ptr [esp + 40h], eax
    mov eax, dword ptr [esp + 18h]
    fstp dword ptr [esp]
    fild dword ptr [esp + 40h]
    push ecx
    mov ecx, dword ptr [esp + 4ch]
    fstp dword ptr [esp]
    push ecx
    mov ecx, dword ptr [esp + 24h]
    push edx
    push eax
    push ecx
    call InterpolateTextureValue
    lea edx, dword ptr [edi + ebp]
    add esp, 18h
    fstp dword ptr [ebx + edx * 4]
cubicNoiseHorizontalAdvance:
    inc ebp
    cmp ebp, 100h
    jl cubicNoiseHorizontalColumn
    add edi, dword ptr [esp + 2ch]
    cmp edi, 10000h
    jl cubicNoiseHorizontalRow
    xor ecx, ecx
    mov dword ptr [esp + 24h], ebx
    mov dword ptr [esp + 3ch], ecx
cubicNoiseVerticalRow:
    test ecx, ecx
    jz cubicNoiseVerticalAdvance
    mov eax, 100h
    lea ebp, dword ptr [esi - 1]
    sub eax, esi
    and eax, ecx
    fild dword ptr [esp + 40h]
    lea ecx, dword ptr [eax + esi]
    mov edx, eax
    and ecx, 0ffh
    sub edx, esi
    fstp dword ptr [esp + 30h]
    lea edi, dword ptr [ecx + esi]
    and edx, 0ffh
    and edi, 0ffh
    shl eax, 8
    shl edx, 8
    shl ecx, 8
    shl edi, 8
    and ebp, dword ptr [esp + 3ch]
    lea ecx, dword ptr [ebx + ecx * 4]
    lea edi, dword ptr [ebx + edi * 4]
    mov dword ptr [esp + 1ch], ecx
    mov dword ptr [esp + 2ch], ebp
    mov ebp, dword ptr [esp + 24h]
    fild dword ptr [esp + 2ch]
    mov dword ptr [esp + 28h], ebp
    mov dword ptr [esp + 20h], edi
    lea ebp, dword ptr [ebx + eax * 4]
    lea edi, dword ptr [ebx + edx * 4]
    fstp dword ptr [esp + 34h]
    mov dword ptr [esp + 2ch], 100h
cubicNoiseVerticalColumn:
    mov edx, dword ptr [edi]
    mov eax, dword ptr [ebp]
    mov ecx, dword ptr [esp + 1ch]
    mov dword ptr [esp + 18h], edx
    mov dword ptr [esp + 14h], eax
    mov eax, dword ptr [esp + 20h]
    mov edx, dword ptr [ecx]
    mov ecx, dword ptr [eax]
    mov eax, dword ptr [esp + 34h]
    mov dword ptr [esp + 10h], edx
    mov edx, dword ptr [esp + 30h]
    push edx
    mov edx, dword ptr [esp + 14h]
    push eax
    mov eax, dword ptr [esp + 1ch]
    mov dword ptr [esp + 4ch], ecx
    push ecx
    mov ecx, dword ptr [esp + 24h]
    push edx
    push eax
    push ecx
    call InterpolateTextureValue
    mov eax, dword ptr [esp + 40h]
    mov edx, dword ptr [esp + 34h]
    mov ecx, 4
    add esp, 18h
    fstp dword ptr [eax]
    add edx, ecx
    add eax, ecx
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esp + 20h]
    mov dword ptr [esp + 28h], eax
    mov eax, dword ptr [esp + 2ch]
    add edi, ecx
    add ebp, ecx
    add edx, ecx
    dec eax
    mov dword ptr [esp + 20h], edx
    mov dword ptr [esp + 2ch], eax
    jnz cubicNoiseVerticalColumn
    mov ecx, dword ptr [esp + 3ch]
cubicNoiseVerticalAdvance:
    mov edx, dword ptr [esp + 24h]
    inc ecx
    add edx, 400h
    cmp ecx, 100h
    mov dword ptr [esp + 3ch], ecx
    mov dword ptr [esp + 24h], edx
    jl cubicNoiseVerticalRow
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 28h
    ret
  }
}


// FUNCTION: SUMO 0x0041a400
// FUNCTION: EDITOR 0x0041a420
__declspec(naked) void GenerateTextureCubicNoise(SumoS32 layerIndex, char channel, SumoS32 spacing, SumoS32 seed0, SumoS32 seed1, SumoS32 seed2, SumoS32 seed3) {

  __asm {
    push esi
    mov esi, dword ptr [esp + 10h]
    test esi, esi
    jz cubicNoiseGeneratorReturn
    mov eax, dword ptr [esp + 14h]
    mov edx, dword ptr [esp + 18h]
    shl eax, 8
    push ebx
    or eax, edx
    push ebp
    mov ebp, dword ptr [esp + 24h]
    shl eax, 8
    or eax, ebp
    push edi
    mov edi, dword ptr [esp + 2ch]
    push 40000h
    shl eax, 8
    or eax, edi
    mov dword ptr [g_textureNoiseSeed], eax
    call malloc
    mov ebx, eax
    push 437f0000h
    push esi
    push ebx
    mov dword ptr [esp + 34h], ebx
    call FillTextureCubicNoise
    mov ecx, dword ptr [esp + 24h]
    mov esi, 2
    mov edx, 0ffh
    mov ebp, 0ffffffh
    mov edi, dword ptr [g_textureLayers + ecx * 4]
    mov ecx, dword ptr [esp + 28h]
    sub esi, ecx
    mov eax, ebx
    shl esi, 3
    mov ecx, esi
    add esp, 10h
    shl edx, cl
    mov dword ptr [esp + 1ch], 10000h
    sub ebp, edx
    sub eax, edi
    mov dword ptr [esp + 20h], eax
    jmp cubicNoiseGeneratorSample
cubicNoiseGeneratorReloadOffset:
    mov eax, dword ptr [esp + 20h]
cubicNoiseGeneratorSample:
    mov ebx, dword ptr [edi]
    fld dword ptr [eax + edi]
    and ebx, ebp
    call __ftol
    cmp eax, 0ffh
    jle cubicNoiseGeneratorClampLow
    mov eax, 0ffh
    jmp cubicNoiseGeneratorValueReady
cubicNoiseGeneratorClampLow:
    test eax, eax
    jge cubicNoiseGeneratorValueReady
    xor eax, eax
cubicNoiseGeneratorValueReady:
    mov ecx, esi
    add edi, 4
    shl eax, cl
    or eax, ebx
    mov dword ptr [edi - 4], eax
    mov eax, dword ptr [esp + 1ch]
    dec eax
    mov dword ptr [esp + 1ch], eax
    jnz cubicNoiseGeneratorReloadOffset
    mov eax, dword ptr [esp + 24h]
    push eax
    call free
    add esp, 4
    pop edi
    pop ebp
    pop ebx
cubicNoiseGeneratorReturn:
    pop esi
    ret
  }
}


// FUNCTION: SUMO 0x0041a4e0
// FUNCTION: EDITOR 0x0041a500
__declspec(naked) SumoU32 *AddTextureLayers(SumoU32 *destination, SumoU32 *source) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov ecx, dword ptr [esp + 8]
    push esi
    push edi
    sub ecx, eax
    mov edx, 10000h
  addNextSample:
    mov esi, dword ptr [ecx + eax]
    mov edi, dword ptr [eax]
    add edi, esi
    mov dword ptr [eax], edi
    add eax, 4
    dec edx
    jne addNextSample
    pop edi
    pop esi
    ret
  }
}

// GLOBAL: SUMO 0x00d0faac
// GLOBAL: EDITOR 0x00d102c4
SumoU8 *g_textureLayers[4];

// GLOBAL: SUMO 0x00d0f6a4
// GLOBAL: EDITOR 0x00d0febc
SumoU8 *g_textureByteBuffer;

// GLOBAL: SUMO 0x00d0f6a8
// GLOBAL: EDITOR 0x00d0fec0
SumoU8 *g_textureIoBuffer;

// GLOBAL: SUMO 0x00d0f6a0
// GLOBAL: EDITOR 0x00d0feb8
TextureProgressCallback g_textureProgressCallback;

// GLOBAL: SUMO 0x00d0fad2
// GLOBAL: EDITOR 0x00d102ea
SumoU8 g_textureGeneratorInitialized;

// GLOBAL: SUMO 0x00d0fad4
// GLOBAL: EDITOR 0x00d102ec
SumoS32 g_textureProgramTotalWork;

// GLOBAL: SUMO 0x00d0fad8
// GLOBAL: EDITOR 0x00d102f0
SumoS32 g_textureProgramCompletedWork;

// GLOBAL: SUMO 0x00d0fad1
// GLOBAL: EDITOR 0x00d102e9
SumoU8 g_textureLoadFromTga;

// GLOBAL: SUMO 0x00d0fabc
// GLOBAL: EDITOR 0x00d102d4
SumoU8 *g_textureCommandCursor;

// GLOBAL: SUMO 0x00d0fac4
// GLOBAL: EDITOR 0x00d102dc
SumoU8 *g_textureColorMap;

// GLOBAL: SUMO 0x00d0fac8
// GLOBAL: EDITOR 0x00d102e0
SumoU32 *g_textureWorkBuffer;

// GLOBAL: SUMO 0x00d0facc
// GLOBAL: EDITOR 0x00d102e4
SumoU32 *g_textureChannelSwapBuffer;

// GLOBAL: SUMO 0x00d0f6ac
// GLOBAL: EDITOR 0x00d0fec4
SumoS32 g_textureInterpolationWeights[256];

// GLOBAL: SUMO 0x0042ce78
// GLOBAL: EDITOR 0x0042ce78
const double g_textureTau = 6.283185482025146484375;

// GLOBAL: SUMO 0x0042ce08
// GLOBAL: EDITOR 0x0042ce08
const double g_textureInvSize = 0.00390625;

// GLOBAL: SUMO 0x0042ce38
// GLOBAL: EDITOR 0x0042ce38
const double g_textureWaveAmplitude = 127.0;

// GLOBAL: SUMO 0x0042ce68
// GLOBAL: EDITOR 0x0042ce68
const double g_textureContrastScale = 0.03125;

// GLOBAL: SUMO 0x0042ce40
// GLOBAL: EDITOR 0x0042ce40
const double g_texturePlasmaAmplitude = 63.0;

// GLOBAL: SUMO 0x0042ce48
// GLOBAL: EDITOR 0x0042ce48
const double g_textureRadiansPerPixel = 0.02454369328916073;

// GLOBAL: SUMO 0x0042ce70
// GLOBAL: EDITOR 0x0042ce70
const double g_textureHalfCenter = 127.5;

// GLOBAL: SUMO 0x0042ce60
// GLOBAL: EDITOR 0x0042ce60
const double g_textureAngleToByte = 40.74366429772945;

// GLOBAL: SUMO 0x0042ce5c
// GLOBAL: EDITOR 0x0042ce5c
extern const SumoF32 g_textureCenterFloat = 128.0f;

// GLOBAL: SUMO 0x0042ce58
// GLOBAL: EDITOR 0x0042ce58
const SumoF32 g_textureTwirlFrequency = 0.012271847f;

// GLOBAL: SUMO 0x0042ce50
// GLOBAL: EDITOR 0x0042ce50
const double g_textureRadialBaseScale = 0.8;

// GLOBAL: SUMO 0x0042cde8
// GLOBAL: EDITOR 0x0042cde8
const double g_textureByteMaximum = 255.0;

// GLOBAL: SUMO 0x0042ce20
// GLOBAL: EDITOR 0x0042ce20
extern const SumoF32 g_textureByteMaximumFloat = 255.0f;

// GLOBAL: SUMO 0x0042ce28
// GLOBAL: EDITOR 0x0042ce28
const double g_textureCenter = 128.0;

// GLOBAL: SUMO 0x0042ce30
// GLOBAL: EDITOR 0x0042ce30
const double g_textureCellRadiusScale = 0.0390625;

// GLOBAL: SUMO 0x0042ce10
// GLOBAL: EDITOR 0x0042ce10
extern const double g_textureHalf = 0.5;

// GLOBAL: SUMO 0x0042ce18
// GLOBAL: EDITOR 0x0042ce18
const double g_texturePi = 3.1415927410125732421875;

// GLOBAL: SUMO 0x0042cdf0
// GLOBAL: EDITOR 0x0042cdf0
extern const double g_textureOne = 1.0;

// GLOBAL: SUMO 0x0042cd90
// GLOBAL: EDITOR 0x0042cd90
const double g_textureSize = 256.0;

// GLOBAL: SUMO 0x0042cdf8
// GLOBAL: EDITOR 0x0042cdf8
const double g_textureColorMapRowScale = 0.007874015748031496;

// GLOBAL: SUMO 0x0042ceb0
// GLOBAL: EDITOR 0x0042ceb0
const SumoF32 g_textureBlendScale = 0.00390625f;

// GLOBAL: SUMO 0x0042cd70
// GLOBAL: EDITOR 0x0042cd70
extern const double g_textureHueSectorTwo = 2.0;

// GLOBAL: SUMO 0x0042ce98
// GLOBAL: EDITOR 0x0042ce98
extern const double g_textureHueSectorFour = 4.0;

// GLOBAL: SUMO 0x0042ce90
// GLOBAL: EDITOR 0x0042ce90
extern const double g_textureHueDegreesPerSector = 60.0;

// GLOBAL: SUMO 0x0042ce88
// GLOBAL: EDITOR 0x0042ce88
extern const double g_textureHueCircle = 360.0;

// GLOBAL: SUMO 0x0042d1d8
// GLOBAL: EDITOR 0x0042d1d8
extern const double g_textureZero = 0.0;

// GLOBAL: SUMO 0x0042ce80
// GLOBAL: EDITOR 0x0042ce80
extern const double g_textureHueSectorScale = 0.016666666666666666;

// GLOBAL: SUMO 0x0042cea8
// GLOBAL: EDITOR 0x0042cea8
extern const double g_textureHueByteToDegrees = 1.40625;

// GLOBAL: SUMO 0x0042cea0
// GLOBAL: EDITOR 0x0042cea0
extern const double g_textureInvByteMaximum = 0.0039215686274509803;


// FUNCTION: SUMO 0x0041a510
// FUNCTION: EDITOR 0x0041a530
__declspec(naked) void FillTextureFractalMap(SumoU32 *output, SumoS32 spacing, SumoF32 amplitude) {

  __asm {
    sub esp, 10h
    fld dword ptr [esp + 1ch]
    fmul qword ptr [g_textureInvSize]
    push ebx
    mov ebx, dword ptr [esp + 18h]
    push ebp
    push esi
    mov esi, dword ptr [esp + 24h]
    push edi
    fstp dword ptr [esp + 1ch]
    mov ecx, 10000h
    xor eax, eax
    mov edi, ebx
    mov dword ptr [esp + 10h], eax
    rep stosd
    mov dword ptr [esp + 24h], eax
    mov eax, esi
    shl eax, 0ah
    mov dword ptr [esp + 14h], eax
    mov dword ptr [esp + 2ch], ebx
fillFractalNextLatticeRow:
    mov ebp, dword ptr [esp + 2ch]
    xor edi, edi
fillFractalNextLatticeColumn:
    mov ecx, dword ptr [esp + 10h]
    mov eax, ecx
    inc ecx
    push eax
    mov dword ptr [esp + 14h], ecx
    call TextureNoiseHash
    and eax, 0ffh
    add esp, 4
    mov dword ptr [esp + 18h], eax
    fild dword ptr [esp + 18h]
    fmul dword ptr [esp + 1ch]
    call __ftol
    shl eax, 10h
    mov dword ptr [ebp], eax
    lea eax, dword ptr [esi * 4]
    add edi, esi
    add ebp, eax
    cmp edi, 100h
    jl fillFractalNextLatticeColumn
    mov eax, dword ptr [esp + 24h]
    mov ecx, dword ptr [esp + 14h]
    mov edx, dword ptr [esp + 2ch]
    add eax, esi
    add edx, ecx
    cmp eax, 100h
    mov dword ptr [esp + 24h], eax
    mov dword ptr [esp + 2ch], edx
    jl fillFractalNextLatticeRow
    xor edi, edi
    test esi, esi
    mov dword ptr [esp + 24h], edi
    jle fillFractalWeightsReady
    fild dword ptr [esp + 28h]
    mov ebp, offset g_textureInterpolationWeights
fillFractalNextWeight:
    fild dword ptr [esp + 24h]
    fmul qword ptr [g_texturePi]
    fdiv st, st(1)
    fcos
    fsubr qword ptr [g_textureOne]
    fmul qword ptr [g_textureHalf]
    fmul qword ptr [g_textureSize]
    call __ftol
    mov dword ptr [ebp], eax
    inc edi
    add ebp, 4
    cmp edi, esi
    mov dword ptr [esp + 24h], edi
    jl fillFractalNextWeight
    fstp st
fillFractalWeightsReady:
    mov eax, 100h
    xor edi, edi
    sub eax, esi
    mov dword ptr [esp + 2ch], eax
    mov eax, esi
    shl eax, 8
    mov dword ptr [esp + 1ch], eax
    mov eax, ebx
    mov dword ptr [esp + 24h], eax
fillFractalHorizontalNextRow:
    xor ecx, ecx
    mov dword ptr [esp + 28h], eax
fillFractalHorizontalNextPixel:
    mov eax, dword ptr [esp + 2ch]
    and eax, ecx
    lea edx, dword ptr [edi + eax]
    add eax, esi
    and eax, 0ffh
    mov edx, dword ptr [ebx + edx * 4]
    add eax, edi
    mov ebp, dword ptr [ebx + eax * 4]
    lea eax, dword ptr [esi - 1]
    and eax, ecx
    sub ebp, edx
    imul ebp, dword ptr [g_textureInterpolationWeights + eax * 4]
    mov eax, dword ptr [esp + 28h]
    sar ebp, 8
    add ebp, edx
    inc ecx
    mov dword ptr [eax], ebp
    add eax, 4
    cmp ecx, 100h
    mov dword ptr [esp + 28h], eax
    jl fillFractalHorizontalNextPixel
    mov ebp, dword ptr [esp + 1ch]
    mov eax, dword ptr [esp + 24h]
    mov edx, dword ptr [esp + 14h]
    add edi, ebp
    add eax, edx
    cmp edi, 10000h
    mov dword ptr [esp + 24h], eax
    jl fillFractalHorizontalNextRow
    xor edx, edx
    mov dword ptr [esp + 28h], ebx
    mov dword ptr [esp + 24h], edx
fillFractalVerticalNextRow:
    test edx, edx
    je fillFractalVerticalAdvance
    mov eax, dword ptr [esp + 2ch]
    lea edi, dword ptr [esi - 1]
    and eax, edx
    mov dword ptr [esp + 14h], 100h
    lea ecx, dword ptr [eax + esi]
    and ecx, 0ffh
    shl eax, 8
    shl ecx, 8
    and edi, edx
    lea eax, dword ptr [ebx + eax * 4]
    lea ecx, dword ptr [ebx + ecx * 4]
    lea edx, dword ptr [g_textureInterpolationWeights + edi * 4]
    mov dword ptr [esp + 1ch], edx
    mov edx, dword ptr [esp + 28h]
fillFractalVerticalNextPixel:
    mov edi, dword ptr [eax]
    mov ebp, dword ptr [ecx]
    sub ebp, edi
    mov edi, dword ptr [esp + 1ch]
    add eax, 4
    add ecx, 4
    imul ebp, dword ptr [edi]
    mov edi, dword ptr [eax - 4]
    add edx, 4
    sar ebp, 8
    add ebp, edi
    mov edi, dword ptr [esp + 14h]
    mov dword ptr [edx - 4], ebp
    dec edi
    mov dword ptr [esp + 14h], edi
    jne fillFractalVerticalNextPixel
    mov edx, dword ptr [esp + 24h]
fillFractalVerticalAdvance:
    mov ecx, dword ptr [esp + 28h]
    inc edx
    add ecx, 400h
    cmp edx, 100h
    mov dword ptr [esp + 24h], edx
    mov dword ptr [esp + 28h], ecx
    jl fillFractalVerticalNextRow
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 10h
    ret
  }
}


// FUNCTION: SUMO 0x0041a720
// FUNCTION: EDITOR 0x0041a740
__declspec(naked) void GenerateTextureFractalPlasma(SumoS32 layerIndex, char channel, SumoS32 seed0, SumoS32 seed1, SumoS32 seed2, SumoS32 seed3) {

  __asm {
    mov ecx, dword ptr [esp + 8]
    mov edx, dword ptr [esp + 10h]
    push ebx
    push esi
    mov esi, 2
    mov eax, dword ptr [esp + 0ch]
    mov ebx, dword ptr [esp + 1ch]
    sub esi, ecx
    mov ecx, dword ptr [esp + 14h]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [esp + 24h]
    shl ecx, 8
    or ecx, edx
    mov edx, dword ptr [g_textureWorkBuffer]
    shl ecx, 8
    or ecx, ebx
    push 43000000h
    shl ecx, 8
    or ecx, eax
    push 80h
    push edx
    mov dword ptr [g_textureNoiseSeed], ecx
    shl esi, 3
    call FillTextureFractalMap
    add esp, 0ch
    mov ebx, 40h
    mov dword ptr [esp + 10h], 42800000h
fractalPlasmaNextOctave:
    mov eax, dword ptr [esp + 10h]
    mov ecx, dword ptr [g_textureChannelSwapBuffer]
    push eax
    push ebx
    push ecx
    call FillTextureFractalMap
    mov edx, dword ptr [g_textureChannelSwapBuffer]
    mov eax, dword ptr [g_textureWorkBuffer]
    push edx
    push eax
    call AddTextureLayers
    fld dword ptr [esp + 24h]
    fmul qword ptr [g_textureHalf]
    mov eax, ebx
    add esp, 14h
    cdq
    fstp dword ptr [esp + 10h]
    sub eax, edx
    sar eax, 1
    mov ebx, eax
    test ebx, ebx
    jg fractalPlasmaNextOctave
    mov eax, 0ffh
    mov ecx, esi
    shl eax, cl
    mov edx, 0ffffffh
    sub edx, eax
    xor eax, eax
fractalPlasmaMergeNextPixel:
    mov ecx, dword ptr [g_textureWorkBuffer]
    add eax, 4
    mov ebx, dword ptr [eax + ecx - 4]
    mov ecx, esi
    shr ebx, 10h
    shl ebx, cl
    mov ecx, dword ptr [eax + edi - 4]
    and ecx, edx
    or ebx, ecx
    cmp eax, 40000h
    mov dword ptr [eax + edi - 4], ebx
    jl fractalPlasmaMergeNextPixel
    pop edi
    pop esi
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041a810
// FUNCTION: EDITOR 0x0041a830
__declspec(naked) void GenerateTextureCells(SumoS32 layerIndex, char channel, SumoS32 cellCount, SumoS32 radiusScale, SumoS32 seed0, SumoS32 seed1, SumoS32 seed2, SumoS32 seed3) {

  __asm {
    sub esp, 0ch
    fild dword ptr [esp + 1ch]
    push ebx
    push ebp
    push esi
    push edi
    fmul qword ptr [g_textureCellRadiusScale]
    push 40000h
    fstp dword ptr [esp + 1ch]
    call malloc
    add esp, 4
    mov ebp, eax
    xor ebx, ebx
    mov dword ptr [esp + 14h], ebp
    mov dword ptr [esp + 10h], ebx
    mov esi, ebp
cellsKernelNextRow:
    fild dword ptr [esp + 10h]
    xor edi, edi
    mov dword ptr [esp + 2ch], edi
    fsub qword ptr [g_textureCenter]
    fld st
    fmulp st(1), st
cellsKernelNextColumn:
    fild dword ptr [esp + 2ch]
    fsub qword ptr [g_textureCenter]
    fld st
    fmulp st(1), st
    fadd st, st(1)
    fsqrt
    fmul dword ptr [esp + 18h]
    fcom dword ptr [g_textureByteMaximumFloat]
    fnstsw ax
    test ah, 41h
    jne cellsKernelClampReady
    fstp st
    fld dword ptr [g_textureByteMaximumFloat]
cellsKernelClampReady:
    call __ftol
    mov dword ptr [esi], eax
    inc edi
    add esi, 4
    cmp edi, 100h
    mov dword ptr [esp + 2ch], edi
    jl cellsKernelNextColumn
    inc ebx
    cmp ebx, 100h
    mov dword ptr [esp + 10h], ebx
    fstp st
    jl cellsKernelNextRow
    mov eax, dword ptr [esp + 30h]
    mov ebx, dword ptr [esp + 34h]
    mov esi, dword ptr [esp + 38h]
    mov ecx, dword ptr [esp + 3ch]
    shl eax, 8
    or eax, ebx
    shl eax, 8
    or eax, esi
    shl eax, 8
    or eax, ecx
    mov dword ptr [g_textureNoiseSeed], eax
    xor eax, eax
cellsClearNextPixel:
    mov ecx, dword ptr [g_textureWorkBuffer]
    add eax, 4
    cmp eax, 40000h
    mov dword ptr [eax + ecx - 4], 0ffh
    jl cellsClearNextPixel
    mov eax, dword ptr [esp + 28h]
    xor edi, edi
    test eax, eax
    jle cellsMergeResult
    mov dword ptr [esp + 2ch], eax
cellsNextSeed:
    mov eax, edi
    inc edi
    push eax
    call TextureNoiseHash
    mov esi, eax
    mov eax, edi
    and esi, 0ffh
    inc edi
    push eax
    mov dword ptr [esp + 44h], edi
    call TextureNoiseHash
    and eax, 0ffh
    add esp, 8
    xor ecx, ecx
    lea ebx, dword ptr [eax - 80h]
    add eax, 80h
    cmp ebx, eax
    mov dword ptr [esp + 28h], eax
    jge cellsSeedComplete
    lea edx, dword ptr [esi - 80h]
    lea ebp, dword ptr [esi + 80h]
    mov dword ptr [esp + 30h], edx
    mov dword ptr [esp + 34h], ebp
cellsNextWrappedRow:
    mov esi, dword ptr [esp + 30h]
    cmp esi, ebp
    jge cellsAdvanceWrappedRow
    mov eax, ebx
    sub ebp, esi
    and eax, 0ffh
    shl eax, 8
    mov edi, eax
    mov eax, dword ptr [esp + 14h]
    lea edx, dword ptr [eax + ecx * 4]
    add ecx, ebp
    mov dword ptr [esp + 38h], ecx
cellsNextWrappedColumn:
    mov ebp, dword ptr [g_textureWorkBuffer]
    mov eax, esi
    and eax, 0ffh
    mov ecx, dword ptr [edx]
    add eax, edi
    add edx, 4
    lea eax, dword ptr [ebp + eax * 4]
    cmp dword ptr [eax], ecx
    jbe cellsKeepMinimum
    mov dword ptr [eax], ecx
cellsKeepMinimum:
    mov ebp, dword ptr [esp + 34h]
    inc esi
    cmp esi, ebp
    jl cellsNextWrappedColumn
    mov ecx, dword ptr [esp + 38h]
    mov edi, dword ptr [esp + 3ch]
    mov eax, dword ptr [esp + 28h]
cellsAdvanceWrappedRow:
    inc ebx
    cmp ebx, eax
    jl cellsNextWrappedRow
cellsSeedComplete:
    mov eax, dword ptr [esp + 2ch]
    dec eax
    mov dword ptr [esp + 2ch], eax
    jne cellsNextSeed
    mov ebp, dword ptr [esp + 14h]
cellsMergeResult:
    mov ebx, dword ptr [esp + 24h]
    mov ecx, 2
    sub ecx, ebx
    mov edx, 0ffh
    shl ecx, 3
    mov edi, dword ptr [esp + 20h]
    mov esi, 0ffffffh
    shl edx, cl
    sub esi, edx
    xor eax, eax
cellsMergeNextPixel:
    mov edx, dword ptr [g_textureLayers + edi * 4]
    add edx, eax
    mov ebx, dword ptr [edx]
    and ebx, esi
    mov dword ptr [edx], ebx
    mov ebx, dword ptr [g_textureWorkBuffer]
    mov edx, dword ptr [g_textureLayers + edi * 4]
    mov ebx, dword ptr [eax + ebx]
    add edx, eax
    shl ebx, cl
    add eax, 4
    or dword ptr [edx], ebx
    cmp eax, 40000h
    jl cellsMergeNextPixel
    push ebp
    call free
    add esp, 4
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 0ch
    ret
  }
}


// FUNCTION: SUMO 0x0041aa10
// FUNCTION: EDITOR 0x0041aa30
__declspec(naked) void GenerateTexturePlasma(SumoS32 layerIndex, char channel, SumoS32 frequencyX, SumoS32 frequencyY, SumoS32 shiftX, SumoS32 shiftY) {

  __asm {
    push ecx
    mov al, byte ptr [esp + 0ch]
    mov edx, dword ptr [esp + 8]
    fild dword ptr [esp + 10h]
    shl al, 3
    mov cl, 10h
    push ebx
    mov ebx, dword ptr [g_textureLayers + edx * 4]
    sub cl, al
    fild dword ptr [esp + 18h]
    push ebp
    push esi
    mov byte ptr [esp + 0ch], cl
    push edi
    mov ebp, dword ptr [esp + 10h]
    xor edi, edi
    mov dword ptr [esp + 1ch], edi
    and ebp, 0ffh
plasmaNextRow:
    mov eax, dword ptr [esp + 2ch]
    mov ecx, dword ptr [esp + 1ch]
    xor esi, esi
    add ecx, eax
    mov dword ptr [esp + 18h], ecx
    fild dword ptr [esp + 18h]
    fmul st, st(1)
    fmul qword ptr [g_textureRadiansPerPixel]
    fsin
plasmaNextColumn:
    mov edx, dword ptr [esp + 28h]
    lea eax, dword ptr [esi + edx]
    mov dword ptr [esp + 18h], eax
    fild dword ptr [esp + 18h]
    fmul st, st(3)
    fmul qword ptr [g_textureRadiansPerPixel]
    fsin
    fadd st, st(1)
    fmul qword ptr [g_texturePlasmaAmplitude]
    fadd qword ptr [g_textureWaveAmplitude]
    call __ftol
    mov ecx, ebp
    shl eax, cl
    mov ecx, dword ptr [g_textureWorkBuffer]
    inc edi
    inc esi
    cmp esi, 100h
    mov dword ptr [ecx + edi * 4 - 4], eax
    jl plasmaNextColumn
    mov eax, dword ptr [esp + 1ch]
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 1ch], eax
    fstp st
    jl plasmaNextRow
    mov eax, 0ffh
    mov ecx, ebp
    shl eax, cl
    mov edx, 0ffffffh
    fstp st
    fstp st
    sub edx, eax
    xor eax, eax
plasmaMergeNextPixel:
    mov ebp, dword ptr [eax + ebx]
    add eax, 4
    and ebp, edx
    mov dword ptr [eax + ebx - 4], ebp
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, ebp
    mov esi, dword ptr [eax + esi - 4]
    or esi, ecx
    cmp eax, 40000h
    mov dword ptr [eax + ebx - 4], esi
    jl plasmaMergeNextPixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop ecx
    ret
  }
}


// FUNCTION: SUMO 0x0041ab00
// FUNCTION: EDITOR 0x0041ab20
__declspec(naked) void GenerateTextureRadialGradient(SumoS32 layerIndex, SumoS32 mode, char channel, SumoS32 scale) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov ecx, dword ptr [esp + 8]
    test ecx, ecx
    mov eax, dword ptr [g_textureLayers + eax * 4]
    jne radialCheckChannelMode
    fld dword ptr [g_gameOne]
    jmp radialScaleReady
radialCheckChannelMode:
    cmp ecx, 1
    jne radialUseExplicitScale
    fild dword ptr [esp + 10h]
    fmul qword ptr [g_textureInvSize]
    fadd qword ptr [g_textureRadialBaseScale]
    jmp radialScaleReady
radialUseExplicitScale:
    fld dword ptr [esp + 8]
radialScaleReady:
    push ebx
    push ebp
    mov ebp, dword ptr [esp + 14h]
    mov ebx, 2
    sub ebx, ebp
    mov edx, 0ffh
    shl ebx, 3
    mov ecx, ebx
    mov ebp, 0ffffffh
    shl edx, cl
    push esi
    push edi
    mov dword ptr [esp + 14h], 0
    sub ebp, edx
    jmp radialBeginRow
radialReloadRowPointer:
    mov eax, dword ptr [esp + 20h]
radialBeginRow:
    mov ecx, dword ptr [esp + 14h]
    xor edi, edi
    add ecx, 0ffffff80h
    mov esi, eax
    mov dword ptr [esp + 20h], ecx
    add eax, 400h
    fild dword ptr [esp + 20h]
    mov dword ptr [esp + 20h], eax
    fld st
    fmulp st(1), st
radialNextColumn:
    lea edx, dword ptr [edi - 80h]
    mov dword ptr [esp + 1ch], edx
    fild dword ptr [esp + 1ch]
    fld st
    fmul st, st(1)
    fadd st, st(2)
    fsqrt
    fld st(3)
    fmulp st(1), st
    fadd st, st
    fsubr qword ptr [g_textureByteMaximum]
    call __ftol
    test eax, eax
    fstp st
    jge radialClampUpper
    xor eax, eax
    jmp radialValueReady
radialClampUpper:
    cmp eax, 0ffh
    jle radialValueReady
    mov eax, 0ffh
radialValueReady:
    mov ecx, dword ptr [esp + 18h]
    test ecx, ecx
    jne radialMaybeSelectedChannel
    mov ecx, eax
    shl ecx, 8
    or ecx, eax
    shl ecx, 8
    or ecx, eax
    mov dword ptr [esi], ecx
    jmp radialAdvanceColumn
radialMaybeSelectedChannel:
    cmp ecx, 1
    jne radialAdvanceColumn
    mov edx, dword ptr [esi]
    mov ecx, ebx
    shl eax, cl
    and edx, ebp
    or edx, eax
    mov dword ptr [esi], edx
radialAdvanceColumn:
    add esi, 4
    inc edi
    cmp edi, 100h
    jl radialNextColumn
    mov eax, dword ptr [esp + 14h]
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 14h], eax
    fstp st
    jl radialReloadRowPointer
    pop edi
    pop esi
    pop ebp
    pop ebx
    fstp st
    ret
  }
}


// FUNCTION: SUMO 0x0041ac20
// FUNCTION: EDITOR 0x0041ac40
__declspec(naked) SumoS32 DistortTextureSine( SumoS32 layerIndex, SumoS32 xFrequency, SumoS32 yFrequency, SumoS32 xAmplitude, SumoS32 yAmplitude, SumoS32 xPhase, SumoS32 yPhase) {

  __asm {
    sub esp, 41ch
    fild dword ptr [esp + 42ch]
    mov eax, dword ptr [esp + 420h]
    push ebx
    push ebp
    push esi
    fstp dword ptr [esp + 1ch]
    fild dword ptr [esp + 43ch]
    fild dword ptr [esp + 430h]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    xor ebx, ebx
    xor eax, eax
    fstp dword ptr [esp + 28h]
    fild dword ptr [esp + 438h]
    fild dword ptr [esp + 444h]
    mov dword ptr [esp + 10h], eax
    lea ecx, dword ptr [esp + 2ch]
    fstp dword ptr [esp + 1ch]
    fild dword ptr [esp + 448h]
distortSineBuildCosineTable:
    fild dword ptr [esp + 10h]
    inc eax
    add ecx, 4
    cmp eax, 100h
    mov dword ptr [esp + 10h], eax
    fadd st, st(1)
    fld st(2)
    fmulp st(1), st
    fmul qword ptr [g_textureRadiansPerPixel]
    fcos
    fld st(3)
    fmulp st(1), st
    fstp dword ptr [ecx - 4]
    jl distortSineBuildCosineTable
    fstp st
    fstp st
    fstp st
    mov dword ptr [esp + 10h], 0
    mov dword ptr [esp + 14h], ebx
distortSineNextRow:
    fild dword ptr [esp + 14h]
    mov dword ptr [esp + 18h], 0
    lea esi, dword ptr [esp + 2ch]
    mov ebp, 100h
    fadd dword ptr [esp + 1ch]
    fmul dword ptr [esp + 28h]
    fmul qword ptr [g_textureRadiansPerPixel]
    fsin
    fmul dword ptr [esp + 20h]
    fstp dword ptr [esp + 24h]
distortSineNextColumn:
    fld dword ptr [esp + 10h]
    fadd dword ptr [esi]
    push ecx
    fstp dword ptr [esp]
    fld dword ptr [esp + 1ch]
    fadd dword ptr [esp + 28h]
    push ecx
    fstp dword ptr [esp]
    push edi
    call SampleTexturePixel
    fld dword ptr [esp + 24h]
    mov ecx, dword ptr [g_textureWorkBuffer]
    add esp, 0ch
    fadd dword ptr [g_gameOne]
    mov dword ptr [ecx + ebx * 4], eax
    inc ebx
    add esi, 4
    dec ebp
    fstp dword ptr [esp + 18h]
    jnz distortSineNextColumn
    fld dword ptr [esp + 10h]
    mov eax, dword ptr [esp + 14h]
    fadd dword ptr [g_gameOne]
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 14h], eax
    fstp dword ptr [esp + 10h]
    jl distortSineNextRow
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    rep movsd
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 41ch
    ret
  }
}


// FUNCTION: SUMO 0x0041ad60
// FUNCTION: EDITOR 0x0041ad80
__declspec(naked) SumoS32 DistortTextureTwirl(SumoS32 layerIndex, SumoS32 strength) {

  __asm {
    sub esp, 0ch
    fild dword ptr [esp + 14h]
    mov eax, dword ptr [esp + 10h]
    push ebx
    push ebp
    push esi
    fsub qword ptr [g_textureHalfCenter]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov dword ptr [esp + 14h], 0bf800000h
    fmul qword ptr [g_textureContrastScale]
    fstp dword ptr [esp + 10h]
    fld dword ptr [esp + 10h]
    fcomp dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 41h
    jz distortTwirlDirectionReady
    mov dword ptr [esp + 14h], 3f800000h
distortTwirlDirectionReady:
    xor ebx, ebx
    xor ebp, ebp
    mov dword ptr [esp + 24h], ebp
distortTwirlNextRow:
    fild dword ptr [esp + 24h]
    xor esi, esi
    mov dword ptr [esp + 20h], esi
    fsub qword ptr [g_textureHalfCenter]
    fst dword ptr [esp + 24h]
    fmul dword ptr [esp + 24h]
    fstp dword ptr [esp + 18h]
distortTwirlNextColumn:
    fild dword ptr [esp + 20h]
    fsub qword ptr [g_textureHalfCenter]
    fld st
    fmul st, st(1)
    fadd dword ptr [esp + 18h]
    fsqrt
    fstp dword ptr [esp + 20h]
    fld dword ptr [esp + 24h]
    fpatan
    fmul qword ptr [g_textureAngleToByte]
    fld dword ptr [g_textureCenterFloat]
    fsub dword ptr [esp + 20h]
    fcom dword ptr [g_vectorZero]
    fnstsw ax
    test ah, 1
    jz distortTwirlInsideRadius
    fstp st
    fld dword ptr [g_vectorZero]
    jmp distortTwirlPhaseReady
distortTwirlInsideRadius:
    fmul dword ptr [esp + 10h]
    fmul dword ptr [g_textureTwirlFrequency]
    fcos
    fmul qword ptr [g_textureCenter]
    fadd qword ptr [g_textureCenter]
distortTwirlPhaseReady:
    fmul dword ptr [esp + 14h]
    push ecx
    faddp st(1), st
    fmul qword ptr [g_textureRadiansPerPixel]
    fld st
    fcos
    fmul dword ptr [esp + 24h]
    fadd qword ptr [g_textureCenter]
    fstp dword ptr [esp]
    push ecx
    fsin
    fmul dword ptr [esp + 28h]
    fadd qword ptr [g_textureCenter]
    fstp dword ptr [esp]
    push edi
    call SampleTexturePixel
    mov ecx, dword ptr [g_textureWorkBuffer]
    add esp, 0ch
    mov dword ptr [ecx + ebx * 4], eax
    inc ebx
    inc esi
    cmp esi, 100h
    mov dword ptr [esp + 20h], esi
    jl distortTwirlNextColumn
    inc ebp
    cmp ebp, 100h
    mov dword ptr [esp + 24h], ebp
    jl distortTwirlNextRow
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    rep movsd
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 0ch
    ret
  }
}


// FUNCTION: SUMO 0x0041aea0
// FUNCTION: EDITOR 0x0041aec0
__declspec(naked) void TranslateTextureLayerWrapped(SumoS32 layerIndex, char offsetX, char offsetY) {

  __asm {
    mov eax, dword ptr [esp + 4]
    push ebx
    push ebp
    push esi
    mov esi, dword ptr [esp + 14h]
    xor ecx, ecx
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov dword ptr [esp + 14h], ecx
translateNextRow:
    mov edx, dword ptr [esp + 1ch]
    xor eax, eax
    add edx, ecx
    and edx, 0ffh
    shl edx, 8
    shl ecx, 0ah
translateNextColumn:
    mov ebp, dword ptr [g_textureWorkBuffer]
    lea ebx, dword ptr [eax + esi]
    and ebx, 0ffh
    add ecx, 4
    add ebx, edx
    inc eax
    cmp eax, 100h
    mov ebx, dword ptr [edi + ebx * 4]
    mov dword ptr [ecx + ebp - 4], ebx
    jl translateNextColumn
    mov ecx, dword ptr [esp + 14h]
    inc ecx
    cmp ecx, 100h
    mov dword ptr [esp + 14h], ecx
    jl translateNextRow
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    rep movsd
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041af20
// FUNCTION: EDITOR 0x0041af40
__declspec(naked) void SubtractShiftedTextureLayer(SumoS32 layerIndex, SumoS16 diagonalOffset) {

  __asm {
    push ecx
    mov eax, dword ptr [esp + 8]
    mov ecx, dword ptr [esp + 0ch]
    push ebx
    push ebp
    push esi
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov eax, ecx
    shl eax, 8
    add eax, ecx
    xor ebp, ebp
    mov dword ptr [esp + 18h], eax
    jmp subtractShiftedLoad
subtractShiftedReloadOffset:
    mov eax, dword ptr [esp + 18h]
subtractShiftedLoad:
    lea ecx, dword ptr [eax + ebp]
    xor edx, edx
    and ecx, 0ffffh
    xor ebx, ebx
    mov eax, dword ptr [edi + ecx * 4]
    mov ecx, dword ptr [edi + ebp * 4]
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 1ch], ecx
    mov dl, byte ptr [esp + 1eh]
    mov bl, byte ptr [esp + 12h]
    sub ebx, edx
    xor edx, edx
    mov esi, ebx
    xor ebx, ebx
    mov dl, ch
    mov bl, ah
    and ecx, 0ffh
    and eax, 0ffh
    sub ebx, edx
    sub eax, ecx
    test esi, esi
    mov edx, ebx
    jge shiftedRedReady
    xor esi, esi
shiftedRedReady:
    test edx, edx
    jge shiftedGreenReady
    xor edx, edx
shiftedGreenReady:
    test eax, eax
    jge shiftedBlueReady
    xor eax, eax
shiftedBlueReady:
    shl esi, 8
    or esi, edx
    shl esi, 8
    or esi, eax
    mov eax, dword ptr [g_textureWorkBuffer]
    mov dword ptr [eax + ebp * 4], esi
    inc ebp
    cmp ebp, 10000h
    jl subtractShiftedReloadOffset
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    rep movsd
    pop edi
    pop esi
    pop ebp
    pop ebx
    pop ecx
    ret
  }
}


// FUNCTION: SUMO 0x0041b130
// FUNCTION: EDITOR 0x0041b150
__declspec(naked) void SwapTextureChannels(SumoS32 firstIndex, char firstChannel, SumoS32 secondIndex, char secondChannel) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov cl, byte ptr [esp + 8]
    shl cl, 3
    mov edx, dword ptr [g_textureLayers + eax * 4]
    mov al, 10h
    sub al, cl
    mov cl, byte ptr [esp + 10h]
    mov byte ptr [esp + 8], al
    mov al, 10h
    shl cl, 3
    push ebx
    mov ebx, dword ptr [esp + 10h]
    sub al, cl
    push ebp
    push esi
    mov esi, dword ptr [esp + 14h]
    mov byte ptr [esp + 10h], al
    push edi
    mov edi, dword ptr [esp + 14h]
    and esi, 0ffh
    and edi, 0ffh
    xor eax, eax
swapTextureExtractSecond:
    mov ecx, dword ptr [g_textureLayers + ebx * 4]
    add eax, 4
    mov ebp, dword ptr [ecx + eax - 4]
    mov ecx, edi
    shr ebp, cl
    mov ecx, esi
    and ebp, 0ffh
    shl ebp, cl
    mov ecx, dword ptr [g_textureWorkBuffer]
    cmp eax, 40000h
    mov dword ptr [eax + ecx - 4], ebp
    jl swapTextureExtractSecond
    xor eax, eax
swapTextureExtractFirst:
    mov ebp, dword ptr [eax + edx]
    mov ecx, esi
    shr ebp, cl
    mov ecx, edi
    add eax, 4
    and ebp, 0ffh
    shl ebp, cl
    mov ecx, dword ptr [g_textureChannelSwapBuffer]
    cmp eax, 40000h
    mov dword ptr [eax + ecx - 4], ebp
    jl swapTextureExtractFirst
    mov eax, 0ffh
    mov ecx, esi
    shl eax, cl
    mov esi, 0ffffffh
    sub esi, eax
    xor eax, eax
swapTextureMergeFirst:
    mov ecx, dword ptr [eax + edx]
    add eax, 4
    and ecx, esi
    mov dword ptr [eax + edx - 4], ecx
    mov ebp, dword ptr [g_textureWorkBuffer]
    mov ebp, dword ptr [eax + ebp - 4]
    or ebp, ecx
    cmp eax, 40000h
    mov dword ptr [eax + edx - 4], ebp
    jl swapTextureMergeFirst
    mov eax, 0ffh
    mov ecx, edi
    shl eax, cl
    mov edx, 0ffffffh
    sub edx, eax
    xor eax, eax
swapTextureMergeSecond:
    mov ecx, dword ptr [g_textureLayers + ebx * 4]
    add ecx, eax
    mov ebp, dword ptr [ecx]
    and ebp, edx
    mov dword ptr [ecx], ebp
    mov ecx, dword ptr [g_textureLayers + ebx * 4]
    mov esi, dword ptr [g_textureChannelSwapBuffer]
    add ecx, eax
    mov esi, dword ptr [eax + esi]
    mov edi, dword ptr [ecx]
    add eax, 4
    or edi, esi
    cmp eax, 40000h
    mov dword ptr [ecx], edi
    jl swapTextureMergeSecond
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b250
// FUNCTION: EDITOR 0x0041b270
__declspec(naked) SumoS32 ReplicateTextureChannel(SumoS32 planeIndex, char channel) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov cl, byte ptr [esp + 8]
    shl cl, 3
    mov edx, dword ptr [g_textureLayers + eax * 4]
    mov al, 10h
    sub al, cl
    push esi
    mov byte ptr [esp + 8], al
    push edi
    mov ecx, dword ptr [esp + 0ch]
    mov esi, 10000h
    and ecx, 0ffh
  expandNextChannelSample:
    mov eax, dword ptr [edx]
    add edx, 4
    shr eax, cl
    and eax, 0ffh
    mov edi, eax
    shl edi, 8
    or edi, eax
    shl edi, 8
    or edi, eax
    dec esi
    mov dword ptr [edx - 4], edi
    jne expandNextChannelSample
    pop edi
    pop esi
    ret
  }
}


// FUNCTION: SUMO 0x0041b2a0
// FUNCTION: EDITOR 0x0041b2c0
__declspec(naked) void ShadeTextureLayerByChannel(SumoS32 destinationIndex, SumoS32 sourceIndex, char sourceChannel) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov ecx, dword ptr [esp + 8]
    mov dl, byte ptr [esp + 0ch]
    push ebx
    push ebp
    push esi
    mov esi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [g_textureLayers + ecx * 4]
    shl dl, 3
    mov cl, 10h
    push edi
    sub cl, dl
    mov byte ptr [esp + 14h], cl
    mov ecx, dword ptr [esp + 14h]
    mov dword ptr [esp + 14h], 10000h
    and ecx, 0ffh
    sub eax, esi
    mov dword ptr [esp + 18h], eax
    jmp shadeTextureLoad
shadeTextureReloadOffset:
    mov eax, dword ptr [esp + 18h]
shadeTextureLoad:
    mov eax, dword ptr [eax + esi]
    mov edx, dword ptr [esi]
    shr eax, cl
    mov ebp, dword ptr [g_textureColorMap]
    mov dword ptr [esp + 1ch], edx
    xor ebx, ebx
    add esi, 4
    and eax, 0ffh
    shl eax, 8
    mov edi, eax
    xor eax, eax
    mov al, byte ptr [esp + 1eh]
    add eax, edi
    mov bh, byte ptr [eax + ebp]
    xor eax, eax
    mov al, dh
    and edx, 0ffh
    add eax, edi
    add edx, edi
    mov bl, byte ptr [eax + ebp]
    xor eax, eax
    mov al, byte ptr [edx + ebp]
    shl ebx, 8
    or ebx, eax
    mov eax, dword ptr [esp + 14h]
    mov dword ptr [esi - 4], ebx
    dec eax
    mov dword ptr [esp + 14h], eax
    jne shadeTextureReloadOffset
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b340
// FUNCTION: EDITOR 0x0041b360
__declspec(naked) void CopyTextureChannel(SumoS32 destinationIndex, char destinationChannel, SumoS32 sourceIndex, char sourceChannel) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov cl, byte ptr [esp + 8]
    shl cl, 3
    mov edx, dword ptr [g_textureLayers + eax * 4]
    mov al, 10h
    sub al, cl
    mov cl, byte ptr [esp + 10h]
    mov byte ptr [esp + 8], al
    mov al, 10h
    shl cl, 3
    push ebx
    sub al, cl
    mov ecx, dword ptr [esp + 10h]
    push ebp
    push esi
    mov esi, dword ptr [esp + 14h]
    mov byte ptr [esp + 10h], al
    push edi
    mov edi, dword ptr [esp + 14h]
    and ecx, 0ffh
    and edi, 0ffh
    and esi, 0ffh
    lea ebx, dword ptr [g_textureLayers + ecx * 4]
    xor eax, eax
copyTextureChannelToScratch:
    mov ecx, dword ptr [ebx]
    add eax, 4
    mov ebp, dword ptr [eax + ecx - 4]
    mov ecx, edi
    shr ebp, cl
    mov ecx, esi
    and ebp, 0ffh
    shl ebp, cl
    mov ecx, dword ptr [g_textureWorkBuffer]
    cmp eax, 40000h
    mov dword ptr [eax + ecx - 4], ebp
    jl copyTextureChannelToScratch
    mov eax, 0ffh
    mov ecx, esi
    shl eax, cl
    mov esi, 0ffffffh
    sub esi, eax
    xor eax, eax
copyTextureChannelToDestination:
    mov ebp, dword ptr [eax + edx]
    add eax, 4
    and ebp, esi
    mov dword ptr [eax + edx - 4], ebp
    mov edi, dword ptr [g_textureWorkBuffer]
    mov ecx, ebp
    mov edi, dword ptr [eax + edi - 4]
    or edi, ecx
    cmp eax, 40000h
    mov dword ptr [eax + edx - 4], edi
    jl copyTextureChannelToDestination
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b400
// FUNCTION: EDITOR 0x0041b420
__declspec(naked) void MixTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex, SumoS32 amount) {

  __asm {
    mov edx, dword ptr [esp + 0ch]
    mov eax, dword ptr [esp + 4]
    mov ecx, dword ptr [esp + 8]
    push ebx
    mov eax, dword ptr [g_textureLayers + eax * 4]
    push ebp
    mov ebp, dword ptr [g_textureColorMap]
    push esi
    mov esi, dword ptr [g_textureLayers + ecx * 4]
    and edx, 0fffffffeh
    push edi
    mov edi, edx
    shl edx, 7
    mov ebx, 7f00h
    mov ecx, eax
    shl edi, 7
    sub ebx, edx
    add edi, ebp
    add ebp, ebx
    mov dword ptr [esp + 14h], 10000h
mixNextTexturePixel:
    xor edx, edx
    xor ebx, ebx
    mov dl, byte ptr [esi]
    mov bl, byte ptr [eax]
    mov dl, byte ptr [edx + ebp]
    add dl, byte ptr [ebx + edi]
    inc ecx
    inc eax
    inc esi
    mov byte ptr [ecx - 1], dl
    xor edx, edx
    mov dl, byte ptr [esi]
    xor ebx, ebx
    mov bl, byte ptr [eax]
    mov dl, byte ptr [edx + ebp]
    add dl, byte ptr [ebx + edi]
    inc ecx
    inc eax
    inc esi
    mov byte ptr [ecx - 1], dl
    xor edx, edx
    mov dl, byte ptr [esi]
    xor ebx, ebx
    mov bl, byte ptr [eax]
    add ecx, 2
    mov dl, byte ptr [edx + ebp]
    add eax, 2
    add dl, byte ptr [ebx + edi]
    add esi, 2
    mov byte ptr [ecx - 2], dl
    mov edx, dword ptr [esp + 14h]
    dec edx
    mov dword ptr [esp + 14h], edx
    jne mixNextTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b4a0
// FUNCTION: EDITOR 0x0041b4c0
__declspec(naked) void MultiplyTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov edx, dword ptr [esp + 8]
    push ebx
    push ebp
    mov ecx, dword ptr [g_textureLayers + eax * 4]
    mov edx, dword ptr [g_textureLayers + edx * 4]
    push esi
    push edi
    sub edx, ecx
    mov dword ptr [esp + 14h], 10000h
multiplyNextTexturePixel:
    mov eax, dword ptr [ecx]
    xor ebx, ebx
    mov esi, eax
    mov bl, ah
    and eax, 0ffh
    mov edi, ebx
    mov ebp, eax
    mov eax, dword ptr [edx + ecx]
    xor ebx, ebx
    add ecx, 4
    mov bl, ah
    imul ebx, edi
    mov edi, eax
    and eax, 0ffh
    sar esi, 10h
    imul eax, ebp
    sar edi, 10h
    imul edi, esi
    sar edi, 8
    sar ebx, 8
    shl edi, 8
    or ebx, edi
    shl ebx, 8
    sar eax, 8
    or ebx, eax
    mov eax, dword ptr [esp + 14h]
    mov dword ptr [ecx - 4], ebx
    dec eax
    mov dword ptr [esp + 14h], eax
    jne multiplyNextTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}

// FUNCTION: SUMO 0x0041b520
// FUNCTION: EDITOR 0x0041b540
__declspec(naked) void InvertTextureLayerLowBytes(SumoS32 index) {
  __asm {
    push ebp
    mov ebp, esp
    mov eax, dword ptr [ebp + 8]
    push esi
    mov ecx, dword ptr [g_textureLayers + eax * 4]
    mov dword ptr [ebp + 8], ecx
    mov esi, dword ptr [ebp + 8]
    mov ecx, 10000h
invertNextSample:
    xor byte ptr [esi], 0ffh
    add esi, 4
    dec ecx
    jne invertNextSample
    pop esi
    pop ebp
    ret
  }
}


// FUNCTION: SUMO 0x0041b550
// FUNCTION: EDITOR 0x0041b570
__declspec(naked) void AdjustTextureContrast(SumoS32 layerIndex, SumoS32 amount) {

  __asm {
    fild dword ptr [esp + 8]
    mov eax, dword ptr [esp + 4]
    push ebx
    push ebp
    push esi
    mov ebp, dword ptr [g_textureLayers + eax * 4]
    push edi
    fmul qword ptr [g_textureContrastScale]
    mov dword ptr [esp + 14h], 10000h
contrastNextTexturePixel:
    mov ebx, dword ptr [ebp]
    xor ecx, ecx
    mov dword ptr [esp + 18h], ebx
    mov cl, byte ptr [esp + 1ah]
    sub ecx, 80h
    mov dword ptr [esp + 18h], ecx
    fild dword ptr [esp + 18h]
    fld st(1)
    fmulp st(1), st
    call __ftol
    xor edx, edx
    mov esi, eax
    mov dl, bh
    sub edx, 80h
    mov dword ptr [esp + 18h], edx
    fild dword ptr [esp + 18h]
    fld st(1)
    fmulp st(1), st
    call __ftol
    and ebx, 0ffh
    mov edi, eax
    sub ebx, 80h
    mov dword ptr [esp + 18h], ebx
    fild dword ptr [esp + 18h]
    fld st(1)
    fmulp st(1), st
    call __ftol
    cmp esi, 7fh
    jle contrastRedUpperReady
    mov esi, 7fh
contrastRedUpperReady:
    cmp edi, 7fh
    jle contrastGreenUpperReady
    mov edi, 7fh
contrastGreenUpperReady:
    cmp eax, 7fh
    jle contrastBlueUpperReady
    mov eax, 7fh
contrastBlueUpperReady:
    cmp esi, 0ffffff81h
    jge contrastRedLowerReady
    mov esi, 0ffffff81h
contrastRedLowerReady:
    cmp edi, 0ffffff81h
    jge contrastGreenLowerReady
    mov edi, 0ffffff81h
contrastGreenLowerReady:
    cmp eax, 0ffffff81h
    jge contrastBlueLowerReady
    mov eax, 0ffffff81h
contrastBlueLowerReady:
    add edi, 80h
    add esi, 80h
    shl edi, 8
    shl esi, 10h
    or edi, esi
    add eax, 80h
    or edi, eax
    mov eax, dword ptr [esp + 14h]
    mov dword ptr [ebp], edi
    add ebp, 4
    dec eax
    mov dword ptr [esp + 14h], eax
    jne contrastNextTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    fstp st
    ret
  }
}


// FUNCTION: SUMO 0x0041b650
// FUNCTION: EDITOR 0x0041b670
__declspec(naked) void ApplyTextureColorMap(SumoS32 layerIndex, SumoS32 mapBank) {

  __asm {
    mov eax, dword ptr [esp + 4]
    push ebx
    push ebp
    push esi
    mov esi, dword ptr [esp + 14h]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov ecx, 10000h
    shl esi, 8
mapNextTexturePixel:
    mov eax, dword ptr [edi]
    mov ebp, dword ptr [g_textureColorMap]
    mov dword ptr [esp + 14h], eax
    xor edx, edx
    mov dl, byte ptr [esp + 16h]
    xor ebx, ebx
    add edx, ebp
    add edi, 4
    mov bh, byte ptr [edx + esi]
    xor edx, edx
    mov dl, ah
    and eax, 0ffh
    add edx, ebp
    add eax, ebp
    mov bl, byte ptr [edx + esi]
    xor edx, edx
    mov dl, byte ptr [eax + esi]
    shl ebx, 8
    or ebx, edx
    dec ecx
    mov dword ptr [edi - 4], ebx
    jne mapNextTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b6b0
// FUNCTION: EDITOR 0x0041b6d0
__declspec(naked) void ApplyTextureCosineWave(SumoS32 layerIndex, char channel, SumoS32 frequency) {

  __asm {
    mov cl, byte ptr [esp + 8]
    mov eax, dword ptr [esp + 4]
    shl cl, 3
    mov dl, 10h
    push ebx
    fild dword ptr [esp + 10h]
    sub dl, cl
    push ebp
    mov byte ptr [esp + 0ch], dl
    push esi
    mov ebx, dword ptr [esp + 10h]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    and ebx, 0ffh
    fmul qword ptr [g_textureTau]
    mov eax, 0ffh
    mov ecx, ebx
    shl eax, cl
    mov ebp, 0ffffffh
    mov dword ptr [esp + 14h], 10000h
    fmul qword ptr [g_textureInvSize]
    sub ebp, eax
cosineNextTexturePixel:
    mov esi, dword ptr [edi]
    mov ecx, ebx
    mov edx, esi
    shr edx, cl
    and edx, 0ffh
    mov dword ptr [esp + 18h], edx
    fild dword ptr [esp + 18h]
    fmul st, st(1)
    fcos
    fmul qword ptr [g_textureWaveAmplitude]
    fsubr qword ptr [g_textureWaveAmplitude]
    call __ftol
    mov ecx, ebx
    and esi, ebp
    shl eax, cl
    add edi, 4
    or esi, eax
    mov eax, dword ptr [esp + 14h]
    mov dword ptr [edi - 4], esi
    dec eax
    mov dword ptr [esp + 14h], eax
    jne cosineNextTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    fstp st
    ret
  }
}


// FUNCTION: SUMO 0x0041b750
// FUNCTION: EDITOR 0x0041b770
__declspec(naked) void RemapTextureChannelRange(SumoS32 layerIndex, char channel, SumoS32 rangeStart, SumoS32 rangeEnd) {

  __asm {
    mov cl, byte ptr [esp + 8]
    mov eax, dword ptr [esp + 4]
    push ebx
    push ebp
    push esi
    mov dl, 10h
    shl cl, 3
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [esp + 20h]
    sub dl, cl
    mov ecx, dword ptr [esp + 1ch]
    mov byte ptr [esp + 18h], dl
    sub eax, ecx
    mov dword ptr [esp + 14h], eax
    jne remapTextureRangeReady
    mov dword ptr [esp + 14h], 1
remapTextureRangeReady:
    mov ebx, dword ptr [esp + 18h]
    mov edx, 0ffh
    fild dword ptr [esp + 14h]
    and ebx, 0ffh
    mov ebp, 0ffffffh
    mov ecx, ebx
    shl edx, cl
    fmul qword ptr [g_textureInvSize]
    fild dword ptr [esp + 1ch]
    sub ebp, edx
    mov dword ptr [esp + 1ch], 10000h
remapNextTexturePixel:
    mov esi, dword ptr [edi]
    mov ecx, ebx
    mov eax, esi
    shr eax, cl
    and eax, 0ffh
    mov dword ptr [esp + 14h], eax
    fild dword ptr [esp + 14h]
    fmul st, st(2)
    fld st(1)
    fadd st, st(1)
    call __ftol
    mov ecx, ebx
    and esi, ebp
    shl eax, cl
    add edi, 4
    fstp st
    or eax, esi
    mov dword ptr [edi - 4], eax
    mov eax, dword ptr [esp + 1ch]
    dec eax
    mov dword ptr [esp + 1ch], eax
    jne remapNextTexturePixel
    pop edi
    pop esi
    fstp st
    pop ebp
    pop ebx
    fstp st
    ret
  }
}


// FUNCTION: SUMO 0x0041b800
// FUNCTION: EDITOR 0x0041b820
__declspec(naked) SumoU32 *ExpandTextureBitmap(SumoS32 planeIndex, SumoU8 *bits, SumoU32 zeroValue, SumoU32 oneValue) {

  __asm {
    mov eax, dword ptr [esp + 4]
    push ebx
    push ebp
    push esi
    mov ebx, dword ptr [g_textureLayers + eax * 4]
    push edi
    xor ecx, ecx
    xor edi, edi
decodeNextByte:
    mov edx, dword ptr [esp + 18h]
    lea eax, dword ptr [ebx + ecx * 4]
    mov esi, 8
    mov dl, byte ptr [edi + edx]
decodeNextBit:
    mov ebp, dword ptr [esp + 1ch]
    test dl, 1
    je storeDecodedBit
    mov ebp, dword ptr [esp + 20h]
storeDecodedBit:
    mov dword ptr [eax], ebp
    inc ecx
    add eax, 4
    shr dl, 1
    dec esi
    jne decodeNextBit
    inc edi
    cmp edi, 2000h
    jl decodeNextByte
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041b850
// FUNCTION: EDITOR 0x0041b870
__declspec(naked) SumoS32 BlurTextureLayer(SumoS32 layerIndex, SumoS32 passCount) {

  __asm {
    sub esp, 2ch
    mov eax, dword ptr [esp + 30h]
    mov edx, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [esp + 34h]
    test eax, eax
    mov dword ptr [esp + 4], edx
    jle blurTextureReturn
    push ebx
    push ebp
    push esi
    push edi
    mov dword ptr [esp + 30h], eax
blurTextureNextPass:
    xor ebx, ebx
    mov eax, 1
    mov dword ptr [esp + 1ch], ebx
    mov dword ptr [esp + 2ch], eax
    mov dword ptr [esp + 10h], ebx
    mov edi, edx
    jmp blurTextureRowSetup
blurTextureReloadLayerForRow:
    mov edx, dword ptr [esp + 14h]
blurTextureRowSetup:
    lea ecx, dword ptr [eax - 2]
    and eax, 0ffh
    and ecx, 0ffh
    mov esi, 1
    shl ecx, 0ah
    shl eax, 0ah
    add ecx, edx
    add eax, edx
    mov dword ptr [esp + 28h], edi
    mov dword ptr [esp + 24h], ecx
    mov dword ptr [esp + 20h], eax
    jmp blurTexturePixel
blurTextureReloadLayerForPixel:
    mov edx, dword ptr [esp + 14h]
    mov ebx, dword ptr [esp + 10h]
blurTexturePixel:
    mov ecx, dword ptr [ecx]
    lea ebp, dword ptr [esi - 2]
    mov dword ptr [esp + 44h], ecx
    mov ecx, esi
    and ebp, 0ffh
    and ecx, 0ffh
    add ebp, ebx
    add ecx, ebx
    xor ebx, ebx
    mov eax, dword ptr [eax]
    mov ebp, dword ptr [edx + ebp * 4]
    mov ecx, dword ptr [edx + ecx * 4]
    mov edx, dword ptr [edi]
    mov dword ptr [esp + 34h], ecx
    mov bl, byte ptr [esp + 36h]
    mov dword ptr [esp + 40h], edx
    xor edx, edx
    mov dword ptr [esp + 18h], ebp
    mov dl, byte ptr [esp + 42h]
    mov dword ptr [esp + 38h], eax
    lea ebp, dword ptr [ebx + edx * 4]
    xor edx, edx
    mov dl, byte ptr [esp + 46h]
    xor ebx, ebx
    add ebp, edx
    xor edx, edx
    mov dl, byte ptr [esp + 1ah]
    mov bl, ch
    add ebp, edx
    xor edx, edx
    mov dl, byte ptr [esp + 3ah]
    and ecx, 0ffh
    add ebp, edx
    xor edx, edx
    mov dl, byte ptr [esp + 41h]
    sar ebp, 3
    lea edi, dword ptr [ebx + edx * 4]
    xor edx, edx
    mov dl, byte ptr [esp + 45h]
    xor ebx, ebx
    add edi, edx
    mov edx, dword ptr [esp + 18h]
    mov bl, dh
    and edx, 0ffh
    add edi, ebx
    xor ebx, ebx
    mov bl, ah
    and eax, 0ffh
    add edi, ebx
    shl ebp, 8
    sar edi, 3
    or ebp, edi
    mov edi, dword ptr [esp + 40h]
    and edi, 0ffh
    shl ebp, 8
    lea edi, dword ptr [ecx + edi * 4]
    mov ecx, dword ptr [esp + 44h]
    and ecx, 0ffh
    add edi, ecx
    mov ecx, dword ptr [g_textureWorkBuffer]
    add edi, edx
    add edi, eax
    mov eax, dword ptr [esp + 1ch]
    sar edi, 3
    or ebp, edi
    mov edi, dword ptr [esp + 28h]
    mov dword ptr [ecx + eax * 4], ebp
    mov ecx, dword ptr [esp + 24h]
    inc eax
    add ecx, 4
    mov dword ptr [esp + 1ch], eax
    mov eax, dword ptr [esp + 20h]
    add eax, 4
    add edi, 4
    inc esi
    mov dword ptr [esp + 20h], eax
    mov dword ptr [esp + 24h], ecx
    mov dword ptr [esp + 28h], edi
    lea edx, dword ptr [esi - 1]
    cmp edx, 100h
    jl blurTextureReloadLayerForPixel
    mov ebx, dword ptr [esp + 10h]
    mov eax, dword ptr [esp + 2ch]
    add ebx, 100h
    inc eax
    mov dword ptr [esp + 10h], ebx
    mov dword ptr [esp + 2ch], eax
    lea ecx, dword ptr [eax - 1]
    cmp ecx, 100h
    jl blurTextureReloadLayerForRow
    mov edx, dword ptr [esp + 14h]
    mov eax, dword ptr [esp + 30h]
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    mov edi, edx
    dec eax
    rep movsd
    mov dword ptr [esp + 30h], eax
    jnz blurTextureNextPass
    pop edi
    pop esi
    pop ebp
    pop ebx
blurTextureReturn:
    add esp, 2ch
    ret
  }
}


// FUNCTION: SUMO 0x0041ba20
// FUNCTION: EDITOR 0x0041ba40
__declspec(naked) void DirectionalBlurTextureLayer(SumoS32 destinationIndex, SumoS32 directionIndex, char directionChannel, SumoS32 sampleCount) {

  __asm {
    sub esp, 18h
    mov ecx, dword ptr [esp + 24h]
    mov eax, dword ptr [esp + 1ch]
    push ebx
    mov ebx, 2
    sub ebx, ecx
    mov ecx, dword ptr [esp + 24h]
    push ebp
    push esi
    mov edx, dword ptr [g_textureLayers + ecx * 4]
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov dword ptr [esp + 18h], edx
    shl ebx, 3
    xor ebp, ebp
    mov dword ptr [esp + 14h], ebp
    mov dword ptr [esp + 10h], ebp
directionalBlurNextRow:
    mov esi, dword ptr [esp + 38h]
    mov dword ptr [esp + 30h], 0
    jmp directionalBlurPixelSetup
directionalBlurReloadCount:
    mov esi, dword ptr [esp + 38h]
directionalBlurPixelSetup:
    mov eax, dword ptr [esp + 18h]
    mov ecx, ebx
    fld dword ptr [g_vectorZero]
    mov edx, dword ptr [eax + ebp * 4]
    fld dword ptr [g_vectorZero]
    fld dword ptr [g_vectorZero]
    shr edx, cl
    and edx, 0ffh
    mov dword ptr [esp + 34h], edx
    fild dword ptr [esp + 34h]
    test esi, esi
    fmul qword ptr [g_textureRadiansPerPixel]
    fld st
    fsin
    fstp dword ptr [esp + 20h]
    fcos
    fstp dword ptr [esp + 1ch]
    jle directionalBlurAverage
    fild dword ptr [esp + 10h]
    fild dword ptr [esp + 30h]
    mov dword ptr [esp + 34h], 0
directionalBlurNextSample:
    fild dword ptr [esp + 34h]
    fld st
    fmul dword ptr [esp + 1ch]
    fadd st, st(3)
    call __ftol
    fmul dword ptr [esp + 20h]
    mov ebp, eax
    and ebp, 0ffh
    fadd st, st(1)
    shl ebp, 8
    call __ftol
    and eax, 0ffh
    add ebp, eax
    mov eax, dword ptr [edi + ebp * 4]
    mov ecx, eax
    mov edx, eax
    sar ecx, 10h
    mov dword ptr [esp + 24h], ecx
    mov ecx, dword ptr [esp + 34h]
    fild dword ptr [esp + 24h]
    sar edx, 8
    and edx, 0ffh
    and eax, 0ffh
    faddp st(3), st
    mov dword ptr [esp + 24h], edx
    add ecx, 2
    fild dword ptr [esp + 24h]
    mov dword ptr [esp + 24h], eax
    dec esi
    mov dword ptr [esp + 34h], ecx
    faddp st(4), st
    fild dword ptr [esp + 24h]
    faddp st(5), st
    jnz directionalBlurNextSample
    mov ebp, dword ptr [esp + 14h]
    fstp st
    fstp st
directionalBlurAverage:
    fild dword ptr [esp + 38h]
    fstp dword ptr [esp + 34h]
    fdiv dword ptr [esp + 34h]
    call __ftol
    fdiv dword ptr [esp + 34h]
    mov esi, eax
    shl esi, 8
    call __ftol
    fdiv dword ptr [esp + 34h]
    or esi, eax
    shl esi, 8
    call __ftol
    or esi, eax
    mov eax, dword ptr [g_textureWorkBuffer]
    mov dword ptr [eax + ebp * 4], esi
    mov eax, dword ptr [esp + 30h]
    inc ebp
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 14h], ebp
    mov dword ptr [esp + 30h], eax
    jl directionalBlurReloadCount
    mov eax, dword ptr [esp + 10h]
    inc eax
    cmp eax, 100h
    mov dword ptr [esp + 10h], eax
    jl directionalBlurNextRow
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    rep movsd
    mov ecx, dword ptr [esp + 2ch]
    push 2
    push ecx
    call BlurTextureLayer
    add esp, 8
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 18h
    ret
  }
}


// FUNCTION: SUMO 0x0041bbd0
// FUNCTION: EDITOR 0x0041bbf0
__declspec(naked) void AddTextureLayersSaturated(SumoS32 destinationIndex, SumoS32 sourceIndex) {

  __asm {
    mov eax, dword ptr [esp + 4]
    mov ecx, dword ptr [esp + 8]
    push ebx
    push ebp
    push esi
    push edi
    mov edi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [g_textureLayers + ecx * 4]
    mov ebp, eax
    mov dword ptr [esp + 14h], 10000h
    sub ebp, edi
addNextSaturatedTexturePixel:
    mov ecx, dword ptr [edi]
    mov eax, dword ptr [edi + ebp]
    mov esi, eax
    mov edx, ecx
    sar esi, 10h
    sar edx, 10h
    add esi, edx
    xor edx, edx
    xor ebx, ebx
    mov dl, ah
    mov bl, ch
    and eax, 0ffh
    and ecx, 0ffh
    add edx, ebx
    add eax, ecx
    cmp esi, 0ffh
    jle saturatedRedReady
    mov esi, 0ffh
saturatedRedReady:
    cmp edx, 0ffh
    jle saturatedGreenReady
    mov edx, 0ffh
saturatedGreenReady:
    cmp eax, 0ffh
    jle saturatedBlueReady
    mov eax, 0ffh
saturatedBlueReady:
    shl esi, 8
    or esi, edx
    add edi, 4
    shl esi, 8
    or esi, eax
    mov eax, dword ptr [esp + 14h]
    mov dword ptr [edi - 4], esi
    dec eax
    mov dword ptr [esp + 14h], eax
    jne addNextSaturatedTexturePixel
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret
  }
}


// FUNCTION: SUMO 0x0041bc70
// FUNCTION: EDITOR 0x0041bc90
__declspec(naked) void MaxTextureLayers(SumoS32 destinationIndex, SumoS32 sourceIndex) {

  __asm {
    sub esp, 8
    mov eax, dword ptr [esp + 0ch]
    mov ecx, dword ptr [esp + 10h]
    push ebx
    push ebp
    mov ecx, dword ptr [g_textureLayers + ecx * 4]
    push esi
    mov esi, dword ptr [g_textureLayers + eax * 4]
    push edi
    sub ecx, esi
    mov dword ptr [esp + 1ch], 10000h
    mov dword ptr [esp + 20h], ecx
    jmp maxTextureLoad
maxTextureReloadOffset:
    mov ecx, dword ptr [esp + 20h]
maxTextureLoad:
    mov eax, dword ptr [esi]
    xor edx, edx
    mov dword ptr [esp + 10h], eax
    mov ecx, dword ptr [ecx + esi]
    mov dl, byte ptr [esp + 12h]
    mov dword ptr [esp + 14h], ecx
    mov edi, edx
    xor edx, edx
    mov dl, ah
    and eax, 0ffh
    mov ebp, edx
    mov ebx, eax
    xor edx, edx
    xor eax, eax
    mov dl, byte ptr [esp + 16h]
    mov al, ch
    and ecx, 0ffh
    cmp edi, edx
    jle maxTextureRedReady
    mov edx, edi
maxTextureRedReady:
    cmp ebp, eax
    jle maxTextureGreenReady
    mov eax, ebp
maxTextureGreenReady:
    cmp ebx, ecx
    jle maxTextureBlueReady
    mov ecx, ebx
maxTextureBlueReady:
    shl edx, 8
    or edx, eax
    mov eax, dword ptr [esp + 1ch]
    shl edx, 8
    or edx, ecx
    mov dword ptr [esi], edx
    add esi, 4
    dec eax
    mov dword ptr [esp + 1ch], eax
    jne maxTextureReloadOffset
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 8
    ret
  }
}


// FUNCTION: SUMO 0x0041c160
// FUNCTION: EDITOR 0x0041c180
__declspec(naked) void ApplyTextureGradient(SumoS32 layerIndex, SumoS8 channel, SumoS32 redLow, SumoS32 redHigh, SumoS32 greenLow, SumoS32 greenHigh, SumoS32 blueLow, SumoS32 blueHigh) {

  __asm {
    sub esp, 408h
    mov eax, dword ptr [esp + 410h]
    push ebx
    mov ebx, dword ptr [esp + 418h]
    push ebp
    push esi
    mov ecx, dword ptr [esp + 42ch]
    mov edx, dword ptr [esp + 428h]
    mov esi, 2
    sub esi, eax
    mov eax, dword ptr [esp + 424h]
    sub eax, ebx
    sub ecx, edx
    mov edx, dword ptr [esp + 434h]
    mov dword ptr [esp + 0ch], eax
    fild dword ptr [esp + 0ch]
    fild dword ptr [esp + 420h]
    mov eax, dword ptr [esp + 430h]
    push edi
    mov dword ptr [esp + 10h], ecx
    xor edi, edi
    fild dword ptr [esp + 10h]
    fild dword ptr [esp + 42ch]
    shl esi, 3
    sub edx, eax
    mov dword ptr [esp + 14h], edi
    mov dword ptr [esp + 10h], edx
    lea ebx, dword ptr [esp + 18h]
    fild dword ptr [esp + 10h]
    fild dword ptr [esp + 434h]
gradientBuildNext:
    fild dword ptr [esp + 14h]
    fld st
    fmul st, st(7)
    fmul dword ptr [g_textureBlendScale]
    fadd st, st(6)
    call __ftol
    fld st(4)
    fmul st, st(1)
    mov ebp, eax
    shl ebp, 8
    fmul dword ptr [g_textureBlendScale]
    fadd st, st(4)
    call __ftol
    fld st(2)
    fmul st, st(1)
    or ebp, eax
    shl ebp, 8
    fmul dword ptr [g_textureBlendScale]
    fadd st, st(2)
    call __ftol
    or ebp, eax
    inc edi
    mov dword ptr [ebx], ebp
    add ebx, 4
    cmp edi, 100h
    mov dword ptr [esp + 14h], edi
    fstp st
    jl gradientBuildNext
    fstp st
    fstp st
    mov edi, dword ptr [esp + 41ch]
    xor eax, eax
    fstp st
    fstp st
    fstp st
    fstp st
gradientMapNext:
    mov ecx, dword ptr [g_textureLayers + edi * 4]
    mov ebx, dword ptr [ecx + eax]
    lea edx, dword ptr [ecx + eax]
    mov ecx, esi
    add eax, 4
    shr ebx, cl
    and ebx, 0ffh
    cmp eax, 40000h
    mov ecx, dword ptr [esp + ebx * 4 + 18h]
    mov dword ptr [edx], ecx
    jl gradientMapNext
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 408h
    ret
  }
}


// FUNCTION: SUMO 0x0041c280
// FUNCTION: EDITOR 0x0041c2a0
__declspec(naked) void BlendTextureLayersByMask(SumoS32 destinationIndex, SumoS32 sourceIndex, SumoS32 maskIndex, SumoS8 maskChannel) {

  __asm {
    sub esp, 10h
    mov eax, dword ptr [esp + 14h]
    mov ecx, dword ptr [esp + 18h]
    push ebx
    push ebp
    mov edx, dword ptr [g_textureLayers + ecx * 4]
    mov ecx, dword ptr [esp + 28h]
    push esi
    mov esi, dword ptr [g_textureLayers + eax * 4]
    mov eax, dword ptr [esp + 28h]
    push edi
    mov edi, 2
    mov dword ptr [esp + 2ch], 10000h
    mov eax, dword ptr [g_textureLayers + eax * 4]
    sub edi, ecx
    shl edi, 3
    sub eax, edx
    sub edx, esi
    mov dword ptr [esp + 10h], eax
    mov dword ptr [esp + 30h], edx
    jmp maskBlendLoad
maskBlendReloadOffsets:
    mov edx, dword ptr [esp + 30h]
    mov eax, dword ptr [esp + 10h]
maskBlendLoad:
    add edx, esi
    mov ecx, edi
    mov eax, dword ptr [edx + eax]
    mov ebx, dword ptr [edx]
    shr eax, cl
    mov ecx, 0ffh
    xor edx, edx
    mov dword ptr [esp + 18h], ebx
    and eax, 0ffh
    sub ecx, eax
    mov eax, dword ptr [esi]
    mov dword ptr [esp + 24h], eax
    mov dword ptr [esp + 14h], ecx
    mov dl, byte ptr [esp + 26h]
    xor ecx, ecx
    fild dword ptr [esp + 14h]
    mov ebp, edx
    xor edx, edx
    mov dl, byte ptr [esp + 1ah]
    mov dword ptr [esp + 1ch], ebp
    sub edx, ebp
    mov cl, ah
    mov dword ptr [esp + 18h], edx
    and eax, 0ffh
    fild dword ptr [esp + 18h]
    mov dword ptr [esp + 24h], ecx
    mov dword ptr [esp + 28h], eax
    fmul st, st(1)
    fmul dword ptr [g_textureBlendScale]
    fiadd dword ptr [esp + 1ch]
    call __ftol
    mov edx, dword ptr [esp + 24h]
    mov ebp, eax
    xor eax, eax
    mov al, bh
    sub eax, edx
    mov dword ptr [esp + 1ch], eax
    fild dword ptr [esp + 1ch]
    shl ebp, 8
    fmul st, st(1)
    fmul dword ptr [g_textureBlendScale]
    fiadd dword ptr [esp + 24h]
    call __ftol
    or ebp, eax
    mov eax, dword ptr [esp + 28h]
    and ebx, 0ffh
    sub ebx, eax
    mov dword ptr [esp + 24h], ebx
    fild dword ptr [esp + 24h]
    shl ebp, 8
    fmul st, st(1)
    fmul dword ptr [g_textureBlendScale]
    fiadd dword ptr [esp + 28h]
    call __ftol
    or ebp, eax
    mov eax, dword ptr [esp + 2ch]
    mov dword ptr [esi], ebp
    add esi, 4
    dec eax
    fstp st
    mov dword ptr [esp + 2ch], eax
    jne maskBlendReloadOffsets
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 10h
    ret
  }
}

// FUNCTION: SUMO 0x0041c3b0
// FUNCTION: EDITOR 0x0041c3d0
__declspec(naked) void EmbossTextureLayer(SumoS32 layerIndex) {
  __asm {
    sub esp, 20h
    push ebx
    push ebp
    xor ecx, ecx
    push esi
    push edi
    mov byte ptr [esp + 10h], 0ffh
    mov byte ptr [esp + 11h], cl
    mov byte ptr [esp + 12h], 1
    mov dword ptr [esp + 18h], ecx
    mov dword ptr [esp + 28h], ecx
embossNextRow:
    mov eax, 1
    mov dword ptr [esp + 14h], ecx
    mov dword ptr [esp + 24h], eax
embossNextPixel:
    mov esi, dword ptr [esp + 34h]
    xor edx, edx
    mov dword ptr [esp + 1ch], ecx
    xor ebp, ebp
    mov esi, dword ptr [g_textureLayers + esi * 4]
    mov dword ptr [esp + 20h], ecx
    mov dword ptr [esp + 2ch], esi
embossNextKernelRow:
    mov esi, dword ptr [esp + 18h]
    lea edi, dword ptr [esi + ecx - 1]
    mov ecx, dword ptr [esp + 14h]
    and edi, 0ffh
    shl edi, 8
    dec ecx
embossNextKernelColumn:
    lea eax, dword ptr [esp + eax + 10h]
    mov ebx, dword ptr [esp + 2ch]
    movsx esi, byte ptr [eax + ecx]
    mov eax, ecx
    and eax, 0ffh
    add eax, edi
    mov eax, dword ptr [ebx + eax * 4]
    mov ebx, eax
    shr ebx, 10h
    imul ebx, esi
    add ebp, ebx
    xor ebx, ebx
    mov bl, ah
    and eax, 0ffh
    imul ebx, esi
    imul eax, esi
    mov esi, dword ptr [esp + 1ch]
    add edx, ebx
    add esi, eax
    mov eax, dword ptr [esp + 24h]
    inc ecx
    mov dword ptr [esp + 1ch], esi
    lea ebx, dword ptr [eax + ecx]
    cmp ebx, 3
    jl embossNextKernelColumn
    mov ecx, dword ptr [esp + 20h]
    inc ecx
    cmp ecx, 3
    mov dword ptr [esp + 20h], ecx
    jl embossNextKernelRow
    add ebp, 80h
    add edx, 80h
    add esi, 80h
    cmp ebp, 0ffh
    jle embossRedMaximumReady
    mov ebp, 0ffh
embossRedMaximumReady:
    cmp edx, 0ffh
    jle embossGreenMaximumReady
    mov edx, 0ffh
embossGreenMaximumReady:
    cmp esi, 0ffh
    jle embossBlueMaximumReady
    mov esi, 0ffh
embossBlueMaximumReady:
    xor ecx, ecx
    cmp ebp, ecx
    jge embossRedReady
    xor ebp, ebp
embossRedReady:
    cmp edx, ecx
    jge embossGreenReady
    xor edx, edx
embossGreenReady:
    cmp esi, ecx
    jge embossBlueReady
    xor esi, esi
embossBlueReady:
    shl ebp, 8
    or ebp, edx
    mov edx, dword ptr [esp + 28h]
    shl ebp, 8
    mov ebx, dword ptr [g_textureWorkBuffer]
    or ebp, esi
    mov esi, dword ptr [esp + 14h]
    lea edi, dword ptr [edx + esi]
    inc esi
    dec eax
    mov dword ptr [esp + 14h], esi
    cmp eax, 0ffffff01h
    mov dword ptr [ebx + edi * 4], ebp
    mov dword ptr [esp + 24h], eax
    jg embossNextPixel
    mov edi, dword ptr [esp + 18h]
    add edx, 100h
    inc edi
    cmp edx, 10000h
    mov dword ptr [esp + 18h], edi
    mov dword ptr [esp + 28h], edx
    jl embossNextRow
    mov edx, dword ptr [esp + 34h]
    mov esi, dword ptr [g_textureWorkBuffer]
    mov ecx, 10000h
    mov edi, dword ptr [g_textureLayers + edx * 4]
    rep movsd
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 20h
    ret
  }
}
