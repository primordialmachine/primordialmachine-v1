#if !defined(MACHINE_RUNTIME_WEAKREFERENCE_H_INCLUDED)
#define MACHINE_RUNTIME_WEAKREFERENCE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/Object/Object.h"
#include "Runtime/Value.h"

/// @brief The C-level representation of a weak reference.
MACHINE_DECLARE_CLASSTYPE(Machine_WeakReference)

struct Machine_WeakReference_Class {
  Machine_Object_Class parent;
};

struct Machine_WeakReference {
  Machine_Object parent;
  uintptr_t id;
  Machine_Value value;
};

/// @brief Create a weak reference.
/// @param value The value.
Machine_WeakReference* Machine_WeakReference_create(Machine_Value value);

/// @brief Get the object of the weak reference.
/// @return The value.
Machine_Value Machine_WeakReference_get(Machine_WeakReference* self);

#endif // MACHINE_RUNTIME_WEAKREFERENCE_H_INCLUDED
