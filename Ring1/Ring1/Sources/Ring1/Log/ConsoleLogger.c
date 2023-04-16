// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/ConsoleLogger.c
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/ConsoleLogger.h"
#undef RING1_PRIVATE


Ring1_CheckReturn() static Ring1_Result
setColor
  (
    Ring1_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  );

Ring1_CheckReturn() static Ring1_Result
getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Ring1_ConsoleLogger* self
  );

Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_construct
  (
    Ring1_ConsoleLogger* self
  )
{
  if (Ring1_Logger_construct(RING1_LOGGER(self))) {
    return Ring1_Result_Failure;
  }
  #if 0
  if (Ring1_Unlikely(Ring1_Logger_construct(MKX_LOGGER(self)))) {
    return Ring1_Result_Failure;
  }
  #endif
  self->setColor = &setColor;
  self->getColor = &getColor;
  self->color = Ring1_ConsoleLogger_Color_Default;
  RING1_LOGGER(self)->destruct = (void (*)(Ring1_Logger*))&Ring1_ConsoleLogger_destruct;
  return Ring1_Result_Success;
}

void
Ring1_ConsoleLogger_destruct
  (
    Ring1_ConsoleLogger* self
  )
{}

Ring1_CheckReturn() static Ring1_Result
setColor
  (
    Ring1_ConsoleLogger* self,
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
    Ring1_ConsoleLogger* self
  )
{
  *result = self->color;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_setColor
  (
    Ring1_ConsoleLogger* self,
    Ring1_ConsoleLogger_Color color
  )
{ return self->setColor(self, color); }

Ring1_CheckReturn() Ring1_Result
Ring1_ConsoleLogger_getColor
  (
    Ring1_ConsoleLogger_Color *result,
    Ring1_ConsoleLogger* self
  )
{ return self->getColor(result, self); }
