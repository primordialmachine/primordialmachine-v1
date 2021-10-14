#define MACHINE_RUNTIME_PRIVATE (1)
#include "Machine.h"



#include "Runtime/String.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Stack {
  Machine_Value* elements;
  size_t size, capacity;
} Stack;

static int Stack_initialize(Stack* self) {
  self->elements = malloc(sizeof(Machine_Value) * 8);
  if (!self->elements) {
    return Machine_Status_AllocationFailed;
  }
  for (size_t i = 0; i < 8; ++i) {
    Machine_Value_setVoid(self->elements + i, Machine_Void_Void);
  }
  self->size = 0;
  self->capacity = 8;
  return 0;
}

static void Stack_uninitialize(Stack* self) {
  if (self->elements) {
    free(self->elements);
    self->elements = NULL;
  }
}

int Stack_create(Stack **stack) {
  Stack *stack0 = malloc(sizeof(Stack));
  if (!stack0) {
    return Machine_Status_AllocationFailed;
  }
  int result = Stack_initialize(stack0);
  if (result) {
    free(stack0);
    return result;
  }
  *stack = stack0;
  return 0;
}

void Stack_destroy(Stack* stack) {
  Stack_uninitialize(stack);
  free(stack);
}

static Machine_Tag* g_objects = NULL;
static Machine_Tag* g_gray = NULL;
static Stack *g_stack = NULL;
static size_t g_objectCount = 0;

int Machine_startup() {
  int result;
  result = Stack_create(&g_stack);
  if (result) {
    return result;
  }
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_ClassObjectTag* o2cot(void* src);

static Machine_Tag* o2t(void* src);

static Machine_Tag* cot2t(void* src);

static Machine_ClassObjectTag* t2cot(void* src);

static Machine_Object* cot2o(void* src);

static Machine_Object* t2o(void* src);

static Machine_ClassObjectTag* o2cot(void* src) {
  return t2cot(o2t(src));
}

static Machine_Tag* o2t(void* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) - N;
  return (Machine_Tag*)dst;
}

static Machine_Tag* cot2t(void* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) + N;
  return (Machine_Tag*)dst;
}

static Machine_ClassObjectTag* t2cot(void* src) {
  static const size_t N = sizeof(Machine_ClassObjectTag);
  char* dst = ((char*)src) - N;
  return (Machine_ClassObjectTag*)dst;
}

static Machine_Object* cot2o(void* src) {
  return t2o(cot2t(src));
}

