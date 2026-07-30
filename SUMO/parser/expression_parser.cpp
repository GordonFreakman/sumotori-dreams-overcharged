#include "expression_parser.h"

#include "decomp.h"
#include "game_runtime.h"
#include "parser_helpers.h"

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
    if (g_nextGameMan < (GameMan *)&g_gameMenEnd) {
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
void ExpressionParser::AddBuiltinFunctions(SumoS32 count, BuiltinFunctionEntry *entries) {

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
