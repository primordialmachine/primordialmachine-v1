// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Console.h"


#include "Ring1/Memory.h"
#include "Ring1/Console/Null/Connection.h"
#include "Ring1/Console/Windows/Connection.h"


static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

Ring1_Module_Define(Ring1, Console, initializeModule, uninitializeModule)

static Ring1_Memory_ModuleHandle memory = Ring1_Memory_ModuleHandle_Invalid;

static Ring1_Result
initializeModule
  (
  )
{
  memory = Ring1_Memory_ModuleHandle_acquire();
  if (!memory) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{ 
  Ring1_Memory_ModuleHandle_relinquish(memory);
  memory = Ring1_Memory_ModuleHandle_Invalid;
}

Ring1_NoDiscardReturn() Ring1_Console_Connection*
Ring1_Console_getOutputConnection
  (
  )
{ return Ring1_Console_WindowsConnection_create(Ring1_Console_WindowsConnection_CreationFlags_StandardOutput); }

Ring1_NoDiscardReturn() Ring1_Console_Connection*
Ring1_Console_getErrorConnection
  (
  )
{ return Ring1_Console_WindowsConnection_create(Ring1_Console_WindowsConnection_CreationFlags_StandardError); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_flush
  (
    Ring1_Console_Connection *connection
  )
{ return Ring1_Console_ConnectionBase_flush(connection); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_getColor
  (
    Ring1_Console_Color *result,
    Ring1_Console_Connection* connection
  )
{ return Ring1_Console_ConnectionBase_getColor(connection, result); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_setColor
  (
    Ring1_Console_Connection* connection,
    Ring1_Console_Color color
  )
{ return Ring1_Console_ConnectionBase_setColor(connection, color); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_Connection_write
  (
    Ring1_Console_Connection* connection,
    const char* bytes,
    size_t numberOfBytes
  )
{ return Ring1_Console_ConnectionBase_write(connection, bytes, numberOfBytes); }

void
Ring1_Console_Connection_ref
  (
    Ring1_Console_Connection* connection
  )
{ Ring1_Console_ConnectionBase_ref(connection); }

void
Ring1_Console_Connection_unref
  (
    Ring1_Console_Connection* connection
  )
{ Ring1_Console_ConnectionBase_unref(connection); }
