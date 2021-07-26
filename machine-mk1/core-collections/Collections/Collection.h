/// @file Collections/Collection.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_COLLECTION_H_INCLUDED)
#define MACHINE_COLLECTIONS_COLLECTION_H_INCLUDED



#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif

#include "_Runtime.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Collection)

struct Machine_Collection {
  Machine_Object parent;
  void(*clear)(Machine_Collection* self);
  size_t(*getSize)(const Machine_Collection* self);
};

/// @brief Construct this collection.
/// @param self This collection.
void Machine_Collection_construct(Machine_Collection* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @brief Clear this collection.
/// @param self A pointer to this collection.
/// @abstract
void Machine_Collection_clear(Machine_Collection* self);

/// @brief Get the size of this collection.
/// @param self A pointer to this collection.
/// @return The size of this collection.
/// @error Machine_Status_InvalidArgument @a self is null.
/// @abstract
size_t Machine_Collection_getSize(const Machine_Collection* self);



#endif // MACHINE_COLLECTIONS_COLLECTION_H_INCLUDEd
