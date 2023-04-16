// Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/DefaultConsoleLogger.c
/// @copyright Copyright (c) 2019-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/DefaultConsoleLogger.h"
#undef RING1_PRIVATE

#include "Ring1/Console.h"
#include "Ring1/Status.h"
#include <malloc.h>


Ring1_CheckReturn() static Ring1_Result
write
  (
    Ring1_DefaultConsoleLogger *self,
    char const* bytes,
    size_t numberOfBytes
  );

void
Ring1_DefaultConsoleLogger_destruct
  (
    Ring1_DefaultConsoleLogger *self
  )
{
  if (self->connection) {
    Ring1_Console_Connection_unref(self->connection);
    self->connection = NULL;
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_DefaultConsoleLogger_construct
  (
    Ring1_DefaultConsoleLogger* self,
    Ring1_Console_Connection *connection
  )
{
  if (Ring1_Unlikely(!self || !connection)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_ConsoleLogger_construct(RING1_CONSOLELOGGER(self)))) {
    return Ring1_Result_Failure;
  }
  self->connection = connection;
  Ring1_Console_Connection_ref(connection);
  RING1_LOGGER(self)->write = (Ring1_Result (*)(Ring1_Logger *, char const*, size_t))&write;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_DefaultConsoleLogger_create
  (
    Ring1_DefaultConsoleLogger** result,
    Ring1_Console_Connection *connection
  )
{
  if (Ring1_Unlikely(!result || !connection)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Ring1_DefaultConsoleLogger* self = malloc(sizeof(Ring1_DefaultConsoleLogger));
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  if (Ring1_DefaultConsoleLogger_construct(RING1_DEFAULTCONSOLELOGGER(self), connection)) {
    return Ring1_Result_Failure;
  }
  *result = self;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() static Ring1_Result
write
  (
    Ring1_DefaultConsoleLogger *self,
    char const* bytes,
    size_t numberOfBytes
  )
{
  Ring1_Result result = 0;
  Ring1_Console_Color oldColor, newColor;
  switch (RING1_CONSOLELOGGER(self)->color) {
  case Ring1_ConsoleLogger_Color_Default:
    newColor = Ring1_Console_Color_Default;
    break;
  case Ring1_ConsoleLogger_Color_Information:
    newColor = Ring1_Console_Color_LightBlue;
    break;
  case Ring1_ConsoleLogger_Color_Warning:
    newColor = Ring1_Console_Color_LightYellow;
    break;
  case Ring1_ConsoleLogger_Color_Error:
    newColor = Ring1_Console_Color_LightRed;
    break;
  default:
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  };
  if (Ring1_Console_Connection_getColor(&oldColor, self->connection)) {
    return Ring1_Result_Failure;
  }
  Ring1_Console_Connection_setColor(self->connection, newColor);
  Ring1_Console_Connection_write(self->connection, bytes, numberOfBytes);
  Ring1_Console_Connection_setColor(self->connection, oldColor);
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_DefaultConsoleLogger*
Ring1_DefaultConsoleLogger_createStandardError
  (
  )
{
  Ring1_Console_Connection *connection = Ring1_Console_getErrorConnection();
  if (!connection) {
    return NULL;
  }
  Ring1_DefaultConsoleLogger *temporary;
  if (Ring1_Unlikely(Ring1_DefaultConsoleLogger_create(&temporary, Ring1_Console_getErrorConnection()))) {
    Ring1_Console_Connection_unref(connection);
    return NULL;
  }
  Ring1_Console_Connection_unref(connection);
  return temporary;
}

Ring1_CheckReturn() Ring1_DefaultConsoleLogger*
Ring1_DefaultConsoleLogger_createStandardOutput
  (
  )
{
  Ring1_Console_Connection *connection = Ring1_Console_getOutputConnection();
  if (!connection) {
    return NULL;
  }
  Ring1_DefaultConsoleLogger *temporary;
  if (Ring1_Unlikely(Ring1_DefaultConsoleLogger_create(&temporary, Ring1_Console_getOutputConnection()))) {
    Ring1_Console_Connection_unref(connection);
    return NULL;
  }
  Ring1_Console_Connection_unref(connection);
  return temporary;
}
