/// @file Collections/ArrayList.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_ARRAYLIST_H_INCLUDED)
#define MACHINE_COLLECTIONS_ARRAYLIST_H_INCLUDED

#include "Collections/_header.i"

/// @brief An array list.
MACHINE_DECLARE_CLASSTYPE(Machine_ArrayList)

struct Machine_ArrayList_Class {
  Machine_Object_Class parent;
};

struct Machine_ArrayList {
  Machine_Object parent;
  size_t size;
  size_t capacity;
  Machine_Value* elements;
};

/// @brief Construct this list.
/// @param self A pointer to this list.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_ArrayList_construct(Machine_ArrayList* self, size_t numberOfArguments,
                                 Machine_Value const* arguments);

/// @brief Create an empty list.
/// @return The list.
Machine_ArrayList* Machine_ArrayList_create();

#endif // MACHINE_COLLECTIONS_ARRAYLIST_H_INCLUDED
