/// @file Ring1/Crt/memset.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/memset.h"

#include <string.h>

void*
crt_memset
  (
    void* p,
    int v,
    size_t n
  )
{ return memset(p, v, n); }
