// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/ClassType.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPESYSTEM_CLASSTYPE_H_INCLUDED)
#define RING2_TYPESYSTEM_CLASSTYPE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/TypeSystem/ClassType.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/TypeSystem/Type.h"
#include "Ring1/InlineArray.h"
typedef struct Machine_EnumerationType Machine_EnumerationType;
typedef struct Machine_InterfaceType Machine_InterfaceType;
typedef struct Machine_InterfaceDispatch Machine_InterfaceDispatch;
typedef struct Machine_Value Machine_Value;

/// @brief The description of a class type.
/// @detail
/// This structure holds the following fields:
/// - parent
/// A pointer to the parent class type if any, a null pointer otherwise.
/// - size
/// The size, in Bytes, of an object of this class.
/// - classSize
/// The size, in Bytes, of the dispatch of this class.
/// - visit, construct, destruct
/// Callbacks invoked when an object of that type is visited, constructed, or destructed.
typedef struct Machine_ClassType Machine_ClassType;

/// @brief Type of a class object visit callback.
/// @param self A pointer to the object.
typedef void(Machine_ClassObjectVisitCallback)(void* self);

/// @brief Type of an object destruct callback.
/// @param self A pointer to the object.
typedef void(Machine_ClassObjectDestructCallback)(void* self);

/// @brief The callback for constructing a class.
typedef void(Machine_ClassConstructCallback)(void*);

/// @brief A callback for constructing an interface.
/// @param self A pointer to the class type.
typedef void(Machine_InterfaceConstructCallback)(Machine_InterfaceDispatch *);

/// @brief Type of an implement interfaces callback.
/// @param self A pointer to the class type.
typedef void(Machine_ImplementInterfacesCallback)(Machine_ClassType* self);

typedef struct Machine_InterfaceImplementation {
  Machine_InterfaceType* interfaceType;
  Machine_InterfaceConstructCallback* constructInterface;
} Machine_InterfaceImplementation;

typedef struct Machine_InterfaceDispatchNode {
  Machine_InterfaceDispatch* dispatch;
} Machine_InterfaceDispatchNode;

/// @brief Type of a class object visit callback.
/// @param self A pointer to the object.
/// @param numberOfArguments The number of elements in the array pointed to by @a arguments.
/// @param arguments A pointer to an array of @a numberOfArguments arguments.
typedef void(Machine_ClassObjectConstructCallback)(void* self, size_t numberOfArguments,
                                                   Machine_Value const* arguments);

typedef struct Machine_CreateClassTypeArgs {
  Machine_CreateTypeArgs createTypeArgs;

  /// @brief A pointer to the parent class type or a null pointer.
  Machine_ClassType* parent;

  struct {
    /// @brief The size, in Bytes, of an object of the class.
    size_t size;

    /// @brief Pointer to a Machine_ClassObjectVisitCallback function or a null pointer.
    Machine_ClassObjectVisitCallback* visit;

    /// @brief Pointer to a Machine_ClassObjectConstructCallback function or a null pointer.
    Machine_ClassObjectConstructCallback* construct;

    /// @brief Pointer to a Machine_ClassObjectDestructCallback function or a null pointer.
    Machine_ClassObjectDestructCallback* destruct;
  } object;

  struct {
    /// @brief The size, in Bytes, of the dispatch of this class.
    size_t size;
    /// @brief Pointer to a Machine_ClassConstructCallback function or a null pointer.
    Machine_ClassConstructCallback* construct;
  } class;

  struct {
    /// @brief Pointer to a Machine_ImplementInterfacesCallback or a null pointer.
    Machine_ImplementInterfacesCallback* implementInterfaces;
  } interfaces;

} Machine_CreateClassTypeArgs;

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
    Ring1_InlineArray implementations2;
    bool implementationsInitialized;
    Ring1_InlineArray dispatches2;
    bool dispatchesInitialized;
  } interfaces;
};

/// @brief Create a class type.
/// @param args A pointer to a stack-allocated Machine_CreateClassTypeArgs object.
/// @return A pointer to the class type.
Machine_ClassType* Machine_createClassType(Machine_CreateClassTypeArgs* args);

/// @brief Make this class type implement the specified interface type.
/// @param self This class type.
/// @param implemented The implemented type. Must be an interface type.
/// @error Machine.Status.InvalidOperation An implementation for that interface already exists.
void Machine_ClassType_implement(Machine_ClassType* self, Machine_InterfaceType* implemented,
                                 Machine_InterfaceConstructCallback* constructInterface);

void Machine_ClassType_ensureInitialized(Machine_ClassType* self);

Machine_ClassType* Machine_ClassType_getParent(Machine_ClassType *self);

/// @brief Get the dispatch of this class type.
/// @param self A pointer to this class type.
/// @return A pointer to the dispatch.
void* Machine_ClassType_getDispatch(Machine_ClassType* self);

/// @brief Get an interface dispatch of this class.
/// @param self A pointer to this class type.
/// @param interfaceType A pointer to ther interface type.
/// @return A pointer to the dispatch or a null pointer.
void* Machine_ClassType_getInterfaceDispatch(Machine_ClassType* self,
                                             Machine_InterfaceType* interfaceType);

#define MACHINE_DECLARE_CLASSTYPE(THIS)                                                            \
  typedef struct THIS THIS;                                                                        \
  typedef struct THIS##_Class THIS##_Class;                                                        \
  Machine_ClassType* THIS##_getType();

#define MACHINE_DEFINE_CLASSTYPE(THIS, PARENT, VISIT, CONSTRUCT, DESTRUCT, CLASS_CONSTRUCT,        \
                                 INTERFACES_IMPLEMENT)                                             \
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
        .object.size = sizeof(THIS), \
        .object.visit = (Machine_ClassObjectVisitCallback*)VISIT, \
        .object.construct = (Machine_ClassObjectConstructCallback*)CONSTRUCT, \
        .object.destruct = (Machine_ClassObjectDestructCallback*)DESTRUCT, \
        .class.size = sizeof(THIS##_Class), \
        .class.construct = (Machine_ClassConstructCallback*)CLASS_CONSTRUCT, \
        .interfaces.implementInterfaces = (Machine_ImplementInterfacesCallback*)INTERFACES_IMPLEMENT, \
      };                                                      \
      g_##THIS##_ClassType = Machine_createClassType(&args);                                       \
    }                                                                                              \
    return g_##THIS##_ClassType;                                                                   \
  }

#endif // RING2_TYPESYSTEM_CLASSTYPE_H_INCLUDED
