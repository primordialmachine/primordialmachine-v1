// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/Null/Connection.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#define RING1_PRIVATE (1)
#include "Ring1/Console/Null/Connection.h"
#undef RING1_PRIVATE

void
Ring1_Console_NullConnection_destruct
  (
    Ring1_Console_NullConnection* connection
  )
{ Ring1_Console_ConnectionBase_destruct(RING1_CONSOLE_CONNECTIONBASE(connection)); }

Ring1_CheckReturn() Ring1_Result
Ring1_Console_NullConnection_flush
  (
    Ring1_Console_NullConnection* connection
  )
{ return Ring1_Result_Success; }

Ring1_CheckReturn() Ring1_Result
Ring1_Console_NullConnection_getColor
  (
    Ring1_Console_NullConnection *connection,
    Ring1_Console_Color *color
  )
{
  *color = connection->color;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Console_NullConnection_setColor
  (
    Ring1_Console_NullConnection* connection,
    Ring1_Console_Color color
  )
{
  connection->color = color;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Console_NullConnection_write
  (
    Ring1_Console_NullConnection* connection,
    const char* bytes,
    size_t numberOfBytes
  )
{ return Ring1_Result_Success; }

Ring1_CheckReturn() Ring1_Result
Ring1_Console_NullConnection_construct
  (
    Ring1_Console_NullConnection *connection
  )
{
  if (Ring1_Console_ConnectionBase_construct(RING1_CONSOLE_CONNECTIONBASE(connection))) {
    return Ring1_Result_Failure;
  }
  connection->color = Ring1_Console_Color_Default;
  RING1_CONSOLE_CONNECTIONBASE(connection)->destruct = (void (*)(Ring1_Console_ConnectionBase *))&Ring1_Console_NullConnection_destruct;
  RING1_CONSOLE_CONNECTIONBASE(connection)->flush = (Ring1_Result (*)(Ring1_Console_ConnectionBase *))&Ring1_Console_NullConnection_flush;
  RING1_CONSOLE_CONNECTIONBASE(connection)->getColor = (Ring1_Result (*)(Ring1_Console_ConnectionBase *, Ring1_Console_Color *))&Ring1_Console_NullConnection_getColor;
  RING1_CONSOLE_CONNECTIONBASE(connection)->setColor = (Ring1_Result (*)(Ring1_Console_ConnectionBase *, Ring1_Console_Color))&Ring1_Console_NullConnection_setColor;
  RING1_CONSOLE_CONNECTIONBASE(connection)->write = (Ring1_Result (*)(Ring1_Console_ConnectionBase *, const char *, size_t))&Ring1_Console_NullConnection_write;
  return Ring1_Result_Success;
}

Ring1_Console_NullConnection *
Ring1_Console_NullConnection_create
  (
  )
{
  Ring1_Console_NullConnection* connection;
  if (Ring1_Memory_allocate(&connection, sizeof(Ring1_Console_NullConnection))) {
    return NULL;
  }
  if (Ring1_Console_NullConnection_construct(connection)) {
    Ring1_Memory_deallocate(connection);
    return NULL;
  }
  return connection;
}
