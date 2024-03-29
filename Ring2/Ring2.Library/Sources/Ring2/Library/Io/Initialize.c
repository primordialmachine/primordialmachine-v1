// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Io/Initialize.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Io/Initialize.h"


#include <stdio.h>
#include "Ring1/Status.h"
#include "Ring1/FileSystem/_Include.h"
#include "Ring2/_Include.h"


static Ring1_FileSystem_ModuleHandle g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;

static void
onUninitializeStaticVariables
  (
  )
{
  Ring1_FileSystem_ModuleHandle_relinquish(g_moduleHandle);
  g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;
}

void
Machine_Io_initialize
  (
  )
{
  if (Ring1_FileSystem_ModuleHandle_Invalid == g_moduleHandle) {
    g_moduleHandle = Ring1_FileSystem_ModuleHandle_acquire();
    if (!g_moduleHandle) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    if (Ring2_registerStaticVariables(&onUninitializeStaticVariables)) {
      Ring1_FileSystem_ModuleHandle_relinquish(g_moduleHandle);
      g_moduleHandle = Ring1_FileSystem_ModuleHandle_Invalid;
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
  }
}

Ring2_String*
Machine_Io_makePathname
  (
    Ring2_Context* context,
    const Ring2_String* source
  )
{
  Ring2_String* temporary;

  temporary = Ring2_String_create("", 1);

  if (-1 != Ring2_String_firstOccurrenceOf(context, source, temporary)) {
    fprintf(stderr, "invalid pathname: string contains the zero-terminator character\n");
    Ring1_Status_set(Ring1_Status_InvalidLexics);
    Ring2_jump();
  }

  temporary =
    Ring2_String_concatenate
      (
        context,
        source,
        temporary
      );

  return temporary;
}
