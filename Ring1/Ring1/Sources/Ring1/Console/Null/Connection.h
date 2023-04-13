// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/Null/Connection.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_CONSOLE_NULLCONNECTION_H_INCLUDED)
#define RING1_CONSOLE_NULLCONNECTION_H_INCLUDED


#include "Ring1/Console/ConnectionBase.h"


typedef struct Ring1_Console_NullConnection {
  Ring1_Console_ConnectionBase parent;
  Ring1_Console_Color color;
} Ring1_Console_NullConnection;

void
Ring1_Console_NullConnection_destruct
  (
    Ring1_Console_NullConnection* connection
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_NullConnection_flush
  (
    Ring1_Console_NullConnection* connection
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_NullConnection_getColor
  (
    Ring1_Console_NullConnection* connection,
    Ring1_Console_Color* color
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_NullConnection_setColor
  (
    Ring1_Console_NullConnection* connection,
    Ring1_Console_Color color
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_NullConnection_write
  (
    Ring1_Console_NullConnection* connection,
    const char* bytes,
    size_t numberOfBytes
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_NullConnection_construct
  (
    Ring1_Console_NullConnection* connection
  );

Ring1_Console_NullConnection*
Ring1_Console_NullConnection_create
  (
  );


#endif // RING1_CONSOLE_NULLCONNECTION_H_INCLUDED
