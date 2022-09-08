/// @file Collections/HashMap.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED)
#define MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED

#include "Collections/_header.i"

/// @brief A hash map.
/// @implements Machine.Map
/// @details
/// This hash map uses the default getHashValue functions for Machine.Value values.
/// It uses the default isEqualTo functions for Machine.Value values with one exception:
/// When two <code>NaN</code> values are compared, then they are considered as equal.
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
                               Ring2_Value const* arguments);

/// @brief Create an empty hash map.
/// @return The hash map.
Machine_HashMap* Machine_HashMap_create();

#endif // MACHINE_COLLECTIONS_HASHMAP_H_INCLUDED
