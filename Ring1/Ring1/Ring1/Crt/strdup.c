/// @file Ring1/Crt/strdup.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/strdup.h"

#include <string.h>

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strdup
  (
    char const* a
  )
{ return _strdup(a); }
