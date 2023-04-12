#if !defined(MKX_WEAKREFERENCES_WEAKREFERENCE_H_INCLUDED)
#define MKX_WEAKREFERENCES_WEAKREFERENCE_H_INCLUDED

#include "Ring1/Status.h"
#include "Ring1/Intrinsic/_Include.h"
#include "Mkx/Object/Object.h"

#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/WeakReference.h' directly, include 'Mkx/Object.h' instead.")
#endif

Mkx_Type_DeclareClassType("Mkx.WeakReference",
                          Mkx_WeakReference,
                          MKX_WEAKREFERENCE)

struct Mkx_WeakReference_Dispatch
{
  Mkx_Object_Dispatch parent;
};

struct Mkx_WeakReference
{
  Mkx_Object parent;
  Mkx_Object* object;
  Mkx_WeakReference* next;
};

/// @brief Create a weak reference.
/// @param result A pointer to a <code>Mkx_WeakReference *</code> variable.
/// @param object A pointer to an <code>Mkx_Object</code> object.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
Ring1_CheckReturn() Ring1_Status
Mkx_WeakReference_create
  (
    Mkx_WeakReference** result,
    Mkx_Object* object
  );

/// @brief Increment the reference count of a weak reference.
/// @param object A pointer to an <code>Mkx_WeakReference</code> object.
Ring1_CheckReturn() Ring1_Status
Mkx_WeakReference_get
  (
    Mkx_Object **result,
    Mkx_WeakReference* self
  );

#endif // MKX_WEAKREFERENCES_WEAKREFERENCE_H_INCLUDED
