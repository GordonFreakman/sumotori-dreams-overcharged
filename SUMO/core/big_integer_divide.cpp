#include "big_integer.h"

// FUNCTION: SUMO 0x00401adb
// FUNCTION: EDITOR 0x00401adb
BigInteger BigInteger::operator%(BigInteger& other)
{
  BigInteger quotient;
  Divide(this, &other, &quotient);
  return *this - quotient * other;
}

// FUNCTION: SUMO 0x00401b5c
// FUNCTION: EDITOR 0x00401b5c
BigInteger BigInteger::operator/(BigInteger& other)
{
  BigInteger result;
  Divide(this, &other, &result);
  return result;
}
