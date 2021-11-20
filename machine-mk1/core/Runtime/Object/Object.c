#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/Object.h"



#include <assert.h>
#include "Machine.h"



Machine_ClassObjectTag* o2cot(void* src) {
  return t2cot(Machine_o2t(src));
}

Machine_Tag* cot2t(void* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) + N;
  return (Machine_Tag*)dst;
}

Machine_ClassObjectTag* t2cot(void* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) - N;
  return (Machine_ClassObjectTag*)dst;
}

Machine_Object* cot2o(void* src) {
  return Machine_t2o(cot2t(src));
}

static size_t Machine_Object_getHashValueImpl(Machine_Object const* self) {
  return (size_t)(uintptr_t)self;
}

static Machine_Boolean Machine_Object_isEqualToImpl(Machine_Object const* self, Machine_Object const* other) {
  return self == other;
}

static Machine_String* Machine_Object_toStringImpl(Machine_Object const* self) {
  static_assert(INTPTR_MAX <= Machine_Integer_Greatest, "Machine_Integer can not represent an identity value");
  static_assert(INTPTR_MIN >= Machine_Integer_Least, "Machine_Integer can not represent an identity value");
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
      .size = sizeof(Machine_Object),
      .visit = (Machine_ClassObjectVisitCallback*)NULL,
      .construct = (Machine_ClassObjectConstructCallback*)&Machine_Object_construct,
      .destruct = (Machine_ClassObjectDestructCallback*)NULL,
      .classSize = sizeof(Machine_Object_Class),
      .constructClass = (Machine_ClassConstructCallback*)&Machine_Object_constructClass,
    };
    g_Machine_Object_ClassType =
      Machine_createClassType
      (
        &args
      );
  }
  return g_Machine_Object_ClassType;
}

void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments, Machine_Value const* arguments) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_setClassType(self, Machine_Object_getType());
}

static void Machine_ClassObject_visit(void* self) {
#if defined(_DEBUG)
  Machine_Tag* tag = Machine_o2t(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(self);
  Machine_ClassType* classType = classObjectTag->classType;
  while (classType) {
    if (classType->visit) {
      classType->visit(self);
    }
    classType = classType->parent;
  }
}

static void Machine_ClassObject_finalize(void* self) {
#if defined(_DEBUG)
  Machine_Tag* tag = Machine_o2t(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(self);
  Machine_ClassType* classType = classObjectTag->classType;
  while (classType) {
    if (classType->destruct) {
      classType->destruct(self);
    }
    classType = classType->parent;
  }
  // NOW release the class type.
  Machine_unlock(classObjectTag->classType);
}

void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType) {
  assert(object != NULL);
  assert(classType != NULL);

#if defined(_DEBUG)
  Machine_Tag* tag = Machine_o2t(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif

  Machine_ClassObjectTag* classObjectTag = o2cot(object);
  if (classType) {
    Machine_lock(classType);
  }
  if (classObjectTag->classType) {
    Machine_unlock(classObjectTag->classType);
  }
  classObjectTag->classType = classType;
}

Machine_ClassType* Machine_getClassType(Machine_Object* object) {
#if defined(_DEBUG)
  Machine_Tag* tag = Machine_o2t(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = o2cot(object);
  return classObjectTag->classType;
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, const Machine_Value* arguments) {
  void* p = Machine_allocateEx(type->size, sizeof(Machine_ClassObjectTag), &Machine_ClassObject_visit, &Machine_ClassObject_finalize);
  if (!p) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Tag* t = Machine_o2t(p);
  Machine_ClassObjectTag* cot = o2cot(p);
  t->flags |= Machine_Flag_Class;
  cot->classType = type;
  Machine_lock(cot->classType);
  type->construct((Machine_Object*)p, numberOfArguments, arguments);
  return (Machine_Object*)p;
}

size_t Machine_Object_getHashValue(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, getHashValue);
}

Machine_Boolean Machine_Object_isEqualTo(Machine_Object const* self, Machine_Object const* other) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Object, isEqualTo, other);
}

Machine_String* Machine_Object_toString(Machine_Object const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Object, toString);
}
