#include "containers.h"

#include "assert.h"

#include <math.h>

// GLOBAL: SUMO 0x004343cc
// GLOBAL: EDITOR 0x004343cc
extern const SumoF32 g_vectorZero = 0.0f;

// FUNCTION: SUMO 0x00402172
// FUNCTION: EDITOR 0x00402172
Vector3 Vector3::operator+(Vector3 &other) {
  Vector3 result;
  result.x = x + other.x;
  result.y = y + other.y;
  result.z = z + other.z;
  return result;
}

// FUNCTION: SUMO 0x004021a7
// FUNCTION: EDITOR 0x004021a7
Vector3 Vector3::operator-(Vector3 &other) {
  Vector3 result;
  result.x = x - other.x;
  result.y = y - other.y;
  result.z = z - other.z;
  return result;
}

// FUNCTION: SUMO 0x004021dc
// FUNCTION: EDITOR 0x004021dc
Vector3 Vector3::Cross(Vector3 &other) {
  Vector3 result;
  result.x = y * other.z - other.y * z;
  result.y = other.x * z - x * other.z;
  result.z = other.y * x - y * other.x;
  return result;
}

// FUNCTION: SUMO 0x00402227
// FUNCTION: EDITOR 0x00402227
Vector3 Vector3::Scale(SumoF32 &scale) {
  Vector3 result;
  result.x = x * scale;
  result.y = y * scale;
  result.z = z * scale;
  return result;
}

