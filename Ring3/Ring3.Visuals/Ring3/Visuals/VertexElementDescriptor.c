/// @file Ring3/Visuals/VertexElementDescriptor.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/VertexElementDescriptor.h"
#undef RING3_VISUALS_PRIVATE


#include "Ring1/All/_Include.h"


struct Ring3_VertexElementDescriptor_Class {
  Machine_Object_Class __parent;
};

struct Ring3_VertexElementDescriptor {
  Machine_Object __parent;
  Ring3_VertexElementSemantics semantics;
};

static void
Ring3_VertexElementDescriptor_construct
  (
    Ring3_VertexElementDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_VertexElementDescriptor,
                         Machine_Object,
                         NULL,
                         &Ring3_VertexElementDescriptor_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Ring3_VertexElementDescriptor_construct
  (
    Ring3_VertexElementDescriptor* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->semantics = (Ring3_VertexElementSemantics)Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 0);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_VertexElementDescriptor_getType());
}

Ring1_NoDiscardReturn() Ring3_VertexElementDescriptor*
Ring3_VertexElementDescriptor_create
  (
    Ring3_VertexElementSemantics semantics
  )
{
  Machine_ClassType* ty = Ring3_VertexElementDescriptor_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setInteger(&(ARGUMENTS[0]), semantics);
  Ring3_VertexElementDescriptor* self = (Ring3_VertexElementDescriptor*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() size_t
Ring3_VertexElementDescriptor_getSize
  (
    Ring3_VertexElementDescriptor* self
  )
{
  switch (self->semantics) {
    case Ring3_VertexElementSemantics_XfYf:
      return sizeof(float) * 2;
      break;
    case Ring3_VertexElementSemantics_RfGfBf:
      return sizeof(float) * 3;
      break;
    case Ring3_VertexElementSemantics_UfVf:
      return sizeof(float) * 2;
      break;
    default: {
      Ring1_Status_set(Ring1_Status_UnreachableProgramPointReached);
      Ring2_jump();
    } break;
  };
}

Ring1_NoDiscardReturn() Ring3_VertexElementSemantics
Ring3_VertexElementDescriptor_getSemantics
  (
    Ring3_VertexElementDescriptor* self
  )
{ return self->semantics; }
