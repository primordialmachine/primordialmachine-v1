// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/Object.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/Object.h"
#include "Mkx/Object/Type.internal.h"
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/WeakReference.Module.h"
#undef MKX_OBJECT_INTERNAL


#include "Ring1/Memory/_Include.h"
#include <assert.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() static int
equalTo
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Object* other
  )
{
  if (Ring1_Unlikely(!result || !self || !other)) return 1;
  *result = (self == other);
  return 0;
}

Ring1_CheckReturn() static int
notEqualTo
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Object* other
  )
{
  bool temporary;
  if (Ring1_Unlikely(Mkx_Object_equalTo(&temporary, self, other))) return 1;
  *result = !temporary;
  return 0;
}

Ring1_CheckReturn() static Ring1_Status
hashValue
  (
    int64_t* result,
    Mkx_Object* self
  )
{
  if (Ring1_Unlikely(!result || !self)) return Ring1_Status_InvalidArgument;
  *result = (int64_t)(uintptr_t)self;
  return Ring1_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NonNull() static inline void
Mkx_Object_destruct
  (
    Mkx_Object* self
  )
{}

Ring1_CheckReturn() Ring1_NonNull() static inline int
Mkx_Object_Dispatch_construct
  (
    Mkx_Object_Dispatch *self
  )
{
  self->equalTo = &equalTo;
  self->notEqualTo = &notEqualTo;
  self->hashValue = &hashValue;
  return 0;
}

Ring1_NonNull() static inline void
Mkx_Object_Dispatch_destruct
  (
    Mkx_Object_Dispatch *self
  )
{}

static Mkx_Type* g_type = NULL;

static inline void
Mkx_Object_typeRemoved
  (
  )
{ g_type = NULL; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Mkx_Type*
__Mkx_Object_getType__
  (
  )
{
  if (!g_type)
  {
    Mkx_ClassTypeRegistrationInfo info =
    {
      .name = "Mkx.Object",
      //
      .parent = NULL,
      //
      .size = sizeof(Mkx_Object),
      .destruct = (void (*)(void*))&Mkx_Object_destruct,
      //
      .dispatchSize = sizeof(Mkx_Object_Dispatch),
      .constructDispatch = &Mkx_Object_Dispatch_construct,
      .destructDispatch = &Mkx_Object_Dispatch_destruct,
    };
    g_type = Mkx_registerClassType(&Mkx_Object_typeRemoved, &info);
  }
  return g_type;
}

Mkx_Type*
Mkx_Object_getType
  (
    const Mkx_Object* self
  )
{ return self ? self->type : NULL; }

Ring1_CheckReturn() int
Mkx_Object_construct
  (
    Mkx_Object* self
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_Object);
  if (Ring1_Unlikely(!type)) return 1;
  self->weakReferences = NULL;
  self->type = type;
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NonNull() void
Mkx_Object_reference
  (
    Mkx_Object* self
  )
{
  Ring1_ReferenceCounter_increment(&self->referenceCount);
}

Ring1_NonNull() void
Mkx_Object_unreference
  (
    Mkx_Object* self
  )
{
  Ring1_ReferenceCounter new = Ring1_ReferenceCounter_decrement(&self->referenceCount);
  if (0 == new)
  {
    // We prevent addition of new weak references by locking the weak references mutex:
    // Existing weak references might have re-increment the reference count at this point.
    // If the reference count is not 1 anymore, then abort destroy.
    Mkx_WeakReferences_lock();
    if (Ring1_ReferenceCounter_get(&self->referenceCount) > 0)
    {
      // Abort destroy.
      Mkx_WeakReferences_unlock();
      return;
    }
    // - for other threads:
    // The weak reference list can not be created, if it exists then no new weak references can be added.
    // - for this thread:
    // The callback of a weak reference must not add weak references or convert weak references to this object to strong references.
    // TODO: Assert no weak references are added from this thread and no weak references are turned into strong references from this thread.
    while (self->weakReferences) {
      Mkx_WeakReference* weakReference = self->weakReferences;
      self->weakReferences = weakReference->next;
      weakReference->object = NULL;
      weakReference->next = NULL;
    }
    Mkx_WeakReferences_unlock();
    // Run destructors.
    while (self->type)
    {
      if (MKX_CLASSTYPE(self->type)->destruct) MKX_CLASSTYPE(self->type)->destruct(self);
      self->type = MKX_CLASSTYPE(self->type)->parent;
    }
    // Run memory manager deallocation.
    Mkx_MemoryManager* memoryManager = self->memoryManager;
    memoryManager->deallocate(memoryManager, self);
  }
}

Ring1_CheckReturn() Ring1_NonNull() Ring1_ReferenceCounter
Mkx_Object_getReferences
  (
    Mkx_Object* self
  )
{ return Ring1_ReferenceCounter_get(&self->referenceCount); }

Ring1_CheckReturn() int
Mkx_Object_equalTo
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Object* other
  )
{ MKX_OBJECTCLASSMETHODCALLBODY(Mkx_Object, equalTo, result, self, other); }

Ring1_CheckReturn() int
Mkx_Object_notEqualTo
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Object* other
  )
{ MKX_OBJECTCLASSMETHODCALLBODY(Mkx_Object, notEqualTo, result, self, other); }

