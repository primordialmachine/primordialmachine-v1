/// @file Runtime/LogModule.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/LogModule.h"

#if defined(MACHINE_WITH_LOG) && 1 == MACHINE_WITH_LOG

#include "Runtime/Status.h"
#include <stdio.h>
#include <stdarg.h>

Ring1_Result Machine_initializeLogModule() {
  return Ring1_Result_Success;
}

void Machine_uninitializeLogModule() {
}


void Machine_log(int flags, const char* file, int line, const char* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  fprintf(stdout, "%s:%d: ", file, line);
  vfprintf(stdout, format, arguments);
  va_end(arguments);
}

#endif
