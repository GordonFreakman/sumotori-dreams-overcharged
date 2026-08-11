#include "decomp_keywords.h"
#include "parser.h"
#include "decomp.h"
#include "runtime.h"
#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(ParserValue, 0x0c);
DECOMP_SIZE_ASSERT(ParserBuiltinCall, 0x18);
DECOMP_SIZE_ASSERT(ParserVariable, 0x2c);
DECOMP_SIZE_ASSERT(UserFunction, 0x128);
DECOMP_SIZE_ASSERT(ParserRegisterInfo, 0x0c);
DECOMP_SIZE_ASSERT(ParserRegisterInfoVector, 0x0c);
DECOMP_SIZE_ASSERT(ExpressionParser, 0x3094);

// GLOBAL: SUMO 0x0042c2cc
// GLOBAL: EDITOR 0x0042c2cc
extern const SumoF32 g_parserPi = 3.1415927f;

// GLOBAL: SUMO 0x0042c2d4
// GLOBAL: EDITOR 0x0042c2d4
extern const SumoF32 g_gameBoxYScale = -1.0f;

// GLOBAL: SUMO 0x0042c2dc
// GLOBAL: EDITOR 0x0042c2dc
extern const char g_parserIdentifierTooLong[] = "identifier too long";

// FUNCTION: SUMO 0x00404693
// FUNCTION: EDITOR 0x004046b5
SumoF64 ParserAtan2(SumoF32 y, SumoF32 x) {
  return atan2((SumoF64)y, (SumoF64)x);
}

// FUNCTION: SUMO 0x004046ae
// FUNCTION: EDITOR 0x004046d0
SumoF64 ParserModulo(SumoF32 value, SumoF32 divisor) {
  return fmod((SumoF64)value, (SumoF64)divisor);
}

// FUNCTION: SUMO 0x004046c9
// FUNCTION: EDITOR 0x004046eb
SumoF32 ParserAtan2Value(SumoF32 y, SumoF32 x) { return ParserAtan2(y, x); }

// FUNCTION: SUMO 0x004046e2
// FUNCTION: EDITOR 0x00404704
SumoF32 ParserModuloValue(SumoF32 value, SumoF32 divisor) {
  return ParserModulo(value, divisor);
}

// FUNCTION: SUMO 0x0040473f
// FUNCTION: EDITOR 0x00404761
ParserValue MakeParserValue(SumoF32 value) {
  return MakeVector3(value, value, value);
}

// FUNCTION: SUMO 0x00404778
// FUNCTION: EDITOR 0x0040479a
void ParserBuiltinAtanXY(ParserBuiltinCall *call) {
  ParserValue value = MakeParserValue(
      ParserAtan2Value(call->arguments[0]->x, call->arguments[0]->y));
  *call->output = value;
}

// FUNCTION: SUMO 0x004047be
// FUNCTION: EDITOR 0x004047e0
void ParserBuiltinAbs(ParserBuiltinCall *call) {
  SumoF64 length = sqrt(call->arguments[0]->LengthSquared());
  ParserValue value = MakeParserValue((SumoF32)length);
  *call->output = value;
}

// FUNCTION: SUMO 0x00404806
// FUNCTION: EDITOR 0x00404828
void ParserBuiltinVector(ParserBuiltinCall *call) {
  ParserValue value = MakeVector3(call->arguments[0]->x, call->arguments[1]->x,
                                  call->arguments[2]->x);
  *call->output = value;
}

// FUNCTION: SUMO 0x00404850
// FUNCTION: EDITOR 0x00404872
void ParserBuiltinSelectX(ParserBuiltinCall *call) {
  if (call->arguments[0]->x > g_vectorZero) {
    *call->output = *call->arguments[1];
  } else {
    *call->output = *call->arguments[2];
  }
}

// FUNCTION: SUMO 0x00404878
// FUNCTION: EDITOR 0x0040489a
void ParserBuiltinModulo(ParserBuiltinCall *call) {
  ParserValue value = MakeVector3(
      ParserModuloValue(call->arguments[0]->x, call->arguments[1]->x),
      ParserModuloValue(call->arguments[0]->y, call->arguments[1]->y),
      ParserModuloValue(call->arguments[0]->z, call->arguments[1]->z));
  *call->output = value;
}

// FUNCTION: SUMO 0x004048f9
// FUNCTION: EDITOR 0x0040491b
void ParserBuiltinCos(ParserBuiltinCall *call) {
  ParserValue value = MakeVector3((SumoF32)cos(call->arguments[0]->x),
                                  (SumoF32)cos(call->arguments[0]->y),
                                  (SumoF32)cos(call->arguments[0]->z));
  *call->output = value;
}

// FUNCTION: SUMO 0x0040496b
// FUNCTION: EDITOR 0x0040498d
void ParserBuiltinDot(ParserBuiltinCall *call) {
  ParserValue value =
      MakeParserValue(call->arguments[0]->Dot(*call->arguments[1]));
  *call->output = value;
}

// FUNCTION: SUMO 0x004049b5
// FUNCTION: EDITOR 0x004049d7
void ParserBuiltinNormalize(ParserBuiltinCall *call) {
  *call->output = call->arguments[0]->Normalized();
}

// FUNCTION: SUMO 0x004049d7
// FUNCTION: EDITOR 0x004049f9
void ParserOperatorAdd(ParserBuiltinCall *call) {
  *call->output = *call->arguments[0] + *call->arguments[1];
}

// FUNCTION: SUMO 0x004049fc
// FUNCTION: EDITOR 0x00404a1e
void ParserOperatorSubtract(ParserBuiltinCall *call) {
  *call->output = *call->arguments[0] - *call->arguments[1];
}

// FUNCTION: SUMO 0x00404a21
// FUNCTION: EDITOR 0x00404a43
void ParserOperatorMultiply(ParserBuiltinCall *call) {
  *call->output = call->arguments[0]->MultiplyComponents(*call->arguments[1]);
}

// FUNCTION: SUMO 0x00404a46
// FUNCTION: EDITOR 0x00404a68
void ParserOperatorDivide(ParserBuiltinCall *call) {
  ParserValue value =
      MakeVector3(call->arguments[0]->x / call->arguments[1]->x,
                  call->arguments[0]->y / call->arguments[1]->y,
                  call->arguments[0]->z / call->arguments[1]->z);
  *call->output = value;
}

