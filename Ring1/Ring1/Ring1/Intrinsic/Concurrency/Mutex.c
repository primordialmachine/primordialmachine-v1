// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Concurrency/Mutex.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_INTRINSIC_PRIVATE (1)
#include "Ring1/Intrinsic/Concurrency/Mutex.h"
#undef RING1_INTRINSIC_PRIVATE

#define NOCOMM
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX
#undef NOCOMM

Ring1_CheckReturn() int
Mkx_Mutex_initialize
  (
    Mkx_Mutex *mutex
  )
{
  mutex->pimpl = (void*)CreateMutex(NULL, FALSE, NULL);
  if (!mutex->pimpl)
  {
    return 1;
  }
  return 0;
}

void
Mkx_Mutex_uninitialize
  (
    Mkx_Mutex *mutex
  )
{
  CloseHandle((HANDLE)mutex->pimpl);
  mutex->pimpl = NULL;
}

void
Mkx_Mutex_lock
  (
    Mkx_Mutex *mutex
  )
{
  WaitForSingleObject((HANDLE)mutex->pimpl, INFINITE);
}

void
Mkx_Mutex_unlock
  (
    Mkx_Mutex *mutex
  )
{
  ReleaseMutex(mutex->pimpl);
}
