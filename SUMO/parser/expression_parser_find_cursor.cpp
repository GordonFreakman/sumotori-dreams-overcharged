#include "expression_parser.h"

// FUNCTION: SUMO 0x00405751
// FUNCTION: EDITOR 0x00405773
ParserVariable* ExpressionParser::FindVariableAtCursor(char* cursor)
{
  char name[16];
  ReadIdentifier(cursor, name);
  return FindVariable(name);
}