// FUNCTION: SUMO 0x00404a97
// FUNCTION: EDITOR 0x00404ab9
SumoF32 ParserPower(SumoF32 base, SumoF32 exponent) {
  if (base < g_vectorZero) {
    SumoF32 power = (SumoF32)(log((SumoF64)-base) * exponent);
    SumoF32 sign = (SumoF32)cos(exponent * g_parserPi);
    return (SumoF32)(exp((SumoF64)power) * sign);
  }

  return (SumoF32)exp(log((SumoF64)base) * exponent);
}

// FUNCTION: SUMO 0x00404afe
// FUNCTION: EDITOR 0x00404b20
void ParserOperatorPower(ParserBuiltinCall *call) {
  ParserValue value = MakeVector3(
      (SumoF32)ParserPower(call->arguments[0]->x, call->arguments[1]->x),
      (SumoF32)ParserPower(call->arguments[0]->y, call->arguments[1]->y),
      (SumoF32)ParserPower(call->arguments[0]->z, call->arguments[1]->z));
  *call->output = value;
}

// GLOBAL: SUMO 0x00453420
// GLOBAL: EDITOR 0x00453420
BuiltinFunctionEntry g_parserBuiltinFunctions[] = {
    {"atanxy", 1, ParserBuiltinAtanXY},
    {"abs", 1, ParserBuiltinAbs},
    {"vec", 3, ParserBuiltinVector},
    {"selx", 3, ParserBuiltinSelectX},
    {"cos", 1, ParserBuiltinCos},
    {"sin", 1, ParserBuiltinCos},
    {"tan", 1, ParserBuiltinCos},
    {"atan", 1, ParserBuiltinCos},
    {"rot", 2, ParserBuiltinRotate},
    {"dot", 2, ParserBuiltinDot},
    {"normalize", 1, ParserBuiltinNormalize},
    {"mod", 2, ParserBuiltinModulo}};

// GLOBAL: SUMO 0x00453540
// GLOBAL: EDITOR 0x00453540
OperatorEntry g_parserOperators[] = {{'+', 0, 0, ParserOperatorAdd},
                                     {'-', 0, 0, ParserOperatorSubtract},
                                     {'*', 1, 0, ParserOperatorMultiply},
                                     {'/', 1, 0, ParserOperatorDivide},
                                     {'^', 2, 0, ParserOperatorPower}};

// GLOBAL: SUMO 0x00453568
// GLOBAL: EDITOR 0x00453568
BuiltinFunctionEntry g_gameBuiltinFunctions[6] = {
    {"addbox", 4, ParserBuiltinAddBox},
    {"cutplane", 2, ParserBuiltinCutPlane},
    {"random", 1, ParserBuiltinRandom},
    {"turnto", 1, ParserBuiltinTurnTo},
    {"man", 3, ParserBuiltinMan},
    {"breakability", 1, ParserBuiltinBreakability}};

// FUNCTION: SUMO 0x00404b7f
// FUNCTION: EDITOR 0x00404ba1
ParserValue ExpressionParser::ConvertScalar(SumoF64 value) {
  SumoF32 scalar = (SumoF32)value;
  return MakeVector3(scalar, scalar, scalar);
}

// FUNCTION: SUMO 0x00404bb4
// FUNCTION: EDITOR 0x00404bd6
void ParserBuiltinAddBox(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_currentBox != 0) {
    Matrix3 savedOrientation = g_currentBox->orientation;
    SumoF32 savedBreakability = g_currentBox->breakability;
    bool wasImmovable = g_currentBox->flagD0;

    g_currentBox->FinishContacts(1);
    g_currentBox->RecalculateMass();
    g_currentBox->ClearForces();
    g_currentBox->InitializePhysics();
    if (wasImmovable) {
      g_currentBox->MakeImmovable();
    }

    g_currentBox->orientation = savedOrientation;
    g_currentBox->breakability = savedBreakability;
  }

  Vector3 halfSize = *call->arguments[0];
  halfSize.y *= g_gameBoxYScale;

  SumoS32 type = (SumoS32)call->arguments[2]->x;
  if (type < 0) {
    type = 0;
  }
  if (type >= 31) {
    type = 31;
  }

  g_currentBox =
      CreateGameBox(halfSize, *call->arguments[1], type, g_gameBoxDefaultValue);
  if ((SumoS32)call->arguments[3]->x != 0) {
    g_currentBox->MakeImmovable();
  }
}

// FUNCTION: SUMO 0x00404cc2
// FUNCTION: EDITOR 0x00404ce4
void ParserBuiltinBreakability(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_currentBox != 0) {
    SumoF32 minimumBreakability = g_parserMinimumBreakability;
    g_currentBox->breakability = call->arguments[0]->x;
    if (minimumBreakability > g_currentBox->breakability) {
      g_currentBox->breakability = minimumBreakability;
    }
  }
}

// FUNCTION: SUMO 0x00404d04
// FUNCTION: EDITOR 0x00404d26
void ParserBuiltinRandom(ParserBuiltinCall *call) {
  ParserValue value = MakeVector3(g_gameRandom.Next() * 2.0f - g_gameOne,
                                  g_gameRandom.Next() * 2.0f - g_gameOne,
                                  g_gameRandom.Next() * 2.0f - g_gameOne);
  *call->output = value;
}

// FUNCTION: SUMO 0x00404e31
// FUNCTION: EDITOR 0x00404e53
void ParserBuiltinMan(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_gameIsRunning != 0) {
    if (g_nextGameMan < g_gameMen + 4) {
      g_nextGameMan->Initialize(
          *call->arguments[0],
          ParserAtan2Value(call->arguments[1]->x, call->arguments[1]->z),
          (SumoS32)call->arguments[2]->x, 0);
      g_nextGameMan->active = 0;
      g_nextGameMan->mode = 2;
      if ((SumoS32)call->arguments[2]->x == 3) {
        g_nextGameMan->mode = 1;
      }
      if ((SumoS32)call->arguments[2]->x == 2) {
        g_nextGameMan->mode = 0;
      }
      g_nextGameMan->active = 1;
      ++g_nextGameMan;
    }
  } else if (g_pendingManCount <= 8) {
    g_pendingManPositions[g_pendingManCount] = *call->arguments[0];
    g_pendingManAngles[g_pendingManCount] =
        ParserAtan2Value(call->arguments[1]->x, call->arguments[1]->z);
    ++g_pendingManCount;
  }
}