// FUNCTION: SUMO 0x0040225a
// FUNCTION: EDITOR 0x0040225a
void Vector3::operator+=(Vector3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

// FUNCTION: SUMO 0x00402279
// FUNCTION: EDITOR 0x00402279
Vector3 MakeVector3(SumoF32 x, SumoF32 y, SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

// FUNCTION: SUMO 0x004022a2
// FUNCTION: EDITOR 0x004022a2
SumoF32 Vector3::LengthSquared() { return x * x + y * y + z * z; }

// FUNCTION: SUMO 0x00402363
// FUNCTION: EDITOR 0x00402363
Vector3 Matrix3::Transform(Vector3 &vector) {
  Vector3 result;
  result.x = m01 * vector.y + m02 * vector.z + vector.x * m00;
  result.y = m11 * vector.y + m10 * vector.x + m12 * vector.z;
  result.z = m21 * vector.y + m20 * vector.x + m22 * vector.z;
  return result;
}

// FUNCTION: SUMO 0x004023c6
// FUNCTION: EDITOR 0x004023c6
Vector3 Vector3::Transform(Matrix3 &matrix) {
  Vector3 result;
  result.x = matrix.m20 * z + matrix.m10 * y + matrix.m00 * x;
  result.y = matrix.m21 * z + matrix.m01 * x + matrix.m11 * y;
  result.z = matrix.m22 * z + matrix.m02 * x + matrix.m12 * y;
  return result;
}

// FUNCTION: SUMO 0x00402429
// FUNCTION: EDITOR 0x00402429
void Matrix3::SetIdentity() {
  m22 = 1.0f;
  m11 = 1.0f;
  m00 = 1.0f;
  m21 = 0.0f;
  m20 = 0.0f;
  m12 = 0.0f;
  m10 = 0.0f;
  m02 = 0.0f;
  m01 = 0.0f;
}

// FUNCTION: SUMO 0x00402456
// FUNCTION: EDITOR 0x00402456
void Matrix3::RotateRows02(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = cosine * m00 - sine * m20;
  m20 = cosine * m20 + sine * m00;
  m00 = value;
  value = cosine * m01 - sine * m21;
  m21 = sine * m01 + cosine * m21;
  m01 = value;
  value = cosine * m02 - sine * m22;
  m22 = sine * m02 + cosine * m22;
  m02 = value;
}

// FUNCTION: SUMO 0x004024da
// FUNCTION: EDITOR 0x004024da
void Matrix3::RotateRows12(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = sine * m20 + cosine * m10;
  m20 = cosine * m20 - sine * m10;
  m10 = value;
  value = sine * m21 + cosine * m11;
  m21 = cosine * m21 - sine * m11;
  m11 = value;
  value = sine * m22 + cosine * m12;
  m22 = cosine * m22 - sine * m12;
  m12 = value;
}

// FUNCTION: SUMO 0x00402565
// FUNCTION: EDITOR 0x00402565
void Matrix3::RotateRows01(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = sine * m10 + cosine * m00;
  m10 = cosine * m10 - sine * m00;
  m00 = value;
  value = sine * m11 + cosine * m01;
  m11 = cosine * m11 - sine * m01;
  m01 = value;
  value = sine * m12 + cosine * m02;
  m12 = cosine * m12 - sine * m02;
  m02 = value;
}

// FUNCTION: SUMO 0x004025ed
// FUNCTION: EDITOR 0x004025ed
void Matrix3::RotateColumns02(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = cosine * m00 - sine * m02;
  m02 = cosine * m02 + sine * m00;
  m00 = value;
  value = cosine * m10 - sine * m12;
  m12 = sine * m10 + cosine * m12;
  m10 = value;
  value = cosine * m20 - sine * m22;
  m22 = sine * m20 + cosine * m22;
  m20 = value;
}

// FUNCTION: SUMO 0x00402671
// FUNCTION: EDITOR 0x00402671
void Matrix3::RotateColumns12(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = sine * m02 + cosine * m01;
  m02 = cosine * m02 - sine * m01;
  m01 = value;
  value = sine * m12 + cosine * m11;
  m12 = cosine * m12 - sine * m11;
  m11 = value;
  value = sine * m22 + cosine * m21;
  m22 = cosine * m22 - sine * m21;
  m21 = value;
}

// FUNCTION: SUMO 0x004026fc
// FUNCTION: EDITOR 0x004026fc
void Matrix3::RotateColumns01(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos(angle);
  SumoF32 sine = (SumoF32)sin(angle);
  SumoF32 value;

  value = sine * m01 + cosine * m00;
  m01 = cosine * m01 - sine * m00;
  m00 = value;
  value = sine * m11 + cosine * m10;
  m11 = cosine * m11 - sine * m10;
  m10 = value;
  value = sine * m21 + cosine * m20;
  m21 = cosine * m21 - sine * m20;
  m20 = value;
}

// FUNCTION: SUMO 0x0040381a
// FUNCTION: EDITOR 0x0040381a
Matrix3 Matrix3::Transposed() {
  Matrix3 result;
  result.m00 = m00;
  result.m01 = m10;
  result.m02 = m20;
  result.m10 = m01;
  result.m11 = m11;
  result.m12 = m21;
  result.m20 = m02;
  result.m21 = m12;
  result.m22 = m22;
  return result;
}

// FUNCTION: SUMO 0x004046fb
// FUNCTION: EDITOR 0x0040471d
Vector3 Vector3::MultiplyComponents(Vector3 &other) {
  Vector3 result;
  result.x = x * other.x;
  result.y = y * other.y;
  result.z = z * other.z;
  return result;
}

// FUNCTION: SUMO 0x004050ee
// FUNCTION: EDITOR 0x00405110
void Vector3Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(Vector3);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (Vector3 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004055c3
// FUNCTION: EDITOR 0x004055e5
void Vector3Vector::PushBack(const Vector3 &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x00406e68
// FUNCTION: EDITOR 0x00406e8a
Vector3 Vector3::operator-() {
  Vector3 result;
  result.x = -x;
  result.y = -y;
  result.z = -z;
  return result;
}

// FUNCTION: SUMO 0x00407e19
// FUNCTION: EDITOR 0x00407e3b
Vector3 Matrix3::Row0() {
  Vector3 result;
  result.x = m00;
  result.y = m01;
  result.z = m02;
  return result;
}

// FUNCTION: SUMO 0x00407e43
// FUNCTION: EDITOR 0x00407e65
Vector3 Matrix3::Row1() {
  Vector3 result;
  result.x = m10;
  result.y = m11;
  result.z = m12;
  return result;
}

// FUNCTION: SUMO 0x00407e6e
// FUNCTION: EDITOR 0x00407e90
Vector3 Matrix3::Row2() {
  Vector3 result;
  result.x = m20;
  result.y = m21;
  result.z = m22;
  return result;
}

// FUNCTION: SUMO 0x0040e665
// FUNCTION: EDITOR 0x0040e687
Vector3 Matrix3::Column1() {
  Vector3 result;
  result.x = m01;
  result.y = m11;
  result.z = m21;
  return result;
}
