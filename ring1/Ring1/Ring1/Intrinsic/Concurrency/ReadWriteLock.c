// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/ReadWriteLock.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_INTRINSIC_PRIVATE (1)
#include "Ring1/Intrinsic/Concurrency/ReadWriteLock.h"
#undef RING1_INTRINSIC_PRIVATE

#define NOCOMM
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX
#undef NOCOMM

void
Ring1_ReadWriteLock_acquireWriteLock
  (
    Ring1_ReadWriteLock *readWriteLock
  )
{ AcquireSRWLockExclusive((SRWLOCK *)&readWriteLock->pimpl); }

void
Ring1_ReadWriteLock_relinquishWriteLock
  (
    Ring1_ReadWriteLock *readWriteLock
  )
{ ReleaseSRWLockExclusive((SRWLOCK *)&readWriteLock->pimpl); }

void
Ring1_ReadWriteLock_acquireReadLock
  (
    Ring1_ReadWriteLock* readWriteLock
  )
{ AcquireSRWLockShared((SRWLOCK *)&readWriteLock->pimpl); }

void
Ring1_ReadWriteLock_relinquishReadLock
  (
    Ring1_ReadWriteLock* readWriteLock
  )
{ ReleaseSRWLockShared((SRWLOCK*)&readWriteLock->pimpl); }