// FUNCTION: SUMO 0x00404f4a
// FUNCTION: EDITOR 0x00404f6c
void ParserBuiltinCutPlane(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_currentBox != 0) {
    g_currentBox->CutPlane(*call->arguments[0], call->arguments[1]->x);
  }
}

// FUNCTION: SUMO 0x00404f8f
// FUNCTION: EDITOR 0x00404fb1
ParserVariable *ExpressionParser::AllocateVariable() {
  ParserVariable *variable = new ParserVariable;
  variable->next = m_localVariables;
  variable->previous = 0;
  if (m_localVariables != 0) {
    m_localVariables->previous = variable;
  }
  m_localVariables = variable;
  variable->isConstant = 0;
  variable->valueIndex = -1;
  variable->value = m_defaultValue;
  variable->name[0] = 0;
  return variable;
}

// FUNCTION: SUMO 0x0040515d
// FUNCTION: EDITOR 0x0040517f
ParserVariable *ExpressionParser::FindVariable(char *name) {
  ParserVariable *variable;

  for (variable = m_globalVariables; variable != 0; variable = variable->next) {
    if (strcmp(name, variable->name) == 0) {
      return variable;
    }
  }

  for (variable = m_localVariables; variable != 0; variable = variable->next) {
    if (strcmp(name, variable->name) == 0) {
      return variable;
    }
  }

  return 0;
}

// FUNCTION: SUMO 0x00405236
// FUNCTION: EDITOR 0x00405258
UserFunction *ExpressionParser::FindUserFunction(char *name) {
  UserFunction *function = m_userFunctions;

  while (function != 0) {
    if (strcmp(function->name, name) == 0) {
      return function;
    }
    function = function->next;
  }

  return 0;
}

// FUNCTION: SUMO 0x0040536b
// FUNCTION: EDITOR 0x0040538d
void ParserBuiltinRotate(ParserBuiltinCall *call) {
  ParserValue value = *call->arguments[0];
  value.Rotate(*call->arguments[1]);
  *call->output = value;
}

// FUNCTION: SUMO 0x00405398
// FUNCTION: EDITOR 0x004053ba
ExpressionParser::ExpressionParser() {}

// FUNCTION: SUMO 0x004053e9
// FUNCTION: EDITOR 0x0040540b
void ExpressionParser::DestroyStorage() {
  m_valueMappings.~ParserRegisterInfoVector();
  m_operators.~OperatorEntryVector();
  m_builtins.~BuiltinFunctionVector();
  m_parsed.~ParsedOperationVector();
  m_operations.~CompiledOperationVector();
}

// FUNCTION: SUMO 0x00405429
// FUNCTION: EDITOR 0x0040544b
void ExpressionParser::AddConstant(char *name, ParserValue value) {
  ParserVariable *variable = AllocateVariable();
  variable->isConstant = 1;
  strcpy(variable->name, name);
  variable->valueIndex = -1;
  variable->value = value;
}

// FUNCTION: SUMO 0x00405458
// FUNCTION: EDITOR 0x0040547a
void ExpressionParser::Reset() {
  m_localVariables = 0;
  if (m_hasError) {
    m_hasError = false;
  }
  m_operations.Clear();
  m_parsed.Clear();
  m_valueCount = 0;

  m_currentVariable = AllocateVariable();
  m_currentVariable->isConstant = 1;
  strcpy(m_currentVariable->name, "ans");
  m_currentVariable->valueIndex = -1;
  m_currentVariable->value = m_defaultValue;
}

// FUNCTION: SUMO 0x004054bd
// FUNCTION: EDITOR 0x004054df
void ExpressionParser::Initialize(ParserValue value) {
  m_localVariables = 0;
  if (m_hasError) {
    m_hasError = false;
  }
  m_operations.Clear();
  m_parsed.Clear();
  m_defaultValueIndex = -1;
  m_defaultValue = value;
  m_initialValue = value;
  m_maxPrecedence = 0;
  m_valueCount = 0;

  m_currentVariable = AllocateVariable();
  m_currentVariable->isConstant = 1;
  // STRING: SUMO 0x0042c2d8
  // STRING: EDITOR 0x0042c2d8
  strcpy(m_currentVariable->name, "ans");
  m_currentVariable->valueIndex = -1;
  m_currentVariable->value = m_defaultValue;
}

// FUNCTION: SUMO 0x004056c6
// FUNCTION: EDITOR 0x004056e8
UserFunction *ExpressionParser::AllocateUserFunction() {
  UserFunction *function = (UserFunction *)malloc(sizeof(UserFunction));
  function->next = m_userFunctions;
  function->previous = 0;

  if (m_userFunctions != 0) {
    m_userFunctions->previous = function;
  }
  m_userFunctions = function;

  function->parameterCount = 0;
  function->name[0] = 0;
  CharVector *source = &function->source;
  source->m_begin = 0;
  source->m_end = 0;
  source->m_capacity = 0;
  return function;
}

// FUNCTION: SUMO 0x00405712
// FUNCTION: EDITOR 0x00405734
SumoS32 ExpressionParser::FindOperator(char symbol) {
  OperatorEntryVector *operators = &m_operators;
  SumoS32 index = 0;
  if (operators->Size() > 0) {
    do {
      if (symbol == (*operators)[index].symbol) {
        return index;
      }
      ++index;
    } while (index < operators->Size());
  }
  return -1;
}

// FUNCTION: SUMO 0x004057ae
// FUNCTION: EDITOR 0x004057d0
void ExpressionParser::AddStandardConstants() {
  ParserValue value = MakeParserValue(g_parserPi);
  // STRING: SUMO 0x0042c2f4
  // STRING: EDITOR 0x0042c2f4
  AddConstant("pi", value);

  value = MakeParserValue((SumoF32)exp(1.0));
  // STRING: SUMO 0x0042c2f0
  // STRING: EDITOR 0x0042c2f0
  AddConstant("_e", value);
}

