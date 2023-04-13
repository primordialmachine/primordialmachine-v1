// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Log.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Log.h"
#undef RING2_PRIVATE


#include "Ring1/Status.h"
#include <stdio.h>
#include <stdarg.h>


Ring1_CheckReturn() Ring1_Result
Ring2_LogModule_startup
  (
  )
{ return Ring1_Result_Success; }

void
Ring2_LogModule_shutdown
  (
  )
{ }

Ring1_Module_Define(Ring2, LogModule, Ring2_LogModule_startup, Ring2_LogModule_shutdown)

void
Ring2_log
  (
    int flags,
    const char* file,
    int line,
    const char* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  fprintf(stdout, "%s:%d: ", file, line);
  vfprintf(stdout, format, arguments);
  va_end(arguments);
}