Ring1_CheckReturn() int
Mkx_Object_hashValue
  (
    int64_t* result,
    Mkx_Object* self
  )
{ MKX_OBJECTCLASSMETHODCALLBODY(Mkx_Object, hashValue, result, self); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @todo Use procedure style.
Ring1_CheckReturn() void*
Mkx_Object_allocate
  (
    Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!type)) return NULL;
  bool isClassType;
  if (Ring1_Unlikely(Mkx_Type_isClassType(&isClassType, type))) return NULL;
  if (!isClassType) return NULL;
  if (Ring1_Unlikely(Mkx_Type_ensureInitialized(type))) return NULL;
  assert(Mkx_Type_Flags_Initialized == (type->flags & Mkx_Type_Flags_Initialized));
  Mkx_MemoryManager* memoryManager = MKX_CLASSTYPE(type)->memoryManager;
  Mkx_Object* o;
  if (Ring1_Unlikely(memoryManager->allocate(&o, memoryManager, MKX_CLASSTYPE(type)->size)))
  { return NULL; }
  o->memoryManager = memoryManager;
  o->type = NULL;
  o->referenceCount = 1;
  return o;
}

Ring1_CheckReturn() Ring1_Status
Mkx_Object_isInstanceOf
  (
    bool* result,
    Mkx_Object* self,
    Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!result || !self || !type))
  { return Ring1_Status_InvalidArgument; }
  Mkx_Type* objectType = Mkx_Object_getType(self);
  if (Ring1_Unlikely(!objectType))
  { return 1; }
  /// @todo Use procedure style.
  if (Mkx_Type_isSubTypeOf(objectType, type))
  {
    *result = true;
    return 0;
  }
  else
  {
    *result = false;
    return 0;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() static int
Mkx_Invocation_getClassDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* classType
  );

Ring1_CheckReturn() static int
Mkx_Invocation_getInterfaceDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* interfaceType
  );

Ring1_CheckReturn() static int
Mkx_Invocation_getClassDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* classType
  )
{
  if (Ring1_Unlikely(!object))
  { return 1; }
  Mkx_Type* type = Mkx_Object_getType(MKX_OBJECT(object));
  if (Ring1_Unlikely(!type))
  { return 1; }
  *result = MKX_CLASSTYPE(type)->dispatch;
  return 0;
}

Ring1_CheckReturn() static int
Mkx_Invocation_getInterfaceDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* interfaceType
  )
{
  if (Ring1_Unlikely(!object))
  { return 1; }
  Mkx_Type* type = Mkx_Object_getType(MKX_OBJECT(object));
  if (Ring1_Unlikely(!type))
  { return 1; }
  Mkx_ClassType* classType = MKX_CLASSTYPE(type);
  int64_t dispatchIndex = 0;
  if (Ring1_Unlikely(Mkx_Dispatches_getOrCreateEntry(&dispatchIndex, classType->interfaceDispatches, interfaceType, false)))
  {
    return 1;
  }
  Mkx_Dispatch* dispatch = NULL;
  if (Ring1_Unlikely(Mkx_Dispatches_getEntryAt(&dispatch, classType->interfaceDispatches, dispatchIndex)))
  {
    return 1;
  }
  if (Ring1_Unlikely(!dispatch))
  {
    return 1;
  }
  *result = dispatch;
  return 0;
}

Ring1_CheckReturn() int
Mkx_Invocation_getDispatch
  (
    void** result,
    Mkx_Object* object,
    Mkx_Type* type
  )
{
  if (type)
  { return Mkx_Invocation_getInterfaceDispatch(result, object, type); }
  { return Mkx_Invocation_getClassDispatch(result, object, NULL); }
}

