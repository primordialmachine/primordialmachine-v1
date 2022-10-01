// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/Type.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPESYSTEM_TYPE_H_INCLUDED)
#define RING2_TYPESYSTEM_TYPE_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/TypeSystem/Type.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include <stdint.h>
#include <stdbool.h>
#include "Ring2/Types/Object.h"
#include "Ring1/Ring1.h"

/// @brief Type flags. See Machine_Type for more information.
#define Ring2_TypeFlags_Class (1)

/// @brief Type flags. See Machine_Type for more information.
#define Ring2_TypeFlags_Enumeration (2)

/// @brief Type flags. See Machine_Type for more information.
#define Ring2_TypeFlags_Interface (4)

/// @brief Type flags. See Machine_Type for more infomration.
#define Ring2_TypeFlags_Initialized (8)

/// @brief The description of a type.
/// @detail
/// This structure holds the following fields:
///
/// - flags
/// Bitwise or of Ring2_TypeFlags_* symbolic constants.
///
/// If Ring2_TypeFlags_Class is set, then the type object describes a class type.
/// The Ring2_Type object can be cast into a Ring2_ClassType object.
///
/// If Ring2_TypeFlags_Interface is set, then the type object decribes an interface type.
/// The Ring2_Type object can be cast into a Ring2_InterfaceType object.
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
  Ring2_Gc_FinalizeCallback* finalize;
  Ring2_Gc_VisitCallback* visit;

  /// @brief Either Machine_TypeFlags_Class or Machine_TypeFlags_Interface must be set.
  ///        If the type has been initialized, then Machine_TypeFlags_Initialized must be set.
  uint32_t flags;
  /// @brief Pointer to a "type removed" callback or a null pointer.
  Machine_TypeRemovedCallback* typeRemoved;

  /// @todo Use Ring1_InlineArray.
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

/// @brief Get if this type is a class type.
/// @param self A pointer to this type.
/// @return @a true if this type is a class type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isClass
  (
    Machine_Type const* self
  );

/// @brief Get if this type is an enumeration type.
/// @param self A pointer to this type.
/// @return @a true if this type is an enumeration type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isEnumeration
  (
    Machine_Type const* self
  );

/// @brief Get if this type is an interface type.
/// @param self A pointer to this type.
/// @return @a true if this type is an interface type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isInterface
  (
    Machine_Type const* self
  );

/// @brief Ensure this type is initialized.
/// @param self A pointer to this type.
void
Machine_Type_ensureInitialized
  (
    Machine_Type* self
  );

/// @brief Get if this type is a sub-type of another type.
/// @param self A pointer to this type.
/// @param other A pointer to the other type.
/// @return @a true if this type is a sub-type of the other type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isSubTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  );

/// @brief Get if this type is a true sub-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true sub-type of the other other type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isTrueSubTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  );

/// @brief Get if this type is a super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a super-type of the other type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isSuperTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  );

/// @brief Get if this type is a true super-type of another type.
/// @param self This type.
/// @param other The other type.
/// @return @a true if this type is a true super-type of the other type, @a false otherwise.
Ring1_CheckReturn() bool
Machine_Type_isTrueSuperTypeOf
  (
    Machine_Type const* self,
    Machine_Type const* other
  );

/// @brief Visit a type object.
/// @param self A pointer to the type object.
void
Ring2_Type_visit
  (
    Machine_Type* self
  );

/// @brief Finalize a type object.
/// @param self A pointer to the type object.
void
Ring2_Type_finalize
  (
    Machine_Type* self
  );

/// @brief Get if a type flag is set.
/// @param self A pointer to this type.
/// @param flag The type flag.
/// @return @a true if the type flag is set.
bool
Ring2_TypeFlag_isSet
  (
    Machine_Type const* self,
    uint32_t flag
  );

/// @brief Set a type flag.
/// @param self A pointer to this type.
/// @param flag The flag.
void
Ring2_TypeFlag_set
  (
    Machine_Type* self,
    uint32_t flag
  );

#endif // RING2_TYPESYSTEM_TYPE_H_INCLUDED
