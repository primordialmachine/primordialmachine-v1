// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collection.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTION_H_INCLUDED)
#define RING2_LIBRARY_COLLECTION_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Collection.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif

#include "Ring2/_Include.h"

MACHINE_DECLARE_INTERFACETYPE(Machine_Collection)

struct Machine_Collection_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*clear)(Machine_Collection* self);
  int64_t (*getSize)(Machine_Collection const* self);
  bool (*isEmpty)(Machine_Collection const* self);
};

/// @brief Clear this collection.
/// @param self A pointer to this collection.
void
Machine_Collection_clear
  (
    Machine_Collection* self
  );

/// @brief Get the size of this collection.
/// @param self A pointer to this collection.
/// @return The size of this collection.
/// @error Machine_Status_InvalidArgument @a self is null.
Ring1_CheckReturn() int64_t
Machine_Collection_getSize
  (
    Machine_Collection const* self
  );

/// @brief Get if this collection is empty.
/// @param self A pointer to this collection.
/// @return @a true if this collection is empty, @a false otherwise.
/// @error Machine_Status_InvalidArgument @a self is null.
Ring1_CheckReturn() bool
Machine_Collection_isEmpty
  (
    Machine_Collection const* self
  );

#endif // RING2_LIBRARY_COLLECTION_H_INCLUDED