// FUNCTION: SUMO 0x00405818
// FUNCTION: EDITOR 0x0040583a
void ExpressionParser::AddBuiltinFunctions(SumoS32 count,
                                           BuiltinFunctionEntry *entries) {

  SumoS32 remaining = count;
  if (remaining > 0) {
    BuiltinFunctionEntry *entry = entries;
    BuiltinFunctionVector *builtins = &m_builtins;
    do {
      builtins->PushBack(*entry);
      ++entry;
      --remaining;
    } while (remaining != 0);
  }
}

// FUNCTION: SUMO 0x00405841
// FUNCTION: EDITOR 0x00405863
void ExpressionParser::AddOperators(SumoS32 count, OperatorEntry *entries) {
  if (count > 0) {
    char *precedence = (char *)entries;
    OperatorEntryVector *operators = &m_operators;
    ++precedence;
    SumoS32 remaining = count;
    do {
      SumoS32 value = *precedence;
      if (value > m_maxPrecedence) {
        m_maxPrecedence = value;
      }
      operators->PushBack(*(OperatorEntry *)(precedence - 1));
      precedence += sizeof(OperatorEntry);
      --remaining;
    } while (remaining != 0);
  }
}

static const char *volatile g_parserDumpStringAnchors[] = {
    // STRING: SUMO 0x0042c2f8
    // STRING: EDITOR 0x0042c2f8
    "RESULT: r%d\n",
    // STRING: SUMO 0x0042b258
    // STRING: EDITOR 0x0042b258
    "\n",
    // STRING: SUMO 0x0042c308
    // STRING: EDITOR 0x0042c308
    ",",
    // STRING: SUMO 0x0042c30c
    // STRING: EDITOR 0x0042c30c
    "r%d",
    // STRING: SUMO 0x0042c310
    // STRING: EDITOR 0x0042c310
    "%s r%d, ",
    // STRING: SUMO 0x0042c31c
    // STRING: EDITOR 0x0042c31c
    "Const: r%d = %g,%g,%g\n",
    // STRING: SUMO 0x0042b29c
    // STRING: EDITOR 0x0042b29c
    "w"};

// FUNCTION: SUMO 0x00405c85
// FUNCTION: EDITOR 0x00405ca7
void ExpressionParser::InitializeStandardLibrary() {
  ParserValue value;
  value.x = 0.0f;
  value.y = 0.0f;
  value.z = 0.0f;
  Initialize(value);
  AddOperators(5, g_parserOperators);
  AddBuiltinFunctions(12, g_parserBuiltinFunctions);
}

// FUNCTION: SUMO 0x00405cd0
// FUNCTION: EDITOR 0x00405cf2
GameExpressionParser::GameExpressionParser() { InitializeStandardLibrary(); }

// GLOBAL: SUMO 0x004e73d8
// GLOBAL: EDITOR 0x004e7bf8
GameExpressionParser g_gameParser;

// GLOBAL: SUMO 0x004ea46c
// GLOBAL: EDITOR 0x004eac8c
bool g_gameParserInitialized;

// FUNCTION: SUMO 0x00405d06
// FUNCTION: EDITOR 0x00405d28
void InitializeGameParser() {
  if (!g_gameParserInitialized) {
    g_gameParser.InitializeStandardLibrary();
    g_gameParser.AddBuiltinFunctions(6, g_gameBuiltinFunctions);
    g_gameParserInitialized = true;
  }
}

// FUNCTION: SUMO 0x0040650d
// FUNCTION: EDITOR 0x0040652f
char *ExpressionParser::CompileStatements(char *cursor) {
  char *result = cursor;
  while (result) {
    if (*result != ';') {
      break;
    }
    ++result;
  }

  while (result) {
    if (!*result || m_hasError) {
      break;
    }

    cursor = CompileStatement(result);
    if (m_hasError) {
      return cursor;
    }
    for (result = cursor; result; cursor = ++result) {
      if (*result != ';') {
        break;
      }
    }
    SkipWhitespace(&cursor);
    result = cursor;
  }
  return result;
}

extern const char g_parserIdentifierTooLong[];

char *ExpressionParser::ReadIdentifier(char *p_cursor, char *p_output) {
  if (p_output == 0) {
    char *cursor = p_cursor;
    if (IsIdentifierStart(*cursor)) {
      ++cursor;
      SumoS32 remaining = 14;
      while (IsIdentifierContinue(*cursor)) {
        if (remaining == 0) {
          if (!m_hasError) {
            m_hasError = 1;
            m_errorMessage = g_parserIdentifierTooLong;
          }
          break;
        }
        ++cursor;
        --remaining;
      }
    }
    return cursor;
  }

  char *cursor = p_cursor;
  char *output = p_output;
  char value = *cursor;
  if (IsIdentifierStart(value)) {
    *output = value;
    ++output;
    ++cursor;
    SumoS32 remaining = 14;
    for (;;) {
      value = *cursor;
      if (!IsIdentifierContinue(value))
        break;
      if (remaining == 0) {
        *output = 0;
        if (!m_hasError) {
          m_hasError = 1;
          m_errorMessage = g_parserIdentifierTooLong;
        }
        return cursor;
      }
      *output = value;
      ++output;
      ++cursor;
      --remaining;
    }
  }
  *output = 0;
  return cursor;
}

extern const SumoF64 g_gameSoundLogBase;

extern const SumoF64 compileValueFractionScale = 0.1;
extern const char compileValueExpectedError[] = "Value or ( expected";
extern const char compileValueUnknownNameError[] =
    "No such command or variable";
extern const char compileValueUndefinedFunctionError[] = "Undefined Function";
extern const char compileValueMinusError[] = "minus not supported now";
extern const char compileValueParameterError[] = "No parameter expected";

