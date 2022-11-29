// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/Windows/Connection.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONSOLE_WINDOWSCONNECTION_H_INCLUDED)
#define RING1_CONSOLE_WINDOWSCONNECTION_H_INCLUDED


#include "Ring1/Console/ConnectionBase.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX


typedef struct Ring1_Console_WindowsConnection {
  Ring1_Console_ConnectionBase parent;
  HANDLE handle;
} Ring1_Console_WindowsConnection;

void
Ring1_Console_WindowsConnection_destruct
  (
    Ring1_Console_WindowsConnection* connection
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_flush
  (
    Ring1_Console_WindowsConnection* connection
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_getColor
  (
    Ring1_Console_WindowsConnection* connection,
    Ring1_Console_Color* color
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_setColor
  (
    Ring1_Console_WindowsConnection* connection,
    Ring1_Console_Color color
  );

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_write
  (
    Ring1_Console_WindowsConnection* connection,
    const char* bytes,
    size_t numberOfBytes
  );

#define Ring1_Console_WindowsConnection_CreationFlags_StandardOutput (1)

#define Ring1_Console_WindowsConnection_CreationFlags_StandardError (2)

Ring1_CheckReturn() Ring1_Result
Ring1_Console_WindowsConnection_construct
  (
    Ring1_Console_WindowsConnection* connection,
    int flags
  );

Ring1_Console_WindowsConnection*
Ring1_Console_WindowsConnection_create
  (
    int flags
  );


#endif  // RING1_CONSOLE_WINDOWSCONNECTION_H_INCLUDED
