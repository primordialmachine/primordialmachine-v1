#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/WeakReference.h"

#include "Runtime/Arguments.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"

static void callback(void* context) {
  Machine_Value_setVoid(&((Machine_WeakReference*)context)->value, Machine_Void_Void);
}

static void Machine_WeakReference_construct(Machine_WeakReference* self, size_t numberOfArguments,
                                            Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->value = arguments[0];
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Machine_ValueFlag_Object: {
      tag = Ring2_Gc_toTag(self->value.objectValue);
    } break;
    case Machine_ValueFlag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    self->id = Ring2_Gc_Tag_addWeakReference(tag,
                                             (void*)self, &callback);
  }
  Machine_setClassType((Machine_Object*)self, Machine_WeakReference_getType());
}

Machine_WeakReference* Machine_WeakReference_create(Machine_Value value) {
  Machine_ClassType* ty = Machine_WeakReference_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Machine_Value const ARGUMENTS[] = { value };
  Machine_WeakReference* self
      = (Machine_WeakReference*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

static void Machine_WeakReference_destruct(Machine_WeakReference* self) {
  Ring2_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Machine_ValueFlag_Object: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
    case Machine_ValueFlag_String: {
      tag = Ring2_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    Ring2_Gc_Tag_removeWeakReference(tag, self->id);
  }
}

Machine_Value Machine_WeakReference_get(Machine_WeakReference* self) {
  return self->value;
}
