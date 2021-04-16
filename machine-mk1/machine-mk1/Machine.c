#include "Machine.h"



#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_StatusValue g_status = Machine_Status_Success;

Machine_StatusValue Machine_getStatus() {
  return g_status;
}

void Machine_setStatus(Machine_StatusValue status) {
  g_status = status;
}

static Machine_Tag* g_objects = NULL;
static Machine_Tag* g_gray = NULL;

int Machine_startup() {
  return 0;
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

__declspec(noreturn) void Machine_jump() {
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

void Machine_update() {
  // Color all objects white. Add root objects to gray list.
  for (Machine_Tag* object = g_objects; NULL != object; object = object->next) {
    SET_WHITE(object);
    if (IS_ROOT(object)) {
      object->gray = g_gray;
      g_gray = object;
      SET_GRAY(object);
    }
  }
  // Pop objects from gray list, visit them, color them black.
  while (g_gray) {
    Machine_Tag* object = g_gray; g_gray = object->gray;
    if (object->visit) {
      object->visit(object + 1);
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
        object->finalize(object + 1);
      }
      if ((object->flags & Machine_Flag_Class) == Machine_Flag_Class) {
        free(((Machine_ClassObjectTag *)(object + 1)) - 1);
      } else {
        free(object);
      }
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void* Machine_allocate(size_t size, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize) {
  Machine_Tag* t = malloc(sizeof(Machine_Tag) + size);
  if (!t) {
    return NULL;
  }
  memset(t, 0, sizeof(Machine_Tag) + size);
  t->flags = Machine_Flag_White;
  t->size = size;
  t->visit = visit;
  t->finalize = finalize;
  t->next = g_objects; g_objects = t;
  t->gray = NULL;
  return (void*)(((char*)t) + sizeof(Machine_Tag));
}

void Machine_visit(void* object) {
  Machine_Tag* tag = ((Machine_Tag*)object) - 1;
  if (IS_WHITE(tag)) {
    tag->gray = g_gray;
    g_gray = tag;
    SET_GRAY(tag);
  }
}

void Machine_setRoot(void* object, bool isRoot) {
  Machine_Tag* tag = ((Machine_Tag*)object) - 1;
  if (isRoot) {
    tag->flags |= Machine_Flag_Root;
  }
  else {
    tag->flags &= ~Machine_Flag_Root;
  }
}

bool Machine_getRoot(void* object) {
  Machine_Tag* tag = ((Machine_Tag*)object) - 1;
  return Machine_Flag_Root == (tag->flags & Machine_Flag_Root);
}

void Machine_shutdown() {
  Machine_update();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Machine_String {
  size_t hashValue;
  size_t n;
  char p[];
};

Machine_String* Machine_String_create_noraise(const char* p, size_t n) {
  Machine_String* self = Machine_allocate(sizeof(Machine_String) + n, NULL, NULL);
  if (!self) {
    return NULL;
  }
  memcpy(self->p, p, n);
  self->n = n;
  self->hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    self->hashValue = p[i] + self->hashValue * 37;
  }
  return self;
}

Machine_String* Machine_String_create(const char* p, size_t n) {
  Machine_String* self = Machine_allocate(sizeof(Machine_String) + n, NULL, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  memcpy(self->p, p, n);
  self->n = n;
  self->hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    self->hashValue = p[i] + self->hashValue * 37;
  }
  return self;
}


bool Machine_String_equalTo(Machine_String* self, Machine_String* other) {
  if (self == other) return true;
  if (self->n == other->n && self->hashValue == other->hashValue) {
    return !memcmp(self->p, other->p, self->n);
  }
  return false;
}

size_t Machine_String_getHashValue(Machine_String* self) {
  return self->hashValue;
}

const char* Machine_String_getBytes(Machine_String* self) {
  return self->p;
}

size_t Machine_String_getNumberOfBytes(Machine_String* self) {
  return self->n;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Machine_ClassType {
  Machine_ClassType* parent;
  size_t size;
  Machine_ClassObjectVisitCallback* visit;
  Machine_ClassObjectConstructCallback* construct;
  Machine_ClassObjectDestructCallback* destruct;
};

static void Machine_ClassType_visit(Machine_ClassType* self) {
  if (self->parent) {
    Machine_visit(self->parent);
  }
}

Machine_ClassType* Machine_createClassType(Machine_ClassType* parent, size_t size, Machine_ClassObjectVisitCallback* visit, Machine_ClassObjectConstructCallback* construct, Machine_ClassObjectDestructCallback* destruct) {
  Machine_ClassType *classType = Machine_allocate(sizeof(Machine_ClassType), (Machine_VisitCallback *)&Machine_ClassType_visit, NULL);
  if (!classType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  classType->size = size;
  classType->visit = visit;
  classType->construct = construct;
  classType->destruct = destruct;
  return classType;
}

static void Machine_ClassObject_visit(void* self) {
#if defined(_DEBUG)
  Machine_Tag* tag = ((Machine_Tag*)self) - 1;
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = ((Machine_ClassObjectTag*)self) - 1;
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
  Machine_Tag* tag = ((Machine_Tag*)self) - 1;
  assert((tag->flags & Machine_Flag_Class) == Machine_Flag_Class);
#endif
  Machine_ClassObjectTag* classObjectTag = ((Machine_ClassObjectTag*)self) - 1;
  Machine_ClassType* classType = classObjectTag->classType;
  while (classType) {
    if (classType->destruct) {
      classType->destruct(self);
    }
    classType = classType->parent;
  }
}

Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_ClassObjectTag* t = malloc(sizeof(Machine_ClassObjectTag) + type->size);
  if (!t) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  memset(t, 0, sizeof(Machine_ClassObjectTag) + type->size);
  t->tag.flags = Machine_Flag_White | Machine_Flag_Class;
  t->tag.size = type->size;
  t->tag.visit = &Machine_ClassObject_visit;
  t->tag.finalize = &Machine_ClassObject_finalize;
  t->tag.next = g_objects; g_objects = &t->tag;
  t->tag.gray = NULL;
  t->classType = type;

  type->construct((void *)(t + 1), numberOfArguments, arguments);

  return (void*)(t + 1);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Machine_StringBuffer {
  char* p;
  size_t s; /**< The size. */
  size_t c; /**< The capacity.  */
};

static void Machine_StringBuffer_construct(Machine_StringBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->p = NULL;
  self->s = 0;
  self->c = 0;
}

static void Machine_StringBuffer_destruct(Machine_StringBuffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
}

Machine_ClassType* Machine_StringBuffer_getClassType() {
  return
    Machine_createClassType
      (
        NULL,
        sizeof(Machine_StringBuffer),
        (Machine_ClassObjectVisitCallback*)NULL,
        (Machine_ClassObjectConstructCallback*)&Machine_StringBuffer_construct,
        (Machine_ClassObjectDestructCallback*)&Machine_StringBuffer_destruct
      );
}

Machine_StringBuffer* Machine_StringBuffer_create() {
  Machine_ClassType* ty = Machine_StringBuffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_StringBuffer* self = (Machine_StringBuffer *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_StringBuffer_appendBytes(Machine_StringBuffer* self, const char* p, size_t n) {
  if (n == 0) {
    return;
  }
  size_t fc = self->c - self->s;
  if (fc < n) {
    size_t ac = n - fc; // additional capacity
    char *p = realloc(self->p, self->c + ac);
    if (!p) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->p = p;
    self->c = self->c + ac;
  }
  memcpy(self->p + self->s, p, n);
  self->s += n;
}

void Machine_StringBuffer_clear(Machine_StringBuffer* self) {
  self->s = 0;
}

Machine_String *Machine_StringBuffer_toString(Machine_StringBuffer* self) {
  return Machine_String_create(self->p, self->s);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(MACHINE_WITH_LOG) && 1 == MACHINE_WITH_LOG

#include <stdio.h>
#include <stdarg.h>

void Machine_log(int flags, const char* file, int line, const char* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  fprintf(stdout, "%s:%d: ", __FILE__, __LINE__);
  vfprintf(stdout, format, arguments);
  va_end(arguments);
}

#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Machine_PointerArray_MaximalCapacity SIZE_MAX / sizeof(void *)

struct Machine_PointerArray {
  void** elements;
  size_t size, capacity;
};

static void Machine_PointerArray_visit(Machine_PointerArray* self) {
  if (self->elements) {
    for (size_t i = 0, n = self->size; i < n; ++i) {
      void *element = self->elements[i];
      if (element) {
        Machine_visit(element);
      }
    }
  }
}

static void Machine_PointerArray_construct(Machine_PointerArray* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->elements = NULL;
  self->size = 0;
  self->capacity = 0;
}

static void Machine_PointerArray_destruct(Machine_PointerArray* self) {
  if (self->elements) {
    free(self->elements);
    self->elements = NULL;
  }
}

Machine_ClassType* Machine_PointerArray_getClassType() {
  return
    Machine_createClassType
      (
        NULL,
        sizeof(Machine_PointerArray),
        (Machine_ClassObjectVisitCallback*)&Machine_PointerArray_visit,
        (Machine_ClassObjectConstructCallback*)&Machine_PointerArray_construct,
        (Machine_ClassObjectDestructCallback*)&Machine_PointerArray_destruct
      );
}

Machine_PointerArray* Machine_PointerArray_create() {
  Machine_ClassType* ty = Machine_PointerArray_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_PointerArray* self = (Machine_PointerArray *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void *Machine_PointerArray_getAt(Machine_PointerArray* self, size_t index) {
  if (!self){
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return self->elements[index];
}

size_t Machine_PointerArray_getSize(Machine_PointerArray* self) {
  if (!self){
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  return self->size;
}

void Machine_PointerArray_prepend(Machine_PointerArray* self, void* pointer) {
  Machine_PointerArray_insert(self, 0, pointer);
}

void Machine_PointerArray_append(Machine_PointerArray* self, void* pointer) {
  if (!self) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_PointerArray_insert(self, self->size, pointer);
}

void Machine_PointerArray_insert(Machine_PointerArray* self, size_t index, void *pointer) {
  if (!self) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if ((self->capacity - self->size) == 0) {
    if (self->capacity == Machine_PointerArray_MaximalCapacity) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    size_t newCapacity = self->capacity + 1;
    void *newElements = realloc(self->elements, sizeof(void*) * newCapacity);
    if (!newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    memmove(self->elements + index + 1, self->elements + index + 0, sizeof(void *) * (self->size - index));
  }
  self->elements[index] = pointer;
  self->size++;
}
