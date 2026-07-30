#include "big_integer.h"

// FUNCTION: SUMO 0x00401948
// FUNCTION: EDITOR 0x00401948
bool BigInteger::operator==(BigInteger& other)
{
  BigInteger difference = *this - other;
  return difference.Size() == 0;
}

// FUNCTION: SUMO 0x00401980
// FUNCTION: EDITOR 0x00401980
bool BigInteger::operator>(BigInteger& other)
{
  BigInteger difference = other - *this;
  return difference.m_sign == -1;
}
