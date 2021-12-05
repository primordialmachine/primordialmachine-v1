/// @file Video/Buffer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Buffer.h"



#include <string.h>



static void Machine_VideoBuffer_destruct(Machine_VideoBuffer* self) {
  if (self->p) {
    Machine_Eal_Memory_deallocate(self->p);
    self->p = NULL;
  }
}

static const void* Machine_VideoBuffer_getDataImpl(Machine_VideoBuffer const* self) {
  return self->p;
}

static size_t Machine_VideoBuffer_getSizeImpl(Machine_VideoBuffer const* self) {
  return self->n;
}

static void Machine_VideoBuffer_constructClass(Machine_VideoBuffer_Class* self) {
  self->getData = &Machine_VideoBuffer_getDataImpl;
  self->getSize = &Machine_VideoBuffer_getSizeImpl;
}

void Machine_VideoBuffer_construct(Machine_VideoBuffer* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  self->p = Machine_Eal_Memory_allocate(1);
  if (!self->p) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->n = 0;

  Machine_setClassType((Machine_Object*)self, Machine_VideoBuffer_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_VideoBuffer, Machine_Object, NULL, &Machine_VideoBuffer_construct,
                         &Machine_VideoBuffer_destruct, &Machine_VideoBuffer_constructClass, NULL)

void Machine_VideoBuffer_setData(Machine_VideoBuffer* self, size_t n, void const* p) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoBuffer, setData, n, p);
}

void const* Machine_VideoBuffer_getData(Machine_VideoBuffer const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoBuffer, getData);
}

size_t Machine_VideoBuffer_getSize(Machine_VideoBuffer const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoBuffer, getSize);
}

void const* Machine_VideoBuffer_getId(Machine_VideoBuffer const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoBuffer, getId);
}
