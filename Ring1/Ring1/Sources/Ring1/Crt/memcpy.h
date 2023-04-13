/// @file Ring1/Crt/memcpy.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined (RING1_CRT_MEMCPY_H_INCLUDED)
#define RING1_CRT_MEMCPY_H_INCLUDED

#include <stddef.h>

void*
crt_memcpy
  (
    void* p,
    void const* q,
    size_t n
  );

#endif // RING1_CRT_MEMCPY_H_INCLUDED
