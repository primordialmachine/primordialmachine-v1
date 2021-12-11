/// @file Collections/List.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_LIST_H_INCLUDED)
#define MACHINE_COLLECTIONS_LIST_H_INCLUDED



#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif

#include "Collections/Collection.h"



/// @brief A list.
MACHINE_DECLARE_CLASSTYPE(Machine_List)

struct Machine_List_Class {
  Machine_Collection_Class parent;
};

struct Machine_List {
  Machine_Collection parent;
  size_t size;
  size_t capacity;
  Machine_Value* elements;
};

/// @brief Construct this list.
/// @param self A pointer to this list.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_List_construct(Machine_List* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Create an empty list.
/// @return The list.
Machine_List* Machine_List_create();

#endif // MACHINE_COLLECTIONS_LIST_H_INCLUDED
