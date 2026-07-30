#include "containers.h"

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
