#ifndef SUMO_CONTAINERS_H
#define SUMO_CONTAINERS_H

#include <stdlib.h>

#include "types.h"

class U32Vector {
public:
  U32Vector() {
    m_begin = 0;
    m_end = 0;
    m_capacity = 0;
  }

  // FUNCTION: SUMO 0x00404f7a
  // FUNCTION: EDITOR 0x00404f9c
  ~U32Vector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  SumoU32 &operator[](SumoU32 index);
  void Grow();
  void TrimLeadingZeros();
  void Invert();
  SumoS32 TestBit(SumoS32 bit);
  void CopyFrom(U32Vector &other);
  void Resize(SumoU32 size);
  void PushBack(const SumoU32 &value);
  void PadTo(SumoU32 size);

  SumoU32 Size() const { return (SumoU32)(m_end - m_begin); }

protected:
  SumoU32 *m_begin;
  SumoU32 *m_end;
  SumoU32 *m_capacity;
};

Vector3 MakeVector3(SumoF32 x, SumoF32 y, SumoF32 z);

class Vector3Vector {
public:
  Vector3Vector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~Vector3Vector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  Vector3 &operator[](SumoU32 index);
  void Grow();
  void PushBack(const Vector3 &value);

private:
  Vector3 *m_begin;
  Vector3 *m_end;
  Vector3 *m_capacity;
};

class RuntimeVector3Vector {
public:
  ~RuntimeVector3Vector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  Vector3 &operator[](SumoU32 index);
  void Grow();
  void Resize(SumoU32 size);

private:
  Vector3 *m_begin;
  Vector3 *m_end;
  Vector3 *m_capacity;
};

class FloatVector {
public:
  ~FloatVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  SumoF32 &operator[](SumoU32 index);
  void Grow();
  void Resize(SumoU32 size);
  bool Empty() const { return m_begin == m_end; }
  bool HasElements() const { return m_end > m_begin; }

private:
  SumoF32 *m_begin;
  SumoF32 *m_end;
  SumoF32 *m_capacity;
};

#endif
