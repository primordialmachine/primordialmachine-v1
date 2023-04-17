// @file Ring3/Gdl/Name.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_NAME_H_INCLUDED)
#define RING3_GDL_NAME_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Name.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_Name)

struct Ring3_Gdl_Name_Class {
  Machine_Object_Class parent;
};

struct Ring3_Gdl_Name {
  Machine_Object parent;
  Ring2_String* string;
};

void
Ring3_Gdl_Name_construct
  (
    Ring3_Gdl_Name* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gdl_Name*
Ring3_Gdl_Name_create
  (
    Ring2_String *string
  );

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_Name_toString
  (
    Ring3_Gdl_Name* self
  );

#endif // RING3_GDL_NAME_H_INCLUDED
