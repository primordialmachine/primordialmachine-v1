/// @file Ring3/Visuals/GpuProgram.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAM_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAM_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgram.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include "Ring3/Visuals/GpuProgramInputKind.h"
#include "Ring3/Visuals/GpuProgramInputType.h"
typedef struct Ring3_GpuProgramInputDescriptor Ring3_GpuProgramInputDescriptor;

/// @brief A GPU program.
MACHINE_DECLARE_CLASSTYPE(Ring3_GpuProgram)

struct Ring3_GpuProgram_Class {
  Machine_Object_Class parent;
  
  Ring1_NoDiscardReturn() int64_t
  (*getNumberOfInputs)
    (
      Ring3_GpuProgram const* self
    );

  Ring1_NoDiscardReturn() Ring3_GpuProgramInputDescriptor*
  (*getInputAt)
    (
      Ring3_GpuProgram const* self,
      int64_t index
    );

  Ring2_Boolean
  (*addUpdateInput)
    (
      Ring3_GpuProgram* self,
      Ring2_String* name,
      Ring3_GpuProgramInputType type,
      Ring3_GpuProgramInputKind kind
    );
};

struct Ring3_GpuProgram {
  Machine_Object parent;
};

void
Ring3_GpuProgram_construct
  (
    Ring3_GpuProgram* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the number of inputs to this shader program.
/// @param self This shader program.
/// @return The number of inputs.
Ring1_NoDiscardReturn() int64_t
Ring3_GpuProgram_getNumberOfInputs
  (
    Ring3_GpuProgram const* self
  );

/// @brief Get the input to this shader program at the specified index.
/// @param self This shader program.
/// @param index The index.
/// @return The input.
Ring1_NoDiscardReturn() Ring3_GpuProgramInputDescriptor*
Ring3_GpuProgram_getInputAt
  (
    Ring3_GpuProgram const* self,
    int64_t index
  );

/// @brief Add/modify an input to this shader program.
/// @param self This shader program.
/// @param name The name of the input.
/// @param type The type of the input.
/// @param kind The kind of the input.
/// @return @a true if an existing input was modified, @a false if a new input was added.
Ring2_Boolean
Ring3_GpuProgram_addUpdateInput
  (
    Ring3_GpuProgram* self,
    Ring2_String* name,
    Ring3_GpuProgramInputType type,
    Ring3_GpuProgramInputKind kind
  );

#endif // RING3_VISUALS_GPUPROGRAM_H_INCLUDED
