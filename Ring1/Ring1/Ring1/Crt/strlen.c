/// @file Ring1/Crt/strlen.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/strlen.h"

#include <string.h>

#if defined(_MSC_VER)
_Check_return_
#endif
size_t
crt_strlen
  (
    char const* a
  )
{
  return strlen(a);
}
