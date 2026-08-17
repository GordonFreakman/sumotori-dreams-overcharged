#ifndef SUMO_TYPES_H
#define SUMO_TYPES_H

#define MENU_START_INDEX 12
#define SUMO_CSM

typedef signed char SumoS8;
typedef unsigned char SumoU8;
typedef signed short SumoS16;
typedef unsigned short SumoU16;
typedef signed int SumoS32;
typedef unsigned int SumoU32;
#if !defined(_MSC_VER)
typedef signed long long SumoS64;
typedef unsigned long long SumoU64;
#else
typedef signed __int64 SumoS64;
typedef unsigned __int64 SumoU64;
#endif
typedef float SumoF32;
typedef double SumoF64;

#if (defined(_WIN64) ||                                                        \
     (defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8))
typedef SumoS64 SumoIntPtr;
typedef SumoU64 SumoUIntPtr;
#else
typedef SumoS32 SumoIntPtr;
typedef SumoU32 SumoUIntPtr;
#endif

typedef unsigned char undefined;
typedef unsigned short undefined2;
typedef unsigned int undefined4;

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
  inline void AddInline(Vector3 &other) {
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
  inline void SetRow0(Vector3 row) {
    m00 = row.x;
    m01 = row.y;
    m02 = row.z;
  }
  inline void SetRow1(Vector3 row) {
    m10 = row.x;
    m11 = row.y;
    m12 = row.z;
  }
  inline void SetRow2(Vector3 row) {
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

struct GameBoxLitVertex {
  Vector3 position;
#ifndef SUMO_CSM
  SumoS32 color;
#else
  Vector3 normals;
  Vector3 worldPosition;
  Matrix3 orientation;
#endif
  SumoF32 u;
  SumoF32 v;
};

#endif
