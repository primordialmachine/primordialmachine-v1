/// @file Ring3/Visuals/GpuProgramBinding.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GPUPROGRAMBINDING_H_INCLUDED)
#define RING3_VISUALS_GPUPROGRAMBINDING_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/GpuProgramBinding.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Math/_Include.h"
typedef struct Ring3_GpuBuffer Ring3_GpuBuffer;
typedef struct Ring3_GpuProgram Ring3_GpuProgram;
typedef struct Ring3_VertexDescriptor Ring3_VertexDescriptor;

/// @brief
/// An enumeration of types of locations of a GPU program.
/// A GPU program writes data to a location or reads data from a location.
/// Locations are typed: Only data of a certain type can be written to/read from a location.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_GpuProgramLocationType)

enum Ring3_GpuProgramLocationType {
  Ring3_GpuProgramLocationType_Vector2Constant,
  Ring3_GpuProgramLocationType_Vector3Constant,
  Ring3_GpuProgramLocationType_Vector4Constant,

  Ring3_GpuProgramLocationType_Vector2Variable,
  Ring3_GpuProgramLocationType_Vector3Variable,
  Ring3_GpuProgramLocationType_Vector4Variable,

  Ring3_GpuProgramLocationType_Matrix4x4Constant,
  Ring3_GpuProgramLocationType_SamplerConstant,
};

/// @brief A vertex program has variable input variables and constant input variables.
/// These variables must be bound before a program can be used.
/// Any variable input variable must be bound to a vertex element of the vertex the program is
/// invoked for. Any constant input variable must be bound to a constant. A Machine_VideoBinding
/// represents such a binding.
MACHINE_DECLARE_CLASSTYPE(Ring3_Binding_Node)

struct Ring3_Binding_Node_Class {
  Machine_Object_Class parent;
};

struct Ring3_Binding_Node {
  Machine_Object parent;
  Ring3_Binding_Node* next;
  bool isVariable;
  Ring2_Value value;
  /// @brief The type of the constant/variable in the GPU program.
  Ring3_GpuProgramLocationType targetType;
  /// @brief The name of the constant/variable in the GPU program.
  Ring2_String* targetName;
};

Ring3_Binding_Node*
Ring3_Binding_Node_create
  (
    Ring2_String* targetName,
    Ring2_Boolean isVariable,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  );

Ring3_Binding_Node*
Ring3_Binding_Node_createVariable
  (
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  );

Ring3_Binding_Node*
Ring3_Binding_Node_createConstant
  (
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  );

/// @brief Binding between shader program inputs and vertex elements.
/// Not EVERY vertex element needs to have a corresponding shader program input.
/// However EVERY shader program input needs to have a corresponding vertex element.
MACHINE_DECLARE_CLASSTYPE(Ring3_Binding)

struct Ring3_Binding_Class {
  Machine_Object_Class parent;
  Ring2_Boolean (*setVariableBinding)(Ring3_Binding* self,
                                      Ring2_String* targetName,
                                      Ring3_GpuProgramLocationType targetType,
                                      size_t index);
  size_t (*getVariableBinding)(Ring3_Binding const* self, Ring2_String* targetName);
  void (*bindMatrix4)(Ring3_Binding* self, Ring2_String* name,
                      Ring3_Math_Matrix4x4f32 const* value);
  void (*bindVector2)(Ring3_Binding* self, Ring2_String* targetName,
                      Ring3_Math_Vector2f32 const* value);
  void (*bindVector3)(Ring3_Binding* self, Ring2_String* targetName,
                      Ring3_Math_Vector3f32 const* value);
  void (*bindVector4)(Ring3_Binding* self, Ring2_String* targetName,
                      Ring3_Math_Vector4f32 const* value);
  void (*bindSampler)(Ring3_Binding* self, Ring2_String* targetName, size_t const value);
  void (*activate)(Ring3_Binding* self);
  void (*addUpdateConstant)(Ring3_Binding* self,
                            Ring2_String* targetName,
                            Ring3_GpuProgramLocationType targetType,
                            Ring2_Value const* value);
};

struct Ring3_Binding {
  Machine_Object parent;
  Ring3_Binding_Node* nodes;
  Ring3_GpuProgram* program;
  Ring3_VertexDescriptor* vertexDescriptor;
  Ring3_GpuBuffer* buffer;
  bool dirty;
};

void
Ring3_Binding_construct
  (
    Ring3_Binding* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Bind the vertex element of the specified index to the input of the specified name.
/// @param self This binding.
/// @param targetName The name of the variable in the GPU program.
/// @param targetType The type of the variable in the GPU program.
/// @param index The index of the vertex element.
/// @return The index of the vertex element.
Ring2_Boolean
Ring3_Binding_setVariableBinding
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    size_t index
  );

/// @brief Get the index of the vertex element bound to the input of the specified name.
/// @param self This binding.
/// @param targetName The name of the input.
/// @return The index of the vertex element.
size_t
Ring3_Binding_getVariableBinding
  (
    Ring3_Binding const* self,
    Ring2_String* targetName
  );

/// @brief This activates the program and writes the current constant variable and variable variable
/// values.
/// @param self This binding.
void
Ring3_Binding_activate
  (
    Ring3_Binding* self
  );

/// @brief Bind a matrix to a constant.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param value The value.
/// @error The specified name does not denote a constant.
void
Ring3_Binding_bindMatrix4
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Matrix4x4f32 const* value
  );

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param value The value.
/// @error The specified name does not denote a constant.
void
Ring3_Binding_bindVector2
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector2f32 const* value
  );

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param value The value.
/// @error The specified name does not denote a constant.
void
Ring3_Binding_bindVector3
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector3f32 const* value
  );

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param value The value.
/// @error The specified name does not denote a constant.
void
Ring3_Binding_bindVector4
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector4f32 const* value
  );

/// @brief Bind a texture unit index to a texture sampler.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param value The value. The zero-based index of the texture unit.
void
Ring3_Binding_bindSampler
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    size_t const value
  );

/// @brief Bind the specified value to the specified constant.
/// Create the constant if it does not exist.
/// @param self This binding.
/// @param targetName The name of the constant in the GPU program.
/// @param targetType The type of the constant in the GPU program.
/// @param value The value.
void
Ring3_Binding_addUpdateConstant
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  );

#endif // RING3_VISUALS_GPUPROGRAMBINDING_H_INCLUDED
