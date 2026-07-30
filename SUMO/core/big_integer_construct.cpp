#include "big_integer.h"

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
