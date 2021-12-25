/// @file Collections/HashMap.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED)
#define MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED

#include "Collections/_header.i"

/// @brief A map.
MACHINE_DECLARE_CLASSTYPE(Machine_HashMap)

struct Machine_HashMap_Class {
  Machine_Object_Class parent;
};

struct Machine_HashMap {
  Machine_Object parent;
  void* pimpl;
};

/// @brief Construct this hash map.
/// @param self This hash map.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_HashMap_construct(Machine_HashMap* self, size_t numberOfArguments,
                               const Machine_Value* arguments);

/// @brief Create an empty hash map.
/// @return The hash map.
Machine_HashMap* Machine_HashMap_create();

#endif // MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED
