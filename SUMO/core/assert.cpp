#include "assert.h"
#include "containers.h"
#include "decomp.h"
#include "game_replay.h"
#include "expression_parser.h"
#include "parser_containers.h"
#include "parser_helpers.h"

#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset)

static __forceinline void ContainerAssert(bool condition) {
  unsigned char *address = 0;
  while (!condition) {
    ++address;
    *address = 0x7f;
  }
}

DECOMP_SIZE_ASSERT(U32Vector, 0x0c);
DECOMP_SIZE_ASSERT(Vector3, 0x0c);
DECOMP_SIZE_ASSERT(Matrix3, 0x24);
DECOMP_SIZE_ASSERT(Vector3Vector, 0x0c);
DECOMP_SIZE_ASSERT(RuntimeVector3Vector, 0x0c);
DECOMP_SIZE_ASSERT(FloatVector, 0x0c);

// FUNCTION: SUMO 0x00401000
// FUNCTION: EDITOR 0x00401000
SumoU32 &U32Vector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(SumoU32);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(SumoU32 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00401021
// FUNCTION: EDITOR 0x00401021
void U32Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoU32);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (SumoU32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x00401111
// FUNCTION: EDITOR 0x00401111
void U32Vector::Resize(SumoU32 size) {
  SumoU32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0;
  }
}

