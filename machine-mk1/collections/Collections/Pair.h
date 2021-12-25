/// @file Collections/Pair.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_PAIR_H_INCLUDED)
#define MACHINE_COLLECTIONS_PAIR_H_INCLUDED

#include "Collections/_header.i"

/// @brief A pair.
MACHINE_DECLARE_CLASSTYPE(Machine_Pair)

struct Machine_Pair_Class {
  Machine_Object_Class parent;
};

struct Machine_Pair {
  Machine_Object parent;
  Machine_Value first;
  Machine_Value second;
};

/// @brief Construct this pair.
/// @param self This pair.
/// @param numberOfArguments The number of arguments. Must be 2.
/// @param arguments The arguments.
/// The first argument is the first value,
/// the second argument is the second value.
void Machine_Pair_construct(Machine_Pair* self, size_t numberOfArguments,
                            const Machine_Value* arguments);

/// @brief Create a pair with default values.
/// @return The pair.
Machine_Pair* Machine_Pair_create(Machine_Value first, Machine_Value second);

/// @brief Get the value for this pair.
/// @param self This pair.
/// @param index The index. Must be @a 0 or @a 1.
/// @return The value.
Machine_Value Machine_Pair_get(Machine_Pair* self, Machine_Integer index);

#endif // MACHINE_COLLECTIONS_PAIR_H_INCLUDED
