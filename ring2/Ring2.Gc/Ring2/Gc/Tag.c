// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Gc/Tag.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Gc/Tag.h"

#include <malloc.h>

/// @brief Perform a bitwise clear operation.
/// @param value The value.
/// @param mask The mask.
/// @return Any bit that is @a 1 in @a mask will be @a 0 in the returned value.
/// All other bits are the same as in @a value.
static inline uint8_t
clear_u8
  (
    uint8_t value,
    uint8_t mask
  )
{
  return value & ~mask;
}

/// @brief Perform a bitwise or operation.
/// @param value The value.
/// @param mask The mask.
/// @return Any bit that is @a 1 in @a value or in @a mask.
/// All other bits are the same as in @a value.
static inline uint8_t
or_u8
  (
    uint8_t value,
    uint8_t mask
  )
{
  return value | mask;
}

/// @brief Perform a bitwise and operation.
/// @param value The value.
/// @param mask The mask.
/// @return Any bit that is @a 1 in @a value and in @a mask is @a 1.
/// All other bits are @a 0.
static inline uint8_t
and_u8
  (
    uint8_t value,
    uint8_t mask
  )
{
  return value & mask;
}

#define Flags_Color_White (1)

#define Flags_Color_Gray (Flags_Color_White | Flags_Color_Black)

#define Flags_Color_Black (2)

#define Flags_Color_Mask (Flags_Color_White | Flags_Color_Gray | Flags_Color_Black)

/// @brief Tag flag indicating a class type object tag.
#define Machine_Flag_Class (8)

void
Ring2_Gc_Tag_initialize
  (
    Ring2_Gc_Tag* tag
  )
{
  tag->locks = 0;
  tag->flags = Flags_Color_White;
  tag->type = NULL;
  tag->weakReferences = NULL;
}

void
Ring2_Gc_Tag_uninitialize
  (
    Ring2_Gc_Tag* tag
  )
{/*Intentionally empty.*/}

uintptr_t
Ring2_Gc_Tag_addWeakReference
  (
    Ring2_Gc_Tag* tag,
    void* context,
    void (*callback)(void *context)
  )
{
  Ring2_Gc_WeakReference* weakReference = malloc(sizeof(Ring2_Gc_WeakReference));
  if (!weakReference) {
    return (uintptr_t)NULL;
  }

  weakReference->context = context;
  weakReference->callback = callback;

  weakReference->nextWeakReference = tag->weakReferences;
  tag->weakReferences = weakReference;

  return (uintptr_t)weakReference;
}

void
Ring2_Gc_Tag_removeWeakReference
  (
    Ring2_Gc_Tag* tag,
    uintptr_t id
  )
{
  // Remove this weak reference from the list of weak reference of the object.
  Ring2_Gc_WeakReference **previous, *current;
  previous = &tag->weakReferences;
  current = tag->weakReferences;
  while (NULL != current) {
    if ((uintptr_t)current == id) {
      break;
    } else {
      previous = &current->nextWeakReference;
      current = current->nextWeakReference;
    }
  }
  if (current) {
    *previous = current->nextWeakReference;
    free(current);
  } else {
    // Weak reference was not found.
  }
}

void
Ring2_Gc_Tag_notifyWeakReferences
  (
    Ring2_Gc_Tag* tag
  )
{
  while (tag->weakReferences) {
    Ring2_Gc_WeakReference* weakReference = tag->weakReferences;
    tag->weakReferences = weakReference->nextWeakReference;
    weakReference->nextWeakReference = NULL;
    weakReference->callback(weakReference->context);
    free(weakReference);
  }
}

void
Ring2_Gc_Tag_setClassType
  (
    Ring2_Gc_Tag* tag,
    bool classType
  )
{
  if (classType) {
    tag->flags = or_u8(tag->flags, Machine_Flag_Class);
  } else {
    tag->flags = clear_u8(tag->flags, Machine_Flag_Class);
  }
}

bool
Ring2_Gc_Tag_getClassType
  (
    Ring2_Gc_Tag const* tag
  )
{
  return Machine_Flag_Class == and_u8(tag->flags, Machine_Flag_Class);
}

void
Ring2_Gc_Tag_setWhite
  (
    Ring2_Gc_Tag* tag
  )
{
  tag->flags = or_u8(clear_u8(tag->flags, Flags_Color_Mask), Flags_Color_White);
}

bool
Ring2_Gc_Tag_isWhite
  (
    Ring2_Gc_Tag const* tag
  )
{
  return Flags_Color_White == and_u8(tag->flags, Flags_Color_Mask);
}

void
Ring2_Gc_Tag_setGray
  (
    Ring2_Gc_Tag* tag
  )
{
  tag->flags = or_u8(clear_u8(tag->flags, Flags_Color_Mask), Flags_Color_Gray);
}

bool
Ring2_Gc_Tag_isGray
  (
    Ring2_Gc_Tag const* tag
  )
{
  return Flags_Color_Gray == and_u8(tag->flags, Flags_Color_Mask);
}

void
Ring2_Gc_Tag_setBlack
  (
    Ring2_Gc_Tag* tag
  )
{
  tag->flags = or_u8(clear_u8(tag->flags, Flags_Color_Mask), Flags_Color_Black);
}

bool
Ring2_Gc_Tag_isBlack
  (
    Ring2_Gc_Tag const* tag
  )
{
  return Flags_Color_Black == and_u8(tag->flags, Flags_Color_Mask);
}

void
Ring2_Gc_Tag_lock
  (
    Ring2_Gc_Tag* tag
  )
{
  Ring1_ReferenceCounter_increment(&tag->locks);
}

void
Ring2_Gc_Tag_unlock
  (
    Ring2_Gc_Tag* tag
  )
{
  Ring1_ReferenceCounter_decrement(&tag->locks);
}

int32_t
Ring2_Gc_Tag_getLockCount
  (
    Ring2_Gc_Tag const* tag
  )
{
  return Ring1_ReferenceCounter_get(&tag->locks);
}
