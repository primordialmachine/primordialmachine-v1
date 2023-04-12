// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Intrinsic/Concurrency/ThreadId.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_INTRINSIC_CONCURRENCY_THREADID_H_INCLUDED)
#define MKX_INTRINSIC_CONCURRENCY_THREADID_H_INCLUDED

#if !defined(RING1_INTRINSIC_PRIVATE) || 1 != RING1_INTRINSIC_PRIVATE
#error("Do not include `Mkx/Intrinsic/Concurrency/ThreadId.h` directly. Include `Mkx/Intrinsic.h` instead.")
#endif

#include <limits.h>

/// @brief The opaque type of a thread ID.
/// @detail
/// Uniquely identifies a thread during its lifetime.
/// Passable by value and equality comparable.
typedef unsigned long Mkx_ThreadId;

/// @brief Symbolic constant evaluating the invalid thread ID.
#define Mkx_InvalidThreadId (ULONG_MAX)

#endif // MKX_INTRINSIC_CONCURRENCY_THREADID_H_INCLUDED
