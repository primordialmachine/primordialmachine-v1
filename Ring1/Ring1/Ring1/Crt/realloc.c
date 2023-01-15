/// @file Ring1/Crt/realloc.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/realloc.h"

#include <malloc.h>

#if defined(_MSC_VER)
_Check_return_
#endif
void *
crt_realloc
  (
    void* p,
    size_t n
  )
{
  return realloc(p, n);
}
