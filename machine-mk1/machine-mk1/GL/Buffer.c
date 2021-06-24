#include "./../GL/Buffer.h"



#include <malloc.h>
#include <string.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GL_Uint8Buffer_destruct(Machine_GL_Uint8Buffer* self) {
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GL_Uint8Buffer, Machine_Uint8Buffer, NULL, &Machine_GL_Uint8Buffer_construct, &Machine_GL_Uint8Buffer_destruct)

static void Machine_GL_Uint8Buffer_setDataImpl(Machine_GL_Uint8Buffer* self, size_t n, void const* p) {
  uint8_t* t = realloc(((Machine_VideoBuffer*)self)->p, n * sizeof(uint8_t));
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

void const* Machine_GL_Uint8Buffer_getIdImpl(Machine_GL_Uint8Buffer const* self) {
  return &(self->id);
}

void Machine_GL_Uint8Buffer_construct(Machine_GL_Uint8Buffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Uint8Buffer_construct((Machine_Uint8Buffer*)self, numberOfArguments, arguments);
  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(uint8_t), ((Machine_VideoBuffer *)self)->p, GL_STATIC_DRAW);
  ((Machine_VideoBuffer *)self)->setData = (void (*)(Machine_VideoBuffer*, size_t, void const *))&Machine_GL_Uint8Buffer_setDataImpl;
  ((Machine_VideoBuffer *)self)->getId = (void *(*)(const Machine_VideoBuffer*)) &Machine_GL_Uint8Buffer_getIdImpl;
  Machine_setClassType((Machine_Object*)self, Machine_GL_Uint8Buffer_getClassType());
}

Machine_GL_Uint8Buffer* Machine_GL_Uint8Buffer_create() {
  Machine_ClassType* ty = Machine_GL_Uint8Buffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GL_Uint8Buffer* self = (Machine_GL_Uint8Buffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_GL_FloatBuffer_destruct(Machine_GL_FloatBuffer* self) {
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GL_FloatBuffer, Machine_FloatBuffer, NULL, &Machine_GL_FloatBuffer_construct, &Machine_GL_FloatBuffer_destruct)

static void Machine_GL_FloatBuffer_setDataImpl(Machine_GL_FloatBuffer* self, size_t n, void const* p) {
  void* t = realloc(((Machine_VideoBuffer*)self)->p, n * sizeof(float));
  if (!t) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  ((Machine_VideoBuffer*)self)->p = t;
  memcpy(((Machine_VideoBuffer*)self)->p, p, n * sizeof(float));
  ((Machine_VideoBuffer*)self)->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, ((Machine_VideoBuffer*)self)->n * sizeof(float), ((Machine_VideoBuffer*)self)->p, GL_STATIC_DRAW);
}

void const* Machine_GL_FloatBuffer_getIdImpl(Machine_GL_FloatBuffer const* self) {
  return &(self->id);
}

void Machine_GL_FloatBuffer_construct(Machine_GL_FloatBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_FloatBuffer_construct((Machine_FloatBuffer*)self, numberOfArguments, arguments);
  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(float), ((Machine_VideoBuffer*)self)->p, GL_STATIC_DRAW);
  ((Machine_VideoBuffer*)self)->setData = (void (*)(Machine_VideoBuffer *, size_t, void const *))&Machine_GL_FloatBuffer_setDataImpl;
  ((Machine_VideoBuffer*)self)->getId = (void *(*)(const Machine_VideoBuffer *))&Machine_GL_FloatBuffer_getIdImpl;
  Machine_setClassType((Machine_Object*)self, Machine_GL_FloatBuffer_getClassType());
}

Machine_GL_FloatBuffer* Machine_GL_FloatBuffer_create() {
  Machine_ClassType* ty = Machine_GL_FloatBuffer_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GL_FloatBuffer* self = (Machine_GL_FloatBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
