// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/WeakReference.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/WeakReference.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/All/_Include.h"
#include "Ring2/_Include.h"


static void
Machine_WeakReference_construct
  (
    Machine_WeakReference* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Machine_WeakReference_destruct
  (
    Machine_WeakReference* self
  );

static void
callback
  (
    void* context
  );

MACHINE_DEFINE_CLASSTYPE(Machine_WeakReference,
                         Machine_Object,
                         NULL,
                         &Machine_WeakReference_construct,
                         &Machine_WeakReference_destruct,
                         NULL,
                         NULL)

static void
callback
  (
    void* context
  )
{ Ring2_Value_setVoid(&((Machine_WeakReference*)context)->value, Ring2_Void_Void); }

static void
Machine_WeakReference_construct
  (
    Machine_WeakReference* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->value = arguments[0];
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
    case Ring2_Value_Tag_Array: {
      tag = Ring2_Gc_toTag(self->value.arrayValue);
    } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
    case Ring2_Value_Tag_Object: {
      tag = Ring2_Gc_toTag(self->value.objectValue);
    } break;
#endif
    case Ring2_Value_Tag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
    default: {
      Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
      Ring2_jump();
    } break;
  };
  if (tag) {
    self->id = Ring2_Gc_Tag_addWeakReference(tag, Ring1_cast(void *, self), &callback);
  }
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_WeakReference_getType());
}

Machine_WeakReference*
Machine_WeakReference_create
  (
    Ring2_Value value
  )
{
  Machine_Type* ty = Machine_WeakReference_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value const ARGUMENTS[] = { value };
  Machine_WeakReference* self = Ring1_cast(Machine_WeakReference*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

static void
Machine_WeakReference_destruct
  (
    Machine_WeakReference* self
  )
{
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
    case Ring2_Value_Tag_Array: {
      tag = Ring2_Gc_toTag(self->value.arrayValue);
    } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
    case Ring2_Value_Tag_Object: {
      tag = Ring2_Gc_toTag(self->value.objectValue);
    } break;
#endif
    case Ring2_Value_Tag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
    default: {
      Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
      Ring2_jump();
    } break;
  };
  if (tag) {
    Ring2_Gc_Tag_removeWeakReference(tag, self->id);
  }
}

Ring2_Value
Machine_WeakReference_get
  (
    Machine_WeakReference* self
  )
{ return self->value; }
