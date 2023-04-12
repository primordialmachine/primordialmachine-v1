#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/WeakReference.h"

#include "Mkx/Object.h"
#undef MXK_OBJECT_INTERNAL

#include "Ring1/ReferenceCounter.h"
#include "Ring1/Status.h"
#include "Ring1/Intrinsic/_Include.h"
#include "Ring1/Memory/_Include.h"

Ring1_NonNull() static void
Mkx_WeakReference_destruct
  (
    Mkx_WeakReference* self
  )
{
  if (self->object) {
    // Remove this weak reference from the list of weak references of its object.
    Mkx_WeakReference **previous = &self->object->weakReferences,
                      *current = self->object->weakReferences;
    while (current) {
      if (current == self) {
        *previous = current->next;
        break;
      }
    }
  }
}

Mkx_Type_DefineClassType("Mkx.WeakReference",
                         Mkx_WeakReference,
                         MKX_WEAKREFERENCE,
                         Mkx_Object,
                         Mkx_Type_UseDefaultMemoryManager(),
                         Mkx_Type_ImplementInterfaces())

Ring1_CheckReturn() Ring1_NonNull()
Mkx_WeakReference_Dispatch_construct
  (
    Mkx_WeakReference_Dispatch* self
  )
{ return Ring1_Status_Success; }

static void
Mkx_WeakReference_Dispatch_destruct
  (
    Mkx_WeakReference_Dispatch* self
  )
{}

Ring1_CheckReturn() Ring1_Status
Mkx_WeakReference_construct
  (
    Mkx_WeakReference* self,
    Mkx_Object *object
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_WeakReference);
  if (Ring1_Unlikely(!type))
    return 1;
  if (Ring1_Unlikely(Mkx_Object_construct(MKX_OBJECT(self))))
    return 1;
  self->object = object;
  self->next = self->object->weakReferences;
  self->object->weakReferences = self;
  MKX_OBJECT(self)->type = type;
  return Ring1_Status_Success;
}

Ring1_CheckReturn() Ring1_Status
Mkx_WeakReference_create
  (
    Mkx_WeakReference** result,
    Mkx_Object* object
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_WeakReference);
  if (Ring1_Unlikely(!type))
    return 1;
  Mkx_WeakReference* self = Mkx_Object_allocate(type);
  if (Ring1_Unlikely(!self))
    return 1;
  if (Ring1_Unlikely(Mkx_WeakReference_construct(self, object))) {
    Mkx_Object_unreference(MKX_OBJECT(self));
    return 1;
  }
  *result = self;
  return Ring1_Status_Success;
}

Ring1_CheckReturn() Ring1_Status
Mkx_WeakReference_get
  (
    Mkx_Object **result,
    Mkx_WeakReference* self
  )
{ 
  if (self->object) {
    Mkx_Object_reference(self->object);
    *result = self->object;
  } else {
    *result = NULL;  
  }
  return Ring1_Status_Success;
}
