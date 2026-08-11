#ifndef SUMO_GAME_REPLAY_H
#define SUMO_GAME_REPLAY_H

#include "types.h"

#include <stdlib.h>

class ReplayWordVector {
public:
  ReplayWordVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~ReplayWordVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  SumoU32 &operator[](SumoU32 index);
  void Grow();
  void Resize(SumoU32 size);
  void Clear() { m_end = m_begin; }
  SumoU32 Size() const { return m_end - m_begin; }

private:
  SumoU32 *m_begin;
  SumoU32 *m_end;
  SumoU32 *m_capacity;
};

class ReplayStream {
public:
  ReplayStream();
  ~ReplayStream();

  void ReadHeader(char *filename);
  void AppendToFile(char *filename);
  void LoadFile(char *filename);
  void EnsureSpace(SumoU32 additionalWords);
  void Reset();

  SumoS32 header;
  ReplayWordVector words;
  SumoU32 *cursor;
  SumoU32 *limit;
};

extern ReplayStream g_replayStream;
extern ReplayStream g_replayPlaybackStream;
extern bool g_replayRecording;
extern SumoS32 g_gameMode;

void ReplayWriteBoundary();
void ReplayRecordCommand(SumoS32 first, SumoS32 second, SumoS32 third,
                         SumoS32 fourth);
void StopReplayRecording();
void StartReplayRecording();
SumoS32 UpdateGameReplay();
SumoS32 UpdateGameReplay();

#endif
