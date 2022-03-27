/// @file Eal/Zts.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_EAL_PRIVATE (1)
#include "Eal/Zts.h"



#include "Ring1/Intrinsic/Multiply/multiply.h"
#include <string.h>
#include <intsafe.h>
#include <malloc.h>



char* c_strzt_clone(char const* s) {
  return _strdup(s);
}

size_t c_strzt_length(char const* s) {
  return strlen(s);
}
