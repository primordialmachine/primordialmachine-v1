// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/Mutex.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CONCURRENCY_MUTEX_H_INCLUDED)
#define RING1_INTRINSIC_CONCURRENCY_MUTEX_H_INCLUDED

#if !defined(RING1_INTRINSIC_PRIVATE) || 1 != RING1_INTRINSIC_PRIVATE
#error("Do not include `Ring1/Intrinsic/Concurrency/Mutex.h` directly. Include `Ring1/_Include.h` instead.")
#endif

#include "Ring1/Annotations/_Include.h"

/// A recursive mutex.
/// A mutex must be initialized before use and uninitialized after use.
/// A mutex is in unlocked state after creation.
typedef struct Mkx_Mutex { void *pimpl; } Mkx_Mutex;

Ring1_CheckReturn() int
Mkx_Mutex_initialize
  (
    Mkx_Mutex *mutex
  );

void
Mkx_Mutex_uninitialize
  (
    Mkx_Mutex *mutex
  );

/// @brief Acquires a lock on a mutex until it is acquired.
/// @param A pointer to the mutex.
void
Mkx_Mutex_lock
  (
    Mkx_Mutex *mutex
  );

/// @brief Relinquishes a lock on a mutex.
/// @param A pointer to the mutex.
/// @undefined mutex is locked.
void
Mkx_Mutex_unlock
  (
    Mkx_Mutex *mutex
  );

#endif // RING1_INTRINSIC_CONCURRENCY_MUTEX_H_INCLUDED