ParserExpression ExpressionParser::CompileValue(SumoS32 closesParenthesis) {
  ParserExpression result;
  result.valueIndex = m_defaultValueIndex;
  result.value = m_initialValue;
  SumoU8 negate = 0;

  while (*m_cursor == ' ')
    ++m_cursor;

  char token = *m_cursor;
  if (token == '(') {
    ++m_cursor;
    return CompileExpression(closesParenthesis + 1);
  }
  while (token == '-') {
    negate ^= 1;
    ++m_cursor;
    SkipWhitespace(&m_cursor);
    token = *m_cursor;
  }

  if (IsIdentifierStart(token)) {
    char identifier[16];
    char *after = ReadIdentifier(m_cursor, identifier);
    SkipWhitespace(&after);
    if (*after == '(') {
      m_cursor = after + 1;

      SumoS32 builtinCount = (SumoS32)(m_builtins.m_end - m_builtins.m_begin);
      SumoS32 builtinIndex = 0;
      for (; builtinIndex < builtinCount; ++builtinIndex) {
        if (strcmp(identifier, m_builtins[builtinIndex].name) == 0)
          break;
      }

      ParserExpression arguments[16];
      ParserExpression operationResult;
      if (builtinIndex < builtinCount) {
        BuiltinFunctionEntry &entry = m_builtins[builtinIndex];
        CompileExpressionArguments(arguments, entry.argumentCount);
        if (m_hasError) {
          result.valueIndex = m_defaultValueIndex;
          result.value = m_initialValue;
          return result;
        }
        operationResult = CompileOperation(entry.function, entry.argumentCount,
                                           arguments, entry.name);
      } else {
        UserFunction *user = FindUserFunction(identifier);
        if (user == 0) {
          if (!m_hasError) {
            m_errorMessage = compileValueUndefinedFunctionError;
            m_hasError = 1;
          }
          result.valueIndex = m_defaultValueIndex;
          result.value = m_initialValue;
          return result;
        }
        ParserVariable *savedScope = m_globalVariables;
        ParserVariable parameterVariables[16];
        if (user->parameterCount != 0) {
          CompileExpressionArguments(arguments, user->parameterCount);
          if (m_hasError) {
            m_globalVariables = savedScope;
            result.valueIndex = m_defaultValueIndex;
            result.value = m_initialValue;
            return result;
          }
          for (SumoS32 parameter = 0; parameter < user->parameterCount;
               ++parameter) {
            ParserVariable *local = &parameterVariables[parameter];
            strcpy(local->name, user->parameterNames[parameter]);
            local->isConstant = 0;
            local->previous = 0;
            local->valueIndex = arguments[parameter].valueIndex;
            local->value = arguments[parameter].value;
            local->next = local + 1;
          }
          parameterVariables[user->parameterCount - 1].next = 0;
          m_globalVariables = parameterVariables;
        } else {
          SkipWhitespace(&m_cursor);
          if (*m_cursor != ')') {
            if (!m_hasError) {
              m_hasError = 1;
              m_errorMessage = compileValueParameterError;
            }
            m_globalVariables = savedScope;
            result.valueIndex = m_defaultValueIndex;
            result.value = m_initialValue;
            return result;
          }
          ++m_cursor;
        }
        char *savedCursor = m_cursor;
        m_cursor = &user->source[0];
        CompileStatements(m_cursor);
        m_cursor = savedCursor;
        m_globalVariables = savedScope;
        operationResult = m_lastExpression;
      }

      result = operationResult;
      if (negate) {
        if (!m_hasError) {
          m_errorMessage = compileValueMinusError;
          m_hasError = 1;
        }
        result.valueIndex = m_defaultValueIndex;
        result.value = m_initialValue;
        return result;
      }
      return result;
    }

    ParserVariable *variable = FindVariableAtCursor(m_cursor);
    if (variable == 0) {
      if (!m_hasError) {
        m_errorMessage = compileValueUnknownNameError;
        m_hasError = 1;
      }
      result.valueIndex = m_defaultValueIndex;
      result.value = m_initialValue;
      return result;
    }
    m_cursor = ReadIdentifier(m_cursor, 0);
    result.valueIndex = variable->valueIndex;
    result.value = variable->value;
    return result;
  }

  if (!IsDigit(token)) {
    if (!m_hasError) {
      m_errorMessage = compileValueExpectedError;
      m_hasError = 1;
    }
    result.valueIndex = m_defaultValueIndex;
    result.value = m_initialValue;
    return result;
  }

  SumoF64 fractionScale = 1.0;
  SumoF64 number = 0.0;
  for (;;) {
    SumoS32 digit = (SumoS32)*m_cursor - '0';
    ++m_cursor;
    number = number * g_gameSoundLogBase + digit;
    if (!IsDigit(*m_cursor))
      break;
  }
  if (*m_cursor == '.') {
    ++m_cursor;
    while (IsDigit(*m_cursor)) {
      SumoS32 digit = (SumoS32)*m_cursor - '0';
      fractionScale = fractionScale * compileValueFractionScale;
      ++m_cursor;
      number = digit * fractionScale + number;
    }
  }
  if (negate)
    number = -number;
  result.valueIndex = -1;
  result.value = ConvertScalar(number);
  return result;
}

extern const char compileExpressionInvalidError[] = "Unknown Error";
extern const char compileExpressionCloseError[] = "Expected )";
extern const char compileExpressionOperatorError[] = "Operator expected";
extern const char compileExpressionUnexpectedCloseError[] = "Unexpected )";

