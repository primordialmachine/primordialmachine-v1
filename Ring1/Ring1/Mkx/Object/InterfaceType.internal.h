#if !defined(MKX_INTERFACETYPETYPE_USER_H_INCLUDED)
#define MKX_INTERFACETYPE_USER_H_INCLUDED


#include "Mkx/Object/InterfaceType.h"
#include "Mkx/Object/Type.internal.h"


/// @brief Representation of an "interface" type.
struct Mkx_InterfaceType
{
  Mkx_Type __parent;

  /// @brief The size, in Bytes, of the dispatch of this interface type.
  size_t dispatchSize;

  /// @brief Pointer to a function adding the prerequisites of this interface type or a null pointer.
  int (*addPrerequisites)(Mkx_InterfaceType *self);

  /// @brief List of direct prerequisite interfaces of this interface.
  struct
  {
    Mkx_InterfaceType** elements;
    size_t size;
  } extensions;

};

Ring1_NonNull(1, 2) int
Mkx_InterfaceType_construct
  (
    Mkx_InterfaceType *self,
    const char* name,
    void (*notifyTypeRemoved)(),
    int (*addPrerequisites)(Mkx_InterfaceType* self),
    size_t dispatchSize
  );

Ring1_NonNull() void
Mkx_InterfaceType_destruct
  (
    Mkx_InterfaceType* self
  );

/// @brief Get if an interface type @a a is a user of the other type @a b.
/// @param result A pointer to a <code>bool</code> variable.
/// @param a A pointer to the interface type.
/// @param b A pointer to the other type.
/// @success <code>*result</code> is assigned @a true if @a a is a user of @a b and is assigned @a false otherwise.
/// @failure <code>*result</code> was not dereferenced.
/// @remark An interface type A is a user of a type B if B is a DIRECT prerequisite of A.
Ring1_CheckReturn() int
Mkx_InterfaceType_isUserOf
  (
    bool *result,
    const Mkx_InterfaceType *a,
    const Mkx_Type *b
  );

#endif // MKX_INTERFACETYPE_USER_H_INCLUDED
