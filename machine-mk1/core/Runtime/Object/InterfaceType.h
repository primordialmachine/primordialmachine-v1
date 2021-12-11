/// @file Runtime/Object/InterfaceType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_OBJECT_INTERFACETYPE_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_INTERFACETYPE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Type.h"
typedef struct Machine_Value Machine_Value;

/// C-level representation of an interface type.
/// This structure holds the following fields:
/// - extends
/// An array of pointers the interface type extends.
/// - size
/// The size, in Bytes, of the dispatch.
typedef struct Machine_InterfaceType Machine_InterfaceType;

/// @brief Base of all interface dispatch structs.
/// @example
/// @code
/// struct Machine_MyInterfaceDispatch {
///   Machine_InterfaceDispatch parent;
///   ...
/// };
/// @endcode
typedef struct Machine_InterfaceDispatch Machine_InterfaceDispatch;

struct Machine_InterfaceDispatch {
  /// @brief A pointer to an interface type. Must not be null.
  Machine_Type* type;
};

typedef struct Machine_CreateInterfaceTypeArgs {
  Machine_CreateTypeArgs createTypeArgs;

  /// @brief The size, in Bytes, of the dispatch.
  size_t size;

  /// @brief A pointer to the "add prerequisites" function if any, a null pointer otherwise.
  void (*addPrerequisites)(Machine_InterfaceType*);

} Machine_CreateInterfaceTypeArgs;

/// @brief Create an interface type.
/// @param args A pointer to a stack-allocated Machine_CreateInterfaceTypeArgs object.
/// @return A pointer to the interface type.
Machine_InterfaceType* Machine_createInterfaceType(Machine_CreateInterfaceTypeArgs* args);

/// @brief Make this interface type extend the specified type.
/// @param self This interface type.
/// @param extended The specified type. Must be an interface type.
/// @remark If @a extended is a already a super-type of @a self, this function does nothing and returns true.
/// @remark If @a extended is a already a sub-type of @a self, this function does nothing and returns false.
bool Machine_InterfaceType_extend(Machine_InterfaceType* self, Machine_Type* extended);

/// @brief Get if this type is a sub-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a sub-type of the other other type, @a false otherwise.
bool Machine_InterfaceType_isSubTypeOf(Machine_InterfaceType const* self,
                                       Machine_InterfaceType const* other);

/// @brief Get if this type is a true sub-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true sub-type of the other other type, @a false otherwise.
bool Machine_InterfaceType_isTrueSubTypeOf(Machine_InterfaceType const* self,
                                           Machine_InterfaceType const* other);

/// @brief Get if this type is a super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a super-type of the other type, @a false otherwise.
INLINE bool Machine_InterfaceType_isSuperTypeOf(Machine_InterfaceType const* self,
                                                Machine_InterfaceType const* other) {
  return Machine_InterfaceType_isSubTypeOf(other, self);
}

/// @brief Get if this type is a true super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true super-type of the other type, @a false otherwise.
INLINE bool Machine_InterfaceType_isTrueSuperTypeOf(Machine_InterfaceType const* self,
                                                    Machine_InterfaceType const* other) {
  return Machine_InterfaceType_isTrueSubTypeOf(other, self);
}

void Machine_InterfaceType_ensureInitialized(Machine_InterfaceType* self);

#define MACHINE_DECLARE_INTERFACETYPE(THIS_TYPE)                                                   \
  typedef struct THIS_TYPE THIS_TYPE;                                                              \
  typedef struct THIS_TYPE##_Dispatch THIS_TYPE##_Dispatch;                                        \
  Machine_InterfaceType* THIS_TYPE##_getType();

#define MACHINE_DEFINE_INTERFACETYPE(THIS_TYPE, ADD_PREREQUISITES)                                 \
                                                                                                   \
  static Machine_InterfaceType* g_##THIS_TYPE##_InterfaceType = NULL;                              \
                                                                                                   \
  static void THIS_TYPE##_onTypeDestroyed() {                                                      \
    g_##THIS_TYPE##_InterfaceType = NULL;                                                          \
  }                                                                                                \
                                                                                                   \
  Machine_InterfaceType* THIS_TYPE##_getType() {                                                   \
    if (!g_##THIS_TYPE##_InterfaceType) {                                                          \
      Machine_CreateInterfaceTypeArgs args = { \
        .createTypeArgs = { \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed, \
        }, \
        .addPrerequisites = (ADD_PREREQUISITES), \
        .size = sizeof(THIS_TYPE##_Dispatch), \
      };                                                  \
      g_##THIS_TYPE##_InterfaceType = Machine_createInterfaceType(&args);                          \
    }                                                                                              \
    return g_##THIS_TYPE##_InterfaceType;                                                          \
  }

#endif // MACHINE_RUNTIME_OBJECT_INTERFACETYPE_H_INCLUDED
