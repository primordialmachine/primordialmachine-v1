// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/TypeFlags.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/TypeSystem/Type.h"

#include "Ring2/Gc.h"

Ring1_CheckReturn() bool
Machine_Type_isClass
  (
    Machine_Type const* self
  )
{ return Ring2_TypeFlags_Class == (self->flags & Ring2_TypeFlags_Class); }

Ring1_CheckReturn() bool
Machine_Type_isEnumeration
  (
    Machine_Type const* self
  )
{ return Ring2_TypeFlags_Enumeration == (self->flags & Ring2_TypeFlags_Enumeration); }

Ring1_CheckReturn() bool
Machine_Type_isInterface
  (
    Machine_Type const* self
  )
{ return Ring2_TypeFlags_Interface == (self->flags & Ring2_TypeFlags_Interface); }

void
Ring2_Type_visit
  (
    Machine_Type* self
  )
{
  for (size_t i = 0, n = self->children.size; i < n; ++i) {
    Machine_Type* element = self->children.elements[i];
    Ring2_Gc_visit(Ring2_Gc_get(), element);
  }
}

void
Ring2_Type_finalize
  (
    Machine_Type* self
  )
{
  if (self->children.elements) {
    Ring1_Memory_deallocate(self->children.elements);
    self->children.elements = NULL;
  }
  if (self->typeRemoved) {
    self->typeRemoved();
  }
}

bool
Ring2_TypeFlag_isSet
  (
    Machine_Type const* self,
    uint32_t flag
  )
{ return flag == (self->flags & flag); }

void
Ring2_TypeFlag_set
  (
    Machine_Type* self,
    uint32_t flag
  )
{ self->flags |= flag; }
