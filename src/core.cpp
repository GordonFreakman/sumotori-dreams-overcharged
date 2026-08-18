#include "decomp_keywords.h"
#include "containers.h"
#include "sumo_assert.h"
#include "big_integer.h"
#include "decomp.h"
#include "replay.h"
#include "parser.h"
#include "vectors.h"
#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

extern const SumoF32 g_vectorZero = 0.0f;

Vector3 Vector3::operator+(Vector3 &other) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)x + other.x);
  result.y = (SumoF32)((SumoF64)y + other.y);
  result.z = (SumoF32)((SumoF64)z + other.z);
  return result;
}

Vector3 Vector3::operator-(Vector3 &other) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)x - other.x);
  result.y = (SumoF32)((SumoF64)y - other.y);
  result.z = (SumoF32)((SumoF64)z - other.z);
  return result;
}

Vector3 Vector3::Cross(Vector3 &other) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)y * other.z - (SumoF64)other.y * z);
  result.y = (SumoF32)((SumoF64)other.x * z - (SumoF64)x * other.z);
  result.z = (SumoF32)((SumoF64)other.y * x - (SumoF64)y * other.x);
  return result;
}

Vector3 Vector3::Scale(SumoF32 &scale) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)x * scale);
  result.y = (SumoF32)((SumoF64)y * scale);
  result.z = (SumoF32)((SumoF64)z * scale);
  return result;
}

void Vector3::operator+=(Vector3 &other) {
  x = (SumoF32)((SumoF64)x + other.x);
  y = (SumoF32)((SumoF64)y + other.y);
  z = (SumoF32)((SumoF64)z + other.z);
}

Vector3 MakeVector3(SumoF32 x, SumoF32 y, SumoF32 z) {
  Vector3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

SumoF32 Vector3::LengthSquared() {
  return x * x + y * y + z * z;
}

SumoF32 Vector3::Normalize() {
  SumoF32 scale =
      (SumoF32)sqrt((SumoF64)x * x + (SumoF64)y * y + (SumoF64)z * z);
  if (scale != g_vectorZero) {
    scale = (SumoF32)(1.0 / scale);
  }

  x = (SumoF32)((SumoF64)scale * x);
  y = (SumoF32)((SumoF64)scale * y);
  z = (SumoF32)((SumoF64)scale * z);
  return scale;
}

Vector3 Vector3::Normalized() {
  SumoF32 scale =
      (SumoF32)sqrt((SumoF64)x * x + (SumoF64)y * y + (SumoF64)z * z);
  if (scale != g_vectorZero) {
    scale = (SumoF32)(1.0 / scale);
  }

  Vector3 result = *this;
  result.x = (SumoF32)((SumoF64)result.x * scale);
  result.y = (SumoF32)((SumoF64)result.y * scale);
  result.z = (SumoF32)((SumoF64)result.z * scale);
  return result;
}

Vector3 Matrix3::Transform(Vector3 &vector) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)m01 * vector.y + (SumoF64)m02 * vector.z +
                       (SumoF64)vector.x * m00);
  result.y = (SumoF32)((SumoF64)m11 * vector.y + (SumoF64)m10 * vector.x +
                       (SumoF64)m12 * vector.z);
  result.z = (SumoF32)((SumoF64)m21 * vector.y + (SumoF64)m20 * vector.x +
                       (SumoF64)m22 * vector.z);
  return result;
}

Vector3 Vector3::Transform(Matrix3 &matrix) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)matrix.m20 * z + (SumoF64)matrix.m10 * y +
                       (SumoF64)matrix.m00 * x);
  result.y = (SumoF32)((SumoF64)matrix.m21 * z + (SumoF64)matrix.m01 * x +
                       (SumoF64)matrix.m11 * y);
  result.z = (SumoF32)((SumoF64)matrix.m22 * z + (SumoF64)matrix.m02 * x +
                       (SumoF64)matrix.m12 * y);
  return result;
}

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

void Matrix3::RotateRows02(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)cosine * m00 - (SumoF64)sine * m20);
  m20 = (SumoF32)((SumoF64)cosine * m20 + (SumoF64)sine * m00);
  m00 = value;
  value = (SumoF32)((SumoF64)cosine * m01 - (SumoF64)sine * m21);
  m21 = (SumoF32)((SumoF64)sine * m01 + (SumoF64)cosine * m21);
  m01 = value;
  value = (SumoF32)((SumoF64)cosine * m02 - (SumoF64)sine * m22);
  m22 = (SumoF32)((SumoF64)sine * m02 + (SumoF64)cosine * m22);
  m02 = value;
}

