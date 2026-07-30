#ifndef SUMOTORI_GAME_AUDIO_XM_ADAPTER_H
#define SUMOTORI_GAME_AUDIO_XM_ADAPTER_H

#include "game_audio_tracker.h"

typedef struct GameAudioOwnedBlock GameAudioOwnedBlock;


struct GameAudioOwnedBlock {
  char flag;
  SumoU8 unknown01[0x0f];
  SumoS32 releaseValue;
  SumoS32 userValue;
};

typedef char
    GameAudioOwnedBlockSizeCheck[sizeof(GameAudioOwnedBlock) == 0x18 ? 1 : -1];

SumoS32 InvokeGameAudioBlockTail(SumoS32 first, SumoS32 second,
                                 GameAudioOwnedBlock *block);
SumoS32 InvokeGameAudioBlockHead(GameAudioOwnedBlock *block, SumoS32 second,
                                 SumoS32 third);
SumoS32 ReleaseGameAudioOwnedBlock(GameAudioOwnedBlock *block);

void GameAudioParsedTick(GameAudioParsedModule *module);

extern GameAudioParsedSample g_gameAudioEmptySample;
extern const char g_gameAudioXmSignature[];

#endif
