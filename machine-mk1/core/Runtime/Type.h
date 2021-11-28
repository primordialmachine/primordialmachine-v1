/// @file Runtime/TS/Type.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_TS_TYPE_H_INCLUDED)
#define MACHINE_RUNTIME_TS_TYPE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "_Eal.h"



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
typedef void (Machine_TypeRemovedCallback)();

/// @brief Type flags. See Machine_Type for more information.
#define Machine_TypeFlags_Class (1)

/// @brief Type flags. See Machine_Type for more information.
#define Machine_TypeFlags_Interface (2)

/// @brief Type flags. See Machine_Type for more infomration.
#define Machine_TypeFlags_Initialized (4)

struct Machine_Type {
  /// @brief Either Machine_TypeFlags_Class or Machine_TypeFlags_Interface must be set.
  ///        If the type has been initialized, then Machine_TypeFlags_Initialized must be set.
  uint32_t flags;
  /// @brief Pointer to a "type removed" callback or a null pointer.
  Machine_TypeRemovedCallback* typeRemoved;
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

/// @brief Get if this type is an interface type.
/// @param self A pointer to this type.
/// @return @a true if this type is an interface type, @a false otherwise.
bool Machine_Type_isInterface(Machine_Type const* self);

#endif // MACHINE_RUNTIME_TS_TYPE_H_INCLUDED
