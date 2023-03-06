/// @file Ring3/Visuals/VertexDescriptor.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/VertexDescriptor.h"
#undef RING3_VISUALS_PRIVATE


#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/VertexElementDescriptor.h"
#undef RING3_VISUALS_PRIVATE


#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"


struct Ring3_VertexDescriptor_Class {
  Machine_Object_Class __parent;
};

struct Ring3_VertexDescriptor {
  Machine_Object __parent;
  Ring2_Collections_List* elements;
};

static void
Ring3_VertexDescriptor_visit
  (
    Ring3_VertexDescriptor* self
  );

static void
Ring3_VertexDescriptor_construct
  (
    Ring3_VertexDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Ring3_VertexDescriptor_visit
  (
    Ring3_VertexDescriptor* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_VertexDescriptor,
                         Machine_Object,
                         &Ring3_VertexDescriptor_visit,
                         &Ring3_VertexDescriptor_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Ring3_VertexDescriptor_construct
  (
    Ring3_VertexDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->elements = (Ring2_Collections_List *)Ring2_Collections_ArrayList_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_VertexDescriptor_getType());
}

static void
Ring3_VertexDescriptor_visit
  (
    Ring3_VertexDescriptor* self
  )
{
  if (self->elements) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->elements);
  }
}

Ring1_NoDiscardReturn() Ring3_VertexDescriptor*
Ring3_VertexDescriptor_create
  (
  )
{
  Machine_ClassType* ty = Ring3_VertexDescriptor_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_VertexDescriptor* self = (Ring3_VertexDescriptor*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getVertexSize
  (
    Ring3_VertexDescriptor* self
  )
{
  Ring2_Integer size = 0;
  for (Ring2_Integer i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)self->elements); i < n; ++i) {
    Ring2_Value v = Ring2_Collections_List_getAt(self->elements, i);
    Ring3_VertexElementDescriptor* element = (Ring3_VertexElementDescriptor*)Ring2_Value_getObject(&v);
    switch (Ring3_VertexElementDescriptor_getSemantics(element)) {
      case Ring3_VertexElementSemantics_XfYf:
        size += sizeof(float) * 2;
        break;
      case Ring3_VertexElementSemantics_RfGfBf:
        size += sizeof(float) * 3;
        break;
      case Ring3_VertexElementSemantics_UfVf:
        size += sizeof(float) * 2;
        break;
    };
  }
  return size;
}

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getNumberOfElements
  (
    Ring3_VertexDescriptor* self
  )
{ return Ring2_Collections_Collection_getSize((Ring2_Collections_Collection *)self->elements); }

Ring1_NoDiscardReturn() Ring3_VertexElementSemantics
Ring3_VertexDescriptor_getElementSemantics
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index
  )
{
  Ring2_Value v = Ring2_Collections_List_getAt(self->elements, index);
  Ring3_VertexElementDescriptor* element = (Ring3_VertexElementDescriptor*)Ring2_Value_getObject(&v);
  return Ring3_VertexElementDescriptor_getSemantics(element);
}

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VertexDescriptor_getElementOffset
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index
  )
{
  Ring2_Integer offset = 0;
  for (Ring2_Integer i = 0, n = index; i < n; ++i) {
    Ring2_Value v = Ring2_Collections_List_getAt(self->elements, i);
    Ring3_VertexElementDescriptor* element = (Ring3_VertexElementDescriptor*)Ring2_Value_getObject(&v);
    switch (Ring3_VertexElementDescriptor_getSemantics(element)) {
      case Ring3_VertexElementSemantics_XfYf:
        offset += sizeof(float) * 2;
        break;
      case Ring3_VertexElementSemantics_RfGfBf:
        offset += sizeof(float) * 3;
        break;
      case Ring3_VertexElementSemantics_UfVf:
        offset += sizeof(float) * 2;
        break;
    };
  }
  return offset;
}

void
Ring3_VertexDescriptor_insert
  (
    Ring3_VertexDescriptor* self,
    Ring2_Integer index,
    Ring3_VertexElementSemantics semantics
  )
{
  Ring2_Value temporary;
  Ring2_Value_setObject(&temporary, (Machine_Object*)Ring3_VertexElementDescriptor_create(semantics));
  Ring2_Collections_List_insertAt(self->elements, index, temporary);
}

void
Ring3_VertexDescriptor_append
  (
    Ring3_VertexDescriptor* self,
    Ring3_VertexElementSemantics semantics
  )
{
  Ring3_VertexDescriptor_insert(self, Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->elements), semantics); }

void
Ring3_VertexDescriptor_prepend
  (
    Ring3_VertexDescriptor* self,
    Ring3_VertexElementSemantics semantics
  )
{ Ring3_VertexDescriptor_insert(self, 0, semantics); }
