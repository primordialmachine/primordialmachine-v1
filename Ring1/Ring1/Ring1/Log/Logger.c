// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/Logger.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/Logger.h"
#undef RING1_PRIVATE

Mkx_Type_DefineClassType("Ring1.Logger",
                         Mkx_Logger,
                         MKX_LOGGER,
                         Mkx_Object,
                         Mkx_Type_UseDefaultMemoryManager(),
                         Mkx_Type_ImplementInterfaces());

Ring1_CheckReturn() int
Mkx_Logger_construct
  (
    Mkx_Logger *self
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_Logger);
  if (Ring1_Unlikely(!self || !type)) return 1;
  if (Ring1_Unlikely(Mkx_Object_construct(MKX_OBJECT(self))))
  { return 1; }
  MKX_OBJECT(self)->type = type;
  return 0;
}

Ring1_NonNull() static void
Mkx_Logger_destruct
  (
    Mkx_Logger* self
  )
{}

Ring1_CheckReturn() Ring1_NonNull() static int
Mkx_Logger_Dispatch_construct
  (
    Mkx_Logger_Dispatch *self
  )
{
  MKX_LOGGER_DISPATCH(self)->write = NULL;
  return 0;
}

Ring1_NonNull() static void
Mkx_Logger_Dispatch_destruct
  (
    Mkx_Logger_Dispatch* self
  )
{}

Ring1_CheckReturn() int
Mkx_Logger_write
  (
    Mkx_Logger* self,
    const char* bytes,
    size_t numberOfBytes
  )
{ MKX_VIRTUALCALLBODY(Mkx_Logger, write, self, bytes, numberOfBytes); }
