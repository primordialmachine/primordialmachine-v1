// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/ReadWriteLock.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_CONCURRENCY_READWRITELOCK_H_INCLUDED)
#define RING1_INTRINSIC_CONCURRENCY_READWRITELOCK_H_INCLUDED

/// A read write lock.
/// Excusive or shared access.
/// Recursiv locks are undefined behavior.
typedef struct Ring1_ReadWriteLock { void* pimpl; } Ring1_ReadWriteLock;

void
Ring1_ReadWriteLock_acquireWriteLock
  (
    Ring1_ReadWriteLock *readWriteLock
  );

void
Ring1_ReadWriteLock_relinquishWriteLock
  (
    Ring1_ReadWriteLock * readWriteLock
  );

void
Ring1_ReadWriteLock_acquireReadLock
  (
    Ring1_ReadWriteLock* readWriteLock
  );

void
Ring1_ReadWriteLock_relinquishReadLock
  (
    Ring1_ReadWriteLock* readWriteLock
  );

#define Ring1_ReadWriteLock_Initializer { 0 }

#endif  // RING1_INTRINSIC_CONCURRENCY_READWRITELOCK_H_INCLUDED
