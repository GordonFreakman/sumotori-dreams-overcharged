#include "big_integer.h"

// FUNCTION: SUMO 0x004011b6
// FUNCTION: EDITOR 0x004011b6
__declspec(nothrow) BigInteger& BigInteger::operator=(BigInteger& other)
{
  CopyFrom(other);
  m_sign = other.m_sign;
  return *this;
}
