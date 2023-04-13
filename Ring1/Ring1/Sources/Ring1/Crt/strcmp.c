/// @file Ring1/Crt/strcmp.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/strcmp.h"

#include <string.h>

#if defined(_MSC_VER)
_Check_return_
#endif
int
crt_strcmp
  (
    char const* p,
    char const* q
  )
{ return strcmp(p, q); }
