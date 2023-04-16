#if !defined(MKX_OBJECT_ARRAYTPYE_USER_H_INCLUDED)
#define MKX_OBJECT_ARRAYTYPE_USER_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/ArrayType.internal.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/ArrayType.h"
#include "Mkx/Object/Type.internal.h"


/// @brief Representation of an "array" type.
struct Mkx_ArrayType
{
  Mkx_Type __parent;
  /// @brief A pointer to the element type of this array type.
  Mkx_Type *elementType;
};

Ring1_NonNull(1, 3) int
Mkx_ArrayType_construct
(
  Mkx_ArrayType* self,
  void (*notifyShutdown)(),
  Mkx_Type *elementType
);

Ring1_NonNull() void
Mkx_ArrayType_destruct
  (
    Mkx_ArrayType* self
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ArrayType_ensureInitialized
  (
    Mkx_ArrayType* self
  );

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ArrayType_ensureUninitialized
  (
    Mkx_ArrayType* self
  );

/// @brief Get if an array type @a a is a user of another type @a b.
/// @param result A pointer to a <code>bool</code> variable.
/// @param a A pointer to the interface type.
/// @param b A pointer to the other type.
/// @success <code>*result</code> is assigned @a true if @a a is a user of @a b and is assigned @a false otherwise.
/// @failure <code>*result</code> was not dereferenced.
/// @remark An array type A is a user of a type B if B is the element type of A.
Ring1_CheckReturn() int
Mkx_ArrayType_isUserOf
  (
    bool *result,
    const Mkx_ArrayType *a,
    const Mkx_Type *b
  );


#endif // MKX_OBJECT_ARRAYTYPE_USER_H_INCLUDED
