#if !defined(MACHINE_COLLECTIONS_COLLECTION_H_INCLUDED)
#define MACHINE_COLLECTIONS_COLLECTION_H_INCLUDED

#include "Collections/_header.i"

MACHINE_DECLARE_INTERFACETYPE(Machine_Collection)

struct Machine_Collection_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*clear)(Machine_Collection* self);
  size_t (*getSize)(Machine_Collection const* self);
};

/// @brief Clear this collection.
/// @param self A pointer to this collection.
void Machine_Collection_clear(Machine_Collection* self);

/// @brief Get the size of this collection.
/// @param self A pointer to this collection.
/// @return The size of this collection.
/// @error Machine_Status_InvalidArgument @a self is null.
size_t Machine_Collection_getSize(Machine_Collection const* self);

#endif // MACHINE_COLLECTIONS_COLLECTION_H_INCLUDED
