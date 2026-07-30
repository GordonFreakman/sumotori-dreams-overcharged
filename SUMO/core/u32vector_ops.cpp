#include "containers.h"

// FUNCTION: SUMO 0x0040106c
// FUNCTION: EDITOR 0x0040106c
void U32Vector::TrimLeadingZeros()
{
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
void U32Vector::Invert()
{
  for (SumoU32 i = 0; i < Size(); ++i) {
    SumoU32& value = (*this)[i];
    value = ~value;
  }
}

// FUNCTION: SUMO 0x004010d6
// FUNCTION: EDITOR 0x004010d6
SumoS32 U32Vector::TestBit(SumoS32 bit)
{
  if ((SumoU32) bit >= Size() * 32) {
    return false;
  }

  return ((*this)[bit / 32] & (1 << (bit % 32))) != 0;
}

// FUNCTION: SUMO 0x0040114e
// FUNCTION: EDITOR 0x0040114e
void U32Vector::CopyFrom(U32Vector& other)
{
  Resize(other.Size());

  for (SumoU32 i = 0; i < other.Size(); ++i) {
    m_begin[i] = other[i];
  }
}
