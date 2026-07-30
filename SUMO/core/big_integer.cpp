#include "big_integer.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(BigInteger, 0x10);

// FUNCTION: SUMO 0x00401247
// FUNCTION: EDITOR 0x00401247
BigInteger::BigInteger(BigInteger& other)
{
  CopyFrom(other);
  m_sign = other.m_sign;
}

// FUNCTION: SUMO 0x0040126c
// FUNCTION: EDITOR 0x0040126c
void BigInteger::SetPositive(SumoU32 value)
{
  Resize(1);
  (*this)[0] = value;
  m_sign = 1;
}

// FUNCTION: SUMO 0x00401290
// FUNCTION: EDITOR 0x00401290
void BigInteger::SetBit(SumoS32 bit, SumoS32 value)
{
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
void BigInteger::operator++(int)
{
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
void BigInteger::AppendLimb(SumoU32 value)
{
  TrimLeadingZeros();
  PushBack(value);
}

// FUNCTION: SUMO 0x00401360
// FUNCTION: EDITOR 0x00401360
BigInteger::BigInteger()
{
  BigInteger(0);
}
