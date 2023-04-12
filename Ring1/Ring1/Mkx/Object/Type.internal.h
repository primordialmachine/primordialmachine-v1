#if !defined(MKX_OBJECT_TYPE_INTERNAL_H_INCLUDED)
#define MKX_OBJECT_TYPE_INTERNAL_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/Type.internal.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Ring1/Atom/_Include.h"
#include "Mkx/Object/Type.h"


/// @internal
/// @brief Type flag indicating a type is an array type.
#define Mkx_Type_Flags_ArrayType (1)

/// @internal
/// @brief Type flag indicating a type is a class type.
#define Mkx_Type_Flags_ClassType (2)

/// @internal
/// @brief Type flag indicating a type is an enumeration type.
#define Mkx_Type_Flags_EnumerationType (4)

/// @internal
/// @brief Type flag indicating a type is an interface type.
#define Mkx_Type_Flags_InterfaceType (8)

/// @internal
/// @brief Type flag indicating a type is a scalar type.
#define Mkx_Type_Flags_ScalarType (16)


#define Mkx_Type_FlagsMask_Kind (Mkx_Type_Flags_ArrayType | Mkx_Type_Flags_ClassType | Mkx_Type_Flags_EnumerationType | Mkx_Type_Flags_InterfaceType | Mkx_Type_Flags_ScalarType)


/// @internal
/// @brief Type flag indicating a type is instantiable type.
/// @remark Interfaces and abstract classes are not instantiable.
#define Mkx_Type_Flag_InstantiableType (32)


/// @internal
/// @brief Type flag indicating a type is initialized state.
/// - For array types, this is set then the element type was initialized.
/// Initially this flag is not set.
/// - For class types, this is set when the dispatch was initialized.
/// Initially this flag is not set.
/// - For interface types, this is set when the prerequies were added.
/// Initially this flag is not set.
/// - For scalar and enumeration types, this is set when the type is added.
#define Mkx_Type_Flags_Initialized (64)

/// @todo Shoud be part of the public API.
struct Mkx_Type
{
  Mkx_Type* next;
  /// @brief The flags of this type.
  int flags;
  /// @brief A pointer to the type name.
  Ring1_Atom* name;
  /// @brief A pointer to a "notify type removed" function.
  void (*notifyTypeRemoved)();
};

/// @internal
static inline bool
Mkx_Type_isInitialized
  (
    const Mkx_Type *self
  )
{ return Mkx_Type_Flags_Initialized == (self->flags & Mkx_Type_Flags_Initialized); }

/// @internal
int
Mkx_Type_construct
  (
    Mkx_Type* self,
    const char* name,
    void (*notifyTypeRemoved)(),
    int flags
  );

/// @internal
void
Mkx_Type_destruct
  (
    Mkx_Type* self
  );

/// @todo Should be part of the public API.
/// @brief Ensure this type is initialized.
/// @param self A pointer to this type.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @todo Should not be part of the public API.
Ring1_CheckReturn() int
Mkx_Type_ensureInitialized
  (
    Mkx_Type* self
  );

/// @todo Should be part of the public API.
/// @brief Ensure this type is uninitialized.
/// @param self A pointer to this type.
/// @return #Ring1_Status_Success on success, a failure status code on failure.
/// @todo Should not be part of the public API.
Ring1_CheckReturn() Ring1_NonNull() int
Mkx_Type_ensureUninitialized
  (
    Mkx_Type* self
  );

/// @brief Get if a type @a a is a user of type @a b.
/// @param a, b The types.
/// @return @a true if @a a is a user of @a b, @a false otherwise.
/// @see Mkx_ArrayType_isUserOf
/// @see Mkx_ClassType_isUserOf
/// @see Mkx_EnumerationType_isUserOf
/// @see Mkx_InterfaceType_isUserOf
/// @see Mkx_ScalarType_isUserOf
Ring1_CheckReturn() Ring1_NonNull() int
Mkx_Type_isUserOf
  (
    bool* result,
    const Mkx_Type* a,
    const Mkx_Type* b
  );

Ring1_CheckReturn() Ring1_NonNull() static inline int
getTypeKind
  (
    int *kind,
    const Mkx_Type* type
  )
{
  if (Ring1_Unlikely(!kind || !type)) return 1;
  *kind = (type->flags & Mkx_Type_FlagsMask_Kind);
  return 0;
}

#endif // MKX_OBJECT_TYPE_INTERNAL_H_INCLUDED
