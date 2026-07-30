#include "big_integer.h"

// FUNCTION: SUMO 0x00401e60
// FUNCTION: EDITOR 0x00401e60
void BigInteger::ModularPower(
  BigInteger& base,
  BigInteger& exponent,
  BigInteger& modulus
)
{
  SetPositive(1);
  BigInteger factor(base);
  BigInteger bitValue(1);
  SumoS32 bit = 0;

  do {
    if (exponent.TestBit(bit)) {
      *this = (*this * factor) % modulus;
    }

    ++bit;
    bitValue = bitValue + bitValue;
    factor = (factor * factor) % modulus;
  } while (!(bitValue > exponent));
}
