#if !defined(MACHINE_RUNTIME_TYPE_MODULE_H_INCLUDED)
#define MACHINE_RUNTIME_TYPE_MODULE_H_INCLUDED

#include "Runtime/Type.h"

/// @brief Type flags. See Machine_Type for more information.
#define Machine_TypeFlags_Class (1)

/// @brief Type flags. See Machine_Type for more information.
#define Machine_TypeFlags_Enumeration (2)

/// @brief Type flags. See Machine_Type for more information.
#define Machine_TypeFlags_Interface (4)

/// @brief Type flags. See Machine_Type for more infomration.
#define Machine_TypeFlags_Initialized (8)

void _Type_visit(Machine_Type* self);

void _Type_finalize(Machine_Type* self);

/// @brief Get if a type flag is set.
/// @param self A pointer to this type.
/// @param flag The type flag.
/// @return @a true if the type flag is set.
Ring1_Inline() bool _TypeFlag_isSet(Machine_Type const* self, uint32_t flag) {
  return flag == (self->flags & flag);
}

/// @brief Set a type flag.
/// @param self A pointer to this type.
/// @param flag The flag.
Ring1_Inline() void _TypeFlag_set(Machine_Type* self, uint32_t flag) {
  self->flags |= flag;
}

#endif // MACHINE_RUNTIME_TYPE_MODULE_H_INCLUDED
