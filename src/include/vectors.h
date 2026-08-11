#ifndef SUMO_PARSER_CONTAINERS_H
#define SUMO_PARSER_CONTAINERS_H

#include <stdlib.h>

#include "types.h"

struct Vector3;
typedef Vector3 ParserValue;

struct ParserBuiltinCall {
  ParserValue *output;
  ParserValue *arguments[5];
};

typedef void(__cdecl *ParserCallback)(ParserBuiltinCall *call);

struct CompiledOperation {
  ParserCallback function;
  ParserBuiltinCall call;
};

struct BuiltinFunctionEntry {
  char name[16];
  SumoS32 argumentCount;
  ParserCallback function;
};

struct OperatorEntry {
  char symbol;
  SumoS8 precedence;
  SumoU16 padding;
  ParserCallback function;
};

struct ParsedOperation {
  void *function;
  SumoS32 argumentCount;
  SumoS32 outputRegister;
  SumoS32 arguments[5];
  char name[16];
};

struct ParserRegisterInfo {
  SumoS32 producerOperation;
  SumoS32 lastConsumer;
  SumoS32 valueIndex;
};

class CompiledOperationVector {
public:
  CompiledOperationVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~CompiledOperationVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  void Grow();
  void PushBack(const CompiledOperation &value);
  void Clear() { m_end = m_begin; }

private:
  friend class ExpressionParser;

  CompiledOperation *m_begin;
  CompiledOperation *m_end;
  CompiledOperation *m_capacity;
};

class BuiltinFunctionVector {
public:
  BuiltinFunctionVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~BuiltinFunctionVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  BuiltinFunctionEntry &operator[](SumoU32 index);
  void Grow();
  void PushBack(const BuiltinFunctionEntry &value);
  SumoS32 Size() const { return m_end - m_begin; }

private:
  friend class ExpressionParser;

  BuiltinFunctionEntry *m_begin;
  BuiltinFunctionEntry *m_end;
  BuiltinFunctionEntry *m_capacity;
};

class OperatorEntryVector {
public:
  OperatorEntryVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~OperatorEntryVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  OperatorEntry &operator[](SumoU32 index);
  void Grow();
  void PushBack(const OperatorEntry &value);
  SumoS32 Size() const { return m_end - m_begin; }

private:
  friend class ExpressionParser;

  OperatorEntry *m_begin;
  OperatorEntry *m_end;
  OperatorEntry *m_capacity;
};

class CharVector {
public:
  CharVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~CharVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  char &operator[](SumoU32 index);
  void Grow();
  void PushBack(const char &value);
  void Clear() { m_end = m_begin; }

private:
  friend class ExpressionParser;

  char *m_begin;
  char *m_end;
  char *m_capacity;
};

class ParsedOperationVector {
public:
  ParsedOperationVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~ParsedOperationVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  void Grow();
  void PushBack(const ParsedOperation &value);
  void Clear() { m_end = m_begin; }

private:
  friend class ExpressionParser;

  ParsedOperation *m_begin;
  ParsedOperation *m_end;
  ParsedOperation *m_capacity;
};

class ParserRegisterInfoVector {
public:
  ParserRegisterInfoVector() : m_begin(0), m_end(0), m_capacity(0) {}
  ~ParserRegisterInfoVector() {
    if (m_begin != 0) {
      free(m_begin);
      m_begin = 0;
    }
  }

  ParserRegisterInfo &operator[](SumoU32 index);

private:
  friend class ExpressionParser;
  ParserRegisterInfo *m_begin;
  ParserRegisterInfo *m_end;
  ParserRegisterInfo *m_capacity;
};

#endif
