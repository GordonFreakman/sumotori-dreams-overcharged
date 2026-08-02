#ifndef SUMO_BIG_INTEGER_H
#define SUMO_BIG_INTEGER_H

#include "containers.h"

class BigInteger;
void Divide(BigInteger *dividend, BigInteger *divisor, BigInteger *quotient);

class BigInteger : public U32Vector {
public:
  BigInteger();
  explicit BigInteger(SumoS32 value);
  BigInteger(BigInteger &other);
  BigInteger(char *text, SumoS32 length, const char *alphabet, SumoS32 radix);

  // FUNCTION: SUMO 0x00401067
  // FUNCTION: EDITOR 0x00401067
  ~BigInteger() {}

  __declspec(nothrow) BigInteger &operator=(BigInteger &other);
  void operator-=(BigInteger &other);
  void operator+=(BigInteger &other);
  BigInteger operator+(BigInteger &other);
  BigInteger operator-(BigInteger &other);
  __declspec(nothrow) BigInteger operator*(BigInteger &other);
  __declspec(nothrow) BigInteger operator<<(SumoS32 p_bits);
  BigInteger operator/(BigInteger &other);
  BigInteger operator%(BigInteger &other);
  bool operator==(BigInteger &other);
  bool operator>(BigInteger &other);
  SumoS32 Log(BigInteger &base);
  BigInteger Power(SumoS32 exponent);
  void ModularPower(BigInteger &base, BigInteger &exponent,
                    BigInteger &modulus);
  void WriteString(char *output, SumoS32 capacity, const char *alphabet,
                   SumoS32 radix, SumoS32 minimumDigits);

  void SetPositive(SumoU32 value);
  void SetBit(SumoS32 bit, SumoS32 value);
  void operator++(int);
  void AppendLimb(SumoU32 value);

private:
  friend void Divide(BigInteger *dividend, BigInteger *divisor,
                     BigInteger *quotient);

  SumoS32 m_sign;
};

#endif
