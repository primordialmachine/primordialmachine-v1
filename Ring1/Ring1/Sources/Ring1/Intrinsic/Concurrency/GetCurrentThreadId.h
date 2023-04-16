// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/GetCurrentThreadId.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CONCURRENCY_GETCURRENTTHREADID_H_INCLUDED)
#define RING1_INTRINSIC_CONCURRENCY_GETCURRENTTHREADID_H_INCLUDED

#if !defined(RING1_INTRINSIC_PRIVATE) || 1 != RING1_INTRINSIC_PRIVATE
#error("Do not include `Ring1/Intrinsic/Concurrency/GetCurrentThreadId.h` directly. Include `Ring1/_Include.h` instead.")
#endif

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Intrinsic/Concurrency/ThreadId.h"

/// @brief Get the ID of the current thread.
/// @return The ID of the current thread on success, Mkx_InvalidThreadId on failure.
Ring1_CheckReturn() Mkx_ThreadId
Mkx_GetCurrentThreadId
  (
  );

#endif // RING1_INTRINSIC_CONCURRENCY_GETCURRENTTHREADID_H_INCLUDED
