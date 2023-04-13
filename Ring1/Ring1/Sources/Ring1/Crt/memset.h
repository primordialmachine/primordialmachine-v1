/// @file Ring1/Crt/memset.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined (RING1_CRT_MEMSET_H_INCLUDED)
#define RING1_CRT_MEMSET_H_INCLUDED

#include <stddef.h>

void*
crt_memset
  (
    void* p,
    int v,
    size_t n
  );

#endif // RING1_CRT_MEMSET_H_INCLUDED
