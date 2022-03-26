#if !defined(RING1_MEMORY_WINDOWS_GETPAGESIZE_H_INCLUDED)
#define RING1_MEMORY_WINDOWS_GETPAGESIZE_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"
#include <stddef.h>

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_Windows_getPageSize
  (
    size_t* result
  );

#endif // RING1_MEMORY_WINDOWS_GETPAGESIZE_H_INCLUDED