// FUNCTION: SUMO 0x00401193
// FUNCTION: EDITOR 0x00401193
void U32Vector::PushBack(const SumoU32 &value) {
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x004011d1
// FUNCTION: EDITOR 0x004011d1
void U32Vector::PadTo(SumoU32 size) {
  SumoU32 currentSize = m_end - m_begin;

  if (currentSize < size) {
    SumoU32 zero = 0;
    do {
      PushBack(zero);
      currentSize = m_end - m_begin;
    } while (currentSize < size);
  }
}

#include "big_integer.h"

#include "assert.h"

// FUNCTION: SUMO 0x004019b1
// FUNCTION: EDITOR 0x004019b1
void Divide(BigInteger* dividend, BigInteger* divisor, BigInteger* quotient)
{
  SumoAssert(quotient != dividend && quotient != divisor);
  SumoAssert(dividend->m_sign == 1 && divisor->m_sign == 1);

  if (divisor->Size() == 0) {
    SumoU8* invalidAddress = 0;
    for (;;) {
      *++invalidAddress = 0x7f;
    }
  }

  SumoS32 limbDifference = dividend->Size() - divisor->Size() + 1;
  quotient->SetPositive(0);
  SumoS32 bit = limbDifference * 32 - 1;
  BigInteger remainder(0);

  while (bit >= 0) {
    quotient->SetBit(bit, 1);
    BigInteger previousRemainder(remainder);

    remainder += *divisor << bit;

    if (remainder > *dividend) {
      quotient->SetBit(bit, 0);
      remainder = previousRemainder;
    }

    --bit;
  }

  quotient->TrimLeadingZeros();
}


// FUNCTION: SUMO 0x00404730
// FUNCTION: EDITOR 0x00404752
void SumoAssert(bool condition) {
  unsigned char *address = 0;

  while (!condition) {
    ++address;
    *address = 0x7f;
  }
}

// FUNCTION: SUMO 0x00404fcc
// FUNCTION: EDITOR 0x00404fee
Vector3 &Vector3Vector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(Vector3);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(Vector3 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00404ff0
// FUNCTION: EDITOR 0x00405012
void SkipWhitespace(char** cursor)
{
  while (
    **cursor == ' ' ||
    **cursor == '\t' ||
    **cursor == '\r' ||
    **cursor == '\n'
  ) {
    ++*cursor;
  }
}

#include "parser_containers.h"

#include "assert.h"
#include "decomp.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(CompiledOperation, 0x1c);
DECOMP_SIZE_ASSERT(BuiltinFunctionEntry, 0x18);
DECOMP_SIZE_ASSERT(OperatorEntry, 0x08);
DECOMP_SIZE_ASSERT(ParsedOperation, 0x30);
DECOMP_SIZE_ASSERT(CompiledOperationVector, 0x0c);
DECOMP_SIZE_ASSERT(BuiltinFunctionVector, 0x0c);
DECOMP_SIZE_ASSERT(OperatorEntryVector, 0x0c);
DECOMP_SIZE_ASSERT(CharVector, 0x0c);
DECOMP_SIZE_ASSERT(ParsedOperationVector, 0x0c);

// FUNCTION: SUMO 0x00405012
// FUNCTION: EDITOR 0x00405034
void CompiledOperationVector::Grow()
{
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(CompiledOperation);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (CompiledOperation*) realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040505b
// FUNCTION: EDITOR 0x0040507d
void BuiltinFunctionVector::Grow()
{
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(BuiltinFunctionEntry);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (BuiltinFunctionEntry*) realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004050a8
// FUNCTION: EDITOR 0x004050ca
void OperatorEntryVector::Grow()
{
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(OperatorEntry);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (OperatorEntry*) realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040513b
// FUNCTION: EDITOR 0x0040515d
SumoS32 ExpressionParser::IsIdentifierStart(char value)
{
  return
    (value >= 'a' && value <= 'z') ||
    (value >= 'A' && value <= 'Z') ||
    value == '_';
}

// FUNCTION: SUMO 0x0040520c
// FUNCTION: EDITOR 0x0040522e
SumoS32 ExpressionParser::IsIdentifierContinue(char value)
{
  return
    (value >= 'a' && value <= 'z') ||
    (value >= 'A' && value <= 'Z') ||
    value == '_' ||
    (value >= '0' && value <= '9');
}

// FUNCTION: SUMO 0x00405263
// FUNCTION: EDITOR 0x00405285
BuiltinFunctionEntry &BuiltinFunctionVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(BuiltinFunctionEntry);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(BuiltinFunctionEntry *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00405287
// FUNCTION: EDITOR 0x004052a9
OperatorEntry &OperatorEntryVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(OperatorEntry);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(OperatorEntry *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x004052a8
// FUNCTION: EDITOR 0x004052ca
void CharVector::Grow()
{
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(char);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (char*) realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004052e6
// FUNCTION: EDITOR 0x00405308
char &CharVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(char);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(char *)((unsigned char *)m_begin + offset);
}

ParserRegisterInfo &ParserRegisterInfoVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(ParserRegisterInfo);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(ParserRegisterInfo *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x00405304
// FUNCTION: EDITOR 0x00405326
SumoS32 ExpressionParser::IsDigit(char value)
{
  return value >= '0' && value <= '9';
}

// FUNCTION: SUMO 0x0040531c
// FUNCTION: EDITOR 0x0040533e
void ParsedOperationVector::Grow()
{
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(ParsedOperation);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (ParsedOperation*) realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040554a
// FUNCTION: EDITOR 0x0040556c
void CompiledOperationVector::PushBack(const CompiledOperation& value)
{
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x00405572
// FUNCTION: EDITOR 0x00405594
void BuiltinFunctionVector::PushBack(const BuiltinFunctionEntry& value)
{
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x0040559a
// FUNCTION: EDITOR 0x004055bc
void OperatorEntryVector::PushBack(const OperatorEntry& value)
{
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x004056a4
// FUNCTION: EDITOR 0x004056c6
void CharVector::PushBack(const char& value)
{
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

// FUNCTION: SUMO 0x00405786
// FUNCTION: EDITOR 0x004057a8
void ParsedOperationVector::PushBack(const ParsedOperation& value)
{
  if (m_end >= m_capacity) {
    Grow();
  }

  *m_end = value;
  ++m_end;
}

#pragma code_seg(push, float_vector_code, ".text$float_vector")

// FUNCTION: SUMO 0x00408f3c
// FUNCTION: EDITOR 0x00408f5e
SumoF32 &FloatVector::operator[](SumoU32 index) {
  unsigned char *begin = (unsigned char *)m_begin;
  index *= sizeof(SumoF32);
  if (index >= (SumoU32)((unsigned char *)m_end - begin)) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  return *(SumoF32 *)(begin + index);
}

#pragma code_seg(pop, float_vector_code)

#pragma code_seg(push, runtime_vector_code, ".text$runtime_vector")

// FUNCTION: SUMO 0x0040c0e7
// FUNCTION: EDITOR 0x0040c109
Vector3 &RuntimeVector3Vector::operator[](SumoU32 index) {
  unsigned char *begin = (unsigned char *)m_begin;
  index *= sizeof(Vector3);
  if (index >= (SumoU32)((unsigned char *)m_end - begin)) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  return *(Vector3 *)(begin + index);
}

// FUNCTION: SUMO 0x0040c109
// FUNCTION: EDITOR 0x0040c12b
void RuntimeVector3Vector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(Vector3);

  if (newSizeBytes >= 0x10000000) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  m_begin = (Vector3 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040c548
// FUNCTION: EDITOR 0x0040c56a
void RuntimeVector3Vector::Resize(SumoU32 size) {
  Vector3 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  Vector3 zero;
  memset(&zero, 0, sizeof(zero));
  while (oldEnd < m_end) {
    *oldEnd++ = zero;
  }
}

#pragma code_seg(pop, runtime_vector_code)

#pragma code_seg(push, replay_code, ".text$replay")

// FUNCTION: SUMO 0x0040d536
// FUNCTION: EDITOR 0x0040d558
SumoU32 &ReplayWordVector::operator[](SumoU32 index) {
  SumoU32 offset = index * sizeof(SumoU32);
  SumoAssert(offset <
             (SumoU32)((unsigned char *)m_end - (unsigned char *)m_begin));
  return *(SumoU32 *)((unsigned char *)m_begin + offset);
}

// FUNCTION: SUMO 0x0040d557
// FUNCTION: EDITOR 0x0040d579
void ReplayWordVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoU32);

  SumoAssert(newSizeBytes < 0x10000000);
  m_begin = (SumoU32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x0040d622
// FUNCTION: EDITOR 0x0040d644
void ReplayWordVector::Resize(SumoU32 size) {
  SumoU32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0;
  }
}

#pragma code_seg(pop, replay_code)

#pragma code_seg(push, float_vector_growth_code, ".text$float_vector_growth")

// FUNCTION: SUMO 0x00416572
// FUNCTION: EDITOR 0x00416594
void FloatVector::Grow() {
  SumoU32 oldSize = m_end - m_begin;
  SumoU32 newCapacity = (oldSize >> 3) + oldSize + 1;
  SumoU32 newSizeBytes = newCapacity * sizeof(SumoF32);

  if (newSizeBytes >= 0x10000000) {
    unsigned char *address = 0;
    do {
      ++address;
      *address = 0x7f;
    } while (true);
  }
  m_begin = (SumoF32 *)realloc(m_begin, newSizeBytes);
  m_capacity = m_begin + newCapacity;
  m_end = m_begin + oldSize;
}

// FUNCTION: SUMO 0x004167b0
// FUNCTION: EDITOR 0x004167d2
void FloatVector::Resize(SumoU32 size) {
  SumoF32 *oldEnd = m_end;
  m_end = m_begin + size;

  if (m_end > m_capacity) {
    SumoU32 oldSize = oldEnd - m_begin;
    Grow();
    oldEnd = m_begin + oldSize;
  }

  while (oldEnd < m_end) {
    *oldEnd++ = 0.0f;
  }
}

#pragma code_seg(pop, float_vector_growth_code)
