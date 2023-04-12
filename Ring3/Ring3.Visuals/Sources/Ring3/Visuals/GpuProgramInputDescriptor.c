/// @file Ring3/Visuals/GpuProgramInputDescriptor.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/GpuProgramInputDescriptor.h"
#undef RING3_VISUALS_PRIVATE

static void
Ring3_GpuProgramInputDescriptor_visit
  (
    Ring3_GpuProgramInputDescriptor* self
  )
{
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
}

static void
Ring3_GpuProgramInputDescriptor_construct
  (
    Ring3_GpuProgramInputDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->name = Ring2_Value_getString(&arguments[0]);
  self->type = Ring2_Value_getInteger(&arguments[1]);
  self->kind = Ring2_Value_getInteger(&arguments[2]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_GpuProgramInputDescriptor_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_GpuProgramInputDescriptor,
                         Machine_Object,
                         &Ring3_GpuProgramInputDescriptor_visit,
                         &Ring3_GpuProgramInputDescriptor_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_GpuProgramInputDescriptor*
Ring3_GpuProgramInputDescriptor_create
  (
    Ring2_String* name,
    Ring3_GpuProgramInputType type,
    Ring3_GpuProgramInputKind kind
  )
{
  Machine_Type* ty = Ring3_GpuProgramInputDescriptor_getType();
  Ring2_Value arguments[3];
  Ring2_Value_setString(&arguments[0], name);
  Ring2_Value_setInteger(&arguments[1], type);
  Ring2_Value_setInteger(&arguments[2], kind);
  Ring3_GpuProgramInputDescriptor* self = (Ring3_GpuProgramInputDescriptor*)Machine_allocateClassObject(ty, 3, arguments);
  return self;
}
