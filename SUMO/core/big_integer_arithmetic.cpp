#include "big_integer.h"

#include "assert.h"

// FUNCTION: SUMO 0x00401764
// FUNCTION: EDITOR 0x00401764
BigInteger BigInteger::operator+(BigInteger& other)
{
  BigInteger result(*this);
  result += other;
  return result;
}

// FUNCTION: SUMO 0x004017b9
// FUNCTION: EDITOR 0x004017b9
BigInteger BigInteger::operator-(BigInteger& other)
{
  BigInteger result(*this);
  result -= other;
  return result;
}
