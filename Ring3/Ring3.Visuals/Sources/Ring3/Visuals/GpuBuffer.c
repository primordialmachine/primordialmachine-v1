/// @file Ring3/Visuals/Buffer.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/GpuBuffer.h"
#undef RING3_VISUALS_PRIVATE


#include "Ring1/All/_Include.h"


void
Ring3_GpuBuffer_construct
  (
    Ring3_GpuBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_GpuBuffer_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_GpuBuffer,
                         Machine_Object,
                         NULL,
                         &Ring3_GpuBuffer_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_GpuBuffer_setData
  (
    Ring3_GpuBuffer* self,
    size_t n,
    void const* p
  )
{
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_GpuBuffer, setData, n, p);
}

void const*
Ring3_GpuBuffer_getData
  (
    Ring3_GpuBuffer const* self
  )
{
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_GpuBuffer, getData);
}

size_t
Ring3_GpuBuffer_getSize
  (
    Ring3_GpuBuffer const* self
  )
{
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_GpuBuffer, getSize);
}

void const*
Ring3_GpuBuffer_getId
  (
    Ring3_GpuBuffer const* self
  )
{
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_GpuBuffer, getId);
}
