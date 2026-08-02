#include "expression_parser.h"

#include <stdio.h>

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
