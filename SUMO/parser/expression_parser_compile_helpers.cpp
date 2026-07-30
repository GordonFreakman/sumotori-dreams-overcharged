#include "expression_parser.h"

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
SumoS32 ExpressionParser::CompileExpressionArguments(
    ParserExpression* arguments, SumoS32 argumentCount)
{
  ParserExpression* argumentCursor = arguments;
  SumoS32 parsedCount = 0;

  do {
    --argumentCount;
    if (argumentCount > 0) {
      *argumentCursor = CompileExpression(0);
      ++parsedCount;
      ++argumentCursor;

      if (*m_cursor == ',') {
        ++m_cursor;
      }
      else {
        if (!m_hasError) {
          m_hasError = true;
          // STRING: SUMO 0x0042c40c
          // STRING: EDITOR 0x0042c40c
          m_errorMessage = "More parameters expected";
        }
        return 0;
      }
    }
    else {
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
