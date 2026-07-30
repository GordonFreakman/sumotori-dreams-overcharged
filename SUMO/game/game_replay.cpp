#include "game_replay.h"
#include "game_input.h"
#include "game_runtime.h"

#include "assert.h"
#include "decomp.h"

#include <new>
#include <stdio.h>
#include <string.h>

extern const char g_gameScreenshotReadMode[];

DECOMP_SIZE_ASSERT(ReplayWordVector, 0x0c);
DECOMP_SIZE_ASSERT(ReplayStream, 0x18);

// FUNCTION: SUMO 0x0040d465
// FUNCTION: EDITOR 0x0040d487
void ReplayStream::ReadHeader(char *filename) {
  FILE *stream = fopen(filename, g_gameScreenshotReadMode);
  header = 0;
  if (stream != 0) {
    SumoS32 value;
    fread(&value, 1, sizeof(value), stream);
    header = value;
    fclose(stream);
  }
}

// FUNCTION: SUMO 0x0040d4a6
// FUNCTION: EDITOR 0x0040d4c8
void ReplayWriteBoundary() {
  if (g_replayRecording) {
    *g_replayStream.cursor = 4;
    ++g_replayStream.cursor;
  }
}


// FUNCTION: SUMO 0x0040d4c1
// FUNCTION: EDITOR 0x0040d4e3
void ReplayRecordCommand(SumoS32 first, SumoS32 second, SumoS32 third,
                         SumoS32 fourth)
{

  if ((g_gameMode == 1 || g_gameMode == 3) && g_replayRecording) {
    *g_replayStream.cursor = 7;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = first;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = second;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = third;
    ++g_replayStream.cursor;
    *g_replayStream.cursor = fourth;
    ++g_replayStream.cursor;
  }
}


// FUNCTION: SUMO 0x0040d59d
// FUNCTION: EDITOR 0x0040d5bf
void ReplayStream::AppendToFile(char *filename)
{

  if (header != 0) {
    // STRING: SUMO 0x0042c798
    // STRING: EDITOR 0x0042c798
    FILE *stream = fopen(filename, "ab");
    ftell(stream);
    fwrite(&words[0], 1, (cursor - &words[0]) * sizeof(SumoU32), stream);
    fclose(stream);
  }
}

// FUNCTION: SUMO 0x0040d5f9
// FUNCTION: EDITOR 0x0040d61b
ReplayStream::~ReplayStream() {}

// FUNCTION: SUMO 0x0040d601
// FUNCTION: EDITOR 0x0040d623
void StopReplayRecording() {
  // STRING: SUMO 0x0042c79c
  // STRING: EDITOR 0x0042c79c
  g_replayStream.AppendToFile("out.dat");
  g_replayStream.cursor = g_replayStream.limit;
  g_replayRecording = false;
}

// FUNCTION: SUMO 0x0040d65f
// FUNCTION: EDITOR 0x0040d681
void ReplayStream::EnsureSpace(SumoU32 additionalWords) {
  SumoU32 cursorOffset = cursor - &words[0];
  SumoU32 requiredSize = cursorOffset + additionalWords;
  if (words.Size() < requiredSize) {
    words.Resize(requiredSize);
    cursor = &words[0] + cursorOffset;
    limit = 0;
  }
}

// FUNCTION: SUMO 0x0040d6ab
// FUNCTION: EDITOR 0x0040d6cd
void ReplayStream::LoadFile(char *filename) {
  FILE *stream = fopen(filename, g_gameScreenshotReadMode);
  fseek(stream, 0, SEEK_END);
  SumoS32 fileSize = ftell(stream);
  fseek(stream, 0, SEEK_SET);

  words.Resize(fileSize / sizeof(SumoU32));
  fread(&words[0], 1, fileSize, stream);
  fclose(stream);

  cursor = &words[0];
  limit = cursor + fileSize / sizeof(SumoU32);
}

// FUNCTION: SUMO 0x0040d729
// FUNCTION: EDITOR 0x0040d74b
void ReplayStream::Reset() {
  words.Clear();
  words.Resize(0x40000);
  cursor = &words[0];
  limit = 0;
  EnsureSpace(0x10000);
  header = 0;
}

// FUNCTION: SUMO 0x0040d763
// FUNCTION: EDITOR 0x0040d785
ReplayStream::ReplayStream() { Reset(); }

// FUNCTION: SUMO 0x0040d77a
// FUNCTION: EDITOR 0x0040d79c
void StartReplayRecording() {
  g_replayStream.Reset();
  g_replayRecording = true;
  g_replayStream.ReadHeader("out.dat");
  *g_replayStream.cursor = 4;
  ++g_replayStream.cursor;
}

// GLOBAL: SUMO 0x00c06064
// GLOBAL: EDITOR 0x00c06884
bool g_replayRecording;

// GLOBAL: SUMO 0x00c0602c
// GLOBAL: EDITOR 0x00c0684c
SumoS32 g_gameMode;

// GLOBAL: SUMO 0x00c0601c
// GLOBAL: EDITOR 0x00c0683c
SumoS32 g_gameReplayFrame;
