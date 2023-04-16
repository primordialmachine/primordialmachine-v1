// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Object/InterfaceType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/InterfaceType.internal.h"
#undef MKX_OBJECT_INTERNAL


#include "Ring1/Memory/_Include.h"


Ring1_NonNull() bool
Mkx_InterfaceType_isPrerequisite
  (
    const Mkx_InterfaceType* self,
    const Mkx_InterfaceType* other
  )
{
  //
  if (self == other)
  { return true; }
  //
  for (size_t i = 0, n = other->extensions.size; i < n; ++i)
  {
    if (Mkx_InterfaceType_isPrerequisite(MKX_INTERFACETYPE(other->extensions.elements[i]), self))
    { return true; }
  }
  //
  return false;
}

Ring1_NonNull(1, 2) bool
Mkx_InterfaceType_isDirectPrerequisite
  (
    const Mkx_InterfaceType* self,
    const Mkx_InterfaceType* other
  ) 
{
  //
  if (self == other)
  {
    return true;
  }
  //
  for (size_t i = 0, n = other->extensions.size; i < n; ++i)
  {
    if (other->extensions.elements[i] == self)
    {
      return true;
    }
  }
  //
  return false;
}

Ring1_NonNull() int
Mkx_InterfaceType_addPrerequisite
  (
    Mkx_InterfaceType* self,
    Mkx_InterfaceType* other
  )
{
  // Neither "self" nor "other" may be null.
  if (Ring1_Unlikely(!self || !other)) return 1;
  // "other" must not be already a prerequisite of "self".
  if (Mkx_InterfaceType_isPrerequisite(other, self)) return 0;
  // @todo
  // Reallocating each time is not too efficient.
  // Use the following scheme:
  // If "nextPowerOfTwo(size) == size" holds, then reallocate the array to "nextPowerOfTwo(numberOfElements+1)"
  // (if such a next power of two exists). We then can determine the current capacity by computing (again) the
  // "nextPowerOfTwo(size)" at any point.
  Mkx_InterfaceType** newExtensions = NULL;
  if (Ring1_Memory_reallocateArray((void **)&newExtensions,
                                   self->extensions.elements,
                                   self->extensions.size + 1,
                                   sizeof(Mkx_InterfaceType*)))
    return 1;
  self->extensions.elements = newExtensions;
  self->extensions.elements[self->extensions.size++] = other;
  //
  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_InterfaceType_ensureInitialized
  (
    Mkx_InterfaceType* self
  )
{
  /*@todo Ensure the type is initialized.*/
  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_InterfaceType_ensureUninitialized
  (
    Mkx_InterfaceType* self
  )
{
  /*@todo Ensure the type is initialized.*/
  return 0;
}
