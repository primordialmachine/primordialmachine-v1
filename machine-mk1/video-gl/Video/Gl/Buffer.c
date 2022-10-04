/// @file Video/Gl/Buffer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Buffer.h"


#include "Ring1/Intrinsic.h"
#include "Ring1/Status.h"
#include <string.h>


static void Machine_Gl_VideoBuffer_constructClass(Machine_Gl_VideoBuffer_Class* self);

static void Machine_Gl_VideoBuffer_destruct(Machine_Gl_VideoBuffer* self) {
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_VideoBuffer, Machine_VideoBuffer, NULL,
                         &Machine_Gl_VideoBuffer_construct, &Machine_Gl_VideoBuffer_destruct,
                         &Machine_Gl_VideoBuffer_constructClass, NULL)

static void Machine_Gl_VideoBuffer_setDataImpl(Machine_Gl_VideoBuffer* self, size_t n, void const* p) {
  void* t = NULL;
  if (Ring1_Memory_reallocateArray(&t, ((Machine_VideoBuffer*)self)->p, n, sizeof(uint8_t))) {
    Ring2_jump();
  }
  ((Machine_VideoBuffer*)self)->p = t;
  Ring1_Memory_copyFast(((Machine_VideoBuffer*)self)->p, p, n * sizeof(uint8_t));
  ((Machine_VideoBuffer*)self)->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, ((Machine_VideoBuffer*)self)->n * sizeof(uint8_t), ((Machine_VideoBuffer*)self)->p, GL_STATIC_DRAW);
}

static void const* Machine_Gl_VideoBuffer_getIdImpl(Machine_Gl_VideoBuffer const* self) {
  return &(self->id);
}

static void Machine_Gl_VideoBuffer_constructClass(Machine_Gl_VideoBuffer_Class* self) {
  ((Machine_VideoBuffer_Class*)self)->setData = (void (*)(Machine_VideoBuffer*, size_t, void const*)) & Machine_Gl_VideoBuffer_setDataImpl;
  ((Machine_VideoBuffer_Class*)self)->getId = (void* (*)(Machine_VideoBuffer const*)) & Machine_Gl_VideoBuffer_getIdImpl;
}

void Machine_Gl_VideoBuffer_construct(Machine_Gl_VideoBuffer* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_VideoBuffer_construct((Machine_VideoBuffer*)self, numberOfArguments, arguments);
  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(uint8_t), ((Machine_VideoBuffer *)self)->p, GL_STATIC_DRAW);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_VideoBuffer_getType());
}

Machine_Gl_VideoBuffer* Machine_Gl_VideoBuffer_create() {
  Machine_ClassType* ty = Machine_Gl_VideoBuffer_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Gl_VideoBuffer* self = (Machine_Gl_VideoBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
