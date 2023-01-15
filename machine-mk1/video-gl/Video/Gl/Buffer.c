/// @file Video/Gl/Buffer.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Buffer.h"


#include "Ring1/All/_Include.h"


static size_t
Machine_Gl_VideoBuffer_getSizeImpl
  (
    Machine_Gl_VideoBuffer const* self
  );

static const void*
Machine_Gl_VideoBuffer_getDataImpl
  (
    Machine_Gl_VideoBuffer const* self
  );

static void
Machine_Gl_VideoBuffer_setDataImpl
  (
    Machine_Gl_VideoBuffer* self,
    size_t n,
    void const* p
  );

static void const*
Machine_Gl_VideoBuffer_getIdImpl
  (
    Machine_Gl_VideoBuffer const* self
  );

static void
Machine_Gl_VideoBuffer_destruct
  (
    Machine_Gl_VideoBuffer* self
  );

static void
Machine_Gl_VideoBuffer_constructClass
  (
    Machine_Gl_VideoBuffer_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_VideoBuffer,
                         Ring3_GpuBuffer,
                         NULL,
                         &Machine_Gl_VideoBuffer_construct,
                         &Machine_Gl_VideoBuffer_destruct,
                         &Machine_Gl_VideoBuffer_constructClass,
                         NULL)

static size_t
Machine_Gl_VideoBuffer_getSizeImpl
  (
    Machine_Gl_VideoBuffer const* self
  )
{
  return self->n;
}

static const void*
Machine_Gl_VideoBuffer_getDataImpl
  (
    Machine_Gl_VideoBuffer const* self
  )
{
  return self->p;
}

static void
Machine_Gl_VideoBuffer_setDataImpl
  (
    Machine_Gl_VideoBuffer* self,
    size_t n,
    void const* p
  )
{
  void* t = NULL;
  if (Ring1_Memory_reallocateArray(&t, self->p, n, sizeof(uint8_t))) {
    Ring2_jump();
  }
  self->p = t;
  Ring1_Memory_copyFast(self->p, p, n * sizeof(uint8_t));
  self->n = n;

  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, self->n * sizeof(uint8_t), self->p, GL_STATIC_DRAW);
}

static void const*
Machine_Gl_VideoBuffer_getIdImpl
  (
    Machine_Gl_VideoBuffer const* self
  )
{ return &(self->id); }

static void
Machine_Gl_VideoBuffer_destruct
  (
    Machine_Gl_VideoBuffer* self
  )
{
  if (self->id) {
    glDeleteBuffers(1, &self->id);
    self->id = 0;
  }
  if (self->p) {
    Ring1_Memory_deallocate(self->p);
    self->p = NULL;
  }
}

static void
Machine_Gl_VideoBuffer_constructClass
  (
    Machine_Gl_VideoBuffer_Class* self
  )
{
  ((Ring3_GpuBuffer_Class*)self)->getSize = (size_t(*)(Ring3_GpuBuffer const*)) & Machine_Gl_VideoBuffer_getSizeImpl;
  ((Ring3_GpuBuffer_Class*)self)->getData = (void const* (*)(Ring3_GpuBuffer const*)) & Machine_Gl_VideoBuffer_getDataImpl;
  ((Ring3_GpuBuffer_Class*)self)->setData = (void (*)(Ring3_GpuBuffer*, size_t, void const*)) & Machine_Gl_VideoBuffer_setDataImpl;
  ((Ring3_GpuBuffer_Class*)self)->getId = (void* (*)(Ring3_GpuBuffer const*)) & Machine_Gl_VideoBuffer_getIdImpl;
}

void
Machine_Gl_VideoBuffer_construct
  (
    Machine_Gl_VideoBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_GpuBuffer_construct((Ring3_GpuBuffer*)self, numberOfArguments, arguments);
  self->p = NULL;
  if (Ring1_Memory_allocate(&self->p, 1)) {
    Ring2_jump();
  }
  self->n = 0;
  glGenBuffers(1, &self->id);
  glBindBuffer(GL_ARRAY_BUFFER, self->id);
  glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(uint8_t), self->p, GL_STATIC_DRAW);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_VideoBuffer_getType());
}

Machine_Gl_VideoBuffer*
Machine_Gl_VideoBuffer_create
  (
  )
{
  Machine_ClassType* ty = Machine_Gl_VideoBuffer_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Gl_VideoBuffer* self = (Machine_Gl_VideoBuffer*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
