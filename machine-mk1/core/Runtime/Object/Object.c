#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/Object.h"

#include "Runtime/Machine.h"
#include "Runtime/Type.module.h"
#include "Runtime/Object/ClassType.module.h"
#include "Runtime/Object/InterfaceType.module.h"
#include <assert.h>

Machine_ClassObjectTag* o2cot(void* src) {
  return t2cot(Machine_Gc_toTag(src));
}

Machine_Gc_Tag* cot2t(Machine_ClassObjectTag* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) + N;
  return (Machine_Gc_Tag*)dst;
}

Machine_ClassObjectTag* t2cot(Machine_Gc_Tag* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) - N;
  return (Machine_ClassObjectTag*)dst;
}

Machine_Object* cot2o(Machine_ClassObjectTag* src) {
  return Machine_Gc_toAddress(cot2t(src));
}

static Machine_Integer Machine_Object_getHashValueImpl(Machine_Object const* self) {
  return Machine_hashPointer_i64(self);
}

static Machine_Boolean Machine_Object_isEqualToImpl(Machine_Object const* self,
                                                    Machine_Object const* other) {
  return self == other;
}

static Machine_String* Machine_Object_toStringImpl(Machine_Object const* self) {
  static_assert(INTPTR_MAX <= Machine_Integer_Greatest,
                "Machine_Integer can not represent an identity value");
  static_assert(INTPTR_MIN >= Machine_Integer_Least,
                "Machine_Integer can not represent an identity value");
  return Machine_Integer_toString((Machine_Integer)(intptr_t)self);
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

static void Machine_ClassObject_visit(void* self) {
#if defined(_DEBUG)
  Machine_Gc_Tag* tag = Machine_Gc_toTag(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(self);
  Machine_ClassType* classType = classObjectTag->classType;
  while (classType) {
    if (classType->object.visit) {
      classType->object.visit(self);
    }
    classType = classType->parent;
  }
}

static void Machine_ClassObject_finalize(void* self) {
#if defined(_DEBUG)
  Machine_Gc_Tag* tag = Machine_Gc_toTag(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(self);
  Machine_ClassType* classType = classObjectTag->classType;
  while (classType) {
    if (classType->object.destruct) {
      classType->object.destruct(self);
    }
    classType = classType->parent;
  }
  // NOW release the class type.
  Machine_Gc_unlock(classObjectTag->classType);
}

void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType) {
  assert(object != NULL);
  assert(classType != NULL);

#if defined(_DEBUG)
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif

  Machine_Type_ensureInitialized((Machine_Type*)classType);

  Machine_ClassObjectTag* classObjectTag = o2cot(object);
  if (classType) {
    Machine_Gc_lock(classType);
  }
  if (classObjectTag->classType) {
    Machine_Gc_unlock(classObjectTag->classType);
  }
  classObjectTag->classType = classType;
}

Machine_ClassType* Machine_getClassType(Machine_Object* object) {
#if defined(_DEBUG)
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(object);
  return classObjectTag->classType;
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments,
                                            Machine_Value const* arguments) {
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = sizeof(Machine_ClassObjectTag),
    .suffixSize = type->object.size,
    .visit = (Machine_Gc_VisitCallback*)&Machine_ClassObject_visit,
    .finalize = (Machine_Gc_FinalizeCallback*)&Machine_ClassObject_finalize,
  };
  void* p = Machine_Gc_allocate(&allocationArguments);
  if (!p) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Gc_Tag* t = Machine_Gc_toTag(p);
  Machine_ClassObjectTag* cot = o2cot(p);
  t->flags |= Machine_Flag_Class;
  cot->classType = type;
  Machine_Gc_lock(cot->classType);
  type->object.construct((Machine_Object*)p, numberOfArguments, arguments);
  return (Machine_Object*)p;
}

Machine_Integer Machine_Object_getHashValue(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, getHashValue);
}

Machine_Boolean Machine_Object_isEqualTo(Machine_Object const* self, Machine_Object const* other) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Object, isEqualTo, other);
}

Machine_String* Machine_Object_toString(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, toString);
}