void Matrix3::RotateRows12(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)sine * m20 + (SumoF64)cosine * m10);
  m20 = (SumoF32)((SumoF64)cosine * m20 - (SumoF64)sine * m10);
  m10 = value;
  value = (SumoF32)((SumoF64)sine * m21 + (SumoF64)cosine * m11);
  m21 = (SumoF32)((SumoF64)cosine * m21 - (SumoF64)sine * m11);
  m11 = value;
  value = (SumoF32)((SumoF64)sine * m22 + (SumoF64)cosine * m12);
  m22 = (SumoF32)((SumoF64)cosine * m22 - (SumoF64)sine * m12);
  m12 = value;
}

void Matrix3::RotateRows01(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)sine * m10 + (SumoF64)cosine * m00);
  m10 = (SumoF32)((SumoF64)cosine * m10 - (SumoF64)sine * m00);
  m00 = value;
  value = (SumoF32)((SumoF64)sine * m11 + (SumoF64)cosine * m01);
  m11 = (SumoF32)((SumoF64)cosine * m11 - (SumoF64)sine * m01);
  m01 = value;
  value = (SumoF32)((SumoF64)sine * m12 + (SumoF64)cosine * m02);
  m12 = (SumoF32)((SumoF64)cosine * m12 - (SumoF64)sine * m02);
  m02 = value;
}

void Matrix3::RotateColumns02(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)cosine * m00 - (SumoF64)sine * m02);
  m02 = (SumoF32)((SumoF64)cosine * m02 + (SumoF64)sine * m00);
  m00 = value;
  value = (SumoF32)((SumoF64)cosine * m10 - (SumoF64)sine * m12);
  m12 = (SumoF32)((SumoF64)sine * m10 + (SumoF64)cosine * m12);
  m10 = value;
  value = (SumoF32)((SumoF64)cosine * m20 - (SumoF64)sine * m22);
  m22 = (SumoF32)((SumoF64)sine * m20 + (SumoF64)cosine * m22);
  m20 = value;
}

void Matrix3::RotateColumns12(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)sine * m02 + (SumoF64)cosine * m01);
  m02 = (SumoF32)((SumoF64)cosine * m02 - (SumoF64)sine * m01);
  m01 = value;
  value = (SumoF32)((SumoF64)sine * m12 + (SumoF64)cosine * m11);
  m12 = (SumoF32)((SumoF64)cosine * m12 - (SumoF64)sine * m11);
  m11 = value;
  value = (SumoF32)((SumoF64)sine * m22 + (SumoF64)cosine * m21);
  m22 = (SumoF32)((SumoF64)cosine * m22 - (SumoF64)sine * m21);
  m21 = value;
}

void Matrix3::RotateColumns01(SumoF32 angle) {
  SumoF32 cosine = (SumoF32)cos((SumoF64)angle);
  SumoF32 sine = (SumoF32)sin((SumoF64)angle);
  SumoF32 value;

  value = (SumoF32)((SumoF64)sine * m01 + (SumoF64)cosine * m00);
  m01 = (SumoF32)((SumoF64)cosine * m01 - (SumoF64)sine * m00);
  m00 = value;
  value = (SumoF32)((SumoF64)sine * m11 + (SumoF64)cosine * m10);
  m11 = (SumoF32)((SumoF64)cosine * m11 - (SumoF64)sine * m10);
  m10 = value;
  value = (SumoF32)((SumoF64)sine * m21 + (SumoF64)cosine * m20);
  m21 = (SumoF32)((SumoF64)cosine * m21 - (SumoF64)sine * m20);
  m20 = value;
}

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

Vector3 Vector3::MultiplyComponents(Vector3 &other) {
  Vector3 result;
  result.x = (SumoF32)((SumoF64)x * other.x);
  result.y = (SumoF32)((SumoF64)y * other.y);
  result.z = (SumoF32)((SumoF64)z * other.z);
  return result;
}

