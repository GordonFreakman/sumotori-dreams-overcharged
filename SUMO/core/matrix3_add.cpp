#include "containers.h"

// FUNCTION: SUMO 0x0040807d
// FUNCTION: EDITOR 0x0040809f
Matrix3 Matrix3::operator+(Matrix3& other)
{
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
