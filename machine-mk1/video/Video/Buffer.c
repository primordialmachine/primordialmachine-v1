#include "./../Video/Buffer.h"



#include <malloc.h>
#include <string.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_VideoBuffer_destruct(Machine_VideoBuffer* self) {
  if (self->p) {
    free(self->p);
    self->p = NULL;
  }
}

static const void* Machine_VideoBuffer_getDataImpl(const Machine_VideoBuffer* self) {
  return self->p;
}

static size_t Machine_VideoBuffer_getSizeImpl(const Machine_VideoBuffer* self) {
  return self->n;
}

void Machine_VideoBuffer_construct(Machine_VideoBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  self->p = malloc(1);
  if (!self->p) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->n = 0;

  self->getData = &Machine_VideoBuffer_getDataImpl;
  self->getSize = &Machine_VideoBuffer_getSizeImpl;

  Machine_setClassType((Machine_Object*)self, Machine_VideoBuffer_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_VideoBuffer, Machine_Object, NULL, &Machine_VideoBuffer_construct, &Machine_VideoBuffer_destruct)

void Machine_VideoBuffer_setData(Machine_VideoBuffer* self, size_t n, void const* p) {
  self->setData(self, n, p);
}

void const* Machine_VideoBuffer_getData(Machine_VideoBuffer const* self) {
  return self->getData(self);
}

size_t Machine_VideoBuffer_getSize(Machine_VideoBuffer const* self) {
  return self->getSize(self);
}

void const* Machine_VideoBuffer_getId(Machine_VideoBuffer const* self) {
  return self->getId(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Uint8Buffer_destruct(Machine_Uint8Buffer* self)
{}

void Machine_Uint8Buffer_construct(Machine_Uint8Buffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_VideoBuffer_construct((Machine_VideoBuffer*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_Uint8Buffer_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Uint8Buffer, Machine_VideoBuffer, NULL, &Machine_Uint8Buffer_construct, &Machine_Uint8Buffer_destruct)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_FloatBuffer_destruct(Machine_FloatBuffer* self)
{}

void Machine_FloatBuffer_construct(Machine_FloatBuffer* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_VideoBuffer_construct((Machine_VideoBuffer*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_FloatBuffer_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_FloatBuffer, Machine_VideoBuffer, NULL, &Machine_FloatBuffer_construct, &Machine_FloatBuffer_destruct)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
