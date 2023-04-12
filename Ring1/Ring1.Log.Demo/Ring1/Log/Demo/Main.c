// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Log/Demo/Main.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include <stdlib.h>
#include "Ring1/Log.h"

int
main
  (
  )
{
  Ring1_Log_ModuleHandle handle = Ring1_Log_ModuleHandle_acquire();
  if (!handle) {
    return EXIT_FAILURE;
  }
  Ring1_Log_information("application startup");
  Ring1_Log_warning("this is a warning");
  Ring1_Log_warning("this is a warning with a cr nl\r\n");
  Ring1_Log_warning("this is a warning with a nl\n");
  Ring1_Log_error("this is an error");
  Ring1_Log_information("application shutdown");
  Ring1_Log_ModuleHandle_relinquish(handle);
  return EXIT_SUCCESS;
}
