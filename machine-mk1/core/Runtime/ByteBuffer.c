#define MACHINE_RUNTIME_PRIVATE (1)
#include "./Runtime/ByteBuffer.h"

#include <malloc.h>
#include <memory.h>

struct Machine_ByteBuffer {
  Machine_Object parent;
  char* p;
  size_t s; ///< The size.
  size_t c; ///< The capacity.
};

static void Machine_ByteBuffer_construct(Machine_ByteBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->p = NULL;
  self->s = 0;
  self->c = 0;
  Machine_setClassType((Machine_Object *)self, Machine_ByteBuffer_getClassType());
}

static void Machine_ByteBuffer_destruct(Machine_ByteBuffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_ByteBuffer)
MACHINE_DEFINE_CLASSTYPE_EX(Machine_ByteBuffer, Machine_Object, NULL, &Machine_ByteBuffer_construct, &Machine_ByteBuffer_destruct)

Machine_ByteBuffer* Machine_ByteBuffer_create() {
  Machine_ClassType* ty = Machine_ByteBuffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_ByteBuffer* self = (Machine_ByteBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_ByteBuffer_appendBytes(Machine_ByteBuffer* self, const char* p, size_t n) {
  Machine_ByteBuffer_insertBytesAt(self, self->s, p, n);
}

void Machine_ByteBuffer_prependBytes(Machine_ByteBuffer* self, const char* p, size_t n) {
  Machine_ByteBuffer_insertBytesAt(self, 0, p, n);
}

void Machine_ByteBuffer_insertBytesAt(Machine_ByteBuffer* self, size_t i, const char* p, size_t n) {
  if (n == 0) {
    return;
  }
  size_t fc = self->c - self->s;
  if (fc < n) {
    size_t ac = n - fc; // additional capacity
    char* p = realloc(self->p, self->c + ac);
    if (!p) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->p = p;
    self->c = self->c + ac;
  }
  if (i < n) {
    memmove(self->p + i + n, self->p + i, self->s - i);
  }
  memcpy(self->p + i, p, n);
  self->s += n;
}

void Machine_ByteBuffer_clear(Machine_ByteBuffer* self) {
  self->s = 0;
}

const char* Machine_ByteBuffer_getBytes(const Machine_ByteBuffer* self) {
  return self->p;
}

size_t Machine_ByteBuffer_getNumberOfBytes(const Machine_ByteBuffer* self) {
  return self->s;
}
