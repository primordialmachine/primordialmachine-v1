#if !defined(MACHINE_RUNTIME_OBJECT_INTERFACETYPE_MODULE_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_INTERFACETYPE_MODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Object/InterfaceType.module.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring1/InlineArray.h"
#include "Runtime/Object/InterfaceType.h"

/// @brief Flags set if the prerequisites were added.
#define Machine_InterfaceTypeFlags_PrerequisitesAdded (1<<1)

/// @brief Flag set if the prerequisites were initialized.
#define Machine_InterfaceTypeFlags_PrerequisitesInitialized (1<<2)

struct Machine_InterfaceType {
  Machine_Type parent_;

  uint8_t flags;

  bool extendsArrayInitialized;
  Ring1_InlineArray extends;
  
  /// @brief The size, in Bytes, of the interface dispatch.
  size_t size;

  /// @brief A pointer to the "add prerequisites" function if any, a null pointer otherwise.
  void (*addPrerequisites)(Machine_InterfaceType*);
};

Ring1_Inline() bool Machine_InterfaceType_hasFlag(Machine_InterfaceType const* self, uint8_t flag) {
  return flag == (self->flags & flag);
}

Ring1_Inline() void Machine_InterfaceType_addFlag(Machine_InterfaceType* self, uint8_t flag) {
  self->flags |= flag;
}

#endif // MACHINE_RUNTIME_OBJECT_INTERFACETYPE_MODULE_H_INCLUDED
