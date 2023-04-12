#if !defined(MKX_OBJECT_TYPES_INTERNAL_H_INCLUDED)
#define MKX_OBJECT_TYPES_INTERNAL_H_INCLUDED


#include "Mkx/Object/Types.h"
#include <stdbool.h>


// Forward declaration.
typedef struct Mkx_Type Mkx_Type;

/// @internal
/// @brief Add a type to the type set singleton.
/// @param type A pointer to the type.
/// @return @a 0 on succes, a non-zero value on failure.
/// @todo Fail if a type with the same name is already in the type set.
int
Mkx_Object_Types_add
  (
    Mkx_Type *type
  );

/// @internal
/// @brief Initialize the type set singleton.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @warning Not mt-safe, must not be outside from the mt-safe module initialization/uninitialization functions.
Ring1_CheckReturn() int
Mkx_Object_Types_initialize
  (
  );

/// @internal
/// @brief Uninitialize the type set singleton.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @warning Not mt-safe, must not be outside from the mt-safe module initialization/uninitialization functions.
void
Mkx_Object_Types_uninitialize
  (
  );

/// @todo Should not be part of the public API.
/// @todo Move into 'Types.internal.h'.
int
Mkx_Object_Types_findFirst
  (
    Mkx_Type** result,
    void* context,
    int (*predicate)(bool *,void*, Mkx_Type*)
  );


#endif // MKX_OBJECT_TYPES_INTERNAL_H_INCLUDED