static Machine_Object* t2o(void* src) {
  static const size_t N = sizeof(Machine_Tag);
  char* dst = ((char*)src) + N;
  return (Machine_Object*)dst;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_JumpTarget* g_jumpTargets = NULL;

void Machine_pushJumpTarget(Machine_JumpTarget* jumpTarget) {
  jumpTarget->previous = g_jumpTargets;
  g_jumpTargets = jumpTarget;
}

void Machine_popJumpTarget() {
  g_jumpTargets = g_jumpTargets->previous;
}

NORETURN void Machine_jump() {
  longjmp(g_jumpTargets->environment, -1);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void SET_WHITE(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_Black;
  tag->flags |= Machine_Flag_White;
}

static bool IS_WHITE(Machine_Tag* tag) {
  return (tag->flags & Machine_Flag_Gray) == Machine_Flag_White;
}

static void SET_BLACK(Machine_Tag* tag) {
  tag->flags &= ~Machine_Flag_White;
  tag->flags |= Machine_Flag_Black;
}

static bool IS_BLACK(Machine_Tag* tag) {
  return (tag->flags & Machine_Flag_Black) == Machine_Flag_Black;
}

static void SET_GRAY(Machine_Tag* tag) {
  tag->flags |= Machine_Flag_Gray;
}

static bool IS_GRAY(Machine_Tag* tag) {
  return (tag->flags & Machine_Flag_Gray) == Machine_Flag_Gray;
}

static bool IS_ROOT(Machine_Tag* tag) {
  return (tag->flags & Machine_Flag_Root) == Machine_Flag_Root;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void visit(Machine_Tag* tag) {
  if (IS_GRAY(tag) || IS_BLACK(tag)) {
    return;
  }
  tag->gray = g_gray;
  g_gray = tag;
  SET_GRAY(tag);
}

static void rungc(size_t* live, size_t *dead) {
  (*live) = 0;
  (*dead) = 0;

  // Color all objects white. Add root objects or objects with a lock count greater than 0 to the gray list.
  for (Machine_Tag* object = g_objects; NULL != object; object = object->next) {
    SET_WHITE(object);
    if (IS_ROOT(object) || object->lockCount > 0) {
      object->gray = g_gray;
      g_gray = object;
      SET_GRAY(object);
    }
  }
  // Pop objects from gray list, visit them, color them black.
  while (g_gray) {
    assert(g_gray != NULL);
    Machine_Tag* object = g_gray; g_gray = object->gray;
    assert(object != NULL);
    if (object->visit) {
      object->visit(t2o(object));
    }
    SET_BLACK(object);
  }
  // Separate dead (white) and live (black) objects.
  Machine_Tag** previous = &g_objects, * current = g_objects;
  while (current) {
    if (IS_WHITE(current)) {
      *previous = current->next;
      Machine_Tag* object = current;
      current = current->next;
      if (object->finalize) {
        object->finalize(t2o(object));
      }
      if ((object->flags & Machine_Flag_Class) == Machine_Flag_Class) {
        free(t2cot(object));
      } else {
        free(object);
      }
      g_objectCount--;
      (*dead)++;
    } else {
      previous = &current->next;
      current = current->next;
      (*live)++;
    }
  }
}

void Machine_update() {
  size_t live, dead;
  rungc(&live, &dead);
}

void* Machine_allocate(size_t size, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize) {
  Machine_Tag* t = malloc(sizeof(Machine_Tag) + size);
  if (!t) {
    return NULL;
  }
  g_objectCount++;
  memset(t, 0, sizeof(Machine_Tag) + size);
  t->lockCount = 0;
  t->flags = Machine_Flag_White;
  t->size = size;
  t->visit = visit;
  t->finalize = finalize;
  t->next = g_objects; g_objects = t;
  t->gray = NULL;
  return t2o(t);
}

void Machine_visit(void* object) {
  Machine_Tag* tag = o2t(object);
  if (IS_WHITE(tag)) {
    tag->gray = g_gray;
    g_gray = tag;
    SET_GRAY(tag);
  }
}

void Machine_lock(void* object) {
  Machine_Tag* tag = o2t(object);
  tag->lockCount++;
}

void Machine_unlock(void* object) {
  Machine_Tag* tag = o2t(object);
  tag->lockCount--;
}

void Machine_setRoot(void* object, bool isRoot) {
  Machine_Tag* tag = o2t(object);
  if (isRoot) {
    tag->flags |= Machine_Flag_Root;
  }
  else {
    tag->flags &= ~Machine_Flag_Root;
  }
}

bool Machine_getRoot(void* object) {
  Machine_Tag* tag = o2t(object);
  return Machine_Flag_Root == (tag->flags & Machine_Flag_Root);
}

void Machine_shutdown() {
  size_t MAX_RUN = 8;
  size_t live = 0, dead = 0, run = 0;
  
  do {
    rungc(&live, &dead);
    run++;
  } while (live > 0 && run < MAX_RUN);

  if (live > 0) {
    fprintf(stderr, "warning %zu live objects remaining\n", live);
  }

  Stack_destroy(g_stack);
  g_stack = NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Stack_ensureFreeCapacity(Stack* self, size_t requiredFreeCapacity) {
  size_t availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    size_t requiredAdditionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);
    size_t availableAdditionalCapacity = maximalCapacity - self->capacity;
    if (availableAdditionalCapacity < requiredAdditionalCapacity) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    // TODO: This ensures that we have enough free capacity in any case.
    // However, we should try to allocate more to avoid reallocating over and over.
    size_t newCapacity = self->capacity + requiredAdditionalCapacity;
    Machine_Value *newElements = realloc(self->elements, sizeof(Machine_Value) * newCapacity);
    if (newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
}

void Machine_loadBoolean(Machine_Boolean value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setBoolean(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadInteger(Machine_Integer value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setInteger(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadForeignProcedure(Machine_ForeignProcedure* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setForeignProcedure(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadObject(Machine_Object* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setObject(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadReal(Machine_Real value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setReal(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadString(Machine_String* value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setString(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

void Machine_loadVoid(Machine_Void value) {
  Stack_ensureFreeCapacity(g_stack, 1);
  Machine_Value_setVoid(g_stack->elements + g_stack->size, value);
  g_stack->size++;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static size_t Machine_Object_getHashValueImpl(Machine_Object const * self) {
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

static Machine_ClassType * g_Machine_Object_ClassType = NULL;
static void Machine_Object_onTypeDestroyed() {
  g_Machine_Object_ClassType = NULL;
}

Machine_ClassType* Machine_Object_getClassType() {
  if (!g_Machine_Object_ClassType) {
    Machine_CreateClassTypeArgs args = {
      .parent = NULL,
      .size = sizeof(Machine_Object),
      .typeRemoved = (Machine_ClassTypeRemovedCallback*)&Machine_Object_onTypeDestroyed,
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
  Machine_setClassType(self, Machine_Object_getClassType());
}

static void Machine_ClassObject_visit(void* self) {
#if defined(_DEBUG)
  Machine_Tag* tag = (Machine_Tag *)o2t(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = (Machine_ClassObjectTag *)o2cot(self);
  Machine_ClassType *classType = classObjectTag->classType;
  while (classType) {
    if (classType->visit) {
      classType->visit(self);
    }
    classType = classType->parent;
  }
}

static void Machine_ClassObject_finalize(void* self) {
#if defined(_DEBUG)
  Machine_Tag* tag = (Machine_Tag*)o2t(self);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = (Machine_ClassObjectTag *)o2cot(self);
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
  Machine_Tag* tag = (Machine_Tag *)o2t(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif

  Machine_ClassObjectTag* classObjectTag = (Machine_ClassObjectTag *)o2cot(object);
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
  Machine_Tag* tag = (Machine_Tag *)o2t(object);
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = (Machine_ClassObjectTag *)o2cot(object);
  return classObjectTag->classType;
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_ClassObjectTag* classObjectTag = malloc(sizeof(Machine_ClassObjectTag) + sizeof(Machine_Tag) + type->size);
  if (!classObjectTag) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  g_objectCount++;
  memset(classObjectTag, 0, sizeof(Machine_ClassObjectTag) + sizeof(Machine_Tag) + type->size);
  Machine_Tag* tag = (Machine_Tag *)cot2t(classObjectTag);
  tag->flags = Machine_Flag_White | Machine_Flag_Class;
  tag->size = type->size;
  tag->visit = &Machine_ClassObject_visit;
  tag->finalize = &Machine_ClassObject_finalize;
  tag->next = g_objects; g_objects = tag;
  tag->gray = NULL;
  classObjectTag->classType = type;
  Machine_lock(classObjectTag->classType);
  Machine_Object* object = (Machine_Object*)t2o(tag);
  type->construct(object, numberOfArguments, arguments);
  return object;
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
