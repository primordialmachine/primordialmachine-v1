/// @file Ring3/Visuals/FontsContext.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/FontsContext.h"
#undef RING3_VISUALS_PRIVATE


#include "Ring1/All/_Include.h"


MACHINE_DEFINE_CLASSTYPE(Ring3_FontsContext,
                         Machine_Object,
                         NULL,
                         &Ring3_FontsContext_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_FontsContext_construct
  (
    Ring3_FontsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_FontsContext_getType());
}

Ring3_Font*
Ring3_FontsContext_createFont
  (
    Ring3_FontsContext* self,
    Ring2_String* path,
    Ring2_Integer pointSize
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_FontsContext, createFont, path, pointSize); }
