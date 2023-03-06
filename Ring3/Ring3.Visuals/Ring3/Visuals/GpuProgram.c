/// @file Ring3/Visuals/GpuProgram.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/GpuProgram.h"
#undef RING3_VISUALS_PRIVATE

static void
Ring3_GpuProgram_visit
  (
    Ring3_GpuProgram* self
  );

static void
Ring3_GpuProgram_destruct
  (
    Ring3_GpuProgram* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_GpuProgram,
                         Machine_Object,
                         &Ring3_GpuProgram_visit,
                         &Ring3_GpuProgram_construct,
                         &Ring3_GpuProgram_destruct,
                         NULL,
                         NULL)

static void
Ring3_GpuProgram_visit
  (
    Ring3_GpuProgram* self
  )
{/*Intentionally empty.*/}

static void
Ring3_GpuProgram_destruct
  (
    Ring3_GpuProgram* self
  )
{/*Intentionally empty.*/}

void
Ring3_GpuProgram_construct
  (
    Ring3_GpuProgram* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_GpuProgram_getType());
}

Ring1_NoDiscardReturn() int64_t
Ring3_GpuProgram_getNumberOfInputs
  (
    Ring3_GpuProgram const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_GpuProgram, getNumberOfInputs); }

Ring1_NoDiscardReturn() Ring3_GpuProgramInputDescriptor*
Ring3_GpuProgram_getInputAt
  (
    Ring3_GpuProgram const* self,
    int64_t index
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_GpuProgram, getInputAt, index); }

Ring2_Boolean
Ring3_GpuProgram_addUpdateInput
  (
    Ring3_GpuProgram* self,
    Ring2_String* name,
    Ring3_GpuProgramInputType type,
    Ring3_GpuProgramInputKind kind
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_GpuProgram, addUpdateInput, name, type, kind); }