ParserExpression
ExpressionParser::CompileExpression(SumoS32 closesParenthesis) {
  ParserExpression values[64];
  char operators[64];
  SumoS32 count = 0;
  ParserExpression *writeCursor = values;
  ParserExpression errorResult;
  errorResult.valueIndex = m_defaultValueIndex;
  errorResult.value = m_initialValue;

  for (;;) {
    ParserExpression value = CompileValue(closesParenthesis);
    *writeCursor = value;
    if (m_hasError)
      return errorResult;
    SkipWhitespace(&m_cursor);
    char token = *m_cursor;
    if (token != 0 && token != ';' && token != ')' && token != ',') {
      ++m_cursor;
      SumoS32 operatorIndex = FindOperator(token);
      operators[count] = (char)operatorIndex;
      if ((char)operatorIndex == (char)-1) {
        if (!m_hasError) {
          m_hasError = 1;
          m_errorMessage = compileExpressionOperatorError;
        }
        return errorResult;
      }
    }
    ++count;
    ++writeCursor;
    if (m_hasError)
      break;
    token = *m_cursor;
    if (token == 0 || token == ';' || token == ')' || token == ',')
      break;
  }

  char token = *m_cursor;
  if (token == ')') {
    if (closesParenthesis == 0) {
      if (m_hasError)
        return errorResult;
      m_hasError = 1;
      m_errorMessage = compileExpressionUnexpectedCloseError;
      return errorResult;
    }
    ++m_cursor;
  } else if (closesParenthesis != 0) {
    if (m_hasError)
      return errorResult;
    m_hasError = 1;
    m_errorMessage = compileExpressionCloseError;
    return errorResult;
  }

  for (SumoS32 precedence = m_maxPrecedence; precedence >= 0; --precedence) {
    SumoS32 writeIndex = 1;
    SumoS32 readIndex = 1;
    if (count > 1) {
      ParserExpression *rightCursor = &values[1];
      ParserExpression *leftCursor = &values[0];
      do {
        SumoS32 operatorIndex = (SumoS8)operators[readIndex - 1];
        OperatorEntry &entry = m_operators[operatorIndex];
        if ((SumoS32)entry.precedence == precedence) {
          ParserExpression arguments[2];
          arguments[0] = *leftCursor;
          arguments[1] = *rightCursor;
          char name[4];
          name[0] = 'o';
          name[1] = 'p';
          name[2] = entry.symbol;
          name[3] = 0;
          ParserExpression reduced =
              CompileOperation(entry.function, 2, arguments, name);
          char carried = operators[readIndex];
          ++readIndex;
          ++rightCursor;
          operators[writeIndex - 1] = carried;
          *leftCursor = reduced;
        } else {
          char carried = operators[readIndex];
          ParserExpression *destination = leftCursor + 1;
          ++readIndex;
          ParserExpression *source = rightCursor;
          ++rightCursor;
          operators[writeIndex] = carried;
          ++writeIndex;
          ++leftCursor;
          *destination = *source;
        }
      } while (readIndex < count);
    }
    count = writeIndex;
  }

  if (count != 1) {
    if (!m_hasError) {
      m_hasError = 1;
      m_errorMessage = compileExpressionInvalidError;
    }
  }
  if (m_hasError)
    return errorResult;
  return values[0];
}

// FUNCTION: SUMO 0x00405b91
// FUNCTION: EDITOR 0x00405bb3
ParserExpression ExpressionParser::CompileOperation(ParserCallback function,
                                                    SumoS32 argumentCount,
                                                    ParserExpression *arguments,
                                                    char *name) {
  ParserValue constantValues[5];
  ParserBuiltinCall call;
  SumoS32 constantCount = 0;

  if (argumentCount > 0) {
    ParserExpression *argument = arguments;
    ParserValue *constantValue = constantValues;
    do {
      if (argument->valueIndex != -1) {
        break;
      }
      *constantValue = argument->value;
      call.arguments[constantCount] = constantValue;
      ++constantCount;
      ++argument;
      ++constantValue;
    } while (constantCount < argumentCount);
  }

  ParserExpression result;
  call.output = &result.value;
  if (constantCount == argumentCount) {
    result.valueIndex = -1;
    function(&call);
  } else {
    ParsedOperation operation;
    operation.function = (void *)function;

    SumoS32 argumentIndex = 0;
    if (argumentCount > 0) {
      ParserExpression *argument = arguments;
      do {
        SumoS32 valueIndex = argument->valueIndex;
        if (valueIndex == -1) {
          valueIndex = m_valueCount;
          m_values[m_valueCount] = argument->value;
          ++m_valueCount;
        }
        operation.arguments[argumentIndex] = valueIndex;
        ++argumentIndex;
        ++argument;
      } while (argumentIndex < argumentCount);
    }

    strcpy(operation.name, name);
    operation.argumentCount = argumentCount;
    result.valueIndex = m_valueCount;
    operation.outputRegister = result.valueIndex;
    m_values[m_valueCount] = m_defaultValue;
    ++m_valueCount;
    result.value = m_defaultValue;
    m_parsed.PushBack(operation);
  }

  return result;
}

// FUNCTION: SUMO 0x004061f4
// FUNCTION: EDITOR 0x00406216
char *ExpressionParser::CompileExpressionStatement(char *cursor) {
  m_cursor = cursor;
  ParserExpression expression;
  expression = CompileExpression(0);
  m_lastExpression = expression;

  if (expression.valueIndex == -1) {
    expression.valueIndex = m_valueCount;
    m_values[m_valueCount] = expression.value;
    ++m_valueCount;
  }

  m_resultIndex = expression.valueIndex;
  return m_cursor;
}

// FUNCTION: SUMO 0x00406255
// FUNCTION: EDITOR 0x00406277
SumoS32
ExpressionParser::CompileExpressionArguments(ParserExpression *arguments,
                                             SumoS32 argumentCount) {
  ParserExpression *argumentCursor = arguments;
  SumoS32 parsedCount = 0;

  do {
    --argumentCount;
    if (argumentCount > 0) {
      *argumentCursor = CompileExpression(0);
      ++parsedCount;
      ++argumentCursor;

      if (*m_cursor == ',') {
        ++m_cursor;
      } else {
        if (!m_hasError) {
          m_hasError = true;
          // STRING: SUMO 0x0042c40c
          // STRING: EDITOR 0x0042c40c
          m_errorMessage = "More parameters expected";
        }
        return 0;
      }
    } else {
      *argumentCursor = CompileExpression(1);
      ++parsedCount;
      ++argumentCursor;
    }

    if (m_hasError) {
      return 0;
    }
  } while (argumentCount != 0);

  return parsedCount;
}

// FUNCTION: SUMO 0x004051aa
// FUNCTION: EDITOR 0x004051cc
char *ExpressionParser::CompileBlockStatements(char *cursor) {
  char *result = cursor;
  while (result) {
    if (*result != ';') {
      break;
    }
    ++result;
  }

  while (result) {
    if (*result == '}' || !*result || m_hasError) {
      break;
    }

    cursor = CompileStatement(result);
    if (m_hasError) {
      return 0;
    }
    for (result = cursor; result; cursor = ++result) {
      if (*result != ';') {
        break;
      }
    }
    SkipWhitespace(&cursor);
    result = cursor;
  }
  return result;
}

