/// @file Ring1/Crt/memcpy.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/memcpy.h"

#include <string.h>

void*
crt_memcpy
  (
    void* p,
    void const* q,
    size_t n
  )
{ return memcpy(p, q, n); }
