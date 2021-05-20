#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/StringBuffer.h"


#include <malloc.h>
#include <memory.h>


struct Machine_StringBuffer {
  Machine_Object parent;
  char* p;
  size_t s; /**< The size. */
  size_t c; /**< The capacity.  */
};

static void Machine_StringBuffer_construct(Machine_StringBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->p = NULL;
  self->s = 0;
  self->c = 0;
  Machine_setClassType(self, Machine_StringBuffer_getClassType());
}

static void Machine_StringBuffer_destruct(Machine_StringBuffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_StringBuffer)
MACHINE_DEFINE_CLASSTYPE_EX(Machine_StringBuffer, Machine_Object, NULL, &Machine_StringBuffer_construct, &Machine_StringBuffer_destruct)

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
