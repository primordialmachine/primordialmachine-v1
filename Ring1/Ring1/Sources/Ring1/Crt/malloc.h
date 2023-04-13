/// @file Ring1/Crt/malloc.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CRT_MALLOC_H_INCLUDED)
#define RING1_CRT_MALLOC_H_INCLUDED

#include <stddef.h>

#if defined(_MSC_VER)
_Check_return_
#endif
void *
crt_malloc
  (
    size_t n
  );

#endif // RING1_CRT_MALLOC_H_INCLUDED
