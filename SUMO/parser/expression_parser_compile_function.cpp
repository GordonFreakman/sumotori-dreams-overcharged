#include <string.h>

#include "expression_parser.h"
#include "parser_helpers.h"

// FUNCTION: SUMO 0x004059d7
// FUNCTION: EDITOR 0x004059f9
char *ExpressionParser::CompileFunctionDefinition(char *name, char *parameterCursor, char *bodyCursor) {
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
