/// @file Ring1/Crt/free.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/free.h"

#include <malloc.h>

void
crt_free
  (
    void* p
  )
{
  free(p);
}
