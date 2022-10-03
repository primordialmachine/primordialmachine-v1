// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/WeakReference.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_WEAKREFERENCE_H_INCLUDED)
#define RING2_LIBRARY_WEAKREFERENCE_H_INCLUDED


#if !defined(RING2_LIBRARY_PRIVATE) && 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/WeakReference.h` file directly, include `Ring2/Library/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"


/// @brief The C-level representation of a weak reference.
MACHINE_DECLARE_CLASSTYPE(Machine_WeakReference)

struct Machine_WeakReference_Class {
  Machine_Object_Class parent;
};

struct Machine_WeakReference {
  Machine_Object parent;
  uintptr_t id;
  Ring2_Value value;
};

/// @brief Create a weak reference.
/// @param value The value.
/// @return A pointer to the weak reference.
Machine_WeakReference*
Machine_WeakReference_create
  (
    Ring2_Value value
  );

/// @brief Get the object of this weak reference.
/// @param self A pointer to this weak reference.
/// @return The value.
Ring2_Value
Machine_WeakReference_get
  (
    Machine_WeakReference* self
  );


#endif // RING2_LIBRARY_WEAKREFERENCE_H_INCLUDED
