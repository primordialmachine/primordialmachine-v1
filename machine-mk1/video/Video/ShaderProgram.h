/// @file Video/ShaderProgram.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED)
#define MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED



#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif
#include "./../Video/ProgramInput.h"
#include "./../Video/ProgramInputKind.h"
#include "./../Video/ProgramInputType.h"



/// @brief A shader program.
MACHINE_DECLARE_CLASSTYPE(Machine_ShaderProgram)

struct Machine_ShaderProgram_Class {
  Machine_Object_Class parent;
  size_t(*getNumberOfInputs)(Machine_ShaderProgram const* self);
  Machine_ProgramInput* (*getInputAt)(Machine_ShaderProgram const* self, size_t index);
  Machine_Boolean(*addUpdateInput)(Machine_ShaderProgram* self, Machine_String* name, Machine_ProgramInputType type, Machine_ProgramInputKind kind);
};

struct Machine_ShaderProgram {
  Machine_Object parent;
};

void Machine_ShaderProgram_construct(Machine_ShaderProgram* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Get the number of inputs to this shader program.
/// @param self This shader program.
/// @return The number of inputs.
size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram const* self);

/// @brief Get the input to this shader program at the specified index.
/// @param self This shader program.
/// @param index The index.
/// @return The input.
Machine_ProgramInput* Machine_ShaderProgram_getInputAt(Machine_ShaderProgram const* self, size_t index);

/// @brief Add/modify an input to this shader program.
/// @param self This shader program.
/// @param name The name of the input.
/// @param type The type of the input.
/// @param kind The kind of the input.
/// @return @a true if an existing input was modified, @a false if a new input was added.
Machine_Boolean Machine_ShaderProgram_addUpdateInput(Machine_ShaderProgram* self, Machine_String* name, Machine_ProgramInputType type, Machine_ProgramInputKind kind);



#endif // MACHINE_VIDEO_SHADERPROGRAM_H_INCLUDED
