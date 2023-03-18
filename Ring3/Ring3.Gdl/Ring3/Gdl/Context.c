/// @file Ring3/Gdl/Context.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Context.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"


static void
Machine_Gdl_Context_visit
  (
    Machine_Gdl_Context* self
  )
{
  if (self->trueLiteral) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->trueLiteral);
  }
  if (self->falseLiteral) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->falseLiteral);
  }
  if (self->voidLiteral) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->voidLiteral);
  }
}

static void
Machine_Gdl_Context_construct
  (
    Machine_Gdl_Context* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  
  self->trueLiteral = Ring2_String_fromC(false, "true");
  self->falseLiteral = Ring2_String_fromC(false, "false");
  self->voidLiteral = Ring2_String_fromC(false, "void");
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Context /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_Gdl_Context_visit /*visit*/,
                         &Machine_Gdl_Context_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

Ring1_NoDiscardReturn() Machine_Gdl_Context*
Machine_Gdl_Context_create
  (
  )
{
  Machine_Type* ty = Machine_Gdl_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gdl_Context* self = Ring1_cast(Machine_Gdl_Context*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
