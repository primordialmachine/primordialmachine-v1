/// @file Ring1/Crt/malloc.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/malloc.h"

#include <malloc.h>

#if defined(_MSC_VER)
_Check_return_
#endif
void *
crt_malloc
  (
    size_t n
  )
{
  return malloc(n);
}
