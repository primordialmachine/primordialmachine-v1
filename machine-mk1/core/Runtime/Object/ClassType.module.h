#if !defined(MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Object/ClassType.h"

typedef struct Machine_InterfaceImplementation {
  Machine_InterfaceType* interfaceType;
  Machine_InterfaceConstructCallback* constructInterface;
} Machine_InterfaceImplementation;

typedef struct Machine_InterfaceDispatchNode {
  Machine_InterfaceDispatch* dispatch;
} Machine_InterfaceDispatchNode;

struct Machine_ClassType {
  Machine_Type __parent__;
  Machine_ClassType* parent;

  struct {
    size_t size;
    Machine_ClassObjectVisitCallback* visit;
    Machine_ClassObjectConstructCallback* construct;
    Machine_ClassObjectDestructCallback* destruct;
  } object;

  struct {
    size_t size;
    Machine_ClassConstructCallback* construct;
    void* data;
  } class;

  struct {
    /// @brief Pointer to a Machine_ImplementInterfacesCallback or a null pointer.
    Machine_ImplementInterfacesCallback* implementInterfaces;
    Machine_Eal_InlineArray implementations2;
    bool implementationsInitialized;
    Machine_Eal_InlineArray dispatches2;
    bool dispatchesInitialized;
  } interfaces;
};

/// @brief Get if this type is a sub-type of another type.
/// @param self A pointer to this type.
/// @param other A pointer to the other type.
/// @return @a true if this type is a sub-type of the other type, @a false otherwise.
bool Machine_ClassType_isSubTypeOf(Machine_ClassType const* self, Machine_ClassType const* other);

/// @brief Get if this type is a true sub-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true sub-type of the other other type, @a false otherwise.
bool Machine_ClassType_isTrueSubTypeOf(Machine_ClassType const* self,
                                       Machine_ClassType const* other);

/// @brief Get if this type is a super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a super-type of the other type, @a false otherwise.
static inline bool Machine_ClassType_isSuperTypeOf(Machine_ClassType const* self,
                                                   Machine_ClassType const* other) {
  return Machine_ClassType_isSubTypeOf(other, self);
}

/// @brief Get if this type is a true super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true super-type of the other type, @a false otherwise.
static inline bool Machine_ClassType_isTrueSuperTypeOf(Machine_ClassType const* self,
                                                       Machine_ClassType const* other) {
  return Machine_ClassType_isTrueSubTypeOf(other, self);
}

#endif // MACHINE_RUNTIME_OBJECT_CLASSTYPE_MODULE_H_INCLUDED
