// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Log.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Log.h"

#include "Ring1/Status.h"
#include <stdio.h>
#include <stdarg.h>

static int g_referenceCount = 0;

Ring1_CheckReturn() Ring1_Result
Ring2_LogModule_startup
  (
  )
{
  if (0 == g_referenceCount) {
    /*Intentionally empty.*/
  }
  g_referenceCount++;
  return Ring1_Result_Success;
}

void
Ring2_LogModule_shutdown
  (
  )
{ 
  if (1 == g_referenceCount) {
    /*Intentionally empty.*/
  }
  g_referenceCount--;
}

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
