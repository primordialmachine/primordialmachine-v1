/// @file Video/FontsContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/FontsContext.h"


MACHINE_DEFINE_CLASSTYPE(Machine_FontsContext, Machine_Object, NULL, &Machine_FontsContext_construct, NULL, NULL)

void Machine_FontsContext_construct(Machine_FontsContext* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_Object_getClassType((Machine_Object*)self, Machine_FontsContext_getClassType());
}

Machine_Font* Machine_FontsContext_createFont(Machine_FontsContext* self, Machine_String* path, Machine_Integer pointSize) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_FontsContext, createFont, path, pointSize);
}
