#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/WeakReference.Module.h"
#undef MKX_OBJECT_INTERNAL

#define RING1_INTRINSIC_PRIVATE (1)
#include "Ring1/Intrinsic/Concurrency/Mutex.h"
#undef RING1_INTRINSIC_PRIVATE

static Mkx_Mutex g_mutex;

static void
lock
  (
  )
{ Mkx_Mutex_lock(&g_mutex); }

static void
unlock
  (
  )
{ Mkx_Mutex_unlock(&g_mutex); }

Ring1_CheckReturn() Ring1_Status
Mkx_WeakReferences_initialize
  (
  )
{
  if (Mkx_Mutex_initialize(&g_mutex))
  { return 1; }
  return Ring1_Status_Success;
}

void
Mkx_WeakReferences_uninitialize
  (
  )
{ Mkx_Mutex_uninitialize(&g_mutex); }

void
Mkx_WeakReferences_lock
  (
  )
{ Mkx_Mutex_lock(&g_mutex); }

void
Mkx_WeakReferences_unlock
  (
  )
{ Mkx_Mutex_unlock(&g_mutex); }
