#if !defined(MACHINE_COLLECTIONS_ICOLLECTION_H_INCLUDED)
#define MACHINE_COLLECTIONS_ICOLLECTION_H_INCLUDED

#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif
#include "_Runtime.h"

MACHINE_DECLARE_INTERFACETYPE(Machine_ICollection)

struct Machine_ICollection_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*clear)(Machine_ICollection* self);
  size_t (*getSize)(Machine_ICollection const* self);
};

/// @brief Clear this collection.
/// @param self A pointer to this collection.
void Machine_ICollection_clear(Machine_ICollection* self);

/// @brief Get the size of this collection.
/// @param self A pointer to this collection.
/// @return The size of this collection.
/// @error Machine_Status_InvalidArgument @a self is null.
size_t Machine_ICollection_getSize(Machine_ICollection const* self);

#endif // MACHINE_COLLECTIONS_ICOLLECTION_H_INCLUDED
