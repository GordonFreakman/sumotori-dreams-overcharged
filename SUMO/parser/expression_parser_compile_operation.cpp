#include <string.h>

#include "expression_parser.h"

// FUNCTION: SUMO 0x00405b91
// FUNCTION: EDITOR 0x00405bb3
ParserExpression ExpressionParser::CompileOperation(
    ParserCallback function, SumoS32 argumentCount,
    ParserExpression* arguments, char* name)
{
  ParserValue constantValues[5];
  ParserBuiltinCall call;
  SumoS32 constantCount = 0;

  if (argumentCount > 0) {
    ParserExpression* argument = arguments;
    ParserValue* constantValue = constantValues;
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
  }
  else {
    ParsedOperation operation;
    operation.function = (void*) function;

    SumoS32 argumentIndex = 0;
    if (argumentCount > 0) {
      ParserExpression* argument = arguments;
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
