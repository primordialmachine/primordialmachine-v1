#if !defined(MKX_OBJECT_SCALARTYPE_USER_H_INCLUDED)
#define MKX_OBJECT_SCALARTYPE_USER_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/ScalarType.internal.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/ScalarType.h"
#include "Mkx/Object/Type.internal.h"


/// @brief Representation of a "scalar" type.
struct Mkx_ScalarType
{
  Mkx_Type __parent;
  /// @brief The size, in Bytes, of a value of this type.
  size_t size;
};

Ring1_NonNull(1, 2) int
Mkx_ScalarType_construct
  (
    Mkx_ScalarType* self,
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  );

Ring1_NonNull() void
Mkx_ScalarType_destruct
  (
    Mkx_ScalarType* self
  );

/// @brief Get if a scalar type @a a is a user of another type @a b.
/// @param a A pointer to the scalar type.
/// @param b A pointer to the other type.
/// @success <code>*result</code> is assigned @a true if @a a is a user of @a b and is assigned @a false otherwise.
/// @failure <code>*result</code> was not dereferenced.
/// @remark A scalar type A is never a user of a type B.
Ring1_CheckReturn() int
Mkx_ScalarType_isUserOf
  (
    bool *result,
    const Mkx_ScalarType *a,
    const Mkx_Type *b
  );

#endif // MKX_OBJECT_SCALARTYPE_USER_H_INCLUDED
