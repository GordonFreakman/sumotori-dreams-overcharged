#include "big_integer.h"

// FUNCTION: SUMO 0x0040180e
// FUNCTION: EDITOR 0x0040180e
BigInteger::BigInteger(char *p_text, SumoS32 p_length, const char *p_alphabet, SumoS32 p_radix) {
  if (p_length == 0) {
    char *end = p_text;
    while (*end != 0) {
      ++end;
      ++p_length;
    }
  }

  if (p_alphabet == NULL) {
    p_alphabet = "0123456789";
  }

  SetPositive(0);
  BigInteger place(1);
  p_text += p_length;

  while (p_length > 0) {
    --p_text;

    SumoS32 digit = 0;
    while (digit < p_radix) {
      if (p_alphabet[digit] == *p_text) {
        *this += place * BigInteger(digit);
        place = place * BigInteger(p_radix);
        break;
      }

      ++digit;
    }

    --p_length;
  }
}
