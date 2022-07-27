/// @file Runtime/TS/Type.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_TS_TYPE_H_INCLUDED)
#define MACHINE_RUNTIME_TS_TYPE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Ring1/Ring1.h"

/// C-level representation of a type.
///
/// This structure holds the following fields:
///
/// - flags
/// Bitwise or of Machine_TypeFlags_* symbolic constants.
///
/// If Machine_TypeFlags_Class is set, then the type object describes a class type.
/// The Machine_Type object can be cast into a Machine_ClassType object.
///
/// If Machine_TypeFlags_Interface is set, then the type object decribes an interface type.
/// The Machine_Type object can be cast into a Machine_InterfaceType object.
///
/// - size
/// The size, in Bytes, of an object of this class.
///
/// - typeRemoved
/// callback invoked when the type is removed.
typedef struct Machine_Type Machine_Type;

/// @brief Type callback. See Machine_Type for more information.
typedef void(Machine_TypeRemovedCallback)();

struct Machine_Type {
  /// @brief Either Machine_TypeFlags_Class or Machine_TypeFlags_Interface must be set.
  ///        If the type has been initialized, then Machine_TypeFlags_Initialized must be set.
  uint32_t flags;
  /// @brief Pointer to a "type removed" callback or a null pointer.
  Machine_TypeRemovedCallback* typeRemoved;
  struct {
    /// @brief A pointer to an array of @a size pointers to Machine_Type objects.
    Machine_Type** elements;
    /// @brief The number of elements in array @a elements.
    size_t size;
  } children;
};

typedef struct Machine_CreateTypeArgs {

  /// @brief Pointer to a Machine_ClassTypeRemovedCallback function or a null pointer.
  Machine_TypeRemovedCallback* typeRemoved;

} Machine_CreateTypeArgs;

/// @brief Ensure this type is initialized.
/// @param self A pointer to this type.
void Machine_Type_ensureInitialized(Machine_Type* self);

/// @brief Get if this type is a class type.
/// @param self A pointer to this type.
/// @return @a true if this type is a class type, @a false otherwise.
bool Machine_Type_isClass(Machine_Type const* self);

/// @brief Get if this type is an enumeration type.
/// @param self A pointer to this type.
/// @return @a true if this type is an enumeration type, @a false otherwise.
bool Machine_Type_isEnumeration(Machine_Type const* self);

/// @brief Get if this type is an interface type.
/// @param self A pointer to this type.
/// @return @a true if this type is an interface type, @a false otherwise.
bool Machine_Type_isInterface(Machine_Type const* self);

/// @brief Get if this type is a sub-type of another type.
/// @param self A pointer to this type.
/// @param other A pointer to the other type.
/// @return @a true if this type is a sub-type of the other type, @a false otherwise.
bool Machine_Type_isSubTypeOf(Machine_Type const* self, Machine_Type const* other);

/// @brief Get if this type is a true sub-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true sub-type of the other other type, @a false otherwise.
bool Machine_Type_isTrueSubTypeOf(Machine_Type const* self, Machine_Type const* other);

/// @brief Get if this type is a super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a super-type of the other type, @a false otherwise.
bool Machine_Type_isSuperTypeOf(Machine_Type const* self, Machine_Type const* other);

/// @brief Get if this type is a true super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true super-type of the other type, @a false otherwise.
bool Machine_Type_isTrueSuperTypeOf(Machine_Type const* self, Machine_Type const* other);

#endif // MACHINE_RUNTIME_TS_TYPE_H_INCLUDED