void Vector3Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(Vector3);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (Vector3 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

void Vector3Vector::PushBack(const Vector3 &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

Vector3 Vector3::operator-() {
  Vector3 result;
  result.x = -x;
  result.y = -y;
  result.z = -z;
  return result;
}

Vector3 Matrix3::Row0() {
  Vector3 result;
  result.x = m00;
  result.y = m01;
  result.z = m02;
  return result;
}

Vector3 Matrix3::Row1() {
  Vector3 result;
  result.x = m10;
  result.y = m11;
  result.z = m12;
  return result;
}

Vector3 Matrix3::Row2() {
  Vector3 result;
  result.x = m20;
  result.y = m21;
  result.z = m22;
  return result;
}

Vector3 Matrix3::Column1() {
  Vector3 result;
  result.x = m01;
  result.y = m11;
  result.z = m21;
  return result;
}

// FUNCTION: SUMO 0x00402e1d
// FUNCTION: EDITOR 0x00402e1d
void Vector3::Rotate(Vector3 &axis, SumoF32 cosine, SumoF32 sine) {
  SumoF32 projection = axis.Dot(*this) * (1.0f - cosine);
  *this = Scale(cosine) + axis.Scale(projection) + Cross(axis).Scale(sine);
}

// FUNCTION: SUMO 0x00402ea2
// FUNCTION: EDITOR 0x00402ea2
void Vector3::Rotate(Vector3 &rotation) {
  Vector3 axis = rotation;
  axis.Normalize();
  Rotate(axis, (SumoF32)cos(sqrt(rotation.LengthSquared())),
         (SumoF32)sin(sqrt(rotation.LengthSquared())));
}

// FUNCTION: SUMO 0x0040807d
// FUNCTION: EDITOR 0x0040809f
Matrix3 Matrix3::operator+(Matrix3 &other) {
  Matrix3 result;
  result.m00 = m00 + other.m00;
  result.m01 = m01 + other.m01;
  result.m02 = m02 + other.m02;
  result.m10 = m10 + other.m10;
  result.m11 = m11 + other.m11;
  result.m12 = m12 + other.m12;
  result.m20 = m20 + other.m20;
  result.m21 = m21 + other.m21;
  result.m22 = m22 + other.m22;
  return result;
}

// FUNCTION: SUMO 0x0040918e
// FUNCTION: EDITOR 0x004091b0
void Matrix3::Rotate(Vector3 &axis, SumoF32 cosine, SumoF32 sine) {
  Vector3 row0 = Row0();
  Vector3 row1 = Row1();
  Vector3 row2 = Row2();

  row0.Rotate(axis, cosine, sine);
  row1.Rotate(axis, cosine, sine);
  row2.Rotate(axis, cosine, sine);

  SetRow0(row0);
  SetRow1(row1);
  SetRow2(row2);
}

// FUNCTION: SUMO 0x0040925d
// FUNCTION: EDITOR 0x0040927f
void Matrix3::Rotate(Vector3 &rotation) {
  Vector3 axis = rotation;
  axis.Normalize();
  SumoF32 angle = (SumoF32)sqrt(rotation.LengthSquared());
  Rotate(axis, (SumoF32)cos(sqrt(rotation.LengthSquared())),
         (SumoF32)sin(angle));
}

// FUNCTION: SUMO 0x00407f84
// FUNCTION: EDITOR 0x00407fa6
Matrix3 Matrix3::Multiply(Matrix3 &other) {
  Matrix3 result;
  result.m00 = other.m10 * m10 + other.m00 * m00 + m20 * other.m20;
  result.m01 = m21 * other.m20 + other.m10 * m11 + m01 * other.m00;
  result.m02 = m22 * other.m20 + other.m00 * m02 + other.m10 * m12;
  result.m10 = other.m21 * m20 + other.m01 * m00 + other.m11 * m10;
  result.m11 = other.m21 * m21 + other.m11 * m11 + other.m01 * m01;
  result.m12 = other.m01 * m02 + m22 * other.m21 + m12 * other.m11;
  result.m20 = other.m22 * m20 + other.m02 * m00 + other.m12 * m10;
  result.m21 = other.m22 * m21 + other.m12 * m11 + other.m02 * m01;
  result.m22 = other.m02 * m02 + m22 * other.m22 + m12 * other.m12;
  return result;
}

extern const SumoF32 g_gameOne;

Matrix3 Matrix3::Inverted() {
  double cofactorA = (double)m12 * m20 - (double)m22 * m10;
  volatile SumoF32 cofactorB = m21 * m10 - m20 * m11;
  double cofactorC = (double)m22 * m11 - (double)m12 * m21;
  volatile SumoF32 roundedC = (SumoF32)cofactorC;
  double inverseDeterminant =
      g_gameOne / (cofactorC * m00 + cofactorA * m01 + cofactorB * m02);

  Matrix3 result;
  result.m00 = (SumoF32)(roundedC * inverseDeterminant);
  result.m10 =
      (SumoF32)(((double)m02 * m21 - (double)m22 * m01) * inverseDeterminant);
  result.m20 =
      (SumoF32)(((double)m12 * m01 - (double)m02 * m11) * inverseDeterminant);
  result.m01 = (SumoF32)(cofactorA * inverseDeterminant);
  result.m11 =
      (SumoF32)(((double)m22 * m00 - (double)m02 * m20) * inverseDeterminant);
  result.m21 =
      (SumoF32)(((double)m02 * m10 - (double)m12 * m00) * inverseDeterminant);
  result.m02 = (SumoF32)(cofactorB * inverseDeterminant);
  result.m12 =
      (SumoF32)(((double)m20 * m01 - (double)m00 * m21) * inverseDeterminant);
  result.m22 =
      (SumoF32)(((double)m00 * m11 - (double)m10 * m01) * inverseDeterminant);
  return result;
}

void Matrix3::Orthonormalize() {
  Vector3 normalized = Row0().Normalized();
  m00 = normalized.x;
  m01 = normalized.y;
  m02 = normalized.z;

  normalized = Row1().Normalized();
  m10 = normalized.x;
  m11 = normalized.y;
  m12 = normalized.z;

  Vector3 cross = Row0().Cross(Row1());
  m20 = cross.x;
  m21 = cross.y;
  m22 = cross.z;

  cross = Row2().Cross(Row0());
  m10 = cross.x;
  m11 = cross.y;
  m12 = cross.z;
}

DECOMP_SIZE_ASSERT(BigInteger, 0x10);

// FUNCTION: SUMO 0x00401247
// FUNCTION: EDITOR 0x00401247
BigInteger::BigInteger(BigInteger &other) {
  CopyFrom(other);
  m_sign = other.m_sign;
}

// FUNCTION: SUMO 0x0040126c
// FUNCTION: EDITOR 0x0040126c
void BigInteger::SetPositive(SumoU32 value) {
  Resize(1);
  (*this)[0] = value;
  m_sign = 1;
}

// FUNCTION: SUMO 0x00401290
// FUNCTION: EDITOR 0x00401290
void BigInteger::SetBit(SumoS32 bit, SumoS32 value) {
  switch (value) {
  case 0:
    if (bit < Size() * 32) {
      (*this)[bit / 32] &= ~(1 << (bit % 32));
    }
    break;
  case 1:
    PadTo(bit / 32 + 1);
    (*this)[bit / 32] |= 1 << (bit % 32);
    break;
  }
}

// FUNCTION: SUMO 0x00401301
// FUNCTION: EDITOR 0x00401301
void BigInteger::operator++(int) {
  SumoS32 i = -1;
increment_next_limb:
  ++i;
  if (i < Size()) {
    ++(*this)[i];
    if ((*this)[i] == 0) {
      goto increment_next_limb;
    }
    return;
  }

  SumoU32 one = 1;
  PushBack(one);
}

// FUNCTION: SUMO 0x00401348
// FUNCTION: EDITOR 0x00401348
void BigInteger::AppendLimb(SumoU32 value) {
  TrimLeadingZeros();
  PushBack(value);
}

// FUNCTION: SUMO 0x00401360
// FUNCTION: EDITOR 0x00401360
BigInteger::BigInteger() { BigInteger(0); }

// FUNCTION: SUMO 0x00401206
// FUNCTION: EDITOR 0x00401206
BigInteger::BigInteger(SumoS32 value) {
  Resize(1);

  if (value < 0) {
    (*this)[0] = -value;
    m_sign = -1;
  } else {
    (*this)[0] = value;
    m_sign = 1;
  }
}

// FUNCTION: SUMO 0x0040180e
// FUNCTION: EDITOR 0x0040180e
BigInteger::BigInteger(char *p_text, SumoS32 p_length, const char *p_alphabet,
                       SumoS32 p_radix) {
  if (p_length == 0) {
    char *end = p_text;
    while (*end != 0) {
      ++end;
      ++p_length;
    }
  }

  if (p_alphabet == NULL) {
    p_alphabet = "0123456789";
  }

  SetPositive(0);
  BigInteger place(1);
  p_text += p_length;

  while (p_length > 0) {
    --p_text;

    SumoS32 digit = 0;
    while (digit < p_radix) {
      if (p_alphabet[digit] == *p_text) {
        *this += place * BigInteger(digit);
        place = place * BigInteger(p_radix);
        break;
      }

      ++digit;
    }

    --p_length;
  }
}

// FUNCTION: SUMO 0x004011b6
// FUNCTION: EDITOR 0x004011b6
__declspec(nothrow) BigInteger &BigInteger::operator=(BigInteger &other) {
  CopyFrom(other);
  m_sign = other.m_sign;
  return *this;
}

// FUNCTION: SUMO 0x00401948
// FUNCTION: EDITOR 0x00401948
bool BigInteger::operator==(BigInteger &other) {
  BigInteger difference = *this - other;
  return difference.Size() == 0;
}

// FUNCTION: SUMO 0x00401980
// FUNCTION: EDITOR 0x00401980
bool BigInteger::operator>(BigInteger &other) {
  BigInteger difference = other - *this;
  return difference.m_sign == -1;
}

// FUNCTION: SUMO 0x00401764
// FUNCTION: EDITOR 0x00401764
BigInteger BigInteger::operator+(BigInteger &other) {
  BigInteger result(*this);
  result += other;
  return result;
}

// FUNCTION: SUMO 0x004017b9
// FUNCTION: EDITOR 0x004017b9
BigInteger BigInteger::operator-(BigInteger &other) {
  BigInteger result(*this);
  result -= other;
  return result;
}

void SumoAssert(bool condition);

void BigInteger::operator-=(BigInteger &other) {
  if (m_sign != other.m_sign) {
    m_sign = -m_sign;
    *this += other;
    m_sign = -m_sign;
    return;
  }

  SumoU32 otherSize = other.Size();
  SumoU32 size = Size();
  SumoU32 padded = (size > otherSize ? size : otherSize) + 1;
  PadTo(padded);
  if (other.Size() == 0)
    return;

  SumoU32 *source = &other[0];
  SumoU32 *destination = &(*this)[0];
  SumoS32 sourceCount = (SumoS32)other.Size();
  SumoS32 carryCount = (SumoS32)(Size() - other.Size());
  if (sourceCount != 0) {
    SumoU32 borrow = 0;
    for (SumoS32 index = 0; index < sourceCount; ++index) {
      SumoS64 total = (SumoS64)(SumoU64)*destination - borrow - *source;
      *destination = (SumoU32)total;
      borrow = (SumoU32)(SumoS32) - (SumoS32)(total >> 32);
      ++destination;
      ++source;
    }
    for (SumoS32 index = 0; index < carryCount; ++index) {
      SumoS64 total = (SumoS64)(SumoU64)*destination - borrow;
      *destination = (SumoU32)total;
      borrow = (SumoU32)(SumoS32) - (SumoS32)(total >> 32);
      ++destination;
    }
    if (borrow != 0) {
      m_sign = -m_sign;
      Invert();
      operator++(0);
    }
  }
  TrimLeadingZeros();
}

void BigInteger::operator+=(BigInteger &other) {
  SumoAssert(&other != this);
  if (m_sign != other.m_sign) {
    m_sign = -m_sign;
    *this -= other;
    m_sign = -m_sign;
    return;
  }

  SumoU32 otherSize = other.Size();
  SumoU32 size = Size();
  SumoU32 padded = (size > otherSize ? size : otherSize) + 1;
  PadTo(padded);
  if (other.Size() == 0)
    return;

  SumoU32 *source = &other[0];
  SumoU32 *destination = &(*this)[0];
  SumoS32 sourceCount = (SumoS32)other.Size();
  SumoS32 carryCount = (SumoS32)(Size() - other.Size());
  if (sourceCount != 0) {
    SumoU32 carry = 0;
    for (SumoS32 index = 0; index < sourceCount; ++index) {
      SumoU64 total = (SumoU64)*destination + carry + *source;
      *destination = (SumoU32)total;
      carry = (SumoU32)(total >> 32);
      ++destination;
      ++source;
    }
    for (SumoS32 index = 0; index < carryCount; ++index) {
      SumoU64 total = (SumoU64)*destination + carry;
      *destination = (SumoU32)total;
      carry = (SumoU32)(total >> 32);
      ++destination;
    }
  }
  TrimLeadingZeros();
}

// GLOBAL: SUMO 0x004533ac
// GLOBAL: EDITOR 0x004533ac
SumoS32 g_bigIntegerMultiplyFlag = 1;

extern SumoS32 g_bigIntegerMultiplyFlag;

BigInteger BigInteger::operator*(BigInteger &other) {
  BigInteger product;
  product.PadTo(other.Size() + Size());
  if (Size() != 0) {
    for (SumoU32 limbIndex = 0; limbIndex < Size(); ++limbIndex) {
      SumoU32 otherSize = other.Size();
      if (otherSize == 0)
        return BigInteger(0);
      SumoU32 *productCursor = &product[limbIndex];
      SumoU32 *otherCursor = &other[0];
      SumoU32 multiplier = (*this)[limbIndex];
      for (SumoU32 count = otherSize; count != 0; --count) {
        SumoU64 term = (SumoU64)*otherCursor * multiplier;
        SumoU64 low = (SumoU64)productCursor[0] + (SumoU32)term;
        productCursor[0] = (SumoU32)low;
        SumoU64 high = (SumoU64)productCursor[1] + (SumoU32)(term >> 32) +
                       (SumoU32)(low >> 32);
        productCursor[1] = (SumoU32)high;
        if ((high >> 32) != 0) {
          SumoS32 extra = 2;
          while (++productCursor[extra] == 0)
            ++extra;
        }
        ++productCursor;
        ++otherCursor;
      }
    }
  }
  product.m_sign = other.m_sign * m_sign;
  product.TrimLeadingZeros();
  if (g_bigIntegerMultiplyFlag != 0)
    g_bigIntegerMultiplyFlag = 1;
  return product;
}

// FUNCTION: SUMO 0x00401adb
// FUNCTION: EDITOR 0x00401adb
BigInteger BigInteger::operator%(BigInteger &other) {
  BigInteger quotient;
  Divide(this, &other, &quotient);
  return *this - quotient * other;
}

// FUNCTION: SUMO 0x00401b5c
// FUNCTION: EDITOR 0x00401b5c
BigInteger BigInteger::operator/(BigInteger &other) {
  BigInteger result;
  Divide(this, &other, &result);
  return result;
}

BigInteger BigInteger::operator<<(SumoS32 p_bits) {
  BigInteger shifted;
  shifted.PadTo(Size() * 32 + (SumoU32)((p_bits + 31) / 32));
  SumoS32 limbShift = p_bits / 32;
  SumoS32 bitShift = p_bits % 32;
  for (SumoU32 index = 0; index < Size(); ++index) {
    shifted[index + limbShift] =
        shifted[index + limbShift] + ((*this)[index] << bitShift);
    if (bitShift != 0)
      shifted[index + limbShift + 1] = (*this)[index] >> (32 - bitShift);
  }
  shifted.TrimLeadingZeros();
  shifted.m_sign = m_sign;
  return shifted;
}

BigInteger BigInteger::Power(SumoS32 exponent) {
  BigInteger result;
  result.SetPositive(1);
  BigInteger factor(*this);
  BigInteger bitValue(1);
  SumoS32 bitIndex = 0;
  for (;;) {
    if ((exponent & (1 << bitIndex)) != 0) {
      BigInteger multiplied = result * factor;
      result = multiplied;
    }
    ++bitIndex;
    BigInteger doubled = bitValue + bitValue;
    bitValue = doubled;
    BigInteger squared = factor * factor;
    factor = squared;
    BigInteger limit(exponent);
    if (bitValue > limit)
      break;
  }
  return result;
}

// FUNCTION: SUMO 0x00401e60
// FUNCTION: EDITOR 0x00401e60
void BigInteger::ModularPower(BigInteger &base, BigInteger &exponent,
                              BigInteger &modulus) {
  SetPositive(1);
  BigInteger factor(base);
  BigInteger bitValue(1);
  SumoS32 bit = 0;

  do {
    if (exponent.TestBit(bit)) {
      *this = (*this * factor) % modulus;
    }

    ++bit;
    bitValue = bitValue + bitValue;
    factor = (factor * factor) % modulus;
  } while (!(bitValue > exponent));
}

SumoS32 BigInteger::Log(BigInteger &base) {
  BigInteger powers[32];
  powers[0] = base;
  if (base > *this)
    return 0;

  SumoS32 highest = 0;
  for (;;) {
    BigInteger squared = powers[highest] * powers[highest];
    powers[highest + 1] = squared;
    ++highest;
    if (powers[highest] > *this)
      break;
  }
  --highest;

  BigInteger accumulated(powers[highest]);
  SumoS32 result = 1 << highest;
  SumoS32 bit = highest;
  while (bit > 0) {
    --bit;
    BigInteger candidate = accumulated * powers[bit];
    if (!(candidate > *this)) {
      result |= 1 << bit;
      accumulated = candidate;
    }
  }
  return result;
}

void BigInteger::WriteString(char *output, SumoS32 capacity,
                             const char *alphabet, SumoS32 radix,
                             SumoS32 minimumDigits) {
  if (alphabet == 0)
    alphabet = "0123456789";
  char *limit = output + capacity - 1;
  char *cursor = output;

  BigInteger place(radix);
  SumoS32 digits = Log(place);
  if (minimumDigits != 0 && digits < minimumDigits - 1)
    digits = minimumDigits - 1;
  {
    BigInteger radixValue(radix);
    BigInteger raised = radixValue.Power(digits);
    place = raised;
  }

  BigInteger remaining(*this);
  SumoS32 written = 0;
  if (digits >= 0) {
    SumoS32 count = digits + 1;
    do {
      BigInteger digit = remaining / place;
      SumoU32 digitValue = 0;
      if (digit.Size() != 0)
        digitValue = digit[0];
      if (cursor < limit) {
        if (written == 5 && minimumDigits != 0) {
          *cursor = '-';
          written = 0;
          ++cursor;
        }
        *cursor = alphabet[digitValue];
        ++cursor;
        ++written;
      }
      BigInteger product = place * digit;
      remaining -= product;
      BigInteger radixValue(radix);
      BigInteger quotient = place / radixValue;
      place = quotient;
      --count;
    } while (count != 0);
  }
  *cursor = 0;
}

// FUNCTION: SUMO 0x0040106c
// FUNCTION: EDITOR 0x0040106c
void U32Vector::TrimLeadingZeros() {
  while (Size() != 0) {
    if ((*this)[Size() - 1] != 0) {
      break;
    }

    if (m_end > m_begin) {
      --m_end;
    }
  }
}

// FUNCTION: SUMO 0x004010ac
// FUNCTION: EDITOR 0x004010ac
void U32Vector::Invert() {
  for (SumoU32 i = 0; i < Size(); ++i) {
    SumoU32 &value = (*this)[i];
    value = ~value;
  }
}

// FUNCTION: SUMO 0x004010d6
// FUNCTION: EDITOR 0x004010d6
SumoS32 U32Vector::TestBit(SumoS32 bit) {
  if ((SumoU32)bit >= Size() * 32) {
    return false;
  }

  return ((*this)[bit / 32] & (1 << (bit % 32))) != 0;
}

// FUNCTION: SUMO 0x0040114e
// FUNCTION: EDITOR 0x0040114e
void U32Vector::CopyFrom(U32Vector &other) {
  Resize(other.Size());

  for (SumoU32 i = 0; i < other.Size(); ++i) {
    m_begin[i] = other[i];
  }
}

#pragma intrinsic(memset)

static __forceinline void ContainerAssert(bool condition) {
  unsigned char *address = 0;
  while (!condition) {
    ++address;
    *address = 0x7f;
  }
}

DECOMP_SIZE_ASSERT(U32Vector, 0x0c);
DECOMP_SIZE_ASSERT(Vector3, 0x0c);
DECOMP_SIZE_ASSERT(Matrix3, 0x24);
DECOMP_SIZE_ASSERT(Vector3Vector, 0x0c);
DECOMP_SIZE_ASSERT(RuntimeVector3Vector, 0x0c);
DECOMP_SIZE_ASSERT(FloatVector, 0x0c);

// FUNCTION: SUMO 0x00401000
// FUNCTION: EDITOR 0x00401000
SumoU32 &U32Vector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(SumoU32);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(SumoU32 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00401021
// FUNCTION: EDITOR 0x00401021
void U32Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoU32);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (SumoU32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x00401111
// FUNCTION: EDITOR 0x00401111
void U32Vector::Resize(SumoU32 size) {
  SumoU32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0;
  }
}

// FUNCTION: SUMO 0x00401193
// FUNCTION: EDITOR 0x00401193
void U32Vector::PushBack(const SumoU32 &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x004011d1
// FUNCTION: EDITOR 0x004011d1
void U32Vector::PadTo(SumoU32 size) {
  SumoU32 currentSize = m_end - m_begin;

  if (currentSize < size) {
    SumoU32 zero = 0;
    do {
      PushBack(zero);
      currentSize = m_end - m_begin;
    } while (currentSize < size);
  }
}

// FUNCTION: SUMO 0x004019b1
// FUNCTION: EDITOR 0x004019b1
void Divide(BigInteger *dividend, BigInteger *divisor, BigInteger *quotient) {
  SumoAssert(quotient != dividend && quotient != divisor);
  SumoAssert(dividend->m_sign == 1 && divisor->m_sign == 1);

  if (divisor->Size() == 0) {
    SumoU8 *invalidAddress = 0;
    for (;;) {
      *++invalidAddress = 0x7f;
    }
  }

  SumoS32 limbDifference = dividend->Size() - divisor->Size() + 1;
  quotient->SetPositive(0);
  SumoS32 bit = limbDifference * 32 - 1;
  BigInteger remainder(0);

  while (bit >= 0) {
    quotient->SetBit(bit, 1);
    BigInteger previousRemainder(remainder);

    remainder += *divisor << bit;

    if (remainder > *dividend) {
      quotient->SetBit(bit, 0);
      remainder = previousRemainder;
    }

    --bit;
  }

  quotient->TrimLeadingZeros();
}

// FUNCTION: SUMO 0x00404730
// FUNCTION: EDITOR 0x00404752
void SumoAssert(bool condition) {
  unsigned char *address = 0;

  while (!condition) {
    ++address;
    *address = 0x7f;
  }
}

// FUNCTION: SUMO 0x00404fcc
// FUNCTION: EDITOR 0x00404fee
Vector3 &Vector3Vector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(Vector3);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(Vector3 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00404ff0
// FUNCTION: EDITOR 0x00405012
void SkipWhitespace(char **cursor) {
  while (**cursor == ' ' || **cursor == '\t' || **cursor == '\r' ||
         **cursor == '\n') {
    ++*cursor;
  }
}

DECOMP_SIZE_ASSERT(CompiledOperation, 0x1c);
DECOMP_SIZE_ASSERT(BuiltinFunctionEntry, 0x18);
DECOMP_SIZE_ASSERT(OperatorEntry, 0x08);
DECOMP_SIZE_ASSERT(ParsedOperation, 0x30);
DECOMP_SIZE_ASSERT(CompiledOperationVector, 0x0c);
DECOMP_SIZE_ASSERT(BuiltinFunctionVector, 0x0c);
DECOMP_SIZE_ASSERT(OperatorEntryVector, 0x0c);
DECOMP_SIZE_ASSERT(CharVector, 0x0c);
DECOMP_SIZE_ASSERT(ParsedOperationVector, 0x0c);

// FUNCTION: SUMO 0x00405012
// FUNCTION: EDITOR 0x00405034
void CompiledOperationVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(CompiledOperation);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (CompiledOperation *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040505b
// FUNCTION: EDITOR 0x0040507d
void BuiltinFunctionVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(BuiltinFunctionEntry);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (BuiltinFunctionEntry *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004050a8
// FUNCTION: EDITOR 0x004050ca
void OperatorEntryVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(OperatorEntry);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (OperatorEntry *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040513b
// FUNCTION: EDITOR 0x0040515d
SumoS32 ExpressionParser::IsIdentifierStart(char value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
         value == '_';
}

// FUNCTION: SUMO 0x0040520c
// FUNCTION: EDITOR 0x0040522e
SumoS32 ExpressionParser::IsIdentifierContinue(char value) {
  return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z') ||
         value == '_' || (value >= '0' && value <= '9');
}

// FUNCTION: SUMO 0x00405263
// FUNCTION: EDITOR 0x00405285
BuiltinFunctionEntry &BuiltinFunctionVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(BuiltinFunctionEntry);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(BuiltinFunctionEntry *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00405287
// FUNCTION: EDITOR 0x004052a9
OperatorEntry &OperatorEntryVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(OperatorEntry);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(OperatorEntry *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x004052a8
// FUNCTION: EDITOR 0x004052ca
void CharVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(char);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (char *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004052e6
// FUNCTION: EDITOR 0x00405308
char &CharVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(char);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(char *)((unsigned char *)m_begin + offset);
}

ParserRegisterInfo &ParserRegisterInfoVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(ParserRegisterInfo);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(ParserRegisterInfo *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00405304
// FUNCTION: EDITOR 0x00405326
SumoS32 ExpressionParser::IsDigit(char value) {
  return value >= '0' && value <= '9';
}

// FUNCTION: SUMO 0x0040531c
// FUNCTION: EDITOR 0x0040533e
void ParsedOperationVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(ParsedOperation);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (ParsedOperation *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040554a
// FUNCTION: EDITOR 0x0040556c
void CompiledOperationVector::PushBack(const CompiledOperation &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x00405572
// FUNCTION: EDITOR 0x00405594
void BuiltinFunctionVector::PushBack(const BuiltinFunctionEntry &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x0040559a
// FUNCTION: EDITOR 0x004055bc
void OperatorEntryVector::PushBack(const OperatorEntry &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x004056a4
// FUNCTION: EDITOR 0x004056c6
void CharVector::PushBack(const char &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x00405786
// FUNCTION: EDITOR 0x004057a8
void ParsedOperationVector::PushBack(const ParsedOperation &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

#pragma code_seg(push, float_vector_code, ".text$float_vector")

// FUNCTION: SUMO 0x00408f3c
// FUNCTION: EDITOR 0x00408f5e
SumoF32 &FloatVector::operator[](SumoU32 index) {
  unsigned char *begin = (unsigned char *)m_begin;
  index *= sizeof(SumoF32);
  if (index >= (SumoU32)((unsigned char *)m_end - begin)) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  return *(SumoF32 *)(begin + index);
}

#pragma code_seg(pop, float_vector_code)

#pragma code_seg(push, runtime_vector_code, ".text$runtime_vector")

// FUNCTION: SUMO 0x0040c0e7
// FUNCTION: EDITOR 0x0040c109
Vector3 &RuntimeVector3Vector::operator[](SumoU32 index) {
  unsigned char *begin = (unsigned char *)m_begin;
  index *= sizeof(Vector3);
  if (index >= (SumoU32)((unsigned char *)m_end - begin)) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  return *(Vector3 *)(begin + index);
}

// FUNCTION: SUMO 0x0040c109
// FUNCTION: EDITOR 0x0040c12b
void RuntimeVector3Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(Vector3);

  if (newSizeBytes >= 0x10000000) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  m_begin = (Vector3 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040c548
// FUNCTION: EDITOR 0x0040c56a
void RuntimeVector3Vector::Resize(SumoU32 size) {
  Vector3 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  Vector3 zero;
  memset(&zero, 0, sizeof(zero));
  while (oldEnd < m_end) {
    *oldEnd++ = zero;
  }
}

#pragma code_seg(pop, runtime_vector_code)

#pragma code_seg(push, replay_code, ".text$replay")

// FUNCTION: SUMO 0x0040d536
// FUNCTION: EDITOR 0x0040d558
SumoU32 &ReplayWordVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(SumoU32);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(SumoU32 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x0040d557
// FUNCTION: EDITOR 0x0040d579
void ReplayWordVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoU32);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (SumoU32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040d622
// FUNCTION: EDITOR 0x0040d644
void ReplayWordVector::Resize(SumoU32 size) {
  SumoU32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0;
  }
}

#pragma code_seg(pop, replay_code)

#pragma code_seg(push, float_vector_growth_code, ".text$float_vector_growth")

// FUNCTION: SUMO 0x00416572
// FUNCTION: EDITOR 0x00416594
void FloatVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoF32);

  if (newSizeBytes >= 0x10000000) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  m_begin = (SumoF32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004167b0
// FUNCTION: EDITOR 0x004167d2
void FloatVector::Resize(SumoU32 size) {
  SumoF32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0.0f;
  }
}

#pragma code_seg(pop, float_vector_growth_code)
