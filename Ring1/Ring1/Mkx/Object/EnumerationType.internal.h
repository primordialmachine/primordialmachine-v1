#if !defined(RING1_OBJECT_ENUMERATIONTYPE_INTERNAL_H_INCLUDED)
#define RING1_OBJECT_ENUMERATIONTYPE_INTERNAL_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/EnumerationType.internal.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/EnumerationType.h"
#include "Mkx/Object/Type.internal.h"


/// @brief Representation of an "enumeration" type.
struct Mkx_EnumerationType
{
  Mkx_Type __parent;
  /// @brief The size, in Bytes, of a value of this type.
  size_t size;
};

Ring1_NonNull(1, 2) int
Mkx_EnumerationType_construct
  (
    Mkx_EnumerationType* self,
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  );

Ring1_NonNull() void
Mkx_EnumerationType_destruct
  (
    Mkx_EnumerationType* self
  );

/// @brief Get if an enumeration type @a a is a user of another type @a b.
/// @param a A pointer to the enumeration type.
/// @param b A pointer to the other type.
/// @success <code>*result</code> is assigned @a true if @a a is a user of @a b and is assigned @a false otherwise.
/// @failure <code>*result</code> was not dereferenced.
/// @remark An enumeration type A is never a user of a type B.
Ring1_CheckReturn() int
Mkx_EnumerationType_isUserOf
  (
    bool *result,
    const Mkx_EnumerationType *a,
    const Mkx_Type *b
  );

#endif // RING1_OBJECT_ENUMERATIONTYPE_INTERNAL_H_INCLUDED
