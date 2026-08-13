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

struct Matrix3;

extern const SumoF32 g_vectorZero;

struct Vector3 {
  SumoF32 x;
  SumoF32 y;
  SumoF32 z;

  Vector3 operator+(Vector3 &other);
  Vector3 operator-(Vector3 &other);
  Vector3 operator-();
  Vector3 Cross(Vector3 &other);
  Vector3 Scale(SumoF32 &scale);
  Vector3 MultiplyComponents(Vector3 &other);
  void Rotate(Vector3 &axis, SumoF32 cosine, SumoF32 sine);
  void Rotate(Vector3 &rotation);
  void operator+=(Vector3 &other);
  __forceinline void AddInline(Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
  }
  SumoF32 LengthSquared();
  SumoF32 Dot(Vector3 &other) {
    return x * other.x + y * other.y + z * other.z;
  }
  SumoF32 Normalize();
  Vector3 Normalized();
  Vector3 Transform(Matrix3 &matrix);

  Vector3 operator+(const Vector3 &other) {
    return operator+(const_cast<Vector3 &>(other));
  }
  Vector3 operator-(const Vector3 &other) {
    return operator-(const_cast<Vector3 &>(other));
  }
  Vector3 Cross(const Vector3 &other) {
    return Cross(const_cast<Vector3 &>(other));
  }
  void operator+=(const Vector3 &other) {
    operator+=(const_cast<Vector3 &>(other));
  }
  void AddInline(const Vector3 &other) {
    AddInline(const_cast<Vector3 &>(other));
  }
  SumoF32 Dot(const Vector3 &other) {
    return Dot(const_cast<Vector3 &>(other));
  }
};

struct Matrix3 {
  SumoF32 m00;
  SumoF32 m01;
  SumoF32 m02;
  SumoF32 m10;
  SumoF32 m11;
  SumoF32 m12;
  SumoF32 m20;
  SumoF32 m21;
  SumoF32 m22;

  Vector3 Transform(Vector3 &vector);
  Matrix3 operator+(Matrix3 &other);
  Vector3 Row0();
  Vector3 Row1();
  Vector3 Row2();
  __forceinline void SetRow0(Vector3 row) {
    m00 = row.x;
    m01 = row.y;
    m02 = row.z;
  }
  __forceinline void SetRow1(Vector3 row) {
    m10 = row.x;
    m11 = row.y;
    m12 = row.z;
  }
  __forceinline void SetRow2(Vector3 row) {
    m20 = row.x;
    m21 = row.y;
    m22 = row.z;
  }
  Vector3 Column1();
  void SetIdentity();
  void Rotate(Vector3 &axis, SumoF32 cosine, SumoF32 sine);
  void Rotate(Vector3 &rotation);
  void RotateRows02(SumoF32 angle);
  void RotateRows12(SumoF32 angle);
  void RotateRows01(SumoF32 angle);
  void RotateColumns02(SumoF32 angle);
  void RotateColumns12(SumoF32 angle);
  void RotateColumns01(SumoF32 angle);
  Matrix3 Transposed();
  Matrix3 Inverted();
  Matrix3 Multiply(Matrix3 &other);
  void Orthonormalize();

  Vector3 Transform(const Vector3 &vector) {
    return Transform(const_cast<Vector3 &>(vector));
  }
  Matrix3 Multiply(const Matrix3 &other) {
    return Multiply(const_cast<Matrix3 &>(other));
  }
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
