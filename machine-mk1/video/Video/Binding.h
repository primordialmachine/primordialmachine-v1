/// @file Video/Binding.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_BINDING_H_INCLUDED)
#define MACHINE_VIDEO_BINDING_H_INCLUDED

#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif
typedef struct Machine_ShaderProgram Machine_ShaderProgram;
typedef struct Machine_VertexDescriptor Machine_VertexDescriptor;
typedef struct Machine_VideoBuffer Machine_VideoBuffer;
#include "_Math.h"

/// @brief A vertex program has variable input variables and constant input variables.
/// These variables must be bound before a program can be used.
/// Any variable input variable must be bound to a vertex element of the vertex the program is
/// invoked for. Any constant input variable must be bound to a constant. A Machine_VideoBinding
/// represents such a binding.
MACHINE_DECLARE_CLASSTYPE(Machine_Binding_Node)

struct Machine_Binding_Node_Class {
  Machine_Object_Class parent;
};

struct Machine_Binding_Node {
  Machine_Object parent;
  Machine_Binding_Node* next;
  bool isVariable;
  Machine_String* name;
  Machine_Value value;
};

Machine_Binding_Node* Machine_Binding_Node_create(Machine_String* name, Machine_Boolean isVariable,
                                                  Machine_Value const* value);

Machine_Binding_Node* Machine_Binding_Node_createVariable(Machine_String* name,
                                                          Machine_Value const* value);

Machine_Binding_Node* Machine_Binding_Node_createConstant(Machine_String* name,
                                                          Machine_Value const* value);

/// @brief Binding between shader program inputs and vertex elements.
/// Not EVERY vertex element needs to have a corresponding shader program input.
/// However EVERY shader program input needs to have a corresponding vertex element.
MACHINE_DECLARE_CLASSTYPE(Machine_Binding)

struct Machine_Binding_Class {
  Machine_Object_Class parent;
  Machine_Boolean (*setVariableBinding)(Machine_Binding* self, Machine_String* name, size_t index);
  size_t (*getVariableBinding)(Machine_Binding const* self, Machine_String* name);
  void (*bindMatrix4)(Machine_Binding* self, Machine_String* name,
                      Machine_Math_Matrix4 const* value);
  void (*bindVector2)(Machine_Binding* self, Machine_String* name,
                      Machine_Math_Vector2 const* value);
  void (*bindVector3)(Machine_Binding* self, Machine_String* name,
                      Machine_Math_Vector3 const* value);
  void (*bindVector4)(Machine_Binding* self, Machine_String* name,
                      Machine_Math_Vector4 const* value);
  void (*bindSampler)(Machine_Binding* self, Machine_String* name, size_t const value);
  void (*activate)(Machine_Binding* self);
  void (*addUpdateConstant)(Machine_Binding* self, Machine_String* name,
                            Machine_Value const* value);
};

struct Machine_Binding {
  Machine_Object parent;
  Machine_Binding_Node* nodes;
  Machine_ShaderProgram* program;
  Machine_VertexDescriptor* vertexDescriptor;
  Machine_VideoBuffer* buffer;
  bool dirty;
};

void Machine_Binding_construct(Machine_Binding* self, size_t numberOfArguments,
                               Machine_Value const* arguments);

/// @brief Bind the vertex element of the specified index to the input of the specified name.
/// @param self This binding.
/// @param name The name of the input.
/// @param index The index of the vertex element.
/// @return The index of the vertex element.
Machine_Boolean Machine_Binding_setVariableBinding(Machine_Binding* self, Machine_String* name,
                                                   size_t index);

/// @brief Get the index of the vertex element bound to the input of the specified name.
/// @param self This binding.
/// @param name The name of the input.
/// @return The index of the vertex element.
size_t Machine_Binding_getVariableBinding(Machine_Binding const* self, Machine_String* name);

/// @brief This activates the program and writes the current constant variable and variable variable
/// values.
/// @param self This binding.
void Machine_Binding_activate(Machine_Binding* self);

/// @brief Bind a matrix to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindMatrix4(Machine_Binding* self, Machine_String* name,
                                 Machine_Math_Matrix4 const* value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector2(Machine_Binding* self, Machine_String* name,
                                 Machine_Math_Vector2 const* value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector3(Machine_Binding* self, Machine_String* name,
                                 Machine_Math_Vector3 const* value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector4(Machine_Binding* self, Machine_String* name,
                                 Machine_Math_Vector4 const* value);

/// @brief Bind a texture unit index to a texture sampler.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
void Machine_Binding_bindSampler(Machine_Binding* self, Machine_String* name, size_t const value);

void Machine_Binding_addUpdateConstant(Machine_Binding* self, Machine_String* name,
                                       Machine_Value const* value);

#endif // MACHINE_VIDEO_BINDING_H_INCLUDED
