// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Pair.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_PAIR_H_INCLUDED)
#define RING2_LIBRARY_PAIR_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/Pair.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief A pair.
MACHINE_DECLARE_CLASSTYPE(Machine_Pair)

struct Machine_Pair_Class {
  Machine_Object_Class parent;
};

struct Machine_Pair {
  Machine_Object parent;
  Ring2_Value first;
  Ring2_Value second;
};

/// @brief Construct this pair.
/// @param self This pair.
/// @param numberOfArguments The number of arguments. Must be 2.
/// @param arguments The arguments.
/// The first argument is the first value,
/// the second argument is the second value.
void Machine_Pair_construct(Machine_Pair* self, size_t numberOfArguments,
                            Ring2_Value const* arguments);

/// @brief Create a pair with default values.
/// @return The pair.
Machine_Pair* Machine_Pair_create(Ring2_Value first, Ring2_Value second);

/// @brief Get the value for this pair.
/// @param self This pair.
/// @param index The index. Must be @a 0 or @a 1.
/// @return The value.
Ring2_Value Machine_Pair_get(Machine_Pair* self, Ring2_Integer index);


#endif // RING2_LIBRARY_PAIR_H_INCLUDED
