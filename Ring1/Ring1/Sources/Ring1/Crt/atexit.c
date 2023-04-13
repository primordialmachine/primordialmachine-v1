/// @file Ring1/Crt/atexit.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/atexit.h"

#include <stdlib.h>

int
crt_atexit  
  (
    void(__cdecl* function)(void)
  )
{
  return atexit(function);
}
