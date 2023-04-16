// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/GetCurrentThreadId.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_INTRINSIC_PRIVATE (1)
#include "Ring1/Intrinsic/Concurrency/GetCurrentThreadId.h"
#undef RING1_INTRINSIC_PRIVATE

#define NOCOMM
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX
#undef NOCOMM

Ring1_CheckReturn() Mkx_ThreadId
Mkx_GetCurrentThreadId
  (
  )
{ 
  // We assume here that GetCurrentThreadId is never ULONG_MAX aka Mkx_InvalidThreadId.
  // This assumption holds so far.
  return GetCurrentThreadId();
}