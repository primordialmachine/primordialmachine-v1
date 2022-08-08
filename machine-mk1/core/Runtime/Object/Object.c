#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/Object.h"

#include "Runtime/Assertions.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Hash.h"
#include "Runtime/Object/ClassType.module.h"
#include "Runtime/Object/InterfaceType.module.h"
#include "Runtime/Type.module.h"
#include <assert.h>

static Ring2_Integer Machine_Object_getHashValueImpl(Machine_Object const* self) {
  int64_t temporary;
  Ring1_Hash_toI64_p(&temporary, self);
  return temporary;
}

static Ring2_Boolean Machine_Object_isEqualToImpl(Machine_Object const* self,
                                                  Machine_Object const* other) {
  return self == other;
}

static Ring2_String* Machine_Object_toStringImpl(Machine_Object const* self) {
  static_assert(INTPTR_MAX <= Ring2_Integer_Greatest,
                "Machine_Integer can not represent an identity value");
  static_assert(INTPTR_MIN >= Ring2_Integer_Least,
                "Machine_Integer can not represent an identity value");
  return Ring2_Integer_toString(Ring2_Context_get(), (Ring2_Integer)(intptr_t)self);
}

static void Machine_Object_constructClass(Machine_Object_Class* self) {
  self->getHashValue = &Machine_Object_getHashValueImpl;
  self->isEqualTo = &Machine_Object_isEqualToImpl;
  self->toString = &Machine_Object_toStringImpl;
}

static Machine_ClassType* g_Machine_Object_ClassType = NULL;
static void Machine_Object_onTypeDestroyed() {
  g_Machine_Object_ClassType = NULL;
}

Machine_ClassType* Machine_Object_getType() {
  if (!g_Machine_Object_ClassType) {
    Machine_CreateClassTypeArgs args = {
      .createTypeArgs = {
        .typeRemoved = (Machine_TypeRemovedCallback*)&Machine_Object_onTypeDestroyed,
      },
      .parent = NULL,
      .object.size = sizeof(Machine_Object),
      .object.visit = (Machine_ClassObjectVisitCallback*)NULL,
      .object.construct = (Machine_ClassObjectConstructCallback*)&Machine_Object_construct,
      .object.destruct = (Machine_ClassObjectDestructCallback*)NULL,
      .class.size = sizeof(Machine_Object_Class),
      .class.construct = (Machine_ClassConstructCallback*)&Machine_Object_constructClass,
    };
    g_Machine_Object_ClassType = Machine_createClassType(&args);
  }
  return g_Machine_Object_ClassType;
}

void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments,
                              Machine_Value const* arguments) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_setClassType(self, Machine_Object_getType());
}

static void Machine_ClassObject_visit(void *gc, void* self) {
  Machine_Object* object = (Machine_Object*)self;
  Machine_ClassType *classType = object->classType;
  while (classType) {
    if (classType->object.visit) {
      classType->object.visit(self);
    }
    classType = classType->parent;
  }
}

static void Machine_ClassObject_finalize(void *gc, void* self) {
  Machine_Object* object = (Machine_Object *)self;
  Machine_ClassType* classType = object->classType;
  while (classType) {
    if (classType->object.destruct) {
      classType->object.destruct(self);
    }
    classType = classType->parent;
  }
  // NOW release the class type.
  Ring2_Gc_unlock(object->classType);
}

void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType) {
  assert(object != NULL);
  assert(classType != NULL);

  Machine_Type_ensureInitialized((Machine_Type*)classType);

  if (classType) {
    Ring2_Gc_lock(classType);
  }
  if (object->classType) {
    Ring2_Gc_unlock(object->classType);
  }
  object->classType = classType;
}

Machine_ClassType* Machine_getClassType(Machine_Object* object) {
  return object->classType;
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments,
                                            Machine_Value const* arguments) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_ClassObject_finalize,
    .visit = (Ring2_Gc_VisitCallback*)&Machine_ClassObject_visit,
  };
  Machine_Gc_AllocationArguments const allocationArguments = {
    .suffixSize = type->object.size,
    .type = &gcType,
  };
  Machine_Object *o = Machine_Gc_allocate(&allocationArguments);
  if (!o) {
    Ring2_jump();
  }
  Ring2_Gc_Tag* t = Ring2_Gc_toTag(o);
  o->classType = type;
  Ring2_Gc_lock(o->classType);
  type->object.construct((Machine_Object*)o, numberOfArguments, arguments);
  return o;
}

Ring2_Integer Machine_Object_getHashValue(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, getHashValue);
}

Ring2_Boolean Machine_Object_isEqualTo(Machine_Object const* self, Machine_Object const* other) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Object, isEqualTo, other);
}

Ring2_String* Machine_Object_toString(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, toString);
}
