/// @file Video/ShaderProgram.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED)
#define MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED

#include "Video/_header.i"

/// @brief A shader program.
MACHINE_DECLARE_CLASSTYPE(Machine_ShaderProgram)

struct Machine_ShaderProgram_Class {
  Machine_Object_Class parent;
  size_t (*getNumberOfInputs)(Machine_ShaderProgram const* self);
  Ring3_GpuProgramInputDescriptor* (*getInputAt)(Machine_ShaderProgram const* self, size_t index);
  Ring2_Boolean (*addUpdateInput)(Machine_ShaderProgram* self, Ring2_String* name,
                                  Ring3_GpuProgramInputType type, Ring3_GpuProgramInputKind kind);
};

struct Machine_ShaderProgram {
  Machine_Object parent;
};

void Machine_ShaderProgram_construct(Machine_ShaderProgram* self, size_t numberOfArguments,
                                     Ring2_Value const* arguments);

/// @brief Get the number of inputs to this shader program.
/// @param self This shader program.
/// @return The number of inputs.
size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram const* self);

/// @brief Get the input to this shader program at the specified index.
/// @param self This shader program.
/// @param index The index.
/// @return The input.
Ring3_GpuProgramInputDescriptor*
Machine_ShaderProgram_getInputAt
  (
    Machine_ShaderProgram const* self,
    size_t index
  );

/// @brief Add/modify an input to this shader program.
/// @param self This shader program.
/// @param name The name of the input.
/// @param type The type of the input.
/// @param kind The kind of the input.
/// @return @a true if an existing input was modified, @a false if a new input was added.
Ring2_Boolean Machine_ShaderProgram_addUpdateInput(Machine_ShaderProgram* self,
                                                   Ring2_String* name,
                                                   Ring3_GpuProgramInputType type,
                                                   Ring3_GpuProgramInputKind kind);

#endif // MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED
