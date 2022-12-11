// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Console/ConnectionBase.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)


#include "Ring1/Console/ConnectionBase.h"


void
Ring1_Console_ConnectionBase_destruct
  (
    Ring1_Console_ConnectionBase* connection
  )
{/*Intentionally empty.*/}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_construct
  (
    Ring1_Console_ConnectionBase *connection
  )
{
  connection->referenceCount = 1;
  connection->destruct = &Ring1_Console_ConnectionBase_destruct;
  connection->getColor = NULL;
  connection->flush = NULL;
  connection->setColor = NULL;
  connection->write = NULL;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_flush
  (
    Ring1_Console_ConnectionBase* connection
  )
{
  if (!connection || !connection->flush) {
    return Ring1_Result_Failure;
  }
  return connection->flush(connection);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_getColor
  (
    Ring1_Console_ConnectionBase* connection,
    Ring1_Console_Color *color
  )
{
  if (!connection || !connection->getColor) {
    return Ring1_Result_Failure;
  }
  return connection->getColor(connection, color);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_setColor
  (
    Ring1_Console_ConnectionBase* connection,
    Ring1_Console_Color color
  )
{
  if (!connection || !connection->setColor) {
    return Ring1_Result_Failure;
  }
  return connection->setColor(connection, color);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Console_ConnectionBase_write
  (
    Ring1_Console_ConnectionBase* connection,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!connection || !connection->write || !bytes) {
    return Ring1_Result_Failure;
  }
  return connection->write(connection, bytes, numberOfBytes);
}

void
Ring1_Console_ConnectionBase_ref
  (
    Ring1_Console_ConnectionBase* connection
  )
{ Ring1_ReferenceCounter_increment(&connection->referenceCount); }

void
Ring1_Console_ConnectionBase_unref
  (
    Ring1_Console_ConnectionBase* connection
  )
{
  if (!Ring1_ReferenceCounter_decrement(&connection->referenceCount)) {
    connection->destruct(connection);
    Ring1_Memory_deallocate(connection);
  }
}
