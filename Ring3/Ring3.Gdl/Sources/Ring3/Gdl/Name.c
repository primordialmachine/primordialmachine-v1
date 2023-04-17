// @file Ring3/Gdl/Name.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Name.h"
#undef RING3_GDL_PRIVATE

#include "Ring3/Gdl/parse.h"

static void
Ring3_Gdl_Name_visit
  (
    Ring3_Gdl_Name* self
  )
{
  if (self->string) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->string);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_Name /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring3_Gdl_Name_visit /*visit*/,
                         &Ring3_Gdl_Name_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring3_Gdl_Name_construct
  (
    Ring3_Gdl_Name* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->string = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  parseName(Ring2_String_getBytes(self->string),
            Ring2_String_getBytes(self->string) + Ring2_String_getNumberOfBytes(self->string));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gdl_Name_getType());
}

Ring1_NoDiscardReturn() Ring3_Gdl_Name*
Ring3_Gdl_Name_create
  (
    Ring2_String *string
  )
{
  Machine_Type* ty = Ring3_Gdl_Name_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setString(&arguments[0], string);
  Ring3_Gdl_Name* self = (Ring3_Gdl_Name*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_Name_toString
  (
    Ring3_Gdl_Name* self
  )
{ return self->string; }
