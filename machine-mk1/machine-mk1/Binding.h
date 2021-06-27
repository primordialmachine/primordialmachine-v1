#if !defined(MACHINE_BINDING_H_INCLUDED)
#define MACHINE_BINDING_H_INCLUDED



#include "_Video.h"
#include "_Math.h"
#include <linmath.h>



/// @brief Binding between shader program inputs and vertex elements.
/// Not EVERY vertex element needs to have a corresponding shader program input.
/// However EVERY shader program input needs to have a corresponding vertex element.
MACHINE_DECLARE_CLASSTYPE(Machine_Binding)

Machine_Binding* Machine_Binding_create(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);

/// @brief Bind the vertex element of the specified index to the input of the specified name.
/// @param self This binding.
/// @param name The name of the input.
/// @param index The index of the vertex element.
/// @return The index of the vertex element.
bool Machine_Binding_setVariableBinding(Machine_Binding* self, Machine_String* name, size_t index);

/// @brief Get the index of the vertex element bound to the input of the specified name.
/// @param self This binding.
/// @param name The name of the input.
/// @return The index of the vertex element.
size_t Machine_Binding_getVariableBinding(Machine_Binding const* self, Machine_String* name);

void Machine_Binding_activate(Machine_Binding* self);

/// @brief Bind a matrix to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindMatrix4x4(Machine_Binding* self, Machine_String* name, const mat4x4 value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector2(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector2* value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector3(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector3* value);

/// @brief Bind a vector to a constant.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
/// @error The specified name does not denote a constant.
void Machine_Binding_bindVector4(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector4* value);

/// @brief Bind a texture unit index to a texture sampler.
/// @param self This binding.
/// @param name The name of the constant.
/// @param value The value.
void Machine_Binding_bindSampler(Machine_Binding* self, Machine_String* name, const size_t value);

#endif // MACHINE_BINDING_H_INCLUDED
