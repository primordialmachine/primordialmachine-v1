// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/Windows/Connection.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#define RING1_PRIVATE (1)
#include "Ring1/Console/Windows/Connection.h"
#undef RING1_PRIVATE


void
Ring1_Console_WindowsConnection_destruct
  (
    Ring1_Console_WindowsConnection* connection
  )
{
  if (connection->handle) {
    connection->handle = NULL;
  }
  Ring1_Console_ConnectionBase_destruct(RING1_CONSOLE_CONNECTIONBASE(connection));
}

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_flush
  (
    Ring1_Console_WindowsConnection* connection
  )
{ return Ring1_Result_Success; }

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_getColor
  (
    Ring1_Console_WindowsConnection *connection,
    Ring1_Console_Color *color
  )
{
  CONSOLE_SCREEN_BUFFER_INFO info;
  if (!GetConsoleScreenBufferInfo(connection->handle, &info)) {
    return Ring1_Result_Failure;
  }
#define Define(internal, external) \
  case external: { *color = internal; } break;
  switch (info.wAttributes & (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)) {
#include "Ring1/Console/Windows/Color.i"
  default:
    return Ring1_Result_Failure;
  };
#undef Define
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_setColor
  (
    Ring1_Console_WindowsConnection* connection,
    Ring1_Console_Color color
  )
{
#define Define(internal, external) \
  case internal: { \
    if (!SetConsoleTextAttribute(connection->handle, external)) { \
      return Ring1_Result_Failure; \
    } \
  } break;
  switch (color) {
    #include "Ring1/Console/Windows/Color.i"
  default:
    return Ring1_Result_Failure;
  };
#undef Define
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_write
  (
    Ring1_Console_WindowsConnection* connection,
    const char* bytes,
    size_t numberOfBytes
  )
{
  DWORD numberOfBytesWritten;
  if (!WriteFile(connection->handle, bytes, (DWORD)numberOfBytes, &numberOfBytesWritten, NULL)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

#define Ring1_Console_WindowsConnection_CreationFlags_StandardOutput (1)

#define Ring1_Console_WindowsConnection_CreationFlags_StandardError (2)

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_construct
  (
    Ring1_Console_WindowsConnection *connection,
    int flags
  )
{
  if (Ring1_Console_ConnectionBase_construct(RING1_CONSOLE_CONNECTIONBASE(connection))) {
    return Ring1_Result_Failure;
  }
  connection->handle = INVALID_HANDLE_VALUE;
  if (flags == Ring1_Console_WindowsConnection_CreationFlags_StandardError) {
    connection->handle = GetStdHandle(STD_ERROR_HANDLE);
  } else if (flags == Ring1_Console_WindowsConnection_CreationFlags_StandardOutput) {
    connection->handle = GetStdHandle(STD_OUTPUT_HANDLE);
  } 
  if (INVALID_HANDLE_VALUE == connection->handle) {
    Ring1_Console_ConnectionBase_destruct(RING1_CONSOLE_CONNECTIONBASE(connection));
    return Ring1_Result_Failure;
  }
  RING1_CONSOLE_CONNECTIONBASE(connection)->destruct = (void (*)(Ring1_Console_ConnectionBase *))&Ring1_Console_WindowsConnection_destruct;
  RING1_CONSOLE_CONNECTIONBASE(connection)->flush = (Ring1_Result (*)(Ring1_Console_ConnectionBase *))&Ring1_Console_WindowsConnection_flush;
  RING1_CONSOLE_CONNECTIONBASE(connection)->getColor = (Ring1_Result (*)(Ring1_Console_ConnectionBase*, Ring1_Console_Color *))&Ring1_Console_WindowsConnection_getColor;
  RING1_CONSOLE_CONNECTIONBASE(connection)->setColor = (Ring1_Result (*)(Ring1_Console_ConnectionBase *, Ring1_Console_Color))&Ring1_Console_WindowsConnection_setColor;
  RING1_CONSOLE_CONNECTIONBASE(connection)->write = (Ring1_Result (*)(Ring1_Console_ConnectionBase *, const char *, size_t))&Ring1_Console_WindowsConnection_write;
  return Ring1_Result_Success;
}

Ring1_Console_WindowsConnection *
Ring1_Console_WindowsConnection_create
  (
    int flags
  )
{
  Ring1_Console_WindowsConnection* connection;
  if (Ring1_Memory_allocate(&connection, sizeof(Ring1_Console_WindowsConnection))) {
    return NULL;
  }
  if (Ring1_Console_WindowsConnection_construct(connection, flags)) {
    Ring1_Memory_deallocate(connection);
    return NULL;
  }
  return connection;
}
