#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/WeakReference.h"

#include "Runtime/Arguments.h"
#include "Ring2/_Include.h"

static void callback(void* context) {
  Ring2_Value_setVoid(&((Machine_WeakReference*)context)->value, Ring2_Void_Void);
}

static void Machine_WeakReference_construct(Machine_WeakReference* self, size_t numberOfArguments,
                                            Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->value = arguments[0];
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Ring2_Value_Tag_Object: {
      tag = Ring2_Gc_toTag(self->value.objectValue);
    } break;
    case Ring2_Value_Tag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    self->id = Ring2_Gc_Tag_addWeakReference(tag,
                                             (void*)self, &callback);
  }
  Machine_setClassType((Machine_Object*)self, Machine_WeakReference_getType());
}

Machine_WeakReference* Machine_WeakReference_create(Ring2_Value value) {
  Machine_ClassType* ty = Machine_WeakReference_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value const ARGUMENTS[] = { value };
  Machine_WeakReference* self
      = (Machine_WeakReference*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

static void Machine_WeakReference_destruct(Machine_WeakReference* self) {
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Ring2_Value_Tag_Object: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
    case Ring2_Value_Tag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    Ring2_Gc_Tag_removeWeakReference(tag, self->id);
  }
}

Ring2_Value Machine_WeakReference_get(Machine_WeakReference* self) {
  return self->value;
}
