// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/InterfaceType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPESYSTEM_INTERFACETYPE_H_INCLUDED)
#define RING2_TYPESYSTEM_INTERFACETYPE_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/TypeSystem/InterfaceType.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/TypeSystem/Type.h"
#include "Ring1/Collections/InlineArray.h"


/// @brief Flags set if the prerequisites were added.
#define Machine_InterfaceTypeFlags_PrerequisitesAdded (1<<1)

/// @brief Flag set if the prerequisites were initialized.
#define Machine_InterfaceTypeFlags_PrerequisitesInitialized (1<<2)

/// @brief The description of an interface type.
/// @detail
/// This structure holds the following fields:
/// - extends
/// An array of pointers the interface type extends.
/// - size
/// The size, in Bytes, of the dispatch.
typedef struct Machine_InterfaceType Machine_InterfaceType;

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

Ring1_Inline() bool
Machine_InterfaceType_hasFlag
  (
    Machine_InterfaceType const* self,
    uint8_t flag
  )
{ return flag == (self->flags & flag); }

Ring1_Inline() void
Machine_InterfaceType_addFlag
  (
    Machine_InterfaceType* self,
    uint8_t flag
  )
{ self->flags |= flag; }

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
      Machine_CreateInterfaceTypeArgs args = {                                                     \
        .createTypeArgs = {                                                                        \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed,               \
        },                                                                                         \
        .addPrerequisites = (ADD_PREREQUISITES),                                                   \
        .size = sizeof(THIS_TYPE##_Dispatch),                                                      \
      };                                                                                           \
      g_##THIS_TYPE##_InterfaceType = Machine_createInterfaceType(&args);                          \
    }                                                                                              \
    return g_##THIS_TYPE##_InterfaceType;                                                          \
  }

#endif // RING2_TYPESYSTEM_INTERFACETYPE_H_INCLUDED