extern const char compileStatementConstantError[] =
    "Constant cannot be modified";
extern const char compileStatementRepeatCloseError[] =
    "{ for repeat must be closed by }";
extern const char compileStatementRepeatBraceError[] = "{ expected for repeat";
extern const char compileStatementRepeatNegativeError[] =
    "Parameter of repeat cannot be negative";
extern const char compileStatementRepeatConstantError[] =
    "Parameter of repeat must be definit";
extern const char compileStatementRepeatParenthesisError[] =
    "( expected after repeat";
extern const char compileStatementRepeatKeyword[] = "repeat";

char *ExpressionParser::CompileStatement(char *cursor) {
  if (*cursor == 0)
    return 0;
  SkipWhitespace(&cursor);
  if (!IsIdentifierStart(*cursor))
    return CompileExpressionStatement(cursor);

  char identifier[16];
  char *after = ReadIdentifier(cursor, identifier);
  SkipWhitespace(&after);

  if (strcmp(identifier, compileStatementRepeatKeyword) == 0) {
    if (*after != '(') {
      if (!m_hasError) {
        m_errorMessage = compileStatementRepeatParenthesisError;
        m_hasError = 1;
      }
      return 0;
    }
    ++after;
    SkipWhitespace(&after);
    m_cursor = after;
    ParserExpression argument;
    CompileExpressionArguments(&argument, 1);
    if (argument.valueIndex != -1) {
      if (!m_hasError) {
        m_errorMessage = compileStatementRepeatConstantError;
        m_hasError = 1;
      }
      return 0;
    }
    SumoS32 repeatCount = (SumoS32)argument.value.x;
    if (repeatCount < 0) {
      if (!m_hasError) {
        m_errorMessage = compileStatementRepeatNegativeError;
        m_hasError = 1;
      }
      return 0;
    }
    SkipWhitespace(&m_cursor);
    char *body = m_cursor;
    if (*body != '{') {
      if (!m_hasError) {
        m_errorMessage = compileStatementRepeatBraceError;
        m_hasError = 1;
      }
      return 0;
    }
    ++body;
    m_cursor = body;
    if (repeatCount > 0) {
      SumoS32 remaining = repeatCount;
      do {
        m_cursor = body;
        m_cursor = CompileBlockStatements(body);
        --remaining;
      } while (remaining != 0);
    }
    if (*m_cursor != '}') {
      if (!m_hasError) {
        m_errorMessage = compileStatementRepeatCloseError;
        m_hasError = 1;
      }
      return 0;
    }
    ++m_cursor;
    return m_cursor;
  }

  char *operatorCursor = after;
  char token = *operatorCursor;
  if (token == '=') {
    ParserVariable *variable = FindVariable(identifier);
    if (variable == 0) {
      variable = AllocateVariable();
      strcpy(variable->name, identifier);
    }
    if (variable->isConstant & 1) {
      if (!m_hasError) {
        m_errorMessage = compileStatementConstantError;
        m_hasError = 1;
      }
      return 0;
    }
    ++operatorCursor;
    m_cursor = operatorCursor;
    ParserExpression result = CompileExpression(0);
    variable->valueIndex = result.valueIndex;
    variable->value = result.value;
    return m_cursor;
  }

  if (token == '(') {
    char *parameterCursor = operatorCursor + 1;
    char *scan = parameterCursor;
    char value = *scan;
    SumoS32 foundClose = 0;
    while (value != 0) {
      if (value == '(')
        break;
      if (value == ')') {
        foundClose = 1;
        break;
      }
      ++scan;
      value = *scan;
    }
    if (foundClose || *scan == ')') {
      char *afterClose = scan + 1;
      SkipWhitespace(&afterClose);
      if (*afterClose == '=')
        return CompileFunctionDefinition(identifier, parameterCursor,
                                         afterClose + 1);
    }
  }

  return CompileExpressionStatement(cursor);
}

// FUNCTION: SUMO 0x004059d7
// FUNCTION: EDITOR 0x004059f9
char *ExpressionParser::CompileFunctionDefinition(char *name,
                                                  char *parameterCursor,
                                                  char *bodyCursor) {
  char *parameterHome = parameterCursor;
  BuiltinFunctionVector *builtinList = &m_builtins;
  for (SumoS32 builtinIndex = 0;
       builtinIndex < builtinList->m_end - builtinList->m_begin;
       ++builtinIndex) {
    if (strcmp(name, m_builtins[builtinIndex].name) == 0) {
      if (!m_hasError) {
        m_errorMessage = "Default function cannot be overriden";
        m_hasError = true;
      }
      return NULL;
    }
  }

  UserFunction *function = FindUserFunction(name);
  if (function == NULL) {
    function = AllocateUserFunction();
  }
  strcpy(function->name, name);

  SkipWhitespace(&parameterHome);
  char *parameter = parameterHome;
  function->parameterCount = 0;
  while (*parameter != ')' && *parameter != 0) {
    parameterHome = ReadIdentifier(
        parameter, function->parameterNames[function->parameterCount++]);
    SkipWhitespace(&parameterHome);
    parameter = parameterHome;

    char separator = *parameter;
    if ((separator != ')' && separator != ',') ||
        function->parameterNames[function->parameterCount - 1][0] == 0) {
      CharVector &invalidSource = function->source;
      function->parameterCount = 0;
      invalidSource.Clear();
      if (!m_hasError) {
        m_errorMessage = "Parameter variables exlected";
        m_hasError = true;
      }
      return NULL;
    }
    if (separator == ',') {
      ++parameter;
    }
  }

  SkipWhitespace(&bodyCursor);
  if (*bodyCursor != '{') {
    if (!m_hasError) {
      m_errorMessage = "{ expected to define function";
      m_hasError = true;
    }
    return NULL;
  }

  ++bodyCursor;
  SkipWhitespace(&bodyCursor);
  CharVector *source = &function->source;
  source->Clear();
  char *scanStart = bodyCursor;
  bodyCursor = NULL;
  char *scan = scanStart;
  char symbol = *scan;
  while (symbol != 0 && (symbol != '}' || bodyCursor != NULL)) {
    if (symbol == '{') {
      ++bodyCursor;
    }
    if (symbol == '}') {
      --bodyCursor;
    }
    source->PushBack(*scan);
    ++scan;
    symbol = *scan;
  }

  *((char *)&bodyCursor + 3) = 0;
  source->PushBack(*((char *)&bodyCursor + 3));
  if (*scan == 0) {
    if (!m_hasError) {
      m_errorMessage = "function definition not closed by }";
      m_hasError = true;
    }
    return NULL;
  }
  return scan + 1;
}

