#ifndef SUMO_EXPRESSION_PARSER_H
#define SUMO_EXPRESSION_PARSER_H

#include "containers.h"
#include "vectors.h"

struct ParserExpression {
  SumoS32 valueIndex;
  ParserValue value;
};

struct ParserVariable {
  char name[16];
  SumoS32 valueIndex;
  ParserValue value;
  SumoS32 isConstant;
  ParserVariable *next;
  ParserVariable *previous;
};

struct UserFunction {
  char name[16];
  char parameterNames[16][16];
  SumoS32 parameterCount;
  CharVector source;
  UserFunction *next;
  UserFunction *previous;
};

ParserValue MakeParserValue(SumoF32 value);
SumoF64 ParserAtan2(SumoF32 y, SumoF32 x);
SumoF32 ParserAtan2Value(SumoF32 y, SumoF32 x);
SumoF64 ParserModulo(SumoF32 value, SumoF32 divisor);
SumoF32 ParserModuloValue(SumoF32 value, SumoF32 divisor);
SumoF32 ParserPower(SumoF32 base, SumoF32 exponent);

void ParserBuiltinAtanXY(ParserBuiltinCall *call);
void ParserBuiltinAbs(ParserBuiltinCall *call);
void ParserBuiltinVector(ParserBuiltinCall *call);
void ParserBuiltinSelectX(ParserBuiltinCall *call);
void ParserBuiltinModulo(ParserBuiltinCall *call);
void ParserBuiltinCos(ParserBuiltinCall *call);
void ParserBuiltinDot(ParserBuiltinCall *call);
void ParserBuiltinNormalize(ParserBuiltinCall *call);
void ParserOperatorAdd(ParserBuiltinCall *call);
void ParserOperatorSubtract(ParserBuiltinCall *call);
void ParserOperatorMultiply(ParserBuiltinCall *call);
void ParserOperatorDivide(ParserBuiltinCall *call);
void ParserOperatorPower(ParserBuiltinCall *call);
void ParserBuiltinRotate(ParserBuiltinCall *call);
void ParserBuiltinAddBox(ParserBuiltinCall *call);
void ParserBuiltinBreakability(ParserBuiltinCall *call);
void ParserBuiltinRandom(ParserBuiltinCall *call);
void ParserBuiltinTurnTo(ParserBuiltinCall *call);
void ParserBuiltinMan(ParserBuiltinCall *call);
void ParserBuiltinCutPlane(ParserBuiltinCall *call);

// VTABLE: SUMO 0x0042c3c0
// VTABLE: EDITOR 0x0042c3c0

class ExpressionParser {
public:
  ExpressionParser();
  void DestroyStorage();

  virtual ParserValue ConvertScalar(SumoF64 value);

  ParserVariable *AllocateVariable();
  void AddConstant(char *name, ParserValue value);
  void Reset();
  void Initialize(ParserValue value);
  ParserVariable *FindVariable(char *name);
  ParserVariable *FindVariableAtCursor(char *cursor);
  SumoS32 IsIdentifierStart(char value);
  SumoS32 IsIdentifierContinue(char value);
  SumoS32 IsDigit(char value);
  UserFunction *FindUserFunction(char *name);
  char *ReadIdentifier(char *p_cursor, char *p_output);
  ParserExpression CompileExpression(SumoS32 closesParenthesis);
  char *CompileExpressionStatement(char *cursor);
  SumoS32 CompileExpressionArguments(ParserExpression *arguments,
                                     SumoS32 argumentCount);
  ParserExpression CompileOperation(ParserCallback function,
                                    SumoS32 argumentCount,
                                    ParserExpression *arguments, char *name);
  ParserExpression CompileValue(SumoS32 parenthesisDepth);
  char *CompileFunctionDefinition(char *name, char *parameterCursor,
                                  char *bodyCursor);
  UserFunction *AllocateUserFunction();
  SumoS32 FindOperator(char symbol);
  void AddBuiltinFunctions(SumoS32 count, BuiltinFunctionEntry *entries);
  void AddOperators(SumoS32 count, OperatorEntry *entries);
  void AddStandardConstants();
  void InitializeStandardLibrary();
  ParserValue Evaluate();
  void PrepareEvaluation();
  void DumpAssembly(char *p_filename);
  char *CompileStatement(char *cursor);
  char *CompileBlockStatements(char *cursor);
  char *CompileStatements(char *cursor);

private:
  friend void LoadGameLevel(char *source);

  char *m_cursor;
  const char *m_errorMessage;
  bool m_hasError;
  SumoU8 m_errorPadding[3];
  ParserValue m_defaultValue;
  SumoS32 m_defaultValueIndex;
  ParserValue m_initialValue;
  SumoS32 m_valueCount;
  ParserValue m_values[1024];
  CompiledOperationVector m_operations;
  ParsedOperationVector m_parsed;
  SumoS32 m_resultIndex;
  ParserExpression m_lastExpression;
  ParserVariable *m_localVariables;
  ParserVariable *m_globalVariables;
  ParserVariable *m_currentVariable;
  BuiltinFunctionVector m_builtins;
  UserFunction *m_userFunctions;
  SumoS32 m_maxPrecedence;
  OperatorEntryVector m_operators;
  ParserRegisterInfoVector m_valueMappings;
};

// SYNTHETIC: SUMO 0x00405424 SYMBOL
class GameExpressionParser : public ExpressionParser {
public:
  GameExpressionParser();
};

extern BuiltinFunctionEntry g_gameBuiltinFunctions[6];
extern GameExpressionParser g_gameParser;
extern bool g_gameParserInitialized;

void InitializeGameParser();

#endif
