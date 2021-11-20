/// @file Runtime/Object/ClassType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_OBJECT_CLASSTYPE_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_CLASSTYPE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "Runtime/Type.h"
typedef struct Machine_Value Machine_Value;

/// @brief Type of an object visit callback.
/// @param self A pointer to the object.
typedef void(Machine_ClassObjectVisitCallback)(void* self);

/// @brief Type of an object visiti callback.
/// @param self A pointer to the object.
/// @param numberOfArguments The number of elements in the array pointed to by @a arguments.
/// @param arguments A pointer to an array of @a numberOfArguments arguments.
typedef void(Machine_ClassObjectConstructCallback)(void* self, size_t numberOfArguments,
                                                   Machine_Value const* arguments);

/// @brief Type of an object destruct callback.
/// @param self A pointer to the object.
typedef void(Machine_ClassObjectDestructCallback)(void* self);

typedef void(Machine_ClassConstructCallback)(void*);

/// C-level representation of a class type.
/// This structure holds the following fields:
/// - parent
/// A pointer to the parent class type if any, a null pointer otherwise.
/// - size
/// The size, in Bytes, of an object of this class.
/// - classSize
/// The size, in Bytes, of the dispatch of this class.
/// - typeRemoved
/// Pointer to a callback invoked when the type is removed or null.
/// - visit, construct, destruct
/// Callbacks invoked when an object of that type is visited, constructed, or destructed.
typedef struct Machine_ClassType Machine_ClassType;

struct Machine_ClassType {
  Machine_Type __parent__;
  Machine_ClassType* parent;

  size_t size;
  Machine_ClassObjectVisitCallback* visit;
  Machine_ClassObjectConstructCallback* construct;
  Machine_ClassObjectDestructCallback* destruct;

  size_t classSize;
  Machine_ClassConstructCallback* constructClass;

  void* data;
};

typedef struct Machine_CreateClassTypeArgs {
  Machine_CreateTypeArgs createTypeArgs;

  /// @brief A pointer to the parent class type or a null pointer.
  Machine_ClassType* parent;

  /// @brief The size, in Bytes, of an object of the class.
  size_t size;

  /// @brief Pointer to a Machine_ClassObjectVisitCallback function or a null pointer.
  Machine_ClassObjectVisitCallback* visit;

  /// @brief Pointer to a Machine_ClassObjectConstructCallback function or a null pointer.
  Machine_ClassObjectConstructCallback* construct;

  /// @brief Pointer to a Machine_ClassObjectDestructCallback function or a null pointer.
  Machine_ClassObjectDestructCallback* destruct;

  size_t classSize;
  Machine_ClassConstructCallback* constructClass;

} Machine_CreateClassTypeArgs;

/// @brief Create a class type.
/// @param args A pointer to a stack-allocated Machine_CreateClassTypeArgs object.
/// @return A pointer to the class type.
Machine_ClassType* Machine_createClassType(Machine_CreateClassTypeArgs* args);

/// @brief Get if the specified type "subType" is a sub-type of the specified type "superType".
/// @param subType, superType The specified types.
/// @return @a true if the specified type "subType" is a sub-type of the specified type "superType",
/// @a false otherwise.
bool Machine_ClassType_isSubTypeOf(Machine_ClassType const* subType,
                                   Machine_ClassType const* superType);

/// @brief Get if the specified type "superType" is a super-type of the specified type "subType".
/// @param superType, subType The specified types.
/// @return @a true if the specified type "superType" is a super-type of the specified type
/// "subType", @a false otherwise.
static inline bool Machine_ClassType_isSuperTypeOf(Machine_ClassType const* superType,
                                                   Machine_ClassType const* subType) {
  return Machine_ClassType_isSubTypeOf(subType, superType);
}

void Machine_ClassType_ensureInitialized(Machine_ClassType* self);

#define MACHINE_DECLARE_CLASSTYPE(THIS)                                                            \
  typedef struct THIS THIS;                                                                        \
  typedef struct THIS##_Class THIS##_Class;                                                        \
  Machine_ClassType* THIS##_getType();

#define MACHINE_DEFINE_CLASSTYPE(THIS, PARENT, VISIT, CONSTRUCT, DESTRUCT, CLASS_CONSTRUCT)        \
                                                                                                   \
  static Machine_ClassType* g_##THIS##_ClassType = NULL;                                           \
                                                                                                   \
  static void THIS##_onTypeDestroyed() {                                                           \
    g_##THIS##_ClassType = NULL;                                                                   \
  }                                                                                                \
                                                                                                   \
  Machine_ClassType* THIS##_getType() {                                                            \
    if (!g_##THIS##_ClassType) {                                                                   \
      Machine_CreateClassTypeArgs args = { \
        .createTypeArgs = { \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS##_onTypeDestroyed, \
        }, \
        .parent = PARENT##_getType(), \
        .size = sizeof(THIS), \
        .visit = (Machine_ClassObjectVisitCallback*)VISIT, \
        .construct = (Machine_ClassObjectConstructCallback*)CONSTRUCT, \
        .destruct = (Machine_ClassObjectDestructCallback*)DESTRUCT, \
        .classSize = sizeof(THIS##_Class), \
        .constructClass = (Machine_ClassConstructCallback*)CLASS_CONSTRUCT, \
      };                                                      \
      g_##THIS##_ClassType = Machine_createClassType(&args);                                       \
    }                                                                                              \
    return g_##THIS##_ClassType;                                                                   \
  }

#endif // MACHINE_RUNTIME_OBJECT_CLASSTYPE_H_INCLUDED
