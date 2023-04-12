
/// When a weak reference is created for an object o, it registers a weak reference callback with that object.
#if !defined(MKX_WEAKREFERENCES_WEAKREFERENCE_MODULE_H_INCLUDED)
#define MKX_WEAKREFERENCES_WEAKREFERENCE_MODULE_H_INCLUDED

#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/WeakReference.Module.h' directly, include 'Mkx/Object.h' instead.")
#endif

#include "Mkx/Object/WeakReference.h"

/// @module-scope
void
Mkx_WeakReferences_lock
  (
  );

/// @module-scope
void
Mkx_WeakReferences_unlock
  (
  );

/// @module-scope
Ring1_CheckReturn() Ring1_Status
Mkx_WeakReferences_initialize
  (
  );

/// @module-scope
void
Mkx_WeakReferences_uninitialize
  (
  );

#endif // MKX_WEAKREFERENCES_WEAKREFERENCE_MODULE_H_INCLUDED
