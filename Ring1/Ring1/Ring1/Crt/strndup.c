/// @file Ring1/Crt/strndup.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Crt/strndup.h"

// Provide strndup for Visual C++.
#if defined(_MSC_VER)

#include <malloc.h>
#include <string.h> // memcpy, strnlen_s

static char*
strndup
  (
    char const* a,
    size_t l
  );

static char*
strndup
  (
    const char* a,
    size_t l
  )
{
  size_t m = strnlen_s(a, l);
  char* b = (char*)malloc(m + 1);
  if (NULL == b) {
    return NULL;
  }
  b[m] = '\0';
  return (char*)memcpy(b, a, m);
}

#else

#include <string.h> // strndup

#endif

#if defined(_MSC_VER)
_Check_return_
#endif
char*
crt_strndup
  (
    char const* a,
    size_t l
  )
{
  return strndup(a, l);
}
