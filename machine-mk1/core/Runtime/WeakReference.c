#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/WeakReference.h"

#include "Runtime/Arguments.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"

static void Machine_WeakReference_construct(Machine_WeakReference* self, size_t numberOfArguments,
                                            Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->value = arguments[0];
  Machine_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Machine_ValueFlag_Object: {
      tag = Machine_Gc_toTag(self->value.objectValue);
    } break;
    case Machine_ValueFlag_String: {
      tag = Machine_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    self->next = tag->weakReferences;
    tag->weakReferences = self;
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
  Machine_Gc_Tag* tag = NULL;
  switch (self->value.tag) {
    case Machine_ValueFlag_Object: {
      tag = Machine_Gc_toTag(self->value.stringValue);
    } break;
    case Machine_ValueFlag_String: {
      tag = Machine_Gc_toTag(self->value.stringValue);
    } break;
  };
  if (tag) {
    // Remove this weak reference from the list of weak reference of the object.
    Machine_WeakReference **previous, *current;
    previous = &tag->weakReferences;
    current = tag->weakReferences;
    while (NULL != current) {
      if (current == self) {
        break;
      } else {
        previous = &current->next;
        current = current->next;
      }
    }
    if (current) {
      *previous = current->next;
    } else {
      // Warn.
    }
  }
}

Machine_Value Machine_WeakReference_get(Machine_WeakReference* self) {
  return self->value;
}
