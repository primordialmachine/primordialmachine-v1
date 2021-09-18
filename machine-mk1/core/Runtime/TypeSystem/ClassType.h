/// @file Runtime/TypeSystem/ClassType.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_TYPESYSTEM_CLASSTYPE_H_INCLUDED)
#define MACHINE_RUNTIME_TYPESYSTEM_CLASSTYPE_H_INCLUDED



#include <stddef.h>
typedef struct Machine_Value Machine_Value;



/// @brief Invoked when the class type is removed.
typedef void (Machine_ClassTypeRemovedCallback)();

/// @brief Type of an object visit callback.
/// @param self A pointer to the object.
typedef void (Machine_ClassObjectVisitCallback)(void* self);

/// @brief Type of an object visiti callback.
/// @param self A pointer to the object.
/// @param numberOfArguments The number of elements in the array pointed to by @a arguments.
/// @param arguments A pointer to an array of @a numberOfArguments arguments.
typedef void (Machine_ClassObjectConstructCallback)(void* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Type of an object destruct callback.
/// @param self A pointer to the object.
typedef void (Machine_ClassObjectDestructCallback)(void* self);

/// C-level representation of a class type.
/// This structure holds the following fields:
/// - parent
/// A pointer to the parent class type if any, a null pointer otherwise.
/// - size
/// The size, in Bytes, of an object of this class.
/// - typeRemoved, visit, construct, destruct
/// Callbacks invoked when the type is removed, an object of that type is visited, constructed, or destructed.
typedef struct Machine_ClassType Machine_ClassType;

struct Machine_ClassType {
  Machine_ClassType* parent;
  size_t size;
  Machine_ClassTypeRemovedCallback* typeRemoved;
  Machine_ClassObjectVisitCallback* visit;
  Machine_ClassObjectConstructCallback* construct;
  Machine_ClassObjectDestructCallback* destruct;
};

/// @brief Create a class type.
/// @param parent A pointer to the parent class type or a null pointer.
/// @param size The size, in Bytes, of an object of the class.
/// @param typeRemoved Pointer to a Machine_ClassTypeRemovedCallback function or a null pointer.
/// @param visit Pointer to a Machine_ClassObjectVisitCallback function or a null pointer.
/// @param construct Pointer to a Machine_ClassObjectConstructCallback function or a null pointer.
/// @param destruct Pointer to a Machine_ClassObjectDestructCallback function or a null pointer.
/// @return A pointer to the classed type.
Machine_ClassType* Machine_createClassType(Machine_ClassType* parent, size_t size, Machine_ClassTypeRemovedCallback* typeRemoved, Machine_ClassObjectVisitCallback* visit, Machine_ClassObjectConstructCallback* construct, Machine_ClassObjectDestructCallback* destruct);



#endif // MACHINE_RUNTIME_TYPESYSTEM_CLASSTYPE_H_INCLUDED
