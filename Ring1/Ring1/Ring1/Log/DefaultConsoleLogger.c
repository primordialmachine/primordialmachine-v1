// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Log/DefaultConsoleLogger.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_PRIVATE (1)
#include "Ring1/Log/DefaultConsoleLogger.h"
#undef RING1_PRIVATE

#include "Ring1/Console.h"

Mkx_Type_DefineClassType("Ring1.DefaultConsoleLogger",
                         Mkx_DefaultConsoleLogger,
                         MKX_DEFAULTCONSOLELOGGER,
                         Mkx_ConsoleLogger,
                         Mkx_Type_UseDefaultMemoryManager(),
                         Mkx_Type_ImplementInterfaces());

Ring1_CheckReturn() static int
write
  (
    Mkx_DefaultConsoleLogger *self,
    const char *bytes,
    size_t numberOfBytes
  );
  
Ring1_NonNull() static void
Mkx_DefaultConsoleLogger_destruct
  (
    Mkx_DefaultConsoleLogger *self
  )
{
  if (self->connection) {
    Ring1_Console_Connection_unref(self->connection);
    self->connection = NULL;
  }
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_DefaultConsoleLogger_construct
  (
    Mkx_DefaultConsoleLogger* self,
    Ring1_Console_Connection *connection
  )
{
  if (Ring1_Unlikely(!self || !connection))
  { return 1; }
  Mkx_Type* __type = MKX_TYPE_GET(Mkx_DefaultConsoleLogger);
  if (Ring1_Unlikely(!__type)) return 1;
  if (Ring1_Unlikely(Mkx_ConsoleLogger_construct(MKX_CONSOLELOGGER(self))))
  { return 1; }
  self->connection = connection;
  Ring1_Console_Connection_ref(connection);
  MKX_OBJECT(self)->type = __type;
  return 0;
}

Ring1_CheckReturn() int
Mkx_DefaultConsoleLogger_create
  (
    Mkx_DefaultConsoleLogger** result,
    Ring1_Console_Connection *connection
  )
{
  if (Ring1_Unlikely(!result || !connection))
  { return 1; }
  Mkx_Type* type = MKX_TYPE_GET(Mkx_DefaultConsoleLogger);
  if (Ring1_Unlikely(!type)) return 1;
  Mkx_DefaultConsoleLogger* self = Mkx_Object_allocate(type);
  if (Ring1_Unlikely(!self)) return 1;
  if (Ring1_Unlikely(Mkx_DefaultConsoleLogger_construct(self, connection)))
  {
    Mkx_Object_unreference(MKX_OBJECT(self));
    return 1;
  }
  *result = self;
  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() static int
Mkx_DefaultConsoleLogger_Dispatch_construct
  (
    Mkx_DefaultConsoleLogger_Dispatch *self
  )
{
  MKX_LOGGER_DISPATCH(self)->write = (int (*)(Mkx_Logger *, const char *, size_t))&write;
  return 0;
}

Ring1_NonNull() static void
Mkx_DefaultConsoleLogger_Dispatch_destruct
  (
    Mkx_DefaultConsoleLogger_Dispatch* self
  )
{}

Ring1_CheckReturn() static int
write
  (
    Mkx_DefaultConsoleLogger *self,
    const char *bytes,
    size_t numberOfBytes
  )
{
  int result = 0;
  Ring1_Console_Color oldColor, newColor;
  switch (MKX_CONSOLELOGGER(self)->color)
  {
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
    return 1;
  };
  if (Ring1_Console_Connection_getColor(&oldColor, self->connection))
  { return 1; }
  Ring1_Console_Connection_setColor(self->connection, newColor);
  Ring1_Console_Connection_write(self->connection, bytes, numberOfBytes);
  Ring1_Console_Connection_setColor(self->connection, oldColor);
  return 1;
}

Ring1_CheckReturn() Mkx_DefaultConsoleLogger*
Mkx_DefaultConsoleLogger_createStandardError
  (
  )
{
  Ring1_Console_Connection *connection = Ring1_Console_getErrorConnection();
  if (!connection) {
    return NULL;
  }
  Mkx_DefaultConsoleLogger *temporary;
  if (Ring1_Unlikely(Mkx_DefaultConsoleLogger_create(&temporary, Ring1_Console_getErrorConnection())))
  { Ring1_Console_Connection_unref(connection); return NULL; }
  Ring1_Console_Connection_unref(connection);
  return temporary;
}

Ring1_CheckReturn() Mkx_DefaultConsoleLogger*
Mkx_DefaultConsoleLogger_createStandardOutput
  (
  )
{
  Ring1_Console_Connection *connection = Ring1_Console_getOutputConnection();
  if (!connection) {
    return NULL;
  }
  Mkx_DefaultConsoleLogger *temporary;
  if (Ring1_Unlikely(Mkx_DefaultConsoleLogger_create(&temporary, Ring1_Console_getOutputConnection())))
  { Ring1_Console_Connection_unref(connection); return NULL; }
  Ring1_Console_Connection_unref(connection);
  return temporary;
}
