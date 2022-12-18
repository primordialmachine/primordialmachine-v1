/// @file Video/FontsContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/FontsContext.h"


#include "Ring1/All/_Include.h"


MACHINE_DEFINE_CLASSTYPE(Machine_FontsContext, Machine_Object, NULL,
                         &Machine_FontsContext_construct, NULL, NULL, NULL)

void Machine_FontsContext_construct(Machine_FontsContext* self, size_t numberOfArguments,
                                    Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_FontsContext_getType());
}

Machine_Font* Machine_FontsContext_createFont(Machine_FontsContext* self, Ring2_String* path,
                                              Ring2_Integer pointSize) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_FontsContext, createFont, path, pointSize);
}
