// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/ConsoleLogger.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/ConsoleLogger.h"
#undef RING1_PRIVATE

Mkx_Type_DefineEnumerationType("Ring1.ConsoleLogger.Color",
                               Ring1_ConsoleLogger_Color)

Mkx_Type_DefineClassType("Ring1.ConsoleLogger",
                         Mkx_ConsoleLogger,
                         MKX_CONSOLELOGGER,
                         Mkx_Logger,
                         Mkx_Type_UseDefaultMemoryManager(),
                         Mkx_Type_ImplementInterfaces());

Ring1_CheckReturn() static Ring1_Result
setColor
  (
    Mkx_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  );

Ring1_CheckReturn() static Ring1_Result
getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Mkx_ConsoleLogger* self
  );

Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_construct
  (
    Mkx_ConsoleLogger* self
  )
{
  Mkx_Type* type = MKX_TYPE_GET(Mkx_ConsoleLogger);
  if (Ring1_Unlikely(!self || !type)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Mkx_Logger_construct(MKX_LOGGER(self)))) {
    return Ring1_Result_Failure;
  }
  self->color = Ring1_ConsoleLogger_Color_Default;
  MKX_OBJECT(self)->type = type;
  return Ring1_Result_Success;
}

static void
Mkx_ConsoleLogger_destruct
  (
    Mkx_ConsoleLogger* self
  )
{}

Ring1_CheckReturn() static Ring1_Result
Mkx_ConsoleLogger_Dispatch_construct
  (
    Mkx_ConsoleLogger_Dispatch *self
  )
{
  MKX_CONSOLELOGGER_DISPATCH(self)->getColor = (Ring1_Result (*)(Ring1_ConsoleLogger_Color*, Mkx_ConsoleLogger*))&getColor;
  MKX_CONSOLELOGGER_DISPATCH(self)->setColor = (Ring1_Result (*)(Mkx_ConsoleLogger *, Ring1_ConsoleLogger_Color))&setColor;
  return Ring1_Result_Success;
}

static void
Mkx_ConsoleLogger_Dispatch_destruct
  (
    Mkx_ConsoleLogger_Dispatch* self
  )
{}

Ring1_CheckReturn() static Ring1_Result
setColor
  (
    Mkx_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  )
{
  self->color = color;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() static Ring1_Result
getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Mkx_ConsoleLogger* self
  )
{
  *result = self->color;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_setColor
  (
    Mkx_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  )
{ MKX_VIRTUALCALLBODY(Mkx_ConsoleLogger, setColor, self, color); }

Ring1_CheckReturn() Ring1_Result
Mkx_ConsoleLogger_getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Mkx_ConsoleLogger* self
  )
{ MKX_VIRTUALCALLBODY(Mkx_ConsoleLogger, getColor, result, self); }
