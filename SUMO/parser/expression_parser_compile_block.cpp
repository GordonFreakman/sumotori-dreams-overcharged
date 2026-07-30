#include "expression_parser.h"
#include "parser_helpers.h"

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