void ExpressionParser::PrepareEvaluation() {
  m_operations.Clear();
  m_valueMappings.m_end = m_valueMappings.m_begin;
  if (m_valueCount == 0) {
    m_resultIndex = 0;
    return;
  }

  if (m_valueCount > 0) {
    ParserRegisterInfo info;
    info.producerOperation = -1;
    info.lastConsumer = -1;
    for (SumoS32 index = 0; index < m_valueCount; ++index) {
      info.valueIndex = index;
      ((Vector3Vector *)&m_valueMappings)->PushBack(*(const Vector3 *)&info);
    }
  }

  SumoS32 operationIndex = 0;
  for (ParsedOperation *parsed = m_parsed.m_begin; parsed < m_parsed.m_end;
       ++parsed, ++operationIndex) {
    if (m_valueMappings[parsed->outputRegister].producerOperation == -1)
      m_valueMappings[parsed->outputRegister].producerOperation =
          operationIndex;
    for (SumoS32 argument = 0; argument < parsed->argumentCount; ++argument)
      m_valueMappings[parsed->arguments[argument]].lastConsumer =
          operationIndex;
  }

  SumoS32 mappingCount =
      (SumoS32)(m_valueMappings.m_end - m_valueMappings.m_begin);
  if (m_resultIndex < mappingCount)
    m_valueMappings[m_resultIndex].lastConsumer = operationIndex;
  else
    m_resultIndex = 0;

  operationIndex = 0;
  for (ParsedOperation *parsed = m_parsed.m_begin; parsed < m_parsed.m_end;
       ++parsed, ++operationIndex) {
    CompiledOperation compiled;
    compiled.function = (ParserCallback)parsed->function;
    for (SumoS32 argument = 0; argument < parsed->argumentCount; ++argument) {
      SumoS32 slot = m_valueMappings[parsed->arguments[argument]].valueIndex;
      parsed->arguments[argument] = slot;
      compiled.call.arguments[argument] = &m_values[slot];
    }

    SumoS32 outputMapping = m_valueMappings[parsed->outputRegister].valueIndex;
    for (SumoS32 slot = 0; slot < m_valueCount; ++slot) {
      if (m_valueMappings[slot].lastConsumer > operationIndex)
        continue;
      if (m_valueMappings[slot].producerOperation < 0)
        continue;
      if (slot == outputMapping)
        continue;
      if (m_valueMappings[slot].lastConsumer == -1)
        continue;
      m_valueMappings[slot] = m_valueMappings[outputMapping];
      m_valueMappings[outputMapping].valueIndex = slot;
      break;
    }

    SumoS32 outputSlot = m_valueMappings[parsed->outputRegister].valueIndex;
    parsed->outputRegister = outputSlot;
    compiled.call.output = &m_values[outputSlot];
    m_operations.PushBack(compiled);
  }

  m_resultIndex = m_valueMappings[m_resultIndex].valueIndex;
  static char s_dumpFilename[] = "asm.txt";
  DumpAssembly(s_dumpFilename);
}

ParserValue ExpressionParser::Evaluate() {
  if (m_valueCount == 0)
    return m_defaultValue;
  for (CompiledOperation *operation = m_operations.m_begin;
       operation < m_operations.m_end; ++operation)
    operation->function(&operation->call);
  return m_values[m_resultIndex];
}

// FUNCTION: SUMO 0x00405751
// FUNCTION: EDITOR 0x00405773
ParserVariable *ExpressionParser::FindVariableAtCursor(char *cursor) {
  char name[16];
  ReadIdentifier(cursor, name);
  return FindVariable(name);
}

// FUNCTION: SUMO 0x004058ce
// FUNCTION: EDITOR 0x004058f0
void ExpressionParser::DumpAssembly(char *p_filename) {
  FILE *file = fopen(p_filename, "w");

  for (SumoS32 valueIndex = 0; valueIndex < m_valueCount; ++valueIndex) {
    if (m_valueMappings[valueIndex].producerOperation == -1) {
      fprintf(file, "Const: r%d = %g,%g,%g\n", valueIndex,
              m_values[valueIndex].x, m_values[valueIndex].y,
              m_values[valueIndex].z);
    }
  }

  for (ParsedOperation *operation = m_parsed.m_begin;
       operation < m_parsed.m_end; ++operation) {
    fprintf(file, "%s r%d, ", operation->name, operation->outputRegister);
    for (SumoS32 argumentIndex = 0; argumentIndex < operation->argumentCount;
         ++argumentIndex) {
      fprintf(file, "r%d", operation->arguments[argumentIndex]);
      if (argumentIndex != operation->argumentCount - 1) {
        fprintf(file, ",");
      }
    }
    fprintf(file, "\n");
  }

  fprintf(file, "RESULT: r%d\n", m_resultIndex);
  fclose(file);
}

// FUNCTION: SUMO 0x00404d6d
// FUNCTION: EDITOR 0x00404d8f
void ParserBuiltinTurnTo(ParserBuiltinCall *call) {
  ParserValue *output = call->output;
  output->z = 0.0f;
  output->y = 0.0f;
  output->x = 0.0f;

  if (g_currentBox == NULL) {
    return;
  }

  g_currentBox->orientation.RotateRows02(
      ParserAtan2Value(call->arguments[0]->x, call->arguments[0]->z));

  Vector3 horizontal =
      MakeVector3(call->arguments[0]->x, call->arguments[0]->z, 0.0f);
  g_currentBox->orientation.RotateRows12(ParserAtan2Value(
      call->arguments[0]->y,
      (SumoF32)sqrt(horizontal.x * horizontal.x + horizontal.y * horizontal.y +
                    horizontal.z * horizontal.z)));
}
