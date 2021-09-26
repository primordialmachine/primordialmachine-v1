#include "./../GL/Buffer.h"



#include <malloc.h>
#include <string.h>



static void Machine_GL_VideoBuffer_destruct(Machine_GL_VideoBuffer* self) {
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GL_VideoBuffer, Machine_VideoBuffer, NULL, &Machine_GL_VideoBuffer_construct, &Machine_GL_VideoBuffer_destruct)

static void Machine_GL_VideoBuffer_setDataImpl(Machine_GL_VideoBuffer* self, size_t n, void const* p) {
  void* t = realloc(((Machine_VideoBuffer*)self)->p, n * sizeof(uint8_t));
  if (!t) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  ((Machine_VideoBuffer*)self)->p = t;
  memcpy(((Machine_VideoBuffer*)self)->p, p, n * sizeof(uint8_t));
  ((Machine_VideoBuffer*)self)->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, ((Machine_VideoBuffer*)self)->n * sizeof(uint8_t), ((Machine_VideoBuffer*)self)->p, GL_STATIC_DRAW);
}

void const* Machine_GL_VideoBuffer_getIdImpl(Machine_GL_VideoBuffer const* self) {
  return &(self->id);
}

void Machine_GL_VideoBuffer_construct(Machine_GL_VideoBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_VideoBuffer_construct((Machine_VideoBuffer*)self, numberOfArguments, arguments);
  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(uint8_t), ((Machine_VideoBuffer *)self)->p, GL_STATIC_DRAW);
  ((Machine_VideoBuffer *)self)->setData = (void (*)(Machine_VideoBuffer*, size_t, void const *))& Machine_GL_VideoBuffer_setDataImpl;
  ((Machine_VideoBuffer *)self)->getId = (void *(*)(const Machine_VideoBuffer*)) & Machine_GL_VideoBuffer_getIdImpl;
  Machine_setClassType((Machine_Object*)self, Machine_GL_VideoBuffer_getClassType());
}

Machine_GL_VideoBuffer* Machine_GL_VideoBuffer_create() {
  Machine_ClassType* ty = Machine_GL_VideoBuffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GL_VideoBuffer* self = (Machine_GL_VideoBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
